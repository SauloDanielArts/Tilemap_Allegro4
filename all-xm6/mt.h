#ifndef MT_H
#define MT_H



#include <allegro.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>


#include <zlib.h>

#include <vector>
#include <list>
#include <string>
using std::string;

#include <cstdio>

struct ALLEGRO_Rect
{
 unsigned int x,y;  
 unsigned int w,h;
};




namespace MapaGlobal{
	int	getInt(xmlNode *no, const char* nome=NULL, int def=0){
		xmlChar *str;

		if( !nome )
			str = xmlNodeGetContent(no);
		else
			str = xmlGetProp(no, BAD_CAST nome);

		if( str ){
			def = atoi((char*)str);
			xmlFree(str);
		}
		return def;
	}

	string getString(xmlNode *no, const char *nome=NULL, const string &def=""){
		xmlChar *str;

		if( !nome )
			str = xmlNodeGetContent(no);
		else
			str = xmlGetProp(no, BAD_CAST nome);

		if( str ){
			string ret = (char*)str;
			xmlFree(str);
			return ret;
		}
		return def;
	}

	xmlNodeSet *getNodes(xmlXPathContext *ctxt, xmlXPathObject *xpathObj, const char *xpath){
		xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath, ctxt);
		if( xpathObj )
			if( xpathObj->nodesetval )
				return xpathObj->nodesetval;
		throw 1;
	}

	xmlNode *getNo(xmlXPathContext *ctxt, const char *xpath){
		xmlNodeSet *nos = NULL;
		xmlXPathObjectPtr xpathObj = NULL;

		xpathObj = xmlXPathEvalExpression((const xmlChar*)xpath, ctxt);
		try{
			nos = getNodes(ctxt, xpathObj, xpath);
			if(nos->nodeNr > 0)
				return nos->nodeTab[0];
		}catch(...){}

		xmlXPathFreeObject(xpathObj);
		return NULL;
	}

	static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	//! Obtem a posição do caractere na base64.
	int getPos(char c){
		if( c>='A' && c<='Z')
			return c-'A';
		if( c>='a' && c<='z')
			return c-'a' + 26;
		if( c>='0' && c<='9')
			return c-'0' + 52;
		else if( c=='+' )
			return 62;
		else if( c=='/' )
			return 63;
		else return -1;
	}

	/**
	 * @brief Codifica dados binários (base256) em base64.

	 * Esta função foi originalmente escrita pela equipe do PHP:\n
	 * PHP HTML Embedded Scripting Language Version 3.0\n
	 * Copyright (c) 1997,1998 PHP Development Team (See Credits file)\n
	 */
	unsigned char *base64_encode(const unsigned char *string, int length, int *ret_length){
		const unsigned char *current = string;
		int i = 0;
		unsigned char *result = (unsigned char *)malloc(((length + 3 - length % 3) * 4 / 3 + 1) * sizeof(char));

		while (length > 2) { /* keep going until we have less than 24 bits */
			result[i++] = base64[current[0] >> 2];
			result[i++] = base64[((current[0] & 0x03) << 4) + (current[1] >> 4)];
			result[i++] = base64[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
			result[i++] = base64[current[2] & 0x3f];

			current += 3;
			length -= 3; /* we just handle 3 octets of data */
		}

		/* now deal with the tail end of things */
		if (length != 0) {
			result[i++] = base64[current[0] >> 2];
			if (length > 1) {
				result[i++] = base64[((current[0] & 0x03) << 4) + (current[1] >> 4)];
				result[i++] = base64[(current[1] & 0x0f) << 2];
				result[i++] = '=';
			}
			else {
				result[i++] = base64[(current[0] & 0x03) << 4];
				result[i++] = '=';
				result[i++] = '=';
			}
		}
		if(ret_length) {
			*ret_length = i;
		}
		result[i] = '\0';
		return result;
	}

	/**
	 * @brief Decodifica dados na base64 em binário (base256).

	 * Esta função foi originalmente escrita pela equipe do PHP:\n
	 * PHP HTML Embedded Scripting Language Version 3.0
	 * Copyright (c) 1997,1998 PHP Development Team (See Credits file)
	 * @param string String base64 de entrada. Caracteres inválidos serão ignorados.
	 * @param length Quantidade de memória a ser alocada para o buffer de saída.
	 * @param ret_length Quantidade real decodificada.
	 * @return Ponteiro do buffer com os dados decodificados ou NULL, caso falhe.
	 */
	unsigned char *base64_decode(const unsigned char *string, int length, int *ret_length){
		const unsigned char *current = string;
		int ch, i=0, j=0, k;

		unsigned char *result = new unsigned char[length + 1];

		if( result==NULL ){
			return NULL;
		}

		/* run through the whole string, converting as we go */
		while( (ch = *current++) != '\0' ){
			if( ch=='=' ) break;

			ch = getPos(ch);
			if( ch==-1 ) continue;

			switch(i % 4) {
				case 0:
					result[j] = ch << 2;
					break;
				case 1:
					result[j++] |= ch >> 4;
					result[j] = (ch & 0x0f) << 4;
					break;
				case 2:
					result[j++] |= ch >>2;
					result[j] = (ch & 0x03) << 6;
					break;
				case 3:
					result[j++] |= ch;
					break;
			}
			i++;
		}

		k = j;
		/* mop things up if we ended on a boundary */
		if (ch == '=') {
			switch(i % 4) {
				case 0:
				case 1:
					delete[] result;
					return NULL;
				case 2:
					k++;
				case 3:
					result[k++] = 0;
			}
		}
		if(ret_length) {
			*ret_length = j;
		}
		result[k] = '\0';
		return result;
	}

	int contBase64_decode(const char *dados){
		int i, n=0;

		for(i=0; dados[i]; i++){
			if( dados[i] >= '+' ){
				n++;
			}
		}
		return n*3/4;
	}

};
using namespace MapaGlobal;


