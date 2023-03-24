#ifndef EstructuraGrafo23_H
#define EstructuraGrafo23_H

typedef struct _s_vertice *vertice;

typedef struct
{
    unsigned int x;
    unsigned int y;
} Tupla;

struct GrafoSt {
    unsigned int *list_vertices;  // ordenar por indice
    Tupla        *list_lados;     // ordenar para cargar vertices
    unsigned int  cant_vertices;
    unsigned int  cant_lados;
    unsigned int  mayor_grado;  // Δ
    unsigned int  menor_grado;  // δ
};

struct _s_vertice {
    unsigned int nombre;
    // capaz indice creo que no vale la pena agregar ese campo
    unsigned int  grado;
    unsigned int *indice_vecinos;
};

#endif