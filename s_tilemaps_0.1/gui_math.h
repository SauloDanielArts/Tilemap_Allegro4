#ifndef GUI_MATH
#define GUI_MATH

//vetor bidimencional que guarda valores inteiros
struct Vector2
{
 int x;
 int y;   
}

struct Vector2i
{
 long x;
 long y;   
}

struct Vector2f
{
 double x;
 double y;   
}

//class SPRIT
//{
// private:
//        int x;
//        int y;
//        BITMAP *quadros[];
//        
// public:          
//    SPRIT(BITMAP *img,int collums, int rows)
//    {
//        
//    }
//    
//    
//};

//----colisoes basicas ente figuras geometricas simples---

//implementar

//--------------------------------------------------------




//
//    *  GSMT_INFO: a mensagem � apenas informativa.
//    * GSMT_WARNING: a mensagem � de alerta ao usu�rio.
//    * GSMT_ERROR: a mensagem � de erro.
//

//
// float gsGetDist2(GS_VECTOR2 P0, GS_VECTOR2 P1)
//
//    * Retorna o valor da dist�ncia em linha reta, medida em pixels, entre o ponto P0 e P1.

//
// float gsRadianToDegree(const float fAngle)
//
//    * Retorna o �ngulo em radianos fAngle convertido para graus de 0� a 360�.






//
// float gsDegreeToRadian(const float fAngle)
//
//    * Retorna o valor de �ngulo em graus (de 0� a 360�) convertido para radianos.



//
//bool  GS_SPRITE::SetupSpriteRects(int collums, int rows)
//Esta fun��o � utilizada caso o bitmap do atual sprite possuir mais de um sprite em sua composi��o. Para isso, os sprites precisam possuir a mesma altura e mesma largura, como mostra a imagem � seguir.
//
//Aqui temos um sprite 4x4 com 16 frames de igual dimens�o. A fun��o SetupSpriteRects cria estas divis�es para serem posteriormente usadas para anima��o. Em collums deve ser especificada a quantidade de colunas de sprites e em rows a quantidade de linhas. A pr�pria fun��o se encarregar� de dividi-la igualmente. Para selecionar os quadros espec�ficos, utilize GS_SPRITE::SetRect(int collum, int row).
//

//
//GS_VECTOR2  GS_SPRITE::GetBitmapSizeF()
//Retorna um vetor de valores float com a largura (x) e altura (y), em pixels, do bitmap do sprite.


//criar camadas de rofundidades de tela----------- f(1-10)



















#endif
