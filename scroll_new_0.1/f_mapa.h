#ifndef F_MAPA_H
#define F_MAPA_H

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

void P_map(int PiX, int PiY)//-com parametros- muda a posicao do ponto inicial do mapa na tela 
     {
      X_MAP=PiX;
	  Y_MAP=PiY;
	  }

void P_map()//-sem parametoros- retorna a posicao do ponto inicial do mapa na tela(x=0,y=0) 
     {
      X_MAP=0;
	  Y_MAP=0;
	  }	  

  
class Fill_Mapa
          {
           private:
               int Xmax, Ymax;//dimensões do mapa 
           public:                         
			    void C_Tiles(BITMAP *till[],int Mx,int My,int Ntiles,BITMAP *Tile_Set,BITMAP *Buffer_esterno)
                { 
                 int i,j;
                 
                 int Xmin=0;
                 int Ymin=0;
                 int nt=0;
                                   
                 for(i=0;i<Ntiles;i++)
                     till[i]=create_bitmap(Tx_Tile,Ty_Tile);
    
                for(i=0;i<My;i++)
                 {
                  for(j=0;j<Mx;j++)
                       {
                        blit(Tile_Set,till[nt],Xmin,Ymin,0,0,Tx_Tile,Ty_Tile);
                        Xmin=Xmin+Tx_Tile;   
                        nt++;  
                       }
                  Ymin=Ymin+Ty_Tile;      
                  Xmin=0;  
                }
              }
              
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

        
            void Imp_Map(BITMAP *till[],int Nt,int PiM_X,int PiM_Y,int PfM_X,int PfM_Y, BITMAP *Buffer_externo,int *map_e,int xi,int yi)
                  {//(Mx=colunas)(My=linhas)
					int i,j,cont=0,k,P=0;                  
					Xmax=xi;
                    Ymax=yi;
    
				for(j=PiM_Y;j<PfM_Y;j++)
		                   {
					for(i=PiM_X;i<PfM_X;i++)//inprime o tile map
                       {
	                    for(k=1;k<Nt;k++)
							if(k==map_e[P]){
                              draw_sprite(Buffer_externo, till[k-1], Xmax, Ymax);  
						}	
                           P++; 
                           cont++;
                              Xmax=Xmax+Tx_Tile;
                       }
				       if(cont==PfM_X){ 
						  Xmax=xi;
						  Ymax=Ymax+Ty_Tile;
						  cont=0;}
                      } 		  		
                  }
  
    
            void Scoll_Map(int X_Tela,int Y_Tela,int Mx,int My)//-teste de sroll do tile_map 
		    {//modificar para ter interacao com o pesonagen do jogo
   		     //acrasentar entrada de parametros para modifica velocidade de deslocamento do mapa
			 if(key[KEY_UP]&& Y_MAP<=-4)// && Y_MAP>=0
		        Y_MAP+=4;
		     if(key[KEY_DOWN] && Y_MAP>((My*-Ty_Tile)+Y_Tela))//
		        Y_MAP-=4;    
		     if(key[KEY_LEFT] && X_MAP<=-40) 
		        {X_MAP+=40; }
	         if(key[KEY_RIGHT] && X_MAP<=0 && X_MAP>((Mx*-Tx_Tile)+X_Tela)) //X_MAP> -(x_maximo*tamanho_X_do_tile)+tamanho_da_tela
                {X_MAP-=40; }	
            }      
      
            void T_Colizao()//criar uma classe diferente para a colisao dos objetos
			{}

          };

#endif
