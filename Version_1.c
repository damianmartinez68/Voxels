/*=========================================================================*
 *=Título: Proyecto Final: Voxels                                         =*
 *=Versión: 1.0                                                           =*
 *=Fecha de inicio:  5 de Septiembre de 2015                              =*
 *=Fecha de finalización: 11 de Diciembre de 2015                         =*
 *=Autor: Damián "Mad" Martínez; damian.e.martinez@gmail.com              =*
 *=Notas: El tamaño del cubo principal será el mismo en todos los niveles;=*
 *=Lo único que cambiará es la velocidad de los Voxels malos              =*
 *=Menú principal controlado por Mouse                                    =*
 *=========================================================================*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <time.h>

#define PX 950//900
#define PY 710//675
#define C 20//Numero de Voxels
#define T 22//Tamaño en pixeles de los voxels
#define XIc 200//Punto de inicio en X del contenedor
#define YIc 250//Punto de inicio en Y del contenedor
#define ESP 32//Espacio
#define DOWN 80//Flecha Abajo
#define UP 72//Flecha Arriba
#define LEFT 75//Flecha Izquierda
#define RIGHT 77//Flecha Derecha
#define ESC 27//Tecla Escape
#define ENTER 13

typedef struct{
 int iPuntos;
 char cJugador[30];
}TRecords;

typedef struct{
    int iX, iY, iCon, iRell, iEx;
}TCubo;

void PortadaS();//Dibuja la portada
void PinMenu();
void MScreen();//Menú principal
int  Option(int mX, int mY);//Regresa el lugar donde dió click
void Game(TRecords *info);//Funcion Juego
void PlayerS(TRecords *info,int tamano);//Recibe el nombre del jugador y lo guarda para los Records
void Instruc();//Muestra las instrucciones de juego
void RecordS();//Muestra los records y los jugadores Anteriores
void UI(TRecords *info, char Name[30]);//Interfaz de Usuario
void Cubo(int iPosx,int iPosy,int iCont,int iRelleno);//dibuja cubo
int Timer(clock_t ini);
void StartCont(TCubo cC[C][C][C]);//Inicializa el contenedor principal
void DrawCont(TCubo cC[C][C][C]);//Dibuja el Contenedor
char ingresadato();
void score(char scorename[30]);
void WRecord(TRecords info);

int main(){
    initwindow(PX, PY, "Voxels");
    PortadaS();
    getch();
    MScreen();
    closegraph();
}

/*Muestra la portada del juego*/
void PortadaS(){
    setcolor(15);
    settextstyle(8, HORIZ_DIR, 2);
    outtextxy(PX/2-(textwidth("Universidad Autónoma de San Luis Potosí")/2), 25,"Universidad Autónoma de San Luis Potosí");
    outtextxy(PX/2-(textwidth("Facultad de Ingeniería")/2), 75,"Facultad de Ingeniería");
    outtextxy(PX/2-(textwidth("Area de Computación e Infomática")/2), 125,"Área de Computación e Informática");
    outtextxy(PX/2-(textwidth("Estructuras de Datos y Algoritmos A")/2), 175,"Estructuras de Datos y Algoritmos A");
    setcolor(7);
    outtextxy(550, 620,"Martínez Ramírez Damián Eduardo");
    outtextxy(PX/2-(textwidth("Presione cualquier tecla para continuar")/2),500,"Presione cualquier tecla para continuar");
    settextstyle(3,HORIZ_DIR,8);
    setcolor(11);
    outtextxy(PX/2-(textwidth("Voxels")/2),315,"Voxels");
    return;
}

/*Funcion de Main Screen, muestra el menú principal*/
void MScreen(){
    int mX, mY, opt=0;
    TRecords Jugadorrecord;
    cleardevice();
    fflush(stdin);
    PinMenu();
    clearmouseclick(WM_LBUTTONDOWN);
    do{
        if(ismouseclick(WM_LBUTTONDOWN)){
            mX=mousex();
            mY=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            opt=Option(mX, mY);
            printf("%d", opt);
            cleardevice();
            fflush(stdin);

            switch(opt){
                case (1):
                    PlayerS(&Jugadorrecord,30);
                break;
                case (2):
                    Instruc();
                break;
                case (3):
                    score("Records.txt");
                break;
                default:
                    PinMenu();
                break;
            }
        }
    }while(opt!=4);
}

