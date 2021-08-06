#ifndef DEBUG
#define DEBUG false
#endif

#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <SFML/Audio.hpp>
#include "RecorderC.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::to_string;

// Required
int DEVICE = -1;

// Recorder calls three functions on creation
RecorderC::RecorderC(sf::SoundBufferRecorder* recorder, sf::SoundBuffer* buffer)
{
    setRecorderBuffer(recorder);
    setBuffer(buffer);
    // Ensure recording device exists and is available
    checkAvailabilty();
    // Select windows default audio device
    selectDevice();
    // Create a "Samples" directory to store samples if it doesn't exist
    createSamplesDir();
}

// Simple check
void RecorderC::checkAvailabilty()
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

// Select default audio device if device has not yet been set
void RecorderC::selectDevice()
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

        if (!recorder->setDevice(availableDevices[DEVICE]) && DEBUG)
        {
            cout << "ERROR: Device setting failed" << endl;
        }
    }
}

// Record Audio into recorder buffer
void RecorderC::Record()
{
    m_isRecording = true;
    recorder->start();
}

// STOP will automatically save each recorded audio clip after stopping, storing the file's PATH in private class variable 'audioFilePath'
void RecorderC::Stop()
{
    recorder->stop();
    m_isRecording = false;

    *buffer = recorder->getBuffer();

    sound.setBuffer(*buffer);
    
    setAudioFilePath();

    buffer->saveToFile(audioFilePath);
}

void RecorderC::setAudioFilePath()
{
    time_t now = time(0);
    struct tm buf;
    localtime_s(&buf, &now);

    // filename is timestamped for unique ID
    string timestamp;
    timestamp = timestamp + to_string(1900 + buf.tm_year) + "-" + to_string(1 + buf.tm_mon) + \
        "-" + to_string(buf.tm_mday) + " " + to_string(buf.tm_hour) + to_string(buf.tm_min) + \
        to_string(buf.tm_sec);

    if (DEBUG)
    {
        cout << timestamp << endl;
    }

    // File is saved into Samples/ directory
    audioFilePath = "Samples/" + timestamp + ".wav";
}

// This is just for testing, making sure audio is actually where it needs to be
void RecorderC::Play()
{
    sound.play();
}

// Use this function to get the PATH of the most recently recorded audio clip
std::string RecorderC::getAudioFilePath()
{
    return audioFilePath;
}

// Helper function for checking if Samples/ directory exists
bool RecorderC::dirExists(const std::string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with the path

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory

    return false;    // this is not a directory
}

// Creates Samples directory
void RecorderC::createSamplesDir()
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

bool RecorderC::isRecording()
{
    return m_isRecording;
}