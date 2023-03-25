#ifndef EstructuraGrafo23_H
#define EstructuraGrafo23_H

typedef struct _s_vertice *Vertice;

typedef struct
{
    unsigned int x;
    unsigned int y;
} Tupla;

struct GrafoSt
{
    unsigned int *list_vertices; // ordenar por indice
    Tupla *list_lados;           // ordenar para cargar vertices
    unsigned int cant_vertices;
    unsigned int cant_lados;
    unsigned int mayor_grado; // Δ
    unsigned int menor_grado; // δ
};

struct _s_vertice
{
    unsigned int nombre;
    unsigned int grado;
    unsigned int *puntero_vecino;
};

Grafo init_grafo(unsigned int n, unsigned int m);
/*
Crea un nuevo grafo con la cantidad de vertices
y la cantidad de lados
*/

Vertice init_vertice(unsigned int nombre);
/*
Crea un nuevo Vertice con el nombre
*/

void cargar_lado(Tupla *lista_lados, int i, unsigned int primero, unsigned int segundo);
#endif