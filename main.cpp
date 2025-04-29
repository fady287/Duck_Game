#include "MainMenu.h"
#include "Logic.h"
#include "GameTile.h"
#include "Game.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace sf;
typedef long long ll;

Menu mainMenu, settingsMenu, gameMenu, transition;
RenderWindow window(VideoMode(1280, 720), "Duck Game");
Texture grave;
Sprite Grave;
splashScreen intro;

Clock trans;
bool fullscreen = false;

int menuState = 1000; // 1000 = main menu, 0 = game/levels, 1 = settings, 2 = game menu (& level selector), 3 = transition between games 
bullets bull[3];
ducks duck1, duck2;
float fact;
weapons sword, pistol, sniper, pewpew;
vector<weapons> weaps;
vector<bullets> bulls;
float gravity = 0.5f;
float jumpSpeed = -14.f;
float velocityX = 20.f;
bool GameEnd = 0;
ll mapnum = 4, duck1Score, duck2Score;
float DUCK_SCALE;
float GUN_SCALE;
float scalex, scaley;
const float Width = 1280, Height = 720;


//Fady
void init() {
    //init the first duck
    ducks duck;
    duck1 = duck;
    duck2 = duck;
    weaps.clear();
    bulls.clear();
    duck1.skin.loadFromFile("img/duck1.png");
    duck1.myduck.setTexture(duck1.skin);
    duck1.myduck.setTextureRect(IntRect(0, 0, 32, 32));
    duck1.myduck.setScale(DUCK_SCALE, DUCK_SCALE);
    duck1.myduck.setOrigin(0.f, duck1.myduck.getLocalBounds().height);
    duck1.myduck.setPosition(0.f, 680.f);
    duck1.up = Keyboard::W;
    duck1.right = Keyboard::D;
    duck1.left = Keyboard::A;
    duck1.hold = Keyboard::C;
    duck1.fire = Keyboard::V;
    //init the first duck's arm
    duck1.myarm.skin.loadFromFile("img/duck1arms.png");
    duck1.myarm.arm.setTexture(duck1.myarm.skin);
    duck1.myarm.arm.setTextureRect(IntRect(0, 0, 16, 16));
    duck1.myarm.arm.setScale(DUCK_SCALE, DUCK_SCALE);
    duck1.myarm.arm.setPosition(
        duck1.myduck.getPosition().x + duck1.myduck.getGlobalBounds().width / 6,
        duck1.myduck.getPosition().y - duck1.myduck.getGlobalBounds().height / 2 - fact
    );


    //init the second duck
    duck2.skin.loadFromFile("img/duck2.png");
    duck2.myduck.setTexture(duck2.skin);
    duck2.myduck.setTextureRect(IntRect(0, 0, 32, 32));
    duck2.myduck.setScale(-DUCK_SCALE, DUCK_SCALE);
    duck2.myduck.setOrigin(duck2.myduck.getLocalBounds().width, duck2.myduck.getLocalBounds().height);
    duck2.myduck.setPosition(1200.f, 680.f);
    duck2.up = Keyboard::Up;
    duck2.right = Keyboard::Right;
    duck2.left = Keyboard::Left;
    duck2.hold = Keyboard::K;
    duck2.fire = Keyboard::L;
    duck2.facingRight = false;
    //init the second duck's arm
    duck2.myarm.skin.loadFromFile("img/duck2arms.png");
    duck2.myarm.arm.setTexture(duck2.myarm.skin);
    duck2.myarm.arm.setTextureRect(IntRect(0, 0, 16, 16));
    duck2.myarm.arm.setScale(-DUCK_SCALE, DUCK_SCALE);
    duck2.myarm.arm.setOrigin(22.f, 0.f);
    duck2.myarm.arm.setPosition(
        duck2.myduck.getPosition().x + duck2.myduck.getGlobalBounds().width / 6,
        duck2.myduck.getPosition().y - duck2.myduck.getGlobalBounds().height / 2 - fact
    );


    //init pistol
    pistol.skin.loadFromFile("img/pistol.png");
    pistol.weapon.setTexture(pistol.skin);
    pistol.posx = 600;
    pistol.posy = 660;
    pistol.weapon.setTextureRect(IntRect(0, 0, 16, 10));
    pistol.weapon.setScale(GUN_SCALE, GUN_SCALE);
    pistol.empty = false;
    pistol.bullets = 10;
    pistol.velocity = 10;
    pistol.range = 500.f;
    pistol.bull_type = 1;
    pistol.weapon.setOrigin(0, pistol.weapon.getLocalBounds().height);
    pistol.weapon.setPosition(600.f, 680);
    pistol.type = "pistol";


    //init sniper
    sniper.skin.loadFromFile("img/sniper.png");
    sniper.weapon.setTexture(sniper.skin);
    sniper.posx = 200;
    sniper.posy = 660;
    sniper.weapon.setTextureRect(IntRect(0, 0, 33, 9));
    sniper.weapon.setScale(GUN_SCALE, GUN_SCALE);
    sniper.empty = false;
    sniper.bullets = 4;
    sniper.velocity = 0;
    sniper.range = 100000.f;
    sniper.bull_type = 1;
    sniper.weapon.setOrigin(0, sniper.weapon.getLocalBounds().height);
    sniper.weapon.setPosition(200.f, 680);
    sniper.type = "sniper";

    //init pewpew
    pewpew.skin.loadFromFile("img/pewpewLaser.png");
    pewpew.weapon.setTexture(pewpew.skin);
    pewpew.posx = 300;
    pewpew.posy = 300;
    pewpew.weapon.setTextureRect(IntRect(0, 0, 26, 10));
    pewpew.weapon.setScale(GUN_SCALE, GUN_SCALE);
    pewpew.empty = false;
    pewpew.bullets = 20;
    pewpew.velocity = 0;
    pewpew.range = 100000.f;
    pewpew.bull_type = 2;
    pewpew.weapon.setOrigin(0, pewpew.weapon.getLocalBounds().height);
    pewpew.weapon.setPosition(300.f, 680);
    pewpew.type = "pewpew";

    //init sword
    sword.skin.loadFromFile("img/sword.png");
    sword.weapon.setTexture(sword.skin);
    sword.weapon.setTextureRect(IntRect(0, 0, 8, 23));
    sword.weapon.setScale(GUN_SCALE, GUN_SCALE);
    sword.empty = false;
    sword.type = "sword";
    sword.angle = 90.f;
    sword.weapon.setOrigin(sword.weapon.getLocalBounds().width, sword.weapon.getLocalBounds().height);
    sword.weapon.setPosition(400.f, 680);
    sword.weapon.setRotation(sword.angle);

    //init bullet
    bull[1].skin.loadFromFile("img/pistol_bullet.png");
    bull[1].bullet.setTexture(bull[1].skin);

    bull[2].skin.loadFromFile("img/laser_bullet1.png");
    bull[2].bullet.setTexture(bull[2].skin);


    //init Grave
    grave.loadFromFile("img/rip.png");
    Grave.setTexture(grave);
}
void Fire(ducks& duck, ll shooter) {
    ll idx = duck.myweap.bull_type;
    if (duck.myweap.type == "sword") {
        duck.myweap.hit = 1;
        duck.myweap.myclock.restart();
        return;
    }
    if (duck.myweap.bullets > 0) {
        duck.myweap.bullets--;
        bull[idx].right = duck.facingRight;
        if (duck.facingRight) {
            bull[idx].bullet.setScale(bull[idx].scalex, bull[idx].scaley);
            bull[idx].bullet.setOrigin(0.f, 0.f);
        }
        else {
            bull[idx].bullet.setScale(-1 * bull[idx].scalex, bull[idx].scaley);
            bull[idx].bullet.setOrigin(bull[idx].bullet.getLocalBounds().width, 0.f);
        }
        if (duck.facingRight) bull[idx].bullet.setPosition(duck.myweap.weapon.getPosition().x + duck.myweap.weapon.getGlobalBounds().width, duck.myweap.weapon.getPosition().y + duck.myweap.fix_Y);
        else bull[idx].bullet.setPosition(duck.myweap.weapon.getPosition().x - duck.myweap.weapon.getGlobalBounds().width + duck.myweap.fix_X, duck.myweap.weapon.getPosition().y + duck.myweap.fix_Y);
        bull[idx].duck = shooter;
        bull[idx].velocity = duck.myweap.velocity;
        bull[idx].startX = bull[idx].bullet.getPosition().x;
        bull[idx].range = duck.myweap.range;
        bulls.push_back(bull[idx]);
    }
}
void update_weapons() {
    for (auto& weap : weaps) {
        weap.weapon.move(weap.velocityX, weap.velocityY);
        weap.velocityY += gravity;
        if (weap.weapon.getPosition().y >= 680.f) {
            weap.weapon.setPosition(weap.weapon.getPosition().x, 680.f);
            weap.velocityX = 0.f;
            weap.velocityY = 0.f;
        }
    }
}
void update_sword(ducks& duck, ll shooter) {
    if (duck.myweap.type == "sword" && duck.myweap.hit) {
        if (duck.myweap.weapon.getGlobalBounds().intersects(duck2.myduck.getGlobalBounds()) && shooter == 1) {
            Grave.setPosition(duck2.myduck.getPosition().x, 640.f);
            GameEnd = 1;
            duck2.dead = true;
        }
        if (duck.myweap.weapon.getGlobalBounds().intersects(duck1.myduck.getGlobalBounds()) && shooter == 2) {
            Grave.setPosition(duck1.myduck.getPosition().x, 640.f);
            GameEnd = 1;
            duck1.dead = true;
        }
        if (duck.facingRight) {
            if (duck.myweap.myclock.getElapsedTime().asMilliseconds() >= 5) {
                duck.myweap.angle = duck.myweap.angle + 15 * duck.myweap.fact;
                duck.myweap.weapon.setRotation(duck.myweap.angle);
                if (duck.myweap.weapon.getRotation() >= 90) {
                    duck.myweap.fact = -1;
                }
                if (duck.myweap.weapon.getRotation() <= 0) {
                    duck.myweap.fact = 1;
                    duck.myweap.hit = 0;
                }
                duck.myweap.myclock.restart();
            }
        }
        else {
            if (duck.myweap.myclock.getElapsedTime().asMilliseconds() >= 5) {
                duck.myweap.angle = duck.myweap.angle - 15 * duck.myweap.fact;
                duck.myweap.weapon.setRotation(duck.myweap.angle);
                if (duck.myweap.angle <= -90) {
                    duck.myweap.fact = -1;
                }
                if (duck.myweap.angle >= 0) {
                    duck.myweap.fact = 1;
                    duck.myweap.hit = 0;
                }
                duck.myweap.myclock.restart();
            }
        }
    }
}
void update_duck(ducks& duck) {
    bool moving = false;
    float duckWidth = duck.myduck.getGlobalBounds().width / 3;

    if (Keyboard::isKeyPressed(duck.right)) {
        moving = true;

        if (!duck.facingRight) {
            duck.facingRight = true;
            duck.myduck.setScale(DUCK_SCALE, DUCK_SCALE);
            duck.myduck.setOrigin(0.f, duck.myduck.getLocalBounds().height);
            duck.myarm.arm.setScale(DUCK_SCALE, DUCK_SCALE);
            duck.myarm.arm.setOrigin(0.f, 0.f);
            if (duck.haveWeapon) {
                duck.myweap.weapon.setScale(GUN_SCALE, GUN_SCALE);
                if (duck.myweap.type == "sword")
                    duck.myweap.weapon.setOrigin(duck.myweap.weapon.getLocalBounds().width, duck.myweap.weapon.getLocalBounds().height);
                else
                    duck.myweap.weapon.setOrigin(0.f, duck.myweap.weapon.getLocalBounds().height);
            }
        }

        if (duck.myduck.getPosition().x + velocityX <= 1280 - duckWidth * 2) {
            duck.myduck.move(velocityX, 0.f);
            duck.myarm.arm.setPosition(
                duck.myduck.getPosition().x + duck.myduck.getGlobalBounds().width / 6,
                duck.myduck.getPosition().y - duck.myduck.getGlobalBounds().height / 2 - fact
            );
            duck.myweap.weapon.setPosition(
                duck.myduck.getPosition().x + duck.myweap.fix_hold_x,
                duck.myduck.getPosition().y + duck.myweap.fix_hold_y
            );
        }

    }
    if (Keyboard::isKeyPressed(duck.left)) {
        moving = true;
        if (duck.facingRight) {
            duck.facingRight = false;
            duck.myduck.setScale(-DUCK_SCALE, DUCK_SCALE);
            duck.myduck.setOrigin(duck.myduck.getLocalBounds().width, duck.myduck.getLocalBounds().height);
            duck.myarm.arm.setScale(-DUCK_SCALE, DUCK_SCALE);
            duck.myarm.arm.setOrigin(22.f, 0.f);
            if (duck.haveWeapon) {
                duck.myweap.weapon.setScale(-GUN_SCALE, GUN_SCALE);
                duck.myweap.weapon.setOrigin(duck.myweap.rev, duck.myweap.weapon.getLocalBounds().height);
            }
        }
        if (duck.myduck.getPosition().x - velocityX >= -duckWidth) {
            duck.myduck.move(-velocityX, 0.f);
            duck.myarm.arm.setPosition(
                duck.myduck.getPosition().x + duck.myduck.getGlobalBounds().width / 6,
                duck.myduck.getPosition().y - duck.myduck.getGlobalBounds().height / 2 - fact
            );
            duck.myweap.weapon.setPosition(
                duck.myduck.getPosition().x + duck.myweap.fix_hold_x,
                duck.myduck.getPosition().y + duck.myweap.fix_hold_y
            );
        }
    }

    if (!duck.isJumping && Keyboard::isKeyPressed(duck.up)) {
        duck.isJumping = true;
        duck.velocityY = jumpSpeed;
    }

    if (duck.isJumping) {
        duck.velocityY += gravity;
        duck.myduck.move(0.f, duck.velocityY);
        duck.myarm.arm.setPosition(
            duck.myduck.getPosition().x + duck.myduck.getGlobalBounds().width / 6,
            duck.myduck.getPosition().y - duck.myduck.getGlobalBounds().height / 2 - fact
        );
        duck.myweap.weapon.setPosition(
            duck.myduck.getPosition().x + duck.myweap.fix_hold_x,
            duck.myduck.getPosition().y + duck.myweap.fix_hold_y
        );

        if (duck.velocityY < 0) {
            duck.myduck.setTextureRect(IntRect(0, 32, 32, 32));
        }
        else {
            duck.myduck.setTextureRect(IntRect(32, 32, 32, 32));
        }

        if (duck.myduck.getPosition().y >= 680.f) {
            duck.myduck.setPosition(duck.myduck.getPosition().x, 680.f);
            duck.isJumping = false;
            duck.velocityY = 0.f;
        }
    }
    else if (moving) {
        if (duck.myclock.getElapsedTime().asMilliseconds() > 80) {
            duck.frame = (duck.frame + 1) % 6;
            duck.myduck.setTextureRect(IntRect(duck.frame * 32, 0, 32, 32));
            duck.myclock.restart();
        }
    }
    else {
        duck.myduck.setTextureRect(IntRect(0, 0, 32, 32));
    }
}   
void drop_weapon(ducks& duck) {
    duck.haveWeapon = false;
    duck.myweap.velocityX = 7.f;
    if (!duck.facingRight) {
        duck.myweap.velocityX *= -1.f;
    }
    duck.myweap.velocityY = -7.f;
    if (duck.myweap.type == "sword") {
        duck.myweap.weapon.setOrigin(duck.myweap.weapon.getLocalBounds().width, duck.myweap.weapon.getLocalBounds().height);
        if (duck.facingRight) duck.myweap.weapon.setRotation(90);
        else duck.myweap.weapon.setRotation(-90);
    }
    weaps.push_back(duck.myweap);

    if (duck.facingRight) {
        duck.myarm.arm.setTextureRect(IntRect(0, 0, 16, 16));
        duck.myarm.arm.setScale(DUCK_SCALE, DUCK_SCALE);
        duck.myarm.arm.setOrigin(0.f, 0.f);
    }
    else {
        duck.myarm.arm.setTextureRect(IntRect(0, 0, 16, 16));
        duck.myarm.arm.setScale(-DUCK_SCALE, DUCK_SCALE);
        duck.myarm.arm.setOrigin(22.f, 0.f);
    }
}
void get_weapon(ducks& duck) {
    if (duck.haveWeapon) {
        drop_weapon(duck);
        cout << "sss";
        return;
    }
    if (weaps.size() == 0) return;
    for (ll i = weaps.size() - 1;i >= 0;--i) {
        weapons weap = weaps[i];
        if (duck.myduck.getGlobalBounds().intersects(weap.weapon.getGlobalBounds())) {
            duck.haveWeapon = true;
            duck.myarm.arm.setTextureRect(IntRect(0, 16 * 4, 16, 16));
            if (!duck.facingRight) {
                FloatRect bounds = weap.weapon.getLocalBounds();
                if (weap.type == "sword")
                    weap.weapon.setOrigin(0.f, bounds.height);
                else
                    weap.weapon.setOrigin(weap.rev, bounds.height);
                weap.weapon.setScale(-GUN_SCALE, GUN_SCALE);
            }
            if (duck.facingRight) {
                FloatRect bounds = weap.weapon.getLocalBounds();
                if (weap.type == "sword")
                    weap.weapon.setOrigin(bounds.width, bounds.height);
                else
                    weap.weapon.setOrigin(0, bounds.height);
                weap.weapon.setScale(GUN_SCALE, GUN_SCALE);
            }

            weap.weapon.setPosition(
                duck.myduck.getPosition().x + weap.fix_hold_x,
                duck.myduck.getPosition().y + weap.fix_hold_y
            );
            if (weap.type == "sword") {
                weap.weapon.setRotation(0);
                weap.angle = 0;
            }
            duck.myweap = weap;
            weaps.erase(weaps.begin() + i);
            break;
        }
    }
}
void update_bullets() {
    ll sz = bulls.size();
    for (ll i = sz - 1; i >= 0; i--) {
        if (bulls[i].right) bulls[i].bullet.move(bulls[i].velocity, 0.f);
        else bulls[i].bullet.move(-bulls[i].velocity, 0.f);

        FloatRect bulletBounds = bulls[i].bullet.getGlobalBounds();
        if (bulls[i].right) bulletBounds.left -= 50.f;
        else bulletBounds.left += 50.f;

        if (bulletBounds.intersects(duck1.myduck.getGlobalBounds())) {
            if (bulls[i].duck == 1) {
                continue;
            }
            bulls.erase(bulls.begin() + i);
            Grave.setPosition(duck1.myduck.getPosition().x, 660.f);
            GameEnd = 1;
            duck1.dead = true;
            continue;
        }
        if (bulletBounds.intersects(duck2.myduck.getGlobalBounds())) {
            if (bulls[i].duck == 2) {
                continue;
            }
            bulls.erase(bulls.begin() + i);
            Grave.setPosition(duck2.myduck.getPosition().x, 660.f);
            GameEnd = 1;
            duck2.dead = true;
            continue;
        }

        if (bulls[i].bullet.getPosition().x <= 0 || bulls[i].bullet.getPosition().x >= 1280 || abs(bulls[i].bullet.getPosition().x - bulls[i].startX) >= bulls[i].range) {
            bulls.erase(bulls.begin() + i);
        }
    }
}
void update_Logic() {
    update_duck(duck1);
    update_duck(duck2);
    update_weapons();
    update_bullets();

    if (Keyboard::isKeyPressed(duck1.hold)) {
        if (!duck1.holding) {
            duck1.holding = true;
            get_weapon(duck1);
        }
    }
    else {
        duck1.holding = false;
    }
    if (Keyboard::isKeyPressed(duck2.hold)) {
        if (!duck2.holding) {
            duck2.holding = true;
            get_weapon(duck2);
        }
    }
    else {
        duck2.holding = false;
    }


    if (duck1.haveWeapon && Keyboard::isKeyPressed(duck1.fire)) {
        if (!duck1.firing) {
            duck1.firing = true;
            Fire(duck1, 1);
        }
    }
    else {
        duck1.firing = false;
    }
    if (duck2.haveWeapon && Keyboard::isKeyPressed(duck2.fire)) {
        if (!duck2.firing) {
            duck2.firing = true;
            Fire(duck2, 2);
        }
    }
    else {
        duck2.firing = false;
    }
    update_sword(duck1, 1);
    update_sword(duck2, 2);
}
void draw_Logic() {
    for (auto weap : weaps) {
        window.draw(weap.weapon);
    }
    for (auto bull : bulls) {
        window.draw(bull.bullet);
    }
    if (!duck1.dead) {
        window.draw(duck1.myduck);
        if (duck1.haveWeapon) {
            window.draw(duck1.myweap.weapon);
        }
        window.draw(duck1.myarm.arm);
    }
    else {
        window.draw(Grave);
    }
    if (!duck2.dead) {
        window.draw(duck2.myduck);
        if (duck2.haveWeapon) {
            window.draw(duck2.myweap.weapon);
        }
        window.draw(duck2.myarm.arm);
    }
    else {
        window.draw(Grave);
    }
}


