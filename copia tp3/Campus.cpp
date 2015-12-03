// Created by Sebastián Matias Giambastiani on 28/06/2015

#include "Campus.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "Tipos.h"

// Métodos públicas.
Campus::Campus(Nat columnas, Nat filas) {
    e_campus = Vector<Vector<bool> >();
    for (int i = 0; i < columnas; ++i) {
        Vector<bool> vecFilas = Vector<bool>();
        for (int j = 0; j < filas; ++j) {
            vecFilas.AgregarAtras(false);
        }
        e_campus.AgregarAtras(vecFilas);
    }
}

Campus::Campus(Campus &original): e_campus(original.e_campus) {
}

//Campus::~Campus() {
//}

bool Campus::operator==(Campus &otro) {
    bool filaColumna =  Filas() == otro.Filas() && Columnas() == otro.Columnas();

    if (filaColumna) {
        for (int c = 0; c < Columnas(); ++c) {
            for (int f = 0; f < Filas(); ++f) {
                if (Ocupada(Posicion(c, f)) != otro.Ocupada(Posicion(c, f))) {
                    return false;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

Nat Campus::Filas() {
    return e_campus[0].Longitud();
}

Nat Campus::Columnas() {
    return e_campus.Longitud();
}

bool Campus::Ocupada(Posicion pos) {
    return e_campus[pos.x][pos.y];
}

void Campus::AgregarObstaculo(Posicion pos) {
    e_campus[pos.x][pos.y] = true;
}


bool Campus::PosValida(Posicion pos) {
    return pos.x < Columnas() && pos.y < Filas();
}

bool Campus::IngresoSuperior(Posicion pos) {
    return pos.y == 0;
}

bool Campus::IngresoInferior(Posicion pos) {
    return pos.y == Filas()-1;
}

bool Campus::EsIngreso(Posicion pos) {
    return IngresoSuperior(pos) || IngresoInferior(pos);
}

Conj<Posicion> Campus::Vecinos(Posicion pos) {
    Conj<Posicion> conjPosiciones = Conj<Posicion>();

    if (PosValida(ProxPosicion(pos, abajo))) {
        conjPosiciones.AgregarRapido(ProxPosicion(pos, abajo));
    } else {
        conjPosiciones.AgregarRapido(Posicion(-1, -1));
    }

    if (PosValida(ProxPosicion(pos, arriba))) {
        conjPosiciones.AgregarRapido(ProxPosicion(pos, arriba));
    } else {
        conjPosiciones.AgregarRapido(Posicion(-1, -1));
    }

    if (PosValida(ProxPosicion(pos, der))) {
        conjPosiciones.AgregarRapido(ProxPosicion(pos, der));
    } else {
        conjPosiciones.AgregarRapido(Posicion(-1, -1));
    }

    if (PosValida(ProxPosicion(pos, izq))) {
        conjPosiciones.AgregarRapido(ProxPosicion(pos, izq));
    } else {
        conjPosiciones.AgregarRapido(Posicion(-1, -1));
    }

    return conjPosiciones;

}

Arreglo<Posicion> Campus::PosVecinas(Posicion pos) {
    return DeConjAArreglo(Vecinos(pos));
}

Arreglo<Posicion> Campus::DeConjAArreglo(Conj<Posicion> c) {
    Arreglo<Posicion> arreglo = Arreglo<Posicion>(c.Cardinal());
    Conj<Posicion>::Iterador itConjunto = c.CrearIt();
    Nat i = 0;
    while (itConjunto.HaySiguiente()) {
        // Copiar lo siguiente..
        if (itConjunto.Siguiente() != Posicion(-1, -1)) {
            arreglo.Definir(i, itConjunto.Siguiente());
        }
        ++i;
        itConjunto.Avanzar();
    }
    return arreglo;
}

int Campus::Distancia(Posicion pos1, Posicion pos2) {
    return Abs(pos1.x - pos2.x) + Abs(pos1.y - pos2.y);
}

Posicion Campus::ProxPosicion(Posicion pos, Direccion direccion) {
    switch (direccion) {
        case izq:
            return Posicion(pos.x-1, pos.y);
        case der:
            return Posicion(pos.x+1, pos.y);
        case arriba:
            return Posicion(pos.x, pos.y-1);
        case abajo:
            return Posicion(pos.x, pos.y+1);
    }
}

Conj<Posicion> Campus::IngresosMasCercanos(Posicion pos) {
    Conj<Posicion> conjunto = Conj<Posicion>();
    Posicion superior = Posicion(pos.x, 0);
    Posicion inferior = Posicion(pos.x, Filas()-1);
    if (Distancia(pos, superior) <= Distancia(pos, inferior))
        conjunto.Agregar(superior);
    if (Distancia(pos, superior) >= Distancia(pos, inferior))
        conjunto.Agregar(inferior);
    return conjunto;
}

int Campus::Abs(int numero) {
    if (numero < 0)
        return -numero;
    else
        return numero;
}

// Para testear ver cómo lo había hecho en red.cpp del