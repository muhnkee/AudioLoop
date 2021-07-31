#include <string>
#include <iostream>
#include <reverse.h>
#include <SFML/Audio.hpp>

using std::string;
using std::cout;
using std::endl;

string reverse(string path)
{
	sf::SoundBuffer buffer;

	buffer.loadFromFile(path);

    unsigned int SampleRate = buffer.getSampleRate();
    unsigned int Channels = buffer.getChannelCount();
    sf::Time Duration = buffer.getDuration();
    std::size_t Count = buffer.getSampleCount();

    cout << "SampleRate: " << SampleRate << "\nChannels: " << Channels << "\nDuration: " << Duration.asSeconds() << "\nCount: " << Count << endl;

    const sf::Int16* Samples = buffer.getSamples();
    std::vector<sf::Int16> reversedSamples;

    for (int i = Count - 1; i >= 0; i--)
    {
        reversedSamples.push_back(Samples[i]);
    }

    buffer.loadFromSamples(&reversedSamples[0], reversedSamples.size(), Channels, SampleRate);

    path.insert((path.length() - 4), " rvrsd");

    cout << "path: " << path << endl;

    buffer.saveToFile(path);

    return path;

}