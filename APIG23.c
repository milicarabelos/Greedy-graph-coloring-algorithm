
#include "APIG23.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EstructuraGrafo23.h"

// construcci'on/destrucci'on

/*debe leer desde stdin
Debo calcular el Delta
*/
Grafo ConstruirGrafo(FILE *f_input) {
    char         line[256];
    unsigned int n, m, x, y;
    Grafo        my_grafo;

    while (fgets(line, sizeof(line), f_input)) {
        if (line[0] == 'c') {
            // hago skip a esta linea y continuo a la siguiente
            continue;
        } else if (line[0] == 'p') {
            sscanf(line, "p edge %u %u", &n, &m);
            printf("n = %u, m = %u\n", n, m);
            my_grafo = init_grafo(n, m);
            break;
        } else {
            // En caso de error devuelvo NULL
            return NULL;
        }
    }
    /* Tengo que sacar las ultimas dos guardas, luego de encontrar la linea con p tengo m lineas de formato e num num donde cargo los lados,
   si tengo una linea con otro formato deberia dar error,  despues de m lineas puede haber una cantidad arbitraria de lineas sin formato
   por lo que no tengo que seguir leyendo
    */
    for (size_t i = 0; i < m; i++) {
        fgets(line, sizeof(line), f_input);
        if (line[0] != 'e') {
            // ERROR en formato
            return NULL;
        } else {
            // revisar
            // aca entiendo deberiamos cargar desp ordenar y desp cargar los vertices pero pa eso deberiamos recorrer los vertices y eso esta raro
            sscanf(line, "e %u %u", &x, &y);
            cargar_lado(my_grafo->list_lados, i, x, y);
        }
    }

    // ordeno los lados de menor a mayor por primera y segunda componente
    qsort(my_grafo->list_lados, my_grafo->cant_lados, sizeof(Tupla), cmp_tuples);
}

void DestruirGrafo(Grafo G) {
    G = destroy_grafo(G);
}

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

unsigned int Nombre(unsigned int i, Grafo G) {
    return G->list_vertices[i]->nombre;
}
unsigned int Grado(unsigned int i, Grafo G) {
    return G->list_vertices[i]->grado;
}

unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G) {
    if (i >= G->cant_vertices || j >= G->list_vertices[i]->grado) {
        return 2 ^ 32 - 1;
        // caso de error
    }

    return G->list_vertices[i]->indice_vecinos[j];
}
