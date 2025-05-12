#include "header.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("Mini Puzzle Game", NULL);

    SDL_Surface* bg = loadImage("enigme.png");
    SDL_Surface* imgStar = loadImage("kenz.png");
    SDL_Surface* imgBox  = loadImage("kenz2.png");
    SDL_Surface* imgGem  = loadImage("gem.png");
    SDL_Surface* imgBomb = loadImage("bommmb.png");

    // Initialisation des pièces sans boucle
    Piece pieces[4];
    pieces[0] = (Piece){ imgStar, {100, 450, 0, 0}, {100, 100}, 0, 0 };
    pieces[1] = (Piece){ imgBox,  {220, 450, 0, 0}, {220, 100}, 0, 0 };
    pieces[2] = (Piece){ imgGem,  {340, 450, 0, 0}, {340, 100}, 0, 0 };
    pieces[3] = (Piece){ imgBomb, {460, 450, 0, 0}, {460, 100}, 0, 1 }; // Bombe

    shufflePieces(pieces, 4);

    int quit = 0, selected = -1;
    int gameState = 0;
    SDL_Event event;
    int frame = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = 1;

            if (event.type == SDL_MOUSEBUTTONDOWN && gameState == 0) {
                int mx = event.button.x;
                int my = event.button.y;
                for (int i = 0; i < 4; i++) {
                    if (!pieces[i].isPlaced && checkCollision(mx, my, pieces[i].pos))
                        selected = i;
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP && selected != -1) {
                int mx = event.button.x;
                int my = event.button.y;
                if (mx >= pieces[selected].target.x && mx <= pieces[selected].target.x + 100 &&
                    my >= pieces[selected].target.y && my <= pieces[selected].target.y + 100) {

                    pieces[selected].pos.x = pieces[selected].target.x;
                    pieces[selected].pos.y = pieces[selected].target.y;
                    pieces[selected].isPlaced = 1;

                    if (pieces[selected].isBomb)
                        gameState = 2; // Perdu
                }
                selected = -1;
            }

            if (event.type == SDL_MOUSEMOTION && selected != -1) {
                pieces[selected].pos.x = event.motion.x - 50;
                pieces[selected].pos.y = event.motion.y - 50;
            }
        }

        // Vérification de la victoire
        if (gameState == 0) {
            int win = 1;
            for (int i = 0; i < 4; i++) {
                if (!pieces[i].isPlaced && !pieces[i].isBomb)
                    win = 0;
            }
            if (win)
                gameState = 1;
        }

        SDL_BlitSurface(bg, NULL, screen, NULL);
        animateTimer(screen, frame++);

        for (int i = 0; i < 4; i++)
            SDL_BlitSurface(pieces[i].image, NULL, screen, &pieces[i].pos);

        if (gameState == 1)
            showText(screen, "Bravo !", (SDL_Color){0, 255, 0});
        else if (gameState == 2)
            showText(screen, "Perdu !", (SDL_Color){255, 0, 0});

        if (gameState)
            displayEndImage(screen, "xxxx.png");

        SDL_Flip(screen);
        SDL_Delay(30);
    }

    SDL_FreeSurface(bg);
    SDL_FreeSurface(imgStar);
    SDL_FreeSurface(imgBox);
    SDL_FreeSurface(imgGem);
    SDL_FreeSurface(imgBomb);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
