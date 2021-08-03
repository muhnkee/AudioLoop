#include <string>
#include <iostream>

#include "Reverse.h"

#include <SFML/Audio.hpp>

using std::string;
using std::cout;
using std::endl;

string reverse(string path)
{
    // need this
	sf::SoundBuffer buffer;

    // need that
	buffer.loadFromFile(path);

    // need all of these
    unsigned int SampleRate = buffer.getSampleRate();
    unsigned int Channels = buffer.getChannelCount();
    sf::Time Duration = buffer.getDuration();
    std::size_t Count = buffer.getSampleCount();

    // make sure nothing suspicious is going on
    cout << "SampleRate: " << SampleRate << "\nChannels: " << Channels << "\nDuration: " << Duration.asSeconds() << "\nCount: " << Count << endl;

    // grab all the audio samples from memory and save them into a const array
    const sf::Int16* Samples = buffer.getSamples();

    // create a vector that we can actually write to
    std::vector<sf::Int16> reversedSamples;

    // write to this new vec in reverse order
    for (int i = Count - 1; i >= 0; i--)
    {
        reversedSamples.push_back(Samples[i]);
    }

    // reload reversed samples from our new array
    buffer.loadFromSamples(&reversedSamples[0], reversedSamples.size(), Channels, SampleRate);

    // make a new filename (adding an 'rvrsd' stamp for "reversed")
    path.insert((path.length() - 4), " rvrsd");

    // ensure we have not totally just messed that up
    cout << "path: " << path << endl;

    // write it
    buffer.saveToFile(path);

    // aaaannd give it back
    return path;

}