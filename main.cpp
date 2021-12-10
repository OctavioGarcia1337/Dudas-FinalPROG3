#include <iostream>
#include "Arbol/ArbolBinario.h"
using namespace std;


int main() {
    ArbolBinario<int> arb;

    arb.put(15);
    arb.put(11);
    arb.put(26);
    arb.put(8);
    arb.put(12);
    arb.put(20);
    arb.put(30);
    arb.put(6);
    arb.put(9);
    arb.put(14);
    arb.put(35);

    system("cls");
    cout << "\n\t SumarNivelPerValue: " << arb.sumarNivelPerValue(15);
    cout << "\n\t SumarNivel: " << arb.sumarNivel(0);
    cout << "\n\t SumarDesdeNivel: " << arb.sumarDesdeNivel(0);
    cout << "\n\t LevelCounter: " << arb.LevelCounter();

    return 0;
}