
//#include <iostream.h>
#include <allegro.h>
#include <alpng.h>
#include <algif.h>
#include <alfont.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
//#include <fstream.h>


void highcolor_fade_in(BITMAP *bmp_orig, int speed);
void highcolor_fade_out(int speed);

//void tick(void)
//{
//   t++;
//}
//END_OF_FUNCTION(tick);

#define DEGREES(x) int((x)/360.0*0xFFFFFF)

#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480

#include "mapas.h"
#include "f_mapa.h"
#include "pley.h"

/* Checa se a versao atual eh compativel com a Allegro 4.2.0 */
#if (MAKE_VERSION(4, 2, 0) <= MAKE_VERSION(ALLEGRO_VERSION, ALLEGRO_SUB_VERSION, ALLEGRO_WIP_VERSION))
/* Compatibilidade com Allegro 4.2.0 */
#else //allegro_message("erro");
/* Work-around(??) */
#endif

//typedef struct RGB {    
//    unsigned char r, g, b;
//  } RGB; 


static volatile int ticks = 0;
static void ticker(void)
{
    ticks++;
}

void anim_gif(char const *name,int fips_x,int P_x,int P_y){
    
//clear_to_color(screen, makecol(30,30,100));
	BITMAP **frames;
    int *durations;
    int i, n;
   // char const *name = "p.gif";

    n = algif_load_animation (name, &frames, &durations);

    install_int_ex(ticker, BPS_TO_TIMER(fips_x));

     int e;

        int y=0;
        for (i = 0; i < n; i++)
        { 
            
            draw_sprite(screen, frames[i], P_x, P_y);
            e = ticks + durations[i];

           while (ticks < e)//&& !keypressed ())
            {
                rest (1);
                //if (keypressed ())
                //break;
                
                //textprintf_ex(screen, font, 0, frames[i]->h + 4,
//                    makecol(255, 255, 255), makecol(255, 0, 255), "%-4d: %-4d",
//                    i, e - ticks);                   
            }
        } 
}








    int SCREEN_WIDTH_Z=320;
    int SCREEN_HEIGHT_Z=240;




void init();
void deinit();

