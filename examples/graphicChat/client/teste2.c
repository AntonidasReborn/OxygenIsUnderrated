// Os arquivos de cabeçalho
#include "ACore.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NENHUM 'p'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define CIMA 'w'
#define BAIXO 's'
// Atributos da tela
#define LARGURA_TELA 800
#define ALTURA_TELA 600

#define BUFFER_SIZE 100
#define MAX_HP 300
#define MAX_CLIENTS 2
#define ASTRBR 1
#define ASTRURSS 2
#define ASTRMESSI 3
#define ASTRDEFAULT 4

#define LOGIN_MAX_SIZE 13

typedef struct Pos{
        int x, y; //posicao (x,y) que o boi está
}Pos;

typedef struct Player{
    int id; //numero no intervalo [0,MAX_CLIENTS)
    int oxigenio; //numero entre [0,MAX_HP]
    char movimento; // NENHUM, DIREITA, ESQUERDA, CIMA, BAIXO
    char login[LOGIN_MAX_SIZE];
	char estado;
    char personagem; //é um personagem de define igual BOI_X, em que X está no intervalo [1,4]
    char direcao; //direcao que o astronauta ta
	char direcao2;
	Pos posicao; //posicao (x,y) 
}Player;

Player defaultPlayer(int id_player){
  Player temp;
  temp.id = id_player;
  temp.oxigenio=MAX_HP; 
  temp.movimento=NENHUM;
  strcpy(temp.login,"");
  temp.estado = DIREITA;
  temp.personagem=ASTRBR;
  
  switch(id_player){
    case 0:
      temp.posicao.x=3;
      temp.posicao.y=3;
	  break;
    case 1:
      temp.posicao.x=3;
      temp.posicao.y=9;
	  break;
    case 2:
      temp.posicao.x=22;
      temp.posicao.y=3;
	  break;
    case 3:
      temp.posicao.x=22;
      temp.posicao.y=9;
	  break;
  }
  temp.direcao = DIREITA;
  temp.direcao = BAIXO;
  return temp;
}
void fecha(){
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(botao_historia);
    al_destroy_bitmap(botao_jogar);
    al_destroy_bitmap(botao_tutorial);
    al_destroy_bitmap(background);
    al_destroy_display(janela);
    al_destroy_font(font);
    al_destroy_event_queue(fila_eventos);
     al_destroy_audio_stream(musica);
}

void clearListPlayers(Player * lista_jogadores){
  int i;
  for(i=0;i<MAX_CLIENTS;i++){
    lista_jogadores[i] = defaultPlayer(i);
  }
}

Player lista_jogadores[MAX_CLIENTS];

Pos oxygen;

void printPlayer(Player one){
  printf("Id: %d\n", one.id);
  printf("oxigenio: %d\n", one.oxigenio);
  printf("Movimento: %c\n", one.movimento);
  printf("Login: %s\n", one.login);
  printf("Personagem: %d\n", one.personagem);
  printf("X: %d\n", one.posicao.x);
  printf("Y: %d\n", one.posicao.y);
  printf("Direcao: %c\n", one.direcao);
}

int meu_id;

enum conn_ret_t tryConnect(char IP[]) {
  char server_ip[30];
  //printf("Please enter the server IP: ");
  //scanf(" %s", server_ip);
  //getchar();
  return connectToServer(IP);
}
void assertConnection(char IP[], char login[]) {
  //printHello();
  enum conn_ret_t ans = tryConnect(IP);

  while (ans != SERVER_UP) 
  {
    if (ans == SERVER_DOWN) {
      puts("Server is down!");
    } else if (ans == SERVER_FULL) {
      puts("Server is full!");
    } else if (ans == SERVER_CLOSED) {
      puts("Server is closed for new connections!");
    } else {
      puts("Server didn't respond to connection!");
    }
    printf("Want to try again? [Y/n] ");
    int res;
    while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n'){
      puts("anh???");
    }
    if (res == 'n') {
      exit(EXIT_SUCCESS);
    }
    ans = tryConnect(IP);
  }
  int 
  
  len = (int)strlen(login);
  sendMsgToServer(login, len + 1);
  recvMsgFromServer(&meu_id, WAIT_FOR_IT);
}
void printWaitroom(){
	al_draw_bitmap(backgroundNave, 0,0, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-490,
                     ALLEGRO_ALIGN_CENTRE, "ESPERANDO");
    al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-400,
                     ALLEGRO_ALIGN_CENTRE, "JOGADORES");
    } 
