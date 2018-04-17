// Internship attachment, Housemarque
// Housemarque Pre-Interview Coding Test
// Asteroids using SFML
//
//
// I have watched some videos from youtube
// * https://www.youtube.com/watch?v=UcuuqISJqg0
// * https://www.youtube.com/watch?v=WYSupJ5r2zo&t=117s
// * https://www.youtube.com/watch?v=tux1DQ4Sp3A
// * https://www.youtube.com/watch?v=rWaSo2usU4A
// * https://www.youtube.com/watch?v=axIgxBQVBg0&t=177s
//
//
// I have used Code::Blocks
// This code was compiled by GNU GCC compiler in Linux Ubutu 16.5
// GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
// Have g++ follow the C++11 ISO C++ language standard
//
// It needs bellow files
// * sansation.ttf
// * player2.png
// * stone2.png
// * ufo2.png
// * bullet2.png
// * ufobullet.png
//
//
// Vahid 9.4.2018




#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>


using namespace sf;

const int Width = 800;
const int Height = 600;


float DEGTORAD = 0.017453f;



class GameObject
{
    public:
    float x,y,dx,dy,angle;
    bool life;
    std::string tag;
    float gObjSize;
    Sprite sprite;
    bool readyToShot=false;
    int killPoint=0;

    GameObject()
    {
        life=true;
    }

    void Properties(Texture &t,int gOSize,int X,int Y,float Angle=0)
    {
        x=X; y=Y;
        angle = Angle;
        gObjSize=gOSize;
        sprite.setTexture(t);

    }

    virtual void Update(){};

    void Draw(RenderWindow &app)
    {
        sprite.setPosition(x,y);
        sprite.setRotation(angle+90);
        app.draw(sprite);
    }

    virtual ~GameObject(){};
};


class TablePoint
{
    public:
    int point;
    int level;
    int life;
    sf::Font font;
    sf::Text txtLevel,txtLife,txtPoint;

    TablePoint(int li,int le,int po)
    {
        level=le;
        life=li;
        point=po;
        font.loadFromFile("sansation.ttf");
        txtLevel.setFont(font);
        txtLevel.setCharacterSize(15);
        txtLife.setFont(font);
        txtLife.setCharacterSize(15);
        txtPoint.setFont(font);
        txtPoint.setCharacterSize(15);
        DrawTablePoint();
    }



    void Update()
    {
        DrawTablePoint();
    }

    void DrawTablePoint()
    {
        txtLevel.setColor(sf::Color::Blue);
        txtLevel.setStyle(sf::Text::Bold);
        txtLife.setColor(sf::Color::Red);
        txtLife.setStyle(sf::Text::Italic);
        txtPoint.setColor(sf::Color::Green);
        txtPoint.setStyle(sf::Text::Underlined);
        txtLife.setPosition(70,0);
        txtLevel.setString(" Level : "+std::to_string(level)+" ");
        txtLife.setString(" Life : "+std::to_string(life)+" ");
        txtPoint.setPosition(130,0);
        txtPoint.setString(" Point : "+std::to_string(point)+" ");
    }
};


class Bullet: public GameObject
{
    public:

    Bullet()
    {
        tag="bullet";
        killPoint=0;
    }

    void Update()
    {
        dx=cos(angle*DEGTORAD)*6;
        dy=sin(angle*DEGTORAD)*6;
        x+=dx;
        y+=dy;
        if (x>Width || x<0 || y>Height || y<0) life=false;
    }
};

class UfoBullet: public GameObject
{
    public:

    UfoBullet()
    {
        tag="ufobullet";
        killPoint=0;
    }

    void Update()
    {
        dx=cos(angle*DEGTORAD)*6;
        dy=sin(angle*DEGTORAD)*6;
        x+=dx;
        y+=dy;
        if (x>Width || x<0 || y>Height || y<0) life=false;
    }
};

class Rock: public GameObject
{
    public:
    Rock()
    {
        dx=rand()%8-4;
        dy=rand()%8-4;
        tag="rock";
        killPoint=10;
    }
    void  Update()
    {
        x+=dx;
        y+=dy;

        if (x>Width) x=0;  if (x<0) x=Width;
        if (y>Height) y=0;  if (y<0) y=Height;
    }
};


class Ufo: public GameObject
{
    public:
    Ufo()
    {
        dx=rand()%8-4;
        dy=rand()%8-4;
        tag="ufo";
        readyToShot=true;
        killPoint=50;
    }
    void Update()
    {
        x+=dx;
        y+=dy;

        if (x>Width) x=0;  if (x<0) x=Width;
        if (y>Height) y=0;  if (y<0) y=Height;
    }
};


class Player: public GameObject
{
    public:
    bool isRotate;


    Player()
    {
        tag="player";
        killPoint=0;
    }

    void Update()
    {
        /// Player movement
        if (isRotate)
        {
            dx+=cos(angle*DEGTORAD)*0.2;
            dy+=sin(angle*DEGTORAD)*0.2;
        } else {
            dx*=0.99;
            dy*=0.99;
        }

        int maxSpeed=15;
        float speed = sqrt(dx*dx+dy*dy);
        if (speed>maxSpeed)
        {
            dx *= maxSpeed/speed;
            dy *= maxSpeed/speed;
        }
        x+=dx;
        y+=dy;
        if (x>Width) x=0; if (x<0) x=Width;
        if (y>Height) y=0; if (y<0) y=Height;
    }

};


bool isCollide(GameObject *a,GameObject *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->gObjSize + b->gObjSize)*(a->gObjSize + b->gObjSize);
}

