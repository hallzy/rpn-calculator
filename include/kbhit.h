#ifndef _KBHIT_H_
#define _KBHIT_H_

#ifdef WINDOWS
#include <conio.h>
#define ENTER_KEY '\r'
#else

#define ENTER_KEY '\n'

int kbhit(void);
void singleCharacterInputInit();
#endif //  WINDOWS

char getCharacter();

#endif // _KBHIT_H_
