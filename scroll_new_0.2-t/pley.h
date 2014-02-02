#ifndef PLEY_H
#define PLEY_H

int Vidas=10;

int Px=0;
int Py=0;

void gravidade(int g)
     {
	  Py+=g;		
	 }


void EnqPlay_Scrull(BITMAP *Buffer_esterno,int Color,int Vx_a,int Vy1_a,int Vy2_a,int Vx_b,int Vy1_b,int Vy2_b,int Hx1_a,int Hy_a,int Hx2_a ,int Hx1_b,int Hy_b,int Hx2_b,int V)
		{
		if(V){	
		 vline(Buffer_esterno,Vx_a,Vy1_a,Vy2_a,Color);
		 vline(Buffer_esterno,Vx_b,Vy1_b,Vy2_b,Color);
		 hline(Buffer_esterno,Hx1_a,Hy_a,Hx2_a,Color);
		 hline(Buffer_esterno,Hx1_b,Hy_b,Hx2_b,Color);}
		 }

class Play
       {
		public:
			void Personagen(BITMAP *Buffer_externo,BITMAP *sprite)
			{
			 draw_sprite(Buffer_externo, sprite, Px, Py);  	
			}
			
			void Mov_Play()
			{
			 if(key[KEY_UP])
		        Py-=6;
		     if(key[KEY_DOWN])
		        Py+=6;    
		     if(key[KEY_LEFT]) 
		        Px-=6; 
	         if(key[KEY_RIGHT])
                Px+=6; 
			}
			
       };


#endif
