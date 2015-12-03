// Created by Sebastián Matias Giambastiani on 22/11/15

#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "aed2/Dicc.h"
#include "DiccString.h"
#include "DiccNat.h"
#include <algorithm>
#include "Campus.h"
#include "Sistema.h"

using namespace aed2;

bool menortupla(tup_id_pos_it a, tup_id_pos_it b){
    return a.id < b.id;
}

tup_id_pos_it::tup_id_pos_it(Nat id, Posicion pos, Dicc<Nat, Posicion>::Iterador itPromAgentes): id(id), pos(pos), itPromAgentes(itPromAgentes) {
}

//Sistema::tup_id_capturas::tup_id_capturas(Nat id, Nat capturas): id(id), capturas(capturas) {
//}

Sistema::Sistema(Campus elCampus, Dicc<Nat, Posicion> diccAgentes) :campus(elCampus), promAgentes(diccAgentes.CantClaves()),
                                                                logAgentes(diccAgentes.CantClaves()),
                                                                kSanArreglo(diccAgentes.CantClaves()), estudiantes(), hippies(), masVigilante() {
    // Creo la matriz de datos
    matriz_datos = Arreglo< Arreglo< tup_matriz> > (elCampus.Filas());
    for (int i = 0; i < elCampus.Filas(); ++i) {
        matriz_datos.Definir(i, Arreglo<tup_matriz>(elCampus.Columnas()));
        for (int j = 0; j < elCampus.Columnas(); ++j) {
            matriz_datos[i].Definir(j, tup_matriz());
        }
    }

    //Defino diccionario hash de agentes.
    // Defino arreglo de agentes: tupla(placa, posicion, itDiccLineal)
    kSanLista = Lista<tup_sanciones_agentes>();
    Conj<Nat> losAgentes;
    Conj<Nat> agentes0san;
    int i = 0;
    Dicc<Nat, Posicion>::Iterador it = diccAgentes.CrearIt();
    while (it.HaySiguiente()){
        Nat id = it.SiguienteClave();
        Posicion pos = it.SiguienteSignificado();
        losAgentes.AgregarRapido(id);
        Dicc<Nat, Posicion>::Iterador itag = promAgentes.Definir(id,pos);

        logAgentes.Definir(i, tup_id_pos_it (id, pos, itag));

        Conj<Nat>::Iterador itagconj = agentes0san.AgregarRapido(id);
        matriz_datos[pos.x][pos.y].nombre = "";
        matriz_datos[pos.x][pos.y].id = id;
        matriz_datos[pos.x][pos.y].atrapados = 0;
        //acá no inicializo el iterador de kSanLista porque después no apunta bien.
        matriz_datos[pos.x][pos.y].itAgente = itagconj;
        matriz_datos[pos.x][pos.y].rol = "AGENTE";
        ++i;
        it.Avanzar();
    }

    agentes = losAgentes;

    tup_sanciones_agentes nuevo;
    nuevo.sanciones = 0;
    nuevo.agentes = agentes0san;
    kSanLista.AgregarAtras(nuevo);

    //acá inicializo el iterador de kSanLista.
    Dicc<Nat, Posicion>::Iterador otroIT = diccAgentes.CrearIt();
    while (otroIT.HaySiguiente()) {
        Posicion pos = otroIT.SiguienteSignificado();
        matriz_datos[pos.x][pos.y].itKSanciones = kSanLista.CrearIt();
        otroIT.Avanzar();
    }

    //std::sort(logAgentes[0], logAgentes[agentes.Cardinal()], menortupla);
    //mergeSort(logAgentes);
    huboSancion = false;
    masVigilante.id = logAgentes[0].id;
    masVigilante.capturas = 0;
    kSanArreglo = DeListaAArreglo(kSanLista);
}

//Sistema::Sistema(const Sistema &original) { }

Sistema::~Sistema() {
}

Campus Sistema::DameCampus() {
    return campus;
}

Conj<String>::Iterador Sistema::Estudiantes() {
    return estudiantes.Claves().CrearIt();
}

Conj<String>::Iterador Sistema::Hippies() {
    return hippies.Claves().CrearIt();
}

Conj<Nat >::Iterador Sistema::Agentes() {
    return agentes.CrearIt();
}

