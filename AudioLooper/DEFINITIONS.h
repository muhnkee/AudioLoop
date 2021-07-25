#pragma once
//#define DEBUG 1

// Window dimensions
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

// Component limitations
#define MAX_NUMBER_OF_TRACKS 4

// Fonts
#define ARIAL_FONT "./Assets/Fonts/arial.ttf"

// Icons
#define LOOP_ICON "./Assets/Icons/loop-96.png"
#define PLAY_PAUSE_ICON "./Assets/Icons/resume-60.png"

// Sprites
#define SLIDE_BAR "./Assets/Icons/Slider_bar.png"
#define SLIDE "./Assets/Icons/Slide.png"
#define SLIDE_BAR_LANDSCAPE "./Assets/Icons/Slider_bar_landscape.png"
#define SLIDE_LANDSCAPE "./Assets/Icons/Slide_landscape.png"

// Audio Directory
#define AUDIO_DIR "./Assets/Audio/"

enum class APPLICATION_FUNCTIONS { NO_CHANGE, PLAY, RECORD, PAUSE, STOP};

// Math
#define PI 3.14159265