// Walid
void fadeIn() {

}
void fadeOut() {

}

void updateMusicVal() {
    int musicVal = settingsMenu.menuMusic.getVolume();
    string musicText = "MUSIC VOLUME           " + to_string(musicVal);
    settingsMenu.menuText[0].setString(musicText);
}

void updateMapNum() {
    string currMap= "SELECTED  MAP     " + to_string(mapnum+1);
    gameMenu.menuText[2].setString(currMap);
}

void updateReadiness(Menu& menu) {
    if (menu.selected == 0 && duck1.ready) {
        menu.menuText[0].setString("READY!");
    } 
    else if (menu.selected == 0) {
        menu.menuText[0].setString("PLAYER 1");
    }
    
    if (menu.selected == 3 && duck2.ready) {
        menu.menuText[3].setString("READY!");
    }
    else if (menu.selected == 3) {
        menu.menuText[3].setString("PLAYER 2");
    }
}

void startGame(Menu& menu, ducks& duck1, ducks& duck2) {
    if ((duck1.ready && duck2.ready) && menu.selected == 1) {
        menuState = 0;
    }
}

void initTransition(ducks& duck1, ducks& duck2, int width, int height) {
    transition.font.loadFromFile("img/arcade.ttf");

    for (int i = 0; i < 3; i++) {
        transition.menuText[i].setFont(transition.font);
    }

    transition.menuText[0].setString("SCORE");
    transition.menuText[0].setCharacterSize(60.f);
    transition.menuText[0].setFillColor(Color(255, 255, 255));
    transition.menuText[0].setPosition(Vector2f(width / 2.5f, height / 4.f));

    string score1 = "PLAYER 1    " + to_string(duck1Score);
    transition.menuText[1].setCharacterSize(60.f);
    transition.menuText[1].setFillColor(Color(255, 255, 255));
    transition.menuText[1].setPosition(Vector2f(width / 2.5f, height / 4.f + 200.f));
    transition.menuText[1].setString(score1);
    
    string score2 = "PLAYER 2    " + to_string(duck2Score);
    transition.menuText[2].setCharacterSize(60.f);
    transition.menuText[2].setFillColor(Color(255, 255, 255));
    transition.menuText[2].setPosition(Vector2f(width / 2.5f, height / 4.f + 400.f));
    transition.menuText[2].setString(score2);
    
    }

