// Created by Sebastián Matias Giambastiani on 21/11/2015

#ifndef CAMPUS_H
#define CAMPUS_H

#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "Tipos.h"

using namespace aed2;

class Campus {

public:
                        Campus              (Nat columnas, Nat filas);
                        Campus              (Campus &original);
//                        ~Campus             ();
    Nat                 Filas               ();
    Nat                 Columnas            ();
    bool                Ocupada             (Posicion pos);
    void                AgregarObstaculo    (Posicion pos);
    bool                PosValida           (Posicion pos);
    bool                IngresoSuperior     (Posicion pos);
    bool                IngresoInferior     (Posicion pos);
    bool                EsIngreso           (Posicion pos);
    Conj<Posicion>      Vecinos             (Posicion pos);
    Arreglo<Posicion>   PosVecinas          (Posicion pos);
    Arreglo<Posicion>   DeConjAArreglo      (Conj<Posicion> c);
    int                 Distancia           (Posicion pos1, Posicion pos2);
    Posicion            ProxPosicion        (Posicion pos, Direccion dir);
    Conj<Posicion>      IngresosMasCercanos (Posicion pos);

    bool operator == ( Campus& otro);

private:
    // Funciones Privadas
    int                 Abs                 (int numero);

    // Estructura
    Vector<Vector<bool> > e_campus;
};
#endif //CAMPUS_H