/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include <GL/glu.h> /**/
#include <GL/glut.h> /**/
#include <stdio.h> /**/ 
#include <math.h> /**/	
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Punto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct{/**/	int x;/**/	int y;/**/}Punto;/**/Punto T[3];/**/
void setPuntosIniciales(int x, int y, int i){/**/	T[i].x=x;/**/	T[i].y=y;/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Variables Globales >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int GLOBAL=0;/**/int TAMPINCEL=15;/**/int TIPOPINCEL=0;/**/int ESPECIAL=0;/**/int BORRAR=0;/**/
float ROJO=10;/**/float VERDE=10;/**/float AZUL=10;/**/int ANCHO=480;/**/int ALTO=480;/**/int HERR=140;/**/int H=35;/**/
char opp[4][4]={{'u','y','+','-'},{'0','0','m','n'},{'t','9','k','j'},{'g','b','o','i'},};
int colores[6][4][3]={{{10,0,0},{0,10,0},{0,0,10},{10,10,10}},{{10,0,5},{0,10,5},{0,5,10},{10,10,5}},
						{{10,5,0},{5,10,0},{5,0,10},{10,5,10}},{{10,10,0},{0,10,10},{10,0,10},{10,5,5}},
						{{5,5,0},{0,5,5},{5,0,5},{5,5,5}},{{5,0,0},{0,5,0},{0,0,5},{0,0,0}}};/**/
GLubyte barraHerr[140][480][4],canvasMAX[480][480][4],borrar[1][1][4],borrar2[1][1][4],borrar3[1][1][4];/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Dibujar punto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void aRectaPuntoMedio(int x0,int y0,int x1,int y1){/**/
	int h,k,incr_e,incr_ne,d,x,y,ux=1,uy=1;/**/	int ic=0;/**/	h=x0;/**/	k=y0;/**/	x1=x1-h;/**/
	y1=y1-k;/**/	if(y1<0){	uy=-1;/**/	y1=-y1;/**/	}/**/	if(x1<0){/**/	ux=-1;/**/	x1=-x1;/**/	}/**/
	if(x1<y1){/**/	ic=1;/**/	x1=x1+y1;/**/	y1=x1-y1;/**/	x1=x1-y1;/**/	}/**/	d=2*y1-x1;/**/
	incr_e=y1*2;incr_ne=(y1-x1)*2;/**/	x=0;/**/	y=0;/**/	glBegin(GL_POINTS);/**/	glVertex2f(h,k);/**/
	while(x<x1){/**/	if(d<=0){/**/	d+=incr_e;/**/	}/**/	else{/**/	d+=incr_ne;/**/	y++;/**/}/**/
		x++;/**/	int px,py;/**/	if(ic){px=y;py=x;/**/	}/**/	else{/**/	px=x;/**/	py=y;/**/	}/**/
		px=ux*px;/**/	py=uy*py;/**/	glVertex2f(px+h,py+k);/**/	}/**/	glEnd();/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Rectangulo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void rectangulo(){/**/
	aRectaPuntoMedio(T[2].x,T[2].y,T[2].x,T[1].y);/**/	aRectaPuntoMedio(T[2].x,T[1].y,T[1].x,T[1].y);/**/
	aRectaPuntoMedio(T[1].x,T[1].y,T[1].x,T[2].y);/**/	aRectaPuntoMedio(T[1].x,T[2].y,T[2].x,T[2].y);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void relleno(){/**/
	int y,n,m;/**/	if(T[2].y<T[1].y){/**/	n=T[2].y;/**/	m=T[1].y;/**/	}/**/
	else{n=T[1].y;/**/	m=T[2].y;/**/	}/**/	for(y=n;y<=m;y++){/**/	aRectaPuntoMedio(T[2].x,y,T[1].x,y);/**/}/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Funciones Con Colores >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void circunferencia(){
int i,j,n,xx,yy;
float ii,jj,hh,alfa;
n=TAMPINCEL*2+1;
xx=T[1].x-TAMPINCEL-1;
yy=T[1].y-TAMPINCEL-1;
GLubyte pincelito[n][n][3];
GLubyte canvas1[n][n][4];
glReadPixels(xx,yy,n,n,GL_RGBA,GL_UNSIGNED_BYTE,canvas1);
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){//i=j credits By Luquitas >:3
			ii=i-TAMPINCEL;
			jj=j-TAMPINCEL;	
			hh=sqrt(ii*ii+jj*jj);
			alfa=(TAMPINCEL-((hh*TIPOPINCEL)/2))/TAMPINCEL;
			if(BORRAR==1){
					pincelito[i][j][0] = borrar[0][0][0];
					pincelito[i][j][1] = borrar[0][0][1];
					pincelito[i][j][2] = borrar[0][0][2];
					
					pincelito[j][i][0] = borrar[0][0][0];
					pincelito[j][i][1] = borrar[0][0][1];
					pincelito[j][i][2] = borrar[0][0][2];
			}
			else{
				if(alfa>=0 && hh<=TAMPINCEL){
					pincelito[i][j][0] = (GLubyte)(canvas1[i][j][0]*(1-alfa) + (alfa*(ROJO*25.5)));
					pincelito[i][j][1] = (GLubyte)(canvas1[i][j][1]*(1-alfa) + (alfa*(VERDE*25.5)));
					pincelito[i][j][2] = (GLubyte)(canvas1[i][j][2]*(1-alfa) + (alfa*(AZUL*25.5)));
					
					pincelito[j][i][0] = (GLubyte)(canvas1[j][i][0]*(1-alfa) + (alfa*(ROJO*25.5)));
					pincelito[j][i][1] = (GLubyte)(canvas1[j][i][1]*(1-alfa) + (alfa*(VERDE*25.5)));
					pincelito[j][i][2] = (GLubyte)(canvas1[j][i][2]*(1-alfa) + (alfa*(AZUL*25.5)));
				}
				else	{
					pincelito[i][j][0] = canvas1[i][j][0];
					pincelito[i][j][1] = canvas1[i][j][1];
					pincelito[i][j][2] = canvas1[i][j][2];
					
					pincelito[j][i][0] = canvas1[j][i][0];
					pincelito[j][i][1] = canvas1[j][i][1];
					pincelito[j][i][2] = canvas1[j][i][2];
				}
			}
		}
	}
glRasterPos2i(xx,yy);
glDrawPixels(n,n,GL_RGB,GL_UNSIGNED_BYTE,pincelito);
}
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorActual(){/**/
	glRasterPos2i(480,0);/**/	glDrawPixels(140,480,GL_RGBA,GL_UNSIGNED_BYTE,barraHerr);/**/
	glColor3f(ROJO/10, VERDE/10, AZUL/10);/**/	setPuntosIniciales(ANCHO,0,0);/**/
	setPuntosIniciales(ANCHO+HERR/2,(HERR/2)-5,1);/**/	circunferencia();/**/	glPointSize(1);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void especial(){/**/	glReadPixels(0,0,ANCHO,ALTO,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void cambiarFondo(){
	glReadPixels(ANCHO+HERR/2,(HERR/2)-5,1,1,GL_RGBA,GL_UNSIGNED_BYTE,borrar2);
	especial();
	int i,j;
	for(i=0;i<480;i++){
		for(j=0;j<480;j++){
			if(borrar[0][0][0]==canvasMAX[i][j][0] && borrar[0][0][1]==canvasMAX[i][j][1] && borrar[0][0][2]==canvasMAX[i][j][2]){
				canvasMAX[i][j][0]=borrar2[0][0][0];/**/
				canvasMAX[i][j][1]=borrar2[0][0][1];/**/
				canvasMAX[i][j][2]=borrar2[0][0][2];/**/
			}
		}
	}
	glRasterPos2i(0,0);
	glDrawPixels(480,480,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);
	glReadPixels(ANCHO+HERR/2,(HERR/2)-5,1,1,GL_RGBA,GL_UNSIGNED_BYTE,borrar);
	glClearColor(ROJO/10,VERDE/10,AZUL/10,0.0);
	colorActual();
}
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void cambiarFondo2(){
	especial();
	int i,j;
	for(i=0;i<480;i++){
		for(j=0;j<480;j++){
			if(borrar[0][0][0]==canvasMAX[i][j][0] && borrar[0][0][1]==canvasMAX[i][j][1] && borrar[0][0][2]==canvasMAX[i][j][2]){
				canvasMAX[i][j][0]=borrar3[0][0][0];
				canvasMAX[i][j][1]=borrar3[0][0][1];
				canvasMAX[i][j][2]=borrar3[0][0][2];
			}
		}
	}
	glRasterPos2i(0,0);
	glDrawPixels(480,480,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);
	borrar[0][0][0]=borrar3[0][0][0];
	borrar[0][0][1]=borrar3[0][0][1];
	borrar[0][0][2]=borrar3[0][0][2];
	glClearColor(ROJO/10,VERDE/10,AZUL/10,0.0);
	colorActual();
}
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void limpiarCanvas(){/**/	glClear(GL_COLOR_BUFFER_BIT);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorRojo(){/**/BORRAR=0;/**/ROJO=10;/**/VERDE=0;/**/AZUL=0;/**/glColor3f(1.0f,0.0f,0.0f);/**/	colorActual();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorVerde(){/**/BORRAR=0;/**/ROJO=0;/**/VERDE=10;/**/AZUL=0;/**/glColor3f(0.0f,1.0f,0.0f);/**/colorActual();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorAzul(){/**/BORRAR=0;/**/ROJO=0;/**/VERDE=0;/**/AZUL=10;/**/glColor3f(0.0f,0.0f,1.0f);/**/colorActual();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorBlanco(){/**/BORRAR=0;/**/ROJO=10;/**/VERDE=10;/**/AZUL=10;/**/glColor3f(1.0f, 1.0f, 1.0f);/**/colorActual();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorNegro(){/**/BORRAR=0;/**/ROJO=0;/**/VERDE=0;/**/AZUL=0;/**/glColor3f(0.0f,0.0f,0.0f);/**/colorActual();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorInvertir(){/**/BORRAR=0;/**/ROJO=10-ROJO;/**/VERDE=10-VERDE;/**/AZUL=10-AZUL;/**/
	glColor3f(ROJO/10, VERDE/10, AZUL/10);/**/	colorActual();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorRojopp(){/**/BORRAR=0;/**/if(ROJO<10){/**/ROJO++;/**/glColor3f(ROJO/10,VERDE/10,AZUL/10);/**/colorActual();/**/}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorRojomm(){/**/BORRAR=0;/**/if(ROJO>0){/**/ROJO--;/**/glColor3f(ROJO/10,VERDE/10,AZUL/10);/**/colorActual();/**/}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorVerdepp(){/**/BORRAR=0;/**/if(VERDE<10){/**/VERDE++;/**/glColor3f(ROJO/10,VERDE/10,AZUL/10);/**/colorActual();/**/}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorVerdemm(){/**/BORRAR=0;/**/if(VERDE>0){/**/VERDE--;/**/glColor3f(ROJO/10,VERDE/10,AZUL/10);/**/colorActual();/**/}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorAzulpp(){/**/BORRAR=0;/**/if(AZUL<10){/**/AZUL++;/**/glColor3f(ROJO/10,VERDE/10,AZUL/10);/**/colorActual();/**/}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void colorAzulmm(){/**/BORRAR=0;/**/if(AZUL>0){/**/AZUL--;/**/glColor3f(ROJO/10,VERDE/10,AZUL/10);/**/colorActual();/**/}/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< funciones Abrir Guardar >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void guardar(){/**/
	int i,j;/**/	glReadPixels(0,0,ANCHO,ALTO,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);/**/
	FILE *imagen;/**/	imagen=fopen("imagen.ppm","w");/**/	fprintf(imagen,"P3\n%d %d\n255\n",ANCHO,ALTO);/**/
	for(i=ALTO-1;i>=0;i--){/**/		for(j=0;j<ANCHO;j++){/**/
			fprintf(imagen, "%d %d %d ", canvasMAX[i][j][0],canvasMAX[i][j][1],canvasMAX[i][j][2]);/**/		}/**/
		fputs("\n", imagen);/**/	}/**/	printf("Guardado\n");/**/	fclose(imagen);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void abrir(){/**/
	GLubyte icono[ALTO][ANCHO][4];/**/	FILE *imagen;/**/	imagen=fopen("imagen.ppm","r");/**/
	char tipo[4];/**/	int ancho,alto,max,i,j;/**/	fscanf(imagen,"%s %d %d %d",tipo,&ancho,&alto,&max);/**/
	for(i=0;i<ancho;i++){/**/		for(j=0;j<alto;j++){/**/
			fscanf(imagen,"%hhd %hhd %hhd",&icono[ancho-1-i][j][0],&icono[ancho-1-i][j][1],&icono[ancho-1-i][j][2]);/**/
		}/**/	}/**/
	fclose(imagen);/**/	glRasterPos2i(0,0);/**/	glDrawPixels(480,480,GL_RGBA,GL_UNSIGNED_BYTE,icono);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void miMenu(int option){/**/	switch(option){/**/
		case('o'):/**/	TIPOPINCEL=0;/**/	ESPECIAL=0;/**/		BORRAR=0;/**/	break;/**/
		case('k'):/**/	TIPOPINCEL=1;/**/	ESPECIAL=0;/**/		BORRAR=0;/**/	break;/**/
		case('m'):/**/	TIPOPINCEL=2;/**/	ESPECIAL=0;/**/		BORRAR=0;/**/	break;/**/
		case('0'):/**/	TIPOPINCEL=0;/**/	ESPECIAL=0;/**/		BORRAR=1;/**/	break;/**/
		case('i'):/**/	ESPECIAL=1;/**/		TIPOPINCEL=0;/**/	BORRAR=0;/**/	break;/**/
		case('j'):/**/	ESPECIAL=2;/**/		TIPOPINCEL=0;/**/	BORRAR=0;/**/	break;/**/
		case('n'):/**/	ESPECIAL=3;/**/		TIPOPINCEL=0;/**/	BORRAR=0;/**/	break;/**/
		case('+'):/**/	if(TAMPINCEL<63){TAMPINCEL++;}/**/		break;/**/
		case('-'):/**/	if(TAMPINCEL>1){TAMPINCEL--;}/**/		break;/**/
		case('r'):/**/	TAMPINCEL=10;/**/	break;/**/			case('e'):/**/	TAMPINCEL=20;/**/	break;/**/
		case('d'):/**/	TAMPINCEL=30;/**/	break;/**/			case('c'):/**/	TAMPINCEL=40;/**/	break;/**/
		case('f'):/**/	TAMPINCEL=50;/**/	break;/**/
		case('u'):/**/	cambiarFondo();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('y'):/**/	cambiarFondo2();/**/	GLOBAL=0;/**/	especial();/**/	break;/**/
		case('t'):/**/	limpiarCanvas();/**/	GLOBAL=0;/**/	especial();/**/	break;/**/
		case('g'):/**/	guardar();/**/			GLOBAL=0;/**/	especial();/**/	break;/**/
		case('b'):/**/	abrir();/**/			GLOBAL=0;/**/	especial();/**/	break;/**/
		case('9'):/**/	colorInvertir();/**/	GLOBAL=0;/**/	especial();/**/	break;/**/
		case('1'):/**/	colorBlanco();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('2'):/**/	colorNegro();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('3'):/**/	colorRojo();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('4'):/**/	colorAzul();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('5'):/**/	colorVerde();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('6'):/**/	colorRojo();/**/	colorInvertir();/**/	GLOBAL=0;/**/	especial();/**/	break;/**/
		case('7'):/**/	colorAzul();/**/	colorInvertir();/**/	GLOBAL=0;/**/	especial();/**/	break;/**/
		case('8'):/**/	colorVerde();/**/	colorInvertir();/**/	GLOBAL=0;/**/	especial();/**/	break;/**/
		case('q'):/**/	colorRojomm();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('a'):/**/	colorVerdemm();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('z'):/**/	colorAzulmm();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('w'):/**/	colorRojopp();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('s'):/**/	colorVerdepp();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/
		case('x'):/**/	colorAzulpp();/**/		GLOBAL=0;/**/	especial();/**/	break;/**/	}/**/	colorActual();/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void myInit(void){/**/
	glPointSize(1);/**/	glClearColor(1.0,1.0,1.0,0.0);/**/	glColor3f(0.0f, 0.0f, 0.0f);/**/
	glMatrixMode(GL_PROJECTION);/**/	glLoadIdentity();/**/	gluOrtho2D(0.0, ANCHO+HERR, 0.0, ALTO);/**/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);/**/	glClear(GL_COLOR_BUFFER_BIT);/**/	colorActual();/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void){/**/
	if(GLOBAL == 1){/**/		switch(ESPECIAL){/**/
			case(1):/**/	glRasterPos2i(0,0);/**/	glDrawPixels(ANCHO,ALTO,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);/**/
				glPointSize(TAMPINCEL);/**/	relleno();/**/		break;/**/
			case(2):/**/	glRasterPos2i(0,0);/**/	glDrawPixels(ANCHO,ALTO,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);/**/
				glPointSize(TAMPINCEL);/**/	rectangulo();/**/	break;/**/
			case(3):/**/	glRasterPos2i(0,0);/**/	glDrawPixels(ANCHO,ALTO,GL_RGBA,GL_UNSIGNED_BYTE,canvasMAX);/**/
				glPointSize(TAMPINCEL);/**/	aRectaPuntoMedio(T[2].x,T[2].y,T[1].x,T[1].y);/**/	break;/**/
			default:/**/	circunferencia();/**/		}/**/	}/**/
	colorActual();/**/	glFlush();/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< captura de punto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
void clickder(int x, int y){/**/
	y=(y-1)/35;/**/	if(x>ANCHO && y<6){/**/
		BORRAR=0;/**/	x=(x-ANCHO-1)/35;/**/	x=x*35+ANCHO+19;/**/	y=y*35+19;/**/	GLubyte canvas[1][1][4];/**/
		glReadPixels(x,480-y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,canvas);/**/	ROJO=canvas[0][0][0]/25.5;/**/	VERDE=canvas[0][0][1]/25.5;/**/
		AZUL=canvas[0][0][2]/25.5;/**/	colorActual();/**/	}/**/
	if(x>ANCHO && y>=6 && y<10){/**/	x=(ANCHO+HERR-x)/35;/**/		miMenu(opp[x][y-6]);/**/	}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void eventoMaus(int button, int state, int x, int y){/**/
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && GLOBAL==0){/**/
		setPuntosIniciales(x,ALTO-y,0);/**/		setPuntosIniciales(x,ALTO-y,2);/**/
		setPuntosIniciales(x,ALTO-y,1);/**/		GLOBAL=1;/**/		clickder(x,y);/**/	}/**/
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && GLOBAL==1){/**/
		setPuntosIniciales(x,ALTO-y,0);/**/		setPuntosIniciales(x,ALTO-y,1);/**/
		GLOBAL=0;/**/		especial();/**/	}/**/	glutPostRedisplay();/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void eventoMotion(int x, int y){/**/	if(GLOBAL==1){/**/	setPuntosIniciales(x,480-y,1);/**/}/**/	glutPostRedisplay();/**/}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< evento teclado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><>>>>>>>>>>>>>>>>>>>
void eventoK(unsigned char key, int x, int y){/**/	miMenu(key);/**/	glutPostRedisplay();/**/	}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Iconos >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void leerIcono(FILE *icon, GLubyte icono[32][32][3]){/**/
	char tipo[4];/**/	int ancho,alto,max,i,j;/**/	fscanf(icon,"%s %d %d %d",tipo,&ancho,&alto,&max);/**/
	for(i=0;i<ancho;i++){/**/		for(j=0;j<alto;j++){/**/
			fscanf(icon,"%hhd %hhd %hhd",&icono[ancho-1-i][j][0],&icono[ancho-1-i][j][1],&icono[ancho-1-i][j][2]);/**/
		}/**/	}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void leerIcono2(FILE *icon, GLubyte icono[32][32]){/**/
	char tipo[4];/**/	int ancho,alto,max,i,j;/**/	fscanf(icon,"%s %d %d %d",tipo,&ancho,&alto,&max);/**/
	for(i=0;i<ancho;i++){/**/		for(j=0;j<alto;j++){/**/
			fscanf(icon,"%hhd",&icono[ancho-1-i][j]);/**/		}/**/	}/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void losIconos(){/**/
	GLubyte icono[32][32][3];/**/	GLubyte icono2[32][32];/**/	FILE *icon;/**/	char titulo[]="iconA.ppm";/**/	int i,j,k=66;/**/
	for(j=0;j<2;j++){/**/		for(i=0;i<4;i++){/**/
			titulo[7]='p';/**/	icon=fopen(titulo,"r");/**/		leerIcono(icon,icono);/**/	fclose(icon);/**/
			glRasterPos2i(ANCHO+2+H*i,ALTO-H*(7+j*2)+2);/**/	glDrawPixels(32,32,GL_RGB,GL_UNSIGNED_BYTE,icono);/**/
			titulo[7]='g';/**/	icon=fopen(titulo,"r");/**/		leerIcono2(icon,icono2);/**/	fclose(icon);/**/
			glRasterPos2i(ANCHO+2+H*i,ALTO-H*(8+j*2)+2);/**/	glDrawPixels(32,32,GL_GREEN,GL_UNSIGNED_BYTE,icono2);/**/
			titulo[4]=(char)k;/**/	k++;/**/	}/**/	}/**/
	icon=fopen("delIcon2.ppm","r");/**/	leerIcono(icon,icono);/**/	fclose(icon);/**/	glRasterPos2i(ANCHO+2+H*3,ALTO-H*10+2);/**/
	glDrawPixels(32,32,GL_RGB,GL_UNSIGNED_BYTE,icono);/**/}/**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
void initBarraHerr(){/**/
	int i,j;/**/	glReadPixels(ANCHO+HERR/2,(HERR/2)-5,1,1,GL_RGBA,GL_UNSIGNED_BYTE,borrar3);/**/
	glReadPixels(ANCHO+HERR/2,(HERR/2)-5,1,1,GL_RGBA,GL_UNSIGNED_BYTE,borrar);/**/	setPuntosIniciales(ANCHO,ALTO,0);/**/
	setPuntosIniciales(ANCHO,ALTO,2);/**/	setPuntosIniciales(ANCHO+HERR,HERR-10,1);/**/
	glColor3f(0.2f, 0.2f, 0.2f);relleno();/**/	glColor3f(1.0f, 1.0f, 1.0f);/**/	rectangulo();/**/
	setPuntosIniciales(ANCHO,0,0);/**/	setPuntosIniciales(ANCHO,0,2);/**/
	setPuntosIniciales(ANCHO+HERR,HERR-10,1);/**/	relleno();/**/
	for(i=0;i<4;i++){/**/	aRectaPuntoMedio(ANCHO+35*i,ALTO,ANCHO+35*i,HERR-10);/**/		
		aRectaPuntoMedio(ANCHO,ALTO-(35*(3*i)),ANCHO+HERR,ALTO-(35*(3*i)));/**/
		aRectaPuntoMedio(ANCHO,ALTO-(35*(1+3*i)),ANCHO+HERR,ALTO-(35*(1+3*i)));/**/
		aRectaPuntoMedio(ANCHO,ALTO-(35*(2+3*i)),ANCHO+HERR,ALTO-(35*(2+3*i)));/**/
		for(j=0;j<6;j++){/**/	ROJO=colores[j][i][0];/**/		VERDE=colores[j][i][1];/**/
			AZUL=colores[j][i][2];/**/		setPuntosIniciales(ANCHO+H*i+2,480-H*j,0);/**/
			setPuntosIniciales(ANCHO+H*i+H/2+2,480-H*j-H/2,1);circunferencia();/**/	}/**/	}/**/
	glColor3f(1.0f, 1.0f, 1.0f);/**/	aRectaPuntoMedio(ANCHO,ALTO-(35*(2+3*3)),ANCHO+HERR,ALTO-(35*(2+3*3)));/**/
	losIconos();/**/	glReadPixels(480,0,140,480,GL_RGBA,GL_UNSIGNED_BYTE,barraHerr);/**/
	glRasterPos2i(480,140);/**/	glDrawPixels(140,480,GL_RGBA,GL_UNSIGNED_BYTE,barraHerr);/**/	colorActual();/**/	}/**/
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)	{/**/
	glutInit(&argc, argv);/**/	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);/**/
	glutInitWindowSize(ANCHO+HERR,ALTO);/**/	glutInitWindowPosition(700, 150);/**/ 
	glutCreateWindow("LABORATORIO COMPUTACION GRAFICA. MARTIN MOCCIA");/**/	glutDisplayFunc(myDisplay);/**/
	glutMouseFunc(eventoMaus);/**/	glutMotionFunc(eventoMotion);/**/
	glutKeyboardFunc(eventoK);/**/	glutCreateMenu(miMenu);/**/
	glutAddMenuEntry("Nuevo", 't');/**/	glutAddMenuEntry("Guardar", 'g');/**/
	glutAddMenuEntry("Abrir Guardado", 'b');/**/	glutAddMenuEntry("Pincel Constante", 'o');/**/
	glutAddMenuEntry("Pincel Lineal", 'k');/**/	glutAddMenuEntry("Pincel Cuadratico", 'm');/**/
	glutAddMenuEntry("Pincel Muy Chico", 'r');/**/	glutAddMenuEntry("Pincel Chico", 'e');/**/
	glutAddMenuEntry("Pincel Mediano", 'd');/**/	glutAddMenuEntry("Pincel Grande", 'c');/**/
	glutAddMenuEntry("Pincel Muy Grande", 'f');/**/	glutAddMenuEntry("Mas Rojo", 'w');/**/
	glutAddMenuEntry("Menos Rojo", 'q');/**/	glutAddMenuEntry("Mas Verde", 's');/**/
	glutAddMenuEntry("Menos Verde", 'a');/**/	glutAddMenuEntry("Mas Azul", 'x');/**/
	glutAddMenuEntry("Menos Azul", 'z');/**/	glutAttachMenu(GLUT_RIGHT_BUTTON);/**/
	myInit();initBarraHerr();especial();/**/	glutMainLoop();/**/	}/**/

