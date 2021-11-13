//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();

}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){

	if(i%2==0){
		glColor3f(r1,g1,b1);
	}
	else{
		glColor3f(r2,g2,b2);
	}
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices 
vertices.resize(8); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;

vertices[4].x=-tam;vertices[4].y=2*tam;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=2*tam;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=2*tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=2*tam;vertices[7].z=-tam;


// triangulos

caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=2;
caras[1]._0=0;caras[1]._1=2;caras[1]._2=3;

caras[2]._0=1;caras[2]._1=2;caras[2]._2=5;
caras[3]._0=2;caras[3]._1=5;caras[3]._2=6;

caras[4]._0=2;caras[4]._1=3;caras[4]._2=6;
caras[5]._0=3;caras[5]._1=6;caras[5]._2=7;

caras[6]._0=0;caras[6]._1=1;caras[6]._2=4;
caras[7]._0=1;caras[7]._1=4;caras[7]._2=5;

caras[8]._0=0;caras[8]._1=3;caras[8]._2=7;
caras[9]._0=0;caras[9]._1=7;caras[9]._2=4;

caras[10]._0=4;caras[10]._1=5;caras[10]._2=7;
caras[11]._0=5;caras[11]._1=6;caras[11]._2=7;

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);

for(int i=0; i < n_ver; i++){
  vertices[i].x=ver_ply[3*i];
  vertices[i].y=ver_ply[3*i+1];
  vertices[i].z=ver_ply[3*i+2];
}

caras.resize(n_car);

for(int i=0; i < n_car; i++){
  caras[i]._0=car_ply[3*i];
  caras[i]._1=car_ply[3*i+1];
  caras[i]._2=car_ply[3*i+2];
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, float ancho, float altura, float radio, int tipo){
  
  int i,j,c;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  _vertex3f punto;
  int num_aux;

  // tratamiento de los vértice
  //tipo 2 cono
  if(tipo == 2){

    punto.x=ancho; punto.y=-(altura/2); punto.z=0.0;

    num_aux=1;
    vertices.resize(num_aux*num+3);
    for (j=0;j<num;j++){
      for (i=0;i<num_aux;i++){
          vertice_aux.x=punto.x*cos(2.0*M_PI*j/(1.0*num))+
                        punto.z*sin(2.0*M_PI*j/(1.0*num));
          vertice_aux.z=-punto.x*sin(2.0*M_PI*j/(1.0*num))+
                        punto.z*cos(2.0*M_PI*j/(1.0*num));
          vertice_aux.y=punto.y;
          vertices[i+j*num_aux]=vertice_aux;
      }
    }
  }
  else if(tipo == 0 || tipo == 3){ //tipo 0 rotacion estandar, tipo 3 cilindro
    num_aux=perfil.size();
    vertices.resize(num_aux*num+3);
    for (j=0;j<num;j++){
      for (i=0;i<num_aux;i++){

          vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
          vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
          vertice_aux.y=perfil[i].y;
          vertices[i+j*num_aux]=vertice_aux;
      }
    }
  }
  else if(tipo == 1){ //tipo 1 cilindro


    num_aux=2;

    punto.x=ancho; punto.y=altura/2; punto.z=0.0;
    perfil.push_back(punto);

    punto.x=ancho; punto.y=-(altura/2); punto.z=0.0;
    perfil.push_back(punto);

    vertices.resize(num_aux*num+3);
    for (j=0;j<num;j++){
      for (i=0;i<num_aux;i++){

          vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
          vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                        perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
          vertice_aux.y=perfil[i].y;
          vertices[i+j*num_aux]=vertice_aux;
      }
    }
  }

  

  // tratamiento de las caras 

  caras.resize(2*(num_aux-1)*num+num*2);

  c=0;
  int var, vertic = num*num_aux;

  for(j=0; j<num;j++){
    for(i=0; i<num_aux-1; i++){
      
      caras[c]._0=(j*num_aux+i)%vertic; 
      caras[c]._1=((j+1)*num_aux+i+1)%vertic;
      caras[c]._2=((j+1)*num_aux+i)%vertic;
      c++;
      
      caras[c]._0=(j*num_aux+i)%vertic;
      caras[c]._1=(j*num_aux+i+1)%vertic;
      caras[c]._2=((j+1)*num_aux+i+1)%vertic;
      c++;
      
    }

  }


  

  if(tipo == 0 || tipo == 1){
    // tapa inferior
    if (fabs(perfil[0].x)>0.0){
      _vertex3f vertice_tapa;
      _vertex3f vertice_abajo = perfil[num_aux-1];

      vertice_tapa.x=0;
      vertice_tapa.y=vertice_abajo.y;
      vertice_tapa.z=0;

      vertices[num*num_aux+1] = vertice_tapa;

      var=num_aux-1;

      for(int i=0; i<num; i++){
        caras[c]._0 = var;
        var+=num_aux;
        if(var >= vertic) var = var%vertic;
        caras[c]._1 = var;
        caras[c]._2 = num*num_aux+1;

        c++;
      }
    }

    // tapa superior
    if (fabs(perfil[num_aux-1].x)>0.0){
      _vertex3f vertice_tapa;
      _vertex3f vertice_arriba = perfil[0];

      vertice_tapa.x=0;
      vertice_tapa.y=vertice_arriba.y;
      vertice_tapa.z=0;

      vertices[num*num_aux+2] = vertice_tapa;

      var=0;

      for(int i=0; i<num; i++){
        caras[c]._0 = var;
        var+=num_aux;
        if(var >= vertic) var = var%vertic;
        caras[c]._1 = var;
        caras[c]._2 = num*num_aux+2;

        c++;
      }
    }
  }
  else if(tipo == 2){
    // tapa inferior
    if (fabs(punto.x)>0.0){
      
      _vertex3f vertice_tapa;

      vertice_tapa.x=0;
      vertice_tapa.y=punto.y;
      vertice_tapa.z=0;

      vertices[num*num_aux+1] = vertice_tapa;

      var=num_aux-1;

      for(int i=0; i<num; i++){
        caras[c]._0 = var;
        var+=num_aux;
        if(var >= vertic) var = var%vertic;
        caras[c]._1 = var;
        caras[c]._2 = num*num_aux+1;

        c++;
      }
    }
    // tapa superior
    if (fabs(punto.x)>0.0){

      _vertex3f vertice_tapa;

      vertice_tapa.x=0;
      vertice_tapa.y=altura;
      vertice_tapa.z=0;

      vertices[num*num_aux+2] = vertice_tapa;

      var=0;

      for(int i=0; i<num; i++){
        caras[c]._0 = var;
        var+=num_aux;
        if(var >= vertic) var = var%vertic;
        caras[c]._1 = var;
        caras[c]._2 = num*num_aux+2;

        c++;
      }
    }
  }
  else if(tipo == 3){
    if (fabs(perfil[0].x)>0.0){
      _vertex3f vertice_tapa;

      vertice_tapa.x=0;
      vertice_tapa.y=radio;
      vertice_tapa.z=0;

      vertices[num*num_aux+1] = vertice_tapa;

      var=num_aux-1;

      for(int i=0; i<num; i++){
        caras[c]._0 = var;
        var+=num_aux;
        if(var >= vertic) var = var%vertic;
        caras[c]._1 = var;
        caras[c]._2 = num*num_aux+1;

        c++;
      }
    }
    
    // tapa superior
    if (fabs(perfil[num_aux-1].x)>0.0){
      _vertex3f vertice_tapa;

      vertice_tapa.x=0.0;
      vertice_tapa.y=-radio;
      vertice_tapa.z=0.0;

      vertices[num*num_aux+2] = vertice_tapa;

      var=0;

      for(int i=0; i<num; i++){
        caras[c]._0 = var;
        var+=num_aux;
        if(var >= vertic) var = var%vertic;
        caras[c]._1 = var;
        caras[c]._2 = num*num_aux+2;

        c++;
      }
    }

  }
}


