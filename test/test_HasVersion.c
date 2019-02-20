#include "test_HasVersion.h"
#include <unity.h>
#include <SDL2/SDL.h>

void SDL_VERSION_returns_compiled_against_version_2_0(void){
    /* =====[ Setup ]===== */
    SDL_version compiled;
    /* =====[ Operate ]===== */
    SDL_VERSION(&compiled);
    printf(
        "Compiled against SDL version %d.%d.%d.\n",
        compiled.major,
        compiled.minor,
        compiled.patch
        );
    /* =====[ Test ]===== */
    TEST_ASSERT_EQUAL(2, compiled.major);
    TEST_ASSERT_EQUAL(0, compiled.minor);
}
void SDL_GetVersion_returns_linked_against_version_2_0(void){
    /* =====[ Setup ]===== */
    SDL_version linked;
    /* =====[ Operate ]===== */
    SDL_GetVersion(&linked);
    printf(
        "Linked against SDL version %d.%d.%d.\n",
        linked.major,
        linked.minor,
        linked.patch
        );
    /* =====[ Test ]===== */
    TEST_ASSERT_EQUAL(2, linked.major);
    TEST_ASSERT_EQUAL(0, linked.minor);
}
