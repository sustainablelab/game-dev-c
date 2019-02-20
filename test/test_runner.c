#include <unity.h>
#include "test_HasVersion.h"
#include "test_HasWindow.h"
void (*setUp)(void); void (*tearDown)(void);
void NothingToSetup(void){}
void NothingToTearDown(void){}

void Report_SDL_Version(void){
    printf("# Report SDL Version\n");
    setUp = NothingToSetup; tearDown = NothingToTearDown;
    RUN_TEST(SDL_VERSION_returns_compiled_against_version_2_0);
    RUN_TEST(SDL_GetVersion_returns_linked_against_version_2_0);
}
bool Nope = false;
bool Yep = true;
void Try_the_basics_with_SDL_Init(bool run_tests){ if (run_tests){
    printf("# Try the basics with SDL Init\n");
    setUp = NothingToSetup; tearDown = NothingToTearDown;
    RUN_TEST(SDL_Init_returns_0_on_success);
    RUN_TEST(SDL_Init_initializes_video_subsystem);
    RUN_TEST(SDL_Init_initializes_audio_subsystem);
}}
void Try_window_management(bool run_tests){ if (run_tests){
    printf("# Try window management\n");
    setUp = Setup_SDL_Basics; tearDown = Shutdown_SDL;
    RUN_TEST(SDL_CreateWindow_returns_NULL_if_it_cannot_make_a_window);
    RUN_TEST(SDL_CreateWindowAndRenderer_writes_NULL_to_window_and_renderer_if_it_cannot_make_them);
}}
int main(){
    printf("%% `game-dev` Test Results\n\n");
    UNITY_BEGIN();
    Report_SDL_Version();
    /* Cygwin build uses `XWin` as the video and audio device. */
    /* Abort testing if `XWin` is not running. Notify me in the test results. */
    if (!VideoDeviceIsAvailable()) return UNITY_END();
    Try_the_basics_with_SDL_Init(Nope);
    Try_window_management(Yep);
    /* TEST_ASSERT_EQUAL_HEX8( */
    /*     (0 | 1<<3 ) & (0xFF), */
    /*     1<<3 */
    /*     ); */
    return UNITY_END();
}
