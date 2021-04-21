#include<stdio.h>
#include<stdbool.h>
int N;

int curve_direction[21][1025];  // 20:curve count - 1024:direction cnt

int flag[100][100];

typedef struct start_point {
	int x;
	int y;
	int d;
	int g;
}start_point;

start_point sp[20];

int power(int a, int n) {
	int i;
	int ret = 1;
	for (i = 0; i < n; i++) {
		ret = ret * a;
	}
	return ret;
}

int next_direction(int a) {
	if (a == 3) return 0;
	else return a + 1;
}

void make_dragon(int n) {

	curve_direction[n][1] = sp[n].d;

	int i,j;
	int prev_index;
	int to_make_num;

	for (i = 1; i <= sp[n].g; i++) {
		prev_index = power(2, i - 1);
		to_make_num = prev_index;
		for (j = 1; j <= to_make_num; j++) {
			curve_direction[n][prev_index + j] = next_direction(curve_direction[n][prev_index - j + 1]);
		}
	}
}

bool is_avaliable_path(int x, int y) {

	if (x < 0 || x>100) return false;
	if (y < 0 || y>100)return false;
	return true;
}


void flagging(int n) {
	int i, j;

	int x = sp[n].x;
	int y = sp[n].y;
	int d = sp[n].d;

	for (i = 1; i <= power(2, sp[n].g)+1; i++) {
		if (is_avaliable_path(x, y) == true) flag[x][y] = 1;
		d = curve_direction[n][i];
		switch (d) {
		case 0: x++;
			break;
		case 1: y--;
			break;
		case 2: x--;
			break;
		case 3: y++;
			break;
		}
	}

}

void print_path() {

	int i, j;
	printf("\n");
	for (i = 0; i < N; i++) {
		printf("[%d]\n",i);
		for (j = 1; j <= power(2, sp[i].g); j++) {
			printf("%2d ", curve_direction[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}


int calc_square() {

	int i, j;
	int ret = 0;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 100; j++) {
			if (flag[j][i] == 0)continue;
			if (flag[j+1][i] == 0)continue;
			if (flag[j][i+1] == 0)continue;
			if (flag[j+1][i+1] == 0)continue;
			ret++;
		}
	}
	return ret;
}

int main() {
	
	scanf("%d", &N);
	int i, j;
	int tmp;
	for (i = 0; i < N; i++) {
		scanf("%d", &tmp);
		sp[i].x = tmp;
		scanf("%d", &tmp);
		sp[i].y = tmp;
		scanf("%d", &tmp);
		sp[i].d = tmp;
		scanf("%d", &tmp);
		sp[i].g = tmp;
	}

	for (i = 0; i < N; i++) {
		make_dragon(i);
	}
	//print_path();
	for (i = 0; i < N; i++) {
		flagging(i);
	}

	int ret;
	ret=calc_square();
	printf("%d", ret);

	return 0;
}