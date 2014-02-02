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
      if(PiX>0)
         PiX=-PiX;   
      if(PiY>0)
         PiY=-PiY;     
          
      X_MAP=PiX;
	  Y_MAP=PiY;
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

        
        void Fill_Map(BITMAP *till[],int Nt,int *map_e,int M_X,int M_Y, BITMAP *Buffer_externo)
                  {//(Mx=colunas)(My=linhas)
					int i,j,cont=0,k,P=0;                  
					Xmax=X_MAP;
                    Ymax=Y_MAP;
                    
                 // Lon_Xi_MAP, Lon_Yi_MAP
                 // Lon_Xf_MAP, Lon_Yf_MAP    
    
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
//                    
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
  
    
            void Scoll_Map(int X_Tela,int Y_Tela,int Mx,int My,int v,BITMAP *Buffer_externo)//-teste de sroll do tile_map 
		    {//modificar para ter interacao com o pesonagen do jogo
   		     //acrasentar entrada de parametros para modifica velocidade de deslocamento do mapa
			 if(key[KEY_UP]&& Y_MAP<=-v)// && Y_MAP>=0
		        Y_MAP+=v;
		     if(key[KEY_DOWN] && Y_MAP>((My*-Ty_Tile)+Y_Tela))//
		        Y_MAP-=v;    
		     if(key[KEY_LEFT] && X_MAP<=-4) 
		        {X_MAP+=v; }
	         if(key[KEY_RIGHT] && X_MAP<=0 && X_MAP>((Mx*-Tx_Tile)+X_Tela)) //X_MAP> -(x_maximo*tamanho_X_do_tile)+tamanho_da_tela
                {X_MAP-=v; }	
                
             textprintf_ex(Buffer_externo,font,100,100,makecol(0,255,0),-1,"x_Mi: %d /y_Mi: %d",X_MAP,Y_MAP);
		     textprintf_ex(Buffer_externo,font,100,120,makecol(0,255,0),-1,"x_Mf: %d /y_Mf: %d",X_MAP+-(Mx*-Tx_Tile),Y_MAP+-(My*-Ty_Tile));
		     textprintf_ex(Buffer_externo,font,100,140,makecol(0,255,0),-1,"Lon_Xi: %d /Lon_Yi: %d",Lon_Xi_MAP,Lon_Yi_MAP); 
		     textprintf_ex(Buffer_externo,font,100,160,makecol(0,255,0),-1,"Lon_Xf: %d /Lon_Yf: %d",Lon_Xf_MAP,Lon_Yf_MAP);   
            }
            
            void Scoll_Map(int X_Tela,int Y_Tela,int Mx,int My,int v)//-teste de sroll do tile_map 
		    {//modificar para ter interacao com o pesonagen do jogo
   		     //acrasentar entrada de parametros para modifica velocidade de deslocamento do mapa
			 if(key[KEY_UP]&& Y_MAP<=-v)// && Y_MAP>=0
		        Y_MAP+=v;
		     if(key[KEY_DOWN] && Y_MAP>((My*-Ty_Tile)+Y_Tela))//
		        Y_MAP-=v;    
		     if(key[KEY_LEFT] && X_MAP<=-4) 
		        {X_MAP+=v; }
	         if(key[KEY_RIGHT] && X_MAP<=0 && X_MAP>((Mx*-Tx_Tile)+X_Tela)) //X_MAP> -(x_maximo*tamanho_X_do_tile)+tamanho_da_tela
                {X_MAP-=v; }  
            }      
      
            void T_Colizao()//criar uma funcao diferente para a colisao dos objetos
			{}

          };
          
//------------------------------------------------------------------------------

#endif