int playersReady(Player * playerList){
	int i, ready = 0;
	for(i=0;i<MAX_CLIENTS;i++){
		if(strcmp(playerList[i].login,"")!=0){
			ready++;
		}
	}
	return ready;
}



void printGameCharacter(int astr, float largura, float altura, char estado, char direcao, char direcao2){
	if(estado == DIREITA){
		switch(astr){
			case ASTRBR:
				if(direcao2 == BAIXO) al_draw_bitmap(astrBRR, largura, altura, 0);
				else al_draw_bitmap(astrBRR, largura, altura, 0);
				break;
			case ASTRDEFAULT:
				if(direcao2 == BAIXO) al_draw_bitmap(astrDefaultR, largura, altura, 0);
				else al_draw_bitmap(astrDefaultR, largura, altura, 0);
				break;
			case ASTRURSS:
				if(direcao2 == BAIXO) al_draw_bitmap(astrURSSR, largura, altura, 0);
				else al_draw_bitmap(astrURSSR, largura, altura, 0);
				break;
			case ASTRMESSI:
				if(direcao2 == BAIXO) al_draw_bitmap(astrMessiR, largura, altura, 0);
				else al_draw_bitmap(astrMessiR, largura, altura, 0);
				break;
		}
	}else if(estado == ESQUERDA){
		switch(astr){
			case ASTRBR:
				if(direcao2 == BAIXO) al_draw_bitmap(astrBRL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				else al_draw_bitmap(astrBRL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case ASTRDEFAULT:
				if(direcao2 == BAIXO) al_draw_bitmap(astrDefaultL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				else al_draw_bitmap(astrDefaultL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case ASTRURSS:
				if(direcao2 == BAIXO) al_draw_bitmap(astrURSSL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				else al_draw_bitmap(astrURSSL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case ASTRMESSI:
				if(direcao2 == BAIXO) al_draw_bitmap(astrMessiL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				else al_draw_bitmap(astrMessiL, largura, altura, ALLEGRO_FLIP_HORIZONTAL);
				break;
		}
	}
}
void printPlayers(Player * lista_jogadores){
	int i;
	//ALLEGRO_COLOR cor = al_map_rgb(255,0,0);
	for(i=0;i<MAX_CLIENTS;i++){
		if(strcmp(lista_jogadores[i].login,"") != 0){
			//al_draw_filled_circle(LARGURA/22*(2*(float)lista_jogadores[i].posicao.x+1),ALTURA/22*(2*(float)lista_jogadores[i].posicao.y+1), 10, cor);
			printGameCharacter(lista_jogadores[i].personagem,32*(float)lista_jogadores[i].posicao.x, 24+32*(float) lista_jogadores[i].posicao.y, lista_jogadores[i].estado, lista_jogadores[i].direcao, lista_jogadores[i].direcao2);
		}
	}
}
 short int matriz[18][25] ={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void dropaoxigenio(){

    oxygen.x = rand()%18;
    oxygen.y = rand()%25;
    matriz[oxygen.x][oxygen.y] = 5;
    al_draw_bitmap(oxigenio, (oxygen.x *32) +24, (oxygen.y) *32, 0); 

}
int procura(Player *lista_jogadores){
    int i;
    int index = -1;
    for (i=0;i<MAX_CLIENTS;i++){
        if (matriz[lista_jogadores[i].posicao.x][lista_jogadores[i].posicao.y] == 5){
            index =i;
        }
    }

return index;
}
int main(void){
    
    clearListPlayers(lista_jogadores);
    char ServerIP[30] = {"127.0.0.1"};
    //Salva o login
    char loginMsg[BUFFER_SIZE]={0};
    
    // Flag que condicionará nosso looping
    int sair = 0,historia = 0,tutorial=0,jogar=0,telaIp=0,telaLogin=0,telaCharacter=0,telaEspera=0,telaGameplay=0;
    if (!coreInit()){
        return -1;
	}
    //Agora vamos criar a nossa janela. Largura e Altura em pixels, o título é uma string.
    if (!windowInit(LARGURA_TELA, ALTURA_TELA, "OxygenIsUnderrated")){
	    return -1;
	}
    //Agora inicializamos nosso teclado e mouse, para que a janela responda às entradas deles
    if (!inputInit()){
		printf("Erro no teclado");
        return -1;
	}
    //Agora inicializamos nossas fontes
    if(!fontInit()){
      return -1;
	}
    if(!loadMusic()){
        return -1;
	}
    //E por fim todas as imagens que vamos utilizar no programa.
    if(!loadGraphics()){
        return -1;
	}
    
    
    
    
    
    
 
    //addon que da suporte as extensoes de audio
    
    
    
 
    // Flag indicando se o mouse está sobre o retângulo central
    int botaoSair = 0,botaoJogar = 0,botaoTutorial = 0,botaoHistoria = 0;
    while (!sair){
        startTimer();        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            // Se o evento foi de movimentação do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verificamos se ele está sobre a região do retângulo central
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50 &&
                evento.mouse.x <= LARGURA_TELA - 50 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10){
                    botaoSair = 1;
                }
                else{
                    botaoSair = 0;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_jogar) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 150 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_jogar) - 150){
                    botaoJogar = 1;
                }
                else{
                    botaoJogar = 0;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_historia) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_historia) - 10){
                    botaoHistoria = 1;
                }
                else{
                    botaoHistoria = 0;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_tutorial) - 300 &&
                evento.mouse.x <= LARGURA_TELA - 300 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_tutorial) - 10){
                    botaoTutorial = 1;
                }
                else{
                    botaoTutorial = 0;
                }
            }
            // Ou se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50 &&
                evento.mouse.x <= LARGURA_TELA - 50 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10){
                    sair = 1;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_historia) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_historia) - 10){
                    historia = 1;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_tutorial) - 300 &&
                evento.mouse.x <= LARGURA_TELA - 300 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_tutorial) - 10){
                    tutorial = 1;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_jogar) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 150 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_jogar) - 150){
                    jogar = 1;
                }
            }
        }
        while(jogar==1){
            startTimer();
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            readInput(evento,ServerIP,LOGIN_MAX_SIZE);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        telaLogin=1;
                        jogar=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    fecha();
	            }
        }
             al_draw_bitmap(backgroundIP, LARGURA_TELA - al_get_bitmap_width(backgroundIP),
        ALTURA_TELA  - al_get_bitmap_height(backgroundIP), 0);

        if (strlen(ServerIP) > 0)
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, ServerIP);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
    }
         al_flip_display();    
    }
         while(telaLogin==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            readInput(evento,loginMsg,LOGIN_MAX_SIZE);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        telaCharacter=1;
                        telaLogin=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
	                fecha();
	            }
        }
             al_draw_bitmap(backgroundLogin, LARGURA_TELA - al_get_bitmap_width(backgroundLogin),
        ALTURA_TELA  - al_get_bitmap_height(backgroundLogin), 0);

        if (strlen(loginMsg) > 0)
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, loginMsg);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "<login>");
    }
        
        al_flip_display();    
    }         
        while(historia==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        historia=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    fecha();
	            }
        }
             al_draw_bitmap(backgroundHistoria, LARGURA_TELA - al_get_bitmap_width(backgroundHistoria),
        ALTURA_TELA  - al_get_bitmap_height(backgroundHistoria), 0);
         
        al_flip_display();    
    }
    int personagem_exibido = ASTRBR;
     while(telaCharacter==1){
         startTimer();
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_RIGHT:
                         personagem_exibido+=1;
							personagem_exibido%=5;
							if(personagem_exibido == 0){
								personagem_exibido++;
							}
                        break;
                    case ALLEGRO_KEY_LEFT:
                        personagem_exibido-=1;
							if(personagem_exibido == 0){
								personagem_exibido+=4;
							}
                        break;
                    case ALLEGRO_KEY_ENTER:
                        telaEspera=1;
                        telaCharacter=0;
                        break;
                    
                        
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    fecha();
	            }
        }
         al_draw_bitmap(backgroundCharacter, LARGURA_TELA - al_get_bitmap_width(backgroundCharacter),
        ALTURA_TELA  - al_get_bitmap_height(backgroundCharacter), 0);
        if(personagem_exibido==1){
            al_draw_bitmap(astrBR, LARGURA_TELA - al_get_bitmap_width(astrBR)-340,
            ALTURA_TELA  - al_get_bitmap_height(astrBR)-220, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "BRASIL");
        }
        if(personagem_exibido==2){
           al_draw_bitmap(astrURSS, LARGURA_TELA - al_get_bitmap_width(astrURSS)-340,
        ALTURA_TELA  - al_get_bitmap_height(astrURSS)-220, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "URSS");
        }
        if(personagem_exibido==3){
           al_draw_bitmap(astrMessi, LARGURA_TELA - al_get_bitmap_width(astrMessi)-340,
        ALTURA_TELA  - al_get_bitmap_height(astrMessi)-220, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "ARGENTINA");
        }
        if(personagem_exibido==4){
            al_draw_bitmap(astrDefault, LARGURA_TELA - al_get_bitmap_width(astrDefault)-340,
        ALTURA_TELA  - al_get_bitmap_height(astrDefault)-220, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "DEFAULT");
        }
         al_flip_display();    
    }
     if(telaEspera){
			assertConnection(ServerIP, loginMsg);
			sendMsgToServer((void*)&personagem_exibido, sizeof(personagem_exibido));
			printWaitroom();
			al_flip_display();
		}
		while(telaEspera){
			int ret = recvMsgFromServer(lista_jogadores, DONT_WAIT);
		    if (ret == SERVER_DISCONNECTED) {
		      return -1;
		    } else if (ret != NO_MESSAGE) {
		    	int ready = playersReady(lista_jogadores);
				printf("[[%d]]",ready);
				if(ready == MAX_CLIENTS){
					telaGameplay = 1;
                    telaEspera = 0;
				}
		    }
			while(!al_is_event_queue_empty(fila_eventos)){
	            
	            ALLEGRO_EVENT evento;
	            al_wait_for_event(fila_eventos, &evento);

	            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					
	               fecha();
	            }
	        }
		}
        while(telaGameplay){
	    	int achou=0;
            startTimer();
            al_start_timer(tempo);
            
			while(!al_is_event_queue_empty(fila_eventos)){
				ALLEGRO_EVENT evento;
				al_wait_for_event(fila_eventos, &evento);
				if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
					
                    switch(evento.keyboard.keycode){
						int ret;
						case ALLEGRO_KEY_DOWN:
							lista_jogadores[meu_id].movimento = BAIXO;
							
							if (ret == SERVER_DISCONNECTED) {
								return -1;
							}
							break;
						case ALLEGRO_KEY_LEFT:
							lista_jogadores[meu_id].movimento = ESQUERDA;
							lista_jogadores[meu_id].estado = ESQUERDA;
							
							if (ret == SERVER_DISCONNECTED) {
								return -1;
							}
							break;
						case ALLEGRO_KEY_RIGHT:
							lista_jogadores[meu_id].movimento = DIREITA;
							lista_jogadores[meu_id].estado = DIREITA;
							
							if (ret == SERVER_DISCONNECTED) {
								return -1;
							}
							break;
						case ALLEGRO_KEY_UP:
							lista_jogadores[meu_id].movimento = CIMA;
							
							if (ret == SERVER_DISCONNECTED) {
								return -1;
							}
							break;
						
					}
                    
                    
                    int ret = sendMsgToServer((void *)lista_jogadores, sizeof(Player)*MAX_CLIENTS);
                    
				}

				if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					fecha();
				}
                if(evento.type == ALLEGRO_EVENT_TIMER){
                    int ret;
                    lista_jogadores[meu_id].oxigenio-=50;
                    dropaoxigenio();
                    ret = sendMsgToServer((void *)lista_jogadores, sizeof(Player)*MAX_CLIENTS);
                   
                }
			}
            
            
	        int ret = recvMsgFromServer(lista_jogadores, DONT_WAIT);
		    if (ret == SERVER_DISCONNECTED) {
		      return -1;
		    } else if (ret != NO_MESSAGE) {
		    	printf("Recebeu uma mensagem do servidor!\n");
		    	printPlayer(lista_jogadores[meu_id]);
		    }

			if(strcmp(lista_jogadores[meu_id].login,"")==0){
				
			}
			else if(playersReady(lista_jogadores) == 1){
				
			}
            int index;
                    index = procura(lista_jogadores);
                    if (index != -1){
                        lista_jogadores[index].oxigenio += 50;
                    }
            if(index==-1){
	    	al_draw_bitmap(backgroundGameplay, LARGURA_TELA - al_get_bitmap_width(backgroundGameplay),
            ALTURA_TELA  - al_get_bitmap_height(backgroundGameplay), 0);
            printPlayers(lista_jogadores);
            al_draw_bitmap(oxigenio, (oxygen.x *32) +24, (oxygen.y) *32, 0);
	    	al_flip_display();
	    	al_clear_to_color(al_map_rgb(0, 0, 0));
            FPSLimit();
            }
            else{
            al_draw_bitmap(backgroundGameplay, LARGURA_TELA - al_get_bitmap_width(backgroundGameplay),
            ALTURA_TELA  - al_get_bitmap_height(backgroundGameplay), 0);
            printPlayers(lista_jogadores);
            for(int i=0;i<18;i++){
                for(int j=0;j<25;j++){
                    matriz[i][j]=0;
                }
            }
	    	al_flip_display();
	    	al_clear_to_color(al_map_rgb(0, 0, 0));
            FPSLimit(); 
            }   
			int i;
			for(i=0;i<MAX_CLIENTS;i++){
				lista_jogadores[i].estado = lista_jogadores[i].direcao;
			}
	    	
	    	
               
	    }
     while(tutorial==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        tutorial=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    fecha();
	            }
        }
             al_draw_bitmap(backgroundTutorial, LARGURA_TELA - al_get_bitmap_width(backgroundTutorial),
        ALTURA_TELA  - al_get_bitmap_height(backgroundTutorial), 0);
         
         al_flip_display();    
    }
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(background, LARGURA_TELA - al_get_bitmap_width(background),
        ALTURA_TELA  - al_get_bitmap_height(background), 0);
        if(botaoSair==1){
            al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50,
            ALTURA_TELA - al_get_bitmap_height(botao_sair) - 20, 0);}
        else{
            al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50,
            ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10, 0);
        }
        if(botaoHistoria==1){
        al_draw_bitmap(botao_historia, LARGURA_TELA - al_get_bitmap_width(botao_historia)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_historia)-20, 0);
        }
        else{
            al_draw_bitmap(botao_historia, LARGURA_TELA - al_get_bitmap_width(botao_historia)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_historia)-10, 0);
        }
        if(botaoJogar==1){
        al_draw_bitmap(botao_jogar, LARGURA_TELA - al_get_bitmap_width(botao_jogar)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_jogar)-160, 0);
        }
        else{
            al_draw_bitmap(botao_jogar, LARGURA_TELA - al_get_bitmap_width(botao_jogar)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_jogar)-150, 0);
        }
        if(botaoTutorial==1){
        al_draw_bitmap(botao_tutorial, LARGURA_TELA - al_get_bitmap_width(botao_tutorial)-300,
        ALTURA_TELA  - al_get_bitmap_height(botao_tutorial)-20, 0);
        }
        else{
            al_draw_bitmap(botao_tutorial, LARGURA_TELA - al_get_bitmap_width(botao_tutorial)-300,
        ALTURA_TELA  - al_get_bitmap_height(botao_tutorial)-10, 0);
        }
        
        
        // Atualiza a tela
        al_flip_display();
    }
 
    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(botao_historia);
    al_destroy_bitmap(botao_jogar);
    al_destroy_bitmap(botao_tutorial);
    al_destroy_bitmap(background);
    al_destroy_display(janela);
    al_destroy_font(font);
    al_destroy_event_queue(fila_eventos);
     al_destroy_audio_stream(musica);
    return 0;
}
