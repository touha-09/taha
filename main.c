#include "header.h"
#include <stdio.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Mini Enigme Visuelle", NULL);

    EnigmeImage enigme = charger_enigme("enigmes/enigme1");

    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        SDL_BlitSurface(enigme.img_question, NULL, screen, &enigme.pos_question);
        for (int i = 0; i < 3; i++) {
            SDL_BlitSurface(enigme.img_reponses[i], NULL, screen, &enigme.pos_reponses[i]);
        }

        SDL_Flip(screen);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && enigme.etat == 0) {
                int rep = verifier_click(&event, &enigme);
                if (rep != -1) {
                    enigme.etat = (rep == enigme.bonne_reponse) ? 1 : -1;
                    printf("%s\n", enigme.etat == 1 ? "Bonne réponse !" : "Mauvaise réponse !");
                }
            }
        }
    }

    liberer_enigme(&enigme);
    SDL_Quit();
    return 0;
}
