#ifndef EstructuraGrafo23_H
#define EstructuraGrafo23_H

typedef unsigned int u32;

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
    unsigned int nombre;
    unsigned int grado;
    unsigned int *indiceVecinos;
    unsigned int indice;
} vertice;

typedef struct {
    vertice *listVertices;  // ordenar por indice
    Tupla *listLados;       // ordenar para cargar vertices
    unsigned int cantVertices;
    unsigned int cantLados;
    unsigned int mayorGrado;  // Δ
} GrafoSt;

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