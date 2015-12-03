// Created by Sebastián Matias Giambastiani on 22/11/15

#ifndef SISTEMA_H
#define SISTEMA_H

#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "aed2/Dicc.h"
#include "Tipos.h"
#include "DiccNat.h"
#include "Campus.h"

using namespace aed2;
using namespace std;

struct tup_sanciones_agentes {
    Nat sanciones;
    Conj<Nat> agentes;
};

struct tup_id_pos_it {
    Nat id;
    Posicion pos;
    Dicc<Nat, Posicion>::Iterador itPromAgentes;

    tup_id_pos_it(Nat id, Posicion pos, Dicc<Nat, Posicion>::Iterador itPromAgentes);
};

class Sistema {

public:
    // Comenzar Rastrillaje.
                            Sistema                 (Campus elCampus, Dicc<Nat, Posicion> diccAgentes);
//                            Sistema                 (const Sistema &original);
                            ~Sistema                ();
    Campus                  DameCampus              ();
    Conj<String>::Iterador  Estudiantes             ();
    Conj<String>::Iterador  Hippies                 ();
    Conj<Nat >::Iterador    Agentes                 ();
    Posicion                PosEstudianteYHippie    (String nombre);
    Posicion                PosAgente               (Nat id);
    Nat                     CantSanciones           (Nat id);
    Nat                     CantHippiesAtrapados    (Nat id);
    void                    IngresarEstudiante      (String nombre, Posicion posicion);
    void                    IngresarHippie          (String nombre, Posicion posicion);
    void                    MoverEstudiante         (String nombre, Direccion dir);
    void                    MoverHippie             (String nombre);
    void                    MoverAgente             (Nat id);
    Nat                     MasVigilante            ();
    Conj<Nat>               ConMismasSanciones      (Nat id);
    Conj<Nat>               ConKSanciones           (Nat k);
    Nat                     CantHippies             ();
    Nat                     CantEstudiantes         ();
    Nat CantAgentes();
private:
    // Funciones Privadas
    void                            Transformar                 (Posicion posicion);
    void                            Capturar                    (Posicion posicion);
    void                            SumarCaptura                (Posicion posicion);
    void                            SumarCapturaAgentes         (Arreglo<Posicion> arreglo);
    Arreglo<tup_sanciones_agentes>  DeListaAArreglo             (Lista<tup_sanciones_agentes> lista);
    // Falta BusquedaLogaritmica
    Posicion                        TargetMasCercano            (Posicion pos, DiccString<Posicion> &dicc);
    bool                            SePuedeMoverParaLlegar      (Posicion origen, Posicion destino);
    Posicion                        NuevaPosParaLlegar          (Posicion origen, Posicion destino);
    bool                            Rodeado                     (Posicion posicion);
    bool                            HayVecinoAgente             (Posicion posicion);
    Arreglo<Posicion>               VecinosHippies              (Posicion posicion);
    Arreglo<Posicion>               VecinosEstudiantes          (Posicion posicion);
    Arreglo<Posicion>               VecinosAgentes              (Posicion posicion);
    bool                            HayPorLoMenosUnVecinoHippie (Posicion posicion);
    bool                            TodosVecinosEstudiantes     (Posicion posicion);
    void                            SumarSancion                (Posicion posicion);


    tup_id_pos_it busqbin(Arreglo<tup_id_pos_it> arr, Nat lower, Nat upper, Nat id) {
        if (id > arr.Tamanho()) {
            return tup_id_pos_it(id, Posicion(-1, -1), Dicc<Nat, Posicion>().CrearIt());
        } else {
            if (lower == upper) {
                return arr[lower];
            } else {
                Nat middle = (upper - lower) / 2 + lower;
                if (arr[middle].id == id) {
                    return arr[middle];
                } else {
                    if (arr[middle].id < id) {
                        return busqbin(arr, middle + 1, upper, id);
                    } else {
                        return busqbin(arr, lower, middle, id);
                    }
                }
            }
        }
    }

    tup_sanciones_agentes busqbin(Arreglo<tup_sanciones_agentes> arr, Nat lower, Nat upper, Nat sancion) {
        if (sancion >= arr.Tamanho()) {

            tup_sanciones_agentes tup;
            tup.sanciones = sancion;
            tup.agentes = Conj<Nat>();
            return tup;

        } else {

            if (lower == upper) {
                return arr[lower];
            } else {
                Nat middle = (upper - lower) / 2 + lower;
                if (arr[middle].sanciones == sancion) {
                    return arr[middle];
                } else {
                    if (arr[middle].sanciones < sancion) {
                        return busqbin(arr, middle+1, upper, sancion);
                    } else {
                        return  busqbin(arr, lower, middle, sancion);
                    }
                }
            }

        }
    }

    // Representacion
    struct tup_matriz{
        String nombre;
        Nat id;
        Nat atrapados;
        Lista<tup_sanciones_agentes>::Iterador itKSanciones;
        Conj<Nat>::Iterador itAgente;
        String rol;

        tup_matriz() {
            rol = "";
        }
    };

    struct tup_id_capturas{
        Nat id;
        Nat capturas;

//        tup_id_capturas(Nat id, Nat capturas);
    };

    Campus campus;
    Arreglo< Arreglo< tup_matriz> > matriz_datos;
    DiccString<Posicion> estudiantes;
    DiccString<Posicion> hippies;
    Conj<Nat> agentes;
    DiccNat<Posicion> promAgentes;
    Arreglo<tup_id_pos_it> logAgentes;
    Lista<tup_sanciones_agentes> kSanLista;
    Arreglo<tup_sanciones_agentes> kSanArreglo;
    bool huboSancion;
    tup_id_capturas masVigilante;
};
#endif //SISTEMA_H
