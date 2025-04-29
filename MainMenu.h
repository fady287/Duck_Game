#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Menu {
    // Variables
    float width, height;
    Texture backgroundTexture;
    Sprite background;
    Music menuMusic;
    Text menuText[5];
    int selected;
    Font font;
};

struct splashScreen {
    float transparency = 0;
    Sprite logo;
    Text splashText;
};

// Functions 
void drawMenu(RenderWindow& window);
void moveUp();
void moveDown();
void fadeIn();
void fadeOut();
