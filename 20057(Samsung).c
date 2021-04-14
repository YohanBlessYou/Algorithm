#include <stdio.h>
#include<stdbool.h>
int A[500][500];
int x;
int y;
int N;
int direction;
int out_sand;


void move_coord(int step) {
	switch (direction) {
	case 0: x = x - step; //left
		break;
	case 1: y = y + step; //bottom
		break;
	case 2: x = x + step; //right
		break;
	case 3: y = y - step; //top
		break;
	}
}


void calc_sand(int xx, int yy, int sand) {
	if (x+xx < 0 || y+yy < 0) {
		out_sand += sand;
		A[y][x] -= sand;
		return;
	}
	else if (x+xx >= N || y+yy >= N) {
		out_sand += sand;
		A[y][x] -= sand;
		return;
	}

	A[y+yy][x+xx] += sand;
	A[y][x] -= sand;
}

void spread_sand(int sand) {
	
	int sand1 = sand * 0.01;
	int sand2 = sand * 0.02;
	int sand5 = sand * 0.05;
	int sand7 = sand * 0.07;
	int sand10 = sand * 0.1;
	int sanda = sand- sand5 - 2*(sand1 + sand2 + sand7 + sand10);

	if (direction == 0) {
		calc_sand(0, -2, sand2);
		calc_sand(-1, -1, sand10);
		calc_sand(0, -1, sand7);
		calc_sand(1, -1, sand1);

		calc_sand(-2, 0, sand5);
		calc_sand(-1, 0, sanda);

		calc_sand(-1, 1, sand10);
		calc_sand(0, 1, sand7);
		calc_sand(1, 1, sand1);
		calc_sand(0, 2, sand2);
	}
	else if (direction == 1) {
		calc_sand(-2, 0, sand2);
		calc_sand(-1, 1, sand10);
		calc_sand(-1, 0, sand7);
		calc_sand(-1, -1, sand1);

		calc_sand(0, 2, sand5);
		calc_sand(0, 1, sanda);

		calc_sand(1, 1, sand10);
		calc_sand(1, 0, sand7);
		calc_sand(1, -1, sand1);
		calc_sand(2, 0, sand2);
	}
	else if (direction == 2) {
		calc_sand(0, -2, sand2);
		calc_sand(1, -1, sand10);
		calc_sand(0, -1, sand7);
		calc_sand(-1, -1, sand1);

		calc_sand(2, 0, sand5);
		calc_sand(1, 0, sanda);

		calc_sand(1, 1, sand10);
		calc_sand(0, 1, sand7);
		calc_sand(-1, 1, sand1);
		calc_sand(0, 2, sand2);
	}
	else if (direction == 3) {
		calc_sand(-2, 0, sand2);
		calc_sand(-1, -1, sand10);
		calc_sand(-1, 0, sand7);
		calc_sand(-1, 1, sand1);

		calc_sand(0, -2, sand5);
		calc_sand(0, -1, sanda);

		calc_sand(1, -1, sand10);
		calc_sand(1, 0, sand7);
		calc_sand(1, 1, sand1);
		calc_sand(2, 0, sand2);
	}
}

void print_sand() {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%2d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {

	scanf("%d", &N);
	int i,j;
	int tmp_sand;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			scanf("%d", &tmp_sand);
			A[i][j] = tmp_sand;
		}
	}

	//init
	int ret = 0;
	x = (N / 2); //center
	y = (N / 2); //center

	direction = -1; 
	out_sand = 0; 

	for (i = 1; i < N; i++) {
		direction = (direction + 1) % 4;
		for (j = 0; j < i; j++) {
			move_coord(1);
			spread_sand(A[y][x]);
			//print_sand();
		}

		direction = (direction + 1) % 4;
		for (j = 0; j < i; j++) {
			move_coord(1);
			spread_sand(A[y][x]);
			//print_sand();
		}
	}
	
	direction = (direction + 1) % 4;
	for (j = 0; j < N-1; j++) {
		move_coord(1);
		spread_sand(A[y][x]);
		//print_sand();
	}
	printf("%d", out_sand);

	return 0;
}