#include "header.h"
#include <stdlib.h>
#include <time.h>

// Charge et optimise une image
SDL_Surface* loadImage(const char* path) {
    SDL_Surface* loaded = IMG_Load(path);
    if (!loaded) return NULL;
    SDL_Surface* optimized = SDL_DisplayFormatAlpha(loaded);
    SDL_FreeSurface(loaded);
    return optimized;
}

// Mélange les pièces
void shufflePieces(Piece* pieces, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        Piece temp = pieces[i];
        pieces[i] = pieces[j];
        pieces[j] = temp;
    }
}

// Affiche un message centré
void showText(SDL_Surface* screen, const char* msg, SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("arial.ttf", 36);
    if (!font) return;
    SDL_Surface* text = TTF_RenderText_Solid(font, msg, color);
    SDL_Rect pos = { (SCREEN_WIDTH - text->w) / 2, (SCREEN_HEIGHT - text->h) / 2 };
    SDL_BlitSurface(text, NULL, screen, &pos);
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
}

// Affiche une image de fin
//void displayEndImage(SDL_Surface* screen, const char* path) {
  //  SDL_Surface* end = loadImage(path);
    //if (end) {
      //  SDL_Surface* zoomed = rotozoomSurface(end, 0, 1.2, 1);
        //SDL_Rect pos = { (SCREEN_WIDTH - zoomed->w) / 2, (SCREEN_HEIGHT - zoomed->h) / 2 };
        //SDL_BlitSurface(zoomed, NULL, screen, &pos);
        //SDL_FreeSurface(end);
        //SDL_FreeSurface(zoomed);
    }
}

// Animation simple d’un chrono avec une bande qui défile
void animateTimer(SDL_Surface* screen, int frame) {
    SDL_Rect bar = { 0, 0, frame % SCREEN_WIDTH, 10 };
    SDL_FillRect(screen, &bar, SDL_MapRGB(screen->format, 255, 100, 100));
}

// Détection du clic sur une image
int checkCollision(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}
/*int verifier_reponse(Enigme *enigme, int choix_utilisateur) {
    return choix_utilisateur == enigme->correct_choice;
}

void mettre_a_jour_score(EnigmeManager *manager, int est_correct) {
    if (est_correct) {
        manager->score += 10;
        manager->level += 1;
    } else {
        manager->lives -= 1;
    }
}

void demarrer_chronometre() {
    start_time = time(NULL);
}

int temps_ecoule() {
    return (int)(time(NULL) - start_time);
}




void animer_message_zoom(SDL_Surface *screen, const char *message_text, SDL_Color color, const char *background_path) {
    int min_size = 24;  // taille minimale
    int max_size = 72;  // taille maximale
    int zoom_steps = 20;

    SDL_Surface *background = load_image(background_path);

    for (int i = 0; i < 2; i++) {  // deux cycles : zoom in + zoom out
        for (int step = 0; step <= zoom_steps; step++) {
            int size = min_size + (step * (max_size - min_size)) / zoom_steps;
            double angle = step * (360.0 / zoom_steps);  // rotation complète en un cycle

            TTF_Font *font = load_font("font/THEBOLDFONT.ttf", size);
            SDL_Surface *message = TTF_RenderText_Solid(font, message_text, color);

            // Appliquer la rotation + garder l'échelle normale (zoom = 1.0)
            SDL_Surface *rotated = rotozoomSurface(message, angle, 1.0, 1);

            if (background) {
                SDL_BlitSurface(background, NULL, screen, NULL);
            } else {
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));  // fallback noir
            }

            SDL_Rect pos;
            pos.x = (screen->w - rotated->w) / 2;
            pos.y = (screen->h - rotated->h) / 2;
            SDL_BlitSurface(rotated, NULL, screen, &pos);

            SDL_Flip(screen);

            SDL_FreeSurface(message);
            SDL_FreeSurface(rotated);
            TTF_CloseFont(font);
            SDL_Delay(30);
        }

        // zoom out + rotation inverse
        for (int step = zoom_steps; step >= 0; step--) {
            int size = min_size + (step * (max_size - min_size)) / zoom_steps;
            double angle = step * (360.0 / zoom_steps);

            TTF_Font *font = load_font("font/THEBOLDFONT.ttf", size);
            SDL_Surface *message = TTF_RenderText_Solid(font, message_text, color);

            SDL_Surface *rotated = rotozoomSurface(message, angle, 1.0, 1);

            if (background) {
                SDL_BlitSurface(background, NULL, screen, NULL);
            } else {
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            }

            SDL_Rect pos;
            pos.x = (screen->w - rotated->w) / 2;
            pos.y = (screen->h - rotated->h) / 2;
            SDL_BlitSurface(rotated, NULL, screen, &pos);

            SDL_Flip(screen);

            SDL_FreeSurface(message);
            SDL_FreeSurface(rotated);
            TTF_CloseFont(font);
            SDL_Delay(30);
        }
    }
/*