int main()
{

    /// Create the main window
    sf::RenderWindow app(sf::VideoMode(Width, Height), "SFML window");

    app.setFramerateLimit(60);



    /// Set Textures
    Texture texturePlayer,textureStone,textureUfo,textureBullet,textureUfoBullet;
    texturePlayer.loadFromFile("player2.png");
    textureStone.loadFromFile("stone2.png");
    textureUfo.loadFromFile("ufo2.png");
    textureBullet.loadFromFile("bullet2.png");
    textureUfoBullet.loadFromFile("ufobullet.png");



    /// the list of game objects
    std::list<GameObject*> gameObjects;



    /// Make Table Point
    TablePoint *tPoint=new TablePoint(10,1,0);



    /// make Player
    Player *pl=new Player();
    pl->Properties(texturePlayer,20,200,200,0);
    gameObjects.push_back(pl);



    /// Level setings
    bool levelAdded=false;
    tPoint->level=1;


	/// Start the game loop
    while (app.isOpen())
    {
        /// Process events
        sf::Event event;

        while (app.pollEvent(event))
        {
            /// Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space))
            {
                /// shot bullet
                Bullet *bul=new Bullet();
                bul->Properties(textureBullet,5,pl->x+3,pl->y+8,pl->angle);
                gameObjects.push_back(bul);
            }

        }

        /// Keyboard
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) pl->angle+=3;
           if (Keyboard::isKeyPressed(Keyboard::Left)  || Keyboard::isKeyPressed(Keyboard::A)) pl->angle-=3;
               if (Keyboard::isKeyPressed(Keyboard::Up)  || Keyboard::isKeyPressed(Keyboard::W)) pl->isRotate=true;
                  else pl->isRotate=false;

        /// Mouse
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // left click...
            sf::Vector2i position = sf::Mouse::getPosition();
            if((position.x>pl->x)&&(position.y>pl->y))
            {
                pl->angle+=3;
                pl->isRotate=true;
            } else {
                pl->angle-=3;
                pl->isRotate=true;
            }
        }


        /// add Level feature
        if(!levelAdded)
        {
            levelAdded=true;
            switch (tPoint->level)
            {
                case 1:
                    for(int i=0;i<4;i++)
                    {
                        Rock *rk = new Rock();
                        rk->Properties(textureStone,30, rand()%Width, rand()%Height, rand()%360);
                        gameObjects.push_back(rk);
                    }
                    break;
                case 2:
                    for(int i=0;i<10;i++)
                    {
                        Rock *rk = new Rock();
                        rk->Properties(textureStone,30, rand()%Width, rand()%Height, rand()%360);
                        gameObjects.push_back(rk);
                    }
                    break;
                case 3:
                    for(int i=0;i<10;i++)
                    {
                        Rock *rk = new Rock();
                        rk->Properties(textureStone,30, rand()%Width, rand()%Height, rand()%360);
                        gameObjects.push_back(rk);
                    }
                    for(int i=0;i<=3;i++)
                    {
                        Ufo *uf = new Ufo();
                        uf->Properties(textureUfo,25, rand()%Width, rand()%Height, -90);
                        gameObjects.push_back(uf);
                    }
                    break;
            }
        }


        /// Detect collide Objects
        for(auto a:gameObjects)
        {
            for(auto b:gameObjects)
            {
                if ((a->tag=="rock" && b->tag=="bullet") || (a->tag=="ufo" && b->tag=="bullet"))
                {
                    if ( isCollide(a,b) )
                    {

                        a->life=false;
                        b->life=false;
                        tPoint->point = tPoint->point + a->killPoint;
                    }

                }
                if ((a->tag=="player" && b->tag=="rock") || (a->tag=="player" && b->tag=="ufo") || (a->tag=="player" && b->tag=="ufobullet"))
                {
                    if ( isCollide(a,b) )
                    {
                        b->life=false;

                        tPoint->life--;
                        tPoint->Update();

                        if(tPoint->life<=0)
                            a->life=false;
                     }
                }

            }
        }



        /// Clear screen
        app.clear(Color(100, 100, 100, 255));


        bool enemyFound=false;

        for(auto i=gameObjects.begin();i!=gameObjects.end();)
        {
            GameObject *e = *i;

            if(!enemyFound) /// check levels objects
                if(e->tag=="rock" || e->tag=="ufo")
                {
                    enemyFound=true;
                }

            e->Update();

            /// propering ufo shot
            if(e->tag=="ufo")
            {
                if(e->readyToShot)
                {
                    e->readyToShot=false;
                    UfoBullet *ubul=new UfoBullet();
                    ubul->Properties(textureUfoBullet,3,e->x+25,e->y+30,rand()%180);
                    gameObjects.push_back(ubul);
                } else {
                    if((rand() % 100) <9)
                        e->readyToShot=true;
                }

            }


            if (e->life==false)
            {
                i=gameObjects.erase(i);
                delete e;
            } else i++;
        }

        if(!enemyFound)
        {
            if(tPoint->level<3)
            {
                levelAdded=false;
                tPoint->level++;
                tPoint->Update();
            }
        }


        // inside the main loop, between window.clear() and window.display()


        /// write table points
        app.draw(tPoint->txtLevel);
        app.draw(tPoint->txtLife);
        app.draw(tPoint->txtPoint);
        /// draw game objects
        if(tPoint->life>0)
            for(auto i:gameObjects)
                i->Draw(app);


        /// Update the window
        app.display();

    } // While app.isOpen

    return EXIT_SUCCESS;
}
