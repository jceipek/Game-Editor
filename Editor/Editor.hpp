//
//  Editor.hpp
//  Editor
//
//  Created by Julian Ceipek on 2/8/12.
//  Copyright (c) 2012 Franklin W. Olin College of Engineering. All rights reserved.
//

#ifndef Editor_Editor_hpp
#define Editor_Editor_hpp

#include <SFML/Graphics.hpp>

class Editor {

private:
    sf::RenderWindow* window;
    
    void drawMenu();
    sf::RectangleShape menuBase;
    
public:
    Editor (sf::RenderWindow*);
    ~Editor();
    
    void update(sf::Time elapsedTime);
};


#endif
