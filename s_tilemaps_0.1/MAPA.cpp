/********************************************************************
Programa: Tile_Maps
Descrição: classe utilizada para representar um tile-map
Data: --/--/2011
Local: NATAL/RN
Autor: Saulo Daniel
********************************************************************/
#ifndef MAPA_H
#define MAPA_H

//Bibliotecas utilizadas -nessecarias
#include <allegro.h>

class c
{
    //TILE *tile[];
    
    
 public:
        t(int *m[], int w,int h, BITMAP *t[])
          {
                
          
          }    
    
};


struct TILE_VECOR
{
 int WIDTH;
 int HEIGHT;
} 

class TILE_MAP
{
  private:
   //numero_de_tiles  que formam o mapa
    int QT_WIDTH;//x
    int QT_HEIGHT;//y
    //quantidade normal
    int QT_TOTAL;//x*y
    
    int Tx_Tile, Ty_Tile;//tamanho de cada tile representado no mapa(padrao 16,16)
    
  public: 
        TILE_MAP(int TM_W, int TM_H)
        {
         QT_WIDTH=TM_W;//x
         QT_HEIGHT=TM_H;//y
         
         QT_TOTAL=QT_WIDTH*QT_HEIGHT;
         
         Tx_Tile=16;
         Ty_Tile=16;
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
        
         void CaregaTiles(BITMAP *tile[],BITMAP *Tile_Set)
                { 
                 int i,j;
                 
                 int Xmin=0;
                 int Ymin=0;
                 int Nt=QT_TOTAL;//numero total de tiles
                                   
                 for(i=0;i<Nt;i++)
                     till[i]=create_bitmap(Tx_Tile,Ty_Tile);
    
                 Nt=0;    
    
                 for(i=0;i<My;i++)
                 {
                  for(j=0;j<Mx;j++)
                       {
                        blit(Tile_Set,tile[Nt],Xmin,Ymin,0,0,Tx_Tile,Ty_Tile);
                        Xmin=Xmin+Tx_Tile;   
                        Nt++;  
                       }
                  Ymin=Ymin+Ty_Tile;      
                  Xmin=0;  
                }
              }
    
        void TileTeste(BITMAP *till[],int Mx,int My,BITMAP *Tela_Esterna)
              {
               int i,j,nt=0;
               int Xmin=0;
               int Ymin=0;  
                  
               for(i=0;i<My;i++)
                 {
                  for(j=0;j<Mx;j++)
                       {
                        draw_sprite(Tela_Esterna, till[nt], Xmin,Ymin);
                        Xmin=Xmin+Tx_Tile;   
                        nt++;  
                       }
                  Ymin=Ymin+Ty_Tile;      
                  Xmin=0;  
                }	
              }
    
    //fill_mapa
    //void Fill_Map(BITMAP *tile[],int Nt,int *map_e,int M_X,int M_Y, BITMAP *Tela_Esterna)
//                  {//(Mx=colunas)(My=linhas)
//					int i,j,cont=0,k,P=0;                  
//					Xmax=X_MAP;
//                    Ymax=Y_MAP;
//				for(j=0;j<M_Y;j++)
//		                   {
//					for(i=0;i<M_X;i++)//inprime o tile map
//                       {
//                        if((Xmax-Tx_Tile>=-Tx_Tile*2) && (Xmax<=SCREEN_WIDTH) && (Ymax-Ty_Tile>=-Ty_Tile*2) && (Ymax<=SCREEN_HEIGHT))    
//	                    for(k=1;k<Nt;k++)                  
//							if(k==map_e[P]){
//                              draw_sprite(Tela_Esterna, tile[k-1], Xmax, Ymax); 
//                             // rect(Buffer_externo, Xmax, Ymax, Xmax+Tx_Tile-1, Ymax+Ty_Tile-1, makecol(255, 0, 0));         
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
//              } 
    
    
    
    //colisao_com_mapa
    
    
    //scrol_mapa
    
};




class MAPA_ORT//mapa ortogonal
{
  private:  
   // imagem prioncipal a onde sao desenhados os tilemaps
   BITMAP *TELA; 
    
   // O mapacomtem 5 Bitmaps que completam o cenario
   BITMAP *CAMADA[5];
    
   //tamanho da tela e camadas 
     int TELA_WIDTH, TELA_HEIGHT;
    
    
    
  public:
    
    MAPA()
    {
         
    }
    
    
    
  void fill_objeto(Bitmap *obj,int camada,x,y)
     {
      draw_sprite(CAMADA[camada], obj, x, y);      
     }


};

//funcao que abrevia o caregamento de uma imagem
BITMAP* LoadImg(char* sNome)
{
     BITMAP* temp = load_bitmap(sNome, NULL);

     return temp;
}




#endif


//==============================================================================


/********************************************************************
Programa: Exemplo6
Descrição: classe utilizada para representar um sprite
Data: 23/10/2009
Local: FACTO
Autor: Silvano Malfatti
********************************************************************/

//Bibliotecas utilizadas
#include <allegro.h>

class CSprite
{
      //Atributos da classe
      public:
      BITMAP* sprite;
      int iLarguraQuadro, iAlturaQuadro;
      int iPosX, iPosY;
      int iQtdQuadros;
      int iQuadroAtual;

