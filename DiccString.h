//
// Created by Fer on 11/21/15.
//

#ifndef TP3_ALGO2_DICCSTRING_H
#define TP3_ALGO2_DICCSTRING_H

#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include <algorithm>
#include<assert.h>
using namespace aed2;
using namespace std;

template<class T>
class DiccString {
public:

    DiccString();

    ~DiccString();

    DiccString(const DiccString &otro);

    void Definir(const string &clave, const T &significado);

    const bool Def(const string &clave);

    T& Obtener(const string &clave);

    void Borrar(const string &clave);

    Conj<string> Claves();

    Lista<T> Significados();

private:

    struct Nodo {
        Conj<string>::Iterador itClv;
        typename Lista<T>::Iterador itSig;
        Nodo* hijos[256];
        Nodo* padre;
        Nodo();

        Nodo(const Nodo &otro);

        ~Nodo();

        const bool operator < (const Nodo &otro) const;

        const bool operator > (const Nodo &otro) const;

        const bool operator == (const Nodo &otro) const;

    };

    Nodo* raiz;
    Conj<string> claves;
    Lista<T> significados;

};

//algoritmos nodo

template<class T>
DiccString<T>::Nodo::Nodo() {

    itClv = Conj<string>().CrearIt();
    itSig = Lista<T>().CrearIt();
    Nodo* hijos[256];
    for (int i = 0; i < 256; ++i) {
        hijos[i] = NULL;
    }
    padre = NULL;

}

template<class T>
DiccString<T>::Nodo::Nodo(const Nodo& otro) : itClv(otro.itClv), itSig(otro.itSig), padre(otro.padre) {

    Nodo* hijos[256];
    for (int i = 0; i < 256; ++i) {
        if (otro.hijos[i] != NULL) {
            hijos[i] = new Nodo(*otro.hijos[i]);
            hijos[i]->padre = this;
        }
    }
}

template<class T>
DiccString<T>::Nodo::~Nodo() {
    for (int i = 0; i < 256; ++i) {
        if (hijos[i] != NULL) {
            delete hijos[i];
        }
    }
}

//metodos publicos

template<class T>
DiccString<T>::DiccString() {
    raiz = new Nodo();
    claves = *new Conj<string>();
    significados = *new Lista<T>();

}

template<class T>
DiccString<T>::DiccString(const DiccString<T> &otro) {
    if(otro.raiz != NULL) {
        raiz = new Nodo(*otro.raiz);
        claves = *new Conj<string>(otro.claves);
        significados = *new Lista<T>(otro.significados);
    }
}

template<class T>
DiccString<T>::~DiccString() {
    if (raiz != NULL) {
        delete raiz;
    }
    delete claves;
    delete significados;

}


#endif //TP3_ALGO2_DICCSTRING_H