void drawTransition(int width, int height) {
    string score1 = "PLAYER 1     " + to_string(duck1Score);
    string score2 = "PLAYER 2     " + to_string(duck2Score);

    transition.menuText[0].setString("SCORE");
    transition.menuText[1].setString(score1);
    transition.menuText[2].setString(score2);
    
    for (int i = 0; i < 3; i++) {
        window.draw(transition.menuText[i]);
    }
}

void initMainMenu(int width, int height, RenderWindow& window) {

    float charSize = 60.f;

    // Loading and setting font  
    mainMenu.font.loadFromFile("img/arcade.ttf");

    for (int i = 0; i < 3; i++) {
        mainMenu.menuText[i].setFont(mainMenu.font);
    }

    /* First Button (PLAY) */
    mainMenu.menuText[0].setString("PLAY");
    mainMenu.menuText[0].setCharacterSize(charSize);
    mainMenu.menuText[0].setFillColor(Color(255, 255, 255));
    mainMenu.menuText[0].setPosition(Vector2f(width/1.5f, height / 4.f + 100.f));

    /* Second Button (SETTINGS) */
    mainMenu.menuText[1].setString("SETTINGS");
    mainMenu.menuText[1].setCharacterSize(charSize);
    mainMenu.menuText[1].setFillColor(Color(255, 255, 255));
    mainMenu.menuText[1].setPosition(Vector2f(width / 1.5f, height / 4.f + 250.f));
    
    /* Third Button (EXIT) */
    mainMenu.menuText[2].setString("EXIT");
    mainMenu.menuText[2].setCharacterSize(charSize);
    mainMenu.menuText[2].setFillColor(Color(255, 255, 255));
    mainMenu.menuText[2].setPosition(Vector2f(width / 1.5f, height / 4.f + 400.f));

    // Setting background image
    mainMenu.backgroundTexture.loadFromFile("img/menu.png");
    mainMenu.background.setTexture(mainMenu.backgroundTexture);

    float scaleX, scaleY;

    scaleX = window.getSize().x * 1.0 / mainMenu.backgroundTexture.getSize().x;
    scaleY = window.getSize().y * 1.0 / mainMenu.backgroundTexture.getSize().y;

    mainMenu.background.setScale(scaleX, scaleY);
    mainMenu.background.setPosition(0.f, 0.f);

}

void initGameMenu(int width, int height, RenderWindow& window) { 

    gameMenu.font.loadFromFile("img/arcade.ttf");
    
    for (int i = 0; i < 4; i++) {
        gameMenu.menuText[i].setFont(gameMenu.font);
        gameMenu.menuText[i].setCharacterSize(60);
        gameMenu.menuText[i].setFillColor(Color::White);
    }

    gameMenu.menuText[0].setString("PLAYER 1");
    gameMenu.menuText[0].setPosition(Vector2f(width/6.f - 100, height / 4.f + 400));
    
    gameMenu.menuText[1].setString("START");
    gameMenu.menuText[1].setPosition(Vector2f(width/2.25f, height / 4.f + 400.f));
    
    string currLevel = "SELECTED  MAP     " + to_string(mapnum);
    gameMenu.menuText[2].setString(currLevel);
    gameMenu.menuText[2].setPosition(Vector2f(width/3.f, height / 4.f + 200.f));

    gameMenu.menuText[3].setString("PLAYER 2");
    gameMenu.menuText[3].setPosition(Vector2f(width/1.5f + 100, height / 4.f + 400));




}

