#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "graphics_and_engine.h"
#include "mine_matrix.h"
#include <time.h>

#define BOARD_H 15
#define BOARD_W 20
int height = 40;
using namespace std;
using namespace sf;

mineMatrix matrix;

int MineEngine()
{
    RenderWindow window(sf::VideoMode(800, 600, 32), "Saper");

    matrix.matrixInitialization();

    Vector2i mousePosition;

    Texture texture_button;
    Texture texture_hide_button;
    Texture button_1;
    Texture button_2;
    Texture button_3;
    Texture button_4;
    Texture button_5;
    Texture button_6;
    Texture button_7;
    Texture button_8;
    Texture bomb;
    Texture flag;
    Texture face;
    Texture lose;
    Texture win;
    Texture win_face;
    Texture lose_face;

    if(!texture_button.loadFromFile("Button.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!texture_hide_button.loadFromFile("HidenButton.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!lose_face.loadFromFile("Lost_face.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!win_face.loadFromFile("Win_face.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!lose.loadFromFile("Lose.png"))
    {
        perror("Image loading error");
        exit(-1);
    }


    if(!win.loadFromFile("Win.png"))
    {
        perror("Image loading error");
        exit(-1);
    }


    if(!bomb.loadFromFile("Bomb.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!face.loadFromFile("Head.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!flag.loadFromFile("Flag.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_1.loadFromFile("Button_1.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_2.loadFromFile("Button_2.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_3.loadFromFile("Button_3.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_4.loadFromFile("Button_4.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_5.loadFromFile("Button_5.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_6.loadFromFile("Button_6.png"))
    {
        perror("Image loading error");
        exit(-1);
    }


    if(!button_7.loadFromFile("Button_7.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    if(!button_8.loadFromFile("Button_8.png"))
    {
        perror("Image loading error");
        exit(-1);
    }

    while(window.isOpen())
    {
        Event event;

        if(Mouse::isButtonPressed(Mouse::Left))
        {
            mousePosition = Mouse::getPosition(window);

            if(mousePosition.y < 80 && mousePosition.x > 360 && mousePosition.x < 440)
            {
                matrix.setRestart(true);
                matrix.matrixInitialization();
            }
            else
            {
                int x = mousePosition.x / 40;
                int y = (mousePosition.y - 2 * height)/40;

                if(! matrix.matrix[y][x].getIsVisible())
                {

                    matrix.matrixPropagation(y,x);
                }

            }

        }
        else if(Mouse::isButtonPressed(Mouse::Right))
        {
            mousePosition = Mouse::getPosition(window);

            int x = mousePosition.x / 40;
            int y = (mousePosition.y - 2 * height)/40;

            if(!matrix.matrix[y][x].getIsVisible())
            {
                if(!matrix.matrix[y][x].getIsFlagged())
                {
                    matrix.matrix[y][x].setFlag(true);
                    matrix.flagIncrement();

                }
                else
                {
                    matrix.matrix[y][x].setFlag(false);
                    matrix.flagDecrement();
                }

                struct timespec spec1, spec2;
                spec1.tv_sec = 0;
                spec1.tv_nsec = 300000000L;

                nanosleep(&spec1, &spec2);
            }

        }


        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);


        Sprite sprite;
        if(matrix.isFailure())
        {
             sprite.setTexture(lose_face);
        }
        else if(matrix.isVictory())
        {
             sprite.setTexture(win_face);
        }
        else
        {
            sprite.setTexture(face);
        }

        sprite.setPosition(9 * height, 0);
        window.draw(sprite);

        Sprite sprite_end;
        if(matrix.isFailure())
        {

            sprite_end.setTexture(lose);
            sprite_end.setPosition(3 * height, 0);
            window.draw(sprite_end);

        }
        else if(matrix.isVictory())
        {
            sprite_end.setTexture(win);
            sprite_end.setPosition(3 * height, 0);
            window.draw(sprite_end);
        }

        for(int i=2; i <= BOARD_H+2; i++)
        {
            for(int j=0; j<=BOARD_W; j++)
            {
                Sprite sprite;


                if(!matrix.matrix[i-2][j].getIsVisible() && ! matrix.isFailure() && !matrix.isVictory())
                {
                    if(matrix.matrix[i-2][j].getIsFlagged())
                    {
                        sprite.setTexture(flag);
                    }
                    else
                    {
                        sprite.setTexture(texture_hide_button);
                    }

                }
                else
                {

                    switch (matrix.matrix[i-2][j].getNumber()) {
                     case 0:
                        if(matrix.matrix[i-2][j].getIsBomb())
                        {
                             sprite.setTexture(bomb);
                        }
                        else
                        {
                             sprite.setTexture(texture_button);
                        }

                        break;
                    case 1:
                        sprite.setTexture(button_1);
                        break;
                    case 2:
                        sprite.setTexture(button_2);
                        break;
                    case 3:
                        sprite.setTexture(button_3);
                        break;
                    case 4:
                        sprite.setTexture(button_4);
                        break;
                    case 5:
                        sprite.setTexture(button_5);
                        break;
                    case 6:
                        sprite.setTexture(button_6);
                        break;
                    case 7:
                        sprite.setTexture(button_7);
                        break;
                    case 8:
                        sprite.setTexture(button_8);
                        break;
                    default:
                        break;

                    }

                }


                sprite.setPosition(j * height, i * height);
                window.draw(sprite);
            }
        }



        window.display();
    }

    return 0;

}
