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

#ifndef BUSQUEDADPAPP_H
#define BUSQUEDADPAPP_H

/*----------------Inicio del código ----------------------------------*/

#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

//Mapa para representar un grafo la KEY 1 es el nombre y la KEY 2 los vecinos en un VECTOR
typedef map<string, vector<string>> Grafo;

//Definición de metodos para usar de manera recursiva 
bool busqueda_profundidad_iterativa(const Grafo &grafo,string origen,string destino);
bool busqueda_profundidad_limitada(const Grafo &grafo,string origen,string destino,int profundidad);

/*-------Busqueda en profundidad básica-------------*/
//Pseudo: https://es.wikipedia.org/wiki/Búsqueda_en_profundidad

vector<string> busqueda_profundidad(const Grafo &grafo,const string &origen="A",const string &destino="F"){
    //Variables necesarias para poder ejecutar la busqueda
    vector<string> visitados;
    stack<string> pila;
    vector<string> recorrido;
    visitados.push_back(origen);//El primer visitado será el origen por eso se añade
    pila.push(origen);//Añadimos el origen a la pila
    while (!pila.empty())
    {  
        //Mientras que nuestra pila no este vacia hacer:
        auto const &vertice = pila.top();//Tomamos el primer elemento de la pila
        recorrido.push_back(vertice); //Añadimos el origen a la pila
        if(strcmp(vertice.c_str(),destino.c_str())==0){//Si hubo éxito en la busqueda STOP
            break;
        }  
        pila.pop();//Vaciamos la pila
        auto const &adyacentes = grafo.at(vertice);//Buscamos el nodo en el grafo.at()
        for(size_t i=0;i<adyacentes.size();++i){
                auto const &ady=adyacentes[i];//Obtenemos una lista de vecinos
                if(find(visitados.begin(),visitados.end(),ady)==visitados.end()){//Si dicho nodo fue visitado
                    visitados.push_back(ady);//Lo metemos en la lista de visitados
                    pila.push(ady);//Apilamos a la pila ese nodo para expandirlo 
                }
        }
    }
    return recorrido;
}

/*-------Busqueda por amplitud básica --------------*/
//Pseudo: https://es.wikipedia.org/wiki/Búsqueda_en_anchura

vector<string> busqueda_amplitud(const Grafo &grafo,const string &origen="A",const string &destino="F"){
    //Variables necesarias para poder ejecutar la busqueda
    vector<string> visitados;
    queue<string> cola;
    vector<string> recorrido;
    visitados.push_back(origen); //El primer visitado será el origen por eso se añade
    cola.push(origen); //Añadimos el origen a la cola 
    while (!cola.empty())
    {
        //Mientras que nuestra cola no este vacia hacer:
        auto const &vertice = cola.front(); //Tomamos el primer elemento de la cola
        recorrido.push_back(vertice); //En el recorrido meter el vertice
        if(strcmp(vertice.c_str(),destino.c_str())==0){//Si hubo éxito en la busqueda STOP
            break;
        }  
        cola.pop(); //Vaciamos la cola
        auto const &adyacentes = grafo.at(vertice); //Buscamos el nodo en el grafo.at()
        //Expandimos
        for(size_t i=0;i<adyacentes.size();++i){
                auto const &ady=adyacentes[i]; //Obtenemos una lista de vecinos
                if(find(visitados.begin(),visitados.end(),ady)==visitados.end()){ //Si dicho nodo fue visitado
                    visitados.push_back(ady);//Lo metemos en la lista de visitados
                    cola.push(ady);//Apilamos a la cola ese nodo para expandirlo 
                }
        }   
    }
    return recorrido;
}

/*--------Profundidad iterativa ----------------*/
//Pseudo: https://es.wikipedia.org/wiki/Búsqueda_en_profundidad_iterativa 

bool  busqueda_profundidad_iterativa(const Grafo &grafo,string origen,string destino){
  int profundidad = 0; //Se crea la profundidad para nuestro recorrido 
  auto resultado=false; //Una variable de control para romper el bucle infinito
  while(!resultado){//Mientras que no termine nuestra busqueda ejecutaremos una BPL para encontrar el nodo obetivo
     resultado=busqueda_profundidad_limitada(grafo,origen,destino,profundidad);
     profundidad++; //Aumentamos la profundidad   
  }
   return resultado;
}
bool busqueda_profundidad_limitada(const Grafo &grafo,string origen,string destino,int profundidad){
    bool resultado = false; //Variable de control para el bucle infinito
   if(strcmp(origen.c_str(),destino.c_str())==0){
                return true; //Si el origen es igual al destino, se rompe el bucle
                 }
     if(profundidad>=0){ //Si la profundiad es mayor o igual a 0 se expande el grafo
    //Expansión del grafo
    for(auto vertice: grafo){
        for(size_t i=0;i<vertice.second.size();++i){
           cout<<vertice.second[i]<<endl;
           //Si el vecino es igual al destino romper el bucle 
           if(strcmp(vertice.second[i].c_str(),destino.c_str())==0){ 
               resultado = true;
               return resultado;
               break;
           }
           //De lo contrario debe llamarse recursivamente restandole a la profundidad hasta encontrar el destino
           resultado = busqueda_profundidad_limitada(grafo,vertice.second[i],destino,profundidad-1);
            }
        }
    }
   
    return resultado;
}

/*--------Amplitud iterativa ----------------*/
//Pseudo: http://inteligenciaartificialap.blogspot.com/2017/03/amplitud-iterativa-ibs.html 

vector<string> busqueda_amplitud_iterativa(const Grafo &grafo,const string &origen="A",const string &destino="F"){
    //Variables necesarias para poder ejecutar la busqueda
    vector<string> visitados;
    queue<string> cola;
    vector<string> recorrido;
    int anchura=0; //Variable de control para controlar hasta donde se va a expandir
    visitados.push_back(origen); //El primer visitado será el origen por eso se añade
    cola.push(origen); //Añadimos el origen a la cola 
    while (!cola.empty())
    {
        //Mientras que nuestra cola no este vacia hacer:
        auto const &vertice = cola.front(); //Tomamos el primer elemento de la cola
        recorrido.push_back(vertice); //En el recorrido meter el vertice
        if(strcmp(vertice.c_str(),destino.c_str())==0){//Si hubo éxito en la busqueda STOP
            break;
        }  
        cout<<"Niveles de anchura: "<<anchura<<endl;
        cola.pop(); //Vaciamos la cola
        auto const &adyacentes = grafo.at(vertice); //Buscamos el nodo en el grafo.at()
        //Expandimos de acuerdo de la anchura
        for(size_t i=anchura;i<adyacentes.size();++i){
                auto const &ady=adyacentes[i]; //Obtenemos una lista de vecinos de acuerdo al nivel de anchura
                if(find(visitados.begin(),visitados.end(),ady)==visitados.end()){ //Si dicho nodo fue visitado
                    visitados.push_back(ady);//Lo metemos en la lista de visitados
                    cola.push(ady);//Apilamos a la cola ese nodo para expandirlo 
                }
        }
         anchura++; //Si no es objetivo o el que buscabamos aumenta el ancho   
    }
    return recorrido;
}

#endif
