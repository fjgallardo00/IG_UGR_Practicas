//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CONO, CILINDRO, ESFERA, ARTICULADO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_cono cono(8, 1, 1.5);
_cilindro cilindro(8, 1, 2);
_esfera esfera(1, 16, 16);

_excavadora articulado;

float velocidad_cabina = 2.0;
float velodidad_brazo_base = 1.0;
float velocidad_brazo_final = 1.0;
float velocidad_mano = 1.0;

bool activar_idle_horario = false;

int flag=0, flag2=0, flag3=0;
int mov=7, mov2=2, mov3=1;

int alfa = 0, beta = 0;

// _objeto_ply *ply1;

int estadoRaton[3], xc, yc, cambio=0;
float factor=1.0;

int Ancho, Alto;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case ARTICULADO: articulado.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
	}

}


//**************************************************************************
//
//***************************************************************************

void luces (int alfa, int beta)
{
float   luz_ambiente[]={0.2, 0.2, 0.2, 1.0},
        luz1[]={1.0, 1.0, 1.0, 1.0},
        pos1[]= {0, 20.0, 40.0, 1.0},
		luz2[]={0.2, 1.0, 0.0, 1.0},
		pos2[]={-20., 20.0, 00.0, 1.0};
     


glLightfv (GL_LIGHT0, GL_AMBIENT, luz_ambiente);
glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1);
glLightfv (GL_LIGHT1, GL_SPECULAR, luz1);
//glLightfv(GL_LIGHT1, GL_POSITION, pos1);
glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2);
glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);
glLightfv(GL_LIGHT2, GL_POSITION, pos2);

glPushMatrix();
glRotatef(alfa,0,1,0);
glTranslatef(0,beta,0);
glLightfv(GL_LIGHT1, GL_POSITION, pos1);
glPopMatrix();

glDisable (GL_LIGHT0);
glEnable (GL_LIGHT1);
}

