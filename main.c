/* El juego de la vida
 * main.c
 *
 *  Created on: 10 nov. 2019
 *      Author: Edgar Vallejo Curti
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define for_x for(x = 0; x < XMAX; x++)
#define for_y for(y = 0; y < YMAX; y++)
#define for_yx for_y for_x
#define XMAX 20
#define YMAX 20

void life(short spaceOriginal[][XMAX], int time);
void printMatrix(short canvas[][XMAX]);
void igualarMatrix(short old[][XMAX], short new[][XMAX]);
short contarVecinos(short Matrix[][XMAX],short x, short y);

int main(){
	short space[YMAX][XMAX];
	int x,y;

	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	srand(time(0));

	//Generar espacio
	for_yx space[y][x] = rand() % 2; //Con este arreglo, tendremos numeros random, del 0 al 1

	//Juguemos al guejo
	life(space, 100);

	return 0;
}

void life(short spaceOriginal[][XMAX], int times){
	short spaceNew[YMAX][XMAX]; //Resultado de la matriz anterior
	int x, y;
	short neighbourhood;
	//n es la cantidad de repeticiones
	//X y Y para recorrer matrices


	for(int n = 1; n <= times; n++){
		printMatrix(spaceOriginal);

		//Recorrer la matriz, una celula por una
		for_yx{
			neighbourhood = contarVecinos(spaceOriginal, x, y);

			//Comparar
			if(neighbourhood == 3)	spaceNew[y][x] = 1;	//si tiene 3 vecinos, nace
			else if(neighbourhood == 2 && spaceOriginal[y][x]) spaceNew[y][x] = 1; //si tiene dos vecinos y existe, vive
			else spaceNew[y][x] = 0; //Para todo lo demas, muere
		}

		igualarMatrix(spaceOriginal, spaceNew);

		Sleep(1000);
		system("cls");
	}
}

void printMatrix(short canvas[][XMAX]){
	int x, y;
	for_y{
		for_x	printf("%d ", canvas[y][x]);
		printf("\n");
	}
	printf("\n");
}

void igualarMatrix(short new[][XMAX], short old[][XMAX]){
	//Los valores de la segunda matriz se copia a la de la primera
	int x,y;
	for_yx	new[y][x] = old[y][x];
}

short contarVecinos(short matrix[][XMAX],short x, short y){
	//x y y coordenadas del momento, matrix el espacio como tal
	int j, i;
	short inicioX = x - 1, inicioY = y - 1, finalX = x + 1, finalY = y + 1; //Los limites de chequeo
	short neighbourhood = 0;
	if(x == 0)	inicioX = 0;
	if(y == 0)	inicioY = 0;
	if(x == XMAX - 1)	finalX = XMAX - 1;
	if(y == YMAX - 1)	finalY = YMAX - 1;

	//Contar los vecinos
	for(j = inicioY; j <= finalY; j++)
		for(i = inicioX; i <= finalX; i++)
			if(matrix[j][i]&& !(x == i && y == j))	neighbourhood++;
	return neighbourhood;
}