Posicion Sistema::PosEstudianteYHippie(String nombre) {
    if (estudiantes.Def(nombre))
        return estudiantes.Obtener(nombre);
    else
        return hippies.Obtener(nombre);
}

Posicion Sistema::PosAgente(Nat id) {
    return promAgentes.Obtener(id);
}

Nat Sistema::CantSanciones(Nat id) {
    Posicion pos = PosAgente(id);
    return matriz_datos[pos.x][pos.y].itKSanciones.Siguiente().sanciones;
}

Nat Sistema::CantHippiesAtrapados(Nat id) {
    Posicion pos = PosAgente(id);
    return matriz_datos[pos.x][pos.y].atrapados;
}

void Sistema::IngresarEstudiante(String nombre, Posicion posicion) {
    estudiantes.Definir(nombre, posicion);
    matriz_datos[posicion.x].Definir(posicion.y, tup_matriz());
    matriz_datos[posicion.x][posicion.y].nombre = nombre;
    matriz_datos[posicion.x][posicion.y].id = 0;
    matriz_datos[posicion.x][posicion.y].atrapados = 0;
    // Para chequear si es NULL crear un it vacio y comparar.
    matriz_datos[posicion.x][posicion.y].itKSanciones = Lista<tup_sanciones_agentes>().CrearIt();
    // Para chequear si es NULL crear un it vacio y comparar.
    matriz_datos[posicion.x][posicion.y].itAgente = Conj<Nat>().CrearIt();
    matriz_datos[posicion.x][posicion.y].rol = "ESTUDIANTE";
    bool seTransforma = HayPorLoMenosUnVecinoHippie(posicion);
    Arreglo<Posicion> vecinosHippies = VecinosHippies(posicion);
    for (int i = 0; i < 4; ++i){
        if (vecinosHippies.Definido(i) && TodosVecinosEstudiantes(vecinosHippies[i])){
            Transformar(vecinosHippies[i]);
        }
    }
    if (Rodeado(posicion)){
        Arreglo<Posicion> vecinosAgentes = VecinosAgentes(posicion);
        for (int i = 0; i < 4; ++i){
            if (vecinosAgentes.Definido(i)){
                SumarSancion(vecinosAgentes[i]);
            }
        }
    }
    if (seTransforma) {
        Transformar(posicion);
    }
}

void Sistema::IngresarHippie(String nombre, Posicion posicion) {
    hippies.Definir(nombre, posicion);
    matriz_datos[posicion.x].Definir(posicion.y, tup_matriz());
    matriz_datos[posicion.x][posicion.y].nombre = nombre;
    matriz_datos[posicion.x][posicion.y].id = 0;
    matriz_datos[posicion.x][posicion.y].atrapados = 0;
    // Para chequear si es NULL crear un it vacio y comparar.
    matriz_datos[posicion.x][posicion.y].itKSanciones = Lista<tup_sanciones_agentes>().CrearIt();
    // Para chequear si es NULL crear un it vacio y comparar.
    matriz_datos[posicion.x][posicion.y].itAgente = Conj<Nat>().CrearIt();
    matriz_datos[posicion.x][posicion.y].rol = "HIPPIE";
    bool seTransforma = TodosVecinosEstudiantes(posicion);
    Arreglo<Posicion> vecinosEstudiantes = VecinosEstudiantes(posicion);
    for (int i = 0; i < 4; ++i) {
        if (vecinosEstudiantes.Definido(i) && HayPorLoMenosUnVecinoHippie(vecinosEstudiantes[i])) {
            Transformar(vecinosEstudiantes[i]);
        }
    }
    bool hubocaptura = false;
    if (Rodeado(posicion)) {
        Arreglo<Posicion> vecinosAgentes = VecinosAgentes(posicion);
        for (int i = 0; i < 4; ++i) {
            if (vecinosAgentes.Definido(i)) {
                hubocaptura = true;
                SumarCaptura(vecinosAgentes[i]);
            }
        }
    }
    if (hubocaptura) {
        Capturar(posicion);
    } else {
        if (seTransforma) {
            Transformar(posicion);
        }
    }
}

