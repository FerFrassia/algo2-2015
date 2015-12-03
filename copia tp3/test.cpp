#include "mini_test.h"
#include "DiccNat.h"
#include "DiccString.h"
#include "Campus.h"
#include <string>
#include <iostream>
#include "aed2/Conj.h"
#include "Sistema.h"
//#include "Driver.h"

using namespace aed2;
using namespace std;


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción
 * definidas en mini_test.h
 */

void test_trie(){
    // vacio
   DiccString<int> a;
   ASSERT(!a.Def("pepito"));
   ASSERT(a.Claves().EsVacio());
   ASSERT_EQ(a.Claves().Cardinal(), 0);
   ASSERT_EQ(a.Significados().Longitud(), 0);
   // un elemento
   a.Definir("pepito", 2);
   ASSERT(a.Def("pepito"));
   ASSERT_EQ(a.Claves().Cardinal(), 1);
   ASSERT_EQ(a.Significados().Longitud(), 1);
   ASSERT_EQ(a.Obtener("pepito"),2);
   //redefino pepito
    a.Definir("pepito", 3);
    ASSERT(a.Def("pepito"));
    ASSERT_EQ(a.Claves().Cardinal(), 1);
    ASSERT_EQ(a.Significados().Longitud(), 1);
    ASSERT_EQ(a.Obtener("pepito"), 3);
   // dos elementos
   a.Definir("juancito",3);
   ASSERT(a.Def("pepito"));
   ASSERT_EQ(a.Claves().Cardinal(), 2);
   ASSERT_EQ(a.Significados().Longitud(), 2);
   ASSERT_EQ(a.Obtener("pepito"),3);
   ASSERT_EQ(a.Obtener("juancito"),3);
   // un elemento
   a.Borrar("pepito");
   ASSERT(!a.Def("pepito"));
   ASSERT(a.Def("juancito"));
   ASSERT_EQ(a.Claves().Cardinal(), 1);
   ASSERT_EQ(a.Significados().Longitud(), 1);
   ASSERT_EQ(a.Obtener("juancito"),3);
}

void test_hash(){
    // vacio
    DiccNat<std::string> a = DiccNat<std::string>(3);
    ASSERT(!a.Def(1));
    ASSERT(a.Claves().EsVacio());
    // un elemento
    a.Definir(1, "pepito");
    ASSERT(a.Def(1));
    ASSERT_EQ(a.Claves().Cardinal(), 1);
    ASSERT_EQ(a.Obtener(1),"pepito");
    // dos elementos
    a.Definir(3,"juancito");
    ASSERT(a.Def(3));
    ASSERT(a.Def(1))
    ASSERT_EQ(a.Claves().Cardinal(), 2);
    ASSERT_EQ(a.Obtener(1),"pepito");
    ASSERT_EQ(a.Obtener(3),"juancito");
    // un elemento
    a.Borrar(3);
    ASSERT(!a.Def(3));
    ASSERT_EQ(a.Claves().Cardinal(), 1);
    ASSERT_EQ(a.Obtener(1),"pepito");
}

