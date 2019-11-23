#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define FPS 60
#define WIDTH  800
#define HEIGHT 600
#define IP_MAX_SIZE 100

double startingTime;

    ALLEGRO_DISPLAY *janela;
    ALLEGRO_TIMER *tempo;
    ALLEGRO_FONT *font;
    ALLEGRO_EVENT_QUEUE *fila_eventos;
    ALLEGRO_BITMAP *botao_sair, *botao_jogar,*botao_historia,*botao_tutorial;
    ALLEGRO_BITMAP *background,*backgroundHistoria,*backgroundTutorial,*backgroundIP,*backgroundLogin,*backgroundCharacter;
    ALLEGRO_BITMAP *imagem ,*backgroundNave,*backgroundGameplay;
    ALLEGRO_BITMAP *astrURSS,*astrBR,*astrMessi,*astrDefault,*astrURSSL,*astrURSSR,*astrBRL,*astrBRR;
    ALLEGRO_BITMAP *astrMessiL,*astrMessiR,*astrDefaultL,*astrDefaultR,*oxigenio,*telaDerrota,*telaVitoria;
    ALLEGRO_AUDIO_STREAM *musica;
//========================
//========================

//EXAMPLE STRUCT
typedef struct DADOS
{
    char mensagem[100];
    int valor;
}DADOS;


//MAIN ALLEGRO FUNCTIONS
bool coreInit();
bool windowInit(int W, int H, char title[]);
bool inputInit();
void allegroEnd();

//FPS CONTROL FUNCTIONS
void startTimer();
double getTimer();
void FPSLimit();

//RESOURCE LOADING FUNCTIONS
bool loadGraphics();
bool fontInit();
bool loadMusic();
//INPUT READING FUNCTION
void readInput(ALLEGRO_EVENT event, char str[], int limit);


#endif