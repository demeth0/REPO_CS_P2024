#include <stdint.h>

typedef uint8_t sudoku[9][9];

uint8_t estValideH(sudoku s,uint8_t x,uint8_t y,uint8_t n);
uint8_t estValideV(sudoku s,uint8_t x,uint8_t y,uint8_t n);
uint8_t estValideR(sudoku s,uint8_t x,uint8_t y,uint8_t n);
uint8_t estValide(sudoku s,uint8_t x,uint8_t y,uint8_t n);
uint8_t estVide(sudoku s, uint8_t x,uint8_t y,uint8_t n);


void initialiserSudoku(sudoku s);
uint8_t compterLibres(sudoku s); 
void afficherSudoku(sudoku s);
void lireAction(uint8_t *abandon,uint8_t * l,uint8_t *c,uint8_t *v);
uint8_t estValide(sudoku s,uint8_t x,uint8_t y,uint8_t n);

uint8_t trouverMin(sudoku s,uint8_t *x,uint8_t *y,uint8_t *n);
uint8_t resoudreSudoku(sudoku s);

uint8_t chargerSudoku(sudoku s, char *path); 