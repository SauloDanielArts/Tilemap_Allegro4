#include <cstdlib>
#include "mapa_xml.h"



/*

MAPA mapa;
	
	try{
		if( !mapa.load_XML("map.tmx") )
			printf("Erro ao carregar arquivo 'mapa.tmx'.\n");
	}catch(Mapa::Exception e){
		printf("Arquivo 'mapa.tmx' nao existe.\n");
	}
	mapa.print();



*/















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

	//! Obtem a posi��o do caractere na base64.
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
	 * @brief Codifica dados bin�rios (base256) em base64.

	 * Esta fun��o foi originalmente escrita pela equipe do PHP:\n
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
	 * @brief Decodifica dados na base64 em bin�rio (base256).

	 * Esta fun��o foi originalmente escrita pela equipe do PHP:\n
	 * PHP HTML Embedded Scripting Language Version 3.0
	 * Copyright (c) 1997,1998 PHP Development Team (See Credits file)
	 * @param string String base64 de entrada. Caracteres inv�lidos ser�o ignorados.
	 * @param length Quantidade de mem�ria a ser alocada para o buffer de sa�da.
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

////============================================================================












MAPA::MAPA()//!< Contrutor.
       {
       width = height = tileWidth = tileHeight = x = y= 0;
       }  
	 
MAPA::~MAPA(){limpar();}

MAPA::Tileset *MAPA::newTileset(){
	Tileset *tset = new Tileset;
	tset->firstGid = 0;
	tset->palheta=NULL;
	tset->img_name ="";
	tset->NT=0;

	return tset;
}

void MAPA::delTileset(Tileset *tset){
	delete tset;
}

MAPA::Layer *MAPA::newLayer(){
	Layer *layer = new Layer;
	layer->width = 0;
	layer->height = 0;
	layer->dx = 0;
	layer->dy = 0;
	layer->dados = NULL;
	
	return layer;
}

void MAPA::delLayer(Layer *layer){
	if(layer->dados)
		delete[] layer->dados;

	delete layer;
}	

void MAPA::limpar(){
	version.clear();
	orientation.clear();
	width = height = tileWidth = tileHeight = 0;
}	
	
	
	
void MAPA::readTileset(Tileset *tset, xmlNode *root, xmlXPathContext *ctxt){
    ctxt->node = root;
	tset->name = getString(root, "name");
	tset->firstGid  = getInt(root, "firstgid");
	
	tset->img_name = getString( getNo(ctxt, "image"), "source").c_str();

    tset->palheta = load_bitmap( tset->img_name.c_str() ,NULL);
    
    tset->NT= (tset->palheta->h/tileHeight)*(tset->palheta->w/tileWidth);
    
//    Tile temp_tile;
//
//int temp_id=tset->firstGid;
//
//int i,j;
//int P=0;
//int Xmin=0;
//int Ymin=0;
//
//
//    //prenche o vetorcom dos tiles
//    for( i=0;i<(tset->palheta->h/tileHeight);i++)
//    {
//       for(j=0;j<(tset->palheta->w/tileWidth) ;j++)
//       {
//         temp_tile.id=temp_id;
//         temp_tile.img=create_bitmap(tileWidth,tileHeight);    
//         
//         blit(tset->palheta,temp_tile.img,Xmin,Ymin,0,0,tileWidth,tileHeight);  
//            
//         tset->tile.push_back(temp_tile);   
//
//         Xmin=Xmin+tileWidth;
//         
//         temp_id++;
//         
//         P++;  
//         
//         
//       }
//       
//     Ymin=Ymin+tileHeight;
//     Xmin=0; 
//    }   
	
}



//================================================================================