void initMusic() {

    // Music
    //if (!settingsMenu.menuMusic.openFromFile("img/music.wav")) {
    //    cout << "Error loading menu music.\n";
    //}

    settingsMenu.menuMusic.setLoop(true);
    settingsMenu.menuMusic.play();
}

void initSettingsMenu(int width, int height, RenderWindow& window) {
    settingsMenu.backgroundTexture.loadFromFile("img/menu.png");
    settingsMenu.background.setTexture(settingsMenu.backgroundTexture);

    float scaleX, scaleY;
    scaleX = window.getSize().x * 1.0 / settingsMenu.backgroundTexture.getSize().x;
    scaleY = window.getSize().y * 1.0 / settingsMenu.backgroundTexture.getSize().y;

    settingsMenu.background.setScale(scaleX, scaleY);
    settingsMenu.background.setPosition(0.f, 0.f);

    settingsMenu.font.loadFromFile("img/arcade.ttf");
    settingsMenu.menuText[0].setFont(settingsMenu.font);
    settingsMenu.menuText[1].setFont(settingsMenu.font);
    settingsMenu.menuText[2].setFont(settingsMenu.font);

    int musicValue = settingsMenu.menuMusic.getVolume();
    string musicText = "MUSIC VOLUME           " + to_string(musicValue);

    settingsMenu.menuText[0].setString(musicText);
    settingsMenu.menuText[0].setCharacterSize(60);
    settingsMenu.menuText[0].setFillColor(Color::White);
    settingsMenu.menuText[0].setPosition(Vector2f(width/2.f, height / 4.f + 100.f));
    string fullscreenText = "FULLSCREEN               " + string(fullscreen ? "ON" : "OFF");
    settingsMenu.menuText[1].setString(fullscreenText);
    settingsMenu.menuText[1].setCharacterSize(60);
    settingsMenu.menuText[1].setFillColor(Color::White);
    settingsMenu.menuText[1].setPosition(Vector2f(width/2.f, height / 4.f + 250.f));


    settingsMenu.menuText[2].setString("BACK");
    settingsMenu.menuText[2].setCharacterSize(60);
    settingsMenu.menuText[2].setFillColor(Color::White);
    settingsMenu.menuText[2].setPosition(Vector2f(width/2.f, height / 4.f + 400));
}

void drawMenu(RenderWindow& window, Menu& menu, int itemCount) {
    window.draw(menu.background);
    
    for (int i = 0; i < itemCount; i++) {
        window.draw(menu.menuText[i]);
    }
}

void moveUp(Menu& menu, int itemCount) {
    if (menu.selected - 1 >= -1) {
        menu.menuText[menu.selected].setOutlineThickness(0);
        menu.menuText[menu.selected].setFillColor(Color(255, 255, 255));

        menu.selected--;

        if (menu.selected == -1) {
            menu.selected = itemCount - 1;
        }

        menu.menuText[menu.selected].setOutlineThickness(10);
        menu.menuText[menu.selected].setOutlineColor(Color(255, 150, 0));
        menu.menuText[menu.selected].setFillColor(Color(255, 255, 255));
    }
}

void moveDown(Menu& menu, ll itemCount) {
    if (menu.selected + 1 <= itemCount) {
        // Reset current button's appearance
        menu.menuText[menu.selected].setOutlineThickness(0);
        menu.menuText[menu.selected].setFillColor(Color(255, 255, 255));

        menu.selected++;

        if (menu.selected == itemCount) {
            menu.selected = 0;
        }

        // Set new button's appearance
        menu.menuText[menu.selected].setOutlineThickness(10);
        menu.menuText[menu.selected].setOutlineColor(Color(255, 150, 0));
        menu.menuText[menu.selected].setFillColor(Color(255, 255, 255));
    }
}

void fullscreenMode(RenderWindow& window) {
    fullscreen = !fullscreen;

    if (fullscreen) {
        window.create(VideoMode::getFullscreenModes()[0], "Duck Game", Style::Fullscreen);
    }
    else {
        window.create(VideoMode(Width, Height), "Duck Game", Style::Default);
    }

}


//Khaled's MAP
Texture ground_texture, background_texture, skeleton_texture, stone_texture, tree_texture, cactus1, cactus2, cactus3, bushs_texture, grass_texture, stone_block_texture;
Sprite blocks[25], skeletons[3], stones[2], tree, ccts[5], bush[3], grs[2], stone_block, background;
void grounds()
{
    blocks[0].setPosition(1000, 540);
    blocks[0].setScale(0.4, 0.35);
    blocks[1].setPosition(700, 375);
    blocks[1].setScale(0.4, 0.35);
    blocks[2].setPosition(220, 280);
    blocks[2].setScale(0.4, 0.35);
    blocks[3].setPosition(0, 375);
    blocks[3].setScale(0.4, 0.35);
    blocks[4].setPosition(920, 300);
    blocks[4].setScale(0.4, 0.35);
    blocks[5].setPosition(415, 190);
    blocks[5].setScale(0.4, 0.35);
    blocks[6].setPosition(325, 585);
    blocks[6].setScale(0.4, 0.35);
    blocks[7].setPosition(0, 1040);
    blocks[7].setScale(0.4, 0.35);
    blocks[8].setPosition(550, 645);
    blocks[8].setScale(0.4, 0.35);
    blocks[9].setPosition(1120, 375);
    blocks[9].setScale(0.25, 0.35);
    blocks[10].setPosition(100, 500);
    blocks[10].setScale(0.55, 0.35);
    blocks[11].setPosition(435, 440);
    blocks[11].setScale(0.4, 0.35);
    blocks[12].setPosition(800, 585);
    blocks[12].setScale(0.25, 0.35);
    blocks[13].setPosition(670, 220);
    blocks[13].setScale(0.4, 0.35);
    Vector2f pos, sc;
    for (int i = 0;i < 14;i++)
    {
        pos = blocks[i].getPosition();
        int x = pos.x;
        int y = pos.y;
        blocks[i].setPosition(x + 30, y - 150);
    }
}
void skeleton()
{
    skeletons[0].setPosition(720, 550);
    skeletons[0].setScale(-0.5, 0.5);
    skeletons[1].setPosition(1000, 205);
    skeletons[1].setScale(0.5, 0.5);
    skeletons[2].setPosition(110, 280);
    skeletons[2].setScale(-0.5, 0.5);
}
void stone()
{
    stones[0].setPosition(590, 540);
    stones[0].setScale(0.5, 0.5);
    stones[1].setPosition(285, 170);
    stones[1].setScale(0.55, 0.55);
}
void tre()
{
    tree.setPosition(500, 40);
    tree.setScale(0.3, 0.3);
}
void cactii()
{
    ccts[0].setPosition(125, 248);
    ccts[0].setScale(0.5, 0.5);
    ccts[1].setPosition(760, 93);
    ccts[1].setScale(-0.5, 0.5);
    ccts[2].setPosition(810, 272);
    ccts[2].setScale(0.7, 0.7);
    ccts[3].setPosition(250, 370);
    ccts[3].setScale(0.6, 0.6);
    ccts[4].setPosition(1100, 410);
    ccts[4].setScale(-0.6, 0.6);
}
void bushs()
{
    bush[0].setPosition(740, 265);
    bush[0].setScale(0.5, 0.5);
    bush[1].setPosition(220, 390);
    bush[1].setScale(-0.5, 0.5);
    bush[2].setPosition(850, 110);
    bush[2].setScale(-0.5, 0.5);
}
void grass()
{
    grs[0].setPosition(1120, 437);
    grs[0].setScale(0.6, 0.6);
    grs[1].setPosition(505, 337);
    grs[1].setScale(0.6, 0.6);
}
void stoneblock()
{
    stone_block.setPosition(380, 478);
    stone_block.setScale(0.35, 0.35);
}
void init_Map1()
{
    DUCK_SCALE = 2.5f;
    GUN_SCALE = 2.f;
    fact = 5.f;
    //gravity = Put_your_val;
    //jumpSpeed = Put_your_val;  //give it negative value
    //velocityX = Put_your_val;   // the duck speed
    init();
    // pistol
    pistol.fix_X = -6.f;
    pistol.fix_Y = -28.f;
    pistol.fix_hold_x = 31.f;
    pistol.fix_hold_y = -16.f;
    pistol.rev = 9.f;
    //sniper
    sniper.fix_X = 25.f;
    sniper.fix_Y = -23.f;
    sniper.fix_hold_x = 18.f;
    sniper.fix_hold_y = -22.f;
    sniper.rev = 24.f;
    //pewpew
    pewpew.fix_X = 3.f;
    pewpew.fix_Y = -16.f;
    pewpew.fix_hold_x = 28.f;
    pewpew.fix_hold_y = -20.f;
    pewpew.rev = 13.f;
    //sword
    sword.fix_hold_x = 48.f;
    sword.fix_hold_y = -20.f;
    sword.rev = 2.f;
    //bull1
    bull[1].scalex = 0.06f;
    bull[1].scaley = 0.06f;
    //bull2
    bull[2].scalex = 0.2f;
    bull[2].scaley = 0.2f;
    //grave
    Grave.setScale(0.16f, 0.1f);

    //spawn weaps
    weaps.push_back(pistol);
    weaps.push_back(sniper);
    weaps.push_back(pewpew);
    weaps.push_back(sword);

    background_texture.loadFromFile("img/BG.png");
    skeleton_texture.loadFromFile("img/skeleton.png");
    ground_texture.loadFromFile("img/ground.png");
    stone_texture.loadFromFile("img/Stone.png");
    tree_texture.loadFromFile("img/Tree.png");
    cactus1.loadFromFile("img/Cactus (1).png");
    cactus2.loadFromFile("img/Cactus (2).png");
    cactus3.loadFromFile("img/Cactus (3).png");
    bushs_texture.loadFromFile("img/Bush (2).png");
    grass_texture.loadFromFile("img/Grass (1).png");
    stone_block_texture.loadFromFile("img/Stoneblock.png");
    tre();
    grounds();
    skeleton();
    stone();
    cactii();
    bushs();
    grass();
    stoneblock();
    background.setScale(1, 0.75);
}
void update_Map1()
{
    background.setTexture(background_texture);
    for (int i = 0;i < 14;i++) blocks[i].setTexture(ground_texture);
    for (int i = 0;i < 3;i++) skeletons[i].setTexture(skeleton_texture);
    for (int i = 0;i < 2;i++) stones[i].setTexture(stone_texture);
    tree.setTexture(tree_texture);
    for (int i = 0;i < 2;i++) ccts[i].setTexture(cactus1);
    for (int i = 2;i < 3;i++) ccts[i].setTexture(cactus2);
    for (int i = 3;i < 5;i++) ccts[i].setTexture(cactus3);
    for (int i = 0;i < 3;i++) bush[i].setTexture(bushs_texture);
    for (int i = 0;i < 2;i++) grs[i].setTexture(grass_texture);
    stone_block.setTexture(stone_block_texture);
    update_Logic();
}
void draw_Map1()
{
    window.draw(background);
    for (int i = 0;i < 14;i++)
    {
        if (i == 7) continue;
        window.draw(blocks[i]);
    }
    for (int i = 0;i < 2;i++) window.draw(stones[i]);
    for (int i = 0;i < 3;i++) window.draw(skeletons[i]);
    window.draw(tree);
    for (int i = 0;i < 2;i++) window.draw(ccts[i]);
    for (int i = 2;i < 3;i++) window.draw(ccts[i]);
    for (int i = 3;i < 5;i++) window.draw(ccts[i]);
    for (int i = 0;i < 3;i++) window.draw(bush[i]);
    for (int i = 0;i < 2;i++) window.draw(grs[i]);
    window.draw(stone_block);
    draw_Logic();
}
void Map1() {
    update_Map1();
    draw_Map1();
}


