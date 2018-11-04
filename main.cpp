//JUEGO 1 (DE NAVES).
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<list>

using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    
    SetConsoleCursorPosition(hCon, dwPos);
}//void gotoxy

void OcultarCursor()
{
     HANDLE hCon;
     hCon = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO cci;
     cci.dwSize=1;
     cci.bVisible=FALSE;
     
     SetConsoleCursorInfo(hCon,&cci);         
}//void ocultarcursor

void pintar_limites()
{
     for(int i=2;i<78;i++)
     {
             gotoxy(i,3);
             printf("%c",205);
             gotoxy(i,32);
             printf("%c",205);
     }//for limites x
     for(int i=4;i<32;i++)
     {
             gotoxy(2,i);
             printf("%c",186);
             gotoxy(77,i);
             printf("%c",186);            
     }//for limites y
     gotoxy(2,3);
     printf("%c",201);
     gotoxy(2,32);
     printf("%c",200);
     gotoxy(77,3);
     printf("%c",187);
     gotoxy(77,32);
     printf("%c",188);
          
}//void pintar_limites

class NAVE
{
      int x,y,salud,vidas;
public:
       NAVE(int _x,int _y,int _salud,int _vidas):x(_x),y(_y),salud(_salud),vidas(_vidas)
{
}//constructor nave::nave
       int X()
       {
           return x;
       }//int X
       int Y()
       {
           return y;
       }//int Y
       int VIDAS()
       {
           return vidas;
       }//int VIDAS
       void msalud()
       {
            salud--;
       }//void msalud
       void pintar();
       void borrar();
       void mover();
       void pintar_salud();
       void morir();
};//clase nave

void NAVE::pintar()
{
     gotoxy(x+2,y);
     printf("%c",30);
     gotoxy(x+1,y+1);
     printf("%c%c%c",40,207,41);
     gotoxy(x,y+2);
     printf("%c%c %c%c",30,190,190,30);
}//void nave pintar

void NAVE::borrar()
{
     gotoxy(x,y);
     printf("     ");
     gotoxy(x,y+1);
     printf("     ");
     gotoxy(x,y+2);
     printf("     ");
}//void nave borrar

void NAVE::mover()
{
        if(kbhit())
                     {
                                char tecla=getch();
                                borrar();
                                if(tecla==IZQUIERDA&&x>3)x--;
                                if(tecla==DERECHA&&x+5<77)x++;
                                if(tecla==ARRIBA&&y>4)y--;
                                if(tecla==ABAJO&&y+3<32)y++;
                                
                                pintar();
                                pintar_salud();
                     }//if
}//void nave mover

void NAVE::pintar_salud()
{
     gotoxy(50,2);
     printf("Vidas %d",vidas);
     gotoxy(64,2);
     printf("Salud");
     gotoxy(70,2);
     printf("      ");
     for(int i=0;i<salud;i++)
     {
             gotoxy(70+i,2);
             printf("%c",220);
     }//for
}//void nave pintar_salud

void NAVE::morir()
{
     if(salud==0)
     {
                 borrar();
                 gotoxy(x+1,y);
                 printf("**");
                 gotoxy(x,y+1);
                 printf("****");
                 gotoxy(x+1,y+2);
                 printf("**");
                 Sleep(200);
                 borrar();
                 gotoxy(x,y);
                 printf("*  *");
                 gotoxy(x,y+1);
                 printf("*++*");
                 gotoxy(x,y+2);
                 printf("*  *");
                 Sleep(200);
                 borrar();
                 vidas--;
                 salud=3;
                 pintar_salud();
                 pintar();                 
     }//if
}//void nave morir

class ASTEROIDE
{
      int x,y;
public:
       ASTEROIDE(int _x, int _y):x(_x),y(_y)
       {
       }//constructor asteroide::asteriode
       int X()
       {
           return x;
       }//int X
       int Y()
       {
           return y;
       }//int Y
       void pintar();
       void mover();
       void colision(class NAVE &N);      
};//class asteriode

void ASTEROIDE::pintar()
{
     gotoxy(x,y);
     printf("%c",184);
}//void asteroide::pintar

void ASTEROIDE::mover()
{
     gotoxy(x,y);
     printf(" ");
     y++;
     if(y>31)
     {
             x=rand()%72+4;
             y=4;
     }//if
     pintar();
}//void asteroide::mover

