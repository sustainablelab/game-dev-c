#ifndef _TEST_HASWINDOW_H
#define _TEST_HASWINDOW_H

#include <stdbool.h>

bool VideoDeviceIsAvailable(void);
void SDL_Init_initializes_video_subsystem(void);
void SDL_Init_returns_0_on_success(void);
void SDL_Init_initializes_audio_subsystem(void);
void Setup_SDL_Basics(void);
void Shutdown_SDL(void);
void SDL_CreateWindow_returns_NULL_if_it_cannot_make_a_window(void);
void SDL_CreateWindowAndRenderer_writes_NULL_to_window_and_renderer_if_it_cannot_make_them(void);

#endif // _TEST_HASWINDOW_H
