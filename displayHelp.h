#ifndef DISPLAY_HELP_H
#define DISPLAY_HELP_H

#include <stdbool.h>

extern bool show_help; // Globális kapcsoló

void toggleHelp();     // H gombhoz
void displayHelpText(); // Konzolos debug módhoz

#endif