////====================================================================







class MAPA{//: public Thread{ 
public: //------------------------------------------------------------

//! Exceções disparadas por membros da classe Mapa.
	enum Exception{
		FILE_NULL,  //!< Arquivo não existe.
		ID_LAYER,   //!< Id da Layer não existe.
		DATA_LAYER, //!< Dados da Layer não foram carregados.
		PTR_NULL    //!< Ponteiro nulo.
	};

	//! Objeto tile.
	struct Tile{
		int id; //!< Id global do tile
		BITMAP *img; //!< Imagem do tile.
	};

	//! Tabela de tiles
	struct Tileset{
		string name;      //!< Identificação do tileset.
		int firstGid;     //!< Numeração inicial da grade.
		int tileWidth;    //!< Largura de um tile.
		int tileHeight;   //!< Altura de um tile.
		BITMAP *img; //!< Imagem.
		string img_name;

        std::vector<Tile>tile;
		//Property lProperty; //!< Lista de propriedades.
	};

	//! Layer (Camada)
	struct Layer{
		string name; //!< Identificação da camada.
		int width;   //!< Largura da camada.//numero de tiles em w
		int height;  //!< Altura da camada.//numero de tiles em h
		int xOffset; //!< Deslocamento x.
		int yOffset; //!< Deslocamento y.
		//float opacity="0.37"
		unsigned int *dados; //!< Dados.

	};

//private: //-----------------------------------------------------------


	string version;     //!< Versão: 0.99b ou compatível.
	string orientation; //!< Orientação: orthogonal, isometrico...
	int width;          //!< Largura do mapa.
	int height;         //!< Altura do mapa.
	int tileWidth;      //!< Largura de um tile.
	int tileHeight;     //!< Altura de um tile;
	int tileOut;        //!< Id de um tile fora dos limites da camada.

    //Property Property;      //propriedades do mapa
	std::vector<Tileset*> vTileset;   //!< vetor de tilesets.
	std::vector<Layer*> vLayer;       //!< vetor de layers (camadas).

