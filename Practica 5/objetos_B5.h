//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD,SELECT} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D{
	public:
		_puntos3D();
		void draw_puntos(float r, float g, float b, int grosor);
		vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
void    draw_seleccion(int r, int g, int b);

void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
    
	_rotacion();
	void  parametros(vector<_vertex3f> perfil1, int num, float ancho, float altura, float radio, int tipo);

	vector<_vertex3f> perfil; 
	int num;
};

class _cilindro: public _rotacion
{
public:

	_cilindro(int num=8, float ancho=0.5, float altura=1);
};

class _cono: public _rotacion
{
public:

	_cono(int num=8, float ancho=0.5, float altura=1);
};

class _esfera: public _rotacion
{
public:

	_esfera(float radio=1.0, int n=16, int m=16);
};


/*******************************************************************************************/

class _carroceria: public _triangulos3D{
	
	public:
		
		_carroceria();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

		float altura;

	protected:
		_cilindro ruedas;
		_cubo carroceria;
		
};

class _cabina: public _triangulos3D{
	public:
		
		_cabina();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

		float altura;
		float anchura;

	protected:
		_cubo cabina;
};

class _brazo_base: public _triangulos3D{
		
	public:
		_brazo_base();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

		float altura;
		float anchura;

	protected:
		_cubo brazo_base;

};

class _brazo_final: public _triangulos3D{
		
	public:
		_brazo_final();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

		float altura;
		float anchura;

	protected:
		_cubo brazo_final;

};

class _gancho_mano: public _triangulos3D{
		
	public:
		_gancho_mano();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_piramide mano;

};

class _excavadora: public _triangulos3D{
		
	public:
		_excavadora();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

		void seleccion();

		float giro_cabina;
		float giro_brazo_base;
		float giro_brazo_final;
		float giro_mano;

		float giro_brazo_base_min;
		float giro_brazo_base_max;
		float giro_brazo_final_min;
		float giro_brazo_final_max;
		float giro_mano_min;
		float giro_mano_max;

		/*****************/
		float  color_pick[3];
		int    color_selec[3][5];
		int    activo[5];
		int    piezas;

	protected:
		_carroceria carroceria;
		_cabina cabina;
		_brazo_base brazo_base;
		_brazo_final brazo_final;
		_gancho_mano gancho_mano;

};