//Fawzy's MAP
GameTile::GameTile() {
    loadTexture(Ground, "img/ground2.png");
    loadTexture(Tree, "img/tree2.png");
    loadTexture(Cement, "img/cement.png");
    loadTexture(Weapon, "img/weapon.png");
    loadTexture(Branch, "img/branch.png");
    loadTexture(Stone, "img/stone2.png");
    loadTexture(Root, "img/root.png");
}
void GameTile::loadTexture(TileType type, const std::string& path) {
    sf::Texture texture;
    if (texture.loadFromFile(path)) {
        textures[type] = texture;
        sprites[type].setTexture(textures[type]);
    }
}
const sf::Sprite& GameTile::getTileSprite(TileType type) {
    return sprites[type];
}
const int TILE_SIZE = 9;
GameTile::TileType charToTileType(char c) {
    switch (c) {
    case 'g': return GameTile::Ground;
    case 'r': return GameTile::Root;
    case 'c': return GameTile::Cement;
    case 's': return GameTile::Stone;
    case 'b': return GameTile::Branch;
    case 'w': return GameTile::Weapon;
    case 't': return GameTile::Tree;
    default:  return GameTile::None;
    }
}
GameTile gameTiles;
vector<string> level;
void init_Map2() {
    DUCK_SCALE = 1.5;
    GUN_SCALE = 1.2f;
    fact = 3.f;
    //gravity = Put_your_val;
    //jumpSpeed = Put_your_val;  //give it negative value
    //velocityX = Put_your_val;   // the duck speed
    init();
    // pistol
    pistol.fix_X = -2.f;
    pistol.fix_Y = -17.f;
    pistol.fix_hold_x = 18.f;
    pistol.fix_hold_y = -12.f;
    pistol.rev = 11.f;
    //sniper
    sniper.fix_X = 13.f;
    sniper.fix_Y = -14.f;
    sniper.fix_hold_x = 11.f;
    sniper.fix_hold_y = -15.f;
    sniper.rev = 23.f;
    //pewpew
    pewpew.fix_X = 4.f;
    pewpew.fix_Y = -10.f;
    pewpew.fix_hold_x = 15.f;
    pewpew.fix_hold_y = -13.f;
    pewpew.rev = 16.f;
    //sword
    sword.fix_hold_x = 29.f;
    sword.fix_hold_y = -12.f;
    sword.rev = 2.f;
    //bull1
    bull[1].scalex = 0.036f;
    bull[1].scaley = 0.036f;
    //bull2
    bull[2].scalex = 0.12f;
    bull[2].scaley = 0.12f;
    //grave
    Grave.setScale(0.16f, 0.1f);

    //spawn weaps
    weaps.push_back(pistol);
    weaps.push_back(sniper);
    weaps.push_back(pewpew);
    weaps.push_back(sword);


    level = {
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                       w                            ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                                                                                                                    ",
    "                                           w                                                                                        ",
    "                                                                                                                                    ",
    "                                                                                                      ggggg                         ",
    "                                                                                                      ccccc                         ",
    "                                                                                                   gggccccc                         ",
    "                                                                                                   ccccccc                          ",
    "                                                                                              gggggccccc                            ",
    "                                                                                              ccccccccc                             ",
    "                                                                                              ccccccccc   tt                        ",
    "                        t             gggggggggg                                              ccccccccc   tt                        ",
    "                        t             cccccccccc                                                          tt                   w    ",
    "                        t             cccccccccc                                                          tt                        ",
    "                        t                ccccccc                                                          tttbbbbbt                 ",
    "                        t                ccccccc                           s                                t     t                 ",
    "                        t                ccccccc                                                            t     t                 ",
    "                        t                                               gggggggggg                          t     t                 ",
    "                        t                                   s           cccccccccc                          t     t                 ",
    "                        t                                               ccccccccc                           t     t                 ",
    "                        tbbbbbbb                     gggggggggggggggggggccc                                 t     t                 ",
    "                        t                            cccccccccccccccccccccc                                 t     t        ggggggggg",
    "                        t                                  ccccccccccccc                                    t     r        ccccccccc",
    "                        t                                  ccccccccccccc                                    t              ccccccccc",
    "                        t                                  ccccccccccccc                                    t  ggggggggggggcccccc   ",
    "                        t                                                                                   t  cccccccccccccccccc   ",
    "                        t                                                                                   t     ccccccccccccccc   ",
    "                        t                                                                                bbbt     ccccccccccccccc   ",
    "                        t                                                                                   t     ccccccccccccccc   ",
    "                        t                                                           s                       t                       ",
    "                        t                                                                                   t                       ",
    "                        t                    gggggg                              gggggg                     t                       ",
    "                        t                    cccccc                              cccccc                     t                       ",
    "                        t                    cccccc                              cccccc                     t                       ",
    "                        t                    cccccc      s                    gggccccccggg                  t                       ",
    "                        t                    cccccc                           cccccccccccc                  t                       ",
    "                        t                    ccccccggggggggggggggg bbt  ggggggccccccccc               bbbbbbt                       ",
    "                        t                    ccccccccccccccccccccc   t  ccccccccccccccc                     t                       ",
    "                        t                    ccccccccccccccccccccc   t  ccccccccccccccc                     t                       ",
    "                        t                    ccccccccccccccccccccc   t  ccccccccccccccc                     t            w          ",
    "                        tbbb                 ccccccccccc             t  ccccccccc                           t                       ",
    "                   w    t                ggggccccccccccc             t  ccccccccc                           t                       ",
    "                        t                ccccccccccccccc             r  ccccccccc                           t                       ",
    "                        t                                               ccc                                 t                       ",
    "                        t                                            gggccc                                 t                       ",
    "                        t                                            cccccc                                 t                 ggg   ",
    "            ggg         t                                                                             s     t                 ccc   ",
    "            ccc         r                                                                                   t                 ccc   ",
    "            ccc                                                                                     ggggggggt         ggggggggccc   ",
    "            cccggggggggggggggggggg                                                                  ccccccccr         ccccccccccc   ",
    "            cccccccccccccccccccccc                                                                    cccccc          cccccccc      ",
    "            cccccccccccccccccccccc                                            s                       ccccccggggggggggcccccccc      ",
    "            cccccccccccccccccccccc                                                                    cccccccccccccccccccccccc      ",
    "                  ccccccccccccccccggg              ggggggggggggggggggggggggggggggggg                                                ",
    "                  ccccccccccccccccccc     s        ccccccccccccccccccccccccccccccccc                                                ",
    "                  ccccccccccccccccccc              ccccccccccccccccccccccccccccccccc                                                ",
    "                        cccccccccccccggggggggggggggcccccccccccccccccccccccccccccccccgggggg                                          ",
    "                        cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc                                          ",
    "                        cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc                                          ",
    "                              cccccccccc        ccccccccc                     ccccccccccccggg                                       ",
    "                              cccccccccc        ccccccccc                     ccccccccccccccc                                       ",
    "                              cccccccccc        ccccccccc                                                                           ",
    "                                                   cccccc                                                                           ",
    "                                                   cccccc                                                                           ",
    "                                                   cccccc                                                                           ",
    "                                                                                                                            "
    };
}
void update_Map2() {
    for (size_t y = 0; y < level.size(); ++y) {
        for (size_t x = 0; x < level[y].size(); ++x) {
            char tileChar = level[y][x];
            GameTile::TileType tileType = charToTileType(tileChar);
            if (tileType != GameTile::None) {
                sf::Sprite tile = gameTiles.getTileSprite(tileType);
                tile.setPosition(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE));
                window.draw(tile);
            }
        }
    }
    update_Logic();
    draw_Logic();
}
void Map2() {
    update_Map2();
}