void Sistema::MoverEstudiante(String nombre, Direccion dir){
    Posicion pos = estudiantes.Obtener(nombre);
    Posicion nuevaPos = campus.ProxPosicion(pos, dir);
    //libero la posición en la que estaba
    matriz_datos[pos.x][pos.y] = tup_matriz();
    pos = nuevaPos;
    if (!campus.PosValida(pos)) {
        estudiantes.Borrar(nombre);
    } else {
        //guardo al estudiante en el trie de estudiantes y actualizo su nueva posición en matriz_datos
        estudiantes.Definir(nombre,pos);
        matriz_datos[pos.x].Definir(pos.y, tup_matriz());
        matriz_datos[pos.x][pos.y].nombre = nombre;
        matriz_datos[pos.x][pos.y].id = 0;
        matriz_datos[pos.x][pos.y].atrapados = 0;
        // Para chequear si es NULL crear un it vacio y comparar.
        matriz_datos[pos.x][pos.y].itKSanciones = Lista<tup_sanciones_agentes>().CrearIt();
        // Para chequear si es NULL crear un it vacio y comparar.
        matriz_datos[pos.x][pos.y].itAgente = Conj<Nat>().CrearIt();
        matriz_datos[pos.x][pos.y].rol = "ESTUDIANTE";
        bool seTranforma = HayPorLoMenosUnVecinoHippie(pos);
        Arreglo<Posicion> vecinosHippies = VecinosHippies(pos);
        for (int i = 0; i < 4; ++i){
            if (vecinosHippies.Definido(i) && TodosVecinosEstudiantes(vecinosHippies[i])){
                Transformar(vecinosHippies[i]);
            }
        }
        //no sumo sanciones porque no está rodeado
        //Si se tenía que transformar, lo transformo
        if (seTranforma){
            Transformar(pos);
        }
    }
}

void Sistema::MoverHippie(String nombre) {
    Posicion pos = hippies.Obtener(nombre);
    Posicion destino = TargetMasCercano(pos, estudiantes);
    Posicion nuevaPos = pos;
    if (SePuedeMoverParaLlegar(pos, destino)) {
        nuevaPos = NuevaPosParaLlegar(pos, destino);
    }

    if (pos != nuevaPos) {
        //libero la posición en la que estaba en matriz de datos
        matriz_datos[pos.x][pos.y] = tup_matriz();
        pos = nuevaPos;
        //guardo el hippie en el trie de hippies y actualizo su nueva posición en matriz_datos
        hippies.Definir(nombre, pos);
        matriz_datos[pos.x].Definir(pos.y, tup_matriz());
        matriz_datos[pos.x][pos.y].nombre = nombre;
        matriz_datos[pos.x][pos.y].id = 0;
        matriz_datos[pos.x][pos.y].atrapados = 0;
        // Para chequear si es NULL crear un it vacio y comparar.
        matriz_datos[pos.x][pos.y].itKSanciones = Lista<tup_sanciones_agentes>().CrearIt();
        // Para chequear si es NULL crear un it vacio y comparar.
        matriz_datos[pos.x][pos.y].itAgente = Conj<Nat>().CrearIt();
        matriz_datos[pos.x][pos.y].rol = "HIPPIE";
        Arreglo<Posicion> vecinosEstudiantes = VecinosEstudiantes(pos);

        for (int i = 0; i < 4; ++i){
            if (vecinosEstudiantes.Definido(i) && HayPorLoMenosUnVecinoHippie(vecinosEstudiantes[i])){
                Transformar(vecinosEstudiantes[i]);
            }
        }
    }
}

void Sistema::MoverAgente(Nat id) {
    tup_id_pos_it tupAgente = busqbin(logAgentes, 0, logAgentes.Tamanho()-1, id);
    Posicion pos = tupAgente.pos;
    Posicion destino = TargetMasCercano(pos, hippies);
    Posicion nuevaPos = pos;
    if (SePuedeMoverParaLlegar(pos, destino)) {
        nuevaPos = NuevaPosParaLlegar(pos, destino);
    }

    if (pos != nuevaPos) {
        //guardo los datos del agente
        tup_matriz datosAgente = matriz_datos[pos.x][pos.y];
        //libero la posicion vieja
        matriz_datos[pos.x][pos.y] = tup_matriz();
        pos = nuevaPos;
        //guardo la info del agente en su nueva posicion
        tupAgente.itPromAgentes.SiguienteSignificado() = pos;
        tupAgente.pos = pos;
        matriz_datos[pos.x].Definir(pos.y, datosAgente);
        //sumo al agente los atrapes correspondientes
        Arreglo<Posicion> vecinosHippies = VecinosHippies(pos);
        for (int i = 0; i < 4; ++i) {
            if (vecinosHippies.Definido(i) && Rodeado(vecinosHippies[i])) {
                SumarCaptura(pos);
                Capturar(vecinosHippies[i]);
            }
        }
        //sumo al agente las sanciones correspondientes
        Arreglo<Posicion> vecinosEstudiantes = VecinosEstudiantes(pos);
        for (int i = 0; i < 4; ++i) {
            if (vecinosEstudiantes.Definido(i) && Rodeado(vecinosEstudiantes[i])) {
                SumarSancion(pos);
            }
        }
    }
}

