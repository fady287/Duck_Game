#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace sf;

typedef long long ll;


struct arm {
    Texture skin;
    Sprite arm;
};

struct weapons {
    string type;
    Texture skin;
    Sprite weapon;
    float velocityX = 0.0, velocityY = 0.0;
    Clock myclock;
    float velocity;
    ll bullets;
    bool empty;
    float range;
    float posx, posy;
    float fix_X, fix_Y;
    float fix_hold_x, fix_hold_y;
    ll bull_type;
    float space = 0.f;
    float rev;
    float angle;
    bool hit = 0;
    ll fact = 1;
};

struct bullets {
    Texture skin;
    Sprite bullet;
    ll duck;
    bool right;
    float velocity;
    float startX;
    float range;
    float scalex, scaley;
};

struct ducks {
    Texture skin;
    Clock myclock;
    Sprite myduck;
    int frame = 0;
    int score = 0;
    bool facingRight = true;
    bool isJumping = false;
    bool haveWeapon = false;
    bool holding = false;
    bool firing = false;
    bool dead = false;
    bool ready = false;
    weapons myweap;
    arm myarm;
    Keyboard::Key up;
    Keyboard::Key right;
    Keyboard::Key left;
    Keyboard::Key hold;
    Keyboard::Key fire;
    float velocityY = 0.f;
    float space;
    float fact;
};