/*Regresa una opcion de acuerdo a donde dio click el usuario*/
int Option(int mX, int mY){
    int opt=0;
    if((mX>PX/2-(textwidth("Instrucciones")/2)) && (mX<PX/2+(textwidth("Instrucciones")/2)+10)){
        if((mY>PY/3-10) && mY<PY/3+50)
            opt=1;
        if((mY>PY/3*1.5-10) && mY<PY/3*1.5+50)
            opt=2;
        if((mY>PY/3*2-10) && mY<PY/3*2+50)
            opt=3;
        if((mY>PY/3*2.5-10) && mY<PY/3*2.5+50)
            opt=4;
    }
    return (opt);
}

/*Esta funcion recibe el nombre del jugador y lo guarda para los récords*/
void PlayerS(TRecords *info,int tamano){
    int pag=0;
    int npag=0;
    int pos=0; //posicion para el  caracter nulo
    char cLetra=0;
    char Name[30];
    (*info).cJugador[pos]='\0';
    do{
        setcolor(11);
        outtextxy(PX/2-(textwidth("Ingrese su nombre:")/2),PY/2-300,"Ingrese su nombre:");
        outtextxy(PX/2-(textwidth("Presione intro para continuar")/2),PY/2+300,"Presione intro para continuar");
        setcolor(15);
        strncpy(Name, (*info).cJugador, sizeof((*info).cJugador));
        outtextxy(PX/2-(textwidth(Name))/2,300,Name);//Area de captura de nombre
        cLetra=ingresadato();
        switch(cLetra){
            case ESP:
                if(pos>0){
                pos--;
                (*info).cJugador[pos]='\0';
                }
            break;
            case ENTER:
                cLetra=13;
            break;
            default:
                if(pos<tamano){
                    (*info).cJugador[pos]=cLetra;
                    pos++;
                    (*info).cJugador[pos]='\0';
                }
            break;
        }
        setvisualpage(npag);
        npag=!npag;
        setactivepage(npag);
    }while((cLetra!=13));
    Game(info);
}

/*Funcion que recibibe de letra por letra*/
char ingresadato(){
    char cCaracter;
    cCaracter=getch();
    if(cCaracter==0)
        cCaracter=getch();
    return(cCaracter);
}

/*Dibuja la Interfaz de Usuario en la Pantalla*/
void UI(TRecords info, char Name[]){
    char Score[30];
    sprintf(Score,"%d",info.iPuntos);
    setlinestyle(0,0,3);
    line(PX/8,0,PX/8,PY);
    settextstyle(8,HORIZ_DIR,1);
    setcolor(11);
    outtextxy(PX/40, PY/20*2,"TIEMPO:");
    outtextxy(PX/40, PY/20*7,"JUGADOR:");
    outtextxy(PX/40, PY/20*8, Name);
    outtextxy(PX/40, PY/20*16, "SCORE:");
    outtextxy(PX/40, PY/20*17, Score);

    setlinestyle(0,0,1);
}

/*Esta Función muestra en pantalla las Instrucciones*/
void Instruc(){
    settextstyle(3, HORIZ_DIR, 4);
    setcolor(7);
    outtextxy(PX/13,PY/10,"INSTRUCCIONES:");
    delay(300);
    outtextxy(PX/10,PY/9*2,"-Mueve el cubo azul con las teclas de dirección");
    delay(300);
    outtextxy(PX/10,PY/9*3,"-Dispara con Espacio");
    delay(300);
    outtextxy(PX/10,PY/9*4,"-Destruye los cubos Rojos");
    delay(300);
    outtextxy(PX/10,PY/9*5,"-Presiona ESC para terminar el juego");
    delay(300);
    outtextxy(PX/10,PY/9*8,"-Presiona cualquier tecla para Volver al menú");
    getch();
    MScreen();
}

/*Función que inicia el contenedor entero*/
void StartCont(TCubo cC[C][C][C]){
    int X,Y,Z;
    for(Z=0;Z<C;Z++){//profundidad
        for(Y=0;Y<C;Y++){ //renglon
            for(X=0;X<C;X++){ // columna
                cC[Z][Y][X].iX=XIc+X*T+Z*T/2;
                cC[Z][Y][X].iY=YIc+Y*T-Z*T/2;
                cC[Z][Y][X].iCon=7;
                cC[Z][Y][X].iRell=3;
                cC[Z][Y][X].iEx=0;
            }
        }
    }
}

