//
//  Editor.cpp
//  Editor
//
//  Created by Julian Ceipek on 2/8/12.
//  Copyright (c) 2012 Franklin W. Olin College of Engineering. All rights reserved.
//

#include <iostream>

#include "Editor.hpp"

Editor::Editor (sf::RenderWindow* window) {
    this->window = window;

    this->menuBase = sf::RectangleShape(sf::Vector2f(200.0f,600.0f));
    menuBase.SetFillColor(sf::Color(0,0,0,200)); // Translucent black
}

Editor::~Editor() {
    std::cout << "Deleting editor\n";
}

void Editor::update(sf::Time elapsedTime) {

    //Draw:
    this->window->Draw(this->menuBase);
}
