#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <cmath>


using namespace sf;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

int main()
{
    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5;
    t1.loadFromFile("spaceship.png");
    t2.loadFromFile("background.jpg");




    Sprite sPlayer(t1), sBackground(t2);
    sPlayer.setTextureRect(IntRect(40,0,40,40));
    sPlayer.setOrigin(20,20);




    float x=300, y=300;
    float dx=0, dy=0, angle=0;
    bool thrust;

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if(event.type == Event::Closed)
                app.close();
        }


        if (Keyboard::isKeyPressed(Keyboard::Right)) angle+=3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) angle-=3;
        if (Keyboard::isKeyPressed(Keyboard::Up)) thrust=true;
        else thrust=false;

        ////spaceship movement////
        if(thrust)
        {
            dx+=cos(angle*DEGTORAD)*0.2;
            dy+=sin(angle*DEGTORAD)*0.2;
        } else {
            dx*=0.99;
            dy*=0.99;
        }

        int maxSpeed=15;
        float speed = sqrt(dx*dx+dy*dy);
        if(speed>maxSpeed)
        {
            dx*= maxSpeed/speed;
            dy*= maxSpeed/speed;
        }

        x+=dx;
        y+=dy;

        if(x>W) x=0; if(x<0) x=W;
        if(y>H) y=0; if(y<0) y=H;

        sPlayer.setPosition(x,y);
        sPlayer.setRotation(angle+90);



        //// draw /////
        app.clear();
        app.draw(sBackground);
        app.draw(sPlayer);
        //app.draw(sExplosion);
        //// test1 for(auto i:entities) i->draw(app);

        //app.draw(sRock.sprite);
        app.display();

    } // End of While

    return 0;
}
