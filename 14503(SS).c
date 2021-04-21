#include<stdio.h>
#include<stdbool.h>

int N, M;

int wall[50][50];

int clean_flag[50][50];

typedef struct robot {
	int x;
	int y;
	int d;
}robot;

robot rb;

void print_status() {
	int i, j;

	printf("\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			printf("%2d ", clean_flag[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}


bool find_next_direction(int plus_d) {

	if (plus_d < 0) plus_d = plus_d + 4;

	int tmp_x = rb.x;
	int tmp_y = rb.y;

	switch (plus_d) {
	case 0: tmp_y--;
		break;
	case 1: tmp_x++;
		break;
	case 2: tmp_y++;
		break;
	case 3: tmp_x--;
		break;
	}

	//if out
	if (tmp_x < 0 || tmp_x >= M)return false;
	if (tmp_y < 0 || tmp_y >= N)return false;

	//if cleaned
	if (clean_flag[tmp_x][tmp_y] >= 1)return false;

	rb.x = tmp_x;
	rb.y = tmp_y;
	rb.d = plus_d;
	clean_flag[rb.x][rb.y] = 1;

	//printf("[clean](%d,%d)\n", rb.x, rb.y);
	//print_status();
	return true;
}

bool move_back() {

	switch (rb.d) {
	case 0: rb.y++;
		break;
	case 1: rb.x--;
		break;
	case 2: rb.y--;
		break;
	case 3: rb.x++;
		break;
	}

	//if out
	if (rb.x < 0 || rb.x >= M)return false;
	if (rb.y < 0 || rb.y >= N)return false;

	//if wall
	if (clean_flag[rb.x][rb.y] == 2)return false;

	//printf("[move back](%d,%d)\n", rb.x, rb.y);
	//print_status();
	return true;
}

int main() {

	scanf("%d", &N);
	scanf("%d", &M);

	int tmp;

	scanf("%d", &tmp);
	rb.y = tmp;
	scanf("%d", &tmp);
	rb.x = tmp;
	scanf("%d", &tmp);
	rb.d = tmp;

	int i, j;
	int num_blank = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			scanf("%d", &tmp);
			wall[j][i] = tmp;
			if (tmp == 1)clean_flag[j][i] = 2;
			else num_blank++;
		}
	}
	//printf("[blank]:%d\n", num_blank);
	clean_flag[rb.x][rb.y] = 1;
	int ret = 1;

	do {

		int got_next = 0;
		//find next direction
		for (i = 1; i <= 4; i++) {
			if (find_next_direction(rb.d - i) == true) {
				got_next = 1;
				ret++;

				break;
			}
		}
		if (got_next == 1)continue;

		//move back & check if stop


		if (move_back() == false) break;

	} while (true);

	printf("%d", ret);


	return 0;
}