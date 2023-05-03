#include <assert.h>
#include <stdio.h>

#include "../APIG23.h"
#include "../APIParte2.h"

void error(char msg) {
    if (msg == 1) {
        printf("error en Orden\n");
    }
}

void test_OrdenImparPar(Grafo my_graph) {
    u32 n = NumeroDeVertices(my_graph);
    u32 *Orden = calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    };
    u32 *Color = calloc(n, sizeof(u32));
    u32 min_col = Greedy(my_graph, Orden, Color);

    printf("min_col: %d\n", min_col);
    for (u32 i = 0; i < n; i++) {
        printf("Color de %u : %u\n", i, Color[i]);
    }
    for (u32 i = 0; i < n; i++) {
        printf("%u, ", Orden[i]);
    }
    printf("\n");

    char result;

    /*   result = OrdenImparPar(n, Orden, Color);
       error(result);
       // caso 1
        assert(result == 0);
       assert(Orden[0] == 1 || Orden[0] == 2);
       assert(Orden[1] == 1 || Orden[1] == 2);
       assert(Orden[2] == 0 || Orden[2] == 0);
       assert(Orden[3] == 3 || Orden[3] == 3);

       result = OrdenJedi(my_graph, Orden, Color);
       error(result);
       assert(Orden[0] == 1 || Orden[0] == 2);
       assert(Orden[1] == 1 || Orden[1] == 2);
       assert(Orden[2] == 0 || Orden[2] == 0);
       assert(Orden[3] == 3 || Orden[3] == 3); */

    // caso 2.1
    /*     result = OrdenImparPar(n, Orden, Color);
        error(result);
        printf("Orden: ");

        assert(result == 0);
        assert(Orden[0] == 1 || Orden[0] == 2);
        assert(Orden[1] == 1 || Orden[1] == 2);
        assert(Orden[2] == 3);
        assert(Orden[3] == 0);

        result = OrdenJedi(my_graph, Orden, Color);
        error(result);
        assert(Orden[0] == 3);
        assert(Orden[1] == 1 || Orden[1] == 2);
        assert(Orden[2] == 2 || Orden[2] == 2);
        assert(Orden[3] == 0); */

    // caso 2.2
    result = OrdenImparPar(n, Orden, Color);
    error(result);
    printf("Orden: ");

    assert(result == 0);
    assert(Orden[0] == 1);
    assert(Orden[1] == 2);
    assert(Orden[2] == 3 || Orden[2] == 0);
    assert(Orden[3] == 0 || Orden[3] == 3);

    result = OrdenJedi(my_graph, Orden, Color);
    error(result);
    assert(Orden[0] == 2);
    assert(Orden[1] == 1);
    assert(Orden[2] == 0 || Orden[2] == 3);
    assert(Orden[3] == 0 || Orden[3] == 3);
    //  add more test cases here
}

int main(void) {
    Grafo my_graph = ConstruirGrafo();
    test_OrdenImparPar(my_graph);
    return 0;
}