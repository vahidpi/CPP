#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
    /*
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }
    */

    RenderWindow window(VideoMode(320,480), "TheGame");

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type== Event::Closed)
				window.close();
		}

		window.clear(Color::White);
		window.display();
	}
	//return 0;


    return EXIT_SUCCESS;
}
