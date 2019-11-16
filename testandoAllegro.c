// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
// Atributos da tela
#define LARGURA_TELA 800
#define ALTURA_TELA 600
 
void error_msg(char *text){
	al_show_native_message_box(NULL,"ERRO",
		"Ocorreu o seguinte erro e o programa sera finalizado:",
		text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}
 
int main(void){
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *botao_jogar=NULL,*botao_historia=NULL,*botao_tutorial=NULL,*area_central=0;
    ALLEGRO_BITMAP *background =NULL,*backgroundHistoria=NULL;
    ALLEGRO_BITMAP *imagem =NULL;
    ALLEGRO_AUDIO_STREAM *musica =NULL;
    // Flag que condicionará nosso looping
    int sair = 0,historia = 0;
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
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela){
        error_msg("Falha ao criar janela");
        return -1;
    }
    
    // Configura o título da janela
    al_set_window_title(janela, "Rotinas de Mouse");
 
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse()){
        error_msg("Falha ao inicializar o mouse");
        al_destroy_display(janela);
        return -1;
    }
 
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        error_msg("Falha ao atribuir ponteiro do mouse");
        al_destroy_display(janela);
        return -1;
    }
    backgroundHistoria = al_load_bitmap("/home/flavinl2/Desktop/OxygenIsUnderrated/Resource/background/Backgrounds_800x600/spacebackground_MENU.jpg");
    if (!backgroundHistoria){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
    // Alocamos o retângulo central da tela
    background = al_load_bitmap("/home/flavinl2/Desktop/OxygenIsUnderrated/Resource/background/Backgrounds_800x600/spacebackground_MENU2.jpg");
    if (!background){
        error_msg("Falha ao criar bitmap");
        al_destroy_display(janela);
        return -1;
    }
 
    // Alocamos o botão para fechar a aplicação
    botao_sair = al_load_bitmap("/home/flavinl2/Desktop/OxygenIsUnderrated/Resource/objects/botao_SAIR.png");
    if (!botao_sair){
        error_msg("Falha ao criar botão de saída");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    botao_historia = al_load_bitmap("/home/flavinl2/Desktop/OxygenIsUnderrated/Resource/objects/botao_HISTORIA.png");
    if (!botao_historia){
        error_msg("Falha ao criar botao_historia");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    botao_tutorial = al_load_bitmap("/home/flavinl2/Desktop/OxygenIsUnderrated/Resource/objects/botao_TUTORIAL.png");
    if (!botao_tutorial){
        error_msg("Falha ao criar botao_tutorial");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    botao_jogar = al_load_bitmap("/home/flavinl2/Desktop/OxygenIsUnderrated/Resource/objects/botao_JOGAR.png");
    if (!botao_jogar){
        error_msg("Falha ao criar botao_jogar");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
    musica = al_load_audio_stream("/home/flavinl2/Downloads/musica.ogg", 4, 1024);
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
            }
        }   
 
        // Limpamos a tela
        
        // Desenhamos os retângulos na tela
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
    al_destroy_event_queue(fila_eventos);
     al_destroy_audio_stream(musica);
    return 0;
}