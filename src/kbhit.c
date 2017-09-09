#ifdef WINDOWS
#include <conio.h>
#else

#include <stdio.h>
#include <string.h>

#include <sys/time.h>
#include <termios.h>
#include <stdlib.h>

#include "kbhit.h"

#ifndef TEST
static struct termios g_old_kbd_mode;

// did somebody press somthing???
int kbhit(void){
  struct timeval timeout;
  fd_set read_handles;
  int status;

  // check stdin (fd 0) for activity
  FD_ZERO(&read_handles);
  FD_SET(0, &read_handles);
  timeout.tv_sec = timeout.tv_usec = 0;
  status = select(0 + 1, &read_handles, NULL, NULL, &timeout);
  return status;
}

// put the things as they were befor leave..!!!
static void old_attr(void){
  tcsetattr(0, TCSANOW, &g_old_kbd_mode);
}

void singleCharacterInputInit() {
struct termios new_kbd_mode;

// put keyboard (stdin, actually) in raw, unbuffered mode
  tcgetattr(0, &g_old_kbd_mode);
  memcpy(&new_kbd_mode, &g_old_kbd_mode, sizeof(struct termios));

  new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
  new_kbd_mode.c_cc[VTIME] = 0;
  new_kbd_mode.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &new_kbd_mode);
  atexit(old_attr);
}

#endif // TEST
#endif // WINDOWS

#ifndef TEST
char getCharacter() {
#ifndef WINDOWS
  return getchar();
#else
  return getch();
#endif // WINDOWS
}
#endif // TEST