// Khaled Ghareeb
struct block
{
    Sprite map_blocks;
};

block b; block obs;
const int MAX_BLOCKS = 100;
block finalground[MAX_BLOCKS];
block finalblock[MAX_BLOCKS];
block finalobs[MAX_BLOCKS];
int groundCount = 0;
int blockCount = 0;
int obsCount = 0;

Sprite backgroundGhareeb;
Texture backgroundtexture;

Texture mapblock_Texture;
Texture obstacels_texture;

void groundd()
{
    for (int i = 0; i < 10; i++)
    {
        block ground;


        ground.map_blocks.setTexture(mapblock_Texture);
        ground.map_blocks.setScale(0.45, 0.17);
        ground.map_blocks.setPosition(0 + i * 150, 697);
        finalground[groundCount++] = ground;
    }
}
void obstacels_position(int x, int y)
{
    obs.map_blocks.setPosition(x, y);
    finalobs[obsCount++] = obs;

}
void block_position(int x, int y)
{

    b.map_blocks.setPosition(x, y);
    finalblock[blockCount++] = b;

}
void blocksGhareeb()
{
    groundd();

    block_position(295, 545);
    block_position(0, 595);
    block_position(1060, 465);
    block_position(0, 470);
    block_position(190, 370);
    block_position(400, 370);
    block_position(610, 370);
    block_position(820, 370);
    block_position(1058, 620);
    block_position(800, 540);
    block_position(0, 270);
    block_position(1050, 270);
    block_position(290, 200);
    block_position(550, 130);
    block_position(800, 180);

    obstacels_position(265, 332);
    obstacels_position(300, 332);
    obstacels_position(700, 619);
    obstacels_position(661, 658);
    obstacels_position(700, 658);
    obstacels_position(98, 431);
    obstacels_position(1130, 390);
    obstacels_position(1130, 427);
    obstacels_position(750, 331);
    obstacels_position(460, 161);
}
void collision(ducks& player)
{
    for (block& b : finalblock)
    {
        FloatRect playerbounds = player.myduck.getGlobalBounds();
        FloatRect wallbound = b.map_blocks.getGlobalBounds();
        if (playerbounds.intersects(wallbound))
        {
            FloatRect intersection;
            playerbounds.intersects(wallbound, intersection);

            if (intersection.width < intersection.height) // left & right
            {
                if (playerbounds.left < wallbound.left) // right collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x - intersection.width, player.myduck.getPosition().y);
                }
                else // left collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x + intersection.width, player.myduck.getPosition().y);
                }
            }
            else // up & down
            {
                if (playerbounds.top < wallbound.top) // down collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x, player.myduck.getPosition().y - intersection.height);
                }
                else // up collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x, player.myduck.getPosition().y + intersection.height);
                }
            }
        }
    }


    for (block& bb : finalground)
    {
        FloatRect playerbounds = player.myduck.getGlobalBounds();
        FloatRect wallbound = bb.map_blocks.getGlobalBounds();
        if (playerbounds.intersects(wallbound))
        {
            FloatRect intersection;
            playerbounds.intersects(wallbound, intersection);

            if (intersection.width < intersection.height) // left & right
            {
                if (playerbounds.left < wallbound.left) // right collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x - intersection.width, player.myduck.getPosition().y);
                }
                else // left collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x + intersection.width, player.myduck.getPosition().y);
                }
            }
            else // up & down
            {
                if (playerbounds.top < wallbound.top) // down collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x, player.myduck.getPosition().y - intersection.height);
                }
                else // up collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x, player.myduck.getPosition().y + intersection.height);
                }
            }
        }
    }


    for (block& bbb : finalobs)
    {
        FloatRect playerbounds = player.myduck.getGlobalBounds();
        FloatRect wallbound = bbb.map_blocks.getGlobalBounds();
        if (playerbounds.intersects(wallbound))
        {
            FloatRect intersection;
            playerbounds.intersects(wallbound, intersection);

            if (intersection.width < intersection.height) // left & right
            {
                if (playerbounds.left < wallbound.left) // right collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x - intersection.width, player.myduck.getPosition().y);
                }
                else // left collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x + intersection.width, player.myduck.getPosition().y);
                }
            }
            else // up & down
            {
                if (playerbounds.top < wallbound.top) // down collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x, player.myduck.getPosition().y - intersection.height);
                }
                else // up collision
                {
                    player.myduck.setPosition(player.myduck.getPosition().x, player.myduck.getPosition().y + intersection.height);
                }
            }
        }
    }


}
void windowcollison(ducks& player)
{

    FloatRect playerBounds = player.myduck.getGlobalBounds();

    if (playerBounds.left < 0) // Left
        player.myduck.setPosition(playerBounds.width / 2, player.myduck.getPosition().y);

    if (playerBounds.left + playerBounds.width > 1280) // Right
        player.myduck.setPosition(1280 - playerBounds.width / 2, player.myduck.getPosition().y);

    if (playerBounds.top < 0)// Top
        player.myduck.setPosition(player.myduck.getPosition().x, playerBounds.height / 2);

}
void init_Map3()
{
    DUCK_SCALE = 2.f;
    GUN_SCALE = 1.6f;
    fact = 3.f;
    //gravity = Put_your_val;
    //jumpSpeed = Put_your_val;  //give it negative value
    //velocityX = Put_your_val;   // the duck speed
    init();
    // pistol
    pistol.fix_X = -4.f;
    pistol.fix_Y = -23.f;
    pistol.fix_hold_x = 25.f;
    pistol.fix_hold_y = -12.f;
    pistol.rev = 10.f;
    //sniper
    sniper.fix_X = 17.f;
    sniper.fix_Y = -18.f;
    sniper.fix_hold_x = 14.f;
    sniper.fix_hold_y = -16.f;
    sniper.rev = 23.f;
    //pewpew
    pewpew.fix_X = 7.f;
    pewpew.fix_Y = -13.f;
    pewpew.fix_hold_x = 18.f;
    pewpew.fix_hold_y = -15.f;
    pewpew.rev = 17.f;
    //sword
    sword.fix_hold_x = 38.f;
    sword.fix_hold_y = -14.f;
    sword.rev = 2.f;
    //bull1
    bull[1].scalex = 0.048f;
    bull[1].scaley = 0.048f;
    //bull2
    bull[2].scalex = 0.16f;
    bull[2].scaley = 0.16f;
    //grave
    Grave.setScale(0.16f, 0.1f);

    //spawn weaps
    weaps.push_back(pistol);
    weaps.push_back(sniper);
    weaps.push_back(pewpew);
    weaps.push_back(sword);


    backgroundtexture.loadFromFile("img/background.jpg");
    backgroundGhareeb.setTexture(backgroundtexture);
    backgroundGhareeb.setScale(0.5, 0.5);

    mapblock_Texture.loadFromFile("img/cccc.png");

    obstacels_texture.loadFromFile("img/Block 2.png");


    b.map_blocks.setTexture(mapblock_Texture);
    b.map_blocks.setScale(0.45, 0.17);


    obs.map_blocks.setTexture(obstacels_texture);
    obs.map_blocks.setScale(0.035, 0.035);

    blocksGhareeb();



}
void update3()
{
    /* duck1.move(0, gravity * deltaTime);
     duck2.move(0, gravity * deltaTime);*/
    //windowcollison(duck1);
    //windowcollison(duck2);
    //collision(duck1);
    //collision(duck2);
    update_Logic();

}
void draw3()
{
    window.draw(backgroundGhareeb);

    for (int i = 0; i < groundCount; i++)
        window.draw(finalground[i].map_blocks);

    for (int i = 0; i < blockCount; i++)
        window.draw(finalblock[i].map_blocks);

    for (int i = 0; i < obsCount; i++)
        window.draw(finalobs[i].map_blocks);

    draw_Logic();


}
void Map3() {
    update3();
    draw3();
}

