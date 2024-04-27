/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: VersionControl.C,v $
 *  $Date: 1999/08/27 15:32:10 $
 *  $Revision: 1.1.1.1.2.1 $
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
 * $Log: VersionControl.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:10  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:18  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/09/02  18:54:53  lazy
 * unistd.h and sys/wait.h included.
 *
 * Revision 1.1  1997/09/02  18:21:12  lazy
 * Initial revision
 *
 */

#include "lic.h"
#include "LApp.h"
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define OPEN_FILE_SCRIPT "vcopen"
#define SAVE_FILE_SCRIPT "vcsave"
#define CLOSE_FILE_SCRIPT "vcclose"

// -------------------------------------
// openFileHook()
// -------------------------------------

Boolean 
openFileHook(char *file)
{
  char com[PATH_MAX];
  struct sigaction saction, oaction;
  pid_t pid;
  int status;
  char *argv[3];

  if(!app->getVersionControl())
    return FALSE;

  saction.sa_handler = SIG_DFL;
  saction.sa_flags = 0;
  sigemptyset(&saction.sa_mask);
  sigaction(SIGCHLD, &saction, &oaction);

  switch(pid=fork()) {
  case -1:
    perror("fork()");
  case 0:
    sprintf(com, "%s/%s", app->getBinPath(), OPEN_FILE_SCRIPT);
    argv[0] = com;
    argv[1] = file;
    argv[2] = NULL;
    if(execve(com, argv, NULL) < 0)
      perror("execve()");
    exit(1);
    break;
  default:
    wait(&status);
    break;
  }

  sigaction(SIGCHLD, &oaction, NULL);

  return True;
}

// -------------------------------------
// saveFileHook()
// -------------------------------------

Boolean
saveFileHook(char *file)
{
  char com[PATH_MAX];
  struct sigaction saction, oaction;
  pid_t pid;
  int status;
  char *argv[3];

  if(!app->getVersionControl())
    return FALSE;

  saction.sa_handler = SIG_DFL;
  saction.sa_flags = 0;
  sigemptyset(&saction.sa_mask);
  sigaction(SIGCHLD, &saction, &oaction);

  switch(pid=fork()) {
  case -1:
    perror("fork()");
  case 0:
    sprintf(com, "%s/%s", app->getBinPath(), SAVE_FILE_SCRIPT);
    argv[0] = com;
    argv[1] = file;
    argv[2] = NULL;
    if(execve(com, argv, NULL) < 0)
      perror("execve()");
    exit(1);
    break;
  default:
    wait(&status);
    break;
  }

  sigaction(SIGCHLD, &oaction, NULL);

  return True;
}

// -------------------------------------
// closeFileHook()
// -------------------------------------

Boolean
closeFileHook(char *file)
{
  char com[PATH_MAX];
  struct sigaction saction, oaction;
  pid_t pid;
  int status;
  char *argv[3];

  if(!app->getVersionControl())
    return FALSE;

  saction.sa_handler = SIG_DFL;
  saction.sa_flags = 0;
  sigemptyset(&saction.sa_mask);
  sigaction(SIGCHLD, &saction, &oaction);

  switch(pid=fork()) {
  case -1:
    perror("fork()");
  case 0:
    sprintf(com, "%s/%s", app->getBinPath(), CLOSE_FILE_SCRIPT);
    argv[0] = com;
    argv[1] = file;
    argv[2] = NULL;
    if(execve(com, argv, NULL) < 0)
      perror("execve()");
    exit(1);
    break;
  default:
    wait(&status);
    break;
  }

  sigaction(SIGCHLD, &oaction, NULL);

  return True;
}