int main(int argc, char **argv) {
	init();
	

	
    

        
    
	BITMAP *Buffer = create_bitmap(SCREEN_WIDTH ,SCREEN_HEIGHT);
	    
    
    BITMAP *Tile_Set0 = load_bitmap("tiles0.bmp", NULL);
    
    BITMAP *p = load_bitmap("p1.bmp", NULL);
    BITMAP *pt = load_bitmap("pt.bmp", NULL);
    
     BITMAP *iso = load_bitmap("isometric_tileset.bmp", NULL);
    
    ALFONT_FONT *fnt = alfont_load_font("dr.ttf");
    alfont_set_font_size(fnt, 40);
    
    BITMAP *png = load_png("img.png", NULL);
    
    Play P1;
    
    //set_window_title("Allegro comanda!");
    
//const int ano = ALLEGRO_DATE / 10000;
//const int mes = (ALLEGRO_DATE / 100) % 100;
//const int dia = ALLEGRO_DATE % 100;
//
//allegro_message("Ano %d, mes %d, dia %d\n",ano, mes, dia);
//    
    
//descobre a resolucao da tela    
// if (get_desktop_resolution(&largura, &comprimento) == 0) {
/* Got the resolution correctly */
//}

    
    Fill_Mapa d,f;
    
    BITMAP *till_0[400];//imagens do tileset_0

    P_map(-48,0);//posicao do mapa na tela quando e desenhado
	T_Tile();//tamanho do tile padrao(16x16)  


    set_mouse_sprite(pt);//mause pesonalisado
    //show_mouse(screen);//esibe o mause
    //show_os_cursor(MOUSE_CURSOR_ARROW);//esibe o cursor do 'OPERACIONAL' sobre a tela --//MOUSE_CURSOR_ARROW

    
    
    //vmouse_x;
    //mouse_y;
    //mouse_b;
    //mouse_pos;
     //set_mouse_sprite();
     //set_mouse_sprite_focus(10,10);
     //void set_mouse_sprite_focus(int x, int y); //muda o ponto de referencia do mause
    //clear_to_color(BITMAP *bitmap, int color); 
  
	  	  d.C_Tiles(till_0,20,20,400,Tile_Set0,Buffer);//carega o tile_set

        BITMAP *Buf = create_bitmap(SCREEN_WIDTH ,SCREEN_HEIGHT);
 
        BITMAP *is=create_bitmap(64,128);
        blit(iso,is,192,0,0,0,192,128);
        
        //anim_gif("p.gif",100,0,0); 
         int x=0;
 
	while (!key[KEY_ESC]) {
              clear(Buffer);
       // clear_keybuf();//apaga todas as teclas que foran rejistradas durante uma volta do laco
		    //clear_to_color(screen, makecol(30,30,100));
		//----------------------------------------------------------------------	  
		 if(key[KEY_V]){anim_gif("p.gif",100,0,0);}     	  
               
                
		  Longit_Lat();//latitude e longitude do mapa em relacao ao ponto 0x0 da tela
          
		  d.Imp_Map(till_0,400,0,0,60,32,Buffer,map_1f,X_MAP*0.2,Y_MAP*0.2);//plano de fundo//'X_MAP*0.2' e 'Y_MAP*0.2' taixa de delocamento do mapa
          
		  d.Imp_Map(till_0,400,0,0,60,32,Buffer,map_1,X_MAP,Y_MAP);//mapa dos objetos a tras do pesonagem
          
	     
          
	 
		  P1.Personagen(Buffer,p);
		  P1.Mov_Play(); 
		  //gravidade(4);       
		  
		  //d.Imp_Map(till_0,400,16,16,0,0,60,32,Buffer,map_1,X_MAP,Y_MAP);//mapa dos objetos a frente do pesonagem
          
		  d.Scoll_Map(640,480,58,32); //tacha de movimento do mapa   
		  
		  if(key[KEY_T])//testa o tile_set caregado
             d.Tile_test(till_0,20,20,Buffer);
		  
		  if(key[KEY_S]){//sauva um bitmap do estado atual da tela
		            BITMAP *bmp;
                    get_palette(default_palette);
                    bmp = create_sub_bitmap(screen, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT);
                    save_bmp("pantalla.bmp", bmp, default_palette); 
                    destroy_bitmap(bmp);   
                    }
                    
          if(key[KEY_L]){//sauva um bitmap do estado atual da tela
                    get_palette(default_palette);
                    save_bmp("pantalla.bmp", Buffer, default_palette);    
                    }          
                    
       if(key[KEY_G]){            
       textprintf_ex(screen, font, 0, 0, makecol(255, 255, 255), -1, "s istc"); 
       textprintf_centre_ex(screen, font, 80, 100, makecol(255, 255, 255), -1, "sistc");
       textprintf_right_ex(screen, font, 80, 40, makecol(255, 255, 255), -1, "sistc"); 

       textout_ex(screen, font, "textout", 0, 60, makecol(255, 0, 0), -1); 
       textout_centre_ex(screen, font, "textout", 80 / 2, 80, makecol(255, 0, 0), -1); 
       textout_right_ex(screen, font, "textout", 80, 10, makecol(255, 0, 0), -1);
       }
		  
		  
  if(key[KEY_F]){
  ALFONT_FONT *user_font; 
  user_font = alfont_load_font("C:\\Windows\\Fonts\\arial.ttf"); 
  alfont_set_font_size(user_font, 100); 
 
  //alfont_textprintf(Buffer, user_font, 0, 0, makecol(255, 255, 255), "Test 1"); 

  alfont_textprintf_aa_ex(Buffer, user_font, 10, 10, makecol(255, 255, 255), -1, "Hello World!");
 //alfont_textout_ex(Buffer, user_font,  "Hello World!", 10, 60, makecol(255, 255, 255), -1);
 //alfont_textout_centre_ex(Buffer, user_font, "Hello World!", 10, 90, makecol(255, 255, 255), -1);
 //alfont_textprintf_ex(Buffer, user_font, 10, 130, makecol(255, 255, 255), -1, "Hello World!%d", 32);
 //alfont_textprintf_centre_ex(Buffer, user_font, 10, 160, makecol(255, 255, 255), -1,"Hello World!%d", 32);
 
 //alfont_text_height(user_font);
 //alfont_text_length(user_font, "dgfdgfgdf");
  
  readkey(); 
  alfont_destroy_font(user_font); 
  }
  
  
  
    if(key[KEY_U]){
  putpixel(screen, 10, 30, makecol(255, 255, 255));//macht einen Punkt 
   vline(screen, 30, 80, 300, makecol(0, 255, 0));//senkrechte Linie 
   hline(screen, 40, 20, 400, makecol(0, 0, 255));//waagrechte Linie 
   line(screen, 0, 0, 640, 480, makecol(255, 0, 0)); //Linie 
   triangle(screen, 0, 400, 0, 450, 100, 450, makecol(255, 0, 255));//gefülltes Dreieck 
   rect(screen, 100, 200, 200, 250, makecol(255, 255, 0));//leeres Viereck 
   rectfill(screen, 125, 210, 175, 240, makecol(255, 255, 0));//gefülltes Viereck 
   circle(screen, 500, 400, 50, makecol(255, 0, 0)); //leerer Kreis 
   circlefill(screen, 500, 400, 25, makecol(255, 255, 255));//gefüllter Kreis 
}
  
  //----- relogio -----------------------------------------------------------
//       int h,m,s;
//       
//       time_t tempo;
//       struct tm *tm;
//
//       tempo = time(NULL);
//       tm = localtime( &tempo);
//      
//       printf("\n %d:%d:%d", tm->tm_hour, tm->tm_min, tm->tm_sec);
//       //" --RELOGIO-- "allegro
//        h=tm->tm_hour;
//        m=tm->tm_min;
//        s=tm->tm_sec;
//        //cout<<" test";
//        
//        if(h>12)
//           h=h%12;
//        if(h<10)   
//           alfont_textprintf_aa_ex(Buffer, a, 10, 300, 0x00FF00, -1, "\n0%d:", h);
//        else  
//           alfont_textprintf_aa_ex(Buffer, a, 10, 300, 0x00FF00, -1, "\n%d:", h);    
//        if(m<10)   
//           alfont_textprintf_aa_ex(Buffer, a, 200, 300, 0x00FF00, -1, "0%d:", m);
//        else  
//           alfont_textprintf_aa_ex(Buffer, a, 200, 300, 0x00FF00, -1, "%d:", m);        
//        if(s<10)   
//           alfont_textprintf_aa_ex(Buffer, a, 320, 300, 0x00FF00, -1, "0%d", s);
//        else  
//           alfont_textprintf_aa_ex(Buffer, a, 320, 300, 0x00FF00, -1, "%d", s);     
       //-----------------------------------------------------------------------

  
  
    if(key[KEY_P]){
    set_alpha_blender();
    draw_trans_sprite(Buffer, png, 0, 0);
    }

  
        //----------------------------------------------------------------------  
		
		 EnqPlay_Scrull(Buffer,makecol(255,0,0),208,0,480,448,0,480,0,160,640,0,448,640,1);
		 
		 textprintf_ex(Buffer,font,100,100,makecol(0,255,0),-1,"x_Mi: %d /y_Mi: %d",X_MAP,Y_MAP);
		 textprintf_ex(Buffer,font,100,120,makecol(0,255,0),-1,"Lon_Xi: %d /Lon_Yi: %d",Lon_Xi_MAP,Lon_Yi_MAP); 
		  textprintf_ex(Buffer,font,100,140,makecol(0,255,0),-1,"Lon_Xf: %d /Lon_Yf: %d",Lon_Xf_MAP,Lon_Yf_MAP); 
         //textprintf_ex(Buffer,font,100,140,makecol(0,255,0),-1,"PM_X: %d /PM_Y: %d",	mouse_x,mouse_y); 
		  //alfont_textprintf_ex(Buffer, fnt, 300, 90, makecol(255,0,0), -1, "Mario!");
		  //alfont_textprintf_centre_ex(Buffer, fnt, 300, 150, makecol(255,0,0), -1, "Mario!");
	
		

		//position_mouse(300,100);
        
       //textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), makecol(0, 0, 0), "Hallo Welt!"); 
        
        //acquire_screen()//"captura" e libera atela
        //release_screen()
        
    set_trans_blender(0, 0, 0, 100);    
     drawing_mode(DRAW_MODE_TRANS,  0,0, 0);
     
       //draw_sprite(Buffer, is, mouse_x-32,mouse_y-112);
       
       
       //masked_blit(Buffer, screen, ...);
       
       
        draw_trans_sprite(Buffer, is,  mouse_x-32,mouse_y-112);
         draw_sprite(Buffer, pt, mouse_x,mouse_y);

      // circlefill(Buffer, mouse_x-30, mouse_y-30, 30, makecol(255, 255, 255));
    drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
    
     //draw_sprite(Buffer, pt, mouse_x,mouse_y);
    
    
     //  vsync();//aguarda a sincronizacao vertical

        
        //rotate_sprite(Buffer,Buffer,0,0,DEGREES(450));
		
	//muda a escala da a imagem
	//stretch_blit(Buffer,screen,0,0,SCREEN_WIDTH ,SCREEN_HEIGHT,0,0,SCREEN_WIDTH_Z ,SCREEN_HEIGHT_Z);

 
// set_trans_blender(0, 0, 0, 128);
// drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
// circlefill(Buffer, 160, 100, 80, makecol(0, 255, 0));
// circlefill(Buffer, 220, 200, 80, makecol(0, 255, 255));
// circlefill(Buffer, 100, 200, 80, makecol(0, 0, 255));
// drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
	    
	    
	    
        rest(80);//paralisa o programa por 'x' mile segundos   
        //show_mouse(Buffer);//mostra o malse na tela    
        blit(Buffer,screen,0,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);//fixa o Buffer no screen
        //draw_sprite(screen,Buffer, 0,0);
		//clear(Buffer); 
		
		
	
	}
	highcolor_fade_out(10);// cria efeito de desaparecimento
	
	
	
	
 	alfont_destroy_font(fnt);
    destroy_bitmap(Tile_Set0);
  
    for(int i=0;i<400;i++)
	     destroy_bitmap(till_0[i]);
   
    destroy_bitmap(Buffer);
    
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
    alfont_init();
    algif_init ();


	depth = desktop_color_depth();
//	if (depth == 0) depth = 32;
//	set_color_depth(depth);
	
	if ((depth = desktop_color_depth()) != 0) //usa a profundidade de cor do dekstop
         set_color_depth(depth);
         
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);//GFX_AUTODETECT//GFX_AUTODETECT_WINDOWED//GFX_AUTODETECT_FULLSCREEN
	if (res != 0) {//GFX_SAFE
		allegro_message(allegro_error);
        		exit(-1);	
	}

	install_timer();
	install_keyboard();
	install_mouse();
	set_display_switch_mode(SWITCH_BACKGROUND);
	/* add other initializations here */
}


