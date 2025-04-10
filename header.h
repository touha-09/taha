#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct {
    SDL_Surface *img_question;
    SDL_Surface *img_reponses[3];
    SDL_Rect pos_question;
    SDL_Rect pos_reponses[3];
    int bonne_reponse;
    int etat; // -1: échec, 0: pas encore résolu, 1: réussi
} EnigmeImage;

EnigmeImage charger_enigme(const char *chemin);
void liberer_enigme(EnigmeImage *e);
int verifier_click(SDL_Event *event, EnigmeImage *e);

#endif