/*Función que dibuja el Contenedor*/
void DrawCont(TCubo cC[C][C][C]){
    int X,Y,Z;
    for(Z=C-1;Z>=0;Z--){//profundidad (Z)
        for(Y=C-1;Y>=0;Y--){//columnas (Y)
            for(X=0;X<C;X++){//renglon (X)
                if(cC[Z][Y][X].iEx>0){
                    Cubo(cC[Z][Y][X].iX, cC[Z][Y][X].iY, cC[Z][Y][X].iCon, cC[Z][Y][X].iRell);
                }
            }
        }
    }
}

/*Función que dibuja los cubos*/
void Cubo(int iPosx,int iPosy,int iCont,int iRelleno){
    int A[8];
    setcolor(iCont);
    setfillstyle(SOLID_FILL,iRelleno);
    bar(iPosx,iPosy,iPosx+T,iPosy+T);
    rectangle(iPosx,iPosy,iPosx+T,iPosy+T);
    A[0]= iPosx;
    A[1]= iPosy;
    A[2]= iPosx+T/2;
    A[3]= iPosy-T/2;
    A[4]= iPosx+T+T/2;
    A[5]= iPosy-T/2;
    A[6]= iPosx+T;
    A[7]= iPosy;
    fillpoly(4,A);
    drawpoly(4,A);
    A[0]= iPosx+T;
    A[1]= iPosy;
    A[2]= iPosx+T+T/2;
    A[3]= iPosy-T/2;
    A[4]= iPosx+T+T/2;
    A[5]= iPosy+T/2;
    A[6]= iPosx+T;
    A[7]= iPosy+T;
    fillpoly(4,A);
    drawpoly(4,A);
}

/*Función del Juego Principal*/
void Game(TRecords *info){
    TCubo cC[C][C][C];
    int Xc=0,Yc=C-2,Zc=0;
    int Xd=0, Yd=C-2, Zd=0;
    int Xe=0, Ye=C, Ze=0;
    char cOp;
    char Name[30];
    int iColor;
    int iCont,iCont1;
    int idir;
    int npag=0;
    int n=9, nO=9, i=n-1;
    int n_dis=0;
    int data=0;
    int seg=0;
    time_t td_1, td_2;
    clock_t inicio, inicio2;
    inicio=clock();
    inicio2=clock();
    (*info).iPuntos=0;
    cleardevice();
    StartCont(cC);
    for(iCont1=0;iCont1<C;iCont1++){
        for(iCont=0;iCont<C;iCont++){
            cC[iCont1][C-1][iCont].iEx=1;
        }
    }
    strncpy(Name,(*info).cJugador,sizeof((*info).cJugador));
    cC[Zc][Yc][Xc].iRell=0;
    cC[Zc][Yc][Xc].iEx=1;
    cC[Zc][Yc][Xc].iRell=11;//Posicion inicial de cubo bueno

    do{
        cleardevice();
        UI(*info, Name);
        seg=Timer(inicio);
        DrawCont(cC);
        if(kbhit()){
            cC[Zc][C-2][Xc].iEx=0;
            cC[Zc][C-2][Xc].iRell=iColor;
            fflush(stdin);
            cOp=getch();
            switch(cOp){//mueve el cubo Azul- El Heroe :3
                case RIGHT:
                    if(Xc<C-1)
                        Xc++;
                    else
                        Xc=0;
                break;
                case LEFT:
                    if(Xc>0)
                        Xc--;
                    else
                        Xc=C-1;
                break;
                case UP:
                    if(Zc<C-1)
                        Zc++;
                    else
                        Zc=0;
                break;
                case DOWN:
                    if(Zc>0)
                        Zc--;
                    else
                        Zc=C-1;
                break;
                case ESP:
                    if(n_dis==0){
                        n_dis=1;
                         td_1=clock();
                        Zd=Zc;
                        Xd=Xc;
                    }
                break;
            }
            cC[Zc][C-2][Xc].iEx=1; //cubo bueno
            cC[Zc][C-2][Xc].iRell=11; //Color del cubo bueno
        }
        if(n_dis==1){
            td_2=clock();
            if(td_2-td_1>100){
                if(Yd>0){
                    Yd--;
                    cC[Zd][Yd-1][Xd].iEx=1; //disparo
                    cC[Zd][Yd-1][Xd].iRell=YELLOW;
                    cC[Zd][Yd][Xd].iEx=0;
                }else{
                 n_dis=0;
                 Yd=C-2;
                }
            }
        }
        if(Ze==C-1){
            cC[C-n][Ye][Xe].iEx=0;
            n--;
        }
        else{
            cC[Ze][Ye][Xe].iRell=RED;
            cC[Ze++][Ye][Xe].iEx=1;
            if(Ze-n>=0)
                cC[Ze-n][Ye][Xe].iEx=0;
            else
                cC[C-i--][Ye][Xe].iEx=0;
            if(i==0)
                i=n-1;
        }
        if(n==0){
            Ze=0;
            Xe--;
            if(Xe<0)
                Xe=C-1;
            n=9;
        }
        if(Yd==1){
            if((Zd==Ze)&&(Xd==Xe)){
                n-=1;
                printf("No. de cubos: %d\n", n);
                data+=100;
                printf("Score: %d\n",data);
                if(n==0)
                    n=nO;
            }
        }



        (*info).iPuntos=data;
        setvisualpage(npag);
        npag=!npag;
        setactivepage(npag);
    }while((cOp!=ESC)&& (seg<30));
    if(seg==30){
        setactivepage(0);
        outtextxy(PX/2-(textwidth("GAME OVER")/2), PY/2, "GAME OVER");
        setvisualpage(0);
        getch();
    }
    WRecord(*info);
    setactivepage(0);
    cleardevice();
    setvisualpage(0);
    cleardevice();
    PinMenu();
}