	int nTileset;       //!< Tamanho do vetor Tileset.
	int nLayer;         //!< Tamanho do vetor Layer.

//	Tileset *newTileset();
//	void delTileset(Tileset *tset);
//	Layer *newLayer();
//	void delLayer(Layer *layer);



public: //------------------------------------------------------------

	MAPA()//!< Contrutor.
       {
        tileOut = width = height = tileWidth = tileHeight = 0;
        }  
	
    
    ~MAPA(){
        limpar();
    }
	
	

Tileset *newTileset(){
	Tileset *tset = new Tileset;
	tset->firstGid = 0;
	tset->tileWidth = 0;
	tset->tileHeight = 0;
	tset->img=NULL;
	tset->img_name ="";

	return tset;
}

void delTileset(Tileset *tset){
	delete tset;
}


Layer *newLayer(){
	Layer *layer = new Layer;
	layer->width = 0;
	layer->height = 0;
	layer->xOffset = 0;
	layer->yOffset = 0;
	layer->dados = NULL;
	
	return layer;
}

void delLayer(Layer *layer){
	if(layer->dados)
		delete[] layer->dados;

	delete layer;
}	

	
	
	

void limpar(){
	version.clear();
	orientation.clear();
	width = height = tileWidth = tileHeight = 0;

    nTileset = nLayer = 0; 

    int i;

}	
	
void readTileset(Tileset *tset, xmlNode *root, xmlXPathContext *ctxt){
    ctxt->node = root;
	tset->name = getString(root, "name");
	tset->firstGid  = getInt(root, "firstgid");
	tset->tileWidth   = getInt(root, "tilewidth");
	tset->tileHeight  = getInt(root, "tileheight");
	
	tset->img_name = getString( getNo(ctxt, "image"), "source").c_str();
	

    tset->img = load_bitmap( tset->img_name.c_str() ,NULL);

    
    Tile temp_tile;


int temp_id=tset->firstGid;

int i,j;
int P=0;
int Xmin=0;
int Ymin=0;


    //prenche o vetorcom dos tiles
    for( i=0;i<(tset->img->h/tileHeight);i++)
    {
       for(j=0;j<(tset->img->w/tileWidth) ;j++)
       {
         temp_tile.id=temp_id;
         temp_tile.img=create_bitmap(tileWidth,tileHeight);    
         
         blit(tset->img,temp_tile.img,Xmin,Ymin,0,0,tileWidth,tileHeight);  
            
         tset->tile.push_back(temp_tile);   

         Xmin=Xmin+tileWidth;
         
         temp_id++;
         
         P++;  
         
         
       }
       
     Ymin=Ymin+tileHeight;
     Xmin=0; 
    }   
	
}















void setDados(Layer *layer, const char *dados, bool gzip){
	int len;
	z_stream strm;          //< Estrutura para inflate.
	unsigned char *in=NULL; //< Buffer de entrada para inflate.

	if(layer->dados)
		delete[] layer->dados;

	if( gzip ){
		// Procedimento para realizar o inflateInit.
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		if( inflateInit2(&strm, 15|32)!=Z_OK ) //> 15|32 => 101111
			return;

		len = contBase64_decode(dados);
		strm.next_in = in = base64_decode((unsigned char*)dados, len, &len);
		if(!in){
			inflateEnd(&strm);
			return;
		}
		strm.avail_in = len;

		layer->dados = new unsigned int[layer->width * layer->height];
		strm.avail_out = layer->width * layer->height * 4;
		strm.next_out = (Bytef*)layer->dados;
		inflate(&strm, Z_NO_FLUSH);

		inflateEnd(&strm);
		delete[] in;
	}else{
		len = layer->width * layer->height * 4;
		layer->dados = (unsigned int*) base64_decode((unsigned char*)dados, len, &len);
	}
}




void readLayer(Layer *layer, xmlNode *root, xmlXPathContext *ctxt){
	xmlNode *no;
	xmlChar *dados;

	ctxt->node = root;
	layer->name = getString(root, "name");
	layer->width   = getInt(root, "width");
	layer->height  = getInt(root, "height");
	layer->xOffset  = getInt(root, "xoffset");
	layer->yOffset  = getInt(root, "yoffset");

	no = getNo(ctxt, "data");
	if( getString(no, "encoding")!="base64" ){
		printf("Layer %s: Dados nao se encontram em base64.\n", layer->name.c_str());
		return;
	}
	dados = xmlNodeGetContent(no);
	setDados(layer, (const char*)dados, getString(no, "compression")=="gzip" );
	xmlFree(dados);
}

























void readMap(xmlNode *root, xmlXPathContext *ctxt){
	xmlNode *no;
	Tileset *tset  = NULL;
	Layer *layer   = NULL;

	ctxt->node = root;
	version = getString(root, "version");
	orientation = getString(root, "orientation");
	width  = getInt(root, "width");
	height = getInt(root, "height");
	tileWidth  = getInt(root, "tilewidth");
	tileHeight = getInt(root, "tileheight");



	for(no=root->children; no; no = no->next)
    {
		if(no->type == XML_ELEMENT_NODE)
        { //- seleciona apenas tag's
			if( strcmp((char*)no->name, "tileset")==0 ){
                tset = newTileset();
			    readTileset(tset, no, ctxt );//tset, 
				vTileset.push_back( tset );

			}else if( strcmp((char*)no->name, "layer")==0 ){
				layer = newLayer();
				readLayer( layer, no, ctxt );
				vLayer.push_back( layer );
				
			}
		}
	}


}	


	
	
bool load_XML(const char *file){
	if( access(file, F_OK) != 0 )
		throw FILE_NULL;

	xmlDoc *doc;           //< Documento XML.
	xmlXPathContext *ctxt; //< Contexto

	doc = xmlReadFile(file, NULL, XML_PARSE_NOBLANKS);
	if(doc == NULL)
		return 0;

	limpar();
	ctxt = xmlXPathNewContext(doc);
	readMap( xmlDocGetRootElement(doc), ctxt );

	xmlXPathFreeContext(ctxt);
	xmlFreeDoc(doc);

	return 1;
}
	
	

	
	

//void print(FILE *file=NULL){
//#define TAB(num) for(i=0; i<(num); i++) fprintf(file, " ")
//
//	if(!file)
//		file = stdout;
//
//	int i;
//	//PropertyIterator it;
//	TilesetIterator it2;
//	LayerIterator it3;
//
//	TAB(0);
//	fprintf(file, "<map version=\"%s\" orientation=\"%s\" width=\"%d\" height=\"%d\""
//		" tilewidth=\"%d\" tileheight=\"%d\">\n" ,version.c_str() ,orientation.c_str()
//		,width, height, tileWidth, tileHeight);
//
//	printProp(&lProperty, file, 1,false);
//
//	for(it2=lTileset.begin(); it2!=lTileset.end(); ++it2){
//		TAB(1);
//		fprintf(file, "<tileset name=\"%s\" firstgid=\"%d\" tilewidth=\"%d\""
//			" tileheight=\"%d\"", (*it2)->name.c_str(), (*it2)->firstGid
//			,(*it2)->tileWidth, (*it2)->tileHeight );
//		//if( (*it2)->lProperty.size() ){
//			fprintf(file, ">\n");
//			printProp(&(*it2)->lProperty, file, 2, true);
//			TAB(1); fprintf(file, "</tileset>\n");
//		//}else
//		//	fprintf(file, "/>\n");
//	}
//
//	for(it3=lLayer.begin(); it3!=lLayer.end(); ++it3){
//		TAB(1);
//		fprintf(file, "<layer name=\"%s\" width=\"%d\" height=\"%d\""
//			,(*it3)->name.c_str(), (*it3)->width, (*it3)->height );
//		if( (*it3)->xOffset )
//			fprintf(file, " xoffset=\"%d\"", (*it3)->xOffset);
//		if( (*it3)->yOffset )
//			fprintf(file, " yoffset=\"%d\"", (*it3)->yOffset);
//		//if( (*it3)->lProperty.size() ){
//			fprintf(file, ">\n");
//			printProp(&(*it3)->lProperty, file, 2,false);
//			TAB(1); fprintf(file, "</layer>\n");
//		//}else
//		//	fprintf(file, "/>\n");
//	}
//
//	TAB(0);
//	fprintf(file, "</map>\n");
//}
//	
//	




///*
// * Não é muito realista, mas ajuda a examinar o conteúdo.
// */
//void printProp(Property *lProp, FILE *file, int tab, bool id){
//	int i;
//	//PropertyIterator it;
//
//#define TAB(num) for(i=0; i<(num); i++) fprintf(file, " ")
//
//	//for(it=lProp->begin(); it!=lProp->end(); ++it){
//		TAB(tab); fprintf(file, "<property");
//		if(id)
//			fprintf(file, " id=\"%d\"", lProp->id);
//		fprintf(file, " name=\"%s\" value=\"%s\"/>\n"
//			,lProp->nome.c_str(), lProp->valor.c_str());
//	//}
//}	
//	
//	
//	
//	
	
	
//	/**
// * Quando se conhece o id global de um tile, esta é melhor forma obter
// * um tile para impressão.
// * @param tile Ponteiro do tile que será setado.
// * @param id Id global de um tile.
// * @return true, quando o tile obtido for vádido e false, quando for
// * inválido (0 ou tileOut).
// * @exception PTR_NULL Parâmetro tile passado incorretamente.
// */
//bool Mapa::getTile(Tile *tile, int id){
//	int i, w;
//	Tileset *tset;
//
//	if( !tile )
//		throw PTR_NULL;
//
//	tile->id = id;
//	if(!tile->id  || tile->id>=tileOut){
//		tile->img = NULL;
//		return 0;
//	}
//	for(i=nTileset-1; i>=0; i--){
//		tset = vTileset[i];
//		if( tset->firstGid <= tile->id )
//			break;
//	}
//
//	tile->img = tset->img;
//	i = tile->id - tset->firstGid;
//	w = tset->img->w / tset->tileWidth;
//	setTileXY(tset, i, tile->x, tile->y);
//	tile->ret.x = i % w * tset->tileWidth;
//	tile->ret.y = i / w * tset->tileHeight;
//	tile->ret.w = tset->tileWidth;
//	tile->ret.h = tset->tileHeight;
//	return 1;
//}
//
///**
// * Use esta função quando for montar seu mapa. A classe Mapa não tem
// * um metodo mágico para pintar todo o mapa mas esta função é tudo que
// * você precisa.
// * @param tile Ponteiro do tile que será setado.
// * @param x Coordenada x do mapa. Trata xOffset automaticamente.
// * @param y Coordenada y do mapa. Trata yOffset automaticamente.
// * @param idLayer Id ou posição da camada. A camada de baixo tem id 0.
// * @return true, quando o tile obtido for vádido e false, quando for
// * inválido (0 ou tileOut).
// * @exception PTR_NULL Parâmetro tile passado incorretamente.
// */
//bool Mapa::getTile(Tile *tile, int x, int y, int idLayer){
//	int i, w;
//	Tileset *tset;
//
//	if( !tile )
//		throw PTR_NULL;
//
//	tile->id = getId(x, y, idLayer);
//	if(!tile->id  || tile->id>=tileOut){
//		tile->img = NULL;
//		return 0;
//	}
//	for(i=nTileset-1; i>=0; i--){
//		tset = vTileset[i];
//		if( tset->firstGid <= tile->id )
//			break;
//	}
//
//	tile->img = tset->img;
//	i = tile->id - tset->firstGid;
//	w = tset->img->w / tset->tileWidth;
//	setTileXY(tset, i, tile->x, tile->y);
//	tile->ret.x = i % w * tset->tileWidth;
//	tile->ret.y = i / w * tset->tileHeight;
//	tile->ret.w = tset->tileWidth;
//	tile->ret.h = tset->tileHeight;
//	return 1;
//}
//
//	
	
	
	
};	
	
#endif
