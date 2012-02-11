#include <Python/Python.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include "Editor.hpp"

#include <iostream>
#include <sstream>



// Comment out to disable these features:
#define DYNAMIC_TESTING
#define DEBUG_MONITOR

int main (int argc, const char * argv[])
{
    Py_Initialize();
    PyRun_SimpleString("print('Now we have Python action!')\n");
    Py_Finalize();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Random Editor");

    //window.SetFramerateLimit(1000);
    //window.EnableVerticalSync(true);

    enum GameMode {
        PLAYING = 0,
        EDITING,
        PAUSED
    } gameMode;

    gameMode = PLAYING;

    sf::Font font;
    if (!font.LoadFromFile(ResourcePath() + "sansation.ttf"))
    	return EXIT_FAILURE;


#ifdef DYNAMIC_TESTING
    Editor editor(&window);
#endif

#ifdef DEBUG_MONITOR
    sf::Text fpsMonitor("0", font, 20);
    fpsMonitor.SetColor(sf::Color::Black);
    fpsMonitor.SetPosition(760.0f, 575.0f);
#endif


    // Load a sprite to display
    sf::Texture texture;
    if (!texture.LoadFromFile(ResourcePath() + "cute_image.jpg"))
    	return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Text text("Object", font, 20);
    text.SetColor(sf::Color::White);
    text.SetPosition(10.0f, 0.0f);


    sf::CircleShape circ(10.0f);
    circ.SetFillColor(sf::Color(0,200,0));
    circ.SetPosition(100.0f, 100.0f);

    sf::Clock Clock; //Used to compute time since last update, since SFML 2 removed GetFrametime

    // Load a music to play
    sf::Music music;
    if (!music.OpenFromFile(ResourcePath() + "nice_music.ogg"))
    	return EXIT_FAILURE;

    // Play the music
    music.Play();

    bool movingRight = false; //This variable accounts for the fact that events are not triggered regularly

    // Start the game loop
    while (window.IsOpen())
    {
        sf::Time ElapsedTime = Clock.GetElapsedTime();
        Clock.Restart();

    	// Process events
    	sf::Event event;
    	while (window.PollEvent(event))
    	{
    		// Close window : exit
    		if (event.Type == sf::Event::Closed)
    			window.Close();

    		// Escape pressed : exit
    		if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Escape) {
    		    std::cout << "Escape Pressed!\n";
    			window.Close();
    		}

            //Switch between editor and paused/playing if tab key pressed
            if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Keyboard::Tab) {
                switch (gameMode) {
                    case PLAYING:
#ifdef DYNAMIC_TESTING
                        gameMode = EDITING;
#else
                        gameMode = PAUSED;
#endif
                        break;
                    case EDITING:
                        gameMode = PAUSED;
                        break;
                    case PAUSED:
                        gameMode = PLAYING;
                        break;
                    default:
                        break;
                }
            }

            switch (gameMode) {
                case PLAYING:
                    if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Right) {
                        movingRight = true;
                    }

                    if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Keyboard::Right) {
                        movingRight = false;
                    }
                    break;
                case EDITING:
                    break;
                case PAUSED:
                    break;
                default:
                    break;
            }
    	}

    	// Clear screen
    	window.Clear();

    	// Draw the background
    	window.Draw(sprite);

        window.Draw(circ); // Test "Entity"

        switch (gameMode) {
            case PLAYING:
                if(movingRight) {
                    circ.Move(ElapsedTime.AsMicroseconds()/10000.0f, 0.0f);
                }
                break;

            case EDITING:
#ifdef DYNAMIC_TESTING
                editor.update(ElapsedTime);
                window.Draw(text);
#endif
                break;

            case PAUSED:

                break;
            default:
                break;
        }

#ifdef DEBUG_MONITOR
        std::stringstream fpsText;
        fpsText << (1.f / (ElapsedTime.AsMicroseconds()/1000000.0f));
        fpsMonitor.SetString(fpsText.str());
        window.Draw(fpsMonitor);
#endif

    	// Update the window
    	window.Display();
    }

	return EXIT_SUCCESS;
}
