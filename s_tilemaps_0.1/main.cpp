#include <iostream.h>
#include <allegro.h>
#include <alpng.h>
#include <alfont.h>
#include <gstream.h>



#include "f_mapa.h"
#include "mapas.h"
#include "pley.h"

#define DEGREES(x) int((x)/360.0*0xFFFFFF)



void highcolor_fade_in(BITMAP *bmp_orig, int speed);
void highcolor_fade_out(int speed);



void init();
void deinit();

int main() {
	init();
	
	show_os_cursor(MOUSE_CURSOR_ARROW);//esibe o cursor do 'OPERACIONAL' sobre a tela 
	
	BITMAP *Buffer = create_bitmap(SCREEN_WIDTH ,SCREEN_HEIGHT);
	
	BITMAP *Tile_Set0 = load_bitmap("t_map.bmp", NULL);
    BITMAP *till_0[256];//imagens do tileset_0
    
    BITMAP *Tile_Set00 = load_bitmap("bgs.bmp", NULL);
    BITMAP *till_00[320];//imagens do tileset_0
    
    Mapa d;
    
    P_Map(0,0);//posicao inicial do mapa na tela quando e desenhado
	T_Tile();//tamanho do tile padrao(16x16)  
    
    d.C_Tiles(till_0,Tile_Set0,16,16);//carega o tile_set
    d.C_Tiles(till_00,Tile_Set00,16,20);//carega o tile_set


int g=10,dc=10;
int xc=20*Tx_Tile,yc=15*Ty_Tile;

int r=0;


	while (!key[KEY_ESC]) 
    {clear_to_color(Buffer, makecol(30,30,100));//altera a cor de fundo do Buffer
     Longit_Lat();//latitude e longitude do mapa em relacao ao ponto 0x0 da tela

		  
		//---criar uma funcao chamada fase'x' com o modelo que esta representado abaixo---  
		  d.Fill_Map(till_00,320,map_pf1,200,60,Buffer,0.8,1);//plano de fundo do senario 1
		  d.Fill_Map(till_00,320,map_pf2,200,60,Buffer,0.8,0.7);//plano de fundo do senario 2
          d.Fill_Map(till_0,256,map_1,200,60,Buffer,1,1);//mapa dos objetos atras dos pesonagens 1
          d.Fill_Map(till_0,256,map_1f,200,60,Buffer);//mapa dos objetos atras dos pesonagens 2
		  //-----os pesonagens devem ser postos aqui-----
          //d.Fill_Map(till_0,256,0,0,200,60,Buffer,map_1q,X_MAP,Y_MAP);//mapa dos objetos afente dos pesonagem 
	      r=d.c(64,64,xc,yc,map_1,200,60,Buffer);//--teste de colisoes
	
		  d.Scoll_MapD(200,60,10,Buffer); //tacha de movimento do mapa   
		  

		 // obijeto de test-----------
		  set_trans_blender(0, 0, 0, 100);    
          drawing_mode(DRAW_MODE_TRANS,  0,0, 0);
		  rect(Buffer, xc,yc, xc+64, yc+64, makecol(0, 0, 100));
		  rectfill(Buffer, xc,yc, xc+64, yc+64, makecol(0, 0, 255));
		  drawing_mode(DRAW_MODE_SOLID, 0, 0, 0); 
		  
		if(mouse_b & 1)
		  xc=mouse_x-8,yc=mouse_y-8;
		  //d.c(16,16,xc,yc,map_1,200,60,Buffer,4);
		  cout<<xc<<" "<<yc<<"\n";
  
  
  		 
		 if(key[KEY_UP])//controle do objeto
		        {//yc+=g;
                 yc-=12;
                 }       
		   if(key[KEY_DOWN] )
           	   {yc+=0;
                 // yc+=g;
                  }
          else	   
              yc+=g;
		     if(key[KEY_LEFT]) 
		        {xc-=8;}
	         if(key[KEY_RIGHT] ) 
                {xc+=8;}

  
        if(key[KEY_G])
		  yc+=g;//gravidade
		else
          yc+=0;

		  
		  if(yc>60*Ty_Tile)
		     yc=100;
		     
		   if(key[KEY_Z] && r==1)//r=colisao
              yc-=48;  
           if(key[KEY_X] && r==1)
              yc-=64;    
		  
		  
		  if(key[KEY_T])//testa o tile_set caregado
             d.Tile_test(till_0,16,16,Buffer);
  
		  
	  vsync();//aguarda a sincronizacao vertical
	  rest(80);//espera 'x' milisegundos	  
	  blit(Buffer,screen,0,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);//fixa o Buffer no screen	  
	  clear(Buffer);//limpa o Buffer
	}

    //distruindo bitmaps--------------------------------------------------------
    destroy_bitmap(Tile_Set0);
    for(int i=0;i<256;i++)
	     destroy_bitmap(till_0[i]);
   
    destroy_bitmap(Buffer);//destroi o Biffer da memoria --obrigatorio--
    //--------------------------------------------------------------------------
    
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	alpng_init();
	alfont_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH ,SCREEN_HEIGHT, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	/* set the window title */
    set_window_title("Title");


	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	alfont_exit(); 
    allegro_exit();
	/* add other deinitializations here */
}
