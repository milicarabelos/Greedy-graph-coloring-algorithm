#include "APIG23.h"

#include <stdint.h>
#include <string.h>

#include "EstructuraGrafo23.h"
// construcci'on/destrucci'on

/*debe leer desde stdin
Debo calcular el Delta
*/
Grafo ConstruirGrafo(FILE *f_input) {
    char         line[256];
    unsigned int n, m;

    while (fgets(line, sizeof(line), f_input)) {
        if (line[0] == 'c') {
            // hago skip a esta linea y continuo a la siguiente
            continue;
        } else if (line[0] == 'p') {
            sscanf(line, "p edge %d %d", &n, &m);
            printf("n = %d, m = %d\n", n, m);
            Grafo init_grafo(n, m);
        } else if (line[0] == 'e') {
            // la linea es de lado
            // VER IMPLEMENTACION
        }
    }
}

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