void deinit() {
    alfont_exit();
	clear_keybuf();
	/* add other deinitializations here */
}





void processa_teclado(int* x, int* y) {
      if (key[KEY_UP]) {
			*y = *y - 1;
	    } else if (key[KEY_DOWN]){
			*y = *y + 1;
	    } else if (key[KEY_RIGHT]){
			*x = *x + 1;
	    } else if (key[KEY_LEFT]){
			*x = *x - 1;
	    }
	 }











void inits()// resolucao
{
int i;
   int c = GFX_AUTODETECT;
   int w, h, bpp;

   allegro_init();
   install_keyboard();
   install_mouse();
   install_timer();

   /* set the graphics mode */
   if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
   }
   set_palette(desktop_palette);

   w = SCREEN_W;
   h = SCREEN_H;
   bpp = bitmap_color_depth(screen);
   if (!gfx_mode_select_ex(&c, &w, &h, &bpp)) {
      allegro_exit();
   }

   set_color_depth(bpp);

   if (set_gfx_mode(c, w, h, 0, 0) != 0) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error setting graphics mode\n%s\n", allegro_error);
   }    
}














//------------------------------------------------------------------------------
//rotinas de colisao
struct RETANGULO
{
    int x, y; //posição x e y na tela

    int l, a; //largura e altura do retângulo
};

