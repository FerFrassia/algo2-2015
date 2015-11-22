#ifndef HASH_H
#define HASH_H

#include <assert.h>
#include "aed2/Conj.h"

using namespace std;

template <class uint,class S>
class hash{
    public:
        hash(uint tamanio);
        virtual ~hash();
        void definir(const uint clave,const S significado);
        void borrar(const uint clave);
        bool def?(const uint clave);
        S obtener(const uint clave);
        Conj claves();
    protected:
    private:
        Dicc[tamano] tabla;
        int tamano;
        int tamanio(){
            return tamano;
        }
        int funcion_hash(const uint clave){
            return clave % tamanio();
        }
};

template <class uint,class S>
hash::hash(uint tamanio){
    *Dicc[tamanio] arreglo;
    for(int i = 0; i< tamanio; i++){
        arreglo[i] = NULL;
    }
    tamano = tamanio;
}

template <class uint, class S>
hash::~hash(){
    
}

template <class uint, class S>
void definir(const uint clave,const S significado){
    Dicc a= Dicc();
    if(tabla[this.funcion_hash(clave)] == NULL){
        tabla[this.funcion_hash(clave)] = &a();
    }

}

template <class uint, class S>
void borrar(const uint clave){
    Dicc aux = *tabla[funcion_hash(clave)];
    Borrar(clave, aux);
}

bool def?(const uint clave){
    if(tabla[funcion_hash(clave)] == NULL){
        return false;
    }else{
        Dicc aux = *tabla[funcion_hash(clave)];
        return def?(clave, aux)
    }
}

template <class uint, class S>
S obtener(const uint clave){
    Dicc aux = *tabla[funcion_hash(clave)];
    return *obtener(clave, aux);
}

template <class uint, class S>
Conj claves(){
    Conj clave = vacio();
    for(int i = 0; i<tamanio(); i++){
        if(tabla[i] != NULL){
            itConjLineal actual = CrearIt(claves(*tabla[i]));
            while(HaySiguiente?(actual)){
                AgregarRapido(Siguiente(actual), clave);
                Avanzar(actual);
            }
        }
    }
    return clave;
}

#endif // HASH_H
