#include <allegro.h>
#include <alfont.h>
#include <stdlib.h>


#define DEGREES(x) int((x)/360.0*0xFFFFFF)

#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480

#include "mapas.h"
#include "f_mapa.h"
#include "pley.h"




    int SCREEN_WIDTH_Z=640;
    int SCREEN_HEIGHT_Z=480;


void init();
void deinit();


int main() {
	init();

    BITMAP *Buffer = create_bitmap(SCREEN_WIDTH ,SCREEN_HEIGHT);
    BITMAP *Tile_Set0 = load_bitmap("tiles0.bmp", NULL);
    
    BITMAP *p = load_bitmap("p1.bmp", NULL);
    
    
    ALFONT_FONT *fnt = alfont_load_font("dr.ttf");
    alfont_set_font_size(fnt, 40);
    
    Play P1;
    
    Fill_Mapa d,f;
    
    BITMAP *till_0[400];//imagens do tileset_0

  
 
    P_map(-48,0);//posicao do mapa na tela quando e desenhado
	T_Tile();//tamanho do tile padrao(16x16)  


  
	  	  d.C_Tiles(till_0,20,20,400,Tile_Set0,Buffer);//carega o tile_set
 
	while (!key[KEY_ESC]) {
		
		
		//----------------------------------------------------------------------
		 		  
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
		  
        //----------------------------------------------------------------------  
		
		 EnqPlay_Scrull(Buffer,makecol(255,0,0),208,0,480,448,0,480,0,160,640,0,448,640,1);
		 
		 textprintf_ex(Buffer,font,100,100,makecol(0,255,0),-1,"x_Mi: %d /y_Mi: %d",X_MAP,Y_MAP);
		 textprintf_ex(Buffer,font,100,120,makecol(0,255,0),-1,"Lon_Xi: %d /Lon_Yi: %d",Lon_Xi_MAP,Lon_Yi_MAP); 
		  textprintf_ex(Buffer,font,100,140,makecol(0,255,0),-1,"Lon_Xf: %d /Lon_Yf: %d",Lon_Xf_MAP,Lon_Yf_MAP); 
         //textprintf_ex(Buffer,font,100,140,makecol(0,255,0),-1,"PM_X: %d /PM_Y: %d",	mouse_x,mouse_y); 
		  //alfont_textprintf_ex(Buffer, fnt, 300, 90, makecol(255,0,0), -1, "Mario!");
		  //alfont_textprintf_centre_ex(Buffer, fnt, 300, 150, makecol(255,0,0), -1, "Mario!");
	
		//show_mouse(screen);//mostra o malse na tela
		//position_mouse(300,100);
        
        //rotate_sprite(Buffer,Buffer,0,0,DEGREES(450));
		
	//muda a escala da a imagem
	//stretch_blit(Buffer,screen,0,0,SCREEN_WIDTH ,SCREEN_HEIGHT,0,0,SCREEN_WIDTH_Z ,SCREEN_HEIGHT_Z);
	
	
        rest(60);//paralisa o programa por 'x' mile segundos       
        blit(Buffer,screen,0,0,0,0,640,480);//fixa o Buffer no screen
		clear(Buffer); 
	}
	
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
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);//GFX_AUTODETECT//GFX_AUTODETECT_WINDOWED
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
    alfont_exit();
	clear_keybuf();
	/* add other deinitializations here */
}