void test_campus(){
    Campus a (5, 8);
    Campus b (5, 8);

    //operator ==
    bool igualesAB = a == b;
    ASSERT(igualesAB);

    //copia
    Campus d (a);
    bool igualesAD = a == d;
    ASSERT(igualesAD);

    Posicion pos = Posicion(1,1);
    //pos en rango
    ASSERT(a.PosValida(pos));
    ASSERT_EQ(a.Columnas(),5);
    ASSERT_EQ(a.Filas(),8);
    ASSERT(!a.Ocupada(pos));
    // con obstaculos
    a.AgregarObstaculo(pos);
    ASSERT(a.Ocupada(pos));
    ASSERT_EQ(a.Columnas(),5);
    ASSERT_EQ(a.Filas(),8);
    //ingreso superior
    Posicion sup = Posicion(1,0);
    ASSERT(a.IngresoSuperior(sup));
    //ingreso inferior
    Posicion inf = Posicion(0,7);
    ASSERT(a.IngresoInferior(inf));
    //es ingreso
    ASSERT(a.EsIngreso(sup));
    ASSERT(a.EsIngreso(inf));
    //vecinos del 1,1
    Conj<Posicion> c;
    c.AgregarRapido(Posicion(0,1));
    c.AgregarRapido(Posicion(2,1));
    c.AgregarRapido(Posicion(1,0));
    c.AgregarRapido(Posicion(1,2));
    bool bla = c == a.Vecinos(pos);
    ASSERT(bla);

    //pos vecinas del 1,1
    Arreglo<Posicion> lasPosVecinas (4);
    lasPosVecinas.Definir(0, Posicion(0,1));
    lasPosVecinas.Definir(1, Posicion(2,1));
    lasPosVecinas.Definir(2, Posicion(1,0));
    lasPosVecinas.Definir(3, Posicion(1,2));

    ASSERT(lasPosVecinas.Definido(0));
    ASSERT(lasPosVecinas.Definido(1));
    ASSERT(lasPosVecinas.Definido(2));
    ASSERT(lasPosVecinas.Definido(3));

    bool pos0 = lasPosVecinas[0] == Posicion(0,1);
    bool pos1 = lasPosVecinas[1] == Posicion(2,1);
    bool pos2 = lasPosVecinas[2] == Posicion(1,0);
    bool pos3 = lasPosVecinas[3] == Posicion(1,2);

    ASSERT(pos0);
    ASSERT(pos1);
    ASSERT(pos2);
    ASSERT(pos3);

    Arreglo<Posicion> vecinos (a.PosVecinas(pos));

    ASSERT(vecinos.Definido(0));
    ASSERT(vecinos.Definido(1));
    ASSERT(vecinos.Definido(2));
    ASSERT(vecinos.Definido(3));

    bool v0 = vecinos[0] == Posicion(0,1);
    bool v1 = vecinos[1] == Posicion(2,1);
    bool v2 = vecinos[2] == Posicion(1,0);
    bool v3 = vecinos[3] == Posicion(1,2);

    ASSERT(v0);
    ASSERT(v1);
    ASSERT(v2);
    ASSERT(v3);

    bool bla2 = lasPosVecinas == a.PosVecinas(pos);
    ASSERT(bla2);

    //distancia pos1, pos2
    Posicion posa = Posicion(1,1);
    Posicion posb = Posicion(2,2);
    ASSERT_EQ(a.Distancia(posa, posb), 2);

    //prox Posicion ya testeado

    //ingresos mas cercanos
    Conj<Posicion> ca;
    ca.AgregarRapido(Posicion(1, 0));
    bool lala = ca == a.IngresosMasCercanos(posa);

    ca.Eliminar(Posicion(1,0));
    Posicion posc = Posicion(1,6);
    ca.AgregarRapido(Posicion(1,7));
    lala = ca == a.IngresosMasCercanos(posc);
    ASSERT(lala);

    Campus medioCampus (6, 9);
    Conj<Posicion> medioConj;
    medioConj.AgregarRapido(Posicion(6, 0));
    medioConj.AgregarRapido(Posicion(6, 8));
    Posicion medio = Posicion(6, 4);
    lala = medioConj == medioCampus.IngresosMasCercanos(medio);
    ASSERT(lala);

}

