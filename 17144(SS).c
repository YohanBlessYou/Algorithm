#include<stdio.h>
#include<stdbool.h>
int dust[51][51];
int tmp_dust[51 * 51][51][51];

int R;
int C;
int T;
int cleaner;

bool is_cleaner(int x, int y) {

	if (x == 1 && y == cleaner) return true;
	if (x == 1 && y == cleaner-1) return true;

	return false;
}

void print_status() {
	int i, j;
	printf("\n");
	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			printf("%2d ", dust[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_tmp_status(int n) {
	int i, j;
	printf("\n");
	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			printf("%2d ", tmp_dust[n][j][i]);
		}
		printf("\n");
	}
	printf("\n");
}


bool is_in_area(int x, int y) {
	if (x<1 || x>C) return false;
	if (y<1 || y>R) return false;
	if (is_cleaner(x, y) == true)return false;
	return true;
}

void spread_dust() {

	int i, j,k;

	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			if (dust[j][i] == 0)continue;
			if (is_cleaner(j, i) == true) {
				tmp_dust[i * R + j][j][i] = -1;
			}
			else {
				int sum = dust[j][i];
				int share = 0;
				//up
				if (is_in_area(j, i - 1) == true) {
					share++;
					tmp_dust[i * R + j][j][i - 1] = dust[j][i] / 5;
				}
				//down
				if (is_in_area(j, i + 1) == true) {
					share++;
					tmp_dust[i * R + j][j][i + 1] = dust[j][i] / 5;
				}
				//right
				if (is_in_area(j+1, i) == true) {
					share++;
					tmp_dust[i * R + j][j+1][i] = dust[j][i] / 5;
				}
				//left
				if (is_in_area(j - 1, i) == true) {
					share++;
					tmp_dust[i * R + j][j - 1][i] = dust[j][i] / 5;
				}
				sum = sum - share * (dust[j][i] / 5);
				tmp_dust[i * R + j][j][i] = sum;
				//printf("[direction:%d / remain:%d]\n", share, sum);
				//print_tmp_status(i * R + j);
			}

		}
	}


	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			int sum = 0;
			for (k = 1 * R + 1; k < 51 * 51; k++) {
				sum += tmp_dust[k][j][i];
			}
			dust[j][i] = sum;
		}
	}


}

void clean_tmp_dust() {
	int i, j, k;

	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			for (k = 1 * R + 1; k < 51 * 51; k++) {
				tmp_dust[k][j][i]=0;
			}
		}
	}
}


void move_dust(int from_x, int from_y, int to_x, int to_y) {

	//to cleaner
	if (to_x == 1) {
		if (to_y == cleaner || to_y == cleaner - 1) {
			dust[from_x][from_y] = 0;
			return;
		}
	}

	dust[to_x][to_y] = dust[from_x][from_y];
	dust[from_x][from_y] = 0;
}


void run_cleaner() {

	int i, j, k;

	//case 4 - upside
	for (i = cleaner-2; i >= 1; i--) {
		move_dust(1, i, 1, i + 1); //move down
	}
	//case 4 - downside
	for (i = cleaner+1; i <= R; i++) {
		move_dust(1, i, 1, i - 1); //move up
	}

	//case 3 - upside
	for (j = 2; j <= C; j++) {
		move_dust(j, 1, j-1,1); //move left
	}
	//case 3 - downside
	for (j = 2; j <= C; j++) {
		move_dust(j, R, j - 1, R); //move left
	}

	//case 2 - upside
	for (i = 2; i <= cleaner-1; i++) {
		move_dust(C, i, C, i - 1); //move up
	}
	//case 2 - downside
	for (i = R-1; i >= cleaner; i--) {
		move_dust(C, i, C, i + 1); //move down
	}

	//case 1 - upside
	for (i = C-1; i >= 2; i--) {
		move_dust(i,cleaner-1,i+1,cleaner-1); //move right
	}
	//case 1 - downside
	for (i = C - 1; i >= 2; i--) {
		move_dust(i, cleaner, i + 1, cleaner); //move right
	}
}


int main() {

	int i, j,tmp;

	scanf("%d", &R);
	scanf("%d", &C);
	scanf("%d", &T);

	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			scanf("%d", &tmp);
			if (tmp == -1) cleaner = i;
			dust[j][i] = tmp;
		}
	}

	for (i = 0; i < T; i++) {
		clean_tmp_dust();
		spread_dust();
		//print_status();
		run_cleaner();
		//print_status();
	}


	int ret = 0;
	for (i = 1; i <= R; i++) {
		for (j = 1; j <= C; j++) {
			if (dust[j][i] != -1) ret += dust[j][i];
		}
	}
	printf("%d", ret);

	return 0;

}