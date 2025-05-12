#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    SDL_Surface* image;
    SDL_Rect pos;        // Position actuelle
    SDL_Rect target;     // Position cible
    int isPlaced;        // 1 si la pièce est bien placée
    int isBomb;          // 1 si c'est une bombe
} Piece;

SDL_Surface* loadImage(const char* path);
void shufflePieces(Piece* pieces, int size);
void showText(SDL_Surface* screen, const char* msg, SDL_Color color);
void displayEndImage(SDL_Surface* screen, const char* path);
void animateTimer(SDL_Surface* screen, int frame);
int checkCollision(int x, int y, SDL_Rect rect);

#endif
