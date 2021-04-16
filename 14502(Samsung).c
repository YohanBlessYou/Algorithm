#include<stdio.h>


int N, M;

int status[9][9];
int tmp_status[9][9];


int maxx(int a, int b) {
	if (a > b)return a;
	else return b;
}

void print_current_status(int a) {
	int i, j;
	printf("\n");
	for (i = 1; i <= N; i++) {
		printf("\n");
		for (j = 1; j <= M; j++) {
			if (a == 1) printf("%2d ", status[j][i]);
			if (a == 2) printf("%2d ", tmp_status[j][i]);
		}
	}
	printf("\n");
}

void spread_virus(int x,int y) {
	int i, j;
	if (tmp_status[x][y] != 2) return; //not virus

	if (y != 1) {  //up side
		if (tmp_status[x][y - 1] == 0) {
			tmp_status[x][y - 1] = 2;
			spread_virus(x, y - 1);
		}
	}
	if (y != N) {  //down side
		if (tmp_status[x][y +1] == 0) {
			tmp_status[x][y + 1] = 2;
			spread_virus(x, y + 1);
		}
	}
	if (x != 1) {  //left side
		if (tmp_status[x-1][y] == 0) {
			tmp_status[x-1][y] = 2;
			spread_virus(x-1, y);
		}
	}
	if (x != M) {  //right side
		if (tmp_status[x + 1][y] == 0) {
			tmp_status[x + 1][y] = 2;
			spread_virus(x + 1, y);
		}
	}
}

int calc_safe_area() {
	int i, j;

	//copy status
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			tmp_status[j][i] = status[j][i];
		}
	}

	//spread_virus
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			spread_virus(j, i);
		}
	}
	//print_current_status(2);

	//calc_safe_area
	int ret = 0;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			if (tmp_status[j][i] == 0)ret++;
		}
	}
	//printf("==============================\n");
	//printf("[Safe Area : %d]\n", ret);
	return ret;
}


int pick_blocker(int depth) {
	if (depth == 3) {
		//calc safe area
		//printf("==============================\n");
		//print_current_status(1);
		return calc_safe_area();
	}


	int i, j;
	int max_value = 0;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			if (status[j][i] == 0) {
				status[j][i] = 1;
				max_value = maxx(max_value, pick_blocker(depth + 1));
				status[j][i] = 0;
			}
		}
	}

	return max_value;
}


int main() {


	//init
	scanf("%d", &N);
	scanf("%d", &M);
	int i, j,tmp;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			scanf("%d", &tmp);
			status[j][i] = tmp;
		}
	}

	int ret = 0;

	ret = pick_blocker(0);

	printf("%d", ret);

	return 0;
}