Nat Sistema::MasVigilante() {
    return masVigilante.id;
}

Conj<Nat> Sistema::ConMismasSanciones(Nat id) {
    Posicion pos = promAgentes.Obtener(id);
    tup_sanciones_agentes aux = matriz_datos[pos.x][pos.y].itKSanciones.Siguiente();
    return aux.agentes;
}

Conj<Nat> Sistema::ConKSanciones(Nat k) {
    if (huboSancion) {
        kSanArreglo = DeListaAArreglo(kSanLista);
    }
    tup_sanciones_agentes res = busqbin(kSanArreglo, 0, kSanArreglo.Tamanho()-1, k);
    return res.agentes;
}

Nat Sistema::CantHippies() {
    return hippies.Claves().Cardinal();
}

Nat Sistema::CantEstudiantes() {
    return estudiantes.Claves().Cardinal();
}

// Metodos Privados
void Sistema::Transformar(Posicion posicion) {
    string nombre = matriz_datos[posicion.x][posicion.y].nombre;

    if (matriz_datos[posicion.x][posicion.y].rol == "ESTUDIANTE") {
        hippies.Definir(nombre, posicion);
        estudiantes.Borrar(nombre);
        matriz_datos[posicion.x][posicion.y].rol = "HIPPIE";
    } else {
        estudiantes.Definir(nombre, posicion);
        hippies.Borrar(nombre);
        matriz_datos[posicion.x][posicion.y].rol = "HIPPIE";
    }
}

void Sistema::Capturar(Posicion posicion){
    hippies.Borrar(matriz_datos[posicion.x][posicion.y].nombre);
    matriz_datos[posicion.x][posicion.y] = tup_matriz();
}

void Sistema::SumarCaptura(Posicion posicion){
    matriz_datos[posicion.x][posicion.y].atrapados++;
    Nat atrapados = matriz_datos[posicion.x][posicion.y].atrapados;
    Nat id = matriz_datos[posicion.x][posicion.y].id;
    if ((atrapados > masVigilante.capturas) || (atrapados == masVigilante.capturas && id < masVigilante.id)) {

        masVigilante.id = id;
        masVigilante.capturas = atrapados;

    }

}

void Sistema::SumarCapturaAgentes(Arreglo<Posicion> arreglo){
    for (int i = 0; i < arreglo.Tamanho(); ++i){
        if(arreglo.Definido(i)){
            SumarCaptura(arreglo[i]);
        }
    }
}

Arreglo<tup_sanciones_agentes> Sistema::DeListaAArreglo(Lista<tup_sanciones_agentes> lista){
    Arreglo<tup_sanciones_agentes> res = Arreglo<tup_sanciones_agentes>(lista.Longitud());
    Lista<tup_sanciones_agentes>:: Iterador it = lista.CrearIt();
    int i = 0;
    while(it.HaySiguiente()){
        res.Definir(i, it.Siguiente());
        ++i;
        it.Avanzar();
    }
    return res;
}

