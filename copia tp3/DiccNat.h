//
// Created by Fer on 11/23/15.
//

#ifndef TP3_ALGO2_DICCNAT_H
#define TP3_ALGO2_DICCNAT_H

#include <assert.h>
#include "aed2/Conj.h"
#include "aed2/Dicc.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include <algorithm>
using namespace aed2;
using namespace std;

template<class T>
class DiccNat {
public:

    DiccNat(Nat tamano);

    //~DiccNat();

    DiccNat(const DiccNat &otro);

    typename Dicc<Nat, T>::Iterador Definir(const Nat clave, const T &significado);

    bool Def(const Nat clave);

    T& Obtener(const Nat clave);

    void Borrar(const Nat clave);

    Conj<Nat> Claves();

private:

    Vector< Dicc<Nat, T> > posiciones;

    Nat FuncionHash(Nat clave){
        return clave % posiciones.Longitud();
    }

};

//metodos publicos

template<class T>
DiccNat<T>::DiccNat(Nat tamano) {

    posiciones = Vector< Dicc<Nat, T> >();
    for (Nat i = 0; i < tamano; ++i) {
        posiciones.AgregarAtras(Dicc<Nat, T>());
    }

}

template<class T>
DiccNat<T>::DiccNat(const DiccNat<T> &otro): posiciones(otro.posiciones) {
}

template <class T>
typename Dicc<Nat, T>::Iterador DiccNat<T>::Definir(const Nat clave, const T &significado) {
    Nat posicion = FuncionHash(clave);
    return posiciones[posicion].Definir(clave, significado);
}

template <class T>
bool DiccNat<T>::Def(const Nat clave) {

    Nat posicion = FuncionHash(clave);
    return posiciones[posicion].Definido(clave);

}

template <class T>
T& DiccNat<T>::Obtener(const Nat clave) {

    Nat posicion = FuncionHash(clave);
    return posiciones[posicion].Significado(clave);

}

template <class T>
void DiccNat<T>::Borrar(const Nat clave) {

    Nat posicion = FuncionHash(clave);
    posiciones[posicion].Borrar(clave);

}

template <class T>
Conj<Nat> DiccNat<T>::Claves() {

    Conj<Nat> claves;
    for (Nat i = 0; i < posiciones.Longitud(); ++i) {
        typename Dicc<Nat,T>::Iterador itDic = posiciones[i].CrearIt();
        while (itDic.HaySiguiente()) {
            claves.AgregarRapido(itDic.SiguienteClave());
            itDic.Avanzar();
        }
    }

    return claves;

}

#endif //TP3_ALGO2_DICCNAT_H
