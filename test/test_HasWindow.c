#include "test_HasWindow.h"
#include <unity.h>
#include <SDL2/SDL.h>

typedef Uint32 milliseconds_t;
milliseconds_t const look_at_window = 1000;

/* -------------------- */
/* | Helper Functions | */
/* -------------------- */
void ReportError(char const *sdl_funcname, int error_code){
    printf("- SDL error: %s\n", SDL_GetError());
    printf("\t- Function: %s\n\t- Error code: %d\n", sdl_funcname, error_code);
    /* =====[ Example ]===== */
    /* No available video device */
    /* Error code from SDL_Init: -1 */
}
/* ------------------------------------------------------- */
/* | Test environment has video device for running tests | */
/* ------------------------------------------------------- */
bool VideoDeviceIsAvailable(void){
    int init_error_code = SDL_Init(SDL_INIT_VIDEO);
    if (init_error_code != 0){
        // printf("Cygwin users: bash: `xwin &` to start `XWin` first.\n");
        // printf("Then bash: `twm &` or `fvwm &` to start a Windows manager.\n");
        // printf("Or in one command: `startx /usr/bin/fvwm2 &`\n");
        printf(
            "\n# Video Device Is Not Available\n"
            "Cygwin users: **Launch X11 X Server and a Windows Manager before "
            "running executable.**\n"
            "```bash\n"
            "$ startx /usr/bin/openbox &\n"
            "```\n\n"
            );
        ReportError("SDL_Init", init_error_code);
    }
    SDL_Quit();
    return (init_error_code==0) ? true : false;
    }

/* --------- */
/* | Tests | */
/* --------- */

/* =====[ Try_the_basics_with_SDL_Init ]===== */
void SDL_Init_returns_0_on_success(void){
    /* =====[ Operate ]===== */
    int init_error_code = SDL_Init(SDL_INIT_VIDEO);
    if (init_error_code != 0) ReportError("SDL_Init", init_error_code);
    /* =====[ Test ]===== */
    TEST_ASSERT_EQUAL(0, init_error_code);
    /* =====[ Cleanup ]===== */
    SDL_Quit();
}
void SDL_Init_initializes_video_subsystem(void){
    /* =====[ Operate ]===== */
    int init_error_code = SDL_Init(SDL_INIT_VIDEO);
    if (init_error_code != 0) ReportError("SDL_Init", init_error_code);
    /* =====[ Test ]===== */
    bool video_subsystem_initialized = SDL_WasInit(SDL_INIT_VIDEO);
    TEST_ASSERT_TRUE(video_subsystem_initialized);
    /* =====[ Cleanup ]===== */
    SDL_Quit();
}
void SDL_Init_initializes_audio_subsystem(void){
    /* =====[ Operate ]===== */
    int init_error_code = SDL_Init(SDL_INIT_AUDIO);
    if (init_error_code != 0) ReportError("SDL_Init", init_error_code);
    TEST_ASSERT_EQUAL(0, init_error_code);
    /* =====[ Test ]===== */
    bool audio_subsystem_initialized = SDL_WasInit(SDL_INIT_AUDIO);
    TEST_ASSERT_TRUE(audio_subsystem_initialized);
    /* =====[ Cleanup ]===== */
    SDL_Quit();
}

/* =====[ Try_window_management ]===== */
void Setup_SDL_Basics(void){
    int init_error_code = SDL_Init(
        SDL_INIT_VIDEO | SDL_INIT_AUDIO
        );
    if (init_error_code != 0) ReportError("SDL_Init", init_error_code);
}
void Shutdown_SDL(void){ SDL_Quit(); }
void SDL_CreateWindow_returns_NULL_if_it_cannot_make_a_window(void){
    /* =====[ Setup ]===== */
    SDL_Window *window;
    /* =====[ Operate ]===== */
    window = SDL_CreateWindow(
        "An SDL2 window",
        SDL_WINDOWPOS_UNDEFINED, // x
        SDL_WINDOWPOS_UNDEFINED, // y
        640, // width
        480, // height
        SDL_WINDOW_OPENGL // window usable with OpenGL context
        /* SDL_WINDOW_FULLSCREEN // Fullscreen overrides width and height. */
        );
    /* ---------------------------------------------------------------------- */
    /* SDL_WINDOW_OPENGL */
    /*     libGL error: Screen is not Windows-DRI capable */
    /*     see <https://en.wikipedia.org/wiki/Direct_Rendering_Infrastructure> */
    /* ---------------------------------------------------------------------- */
    //
    if (window == NULL) printf("\tSDL_CreateWindow error: %s\n", SDL_GetError());
    /* =====[ Manual Test: look for the window ]===== */
    else SDL_Delay(look_at_window);
    // Result: window style depends on window manager (tvm, fvwm, etc.)
    /* =====[ Test ]===== */
    TEST_ASSERT_NOT_NULL(window);
    /* =====[ Cleanup ]===== */
    SDL_DestroyWindow(window);
}
/* TODO: CreateWindowAndRenderer has libGL error seen with flag SDL_WINDOW_OPENGL */
void SDL_CreateWindowAndRenderer_writes_NULL_to_window_and_renderer_if_it_cannot_make_them(void){
    /* =====[ Setup ]===== */
    SDL_Window *window;
    SDL_Renderer *renderer;
    /* =====[ Operate ]===== */
    if (SDL_CreateWindowAndRenderer(
            0, // width
            0, // height
            SDL_WINDOW_FULLSCREEN, // flag - see SDL_CreateWindow()
            /* 0 | SDL_WINDOW_FULLSCREEN, // does not prevent libGL error */
            &window,  // pointer filled with window or NULL on error
            &renderer // pointer filled with window or NULL on error
            ))
        printf("\tSDL cannot create window and renderer: "
               "%s\n", SDL_GetError());
    else { // render an image in the window
        SDL_Surface *surface;
        SDL_Texture *texture;
        surface = SDL_LoadBMP("img/cuphead.bmp");
        if (!surface) printf(
            "\tSDL cannot create surface from image: "
            "%s", SDL_GetError());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) printf(
            "\tSDL cannot create texture from surface: "
            "%s", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    /* =====[ Manual Test: look for the window ]===== */
        SDL_Delay(look_at_window);
        SDL_DestroyTexture(texture);
    }
    /* =====[ Test ]===== */
    TEST_ASSERT_NOT_NULL(window);
    TEST_ASSERT_NOT_NULL(renderer);
    /* =====[ Cleanup ]===== */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
