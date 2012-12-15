#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif // !STDIO_H

#define FIELD_WIDTH 160		//lauka pa kuru brauc motocikli izm�ri
#define FIELD_HEIGHT 90

typedef struct {
	int width;
	int height;
} Field;

typedef struct {
	int x;
	int y;
	float angle;	//vai varb�t 2d vektoru kas pasaka kur� virzien� skat�s? vai visp�r cit�d�k noteikt lok�ciju un rot�ciju?
} Lightcycle;

void gameTick();