#include<stdio.h>
#include<stdbool.h>

int N;
int population[21][21];

int area_map[21][21];


int minn(int a, int b) {
	if (a < b)return a;
	else return b;
}

int maxx(int a, int b) {
	if (a > b)return a;
	else return b;
}

void print_status() {
	int i, j;
	printf("\n");
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			printf("%2d ", area_map[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

bool is_available(int x, int y, int d1, int d2) {

	if (x + d2 > N) return false;
	if (x - d1 < 1)return false;
	if (y + d1 + d2 > N) return false;

	return true;

}

bool is_area1(int x, int y, int d1, int d2, int j, int i) {

	if (j > x) return false;
	if (i >= y+d1) return false;

	if (i < (-1 * j) + (x + y)) {
		return true;
	}
	else return false;
}

bool is_area2(int x, int y, int d1, int d2, int j, int i) {

	if (j <= x) return false;
	if (i > y+d2) return false;

	if (i < (j) + (y-x)) {
		return true;
	}
	else return false;
}

bool is_area3(int x, int y, int d1, int d2, int j, int i) {

	if (j >= x-d1+d2) return false;
	if (i < y+d1) return false;

	if (i > (j) + (y+d1)-(x-d1)) {
		return true;
	}
	else return false;
}

bool is_area4(int x, int y, int d1, int d2, int j, int i) {

	if (j < x-d1+d2) return false;
	if (i <= y+d2) return false;

	if (i > (-1 * j) + (y+x+2*d2)) {
		return true;
	}
	else return false;
}

int which_area(int x, int y, int d1, int d2, int j, int i) {

	if (is_area1(x,y,d1,d2,j,i)==true)return 1;
	if (is_area2(x, y, d1, d2, j, i) == true)return 2;
	if (is_area3(x, y, d1, d2, j, i) == true)return 3;
	if (is_area4(x, y, d1, d2, j, i) == true)return 4;

	return 5;
}


int calc_min_gap(int x, int y, int d1, int d2) {

	int max_v=0;
	int min_v=100*20*20;

	int pop[6] = { 0, };

	int i, j;

	//generate area map
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			area_map[j][i] = which_area(x, y, d1, d2, j, i);
		}
	}

	//print_status();

	//calc each area population
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			pop[area_map[j][i]] += population[j][i];
		}
	}

	

	//calc max <-> min
	for (i = 1; i <= 5; i++) {
		max_v = maxx(max_v, pop[i]);
		min_v = minn(min_v, pop[i]);
	}

	return max_v - min_v;
}


void clean_map() {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			area_map[j][i] = 0;
		}
	}
}

int main() {

	scanf("%d", &N);

	int i, j;
	int tmp;

	for (i = 1; i <=N; i++) {
		for (j = 1; j <= N; j++) {
			scanf("%d", &tmp);
			population[j][i] = tmp;
		}
	}


	int x, y, d1, d2;

	int ret = 100 * 20 * 20;

	for (y = 1; y <= N; y++) {
		for (x = 1; x <= N; x++) {
			for (d2 = 1; d2 <= N; d2++) {
				for (d1 = 1; d1 <= N; d1++) {
					clean_map();
					if (is_available(x, y, d1, d2) == false)continue;
					tmp = calc_min_gap(x, y, d1, d2);
					ret = minn(ret, tmp);
				}
			}
			
		}
	}

	printf("%d", ret);

	return 0;

}