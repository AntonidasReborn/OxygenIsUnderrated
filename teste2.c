// Os arquivos de cabeçalho

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
// Atributos da tela
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define BUFFER_SIZE 100
#define ASTRBR 1
#define ASTRURSS 2
#define ASTRMESSI 3
#define ASTRDEFAULT 4
#define LOGIN_MAX_SIZE 13

 void readInput(ALLEGRO_EVENT event, char str[], int limit)
{
    if (event.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(str) <= limit) 
        {
            char temp[] = {event.keyboard.unichar, '\0'};
            if (event.keyboard.unichar == ' ')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= '!' &&
                     event.keyboard.unichar <= '?')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'A' &&
                     event.keyboard.unichar <= 'Z')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'a' &&
                     event.keyboard.unichar <= 'z')
            {
                strcat(str, temp);
            }
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0)
        {
            str[strlen(str) - 1] = '\0';
        }
    }
}
void error_msg(char *text){
	al_show_native_message_box(NULL,"ERRO",
		"Ocorreu o seguinte erro e o programa sera finalizado:",
		text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}
 
int main(void){
    char ServerIP[30] = {"127.0.0.1"};
    //Salva o login
    char loginMsg[BUFFER_SIZE]={0};
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *botao_jogar=NULL,*botao_historia=NULL,*botao_tutorial=NULL,*area_central=0;
    ALLEGRO_BITMAP *background =NULL,*backgroundHistoria=NULL,*backgroundTutorial=NULL,*backgroundIP=NULL,*backgroundLogin=NULL,*backgroundCharacter=NULL;
    ALLEGRO_BITMAP *imagem =NULL;
    ALLEGRO_BITMAP *astrURSS=NULL,*astrBR=NULL,*astrMessi=NULL,*astrDefault=NULL;
    ALLEGRO_AUDIO_STREAM *musica =NULL;
    // Flag que condicionará nosso looping
    int sair = 0,historia = 0,tutorial=0,jogar=0,telaIp=0,telaLogin=0,telaCharacter=0;
    if(!al_install_audio()){
        error_msg("Falha ao inicializar o audio");
        return 0;
    }
 
    //addon que da suporte as extensoes de audio
    if(!al_init_acodec_addon()){
        error_msg("Falha ao inicializar o codec de audio");
        return 0;
    }
    if (!al_init()){
        error_msg("Falha ao inicializar a Allegro");
        return -1;
    }
    if (!al_init_image_addon()){
        error_msg("Falha ao inicializar imagem");
        return -1;
    }
    if (!al_reserve_samples(5)){
        error_msg("Falha ao reservar amostrar de audio");
        return 0;
    }
    
    al_init_font_addon();

    if (!al_init_ttf_addon()){
        error_msg("Falha ao inicializar add-on allegro_ttf");
        return -1;
    }
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela){
        error_msg("Falha ao criar janela");
        return -1;
    }
    font = al_load_font("Resource/font/Minecraft.ttf", 68, 0);
    if (!font){
        al_destroy_display(janela);
        error_msg("Falha ao carregar fonte");
        return -1;
    }
    
    // Configura o título da janela
    al_set_window_title(janela, "Oxygen Is Underrated");
 
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse()){
        error_msg("Falha ao inicializar o mouse");
        al_destroy_display(janela);
        return -1;
    }
    if (!al_install_keyboard())
  {
    error_msg("Falha ao inicializar o teclado.\n");
    al_destroy_display(janela);
    return -1;
  }
 
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        error_msg("Falha ao atribuir ponteiro do mouse");
        al_destroy_display(janela);
        return -1;
    }
    astrBR = al_load_bitmap("Resource/skins/AstrounautaBR.png");
    if (!astrBR){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    astrURSS = al_load_bitmap("Resource/skins/AstrounautinhaURSS.png");
    if (!astrURSS){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    astrMessi = al_load_bitmap("Resource/skins/AstrounautaARGENTINA.png");
    if (!astrMessi){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    astrDefault = al_load_bitmap("Resource/skins/Astrounautinha.png");
    if (!astrDefault){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    
    backgroundCharacter = al_load_bitmap("Resource/background/Backgrounds_800x600/EscolhaPersonagem_background.png");
    if (!backgroundCharacter){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    backgroundHistoria = al_load_bitmap("Resource/background/Backgrounds_800x600/Game_Hist.png");
    if (!backgroundHistoria){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    backgroundTutorial = al_load_bitmap("Resource/background/Backgrounds_800x600/Game_Tutorial.png");
    if (!backgroundTutorial){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    // Alocamos o retângulo central da tela
    background = al_load_bitmap("Resource/background/Backgrounds_800x600/spacebackground_MENU2.jpg");
    if (!background){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
     backgroundIP = al_load_bitmap("Resource/background/Backgrounds_800x600/DigiteIP_background.png");
    if (!background){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    backgroundLogin = al_load_bitmap("Resource/background/Backgrounds_800x600/DigiteLogin_background.png");
    if (!background){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
 
    // Alocamos o botão para fechar a aplicação
    botao_sair = al_load_bitmap("Resource/objects/botao_SAIR.png");
    if (!botao_sair){
        error_msg("Falha ao criar botão de saída");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    botao_historia = al_load_bitmap("Resource/objects/botao_HISTORIA.png");
    if (!botao_historia){
        error_msg("Falha ao criar botao_historia");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    botao_tutorial = al_load_bitmap("Resource/objects/botao_TUTORIAL.png");
    if (!botao_tutorial){
        error_msg("Falha ao criar botao_tutorial");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    botao_jogar = al_load_bitmap("Resource/objects/botao_JOGAR.png");
    if (!botao_jogar){
        error_msg("Falha ao criar botao_jogar");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    musica = al_load_audio_stream("Resource/Music/Interestelar_music.ogg", 4, 1024);
    if (!musica)
    {
        error_msg( "Audio nao carregado" );
        
        
        return 0;
    }
    if (!al_reserve_samples(5)){
        error_msg("Falha ao reservar amostrar de audio");
        return 0;
    }

    //liga o stream no mixer
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    fila_eventos = al_create_event_queue();
    if (!fila_eventos){
        error_msg("Falha ao inicializar o fila de eventos");
        al_destroy_display(janela);
        return -1;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
 
    // Flag indicando se o mouse está sobre o retângulo central
    int botaoSair = 0,botaoJogar = 0,botaoTutorial = 0,botaoHistoria = 0;
    while (!sair){        // Verificamos se há eventos na fila
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
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
             readInput(evento,ServerIP,20);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        telaLogin=1;
                        jogar=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
	                sair=1;
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
	                sair=1;
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
        }
             al_draw_bitmap(backgroundHistoria, LARGURA_TELA - al_get_bitmap_width(backgroundHistoria),
        ALTURA_TELA  - al_get_bitmap_height(backgroundHistoria), 0);
        
         al_flip_display();    
    }
    int personagem_exibido = ASTRBR;
     while(telaCharacter==1){
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
                    
                        
                }
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