      /***********************************************************
      *Função: CSprite()
      *Descrição: Construtor da classe
      *Parametros: char*
      *Retorno: Nenhum
      ************************************************************/
      CSprite()
      {
            sprite = NULL;
            iLarguraQuadro = 0;
            iAlturaQuadro = 0;
            iQtdQuadros = 0;
            iPosX=0;
            iPosY=0;
            iQuadroAtual = 0;
      }

      /***********************************************************
      *Função: CSprite()
      *Descrição: Construtor da classe
      *Parametros: BITMAP*, int, int, int
      *Retorno: Nenhum
      ************************************************************/
      CSprite(BITMAP* pImagem, int pLarguraQuadro, int pAlturaQuadro, int pQtdQuadros)
      {
            sprite = pImagem;
            iLarguraQuadro = pLarguraQuadro;
            iAlturaQuadro = pAlturaQuadro;
            iQtdQuadros = pQtdQuadros;
            iPosX=0;
            iPosY=0;
            iQuadroAtual = 0;
      }

      /***********************************************************
      *Função: DesenhaSprite
      *Descrição: desenha um quadro do sprite no buffer passado
      *Parametros: BITMAP*
      *Retorno: Nenhum
      ************************************************************/
      void DesenhaSprite(BITMAP* buffer)
      {
            int iCoordenadaX = (iQuadroAtual % (sprite->w/iLarguraQuadro)) * iLarguraQuadro;
            int iCoordenadaY = (iQuadroAtual / (sprite->w/iLarguraQuadro)) * iAlturaQuadro;

            masked_blit(sprite,buffer,iCoordenadaX,iCoordenadaY, iPosX, iPosY, iLarguraQuadro, iAlturaQuadro);

            iQuadroAtual = (iQuadroAtual>=iQtdQuadros-1)?0:++iQuadroAtual;
      }
};



























//#include <allegro.h>
//
//int main()
//{
//	allegro_init();
//	install_keyboard();
//
//	set_color_depth(32);
//	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 700, 0, 0);
//
//	BITMAP *buffer = create_bitmap(640, 700);
//	clear_to_color(buffer, 0x333333);
//
//	rect(buffer, 1, 1, 51, 51, 0x21D059);
//	rect(buffer, 2, 2, 50, 50, 0x21D059);
//	rect(buffer, 3, 3, 49, 49, 0x21D059);
//
//	textout_centre_ex(buffer, font, ALLEGRO_VERSION_STR, 320, 5, 0xFFFFFF, 0x333333);
//
//	rectfill(buffer, 50, 100, 550, 600, 0xDF1680);
//
//	blit(buffer, screen, 0, 0, 0, 0, 640, 700);
//
//	readkey();
//
//	destroy_bitmap(buffer);
//
//	return 0;
//}
//END_OF_MAIN();




//==============================================================================
//aloca matriz de inteiros que sera usada em mapas
#include <stdio.h>
#include <stdlib.h>

int **Alocar_matriz(int m, int n) 
{
  int **v; /* ponteiro para a matriz */
  int i; /* variavel auxiliar */
  
  if (m < 1 || n < 1) 
     { /* verifica parametros recebidos */
       printf ("** Erro: Parametro invalido **\n");
       return (NULL);
     }

 /* aloca as linhas da matriz */
 v = (int **) calloc (m, sizeof(int *));
 
 if (v == NULL)
    {
     printf ("** Erro: Memoria Insuficiente **");
     return (NULL);
    }

 /* aloca as colunas da matriz */
 for(i=0; i<m; i++)
    {
     v[i] = (int*) calloc (n, sizeof(int));
    
     if(v[i] == NULL)
       {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
       }
    }

 return (v); /* retorna o ponteiro para a matriz */
}

int **Liberar_matriz_real (int m, int n, int **v) 
    {
     int i; /* variavel auxiliar */

     if (v == NULL) return (NULL);

     if (m < 1 || n < 1) 
       { /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (v);
       }
       
     for (i = 0; i < m; i++) free (v[i]); /* libera as linhas da matriz */
          free (v); /* libera a matriz */
     
     return (NULL); /* retorna um ponteiro nulo */
    }


//int main (void)
//{
//int **mat; /* matriz a ser alocada */
//int l, c; /* numero de linhas e colunas da matriz */
///* outros comandos, inclusive inicializacao para l e c */
//mat = Alocar_matriz_real (l, c);
// /* outros comandos utilizando mat[][] normalmente */
//mat = Liberar_matriz_real (l, c, mat);
//
// return 0;
//
//}
