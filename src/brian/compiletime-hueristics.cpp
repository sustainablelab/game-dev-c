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
#ifdef __cplusplus
extern "C"
#endif

template<typename El, size_t N>
class Array
{
public:
   El& operator[](size_t index) { return data_[index]; }
   const El& operator[](size_t index) const { return data_[index];}
   El* begin() noexcept { return data_; }
   El* end() { return data_ + N;}
private:
    El data_[N];
};



for (const auto& el : range_wrapper<1, 10>(v))
{

}



int main(){
    /* CreateWindowAndRenderBoss(); */
    printf("hi brian");

}

