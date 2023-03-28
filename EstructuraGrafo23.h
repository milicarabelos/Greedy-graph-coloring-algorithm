#ifndef EstructuraGrafo23_H
#define EstructuraGrafo23_H

#include "APIG23.h"

typedef struct
{
    unsigned int x;
    unsigned int y;
} Tupla;

//[punt a _s_vert,...,.]
// direcciones de memoria
//  0,................n
// need pedir memoria para los _s_vertices
typedef struct {
    unsigned int  nombre;
    unsigned int  grado;
    unsigned int *indice_vecinos;
} vertice;

struct GrafoSt {
    vertice     *list_vertices;  // ordenar por indice
    Tupla       *list_lados;     // ordenar para cargar vertices
    unsigned int cant_vertices;
    unsigned int cant_lados;
    unsigned int mayor_grado;  // Δ
    unsigned int menor_grado;  // δ
};

/*
Crea un nuevo grafo con la cantidad de vertices
y la cantidad de lados
*/
// Grafo init_grafo(unsigned int n, unsigned int m);
/*
Crea un nuevo vertice con el nombre
*/
// vertice init_vertice(unsigned int nombre);
//  revisar
// void cargar_lado(Tupla *lista_lados, int i, unsigned int primero, unsigned int segundo);

// int cmp_tuples(const void *a, const void *b);

// Grafo destroy_grafo(Grafo grafo);

#endif