#ifndef MAPA_XML_H
#define MAPA_XML_H

#include <allegro.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>


#include <zlib.h>

#include <vector>
#include <string>
using namespace std;

#include <cstdio>

struct ALLEGRO_Rect
{
 unsigned long x,y;  
 unsigned long w,h;
};

class MAPA{//: public Thread{ 
public: //------------------------------------------------------------

//! Exce��es disparadas por membros da classe Mapa.
	enum Exception{
		FILE_NULL,  //!< Arquivo n�o existe.
		ID_LAYER,   //!< Id da Layer n�o existe.
		DATA_LAYER, //!< Dados da Layer n�o foram carregados.
		PTR_NULL    //!< Ponteiro nulo.
	};

	//! Objeto tile.
	struct Tile{
		int id; //!< Id global do tile
		BITMAP *img; //!< Imagem do tile.
	};

	//! Tabela de tiles
	struct Tileset{
		string name;      //!< Identifica��o do tileset.
		int firstGid;     //!< Numera��o inicial da grade.
		BITMAP *palheta; //!< Imagem.
		string img_name;
		int NT;

       // std::vector<Tile>tile;
		//Property lProperty; //!< Lista de propriedades.
	};

	//! Layer (Camada)
	struct Layer{
		string name; //!< Identifica��o da camada.
		int width;   //!< Largura da camada.//numero de tiles em w
		int height;  //!< Altura da camada.//numero de tiles em h
		int dx; //!< Deslocamento x.
		int dy; //!< Deslocamento y.
		//float opacity="0.37"
		unsigned int *dados; //!< Dados.

	};

private: //-----------------------------------------------------------


	string version;     //!< Vers�o: 0.99b ou compat�vel.
	string orientation; //!< Orienta��o: orthogonal, isometrico...
	int width;          //!< Largura do mapa.
	int height;         //!< Altura do mapa.
	int tileWidth;      //!< Largura de um tile.
	int tileHeight;     //!< Altura de um tile;

	std::vector<Tileset*> vTileset;   //!< vetor de tilesets.
	std::vector<Layer*> vLayer;       //!< vetor de layers (camadas).
	
	long x,y; //posicao do mapa em relacao a tela

	Tileset *newTileset();
	void delTileset(Tileset *tset);
	Layer *newLayer();
	void delLayer(Layer *layer);


public: //------------------------------------------------------------

	MAPA(); 
    ~MAPA();
	
	void limpar();
	
	void setDados(Layer *layer, const char *dados, bool gzip);
    void readTileset(Tileset *tset, xmlNode *root, xmlXPathContext *ctxt);
    void readLayer(Layer *layer, xmlNode *root, xmlXPathContext *ctxt);
    void readMap(xmlNode *root, xmlXPathContext *ctxt);
	bool load_XML(const char *file);


   BITMAP* getTile(BITMAP* palheta, int p);
	
	
	void Fill_Map(BITMAP *Tela,int nLayer,float dx=1,float dy=1);
	
	void Fill_Map(BITMAP *Tela,int nLayer,int nTileset,float dx=1,float dy=1);

		
long get_x();	
	
long get_y();	
	
void set_x(int X=0);
    
void set_y(int Y=0);	

void set_xy(int X=0, int Y=0);

int get_width();		

int get_height();	


int get_tileWidth();	

int get_tileHeight();		
	
void scoll_mt(BITMAP *Tela ,int v);

int size_vTileset();

int size_vLayer();

};	
	
#endif
