
typedef struct
{
    unsigned int x;
    unsigned int y;
} Tupla;

struct _grafo
{
    unsigned int *list_vertices; // ordenar por indice
    Tupla *list_lados;           // ordenar para cargar vertices
    unsigned int n;              // cant de vertices
    unsigned int m;              // cant de lador
    unsigned int mayor_grado;
    unsigned int menor_grado;
};

struct _vertice
{
    unsigned int indice;
    unsigned int grado;
    unsigned int *vecinos;
};