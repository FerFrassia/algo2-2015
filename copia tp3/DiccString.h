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

    const bool Def(const string &clave) const;

    T& Obtener(const string &clave) const;

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
        } else {
            hijos[i] = NULL;
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
DiccString<T>::DiccString(): claves(), significados() {
    raiz = new Nodo();
}

template<class T>
DiccString<T>::DiccString(const DiccString<T> &otro): raiz(otro.raiz), claves(otro.claves), significados(otro.significados) {
}

template<class T>
DiccString<T>::~DiccString() {
    delete raiz;
}

template<class T>
const bool DiccString<T>::Def(const string &clave) const{
    Nodo* actual = raiz;
    int i = 0;
    bool defined = true;
    while (i < clave.size() && defined == true) {

        if (actual->hijos[int(clave[i])] == NULL) {
            defined = false;
        } else {
            actual = actual->hijos[int(clave[i])];
        }
        ++i;

    }
    if (!actual->itSig.HaySiguiente()) {
        defined = false;
    }

    return defined;
}

template<class T>
void DiccString<T>::Definir(const string &clave, const T &significado) {
    if (Def(clave)) {
        Obtener(clave) = significado;
    } else {
        Nodo *actual = raiz;
        for (int i = 0; i < clave.size(); ++i) {
            if (actual->hijos[int(clave[i])] == NULL) {
                actual->hijos[int(clave[i])] = new Nodo();
            }

            Nodo *padre = actual;
            actual = actual->hijos[int(clave[i])];
            actual->padre = padre;

        }
        actual->itSig = significados.AgregarAtras(significado);
        actual->itClv = claves.AgregarRapido(clave);
    }
}

template<class T>
T& DiccString<T>::Obtener(const string &clave) const {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->hijos[int(clave[i])];
    }

    return actual->itSig.Siguiente();
}

template<class T>
void DiccString<T>::Borrar(const string &clave) {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->hijos[int(clave[i])];
    }

    actual->itSig.EliminarSiguiente();
    actual->itSig = Lista<T>().CrearIt();

    actual->itClv.EliminarSiguiente();
    actual->itClv = Conj<string>().CrearIt();

    bool esPrefijo = false;
    for (int i = 0; i < 256 && !esPrefijo; ++i) {
        if (actual->hijos[i] != NULL) {
            esPrefijo = true;
        }
    }

    if (!esPrefijo) {
        bool claveBorrada = false;
        int clvIndex = clave.size()-1;
        while (clvIndex >= 0 && !claveBorrada) {
            bool borrarNodo = true;
            for (int i = 0; i < 256 && borrarNodo; ++i) {
                if (actual->hijos[i] != NULL) {
                    borrarNodo = false;
                }
            }
            if (borrarNodo) {
                actual = actual->padre;
                actual->hijos[int(clave[clvIndex])] = NULL;
            } else {
                claveBorrada = true;
            }
            clvIndex = clvIndex-1;
        }
    }
}

template<class T>
Conj<string> DiccString<T>::Claves() {
    return claves;
}

template<class T>
Lista<T> DiccString<T>::Significados() {
    return significados;
}


#endif //TP3_ALGO2_DICCSTRING_H
