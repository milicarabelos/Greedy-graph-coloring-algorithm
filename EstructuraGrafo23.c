
#include <APIG23.h>
#include <EstructuraGrafo23.h>

Grafo init_grafo(unsigned int n, unsigned int m)
/*
    Crea un nuevo grafo con la cantidad de vertices
    y la cantidad de lados
*/
{
    Grafo new_grafo = calloc(1, sizeof(struct GrafoSt));
    new_grafo->list_lados = (Tupla *)calloc(m, sizeof(unsigned int));
    new_grafo->list_vertices = (Vertice *)calloc(n, sizeof(Vertice));
    new_grafo->cant_vertices = n;
    new_grafo->cant_lados = m;
    new_grafo->mayor_grado = 0;
    new_grafo->menor_grado = 0;

    return new_grafo;
}

Vertice init_vertice(unsigned int nombre)
{
    Vertice new_vertice = calloc(1, sizeof(struct _s_vertice));
    new_vertice->nombre = nombre;
    new_vertice->grado = 0;
    new_vertice->puntero_vecino = NULL;

    // VER ACA COMO PEDIR BIEN LA MEMORIA DE LOS VECINOS PODEMOS PONER NULL ACA Y DESPUES CADA QUE
    // AGREGEMOS UN VECINO VAMOS HACIENDO REALLOC ME PARECE BUENA IDEA TOTAL DIFERENCIAMOS LOS CASOS
    //  CUANDO EL GRADO ES 1 QUE USAMOS CALLOC ELSE REALOCC

    // *juæn
    // Me parece ok, ya que  si queres tener un solo Vertice sin vecinos vas a estar pidiendo memoria
    // al pedo , porque no la vas a usar.
    // Ademas para liberar a los vertices lo que tenemos que hacer es recorrerlo hasta llegar a None
    return new_vertice;
}

// revisar
void cargar_lado(Tupla *lista_lados, int i, unsigned int primero, unsigned int segundo)
{
    lista_lados[i].x = primero;
    lista_lados[i].y = segundo;
}