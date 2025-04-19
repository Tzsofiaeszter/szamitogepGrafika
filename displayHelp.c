#include <stdio.h>
#include "displayHelp.h"

bool show_help = false;       // nem mutatja a degítséget, hacsak nem nyojuk meg a h gombot " h = help "

void toggleHelp() {
    show_help = !show_help;
}

void displayHelpText() {
    if (show_help) {
        printf("Használati útmutató:\n");
        printf("W/A/S/D - Mozgás / Kamera\n");
        printf("+ / -   - Fényerő állítása\n");
        printf("O       - Belépés a nappaliba\n");
        printf("H       - Súgó megjelenítése/elrejtése\n");
        printf("ESC     - Kilépés\n");
    }
}