void vista_orto(){
  glViewport(Ancho/2,Alto/2,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*factor,5*factor,-5*factor,5*factor,-50,50);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  luces(alfa,beta);
  draw_axis();
  draw_objects();

  glViewport(0,Alto/2,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*factor,5*factor,-5*factor,5*factor,-50,50);
  glRotatef(90,1,0,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  luces(alfa,beta);
  draw_axis();
  draw_objects();

  glViewport(0,0,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*factor,5*factor,-5*factor,5*factor,-50,50);
  glRotatef(90,0,1,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  luces(alfa,beta);
  draw_axis();
  draw_objects();

  glViewport(Ancho/2,0,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  glTranslatef(0.0,0.0,-5.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(25,1,0,0);
  glRotatef(-45,0,1,0);
  luces(alfa,beta);
  //draw_axis();
  draw_objects();
}

void draw_viejo(void){
	clean_window();
	change_observer();
	luces(alfa,beta);
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

void draw_nuevo(void){
	glDrawBuffer(GL_FRONT);
	clean_window();

	if(cambio == 0){
	glViewport(0,0,Ancho,Alto);
	change_projection();
	change_observer();
	luces(alfa,beta);
	draw_axis();
	draw_objects();

	}
	else{
	vista_orto();
	}

	if (t_objeto==ARTICULADO){
	glDrawBuffer(GL_BACK);
	clean_window();
	change_observer();
	articulado.seleccion();
	}

	glFlush();
}

void draw(void){
	//draw_viejo();
	draw_nuevo();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
Ancho=Ancho1;
Alto=Alto1;
glutPostRedisplay();
}


void procesar_color(unsigned char color[3]){
	int i;

	for (i=0;i<articulado.piezas;i++){
		if (color[0]==articulado.color_selec[0][i]){

			if (articulado.activo[i]==0){
				articulado.activo[i]=1;
			}
			else{
				articulado.activo[i]=0;
			}
			glutPostRedisplay();
		}
    }                
}



void pick_color(int x, int y){
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
}

void clickRaton(int boton, int estado, int x, int y){
	if(boton== GLUT_RIGHT_BUTTON) {
		if( estado == GLUT_DOWN) {
			estadoRaton[2] = 1;
			xc=x;
			yc=y;
		} 
		else estadoRaton[2] = 1;
	}
	if(boton== GLUT_LEFT_BUTTON){
		if( estado == GLUT_DOWN) {
			estadoRaton[2] = 2;
			xc=x;
			yc=y;
			pick_color(xc, yc);
		} 
	}
	if(boton == 3){
		factor*=0.9;
		glutPostRedisplay();
	}
	else if(boton == 4){
		factor*=1.1;
		glutPostRedisplay();
	}
}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case 'W':modo=POINTS;break;
	case 'E':modo=EDGES;break;
	case 'R':modo=SOLID;break;
	case 'T':modo=SOLID_CHESS;break;
	case 'Y':modo=SOLID_ILLUMINATED_FLAT;break;
    case 'U':modo=SOLID_ILLUMINATED_GOURAUD;break;
        case '1':t_objeto=PIRAMIDE;break;
        case '2':t_objeto=CUBO;break;
        case '3':t_objeto=OBJETO_PLY;break;	
        case '4':t_objeto=ROTACION;break;
		case '5':t_objeto=CONO;break;
		case '6':t_objeto=CILINDRO;break;
		case '7':t_objeto=ESFERA;break;
		case '8':t_objeto=ARTICULADO;break;
	case 'A':velocidad_cabina+=2;break;
	case 'Z':velocidad_cabina-=2;break;
	case 'S':velodidad_brazo_base+=1;break;
	case 'X':velodidad_brazo_base-=1;break;
	case 'D':velocidad_brazo_final+=1;break;
	case 'C':velocidad_brazo_final-=1;break;
	case 'F':velocidad_mano+=1;break;
	case 'V':velocidad_mano-=1;break;
	case 'I':activar_idle_horario=true; break;
	case 'O':activar_idle_horario=false; break;
	case 'K':mov++;mov2++;mov3++; break;
	case 'L':mov--;mov2--;mov3--; break;
	case 'H':alfa+=5; break;
	case 'J':alfa-=5; break;
	case 'N':beta+=5; break;
	case 'M':beta-=5; break;
	case ',':cambio=0;break;
	case '.':cambio=1;break;
	case '+':factor=factor*0.9;break;
	case '-':factor=factor*1.1;break;
	
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y-=3;break;
	case GLUT_KEY_RIGHT:Observer_angle_y+=3;break;
	case GLUT_KEY_UP:Observer_angle_x-=3;break;
	case GLUT_KEY_DOWN:Observer_angle_x+=3;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:articulado.giro_cabina+=velocidad_cabina;break;
	case GLUT_KEY_F2:articulado.giro_cabina-=velocidad_cabina;break;
	case GLUT_KEY_F3:articulado.giro_brazo_base+=1;
        if (articulado.giro_brazo_base>articulado.giro_brazo_base_max) articulado.giro_brazo_base=articulado.giro_brazo_base_max;
            break;
    case GLUT_KEY_F4:articulado.giro_brazo_base-=1;
        if (articulado.giro_brazo_base<articulado.giro_brazo_base_min) articulado.giro_brazo_base=articulado.giro_brazo_base_min;
            break;
	case GLUT_KEY_F5:articulado.giro_brazo_final+=velocidad_brazo_final;
        if (articulado.giro_brazo_final>articulado.giro_brazo_final_max) articulado.giro_brazo_final=articulado.giro_brazo_final_max;
            break;
    case GLUT_KEY_F6:articulado.giro_brazo_final-=velocidad_brazo_final;
        if (articulado.giro_brazo_final<articulado.giro_brazo_final_min) articulado.giro_brazo_final=articulado.giro_brazo_final_min;
            break;
	case GLUT_KEY_F7:articulado.giro_mano+=1;
        if (articulado.giro_mano>articulado.giro_mano_max) articulado.giro_mano=articulado.giro_mano_max;
            break;
	case GLUT_KEY_F8:articulado.giro_mano-=1;
        if (articulado.giro_mano<articulado.giro_mano_min) articulado.giro_mano=articulado.giro_mano_min;
            break;
	}
glutPostRedisplay();
}

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}

void RatonMovido(int x, int y){
	float x0, y0, xn, yn; 
	if(estadoRaton[2]==1){
		getCamara(&x0,&y0);
		yn=y0+(y-yc);
		xn=x0-(x-xc);
		setCamara(xn,yn);
		xc=x;
		yc=y;
		glutPostRedisplay();
	}
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}

vector<_vertex3f> ModeloReinaAjedrez(){
	vector<_vertex3f> perfil2;
	_vertex3f aux;

	aux.x=1.0; aux.y=-2.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.8; aux.y=-1.7; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5; aux.y=-1.5; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.8; aux.y=-1.3; aux.z=0.0;
	perfil2.push_back(aux);
	//5
	aux.x=0.7; aux.y=-1.1; aux.z=0.0;
	perfil2.push_back(aux);//5
	aux.x=0.5; aux.y=-0.9; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4; aux.y=0.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3; aux.y=0.5; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.25; aux.y=0.7; aux.z=0.0;
	perfil2.push_back(aux);
	//10
	aux.x=0.25; aux.y=0.8; aux.z=0.0;
	perfil2.push_back(aux);//10
	aux.x=0.25; aux.y=1.0; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.25; aux.y=1.2; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.25; aux.y=1.4; aux.z=0.0;
	perfil2.push_back(aux);
	//14
	aux.x=0.3; aux.y=1.5; aux.z=0.0;
	perfil2.push_back(aux);//14
	aux.x=0.4; aux.y=1.55; aux.z=0.0;
	perfil2.push_back(aux);
	//16
	aux.x=0.5; aux.y=1.6; aux.z=0.0;
	perfil2.push_back(aux);//16
	aux.x=0.4; aux.y=1.65; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3; aux.y=1.7; aux.z=0.0;
	perfil2.push_back(aux);
	//19
	aux.x=0.35; aux.y=1.75; aux.z=0.0;
	perfil2.push_back(aux);//19
	aux.x=0.3; aux.y=1.8; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3; aux.y=1.9; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4; aux.y=2.0; aux.z=0.0;
	perfil2.push_back(aux);
	//23
	aux.x=0.55; aux.y=2.1; aux.z=0.0;
	perfil2.push_back(aux);//23
	aux.x=0.5; aux.y=2.3; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4; aux.y=2.3; aux.z=0.0;
	perfil2.push_back(aux);
	//26
	aux.x=0.4; aux.y=2.35; aux.z=0.0;
	perfil2.push_back(aux);//26
	//27
	aux.x=0.35; aux.y=2.4; aux.z=0.0;
	perfil2.push_back(aux);//27
	aux.x=0.3; aux.y=2.5; aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.15; aux.y=2.55; aux.z=0.0;
	perfil2.push_back(aux);


	return perfil2;
}

void funcion_idle(){

	if(activar_idle_horario){
		
		//cabina
		articulado.giro_cabina+=mov;

		//brazo_base
		if (flag==0) articulado.giro_brazo_base+=mov2;
		else articulado.giro_brazo_base-=mov2;

		if (articulado.giro_brazo_base>articulado.giro_brazo_base_max){
			articulado.giro_brazo_base=articulado.giro_brazo_base_max;
			flag=1;
		}
		if (articulado.giro_brazo_base<articulado.giro_brazo_base_min){
			articulado.giro_brazo_base=articulado.giro_brazo_base_min;
			flag=0;
		}

		//brazo_final
		if (flag2==0) articulado.giro_brazo_final+=mov3;
		else articulado.giro_brazo_final-=mov3;

		if (articulado.giro_brazo_final>articulado.giro_brazo_final_max){
			articulado.giro_brazo_final=articulado.giro_brazo_final_max;
			flag2=1;
		}
		if (articulado.giro_brazo_final<articulado.giro_brazo_final_min){
			articulado.giro_brazo_final=articulado.giro_brazo_final_min;
			flag2=0;
		}
        
		//mano excavadora
		if (flag3==0) articulado.giro_mano+=mov3;
		else articulado.giro_mano-=mov3;

		if (articulado.giro_mano>articulado.giro_mano_max){
			articulado.giro_mano=articulado.giro_mano_max;
			flag3=1;
		}
		if (articulado.giro_mano<articulado.giro_mano_min){
			articulado.giro_mano=articulado.giro_mano_min;
			flag3=0;
		}

	}

	glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{

// perfil 

vector<_vertex3f> perfil2;
vector<_vertex3f> vec_cilindro;
_vertex3f aux;

/*aux.x=1.2; aux.y=0.8; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.8; aux.y=0.2; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.1; aux.y=-0.3; aux.z=0.0;
perfil2.push_back(aux);*/


//reina ajedrez
perfil2 = ModeloReinaAjedrez();
rotacion.parametros(perfil2,8,0,0,0,0);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutIdleFunc(funcion_idle);

// eventos ratón
glutMouseFunc(clickRaton);
glutMotionFunc(RatonMovido);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
