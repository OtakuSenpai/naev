

#ifndef PLAYER_H
#  define PLAYER_H


#include "SDL.h"


typedef enum { KEYBIND_NULL, KEYBIND_KEYBOARD, KEYBIND_JAXIS, KEYBIND_JBUTTON } KeybindType;


/*
 * input
 */
void input_init (void);
void input_exit (void);
void input_setKeybind( char *keybind, KeybindType type, int key, int reverse );
void input_handle( SDL_Event* event );



#endif /* PLAYER_H */