//*************************************************************************
// clase cilindro
//*************************************************************************

_cilindro::_cilindro(int num, float ancho, float altura)
{
  vector<_vertex3f> nullv;
  parametros(nullv, num, ancho, altura, 0, 1);
}

//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(int num, float ancho, float altura)
{
  vector<_vertex3f> nullv;
  parametros(nullv, num, ancho, altura, 0, 2);
}

//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int n, int m){
  vector<_vertex3f> perfil1;
  _vertex3f aux;
  int i;

  for(i=1; i<n; i++){
    aux.x=radio*cos(M_PI*i/n-M_PI/2.0);
    aux.y=radio*sin(M_PI*i/n-M_PI/2.0);
    aux.z=0;
    perfil1.push_back(aux);
  }
  parametros(perfil1, m, 0, 0, radio, 3);
}



/******************************************************************************************************/

/************************************************************************/
// Objeto prueba
/************************************************************************/



//************************************************************************
// objeto articulado: tanque
//************************************************************************

_cabina::_cabina(){
  
  vector<_vertex3f> perfil;
  ruedas.parametros(perfil, 16, 0.2, 1.0, 0, 1);

};

void _cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  
  glPushMatrix();
  glScalef(1.0,0.25,1.0);
  carroceria.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.4,0.25,0.5);
  glTranslatef(0.75,1.0,0.5);
  cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.5,0.0,0.0);
  glRotatef(90.0,1,0,0);
  ruedas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5,0.0,0.0);
  glRotatef(90.0,1,0,0);
  ruedas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

}

_gancho_base::_gancho_base(){
  vector<_vertex3f> perfil;
  palo_base.parametros(perfil, 16, 0.05, 0.45, 0, 1);
};

void _gancho_base::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  
  glPushMatrix();
  glScalef(0.25,0.40,0.25);
  glTranslatef(1.5,0.63,-0.85);
  plataforma_base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90.0,0.0,0.0,-1.0);
  glTranslatef(-0.5,0.70,-0.20);
  palo_base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

_gancho_mano::_gancho_mano(){
  vector<_vertex3f> perfil;
  palo_final.parametros(perfil, 16, 0.05, 0.45, 0, 1);
};

void _gancho_mano::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  
  /*glPushMatrix();
  glScalef(0.25,0.40,0.25);
  glTranslatef(1.5,0.63,-0.85);
  plataforma_base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();*/

  glPushMatrix();
  glRotatef(90.0,0.0,0.0,-1.0);
  glTranslatef(-0.5,1.70,-0.20);
  palo_final.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

_excavadora::_excavadora(){

};

void _excavadora::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  glPushMatrix();
  cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  gancho_base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  gancho_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
/*_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);*/
rodamiento.parametros(perfil,12,0.2,0.5,0,1);
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.38;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,0,0,0,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};

