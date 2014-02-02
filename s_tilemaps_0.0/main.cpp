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
    
    Mapa d;
    
    P_Map(0,0);//posicao inicial do mapa na tela quando e desenhado
	T_Tile();//tamanho do tile padrao(16x16)  
    
    d.C_Tiles(till_0,Tile_Set0,16,16);//carega o tile_set

    

	while (!key[KEY_ESC]) 
    {clear_to_color(Buffer, makecol(30,30,100));//altera a cor de fundo do Buffer
     Longit_Lat();//latitude e longitude do mapa em relacao ao ponto 0x0 da tela
               
		  
		  
		//---criar uma funcao chamada fase'x' com o modelo que esta representado abaixo---  
		  //d.Fill_Map(till_0,256,0,0,200,60,Buffer,map_pf,X_MAP,Y_MAP);//plano de fundo do senario
          //d.Fill_Map(till_0,256,map_1,200,60,Buffer);//mapa dos objetos atras dos pesonagem 1
          //d.Fill_Map(till_0,256,map_1f,200,60,Buffer);//mapa dos objetos atras dos pesonagem 2
		  //-----os pesonagens devem ser postos aqui-----
          //d.Fill_Map(till_0,256,0,0,200,60,Buffer,map_1q,X_MAP,Y_MAP);//mapa dos objetos afente dos pesonagem 
	
	      d.Fill_Map(till_0,256,map_1,200,60,Buffer);
	
		  d.Scoll_Map(640,480,180,60,10,Buffer); //tacha de movimento do mapa   
		  
		  if(key[KEY_T])//testa o tile_set caregado
             d.Tile_test(till_0,16,16,Buffer);
  
		  
	  //vsync();//aguarda a sincronizacao vertical
	 // rest(80);//espera 'x' milisegundos	  
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
