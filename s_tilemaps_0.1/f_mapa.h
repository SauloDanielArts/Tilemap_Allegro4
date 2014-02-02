#ifndef F_MAPA_H
#define F_MAPA_H

int SCREEN_WIDTH  = 640;
int SCREEN_HEIGHT = 480;

int X_MAP=0, Y_MAP=0;//posicao do ponto inicial do mapa em relacao a tela 

int Tx_Tile=16, Ty_Tile=16;//tamanho de cada tile representado no mapa(padrao 16,16)

int Lon_Xi_MAP=0, Lon_Yi_MAP=0;//tile que esta junto ao ponto de origem da tela
int Lon_Xf_MAP=0, Lon_Yf_MAP=0;//tile que esta junto ao ponto de origem da tela

void Longit_Lat()
     {//calcula o tile que esta junto ao ponto de origem da tela e...     
	  Lon_Xi_MAP=((X_MAP)/-Tx_Tile);	
	  Lon_Yi_MAP=((Y_MAP)/-Ty_Tile);

      //o que esta no ponto final da tela
	  Lon_Xf_MAP= Lon_Xi_MAP +(SCREEN_WIDTH/Tx_Tile);
	  Lon_Yf_MAP= Lon_Yi_MAP +(SCREEN_HEIGHT/Ty_Tile);
     }     


//------------------------

//estrutura para os retangulos
struct RETANGULO
{
	int x, y; //posição x e y na tela
	int l, a; //largura e altura do retângulo
};

//rotina de checagem de colisão baseada em retangulos
bool Colisao(RETANGULO &obj1, RETANGULO &obj2)
{
    if (obj1.x > obj2.x + obj2.l) return false; //obj1 está a direita de obj2
    if (obj1.y > obj2.y + obj2.a) return false; //obj1 está abaixo de obj2
    if (obj1.x + obj1.l-1 < obj2.x) return false; //obj1 está a esquerda de obj2
    if (obj1.y + obj1.a-1 < obj2.y) return false; //obj1 está acima de obj2

    return true; //existe colisão, ou seja, obj1 está tocando em obj2
}

//------------------------



void T_Tile(int Tx, int Ty)//-com parametros- mudar o tamanho dos tiles
     {
	  Tx_Tile=Tx;
      Ty_Tile=Ty;		
     }

void T_Tile()//-sem parametoros- retoernar ao tile padrao(16x16) 
     {
	  Tx_Tile=16;
      Ty_Tile=16;		
     }

void P_Map(int PiX, int PiY)//-com parametros- muda a posicao do ponto inicial do mapa na tela 
     {
      //if(PiX>0)
//         PiX=-PiX;   
//      if(PiY>0)
//         PiY=-PiY;     
          
      X_MAP=PiX*Tx_Tile;
	  Y_MAP=PiY*Ty_Tile;
	  }

void P_Map()//-sem parametoros- retorna a posicao do ponto inicial do mapa na tela(x=0,y=0) 
     {
      X_MAP=0;
	  Y_MAP=0;
	  }	  

  
