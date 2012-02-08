#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"

#include <sstream>

int main (int argc, const char * argv[])
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Random Editor");

    window.SetFramerateLimit(1000);
    //window.EnableVerticalSync(true);
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.LoadFromFile(ResourcePath() + "cute_image.jpg"))
    	return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.LoadFromFile(ResourcePath() + "sansation.ttf"))
    	return EXIT_FAILURE;
    sf::Text text("Object", font, 20);
    text.SetColor(sf::Color::White);
    text.SetPosition(10.0f, 0.0f);

    sf::Text fpsMonitor("0", font, 20);
    fpsMonitor.SetColor(sf::Color::Black);
    fpsMonitor.SetPosition(770.0f, 575.0f);
    
    sf::RectangleShape rect(sf::Vector2f(200.0f,600.0f));
    rect.SetFillColor(sf::Color(0,0,0,200));
    
    sf::CircleShape circ(10.0f);
    circ.SetFillColor(sf::Color(0,200,0));
    circ.SetPosition(100.0f, 100.0f);
    
    float circx = 100.0f;
    
    sf::Clock Clock;
    
    // Load a music to play
    sf::Music music;
    if (!music.OpenFromFile(ResourcePath() + "nice_music.ogg"))
    	return EXIT_FAILURE;

    // Play the music
    music.Play();
    
    bool movingRight = false; //This variable accounts for the fact that events are not triggered regularly
        
    bool showEditor = false;
    
    // Start the game loop
    while (window.IsOpen())
    {
        float ElapsedTime = (float)(Clock.GetElapsedTime().AsMilliseconds());
        Clock.Restart();
        
    	// Process events
    	sf::Event event;        
    	while (window.PollEvent(event))
    	{
    		// Close window : exit
    		if (event.Type == sf::Event::Closed)
    			window.Close();
            
    		// Escape pressed : exit
    		if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Escape)
    			window.Close();
            
            if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Keyboard::Tab) {
                showEditor = !showEditor;
            }
            
            if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Right) {
                movingRight = true;
            }
            
            if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Keyboard::Right) {
                movingRight = false;
            }
    	}

        if(movingRight) {
            circx += ElapsedTime/10.0f;
        }
        
        circ.SetPosition(circx, 100.0f);
        
    	// Clear screen
    	window.Clear();
    	
    	// Draw the background
    	window.Draw(sprite);
        
        window.Draw(circ);

        if (showEditor) {
            window.Draw(rect);
            
            // Draw the string
            window.Draw(text);
        }


        std::stringstream fpsText;
        fpsText << (1.f / (ElapsedTime));
        fpsMonitor.SetString(fpsText.str());
        window.Draw(fpsMonitor);
        
    	// Update the window
    	window.Display();
    }

	return EXIT_SUCCESS;
}
