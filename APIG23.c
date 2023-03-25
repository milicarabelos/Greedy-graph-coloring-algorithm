#include "APIG23.h"

#include <stdint.h>
#include <string.h>

#include "EstructuraGrafo23.h"
// construcci'on/destrucci'on

Grafo ConstruirGrafo(FILE *f_input)
/*debe leer desde stdin
Debo calcular el Delta
*/
{
    char line[256];
    unsigned int n, m, x, y;
    Grafo my_grafo;

    while (fgets(line, sizeof(line), f_input))
    {
        if (line[0] == 'c')
        {
            // hago skip a esta linea y continuo a la siguiente
            continue;
        }
        else if (line[0] == 'p')
        {
            sscanf(line, "p edge %u %u", &n, &m);
            printf("n = %u, m = %u\n", n, m);
            my_grafo = init_grafo(n, m);
            break;
        }
        else
        {
            // En caso de error devuelvo NULL
            return NULL;
        }
    }
    /*  Tengo que sacar las ultimas dos guardas, luego de encontrar la linea con p tengo m
        lineas de formato e num num donde cargo los lados,
        si tengo una linea con otro formato deberia dar error,
        despues de m lineas puede haber una cantidad arbitraria de lineas sin formato
        por lo que no tengo que seguir leyendo
    */
    for (size_t i = 0; i < m; i++)
    {
        fgets(line, sizeof(line), f_input);
        if (line[0] != 'e')
        {
            // ERROR en formato
            return NULL;
        }
        else
        {
            // revisar
            sscanf(line, "e %u %u", &x, &y);
            cargar_lado(my_grafo->list_lados, i, x, y);
        }
    }
}

void DestruirGrafo(Grafo G)
{
    /*
        No se si deberíamos de hacer free a los vertices. Si es así
        struct Vertice* current = G->list_vertices
        struct Vertice* temp;

        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }
    */
    free(G->list_vertices);
    free(G->list_lados);
    G->mayor_grado = 0;
    G->menor_grado = 0;
    G->list_vertices = NULL;
    G->list_lados = NULL;
    G->cant_vertices = 0;
    G->cant_lados = 0;
}

unsigned int NumeroDeVertices(Grafo G)
{
    return G->cant_vertices;
}
unsigned int NumeroDeLados(Grafo G)
{
    return G->cant_lados;
}
unsigned int Delta(Grafo G)
{
    return G->mayor_grado;
}
// funciones de extraccion de informacion de vertices

unsigned int Nombre(unsigned int i, Grafo G);
unsigned int Grado(unsigned int i, Grafo G);
unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G);

unsigned int NumeroDeLados(Grafo G)
{
    return G->cant_lados;
}
unsigned int Delta(Grafo G)
{
    return G->mayor_grado;
}
// funciones de extraccion de informacion de vertices

unsigned int Nombre(unsigned int i, Grafo G);
unsigned int Grado(unsigned int i, Grafo G);
unsigned int IndiceVecino(unsigned int j, unsigned int i, Grafo G);