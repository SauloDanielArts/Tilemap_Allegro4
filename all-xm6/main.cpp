#include <allegro.h>
#include "mapa_xml.h"



// Exemplo da bolinha com limitador de FPS

// global
int fps = 0;

int fps_antigo = 0;
int fps_speed = 0;

 //prototipo do contador de frames
void frame_rate();

// prototipo do contador de velocidade
void incrementa_speed();




int main()
{
   allegro_init();
   set_color_depth(16);
   install_keyboard();
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, 256, 256, 0, 0);//GFX_AUTODETECT_WINDOWED//GFX_AUTODETECT_FULLSCREEN
   set_window_title("----");
  // set_display_switch_mode(SWITCH_BACKGROUND);//faz com que o jogo rode em segundo plano
   
   BITMAP *buffer = create_bitmap(256, 256);
   
   install_timer();
   
  //  a cada 1 segundo mostra quantas vezes a imagem foi impressa na tela
   //install_int( frame_rate, 1000 );
   
  // install_int_ex( incrementa_speed, BPS_TO_TIMER(4) );

   
   

   
   
       MAPA m;
    

		if( !m.load_XML("map.tmx") )
			{printf("Erro ao carregar arquivo 'mapa.tmx'.\n");
             exit(1); 
            }

   
      int dx=0,dy=0; 
 

int x,y;
             int i,j; 
    int k=0;
int DX=x;

int cont=0;
         
   
   
   
         m.set_xy();
      

   
  //  Laço principal
   while( !key[KEY_ESC] )
  {//clear( buffer );
    
      

        
      //while ( ::fps_speed > 0 )
      //{

         // limpa o nosso novo buffer
          clear( buffer );
        
         
          //m.Fill_Map(buffer,0);
          //m.Fill_Map(buffer,1); 
          //m.Fill_Map(buffer,2);
   
          
          
          m.Fill_Map(buffer,0,2,0.7,0.7);
          
          m.Fill_Map(buffer,1,2,0.8,0.8);
          
          m.Fill_Map(buffer,2,0);
          
         // m.Fill_Map(buffer,3,1);
          
         // m.Fill_Map(buffer,4,0);
           
           
           m.scoll_mt(buffer,32);
           
           
         

           // draw_sprite(buffer,m.getTile(m.vTileset[0]->palheta,255),dx,dy);	
            
            
            
            // ellipsefill(buffer, dx,dy, 60, 60, makecol(255,255,0) );

          
             
            
          
         textprintf_ex( buffer, font, 10, 10, makecol(255,0,0), -1, "FPS: %d", ::fps_antigo );
         
         
         

         //::fps_speed--;
         //::fps++;
      //}
      
      
 
             
            
   
   
      
      blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

      vsync();
   
   
   //system("cls");
   
   //rest(150);   
   }


   
   
//while(!key[KEY_ESC]){ 
//  clear(buffer);
//
//    m.x=dx;
//    m.y=dy;
//   
//       m.Fill_Map(buffer,0,0);
//       m.Fill_Map(buffer,0,1);
//        m.Fill_Map(buffer,1,0);
//         m.Fill_Map(buffer,2,0);
//    
//          if(key[KEY_UP] )
//            dy+=16;
//               
//            if(key[KEY_DOWN] )
//            dy-=16;
//               
//             if(key[KEY_LEFT])
//               dx+=16;
//
//            if(key[KEY_RIGHT] )
//               dx-=16;
//  
//
//
//
//blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
//}




blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
   readkey();
   
   destroy_bitmap( buffer );
   
   allegro_exit();
   return 0;
}
END_OF_MAIN();
   
void frame_rate()
{
   ::fps_antigo = ::fps;
   ::fps = 0;
}
   
void incrementa_speed()
{
   ::fps_speed++;
}

