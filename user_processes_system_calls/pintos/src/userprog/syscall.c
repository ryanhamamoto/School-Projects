/* 
 * This file is derived from source code for the Pintos
 * instructional operating system which is itself derived
 * from the Nachos instructional operating system. The 
 * Nachos copyright notice is reproduced in full below. 
 *
 * Copyright (C) 1992-1996 The Regents of the University of California.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose, without fee, and
 * without written agreement is hereby granted, provided that the
 * above copyright notice and the following two paragraphs appear
 * in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE
 * AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
 * BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
 * MODIFICATIONS.
 *
 * Modifications Copyright (C) 2017-2018 David C. Harrison. 
 * All rights reserved.
 */

#include <stdio.h>
#include <syscall-nr.h>
#include <list.h>

#include "devices/shutdown.h"
#include "devices/input.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/inode.h"
#include "filesys/directory.h"
#include "threads/palloc.h"
#include "threads/malloc.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/lock.h"
#include "userprog/syscall.h"
#include "userprog/process.h"
#include "userprog/umem.h"

static struct lock syscall_lock;
static void syscall_handler(struct intr_frame *);

static void write_handler(struct intr_frame *);
static void exit_handler(struct intr_frame *);
static void open_handler(struct intr_frame *f);
static void read_handler(struct intr_frame *f);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  lock_init(&syscall_lock);
}

static void
syscall_handler(struct intr_frame *f)
{
  int syscall;
  ASSERT( sizeof(syscall) == 4 ); // assuming x86

  // The system call number is in the 32-bit word at the caller's stack pointer.
  umem_read(f->esp, &syscall, sizeof(syscall));

  // Store the stack pointer esp, which is needed in the page fault handler.
  // Do NOT remove this line
  thread_current()->current_esp = f->esp;

  switch (syscall) {
  case SYS_HALT: 
    shutdown_power_off();
    break;

  case SYS_EXIT: 
    exit_handler(f);
    break;
      
  case SYS_WRITE: 
    write_handler(f);
    break;
	
  case SYS_EXEC:
    break;

  case SYS_WAIT:
    break;
	
  case SYS_CREATE:
    break;
	
  case SYS_REMOVE:
    break;
	
  case SYS_OPEN:
    open_handler(f);
    break;
	
  case SYS_FILESIZE:
    break;
	
  case SYS_READ:
    read_handler(f);
    break;

  case SYS_SEEK:
    break;

  case SYS_TELL:
    break;

  case SYS_CLOSE:
    break;

  default:
    printf("[ERROR] system call %d is unimplemented!\n", syscall);
    thread_exit();
    break;
  }
}

/****************** System Call Implementations ********************/

void sys_exit(int status) 
{
  printf("%s: exit(%d)\n", thread_current()->name, status);
  thread_exit();
}

static void exit_handler(struct intr_frame *f) 
{
  int exitcode;
  umem_read(f->esp + 4, &exitcode, sizeof(exitcode));

  sys_exit(exitcode);
}

/*
 * BUFFER+0 and BUFFER+size should be valid user adresses
 */
static uint32_t sys_write(int fd, const void *buffer, unsigned size)
{
    umem_check((const uint8_t*) buffer);
    umem_check((const uint8_t*) buffer + size - 1);

    int ret = -1;
    struct file* write_file;
	
    if (fd == 1) // write to stdout
    {
      putbuf(buffer, size);
      ret = size;
    } else { //write to an open file
      lock_acquire(&syscall_lock);
      write_file = thread_current()->open_files[fd];
	  if(write_file)
      {
        ret = file_write(write_file, buffer, size);
      } else {
        ret = -1;
      }
      lock_release(&syscall_lock);
    }
    return (uint32_t) ret;
}

static void write_handler(struct intr_frame *f)
{
    int fd;
    const void *buffer;
    unsigned size;
    
    umem_read(f->esp + 4, &fd, sizeof(fd));
    umem_read(f->esp + 8, &buffer, sizeof(buffer));
    umem_read(f->esp + 12, &size, sizeof(size));
    
    f->eax = sys_write(fd, buffer, size);
}

static uint32_t sys_read(int fd, void *buffer, unsigned size)
{
    umem_check((const uint8_t*) buffer);
    umem_check((const uint8_t*) buffer + size - 1);

    int ret = -1;
    struct file* read_file;
    if (fd == 0) //read from stdin
    {
      putbuf(buffer, size);
      ret = size;
    } else { //read an open file
      lock_acquire(&syscall_lock);
      read_file = thread_current()->open_files[fd];
      if(read_file)
      {
        ret = file_read(read_file, buffer, size);
      } else {
        ret = -1;
      }
      lock_release(&syscall_lock);
    }

    return (uint32_t) ret;
}

static void read_handler(struct intr_frame *f)
{
    int fd;
    void *buffer;
    unsigned size;
    
    umem_read(f->esp + 4, &fd, sizeof(fd));
    umem_read(f->esp + 8, &buffer, sizeof(buffer));
    umem_read(f->esp + 12, &size, sizeof(size));
    
    f->eax = sys_read(fd, buffer, size);
}

static void open_handler(struct intr_frame *f)
{
    const char* cmdline_file;
    umem_read(f->esp + 4, &cmdline_file, sizeof(char *));
    int i;
    struct file* open_file = filesys_open(cmdline_file);
    if(open_file != NULL)
    {
      for(i = 2; i < MAX_OPEN_FILES; i++)
      {
        if(thread_current()->open_files[i] == NULL)
        {
          thread_current()->open_files[i] = open_file;
          break;
        }
      }
      f->eax = i;
    } else {
      f->eax = -1;
    }
    return;
}