bool Colisao(RETANGULO &obj1, RETANGULO &obj2)
{
    if (obj1.x > obj2.x + obj2.l) return false; //obj1 está a direita de obj2

    if (obj1.y > obj2.y + obj2.a) return false; //obj1 está abaixo de obj2

    if (obj1.x + obj1.l < obj2.x) return false; //obj1 está a esquerda de obj2

    if (obj1.y + obj1.a < obj2.y) return false; //obj1 está acima de obj2

    return true; //existe colisão, ou seja, obj1 está tocando em obj2
}

struct CIRCULO

{
    int x, y; //posição x e y na tela
    
    int raio; //raio da circunferência
};



bool Colisao(CIRCULO &obj1, CIRCULO &obj2)
{
    float qx, qy, qr; //para guardar o quadrado de x, y e raio

    qx = pow(obj2.x - obj1.x, 2); //quadrado da distância em x

    qy = pow(obj2.y - obj1.y, 2); //quadrado da distância em y

    qr = pow(obj1.raio + obj2.raio, 2); //quadrado da soma dos raios

    if (qx + qy <= qr)

        return true; //existe colisão

    return false;
}
//------------------------------------------------------------------------------























void highcolor_fade_in(BITMAP *bmp_orig, int speed)
{
   BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;

        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    } 

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}