void ASTEROIDE::colision(class NAVE &N)
{
     if(x>=N.X()&&x<N.X()+5&&y>=N.Y()&&y<=N.Y()+2)
     {
              N.msalud();
              N.borrar();
              N.pintar();
              N.pintar_salud();
              x=rand()%72+4;
              y=4;
     
     }//if
}//void ASTEROIDE::colision

class BALA
{
      int x,y;
public:
       BALA(int _x,int _y):x(_x),y(_y)
       {
       }//constructor bala::bala
       int X()
       {
           return x;
       }//int X
       int Y()
       {
           return y;
       }//int Y
       void mover();
       bool fuera();
};//class bala

void BALA::mover()
{
     gotoxy(x,y);
     printf(" ");
     y--;
     gotoxy(x,y);
     printf("%c",186);     
}//void bala::mover

bool BALA::fuera()
{
     if(y<=4)return true;
     return false;
 }//bool bala::fuera

int main()
{
    SetConsoleTitle("JUEGO_1.");
    char opc;
    cout<<"DESEAS INICIAR EL JUEGO 1[SI] 0[NO] \n";
    cin>>opc;
   
    if(opc=='1')
    {
                char repetir='1'; 
     while(repetir=='1')
     {            
                system("cls");    
    OcultarCursor();
    pintar_limites();
    NAVE N(35,29,3,3);
    N.pintar();
    N.pintar_salud();
    
    list<ASTEROIDE*>A;
    list<ASTEROIDE*>::iterator itA;
    for(int i=0;i<5;i++)
    {
            A.push_back(new ASTEROIDE(rand()%75+3,rand()%5+4));
    }//for
    list<BALA*>B;
    list<BALA*>::iterator it;
    
    int puntos=0;
    bool game_over=false;
    while(!game_over)
    {             
                  gotoxy(2,33);
                  printf("LAMOS INDUSTRIES %c. COPYRIGHT %c 2014.",169,184);
                  gotoxy(65,33);
                  printf("V 1.0.0");
                  gotoxy(1,1);
                  printf("MUEVES LA NAVE CON LAS FLECHAS Y DISPARAS CON 'A'"); 
                  gotoxy(4,2);
                  printf("PUNTOS %d",puntos); 
                  if(kbhit())
                  {
                             char tecla=getch();
                             if(tecla=='a'||tecla=='A')
                             B.push_back(new BALA(N.X()+2,N.Y()-1));
                  }//if
                  
                  for(it=B.begin();it!=B.end();it++)
                  {
                          (*it)->mover();
                          if((*it)->fuera())
                          {
                                          gotoxy((*it)->X(),(*it)->Y());
                                          printf(" ");
                                          delete(*it);
                                          it=B.erase(it);
                          }//if
                  }//for
                     
                  for(itA=A.begin();itA!=A.end();itA++)
                  {
                        (*itA)->mover();
                        (*itA)->colision(N);
                  }//for
                  
                  for(itA=A.begin();itA!=A.end();itA++)
                  {
                        for(it=B.begin();it!=B.end();it++)
                        {
                              if((*itA)->X()==(*it)->X()&&((*itA)->Y()+1==(*it)->Y()||(*itA)->Y()==(*it)->Y()))
                              {
                                   gotoxy((*it)->X(),(*it)->Y());
                                   printf(" ");
                                   delete(*it);
                                   it=B.erase(it);
                                   
                                   A.push_back(new ASTEROIDE(rand()%75+3,4));
                                   gotoxy((*itA)->X(),(*itA)->Y());
                                   printf(" ");
                                   delete(*itA);
                                   itA=A.erase(itA);
                                   
                                   puntos++;
                              }//if
                        }//for
                  }//for
                  
                  if(N.VIDAS()==0)game_over=true;
                  N.morir();
                  N.mover();
                  Sleep(30);
                                    
    }//while(gameover)
    system("cls");
    cout<<"deseas repetir el juego 1[si] 0[no]\n";
    cin>>repetir;
   }//while(repetir)
   
    system("cls");
    cout<<"pulsa una tecla para salir";
}//if general

else
if(opc=='0')
cout<<"pulsa una tecla para salir";
    getch();
}//int main()