// Abdullah
void initBackground()
{
    ground.loadFromFile("img/Lv7nNS.png");
    background.setTexture(ground);
    scalex = window.getSize().x * 1.0f / ground.getSize().x;
    scaley = window.getSize().y * 1.0f / ground.getSize().y;
    background.setScale(scalex, scaley);
    background.setPosition(0.f, 0.f);
}
void init_Map4()
{
    initBackground();
    tileCount = 0;  // track how many tiles we've added
    DUCK_SCALE = 2.f;
    GUN_SCALE = 1.6f;
    fact = 3.f;
    //gravity = Put_your_val;
    //jumpSpeed = Put_your_val;  //give it negative value
    //velocityX = Put_your_val;   // the duck speed
    init();
    // pistol
    pistol.fix_X = -4.f;
    pistol.fix_Y = -23.f;
    pistol.fix_hold_x = 25.f;
    pistol.fix_hold_y = -12.f;
    pistol.rev = 10.f;
    //sniper
    sniper.fix_X = 17.f;
    sniper.fix_Y = -18.f;
    sniper.fix_hold_x = 14.f;
    sniper.fix_hold_y = -16.f;
    sniper.rev = 23.f;
    //pewpew
    pewpew.fix_X = 7.f;
    pewpew.fix_Y = -13.f;
    pewpew.fix_hold_x = 18.f;
    pewpew.fix_hold_y = -15.f;
    pewpew.rev = 17.f;
    //sword
    sword.fix_hold_x = 38.f;
    sword.fix_hold_y = -14.f;
    sword.rev = 2.f;
    //bull1
    bull[1].scalex = 0.048f;
    bull[1].scaley = 0.048f;
    //bull2
    bull[2].scalex = 0.16f;
    bull[2].scaley = 0.16f;
    //grave
    Grave.setScale(0.16f, 0.1f);

    //spawn weaps
    weaps.push_back(pistol);
    weaps.push_back(sniper);
    weaps.push_back(pewpew);
    weaps.push_back(sword);



    ice.loadFromFile("img/iceBlocks.png");
    snow.loadFromFile("img/snowBlocks.png");
    wood.loadFromFile("img/woodBlocks.png");
    // Define a 2D map
    string snowMap[23] = {
    "........................................",
    "........................................",
    "........................................",
    "........................................",
    "........................................",
    "........................................",
    "........................................",
    ".__...1..........................2...__.",
    "..|____....._............._......____|..",
    "......|....<|.....<=>.....|>.....|......",
    "......|.....|.............|......|......",
    "......|.....|.............|......|......",
    "......|.....|.............|......|......",
    "......|...<~|++++.._..++++|=>....|......",
    "......|..........................|......",
    "......|..........................|......",
    "......|..........................|......",
    "......|++++++++++++++++++++++++++|......",
    "........................................",
    "........................................",
    "........................................",
    "........................................",
    "........................................"
    };

    int scaleX = 0, scaleY = 0;
    bool isSnow = false;

    for (int y = 0; y < sizeof(snowMap) / sizeof(snowMap[0]); y++) {
        for (int x = 0; x < snowMap[y].length(); x++) {
            if (tileCount >= 1000) break;
            char tileChar = snowMap[y][x];
            bool isWood = false;
            // determine which part of the texture to use
            IntRect texRect;
            bool valid = true;

            switch (tileChar) {
            case '_':
                scaleX = 16;
                scaleY = 14;
                isSnow = true;
                texRect = IntRect(63, 0, scaleX, scaleY);
                break;
            case '+':
                scaleX = 31;
                scaleY = 14;
                isSnow = false;
                texRect = IntRect(0, 0, scaleX, scaleY);
                break;
            case '=':
                scaleX = 12;
                scaleY = 9;
                isWood = true;
                texRect = IntRect(0, 48, scaleX, scaleY);
                break;
            case '~':
                scaleX = 12;
                scaleY = 9;
                isWood = true;
                texRect = IntRect(4, 32, scaleX, scaleY);
                break;
            case '>':
                scaleX = 15;
                scaleY = 9;
                isWood = true;
                texRect = IntRect(0, 48, scaleX, scaleY);
                break;
            case '<':
                scaleX = 15;
                scaleY = 9;
                isWood = true;
                texRect = IntRect(0, 32, scaleX, scaleY);
                break;
            case '|':
                scaleX = 12;
                scaleY = 14;
                isSnow = false;
                texRect = sf::IntRect(34, 95, scaleX, scaleY);
                break;
            case '.':
                break;
            case '1':
                break;
            case '2':
                break;
            default:
                valid = false;
                break;
            }

            if (valid) {
                if (isSnow) mapTiles[tileCount].tileSprite.setTexture(snow);
                else if (isWood) mapTiles[tileCount].tileSprite.setTexture(wood);
                else mapTiles[tileCount].tileSprite.setTexture(ice);
                mapTiles[tileCount].tileSprite.setTextureRect(texRect);
                mapTiles[tileCount].tileSprite.setScale(
                    static_cast<float>(TILE_SIZEE) / scaleX,  // scale X down to 32px
                    static_cast<float>(TILE_SIZEE) / scaleY   // scale Y down to 32px
                );
                mapTiles[tileCount].tileSprite.setPosition(x * TILE_SIZEE, y * TILE_SIZEE);
                if (tileChar == '.' || tileChar == '1' || tileChar == '2')
                {
                    mapTiles[tileCount].tileSprite.setScale(
                        static_cast<float>(TILE_SIZEE),  // scale X down to 32px
                        static_cast<float>(TILE_SIZEE)    // scale Y down to 32px
                    );
                    mapTiles[tileCount].isCollidable = false;
                }
                else mapTiles[tileCount].isCollidable = true;
                mapTiles[tileCount].bounds = mapTiles[tileCount].tileSprite.getGlobalBounds();
                if (tileChar == '.' || tileChar == '1' || tileChar == '2') {
                    mapTiles[tileCount].bounds.width = 32;
                    mapTiles[tileCount].bounds.height = 32;
                }
            }
            tileCount++;
        }
    }
}
void draw4() {
    update_Logic();
    window.draw(background);
    for (int i = 0; i < tileCount; i++) {
        window.draw(mapTiles[i].tileSprite);
    }
    draw_Logic();
}
void Map4() {
    draw4();
}


//Hekal
CircleShape player(30,4);
Texture backgroundTexture;
Texture blockTexture;
Texture groundTexture;
Sprite blockse[25];
Sprite backgroundSprite;
RectangleShape blockscollider[8];

