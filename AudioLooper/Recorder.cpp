#ifndef DEBUG
#define DEBUG false
#endif
//#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <SFML/Audio.hpp>
#include "recorder.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::to_string;

int DEVICE = -1;

Recorder::Recorder()
{
    // Ensure recording device exists and is available
    checkAvailabilty();
    selectDevice();
    createSamplesDir();
}


void Recorder::checkAvailabilty()
{

    if (!sf::SoundBufferRecorder::isAvailable())
    {
        // error: audio capture is not available on this system
        deviceFlag = false;
    }
    else
    {
        deviceFlag = true;
    }

    if (DEBUG) {
        if (deviceFlag == false)
        {
            cout << "ERROR: Audio capture device is NOT available on this machine" << endl;
        }
        else
        {
            cout << "Audio capture device(s) available" << endl;
        }
    }
}

void Recorder::selectDevice()
{
    if (DEVICE == -1) {
        // Get available devices
        std::vector<std::string> availableDevices = sf::SoundRecorder::getAvailableDevices();

        // List available devices in console, current default device should be first in vector
        if (DEBUG)
        {
            for (int i = 0; i < availableDevices.size(); i++)
            {
                cout << " --> Available Device " << i << ": " << availableDevices[i] << endl;
            }
        }

        // Give the User a choice of audio devices if > 1

        if (availableDevices.size() > 1)
        {
            // Defaults to OS main/current audio device
            int userChoice = 1; 
            DEVICE = userChoice;
        }

        else
        {
            DEVICE = 0;
        }

        if (DEBUG)
        {
            cout << " --> userChoice: " << availableDevices[DEVICE] << endl;
        }

        if (!recorder.setDevice(availableDevices[DEVICE]) && DEBUG)
        {
            cout << "ERROR: Device setting failed" << endl;
        }
    }
}

void Recorder::Record()
{
    recorder.start();
}

void Recorder::Stop()
{
    recorder.stop();

    buffer = recorder.getBuffer();

    sound.setBuffer(buffer);

    time_t now = time(0);
    struct tm buf;
    localtime_s(&buf, &now);

    string timestamp;
    timestamp = timestamp + to_string(1900 + buf.tm_year) + "-" + to_string(1 + buf.tm_mon) + \
        "-" + to_string(buf.tm_mday) + " " + to_string(buf.tm_hour) + to_string(buf.tm_min) + \
        to_string(buf.tm_sec);

    if (DEBUG)
    {
        cout << timestamp << endl;
    }

    audioFilePath = "Samples/" + timestamp + ".wav";

    buffer.saveToFile(audioFilePath);
}

void Recorder::Play()
{
    sound.play();
}

std::string Recorder::getAudioFilePath()
{
    return audioFilePath;
}

bool Recorder::dirExists(const std::string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

void Recorder::createSamplesDir()
{
    if (dirExists("Samples") && DEBUG) {
        cout << "\"Samples\" Directory Exists" << endl;
    }
    else {
        if (DEBUG) {
            cout << "\"Samples\"Directory does not exist, creating.." << endl;
        }
        LPCWSTR sampDir = L"Samples";
        CreateDirectory(sampDir, NULL);
    }
}