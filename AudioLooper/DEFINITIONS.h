#pragma once
//#define DEBUG 1

// Window dimensions
#define SCREEN_WIDTH 1920 
#define SCREEN_HEIGHT 1080

// Component limitations
#define MAX_NUMBER_OF_TRACKS 4

// Fonts
#define ARIAL_FONT "./Assets/Fonts/arial.ttf"

// Icons
#define LOOP_ICON "./Assets/Icons/loop-48.png"
#define PLAY_PAUSE_ICON "./Assets/Icons/resume-60.png"
#define RECORD_ICON "./Assets/Icons/record-50.png"
#define REVERSE_ICON "./Assets/Icons/reverse-60.png"
#define DISABLED_REVERSE_ICON "./Assets/Icons/disabled_reverse-60.png"
#define RECORD_ICON "./Assets/Icons/record-50.png"
#define STOP_ICON "./Assets/Icons/stop-50.png"

// Sprites
#define SLIDE_BAR "./Assets/Icons/Slider_bar.png"
#define SLIDE "./Assets/Icons/Slide.png"
#define SLIDE_BAR_LANDSCAPE "./Assets/Icons/Slider_bar_landscape.png"
#define SLIDE_LANDSCAPE "./Assets/Icons/Slide_landscape.png"

#define MUSIC_SEEK_BAR "./Assets/Icons/music_seek_bar.png"
#define MUSIC_SEEK_SLIDE "./Assets/Icons/music_seek_slide.png"

#define BACKGROUND "./Assets/Icons/background.png"

// Audio Directory
#define AUDIO_DIR "./Assets/Audio/"

// Math
#define PI 3.14159265
enum class APPLICATION_FUNCTIONS { NO_CHANGE, SET_TRACK, SET_PITCH, SET_VOLUME, SET_PAN, LOOP, PLAY, RECORD_TO_FILE, NEXT, PREVIOUS, PAUSE, STOP};