Posicion Sistema::TargetMasCercano(Posicion pos, DiccString <Posicion> &dicc) {
    Lista<Posicion> losSignificados = dicc.Significados();
    Lista<Posicion>::Iterador itSigD = losSignificados.CrearIt();
    Nat cantSignificados = dicc.Significados().Longitud();
    //si hay targets busco el más cercano
    Posicion posMejor = Posicion(0,0);
    if (itSigD.HaySiguiente()) {
        posMejor = itSigD.Siguiente();
        while(itSigD.HaySiguiente()){
            Posicion posActual = itSigD.Siguiente();
            if(campus.Distancia(posActual, pos) < campus.Distancia(posMejor, pos)){
                posMejor = posActual;
            }
            itSigD.Avanzar();
        }
    } else {
        //sino busco la entrada más cercana.
        Conj<Posicion> ingresosMasCercanos = campus.IngresosMasCercanos(pos);
        posMejor = ingresosMasCercanos.CrearIt().Siguiente();
    }
    return posMejor;
}

bool Sistema::SePuedeMoverParaLlegar(Posicion origen, Posicion destino) {

    if (origen.x < destino.x) {

        if (!campus.Ocupada(Posicion(origen.x + 1, origen.y)) && (!matriz_datos[origen.x + 1].Definido(origen.y) ||
                                                            (matriz_datos[origen.x + 1].Definido(origen.y) &&
                                                             matriz_datos[origen.x + 1][origen.y].nombre == "" &&
                                                             matriz_datos[origen.x + 1][origen.y].id == 0))) {
            return true;
        }

    } else {

        if (!campus.Ocupada(Posicion(origen.x - 1, origen.y)) && (!matriz_datos[origen.x - 1].Definido(origen.y) ||
                                                            (matriz_datos[origen.x - 1].Definido(origen.y) &&
                                                             matriz_datos[origen.x - 1][origen.y].nombre == "" &&
                                                             matriz_datos[origen.x - 1][origen.y].id == 0))) {
            return true;
        }

    }

    if (origen.y < destino.y) {

        if (!campus.Ocupada(Posicion(origen.x, origen.y + 1)) && (!matriz_datos[origen.x].Definido(origen.y + 1) ||
                                                            (matriz_datos[origen.x].Definido(origen.y + 1) &&
                                                             matriz_datos[origen.x][origen.y + 1].nombre == "" &&
                                                             matriz_datos[origen.x][origen.y + 1].id == 0))) {
            return true;
        }

    } else {

        if (!campus.Ocupada(Posicion(origen.x, origen.y - 1)) && (!matriz_datos[origen.x].Definido(origen.y - 1) ||
                                                            (matriz_datos[origen.x].Definido(origen.y - 1) &&
                                                             matriz_datos[origen.x][origen.y - 1].nombre == "" &&
                                                             matriz_datos[origen.x][origen.y - 1].id == 0))) {
            return true;
        }

    }

    return false;
}

Posicion Sistema::NuevaPosParaLlegar(Posicion origen, Posicion destino) {

    if (origen.x < destino.x) {

        if (!campus.Ocupada(Posicion(origen.x + 1, origen.y)) && (!matriz_datos[origen.x + 1].Definido(origen.y) ||
                                                                  (matriz_datos[origen.x + 1].Definido(origen.y) &&
                                                                   matriz_datos[origen.x + 1][origen.y].nombre == "" &&
                                                                   matriz_datos[origen.x + 1][origen.y].id == 0))) {
            return Posicion(origen.x + 1, origen.y);
        }

    } else {

        if (!campus.Ocupada(Posicion(origen.x - 1, origen.y)) && (!matriz_datos[origen.x - 1].Definido(origen.y) ||
                                                                  (matriz_datos[origen.x - 1].Definido(origen.y) &&
                                                                   matriz_datos[origen.x - 1][origen.y].nombre == "" &&
                                                                   matriz_datos[origen.x - 1][origen.y].id == 0))) {
            return Posicion(origen.x - 1, origen.y);
        }

    }

    if (origen.y < destino.y) {

        if (!campus.Ocupada(Posicion(origen.x, origen.y + 1)) && (!matriz_datos[origen.x].Definido(origen.y + 1) ||
                                                                  (matriz_datos[origen.x].Definido(origen.y + 1) &&
                                                                   matriz_datos[origen.x][origen.y + 1].nombre == "" &&
                                                                   matriz_datos[origen.x][origen.y + 1].id == 0))) {
            return Posicion(origen.x, origen.y + 1);
        }

    }

    return Posicion(origen.x, origen.y - 1);

}