void MAPA::setDados(Layer *layer, const char *dados, bool gzip){
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




void MAPA::readLayer(Layer *layer, xmlNode *root, xmlXPathContext *ctxt){
	xmlNode *no;
	xmlChar *dados;

	ctxt->node = root;
	layer->name = getString(root, "name");
	layer->width   = getInt(root, "width");
	layer->height  = getInt(root, "height");

	no = getNo(ctxt, "data");
	if( getString(no, "encoding")!="base64" ){
		printf("Layer %s: Dados nao se encontram em base64.\n", layer->name.c_str());
		return;
	}
	dados = xmlNodeGetContent(no);
	setDados(layer, (const char*)dados, getString(no, "compression")=="gzip" );
	xmlFree(dados);
}

























void MAPA::readMap(xmlNode *root, xmlXPathContext *ctxt){
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


	
	
bool MAPA::load_XML(const char *file){
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
	
	

	
	
	



BITMAP* MAPA::getTile(BITMAP* palheta, int p){//metodo 2

int l=palheta->h/tileHeight;
int c=palheta->w/tileWidth;

if(p>=1 || p<=l*c)
{
BITMAP* temp = create_bitmap(tileWidth,tileHeight);


int pos=0;


for(int i=0;i<l;i++)
   for(int j=0;j<c;j++)
     {
       
        if(pos==p)    
           { blit(palheta, temp, j*tileWidth,i*tileHeight,0,0,tileWidth,tileHeight);
            return temp; 
           } 
            
         pos++;       
           
      }                                                                                                                                                                                      

}
else
	return NULL;
}

		

	
	
	
	
	
	

	
	
	
	
	
	
	
//mais lento	//nap muito viavel
void MAPA::Fill_Map(BITMAP *Tela,int nLayer,float dx,float dy){

	
	
	int t,g=0,p;
    long cont=0;

long Xmax=x*dx;
long Ymax=y*dy;


long DX=x;

for(p=0;p<height*width;p++)
     {
     if((Xmax-tileWidth>=-tileWidth*2) && (Xmax-tileWidth*2<=Tela->w) && (Ymax-tileHeight>=-tileHeight*2) && (Ymax-tileHeight*2<=Tela->h))       
       for(g=0;g<vTileset.size();g++)
        {for(t=vTileset[g]->firstGid;t<vTileset[g]->NT+vTileset[g]->firstGid;t++)
				{	
                    	if(t==vLayer[nLayer]->dados[p])
                       {                        
                         	 draw_sprite(Tela,getTile(vTileset[g]->palheta,t-vTileset[g]->firstGid),Xmax,Ymax);	
                           //rect(Tela,Xmax,Ymax,Xmax+tileWidth-1,Ymax+tileHeight-1,makecol(255,0,0));
						}		
            }		
        }
        
        cont++;
               Xmax=Xmax+tileWidth;
        if(cont==width)
              {
			   Xmax=DX;
			   Ymax=Ymax+tileHeight;
			   cont=0;			   
              }
     }
	
}
	

	
	
	
//mais rapido	
void MAPA::Fill_Map(BITMAP *Tela,int nLayer,int nTileset,float dx,float dy){

	
	
	int t,g,l,c=0;
    long cont=0;
    
    
    int Lon_Xi_MAP=((x)/-tileWidth);	
	int Lon_Yi_MAP=((y)/-tileHeight);

    //  o que esta no ponto final da tela
	int  Lon_Xf_MAP= Lon_Xi_MAP +(Tela->w/tileWidth);
	int Lon_Yf_MAP= Lon_Yi_MAP +(Tela->h/tileHeight);
    

long Xmax=(x+(Lon_Xi_MAP*tileWidth));
long Ymax=(y+(Lon_Yi_MAP*tileHeight));

long DX=Xmax;




 printf("xi: %d; yi: %d; xf: %d; yf: %d \n",Lon_Xi_MAP,Lon_Yi_MAP,Lon_Xf_MAP,Lon_Yf_MAP); 



for(l=(y/-tileHeight)*dy;l<=(y/-tileHeight)*dy+(Tela->h/tileHeight);l++)
 for(c=(x/-tileWidth)*dx;c<=(x/-tileWidth)*dx+(Tela->w/tileWidth);c++)
     {
         //teste ddos componentes da matrix
         //printf("%3d ",vLayer[nLayer]->dados[l*width+c]);	
         
         
         
         for(t=vTileset[nTileset]->firstGid;t<vTileset[nTileset]->NT+vTileset[nTileset]->firstGid;t++)
				{	
                    if(t==vLayer[nLayer]->dados[l*width+c])//l*width+c
                       {                        
                         	draw_sprite(Tela,getTile(vTileset[nTileset]->palheta,t-vTileset[nTileset]->firstGid),Xmax,Ymax);	
                         //   rect(Tela,Xmax,Ymax,Xmax+tileWidth-1,Ymax+tileHeight-1,makecol(255,0,0)); 
                        }		
                }
          
        cont++;
               Xmax=(Xmax+tileWidth);
       if(cont==(Tela->w/tileWidth)+1)
              {
			   Xmax=DX;
			   Ymax=(Ymax+tileHeight);
			   cont=0;
               //printf("\n");
               		   
              }   
              
     }
     	
    system("cls"); 	
}	
	
	
	
	
	
long MAPA::get_x()	
	{
     return x;    
    }
	
long MAPA::get_y()
	{
     return y;    
    }	
	
	
void MAPA::set_x(int X)	
	{
     x=X;    
    }	
    
void MAPA::set_y(int Y)	
	{
     y=Y;    
    }	
    
void MAPA::set_xy(int X, int Y)
    {
      x=X;  
      y=Y;   
    }    
	
	
int MAPA::get_width()
	{
     return width;    
    }		

int MAPA::get_height()
	{
     return height;    
    }	


int MAPA::get_tileWidth()
	{
     return tileWidth;    
    }		

int MAPA::get_tileHeight()
	{
     return tileHeight;    
    }		
	
	
	
	
	
	
	
	
	
	
void MAPA::scoll_mt(BITMAP *Tela ,int v)//-teste de sroll do tile_map 
{//modificar para ter interacao com o pesonagen do jogo
   		     //acrasentar entrada de parametros para modifica velocidade de deslocamento do mapa

             

           if(key[KEY_UP] && y <= -1 )
               {
                y += v;
               }
               
              if((y >= -1 ))// && ery <=-1)
                  {
                    y = 0;
                  } 
               

            if(key[KEY_DOWN])
            {
             y -= v;
            }     
             if(y <= -((tileHeight*height) -Tela->h))
               {
                y = -((tileHeight*height) -Tela->h);
               }
               
                
             if(key[KEY_LEFT])
               {
                x += v;
               }
                if(x >= -1)// && er <=-1)
                  {
                    x = 0;
                  }


            if(key[KEY_RIGHT])
            {
             x -= v;
            }           
             if(x <= -((tileWidth*width) -Tela->w))
               {
                x = -((tileWidth*width) -Tela->w);
               }   
                
}  
	
	
	
	
int MAPA::size_vTileset(){return vTileset.size(); }

int MAPA::size_vLayer(){return vLayer.size(); }	
	
	
	
	
	
	
	
	
	
	