void test_sistema(){
    Campus a (8, 5);
    Posicion posObst = Posicion(1,1);
    Posicion posAg = Posicion(2,2);
    a.AgregarObstaculo(posObst);

    Dicc<Nat, Posicion> dic;
    dic.Definir(1, posAg);
    ASSERT_EQ(dic.CantClaves(), 1);
    Sistema sist (a,dic);
    Conj<Nat> p = Conj<Nat>();
    p.Agregar(1);

    // con un policia
    ASSERT_EQ(sist.CantSanciones(1),0);
    ASSERT_EQ(sist.CantHippies(),0);
    ASSERT_EQ(sist.CantEstudiantes(),0);
    ASSERT(!sist.Hippies().HaySiguiente());
    ASSERT(!sist.Estudiantes().HaySiguiente());
    ASSERT_EQ(sist.Agentes().Siguiente(), 1);
    ASSERT(!sist.ConKSanciones(0).EsVacio());
    bool bienCon0Sanciones = sist.ConKSanciones(0) == p;
    ASSERT(bienCon0Sanciones);
    ASSERT(sist.ConKSanciones(1).EsVacio());
    bool bienPosicionAgente = sist.PosAgente(1) == posAg;
    ASSERT(bienPosicionAgente);
    sist.IngresarHippie("John Lennon", Posicion(0, 0));
    sist.IngresarEstudiante("Rafa",Posicion(2, 0));

    // le meto un estudiante y un hippie
    ASSERT_EQ(sist.CantHippies(), 1);
    ASSERT(sist.Hippies().HaySiguiente());
    ASSERT_EQ(sist.Hippies().Siguiente(), "John Lennon");

    ASSERT_EQ(sist.CantEstudiantes(), 1);
    ASSERT(sist.Estudiantes().HaySiguiente());
    ASSERT_EQ(sist.Estudiantes().Siguiente(), "Rafa");

    ASSERT_EQ(sist.CantAgentes(), 1);
    ASSERT(sist.Agentes().HaySiguiente());
    ASSERT_EQ(sist.Agentes().Siguiente(), 1);
    ASSERT_EQ(sist.CantHippiesAtrapados(1), 0);
    ASSERT_EQ(sist.CantSanciones(1), 0);

    ASSERT(!sist.ConKSanciones(0).EsVacio());
    bool bienCon0Sanciones2 = sist.ConKSanciones(0) == p;
    ASSERT(bienCon0Sanciones2);
    ASSERT(sist.ConKSanciones(1).EsVacio());

    //posiciones
    bool bienLaPosDelAgente = sist.PosAgente(1) == posAg;
    ASSERT(bienLaPosDelAgente);

    bool posRafa = sist.PosEstudianteYHippie("Rafa") == Posicion(2, 0);
    ASSERT(posRafa);

    bool posJohn = sist.PosEstudianteYHippie("John Lennon") == Posicion(0, 0);
    ASSERT(posJohn);

    //mover todos agente 1 está en la pos 2,2, se tiene que mover a la 1,2 o 2,1
    sist.MoverAgente(1);
    ASSERT(sist.PosAgente(1) == Posicion(1, 2));
    ASSERT(sist.PosAgente(1) != Posicion(2, 1));
    ASSERT(sist.PosAgente(1) == Posicion(1,2) || sist.PosAgente(1) == Posicion(2, 1));

    //muevo a rafa
    sist.MoverEstudiante("Rafa", der);
    ASSERT(sist.PosEstudianteYHippie("Rafa") == Posicion(3, 0));
    ASSERT(sist.CantEstudiantes() == 1);
    ASSERT(sist.CantHippies() == 1);
    ASSERT(sist.CantAgentes() == 1);

    //mover hippie, john lennon está en la pos 0,0, rafa está en la pos 2,0. se tiene que mover a la 1,0.
    sist.MoverHippie("John Lennon");
    ASSERT(sist.PosEstudianteYHippie("John Lennon") == Posicion(1, 0));
    ASSERT(sist.PosEstudianteYHippie("Rafa") == Posicion(3, 0));
    ASSERT_EQ(sist.CantEstudiantes(), 1);
    ASSERT_EQ(sist.CantHippies(), 1);
    ASSERT_EQ(sist.CantAgentes(), 1);

    //mover y transformar a estudiante.
//    sist.MoverHippie("John Lennon");
//    ASSERT(sist.PosEstudianteYHippie("John Lennon") == );


    // muevo un paso todos los personajes
//    ASSERT_EQ(sist.CantSanciones(1),0);
//    ASSERT_EQ(sist.CantHippies(),0);



//    ASSERT_EQ(sist.Hippies(),Conj<std::string>().Agregar("John Lennon"));
//    ASSERT_EQ(sist.Agentes(), Conj<Nat>().Agregar(1));
//    ASSERT_EQ(sist.Estudiantes(),Conj<std::string>().Agregar("Rafa"));
//    ASSERT_EQ(sist.ConKSanciones(0), p);
//    ASSERT(sist.ConKSanciones(1).EsVacio());
//    ASSERT_EQ(sist.PosAgente(),Posicion(1,2));

//    bool posNuevaRafa = sist.PosEstudianteYHippie("Rafa") == Posicion(3, 0);
//    ASSERT(posNuevaRafa);

//    ASSERT_EQ(sist.PosEstudianteYHippie("John Lennon"), Posicion(0,1));

    //mover y sancionar


}


