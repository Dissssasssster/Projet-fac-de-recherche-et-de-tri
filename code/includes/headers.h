/*
constante de préprocesseur qui permet de ne pas inclure de 
manière infinie, d'inclure les fichiers dans le bon ordre.
*/
#ifndef __HEADERS__H__
#define __HEADERS__H__

// inclusion des bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Constante permettant d'avoir le nombre de ligne à traiter.
static const unsigned int LINE_TO_READ_COUNT = 30;

#endif