/*Funcion para leer los Scores*/
void score(char scorename[30]){
    cleardevice();
    char cOp=0;
    FILE *Arch;
    TRecords aux[5];
    char info[30];
    int i;
    Arch=fopen("Records.txt","r");
    cleardevice();
    setcolor(15);
    do{
    outtextxy(305,35,"RECORDS");
    outtextxy(300,450,"ESC PARA VOLVER");
    if(Arch==NULL) {
    settextstyle(8, HORIZ_DIR,6);
    outtextxy(300,400,"NADIE HA JUGADO");
    }
    else{
     outtextxy(100,100,"JUGADOR:");
     outtextxy(500,100,"PUNTUACION:");
     fgets(info, 30, Arch);
     for(i=0;i<5;i++)
       outtextxy(200,100+(i+1)*50,info);
    }
    cOp=getch();
   }while(cOp!=27);
   fclose(Arch);
   cleardevice();
   PinMenu();
}

/*Función para controlar el Reloj*/
int Timer(clock_t ini){
    clock_t actual;
    int seg,min;
    char cadena[10];
    setcolor(11);
    actual=clock();
    seg=(actual-ini)/CLK_TCK;
    min=seg/60;
    seg=seg%60;
    sprintf(cadena,"%02d:%02d",min,seg);
    outtextxy(PX/40,PY/20*3,cadena);
    return seg;
}

/*Función que pinta Menu*/
void PinMenu(){
    settextstyle(3,HORIZ_DIR,8);
    setcolor(11);
    outtextxy(PX/2-(textwidth("Menu Principal")/2), PY/10, "Menú Principal");
    setcolor(15);
    settextstyle(8, HORIZ_DIR, 5);
    bar3d(PX/2-(textwidth("Jugar")/2)-10, PY/3-10, PX/2+(textwidth("Jugar")/2)+10, PY/3+50,15,1);
    outtextxy(PX/2-(textwidth("Jugar")/2), PY/3, "Jugar");
    bar3d(PX/2-(textwidth("Instrucciones")/2)-10, PY/3*1.5-10, PX/2+(textwidth("Instrucciones")/2)+10, PY/3*1.5+50,15,1);
    outtextxy(PX/2-(textwidth("Instrucciones")/2), PY/3*1.5, "Instrucciones");
    bar3d(PX/2-(textwidth("Records")/2)-10, PY/3*2-10, PX/2+(textwidth("Records")/2)+10, PY/3*2+50,15,1);
    outtextxy(PX/2-(textwidth("Records")/2), PY/3*2, "Récords");
    bar3d(PX/2-(textwidth("Salir")/2)-10, PY/3*2.5-10, PX/2+(textwidth("Salir")/2)+10, PY/3*2.5+50,15,1);
    outtextxy(PX/2-(textwidth("Salir")/2), PY/3*2.5, "Salir");
}

/*Función Para escribir Records*/
void WRecord(TRecords info){
    FILE *Arch;
    char Punt[5];
    char InJug[30];

    sprintf(Punt,"%d",info.iPuntos);

    sprintf(InJug,"%s----------%s\n", info.cJugador, Punt);

    Arch=fopen("Records.txt", "a");
    if (Arch==NULL)
        perror("No se puede abrir Records.txt");
    else
        fputs(InJug,Arch);
    fclose(Arch);
}
