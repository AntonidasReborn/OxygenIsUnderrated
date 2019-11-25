#include "ACore.h"


/*
INITIALIZATION OF BASIC CORE MODULES:
--ALLEGRO
--ALLEGRO IMAGE
--ALLEGRO FONTS
--ALLEGRO TTF FONT SUPPORT
--ALLEGRO PRIMITIVES
--EVENT QUEUE
*/
bool coreInit()
{
    //modules and add-ons initialization
	if (!al_init())
    {
        //fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        //fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_init_font_addon())
    {
        //fprintf(stderr, "Falha ao inicializar add-on allegro_font.\n");
        return false;
    }

    if (!al_init_ttf_addon())
    {
        //fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }

    if (!al_init_primitives_addon())
    {
        //fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }
    if(!al_install_audio()){
        printf("Erro na musica3");
        return false;
    }
    if(!al_init_acodec_addon()){
        printf("Erro na musica4");
        return false;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        //fprintf(stderr, "Falha ao criar fila de eventos.\n");
        return false;
    }
    tempo = al_create_timer( 300/ FPS);
    if(!tempo) {
        
        return false;
    }

 	

    return true;
}


//FOR INITIALIZING A WINDOW OF WxH SIZE WITH TEXT "title[]"
bool windowInit(int W, int H, char title[])
{
    //window and event queue creation
    janela = al_create_display(W, H);
    if (!janela)
    {
        //fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
    al_set_window_title(janela, title);

    //registra janela na fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(tempo));

    return true;
}


//FOR INITIALIZING MAIN EXTERNAL INPUTS (KEYBOARD, MOUSE AND CURSOR)
bool inputInit()
{
	/*------------------------------MOUSE--------------------------------*/
	//Inicializa Mouse
	if (!al_install_mouse())
    {
        //fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return false;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        //fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return false;
    }
    /*------------------------------MOUSE--------------------------------*/

    /*------------------------------KEYBOARD------------------------------*/
    if (!al_install_keyboard())
    {
        //fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    /*------------------------------KEYBOARD------------------------------*/


    //Registra mouse e teclado na fila de eventos
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    return true;
}


//FOR READING KEYBOARD INPUT WITH MAX SIZE = LIMIT AND SAVING AT STR[]
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


//FPS CONTROL (FPS IS DEFINED IN ACORE.H)
void startTimer()
{
    startingTime = al_get_time();
}

double getTimer()
{
    return al_get_time() - startingTime;
}

void FPSLimit()
{
    if (getTimer() < 1.0/FPS)
    {
        al_rest((1.0 / FPS) - getTimer());
    }
}


//FOR DEALLOCATING ALL ALLEGRO STUFF
void allegroEnd()
{
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
}


//MODIFY THIS TO LOAD YOUR OWN FONTS (FONT POINTERS ARE DEFINED AT ACORE.H)
bool fontInit()
{
    /*------------------------------FONTE--------------------------------*/
    font = al_load_font("examples/graphicChat/Resource/font/Minecraft.ttf", 68, 0);
    if (!font){
        
        return false;
    }

    return true;
}
bool loadMusic()
{
    
    if (!al_reserve_samples(5)){
       printf("Erro na musica2");
        return false;
    }
    musica = al_load_audio_stream("examples/graphicChat/Resource/Music/Interestelar_music.ogg", 4, 1024);
    if (!musica)
    {
        printf("Erro na musica1");
        return false;
    }
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    //define que o stream vai tocar no modo repeat
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    return true;
}

//MODIFY THIS TO LOAD YOUR OWN GRAPHICS (BITMAP POINTERS ARE DEFINED AT ACORE.H)
bool loadGraphics()
{
    
    telaCreditos = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/Creditos_screen.png");
    if(!telaCreditos){
        return false;
    }
    
    telaDerrota = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/tela_vitoria.png");
    if(!telaDerrota){
        return false;
    }
     telaVitoria = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/tela_derrota.png");
    if(!telaVitoria){
        return false;
    }
    
    
    
    oxigenio = al_load_bitmap("examples/graphicChat/Resource/objects/oxigenio_size-32x32.png");
    if (!oxigenio){
        
        return false;
    }
    
    astrBR = al_load_bitmap("examples/graphicChat/Resource/skins/AstrounautaBR.png");
    if (!astrBR){
        
        return false;
    }
    astrBRR = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/AstrounautaBR_LEFT.png");
    if (!astrBRR){
        
        return false;
    }
    astrBRL = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/AstrounautaBR_LEFT.png");
    if (!astrBRL){
        
        return false;
    }
    astrURSS = al_load_bitmap("examples/graphicChat/Resource/skins/AstrounautinhaURSS.png");
    if (!astrURSS){
        return false;
    }
    astrURSSR = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/AstrounautinhaURSS_RIGHT.png");
    if (!astrURSSR){
        return false;
    }
    astrURSSL = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/AstrounautinhaURSS_LEFT.png");
    if (!astrURSSL){
        return false;
    }
    astrMessi = al_load_bitmap("examples/graphicChat/Resource/skins/AstrounautaARGENTINA.png");
    if (!astrMessi){
        return false;
    }
    astrMessiL = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/AstrounautaARGENTINA_LEFT.png");
    if (!astrMessiL){
        return false;
    }
    astrMessiR = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/AstrounautaARGENTINA_RIGHT.png");
    if (!astrMessiR){
        return false;
    }
    astrDefault = al_load_bitmap("examples/graphicChat/Resource/skins/Astrounautinha.png");
    if (!astrDefault){
        return false;
    }
    astrDefaultR = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/Astrounautinha_RIGHT.png");
    if (!astrDefaultR){
        return false;
    }
    astrDefaultL = al_load_bitmap("examples/graphicChat/Resource/skins/skins_LEFT_and_RIGHT-32x32/Astrounautinha_LEFT.png");
    if (!astrDefaultL){
        return false;
    }
    backgroundGameplay = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/Game_background.png");
    if (!backgroundGameplay){
        return false;
    }
    backgroundCharacter = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/EscolhaPersonagem_background.png");
    if (!backgroundCharacter){
        return false;
    }
    backgroundHistoria = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/Game_Hist.png");
    if (!backgroundHistoria){
        return false;
    }
    backgroundTutorial = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/Game_Tutorial.png");
    if (!backgroundTutorial){
        return false;
    }
    backgroundNave = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/spacebackground_MENU.jpg");
    if (!backgroundNave){
        return false;
    }
    // Alocamos o retângulo central da tela
    background = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/spacebackground_MENU2.jpg");
    if (!background){
        return false;
    }
     backgroundIP = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/DigiteIP_background.png");
    if (!background){
        return false;
    }
    backgroundLogin = al_load_bitmap("examples/graphicChat/Resource/background/Backgrounds_800x600/DigiteLogin_background.png");
    if (!background){
        return false;
    }
 
    // Alocamos o botão para fechar a aplicação
    botao_sair = al_load_bitmap("examples/graphicChat/Resource/objects/botao_SAIR.png");
    if (!botao_sair){
        return false;
    }
    botao_historia = al_load_bitmap("examples/graphicChat/Resource/objects/botao_HISTORIA.png");
    if (!botao_historia){
        return false;
    }
    botao_tutorial = al_load_bitmap("examples/graphicChat/Resource/objects/botao_TUTORIAL.png");
    if (!botao_tutorial){
        return false;
    }
    botao_jogar = al_load_bitmap("examples/graphicChat/Resource/objects/botao_JOGAR.png");
    if (!botao_jogar){
        return false;
    }
    return true;
}