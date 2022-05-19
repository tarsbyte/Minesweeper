#ifndef MINE_MATRIX_H
#define MINE_MATRIX_H

#define BOARD_H 15
#define BOARD_W 20

#include <time.h>
#include <queue>
using namespace  std;

class matrixElement
{

    int number;
    bool bomb;
    bool visible;
    bool flagged;

public:

    int getNumber()
    {
        return number;
    }

    bool getIsBomb()
    {
        return bomb;
    }

    bool getIsVisible()
    {
        return visible;
    }

    bool getIsFlagged()
    {
        return flagged;
    }

    void changeFlag()
    {
        this->flagged = ! flagged;
    }

    void setFlag(bool value)
    {
        this->flagged = value;
    }

    void setVisibility(bool value)
    {
        this->visible = value;
    }

    void setBomb(bool value)
    {
        this->bomb = value;
    }

    void setNumber(int number)
    {
        this->number = number;
    }
};

class mineMatrix
{

    int bombsNumber = 0;

    int visibleAmount = 0;
    int allCells = (BOARD_H - 2) * BOARD_W;

    bool failure = false;
    bool victory = false;

    int flagsCounter = 0;

    int restart = false;

    int x_vector[8] = {0,1,1,1,0,-1,-1,-1};
    int y_vector[8] = {-1,-1,0,1,1,1,0,-1};

    bool isInBoard(int i, int j)
    {
        return i >= 0 && j >= 0 && i < BOARD_H - 2 && j < BOARD_W;
    }

public:

    bool isFailure()
    {
        return failure;
    }

    bool isVictory()
    {
        return victory;
    }

    void setRestart(bool value)
    {
        restart = value;
    }

    int getVisibleAmount()
    {
            return visibleAmount;
    }

    int getCellsAmount()
    {
        return allCells;
    }

    void visibleIncrement()
    {
        visibleAmount += 1;
        if(failure == false && (getVisibleAmount() + howManyBombs() >= getCellsAmount()))
        {
            victory = true;
        }
    }

    void flagIncrement()
    {
        flagsCounter += 1;
    }

    void flagDecrement()
    {
        flagsCounter -= 1;
    }

    matrixElement matrix[BOARD_H][BOARD_W];

    int howManyBombs()
    {
        return bombsNumber;
    }

    void matrixPropagation(int x, int y)
    {


        if(matrix[x][y].getIsBomb() && ! this->isVictory())
        {
            failure = true;
            return;
        }

        queue<pair<int,int>> q;


        q.push({x,y});

        while(q.size() > 0)
        {
            pair<int,int> current = q.front();
            q.pop();

            if(! matrix[current.first][current.second].getIsVisible())
            {
                matrix[current.first][current.second].setVisibility(true);
                this->visibleIncrement();
            }


            if(matrix[current.first][current.second].getNumber() > 0 || matrix[current.first][current.second].getIsBomb())
            {
                return;
            }

            for(int k=0; k<8; k++)
            {
                int m = current.first + y_vector[k];
                int n = current.second + x_vector[k];
                if(isInBoard(m,n) && ! matrix[m][n].getIsVisible()&& ! matrix[m][n].getIsBomb() && matrix[m][n].getNumber() == 0)
                {
                    pair<int,int> to_add;
                    to_add.first = m;
                    to_add.second = n;
                    q.push(to_add);
                }
                else if(isInBoard(m,n) && ! matrix[m][n].getIsVisible()&& ! matrix[m][n].getIsBomb() )
                {
                    matrix[m][n].setVisibility(true);
                    this->visibleIncrement();
                }
            }

        }
    }

    void matrixInitialization()
    {
        failure = false;
        this->visibleAmount = 0;
        this->victory = false;
        bombsNumber = 0;
        srand(time(0));
        for(int i=0; i<BOARD_H-2; i++)
        {
            for(int j=0; j<BOARD_W; j++)
            {
                int randValue = rand()%100;
                if(randValue < 10)
                {
                     matrix[i][j].setBomb(true);
                     bombsNumber += 1;
                }
                else
                {
                    matrix[i][j].setBomb(false);
                }
                matrix[i][j].setVisibility(false);
                matrix[i][j].setFlag(false);
            }
        }

        for(int i=0; i<BOARD_H-2; i++)
        {
            for(int j=0; j<BOARD_W; j++)
            {
                if(matrix[i][j].getIsBomb())
                {
                    matrix[i][j].setNumber(0);
                    continue;
                }

                int sum_bombs = 0;

                for(int k=0; k<8; k++)
                {
                    int m = i + y_vector[k];
                    int n = j + x_vector[k];
                    if(isInBoard(m,n) && matrix[m][n].getIsBomb())
                    {
                        sum_bombs += 1;
                    }
                }

                matrix[i][j].setNumber(sum_bombs);

            }
        }

    }


};


#endif // MINE_MATRIX_H