//
//void test_agregar_obstaculos() {
//	Driver campus;
//	campus.crearCampus(10,10);
//
//	Dicc<Agente,Posicion> agentes;
//	campus.comenzarRastrillaje(agentes);
//
//
//	Posicion p = Posicion(0,0);
//	p.x = 2;
//	p.y = 3;
//
//	campus.agregarObstaculo(p);
//
//	ASSERT(campus.ocupada(p) == true);
//
//	Posicion p2 = Posicion(0,0);
//	p2.x = 1;
//	p2.y = 1;
//
//	ASSERT(campus.ocupada(p2) == false);
//
//}
//
// void test_ingresa_estudiante(){
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarEstudiante(s,p2);
//
// 	ASSERT(campus.ocupada(p2) == true);
//
// 	Posicion p3 = campus.posEstudianteYHippie(s);
// 	ASSERT(p3.x == p2.x && p3.y == p3.x);
// }
//
// // DIFICIL
// void test_ingresa_hippie_y_convierte() {
// 	Testea que cuando ingresa un hippie y esta rodeado de estudiantes se convierte
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p1;
// 	p1.x = 1;
// 	p1.y = 1;
//
// 	Posicion p2;
// 	p2.x = 2;
// 	p2.y = 1;
//
//
// 	Posicion p3;
// 	p3.x = 3;
// 	p3.y = 1;
//
// 	Nombre s1 = "pepe";
// 	Nombre s2 = "pepo";
// 	Nombre s3 = "pepa";
//
// 	Ingreso 3 estudiantes uno al lado del otro
// 	campus.ingresarEstudiante(s1,p1);
// 	campus.ingresarEstudiante(s2,p2);
// 	campus.ingresarEstudiante(s3,p3);
//
// 	// Avanzo el estudiante del medio
// 	campus.moverEstudiante(s2,abajo);
//
// 	// Ahora hago ingresar un hippie,se tiene que convertir a estudiante
// 	Nombre h1 = "wololoHippie";
// 	campus.ingresarHippie(h1,p2);
// 	ASSERT(campus.cantEstudiantes() == 4);
// 	ASSERT(campus.cantHippies() == 0);
// }
//
// // DIFICIL
// void test_mueve_estudiante_y_convierte() {
// 	// Testea que cuando se mueve un estudiante y rodea a un hippie se convierte
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p1;
// 	p1.x = 1;
// 	p1.y = 1;
//
// 	Posicion p2;
// 	p2.x = 2;
// 	p2.y = 1;
//
//
// 	Posicion p3;
// 	p3.x = 3;
// 	p3.y = 1;
//
// 	Nombre s1 = "pepe";
// 	Nombre s2 = "pepo";
// 	Nombre s3 = "pepa";
//
// 	// Ingreso 3 estudiantes uno al lado del otro
// 	campus.ingresarEstudiante(s1,p1);
// 	campus.ingresarEstudiante(s2,p2);
// 	campus.ingresarEstudiante(s3,p3);
//
// 	// Avanzo el estudiante del medio
// 	campus.moverEstudiante(s2,abajo);
// 	campus.moverEstudiante(s2,abajo);
//
// 	// Ahora hago ingresar un hippie Y NO SE TIENE QUE CONVERTIR
// 	Nombre h1 = "wololoHippie";
// 	campus.ingresarHippie(h1,p2);
//
// 	ASSERT(campus.cantEstudiantes() == 3);
// 	ASSERT(campus.cantHippies() == 1);
//
// 	// Muevo el estudiante hacia arriba y tiene que convertir talannnn
// 	campus.moverEstudiante(s2,arriba);
//
// 	ASSERT(campus.cantEstudiantes() == 4);
// 	ASSERT(campus.cantHippies() == 0);
//
// }
//
// void test_mover_estudiante() {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarEstudiante(s,p2);
// 	campus.moverEstudiante(s, abajo);
//
// 	Posicion p3;
// 	p3.x = 1;
// 	p3.y = 2;
//
// 	ASSERT(campus.ocupada(p2) == false);
// 	ASSERT(campus.ocupada(p3) == true);
//
// 	Posicion p = campus.posEstudianteYHippie(s);
// 	ASSERT(p3.x == p.x && p3.y == p.y);
//
// }
//
// void test_mover_estudiante_fuera() {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarEstudiante(s,p2);
// 	campus.moverEstudiante(s, arriba);
//
//
// 	ASSERT(campus.ocupada(p2) == false);
// 	ASSERT(campus.cantEstudiantes() == 0);
// }
//
// void test_ingresa_hippie() {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarHippie(s,p2);
//
// 	ASSERT(campus.ocupada(p2) == true);
//
// 	Posicion p = campus.posEstudianteYHippie(s);
// 	ASSERT(p2.x == p.x && p2.y == p.y);
//
// }
//
// void test_ingresa_hippie_y_estudiante() {
// 	// Idea de este test es probar el funcionamiento del Trie
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarHippie(s,p2);
//
// 	Posicion p3;
// 	p3.x = 1;
// 	p3.y = 2;
//
// 	Nombre t = "pepa";
// 	campus.ingresarEstudiante(t,p3);
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 3;
//
// 	Nombre r = "pepen";
// 	campus.ingresarEstudiante(r,p);
//
//
// 	ASSERT(campus.iesimoHippie(0) == s);
//
// 	// No importa el orden, pero tienen que estar los dos
// 	ASSERT(campus.iesimoEstudiante(0) == t || campus.iesimoEstudiante(1) == t);
// 	ASSERT(campus.iesimoEstudiante(0) == r || campus.iesimoEstudiante(1) == r);
//
// }
//
//
// void test_mover_hippie_a_estudiante() {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	Nombre t = "pepa";
// 	campus.ingresarEstudiante(t,p);
//
// 	campus.moverEstudiante(t, abajo);
// 	campus.moverEstudiante(t, abajo);
// 	campus.moverEstudiante(t, abajo);
// 	campus.moverEstudiante(t, abajo);
// 	campus.moverEstudiante(t, abajo);
//
// 	// Baja el estudiante
// 	Posicion p3 = campus.posEstudianteYHippie(t);
// 	ASSERT(p3.x == 1 && p3.y == 6);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarHippie(s,p2);
// 	campus.moverHippie(s);
//
// 	// El hippie se mueve hacia abajo
// 	Posicion p4 = campus.posEstudianteYHippie(s);
// 	ASSERT(p4.x == 1 && p4.y == 2);
//
// 	Posicion p5;
// 	p5.x = 3;
// 	p5.y = 1;
//
// 	Nombre r = "pepo";
// 	campus.ingresarEstudiante(r,p5);
//
// 	// El hippie se mueve hacia el nuevo estudiante
// 	campus.moverHippie(s);
// 	p4 = campus.posEstudianteYHippie(s);
// 	ASSERT((p4.x == 1 && p4.y == 1) || (p4.x == 2 && p4.y == 2) );
//
// }
//
//
// void test_mover_hippie_a_ingreso() {
// 	// Idea del test: el hippie se mueve hacia el estudiante
// 	// Luego el estudiante se borra
// 	// Luego el hippie se mueve al ingreso mas cercano
//
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	campus.comenzarRastrillaje(agentes);
//
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	Nombre t = "pepa";
// 	campus.ingresarEstudiante(t,p);
//
// 	for (int i=0; i < 5; i++) {
// 		campus.moverEstudiante(t, abajo);
// 	}
//
// 	// Baja el estudiante
// 	Posicion p3 = campus.posEstudianteYHippie(t);
// 	ASSERT(p3.x == 1 && p3.y == 6);
//
// 	Posicion p2;
// 	p2.x = 1;
// 	p2.y = 1;
//
// 	Nombre s = "pepe";
// 	campus.ingresarHippie(s,p2);
// 	campus.moverHippie(s);
// 	campus.moverHippie(s);
//
// 	// El hippie se mueve hacia abajo
// 	Posicion p4 = campus.posEstudianteYHippie(s);
// 	ASSERT(p4.x == 1 && p4.y == 3);
//
// 	// Hago salir al estudiante, lo muevo a la derecha para no pisar el hippie
// 	campus.moverEstudiante(t, der);
// 	for (int i=0; i < 6; i++) {
// 		campus.moverEstudiante(t, arriba);
// 	}
//
// 	ASSERT(campus.cantEstudiantes() == 0);
//
// 	// Muevo al hippie , tiene que ir al ingreso mas cercano
// 	campus.moverHippie(s);
//
// 	p4 = campus.posEstudianteYHippie(s);
//
// 	ASSERT(p4.x == 1 && p4.y == 2);
//
// }
//
//
// void test_comenzar_rastrillaje_simple() {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	Agente a = 1;
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	agentes.Definir(a,p);
//
// 	campus.comenzarRastrillaje(agentes);
// 	ASSERT(campus.cantAgentes() == 1);
// }
//
//
// void test_rastrillaje_mover_hacia_hippie() {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	Agente a = 1;
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	agentes.Definir(a,p);
//
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion ph;
// 	ph.x = 5;
// 	ph.y = 1;
//
// 	Nombre h = "hippie";
// 	campus.ingresarHippie(h,ph);
//
// 	campus.moverAgente(a);
//
// 	Posicion p4 = campus.posAgente(a);
//
// 	ASSERT(p4.x == 2 && p4.y == 1);
//
// }
//
//
// void test_captura_hippie_entre_agentes()
// {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	Agente a = 1;
// 	Agente a2 = 2;
// 	Agente a3 = 3;
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	Posicion p2;
// 	p2.x = 2;
// 	p2.y = 2;
//
// 	Posicion p3;
// 	p3.x = 3;
// 	p3.y = 1;
//
// 	agentes.Definir(a,p);
// 	agentes.Definir(a2,p2);
// 	agentes.Definir(a3,p3);
//
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion ph;
// 	ph.x = 2;
// 	ph.y = 1;
//
// 	Nombre h = "hippie";
// 	campus.ingresarHippie(h,ph);
//
// 	ASSERT(campus.cantHippiesAtrapados(a) == 1);
// 	ASSERT(campus.cantHippiesAtrapados(a2) == 1);
// 	ASSERT(campus.cantHippiesAtrapados(a3) == 1);
//
// 	ASSERT(campus.masVigilante() == a || campus.masVigilante() == a2 || campus.masVigilante() == a3);
//
// }
//
// void test_captura_estudiante()
// {
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Dicc<Agente,Posicion> agentes;
// 	Agente a = 1;
// 	Agente a2 = 2;
// 	Agente a3 = 3;
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	Posicion p2;
// 	p2.x = 2;
// 	p2.y = 2;
//
// 	Posicion p3;
// 	p3.x = 3;
// 	p3.y = 1;
//
// 	agentes.Definir(a,p);
// 	agentes.Definir(a2,p2);
// 	agentes.Definir(a3,p3);
//
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion pe;
// 	pe.x = 2;
// 	pe.y = 1;
//
// 	Nombre e = "pepe";
// 	campus.ingresarEstudiante(e,pe);
//
// 	ASSERT(campus.conMismasSanciones(a).Cardinal() == 3 );
// 	ASSERT(campus.conMismasSanciones(a2).Cardinal() == 3 );
// 	ASSERT(campus.conMismasSanciones(a3).Cardinal() == 3 );
// 	Nat c = campus.conKSanciones(1).Cardinal();
// 	ASSERT(c == 3);
//
// 	Nat c2 = campus.conKSanciones(0).Cardinal();
// 	ASSERT(c2 == 0 );
//
//
// }
//
// void test_mas_vigilante()
// {
// // 3 primeras lineas antes de que ingresen los estudiantes
// //     1   2   3   4   5
// // 1 | A |   | A |   | O
// // 2 |   | A |   | O |
// // 3 ...
// // Los hippies ingresan en (2,1) y (4,1) los huecos. El Agente en (3,1) se transforma en el mas vigilante
// 	Driver campus;
// 	campus.crearCampus(10,10);
//
// 	Posicion o;
// 	o.x = 4;
// 	o.y = 2;
//
// 	campus.agregarObstaculo(o);
//
// 	Posicion o2;
// 	o2.x = 5;
// 	o2.y = 1;
//
// 	campus.agregarObstaculo(o2);
//
//
// 	Dicc<Agente,Posicion> agentes;
// 	Agente a = 1;
// 	Agente a2 = 2;
// 	Agente a3 = 3;
//
// 	Posicion p;
// 	p.x = 1;
// 	p.y = 1;
//
// 	Posicion p2;
// 	p2.x = 2;
// 	p2.y = 2;
//
// 	Posicion p3;
// 	p3.x = 3;
// 	p3.y = 1;
//
// 	agentes.Definir(a,p);
// 	agentes.Definir(a2,p2);
// 	agentes.Definir(a3,p3);
//
// 	campus.comenzarRastrillaje(agentes);
//
// 	Posicion ph;
// 	ph.x = 2;
// 	ph.y = 1;
//
// 	Nombre h = "hippie";
// 	campus.ingresarHippie(h,ph);
//
// 	Posicion ph2;
// 	ph2.x = 4;
// 	ph2.y = 1;
//
// 	Nombre h2 = "hippie2";
// 	campus.ingresarHippie(h2,ph2);
//
// 	ASSERT(campus.cantHippiesAtrapados(a) == 1);
// 	ASSERT(campus.cantHippiesAtrapados(a2) == 1);
// 	ASSERT(campus.cantHippiesAtrapados(a3) == 2);
//
// 	ASSERT(campus.masVigilante() == a3);
//
// }

