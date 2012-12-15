#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif // !STDIO_H

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izmçri
#define FIELD_HEIGHT 90

typedef struct {
	int width;
	int height;
} Field;

typedef struct {
	int x;
	int y;
	float angle;	//vai varbût 2d vektoru kas pasaka kurâ virzienâ skatâs? vai vispâr citâdâk noteikt lokâciju un rotâciju?
} Lightcycle;

void gameTick();