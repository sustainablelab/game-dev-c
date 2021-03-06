#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef Uint32 milliseconds_t;
milliseconds_t const look_at_window = 1000;

void CreateWindowAndRenderBoss(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;

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
        /* surface = SDL_LoadBMP("img/cuphead.bmp"); */
        surface = SDL_LoadBMP("img/Emalf.PNG");
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
}
/* #ifdef __cplusplus */
/* extern "C" */
/* #endif */

#include <iostream>
#include <type_traits>
#include <vector>

template<typename Derived>
class Object
{
public:
  void func()
  {
    derived()->func_impl();
  }
private:
};


class DerivedObject : public Object<DerivedObject>
{
public:
    void func_impl()
    {
      //
    }
};


template<typename T>
void on_object(const T& obj)
{

}


int main(){
    /* CreateWindowAndRenderBoss(); */
    printf("hi brian");
    std::vector<int> vec;
    plus(vec);
}

