//
// Created by Fer on 11/21/15.
//

#include "DiccString.h"
#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include <algorithm>
#include<assert.h>
using namespace aed2;
using namespace std;

//para compilar esto suelto, cambiar testearDic por main y compilarlo con g++ -g -o DiccString DiccString.cpp
int main() {

    DiccString<int> dicc;

    //definido a?
    std::cout << "Def?(a): " << dicc.Def("a");
    std::cout << "\n";
    std::cout << "\n";

   //defino a
   dicc.Definir("a", 8);
   std::cout<< "defino a, 8";
   std::cout << "\n";
   std::cout << "\n";

   //definido a?
   std::cout << "Def?(a): " << dicc.Def("a");
   std::cout << "\n";
   std::cout << "\n";

   //significado a
   std::cout << "significado a: " << dicc.Obtener("a");
   std::cout << "\n";
   std::cout << "\n";

   //borro a
   dicc.Borrar("a");
   std::cout<< "borro a";
   std::cout << "\n";
   std::cout << "\n";

   //definido a?
   std::cout << "Def?(a): " << dicc.Def("a");
   std::cout << "\n";
   std::cout << "\n";

   //defino a
   dicc.Definir("a", 8);
   std::cout<< "defino a, 8";
   std::cout << "\n";
   std::cout << "\n";

   //defino ab
   dicc.Definir("ab", 10);
   std::cout<< "defino ab, 10";
   std::cout << "\n";
   std::cout << "\n";

   //definido a?
   std::cout << "Def?(a): " << dicc.Def("a");
   std::cout << "\n";
   std::cout << "\n";

   //definido ab?
   std::cout << "Def?(ab): " << dicc.Def("ab");
   std::cout << "\n";
   std::cout << "\n";

   //claves
   std::cout << "claves: " << dicc.Claves();
   std::cout << "\n";
   std::cout << "\n";

   //significados
   std::cout << "significados: " << dicc.Significados();
   std::cout << "\n";
   std::cout << "\n";

   //obtener a
   std::cout << "obtener a: " << dicc.Obtener("a");
   std::cout << "\n";
   std::cout << "\n";

   //obtener ab
   std::cout << "obtener ab: " << dicc.Obtener("ab");
   std::cout << "\n";
   std::cout << "\n";

   //borro a
   dicc.Borrar("a");
   std::cout<< "borro a";
   std::cout << "\n";
   std::cout << "\n";

   //definido a?
   std::cout << "Def?(a): " << dicc.Def("a");
   std::cout << "\n";
   std::cout << "\n";

   //definido ab?
   std::cout << "Def?(ab): " << dicc.Def("ab");
   std::cout << "\n";
   std::cout << "\n";

   //obtener ab
   std::cout << "obtener ab: " << dicc.Obtener("ab");
   std::cout << "\n";
   std::cout << "\n";

   //claves
   std::cout << "claves: " << dicc.Claves();
   std::cout << "\n";
   std::cout << "\n";

   //significados
   std::cout << "significados: " << dicc.Significados();
   std::cout << "\n";
   std::cout << "\n";

    return 0;

}