class Mapa
          {
           private:
               int Xmax, Ymax;//dimensões do mapa 
           public:  
            /***********************************************************
            *Função: C_Tiles(BITMAP *till[],BITMAP *Tile_Set,int Mx,int My)
            *Descrição: Carega um 'tileset' a partir de um 'bitmap' especificado
            *Parametros: 
                BITMAP *till[] //vetor de tiles
                BITMAP *Tile_Set //tileset original
                int Mx //numero maximo de tiles em 'x'
                int My //numero maximo de tiles em 'y'
            *Retorno: Nenhum
            ************************************************************/
			void C_Tiles(BITMAP *till[],BITMAP *Tile_Set,int Mx,int My)
                { 
                 int i,j;
                 
                 int Xmin=0;
                 int Ymin=0;
                 int Nt=Mx*My;
                                   
                 for(i=0;i<Nt;i++)
                     till[i]=create_bitmap(Tx_Tile,Ty_Tile);
    
                 Nt=0;    
    
                 for(i=0;i<My;i++)
                 {
                  for(j=0;j<Mx;j++)
                       {
                        blit(Tile_Set,till[Nt],Xmin,Ymin,0,0,Tx_Tile,Ty_Tile);
                        Xmin=Xmin+Tx_Tile;   
                        Nt++;  
                       }
                  Ymin=Ymin+Ty_Tile;      
                  Xmin=0;  
                }
              }


           /***********************************************************
            *Função: Tile_test(BITMAP *till[],int Mx,int My,BITMAP *Buffer_esterno)
            *Descrição: Testa o 'tileset' caregado o in=mprimindo no Buffer
            *Parametros: 
                BITMAP *till[] //vetor de tiles
                int Mx //numero maximo de tiles em 'x'
                int My //numero maximo de tiles em 'y'
                BITMAP *Buffer_esterno //bitmap usado para impresao
            *Retorno: Nenhum
            ************************************************************/   
           void Tile_test(BITMAP *till[],int Mx,int My,BITMAP *Buffer_esterno)
              {
               int i,j,nt=0;
               int Xmin=0;
               int Ymin=0;  
                  
               for(i=0;i<My;i++)
                 {
                  for(j=0;j<Mx;j++)
                       {
                        draw_sprite(Buffer_esterno, till[nt], Xmin,Ymin);
                        Xmin=Xmin+Tx_Tile;   
                        nt++;  
                       }
                  Ymin=Ymin+Ty_Tile;      
                  Xmin=0;  
                }	
              }

        
        void Fill_Map(BITMAP *till[],int Nt,int *map_e,int M_X,int M_Y, BITMAP *Buffer_externo,float dx ,float dy)
                  {//(Mx=colunas)(My=linhas)
					int i,j,cont=0,k,P=0;                  
					Xmax=X_MAP*dx;
					dx=Xmax;
                    Ymax=Y_MAP*dy;
    
				for(j=0;j<M_Y;j++)
		                   {
					for(i=0;i<M_X;i++)//inprime o tile map
                       {
                        if((Xmax-Tx_Tile>=-Tx_Tile*2) && (Xmax<=SCREEN_WIDTH) && (Ymax-Ty_Tile>=-Ty_Tile*2) && (Ymax<=SCREEN_HEIGHT))    
	                    for(k=1;k<Nt;k++)                  
							if(k==map_e[P]){
                              draw_sprite(Buffer_externo, till[k-1], Xmax, Ymax);  
						}	
                           P++; 
                           cont++;
                              Xmax=Xmax+Tx_Tile;
                       }
				       if(cont==M_X){ 
						  Xmax=dx;
						  Ymax=Ymax+Ty_Tile;
						  cont=0;}
                      } 		  		
                  }
                  
        void Fill_Map(BITMAP *till[],int Nt,int *map_e,int M_X,int M_Y, BITMAP *Buffer_externo)
                  {//(Mx=colunas)(My=linhas)
					int i,j,cont=0,k,P=0;                  
					Xmax=X_MAP;
                    Ymax=Y_MAP;
				for(j=0;j<M_Y;j++)
		                   {
					for(i=0;i<M_X;i++)//inprime o tile map
                       {
                        if((Xmax-Tx_Tile>=-Tx_Tile*2) && (Xmax<=SCREEN_WIDTH) && (Ymax-Ty_Tile>=-Ty_Tile*2) && (Ymax<=SCREEN_HEIGHT))    
	                    for(k=1;k<Nt;k++)                  
							if(k==map_e[P]){
                              draw_sprite(Buffer_externo, till[k-1], Xmax, Ymax); 
                             // rect(Buffer_externo, Xmax, Ymax, Xmax+Tx_Tile-1, Ymax+Ty_Tile-1, makecol(255, 0, 0));         
						}	
                           P++; 
                           cont++;
                              Xmax=Xmax+Tx_Tile;
                       }
				       if(cont==M_X){ 
						  Xmax=X_MAP;
						  Ymax=Ymax+Ty_Tile;
						  cont=0;}
                      } 		  		
                  }                  
                              

            //void Fill_Map(BITMAP *till[],int Nt,int *map_e,int M_X,int M_Y, BITMAP *Buffer_externo)
//                  {//(Mx=colunas)(My=linhas)
//					int i,j,cont=0,k,P=0;                  
//					Xmax=X_MAP;
//                    Ymax=Y_MAP;
//                    
//				for(j=0;j<M_Y;j++)
//		                   {
//					for(i=0;i<M_X;i++)//inprime o tile map
//                       {
//	                    for(k=1;k<Nt;k++)
//							if(k==map_e[P]){
//                              draw_sprite(Buffer_externo, till[k-1], Xmax, Ymax);  
//						}	
//                           P++; 
//                           cont++;
//                              Xmax=Xmax+Tx_Tile;
//                       }
//				       if(cont==M_X){ 
//						  Xmax=X_MAP;
//						  Ymax=Ymax+Ty_Tile;
//						  cont=0;}
//                      } 		  		
//                  }
  
    
            void Scoll_MapD(int Mx,int My,int v,BITMAP *Buffer_externo)//-teste de sroll do tile_map 
		    {// movimenta todo o mapa a partiir dos butoes direcionais
			 if(key[KEY_UP] && Y_MAP<=-v)
		        Y_MAP+=v;
		     if(key[KEY_DOWN] && Y_MAP>((My*-Ty_Tile)+SCREEN_HEIGHT))
		        Y_MAP-=v;    
		     if(key[KEY_LEFT] && X_MAP<=-v) 
		        {X_MAP+=v; }
	         if(key[KEY_RIGHT] && X_MAP<=0 && X_MAP>((Mx*-Tx_Tile)+SCREEN_WIDTH)) 
                {X_MAP-=v; }	
                
             if(key[KEY_P])
             {   
             textprintf_ex(Buffer_externo,font,100,100,makecol(0,100,0),-1,"x_Mi: %d /y_Mi: %d",X_MAP,Y_MAP);
		     textprintf_ex(Buffer_externo,font,100,120,makecol(0,100,0),-1,"x_Mf: %d /y_Mf: %d",X_MAP+-(Mx*-Tx_Tile),Y_MAP+-(My*-Ty_Tile));
		     textprintf_ex(Buffer_externo,font,100,140,makecol(0,100,0),-1,"Lon_Xi: %d /Lon_Yi: %d",Lon_Xi_MAP,Lon_Yi_MAP); 
		     textprintf_ex(Buffer_externo,font,100,160,makecol(0,100,0),-1,"Lon_Xf: %d /Lon_Yf: %d",Lon_Xf_MAP,Lon_Yf_MAP);   
             }
            }
            
            void Scoll_Map(int X_Tela,int Y_Tela,int Mx,int My,int v)//-teste de sroll do tile_map 
		    {//modificar para ter interacao com o pesonagen do jogo
   		     //acrasentar entrada de parametros para modifica velocidade de deslocamento do mapa
			 if(key[KEY_UP]&& Y_MAP<=-v)// && Y_MAP>=0
		        Y_MAP+=v;
		     if(key[KEY_DOWN] && Y_MAP>((My*-Ty_Tile)+Y_Tela))//
		        Y_MAP-=v;    
		     if(key[KEY_LEFT] && X_MAP<=-v) 
		        {X_MAP+=v; }
	         if(key[KEY_RIGHT] && X_MAP<=0 && X_MAP>((Mx*-Tx_Tile)+X_Tela)) //X_MAP> -(x_maximo*tamanho_X_do_tile)+tamanho_da_tela
                {X_MAP-=v; }  
            }      
    
// bool T_Colizao(int largura,int altura,int obj_x,int obj_y,int *map_c,int M_X,int M_Y, BITMAP *Buffer_externo)//criar uma funcao diferente para a colisao dos objetos
//	{             
//        int i,j,cont=0,k,P=0;  
//        RETANGULO tile, obj;                
//		Xmax=X_MAP;
//        Ymax=Y_MAP;
//        int Px=0,Py=0;
//        
//        int Ct=2;//-------
//        
//        //tile
//	    tile.x = 0;
//	    tile.y = 0;
//	    tile.l = Tx_Tile;
//	    tile.a = Ty_Tile;
//
//	    //obj
//	    obj.x = obj_x;
//        obj.y = obj_y;
//        obj.l = largura;
//        obj.a = altura;
//        
//				for(j=0;j<M_Y;j++)
//		                   {
//					for(i=0;i<M_X;i++)
//                       {
//                        
//                           
//                        if((Xmax-Tx_Tile>=-Tx_Tile*2) && (Xmax<=SCREEN_WIDTH) && (Ymax-Ty_Tile>=-Ty_Tile*2) && (Ymax<=SCREEN_HEIGHT))    
//	                       {for(k=1;k<Ct;k++)                  
//							   //if(k==map_c[P])
//                               {
//                              //draw_sprite(Buffer_externo, till[k-1], Xmax, Ymax);    
//                              
//                              tile.x =Xmax;
//	                          tile.y =Ymax;
//                               
//                               Px=obj.x;
//                               Py=obj.y;   
//                               
//                            
//                              //rect(Buffer_externo, Xmax, Ymax, Xmax+Tx_Tile, Ymax+Ty_Tile, makecol(255, 0, 0));      
//                              if(map_c[P]==k && Colisao(tile, obj))
//                                 {
//                                  obj.x=Px;
//                                  obj.y=Py;
//                                  textout_ex(screen, font, "colisao detectada!!!", 20, 20, makecol(255, 0, 0), -1);
//                                  rect(Buffer_externo, Xmax, Ymax, Xmax+Tx_Tile, Ymax+Ty_Tile, makecol(255, 0, 0));
//                                  return true;
//                                 }     
//                           }  
// 
//						}	
//                           P++; 
//                           cont++;
//                              Xmax=Xmax+Tx_Tile;
//                       }
//				       if(cont==M_X){ 
//						  Xmax=X_MAP;
//						  Ymax=Ymax+Ty_Tile;
//						  cont=0;}
//                      } 
//    
//     return false;
//   }
     
     
     
     
     
     
     
     
     
     
     
     
     int c(int largura,int altura,int &obj_x,int &obj_y,int map_e[],int M_X,int M_Y, BITMAP *Buffer_externo)
                  {
					int i,j,cont=0,k,P=0;                  
					Xmax=X_MAP;
                    Ymax=Y_MAP;
                    int Ct=0;
                    
                    int Px=0,Py=0;
                    
                    int colisao=0;
                    
         RETANGULO tile, obj;               
                    
        //tile
	    tile.x = 0;
	    tile.y = 0;
	    tile.l = Tx_Tile;
	    tile.a = Ty_Tile;

	    //obj
	    obj.x = obj_x;
        obj.y = obj_y;
        obj.l = largura;
        obj.a = altura;
                    
                    
                    
				for(j=0;j<M_Y;j++)
		                   {
					for(i=0;i<M_X;i++)//inprime o tile map
                       {
                        //if((Xmax-Tx_Tile>=-Tx_Tile*2) && (Xmax<=SCREEN_WIDTH) && (Ymax-Ty_Tile>=-Ty_Tile*2) && (Ymax<=SCREEN_HEIGHT))    
	                    //for(k=1;k<Ct;k++)                  
							if(map_e[P]>0){//(k==map_e[P])
                              //draw_sprite(Buffer_externo, till[k-1], Xmax, Ymax); 
                              rect(Buffer_externo, Xmax, Ymax, Xmax+Tx_Tile-1, Ymax+Ty_Tile-1, makecol(200, 0, 0));         
						      tile.x =Xmax;
	                          tile.y =Ymax;
                               
                               Px=obj.x;
                               Py=obj.y;   
                               
                            
                              if(Colisao(tile, obj))
                                 {
                                  obj.x=Px;
                                  obj.y=Py;
                                  textout_ex(screen, font, "colisao detectada!!!", 20, 20, makecol(255, 0, 0), -1);
                                  set_trans_blender(0, 0, 0, 100);    
                                  drawing_mode(DRAW_MODE_TRANS,  0,0, 0);
                                  rectfill(Buffer_externo, Xmax, Ymax, Xmax+Tx_Tile-1, Ymax+Ty_Tile-1, makecol(255, 0, 0));
                                  drawing_mode(DRAW_MODE_SOLID, 0, 0, 0); 
                                 
                                 //colisao de quadrados as tachas de deslocamento dos pixels deve ser menor que o tamanho dos tiles testados
                                  
                                  
                                  
                                  
                            
                                
                                
                                 
                                
                                 //obj está abaixo do tile
                                 if (tile.y < obj.y + obj.a && obj.x+obj.l>tile.x-1 && obj.x<tile.x+Tx_Tile && obj.y>tile.y) obj_y=Ymax+(tile.a);  
                                
                                 //obj está acima do tile
                                 if (obj.y + obj.a > tile.y-1 && obj.x+obj.l>tile.x-1 && obj.x<tile.x+Tx_Tile && obj.y<tile.y) obj_y=Ymax-(obj.a+1);                              

                                    
                                    //obj está a esquerda do tile
                                  //if (tile.x + tile.l > obj.x ) obj_x=Xmax-(obj.l);    
                                    
                                  //obj está a direita do tile 
                                  //if (tile.x < obj.x + obj.l ) obj_x=Xmax+(obj.l); 
                                    
                                 
                                 
                                 
                                 //if (tile.y < obj.y + obj.a) obj_y=Ymax+(obj.a); //obj1 está abaixo de obj2
                                 //if (tile.y + tile.a > obj.y) obj_y=Ymax-(obj.a+1); //obj1 está acima de obj2
                                 // if (tile.x < obj.x + obj.l && obj_y+Ty_Tile>=Ymax && obj_y<=Ymax+Ty_Tile-1) obj_x=Xmax+(obj.l+1); //obj1 está a direita de obj2
                                 // if (tile.x + tile.l > obj.x && obj_y+Ty_Tile>=Ymax && obj_y<=Ymax+Ty_Tile-1) obj_x=Xmax-(obj.l+1); //obj1 está a esquerda de obj2
                                  
                                  
                                  //calculo de colizao-------------------------------------
                                   //if(obj_x>=Xmax && obj_x<=(Tx_Tile/1.2) && obj_y>=Ymax && obj_y<=Ymax+Ty_Tile)//bloco 1 ------- //--- 
                                     // obj_x=obj_x-tile.l;                                     //
                                       //if(y>=300 && x>=576 && x<=606 && y<=336)                       //
//                                           x=576;                                                      //
//                                    if(y>=300 && x>=580 && x<=610 && y<=336)                       //
//                                       x=610;                                                      //   
//                                      if((x>=580 && x<=604) && y>=305 && y<=346)                     //
//                                      y=346; //----------------------------------------------- //--- 
                       
                                 colisao=1;
                                }
                                
                                
                        
                        }	
                           P++; 
                           cont++;
                              Xmax=Xmax+Tx_Tile;
                       }
				       if(cont==M_X){ 
						  Xmax=X_MAP;
						  Ymax=Ymax+Ty_Tile;
						  cont=0;}
                      } 
                      
                    return colisao;  	  		
                  }
     
     
     
     
 
          };
          
//------------------------------------------------------------------------------

#endif
