#include <SFML/Graphics.hpp>
#include "Controller.hpp"
#include "DEFINITIONS.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

    Controller main_controller = Controller();


    while (window.isOpen())
    {
        // TODO: REFACTOR THIS INTO CLASS
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyReleased:
                main_controller.selectTrackItem(event);
                break;
            default:
                break;
            }
            
        }

        window.clear();

        main_controller.drawTrackItems(window);

        window.display();
    }

    

    return 0;
}