bool Sistema::Rodeado(Posicion posicion){
   Arreglo<Posicion> a = campus.PosVecinas(posicion);
   int i;
   for (i = 0; i < 4; ++i){
       if (a.Definido(i) && matriz_datos.Definido(a[i].x) && matriz_datos[a[i].x].Definido(i)){
           break;
       }
   }
   return i==4;
}

bool Sistema::HayVecinoAgente(Posicion posicion){
   Arreglo<Posicion> a = campus.PosVecinas(posicion);
   int i = 0;
   for (i = 0; i < 4; ++i){
       if (a.Definido(i)) {
           if (matriz_datos[a[i].x][a[i].y].rol == "AGENTE") {
               break;
           }
       }
   }

   return i<4;
}

Arreglo<Posicion> Sistema::VecinosHippies(Posicion posicion){
   Arreglo<Posicion> a = campus.PosVecinas(posicion);
   for (int i = 0; i < 4; ++i) {
       if (a.Definido(i)) {
           if (matriz_datos[a[i].x][a[i].y].rol != "HIPPIE") {
               a.Borrar(i);
           }
       }
   }

   return a;
}

Arreglo<Posicion> Sistema::VecinosEstudiantes(Posicion posicion) {
   Arreglo<Posicion> a = campus.PosVecinas(posicion);
   for (int i = 0; i < 4; ++i) {
       if (a.Definido(i)) {
           if (matriz_datos[a[i].x][a[i].y].rol != "ESTUDIANTE") {
               a.Borrar(i);
           }
       }
   }

   return a;
}

Arreglo<Posicion> Sistema::VecinosAgentes(Posicion posicion) {
   Arreglo<Posicion> a = campus.PosVecinas(posicion);
   for (int i = 0; i < 4; ++i) {
       if (a.Definido(i)) {
           if (matriz_datos[a[i].x][a[i].y].rol != "AGENTE") {
               a.Borrar(i);
           }
       }
   }

   return a;
}

bool Sistema::HayPorLoMenosUnVecinoHippie(Posicion posicion){
   Arreglo<Posicion> a = VecinosHippies(posicion);
   int numhipp = 0;
   for (int i = 0; i < 4; ++i){
       if (a.Definido(i)){
           numhipp++;
       }
   }
   return numhipp >= 1;
}

bool Sistema::TodosVecinosEstudiantes(Posicion posicion){
   Arreglo<Posicion> a = campus.PosVecinas(posicion);
   int i;
   for (i = 0; i < 4; ++i) {
       if (a.Definido(i)) {
           if (matriz_datos[a[i].x][a[i].y].rol != "ESTUDIANTE") {
               break;
           }
       }
   }

   return i == 4;
}

void Sistema::SumarSancion(Posicion posicion){
   Lista<tup_sanciones_agentes>::Iterador its = matriz_datos[posicion.x][posicion.y].itKSanciones;
   Conj<Nat>::Iterador ita = matriz_datos[posicion.x][posicion.y].itAgente;
   int id = matriz_datos[posicion.x][posicion.y].id;
   its.EliminarSiguiente();
   int sanAg = its.Siguiente().sanciones+1;
   its.Avanzar();
   if (its.HaySiguiente()){
       if(its.Siguiente().sanciones != sanAg){
           Conj<Nat> nuevo = Conj<Nat>();
           Conj<Nat>::Iterador itaux = nuevo.AgregarRapido(id);
           matriz_datos[posicion.x][posicion.y].itAgente = itaux;
           tup_sanciones_agentes q;
           q.sanciones = sanAg;
           q.agentes = nuevo;
           its.AgregarComoSiguiente(q);
       }else{
           matriz_datos[posicion.x][posicion.y].itAgente = its.Siguiente().agentes.AgregarRapido(id);
       }
   }else{
       Conj<Nat> nuevo = Conj<Nat>();
       Conj<Nat>::Iterador itaux = nuevo.AgregarRapido(id);
       matriz_datos[posicion.x][posicion.y].itAgente = itaux;
       tup_sanciones_agentes q;
       q.sanciones = sanAg;
       q.agentes = nuevo;
       its.AgregarComoSiguiente(q);
   }
   huboSancion = true;
}

Nat Sistema::CantAgentes(){
   Conj<Nat>::Iterador agen = Agentes();
   Nat contador = 0;
   while (agen.HaySiguiente()) {
     agen.Avanzar();
     contador++;
   }
   return contador;
}
