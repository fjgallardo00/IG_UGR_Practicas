//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

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

class _cabina: public _triangulos3D{
	
	public:
		
		_cabina();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cilindro ruedas;
		_cubo carroceria;
		_cubo cabina;
};

class _gancho_base: public _triangulos3D{
		
	public:
		_gancho_base();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cilindro palo_base;
		_cubo plataforma_base;
		//_esfera articulacion;
		/*_cubo carroceria;
		_cubo cabina;*/

};

class _gancho_mano: public _triangulos3D{
		
	public:
		_gancho_mano();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cilindro palo_final;
		//_esfera articulacion;

};

class _excavadora: public _triangulos3D{
		
	public:
		_excavadora();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cabina cabina;
		_gancho_base gancho_base;
		_gancho_mano gancho_mano;

};
//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis chasis;
_torreta torreta;
_tubo tubo;
};

