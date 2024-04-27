/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MegaPipe.c,v $
 *  $Date: 1999/08/27 15:31:41 $
 *  $Revision: 1.1.1.1.2.2 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: MegaPipe.c,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:31:41  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:45  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/28 14:01:28  lazy
 * Added the behaviour for logging.
 * Environment variable VDX_LOGFILE is examined.
 *
 * Revision 1.1  1997/07/25 20:29:27  lazy
 * Initial revision
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

#define LOGFILE "VDX_LOGFILE"
  
static void doit(int rfd, int wfd);
static void sigpipe_handler(int num);

typedef struct _RingBuffer {
  char buffer[BUFSIZ];
  int numBytes;
  struct _RingBuffer *next;
} RingBuffer;

static int buffer_get(RingBuffer *ringBuffer, char *buf, int *numBytes);
static void buffer_insert(RingBuffer *ringBuffer, char *buf, int numBytes);
static void buffer_put(RingBuffer *ringBuffer, char *buf, int numBytes);
static RingBuffer *new_buffer();

int
redirectOutput()
{
  int readPipe[2], writePipe[2];
  struct sigaction s_action;

  if(pipe(readPipe) < 0) {
    perror("create read pipe");
    return -1;
  }
  if(pipe(writePipe) < 0) {
    perror("create write pipe");
    return -1;
  }

  switch(fork()) {
  case -1:
    perror("fork");
    return -1;

  case 0:
    /* child process */
    close(writePipe[0]);
    close(readPipe[1]);

    if(setpgid(0, 0) < 0)
      perror("setpgid()");

    s_action.sa_handler = (void (*)(int))sigpipe_handler;
    s_action.sa_flags = 0;
    sigemptyset(&s_action.sa_mask);
    sigaction(SIGPIPE, &s_action, NULL);

    fcntl(readPipe[0], F_SETFL, fcntl(readPipe[0], F_GETFL) | O_NONBLOCK);
    fcntl(writePipe[1], F_SETFL, fcntl(writePipe[1], F_GETFL) | O_NONBLOCK);
    doit(readPipe[0], writePipe[1]);

    break;

  default:
    /* parent process */
    close(writePipe[1]);
    close(readPipe[0]);
    
    dup2(readPipe[1], fileno(stdout));
    dup2(readPipe[1], fileno(stderr));

    close(readPipe[1]);

    fflush(stdout);
    setbuf(stdout, NULL);
    fflush(stderr);
    setbuf(stderr, NULL);

    fcntl(writePipe[0], F_SETFL, fcntl(writePipe[0], F_GETFL) | O_NONBLOCK);
    return writePipe[0];   /* return the pipe end that we have to read from */
  }
  exit(0);
  return -1;
}



static void
doit(int rfd, int wfd)
{
  char buf[BUFSIZ], *ptr;
  fd_set readfds, writefds;
  int max_fd, set_rfd, set_wfd;
  int num_bytes, n;
  RingBuffer *ring_buffer;
  FILE *logfile;

  set_rfd = 1;
  set_wfd = 0;

  ring_buffer = new_buffer();
  
  logfile = NULL;
  if(getenv(LOGFILE)) {
    logfile = fopen(getenv(LOGFILE), "w");
  }

  while(1) {

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    if(set_rfd) {
      FD_SET(rfd, &readfds);
      max_fd = rfd;
    }
    if(set_wfd) {
      FD_SET(wfd, &writefds);
      max_fd = wfd;
    }
    if(set_rfd && set_wfd)
      max_fd = rfd > wfd ? rfd : wfd;
    max_fd++;

    if(select(max_fd, &readfds, &writefds, NULL, NULL) < 0) {
      perror("select");
      if(logfile) {
	fclose(logfile);
      }
      exit(0);
    }

    if(FD_ISSET(rfd, &readfds)) {
      int first = 1;
      while((num_bytes = read(rfd, buf, BUFSIZ)) > 0) {
	first = 0;
	buffer_put(ring_buffer, buf, num_bytes);
	if(num_bytes < BUFSIZ)
	  break;
      }
      if(num_bytes == 0 && first) {  /* broken pipe */
	if(logfile) {
	  fclose(logfile);
	}
	exit(0);
      }
    }

    if(set_wfd && !FD_ISSET(wfd, &writefds))
      continue;

    set_wfd = 0;
    do {
      if(buffer_get(ring_buffer, buf, &n) != -1) {
	if(logfile) {
	  fwrite(buf, sizeof(char), n, logfile);
	  fflush(logfile);
	}
	num_bytes = write(wfd, buf, n);
	if(num_bytes < n) {                        /* ups, pipe full */
	  if(num_bytes == -1)
	    num_bytes = 0;
	  ptr = buf + num_bytes;
	  buffer_insert(ring_buffer, ptr, n - num_bytes);
	  set_wfd = 1;
	  break;
	}
      } else {                                     /* nothing more */
	break;
      }
    } while(num_bytes == n);

  }
}

static void
sigpipe_handler(int num)
{
  exit(0);
}

static RingBuffer *
new_buffer()
{
  RingBuffer *ptr;

  ptr = (RingBuffer*)malloc(sizeof(RingBuffer));
  memset(ptr, 0, sizeof(RingBuffer));
  
  return ptr;
}

static void
buffer_put(RingBuffer *ringBuffer, char *buf, int numBytes)
{
  RingBuffer *ptr;

  ptr = ringBuffer;
  while(ptr->next) ptr = ptr->next;

  ptr->next = new_buffer();
  ptr = ptr->next;

  memcpy(ptr->buffer, buf, numBytes);
  ptr->numBytes = numBytes;
}

static int
buffer_get(RingBuffer *ringBuffer, char *buf, int *numBytes)
{
  RingBuffer *ptr;

  ptr = ringBuffer;
  if(ptr->next) {
    ptr = ptr->next;
    ringBuffer->next = ptr->next;
  } else {
    return -1;
  }
  memcpy(buf, ptr->buffer, ptr->numBytes);
  *numBytes = ptr->numBytes;
  free(ptr);
  
  return 0;
}

static void
buffer_insert(RingBuffer *ringBuffer, char *buf, int numBytes) 
{
  RingBuffer *ptr;

  ptr = new_buffer();
  ptr->next = ringBuffer->next;
  ringBuffer->next = ptr;

  memcpy(ptr->buffer, buf, numBytes);
  ptr->numBytes = numBytes;
}
