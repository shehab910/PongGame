#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <math.h>
#include "Menu.h"

using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
   // Menu menu(window.getSize().x, window.getSize().y);
    //variables that keep the game loop running
    bool play = true;

    //event object holding all events
    Event event;

    //font
    Font font;
    font.loadFromFile("Data/font.otf");
    Text Score1;
    Score1.setFont(font);
    Score1.setCharacterSize(30);
    Score1.setFillColor(Color::Black);
    Score1.setPosition(360, 10);
    Score1.setString("Score");

    Text Score;
    Score.setFont(font);
    Score.setCharacterSize(30);
    Score.setFillColor(Color::Black);
    Score.setPosition(370, 40);
    Score.setString("Score");
    Score.setString("0 : 0");

    Text Name;
    Name.setFont(font);
    Name.setCharacterSize(20);
    Name.setFillColor(Color::Black);
    Name.setPosition(650, 550);
    Name.setString("Shehab");

    //images
    Texture texPad;
    Texture texBall;
    Texture texBackground;
    if (texPad.loadFromFile("Data/rec.png") == 0)
    {
        return -1;
    }
    if (texBall.loadFromFile("Data/ball.png") == 0)
    {
        return -1;
    }
    if (texBackground.loadFromFile("Data/background.jpg") == 0)
    {
        return -1;
    }


    //sounds
    SoundBuffer buff_hit;

    Sound hit;
    hit.setBuffer(buff_hit);
    if (buff_hit.loadFromFile("Data/hit.wav") == 0)
    {
        return-1;
    }

    //states
    bool up = false, down = false;
    bool up2 = false, down2 = false;

    //variables
    int yVelocityP1 = 0;
    int yVelocityP2 = 0;
    int xVelocityBall = 0;
    int yVelocityBall = 0;
    int P1Score = 0;
    int P2Score = 0;
    int indexx = 6;
    int indexy = 6;
    int index = 0;


    //shapes
    RectangleShape Background;
    Background.setSize(Vector2f(800, 600));
    Background.setPosition(0, 0);
    Background.setTexture(&texBackground);

    RectangleShape P1;
    P1.setSize(Vector2f(20, 200));
    P1.setOrigin(Vector2f(5, 100));
    P1.setPosition(Vector2f(20, 300));
    P1.setFillColor(Color::White);
    P1.setTexture(&texPad);

    RectangleShape P2;
    P2.setSize(Vector2f(20, 200));
    P2.setOrigin(Vector2f(10, 100));
    P2.setPosition(Vector2f(780, 300));
    P2.setFillColor(Color::Blue);
    P2.setTexture(&texPad);

    RectangleShape ball;
    ball.setSize(Vector2f(30, 30));
    ball.setPosition(385, 285);
    ball.setTexture(&texBall);


    while (window.isOpen())
    {
        bool ballInBound = true;
        if (ball.getPosition().x <= 25 || ball.getPosition().x >= 775)
        {
            ballInBound = false;
        }
        if (ballInBound == false)
        {
            ball.setPosition(385, 285);
            xVelocityBall = 0;
            yVelocityBall = 0;
        }
        //////////////////////////////////////////habal
        int ll = rand() % 4;
        if (ll == 0)
        {
            indexy = -6;
            indexx = -6;
        }
        else if (ll == 1)
        {
            indexy = 6;
            indexx = -6;
        }
        else if (ll == 2)
        {
            indexy = 6;
            indexx = 6;
        }
        else if (ll == 3)
        {
            indexy = -6;
            indexx = 6;
        }
        ///////////////////////////////////////////

        ////////////////acc by scoree
        if (P1Score + P2Score >= 1)
        {
            if (indexx < 0) indexx = -7;
            else indexx = 7;

            if (indexy < 0) indexy = -7;
            else indexy = 7;
        }
        if (P1Score + P2Score >= 3)
        {
            if (indexx < 0) indexx = -8;
            else indexx = 8;

            if (indexy < 0) indexy = -8;
            else indexy = 8;
        }
        if (P1Score + P2Score >= 6)
        {
            if (indexx < 0) indexx = -9;
            else indexx = 9;

            if (indexy < 0) indexy = -9;
            else indexy = 9;
        }
        if (P1Score + P2Score >= 8)
        {
            if (indexx < 0) indexx = -10;
            else indexx = 10;

            if (indexy < 0) indexy = -10;
            else indexy = 10;
        }
        //////////////////////////////


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
                if (event.key.code == Keyboard::W)
                {
                    up = true;
                }
                if (event.key.code == Keyboard::S)
                {
                    down = true;
                }
                if (event.key.code == Keyboard::Up)
                {
                    up2 = true;
                }
                if (event.key.code == Keyboard::Down)
                {
                    down2 = true;
                }
                if (event.key.code == Keyboard::Space)
                {
                    xVelocityBall = indexx;
                    yVelocityBall = indexy;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::W)
                {
                    up = false;
                }
                if (event.key.code == Keyboard::S)
                {
                    down = false;
                }
                if (event.key.code == Keyboard::Up)
                {
                    up2 = false;
                }
                if (event.key.code == Keyboard::Down)
                {
                    down2 = false;
                }
            }
        }
        //logic
        if (up == true)
        {
            yVelocityP1 = -5;
        }
        if (down == true)
        {
            yVelocityP1 = 5;
        }
        if (up == true && down == true)
        {
            yVelocityP1 = 0;
        }
        if (up == false && down == false)
        {
            yVelocityP1 = 0;
        }
        P1.move(0, yVelocityP1);

        //out of bound check
        if (P1.getPosition().y < 100)
        {
            P1.setPosition(20, 100);
        }
        if (P1.getPosition().y > 500)
        {
            P1.setPosition(20, 500);
        }

        if (up2 == true)
        {
            yVelocityP2 = -5;
        }
        if (down2 == true)
        {
            yVelocityP2 = 5;
        }
        if (up2 == true && down2 == true)
        {
            yVelocityP2 = 0;
        }
        if (up2 == false && down2 == false)
        {
            yVelocityP2 = 0;
        }
        P2.move(0, yVelocityP2);

        //out of bound check
        if (P2.getPosition().y < 100)
        {
            P2.setPosition(780, 100);
        }
        if (P2.getPosition().y > 500)
        {
            P2.setPosition(780, 500);
        }

        /////////////////////////////////lesa
        if (ball.getGlobalBounds().intersects(P1.getGlobalBounds()) == true  && (down == true || up == true))
        {
            yVelocityBall++;
            xVelocityBall++;
            cout << "Y++ x++\n";
        }
        /////////////////////////////////

        
        ball.move(xVelocityBall, yVelocityBall);
        if (ball.getPosition().y < 0 && ballInBound == true)
        {
            yVelocityBall = -yVelocityBall;
        }
        if (ball.getPosition().y > 550 && ballInBound == true)
        {
            yVelocityBall = -yVelocityBall;
        }
        if (ball.getPosition().x < -50 && ballInBound == true)
        {
            P2Score++;
            ball.setPosition(375, 275);
            xVelocityBall = 0;
            yVelocityBall = 0;
        }
        if (ball.getPosition().x > 800 && ballInBound == true)
        {
            P1Score++;
            ball.setPosition(375, 275);
            xVelocityBall = 0;
            yVelocityBall = 0;
        }

        if (ball.getGlobalBounds().intersects(P1.getGlobalBounds()) == true && ballInBound == true)
        {
            xVelocityBall = -xVelocityBall;
            hit.play();
        }
        
        if (ball.getGlobalBounds().intersects(P2.getGlobalBounds()) == true && ballInBound == true)
        {
            xVelocityBall = -xVelocityBall;
            hit.play();
        }
        

        //rendering
        window.clear();

        window.draw(Background);
        window.draw(Name);
        window.draw(P1);
        window.draw(P2);
        window.draw(ball);

        stringstream text;
        text << P1Score << " : " << P2Score;
        Score.setString(text.str());
        window.draw(Score);
        window.draw(Score1);


        window.display();
    }
    return 0;
}