void highcolor_fade_out(int speed)
{
    BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;

            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}

















 volatile int close_button_pressed = FALSE;

//void close_button_handler(void)
//{
//close_button_pressed = TRUE;
//}
//END_OF_FUNCTION(close_button_handler)
//
//
//allegro_init();
//LOCK_FUNCTION(close_button_handler);
//set_close_button_callback(close_button_handler);
//
//
//while (!close_button_pressed)
//do_stuff();







//------------------------------------------------------------------------------
void onWalk()
{
int inipos_x, inipos_y, final_x, final_y, walk_x, walk_y;
inipos_x = 48;
inipos_y = 422;
final_x = 90;
final_y = 108;
walk_x = 0;
walk_y = 0;
BITMAP *hero = load_bitmap("p1.bmp", NULL);
draw_sprite(screen, hero, inipos_x, inipos_y);
while (key[KEY_UP])
{
if (walk_y == 0)
{
walk_y = inipos_y;
}
walk_y -= 1;
walk_x = inipos_x;
clear(screen);
BITMAP *hero = load_bitmap("p1.bmp", NULL);
draw_sprite(screen, hero, walk_x, walk_y);
}
clear(screen);
draw_sprite(screen, hero, walk_x, walk_y);
while (key[KEY_DOWN])
{
if (walk_y == 0)
{
walk_y = inipos_y;
}
walk_y += 1;
walk_x = inipos_x;
clear(screen);
BITMAP *hero = load_bitmap("p1.bmp", NULL);
draw_sprite(screen, hero, walk_x, walk_y);
}
clear(screen);
while (key[KEY_LEFT])
{
if (walk_x == 0)
{
walk_x = inipos_x;
}
walk_x -= 1;
walk_y = inipos_y;
clear(screen);
BITMAP *hero = load_bitmap("p1.bmp", NULL);
draw_sprite(screen, hero, walk_x, walk_y);
}
clear(screen);
while (key[KEY_RIGHT])
{
if (walk_x == 0)
{
walk_x = inipos_x;
}
walk_x += 1;
walk_x = inipos_x;
clear(screen);
BITMAP *hero = load_bitmap("p1.bmp", NULL);
draw_sprite(screen, hero, walk_x, walk_y);
}
clear(screen);
}
















