
/*|-----------------------------------|*/
/*|           Busquedas de IA         |  
  |Diseñado por:                      |
  |  Maria L. Regino Salgado          | 
  |  Brian S. Cañon Rojas             |
  |  Códigos:-20182578014             |
  |  -20191578110                     |
  |              UDFJC                |
  |              2021                 | */
/*|-----------------------------------|*/


/*---------Recomendaciones: ------------------------------------------------------------
  1. No usar DEV-C++ dado a que este usa un compilador desactualizado.
  2. Usar un compilador GCC u otro que este al día, además de usar VS Code como IDE.
  3. Si usa un compilador desactualizado, lo más probable es que el código no compile. 
  4. Algunos métodos presentados acá fueron recuperados de diferentes autores y bibliografias
  creditos a sus respectivos autores. 
-----------------------------------------------------------------------------------------*/

/*----------------Inicio del código ----------------------------------*/

/* En este apartado se hace una sobrecarga al operador << para poder imprimir el grafo (árbol)
para mostrar el nodo con sus respectivos vecinos */

#include "busquedadpapp.hpp" //Libreria con el código fuente de los métodos

ostream& operator<<(ostream &out, const Grafo &grafo){
    for(auto const &vertice: grafo){
        out<<vertice.first<<": "; //Se imprime el nodo principal o padre
        out<<"[";
        for(size_t i=0;i<vertice.second.size();++i){
            out<<vertice.second[i]; // Se imprimen los hijos del nodo principal
            if(i!=vertice.second.size()-1){
                out<<", "; //Si el vecino no es el último se imprime una ,
            }
        }
        out<<"]"<<endl;
    }
    return out;
}

int main(){
    Grafo grafo; //Se crea la instancia del arbol,grafo, etc.
    /* Se añade el padre [] y sus vecinos {}*/
    grafo["A"] = {"B","C","D"};
    grafo["B"] = {"E","F"};
    grafo["C"] = {"G"};
    grafo["D"] = {"H","I","J"};
    grafo["E"] = {"K"};
    grafo["F"] = {};
    grafo["G"] = {"L","M"};
    grafo["H"] = {};
    grafo["I"] = {};
    grafo["J"] = {"N","O"};
    grafo["K"] = {};
    grafo["L"] = {};
    grafo["M"] = {};
    grafo["N"] = {};
    grafo["O"] = {};
    cout<<grafo;//Se usa la sobrecarga del operador << para imprimir el grafo
    cout<<"------Amplitud iterativa------"<<endl;
    vector<string> recorrido2 =  busqueda_amplitud_iterativa(grafo,"A","F");
    for(auto const &vertice: recorrido2){
        cout<<vertice<<endl;
    }
    return 0;
}