void blocks5(Sprite blocks5[25]) {
    //Bottom-Left Block:
    blocks5[0].setPosition(120, 520);
    blocks5[0].setScale(2.25, 1);
    //Middle-Left Block:
    blocks5[1].setPosition(-10, 320);
    blocks5[1].setScale(2, 1);
    //Bottom-Middle Block:
    blocks5[2].setPosition(380, 390);
    blocks5[2].setScale(3.5, 1);
    //Top-Left Block
    blocks5[3].setPosition(20, 90);
    blocks5[3].setScale(2, 1);
    //Center Block:
    blocks5[4].setPosition(360, 175);
    blocks5[4].setScale(1.7, 1);
    //middle-Right Block:
    blocks5[5].setPosition(950, 300);
    blocks5[5].setScale(2, 1);
    //Top-Right Block:
    blocks5[6].setPosition(1000, 90);
    blocks5[6].setScale(2, 1);
    //top middle
    blocks5[7].setPosition(710, 175);
    blocks5[7].setScale(1.7, 1);

    //ground
    for (int i = 1;i <= 15;i++) {
        blocks5[i + 7].setPosition((i - 1) * 100, 675);
        blocks5[i + 7].setScale(0.5, 0.25);
    }
    // bottom right
    blocks5[23].setPosition(810, 520);
    blocks5[23].setScale(2.25, 1);

}
void init_Map5() {
    DUCK_SCALE = 2.f;
    GUN_SCALE = 1.6f;
    fact = 3.f;
    //gravity = Put_your_val;
    //jumpSpeed = Put_your_val;  //give it negative value
    //velocityX = Put_your_val;   // the duck speed
    init();
    // pistol
    pistol.fix_X = -4.f;
    pistol.fix_Y = -23.f;
    pistol.fix_hold_x = 25.f;
    pistol.fix_hold_y = -12.f;
    pistol.rev = 10.f;
    //sniper
    sniper.fix_X = 17.f;
    sniper.fix_Y = -18.f;
    sniper.fix_hold_x = 14.f;
    sniper.fix_hold_y = -16.f;
    sniper.rev = 23.f;
    //pewpew
    pewpew.fix_X = 7.f;
    pewpew.fix_Y = -13.f;
    pewpew.fix_hold_x = 18.f;
    pewpew.fix_hold_y = -15.f;
    pewpew.rev = 17.f;
    //sword
    sword.fix_hold_x = 38.f;
    sword.fix_hold_y = -14.f;
    sword.rev = 2.f;
    //bull1
    bull[1].scalex = 0.048f;
    bull[1].scaley = 0.048f;
    //bull2
    bull[2].scalex = 0.16f;
    bull[2].scaley = 0.16f;
    //grave
    Grave.setScale(0.16f, 0.1f);

    //spawn weaps
    weaps.push_back(pistol);
    weaps.push_back(sniper);
    weaps.push_back(pewpew);
    weaps.push_back(sword);


    backgroundTexture.loadFromFile("img/nature.png");
    blockTexture.loadFromFile("img/blocks.png");
    ground.loadFromFile("img/ground2.png");
    //set the photo in sprites
    blocks5(blockse);
    for (int i = 0;i < 24;i++) {
        if (i > 7 && i < 23) {
            blockse[i].setTexture(ground);
        }
        else
            blockse[i].setTexture(blockTexture);
    }
    //background set and scale
    backgroundSprite.setTexture(backgroundTexture);
    Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
    Vector2f textureSize = static_cast<sf::Vector2f>(backgroundTexture.getSize());
    backgroundSprite.setScale(windowSize.x / textureSize.x, windowSize.y / textureSize.y);
    for (int i = 0;i < 8;i++) {
        blockscollider[i].setOrigin(blockse[i].getOrigin());
        FloatRect bounds = blockse[i].getGlobalBounds();

        // Create a rectangle shape and match its size
        blockscollider[i].setSize(Vector2f(bounds.width / 2, bounds.height / 2));
    }
}
void collisions() {
    for (int i = 0; i < 24; i++) {
        if (player.getGlobalBounds().intersects(blockse[i].getGlobalBounds())) {
            for (int i = 0; i < 24; i++) {
                if (!(i > 7 && i < 23)) {
                    blockse[i].setTexture(blockTexture);
                    FloatRect playerBounds = player.getGlobalBounds();
                    FloatRect blockBounds = blockse[i].getGlobalBounds();

                    if (playerBounds.intersects(blockBounds)) {
                        FloatRect intersection;
                        playerBounds.intersects(blockBounds, intersection);

                        if (intersection.width < intersection.height) {
                            if (playerBounds.left < blockBounds.left) {
                                // Right collision
                                player.setPosition(playerBounds.left - intersection.width, playerBounds.top);
                            }
                            else {
                                // Left collision
                                player.setPosition(playerBounds.left + intersection.width, playerBounds.top);
                            }
                        }
                        else {
                            if (playerBounds.top < blockBounds.top) {
                                // Down collision
                                player.setPosition(playerBounds.left, playerBounds.top - intersection.height);
                            }
                            else {
                                // Up collision
                                player.setPosition(playerBounds.left, playerBounds.top + intersection.height);
                            }
                        }
                    }
                }
            }
        }
        //left
        if (player.getPosition().x < 0) {
            player.setPosition(0, player.getPosition().y);
        }
        //top
        if (player.getPosition().y < 0) {
            player.setPosition(player.getPosition().x, 0);
        }
        //right
        if (player.getPosition().x + player.getGlobalBounds().width > window.getSize().x) {
            player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
        }
        //bottom
        if (player.getPosition().y + player.getGlobalBounds().height > window.getSize().y) {
            player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);
        }


        //left
        if (player.getPosition().x < 0) {
            player.setPosition(0, player.getPosition().y);
        }
        //top
        if (player.getPosition().y < 0) {
            player.setPosition(player.getPosition().x, 0);
        }
        //right
        if (player.getPosition().x + player.getGlobalBounds().width > window.getSize().x) {
            player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
        }
        //bottom
        if (player.getPosition().y + player.getGlobalBounds().height > window.getSize().y) {
            player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);
        }

    }
}
void update_Map5() {
    collisions();
    update_Logic();
}
void draw_Map5() {
    FloatRect bounds = blockse[23].getGlobalBounds();

    for (int i = 0;i < 8;i++) {
        window.draw(blockscollider[i]);
    }

    window.draw(backgroundSprite);
    for (int i = 0;i < 24;i++)
        window.draw(blockse[i]);
    draw_Logic();
}
void Map5() {
    update_Map5();
    draw_Map5();
}


int main() {

    if (mapnum == 0) init_Map1();
    if (mapnum == 1) init_Map2();
    if (mapnum == 2) init_Map3();
    if (mapnum == 3) init_Map4();
    if (mapnum == 4) init_Map5();
    
    window.setFramerateLimit(90);
    initMainMenu(Width, Height, window);
    initTransition(duck1, duck2, Width, Height);
    initGameMenu(Width, Height, window);
    initSettingsMenu(Width, Height, window);
    initMusic();

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (menuState == 1000) {
                    if (event.key.code == Keyboard::Up) {
                        moveUp(mainMenu, 3);
                    }
                    else if (event.key.code == Keyboard::Down) {
                        moveDown(mainMenu, 3);
                    }
                    else if (event.key.code == Keyboard::Return) {
                        if (mainMenu.selected == 0) {
                            menuState = 2;
                        }
                        else if (mainMenu.selected == 1) {
                            menuState = 1;
                        }
                        else if (mainMenu.selected == 2) {
                            window.close();
                        }
                    }
                }

                // Return to main menu 
                else if (menuState != 1000 && event.key.code == Keyboard::Escape) {
                    menuState = 1000;
                }

                else if (menuState == 1) {
                    if (event.key.code == Keyboard::Down) {
                        moveDown(settingsMenu, 3);
                    }
                    else if (event.key.code == Keyboard::Up) {
                        moveUp(settingsMenu, 3);
                    }
                    else if (event.key.code == Keyboard::Return) {

                        if (settingsMenu.selected == 1) {
                            fullscreenMode(window);

                            initMainMenu(Width, Height, window);
                            initGameMenu(Width, Height, window);
                            initSettingsMenu(Width, Height, window);
                        }

                        if (settingsMenu.selected == 2)
                            menuState = 1000;
                    }
                    else if (event.key.code == Keyboard::Right) {
                        if (settingsMenu.selected == 0) {
                            int newMusicVal = min((int)settingsMenu.menuMusic.getVolume() + 5, 100);
                            settingsMenu.menuMusic.setVolume(newMusicVal);
                            updateMusicVal();
                        }
                    }
                    else if (event.key.code == Keyboard::Left) {
                        if (settingsMenu.selected == 0) {
                            int newMusicVal = max((int)settingsMenu.menuMusic.getVolume() - 5, 0);
                            settingsMenu.menuMusic.setVolume(newMusicVal);
                            updateMusicVal();
                        }
                    }
                }
                else if (menuState == 2) {
                    if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
                        moveDown(gameMenu, 4);
                    }
                    else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
                        moveUp(gameMenu, 4);
                    }
                    else if (event.key.code == Keyboard::Return) {
                        if (gameMenu.selected == 0) { 
                            duck1.ready = !duck1.ready;
                            updateReadiness(gameMenu);
                        }
                        else if (gameMenu.selected == 3) {
                            duck2.ready = !duck2.ready;
                            updateReadiness(gameMenu);
                        }
                        else if (gameMenu.selected == 1) {
                            startGame(gameMenu, duck1, duck2);
                        }
                    }
                    else if (event.key.code == Keyboard::Right) {
                        if (gameMenu.selected == 2) {
                            mapnum++;
                            if (mapnum > 4)
                                mapnum = 0;
                            updateMapNum();
                        }
                    }
                    else if (event.key.code == Keyboard::Left) {
                        if (gameMenu.selected == 2) {
                            mapnum--;
                            if (mapnum < 0)
                                mapnum = 4;
                            updateMapNum();
                        }
 
                    }
                }

            }
        }

        window.clear();
        if (menuState == 1000) {
            drawMenu(window, mainMenu, 3);
        }
        else if (menuState == 0) {
            if (GameEnd) {
                if (duck1.dead) {
                    duck2Score++;
                    cout << "Duck 2 Dead" << endl;
                    cout << "Duck 1 - " << duck1Score << endl;
                    cout << "Duck 2 - " << duck2Score << endl;
                }
                else if (duck2.dead) {
                    duck1Score++;
                    cout << "Duck 2 Dead" << endl;
                    cout << "Duck 1 - " << duck1Score << endl;
                    cout << "Duck 2 - " << duck2Score << endl;
                }

                duck1.dead = false;
                duck2.dead = false;
                GameEnd = 0;
                mapnum++;
                mapnum %= 5;
                menuState = 3;
                trans.restart();
                if (mapnum == 0) init_Map1();
                if (mapnum == 1) init_Map2();
                if (mapnum == 2) init_Map3();
                if (mapnum == 3) init_Map4();
                if (mapnum == 4) init_Map5();
            }
            if (mapnum == 0) Map1();
            if (mapnum == 1) Map2();
            if (mapnum == 2) Map3();
            if (mapnum == 3) Map4();
            if (mapnum == 4) Map5();
        }
        else if (menuState == 1) {
            drawMenu(window, settingsMenu, 3);
        }
        else if (menuState == 2) {
            drawMenu(window, gameMenu, 4);
        }
        else if (menuState == 3) {
            drawTransition(Width, Height);
            if (trans.getElapsedTime().asMilliseconds() > 2000) {
                menuState = 0;
            }
        }

        window.display();
    }

    return 0;
}
