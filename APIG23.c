#include "APIG23.h"

#include <stdint.h>

// construcci'on/destrucci'on

/*debe leer desde stdin
Debo calcular el Delta
*/
Grafo ConstruirGrafo();

void DestruirGrafo(Grafo G);

// funciones para extraer datos del grafo. unsigned int debe estar definida en el .h de arriba

unsigned int NumeroDeVertices(Grafo G) {
    return G->cant_vertices;
}
unsigned int NumeroDeLados(Grafo G) {
    return G->cant_lados;
}
unsigned int Delta(Grafo G) {
    return G->mayor_grado;
}
// funciones de extraccion de informacion de vertices

unsigned int Nombre(unsigned int i, Grafo G);
unsigned int Grado(unsigned int i, Grafo G);
unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G);