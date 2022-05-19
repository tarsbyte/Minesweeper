#ifndef STRUCTURES_H
#define STRUCTURES_H

#define BOARD_H 15
#define BOARD_W 20

struct matrix_element
{
    int number;
    bool bomb;
    bool visible;
    bool flagged;
};

struct mine_matrix
{
    matrix_element matrix[BOARD_H][BOARD_W];
};


#endif // STRUCTURES_H
