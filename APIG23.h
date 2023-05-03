

#include <stdio.h>
#include <stdlib.h>

// el .h de abajo debe tener definida GrafoSt y unsigned int.
#include "EstructuraGrafo23.h"

// Grafo es un puntero a una estructura GrafoSt, la cual debe estar definida en el .h de arriba
#ifndef APIG23_H
#define APIG23_H

typedef GrafoSt *Grafo;

// construccion/destruccion

// debe leer desde stdin
Grafo ConstruirGrafo();

void DestruirGrafo(Grafo G);

// funciones para extraer datos del grafo. unsigned int debe estar definida en el .h de arriba

unsigned int NumeroDeVertices(Grafo G);
unsigned int NumeroDeLados(Grafo G);
unsigned int Delta(Grafo G);

// funciones de extraccion de informacion de vertices

unsigned int Nombre(unsigned int i, Grafo G);
unsigned int Grado(unsigned int i, Grafo G);
unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G);

#endif