int main(int argc, char **argv){
    RUN_TEST(test_campus);
    RUN_TEST(test_trie);
    RUN_TEST(test_hash);
    RUN_TEST(test_sistema);
   //  RUN_TEST(test_agregar_obstaculos);
   //  RUN_TEST(test_ingresa_estudiante);
  	// RUN_TEST(test_mover_estudiante);
	  // RUN_TEST(test_mover_estudiante_fuera);
	  // RUN_TEST(test_ingresa_hippie);
	  // RUN_TEST(test_ingresa_hippie_y_estudiante);
	  // RUN_TEST(test_mover_hippie_a_estudiante);
	  // RUN_TEST(test_mover_hippie_a_ingreso);
	  // RUN_TEST(test_ingresa_hippie_y_convierte);
	  // RUN_TEST(test_mueve_estudiante_y_convierte);
	  // RUN_TEST(test_comenzar_rastrillaje_simple);
	  // RUN_TEST(test_rastrillaje_mover_hacia_hippie);
	  // RUN_TEST(test_captura_hippie_entre_agentes);
	  // RUN_TEST(test_captura_estudiante);
	  // RUN_TEST(test_mas_vigilante);

    /********************************************************************
     * TODO: escribir casos de test exhaustivos para todas              *
     * las funcionalidades de cada módulo.                              *
     * La interacción con el TAD principal se debe hacer exclusivamente *
     * a través de la interfaz del driver.                              *
     ********************************************************************/

    return 0;
}
