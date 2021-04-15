#include<stdio.h>
#include<stdbool.h>

int step[4][4][2];
int map[17][2];

typedef struct shark {
	int x;
	int y;
	int value;
	int direction;
}sharks;


int calc_next_x(int x, int y, int n,int plus_direction) {
	int plus_x;
	int plus_y;

	switch ((step[x][y][1] + plus_direction) % 8) {
	case 0: plus_x = 0; plus_y = -1;
		break;
	case 1: plus_x = -1; plus_y = -1;
		break;
	case 2: plus_x = -1; plus_y = 0;
		break;
	case 3: plus_x = -1; plus_y = 1;
		break;
	case 4: plus_x = 0; plus_y = 1;
		break;
	case 5: plus_x = 1; plus_y = 1;
		break;
	case 6: plus_x = 1; plus_y = 0;
		break;
	case 7: plus_x = 1; plus_y = -1;
		break;
	}
	return x + n * plus_x;
}

int calc_next_y(int x, int y, int n,int plus_direction) {
	int plus_x;
	int plus_y;

	switch ((step[x][y][1] + plus_direction) % 8) {
	case 0: plus_x = 0; plus_y = -1;
		break;
	case 1: plus_x = -1; plus_y = -1;
		break;
	case 2: plus_x = -1; plus_y = 0;
		break;
	case 3: plus_x = -1; plus_y = 1;
		break;
	case 4: plus_x = 0; plus_y = 1;
		break;
	case 5: plus_x = 1; plus_y = 1;
		break;
	case 6: plus_x = 1; plus_y = 0;
		break;
	case 7: plus_x = 1; plus_y = -1;
		break;
	}
	return y + n * plus_y;
}

bool is_possible(int x, int y, int plus_direction, sharks shark) {
	
	int next_x = calc_next_x(x, y, 1, plus_direction);
	int next_y = calc_next_y(x,y,1, plus_direction);

	//check if out
	if (next_x < 0 || next_y < 0) return false;
	if (next_x >= 4 || next_y >= 4) return false;

	//check if shark
	if (next_x == shark.x && next_y == shark.y) return false;

	return true;
}

void swap(int victim_x, int victim_y, int aggr_x, int aggr_y) {

	int tmp_value, tmp_direction;
	int victim_n = step[victim_x][victim_y][0];
	int aggr_n = step[aggr_x][aggr_y][0];

	//backup victim
	tmp_value = step[victim_x][victim_y][0];
	tmp_direction = step[victim_x][victim_y][1];
	//copy aggressor to victim
	step[victim_x][victim_y][0] = step[aggr_x][aggr_y][0];
	step[victim_x][victim_y][1] = step[aggr_x][aggr_y][1];
	//copy victim to aggressor
	step[aggr_x][aggr_y][0] = tmp_value;
	step[aggr_x][aggr_y][1] = tmp_direction;

	int tmp_x, tmp_y;
	//backup victim
	tmp_x = map[victim_n][0];
	tmp_y = map[victim_n][1];
	//copy aggressor to victim
	map[victim_n][0] = map[aggr_n][0];
	map[victim_n][1] = map[aggr_n][1];
	//copy victim to aggressor
	map[aggr_n][0] = tmp_x;
	map[aggr_n][1] = tmp_y;
}


void print_status() {
	int i, j;
	printf("\n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%2d ", step[j][i][0]);
		}
		printf("\n");
	}
	printf("\n");
}

void move_fish(int n, sharks shark) {
	int i, j;
	int tmp_x, tmp_y;
	int tmp_value, tmp_direction;
	for (i = 0; i < 8; i++) {
		if (is_possible(map[n][0],map[n][1],i,shark)) {
			tmp_x = calc_next_x(map[n][0],map[n][1],1,i);
			tmp_y = calc_next_y(map[n][0], map[n][1],1, i);
			
			swap(map[n][0], map[n][1], tmp_x, tmp_y);

			return;
		}
	}
}

int maxx(int a, int b) {
	if (a > b)return a;
	else return b;
}


int move_shark(sharks* shark, int n) {
	int to_x=shark->x;
	int to_y=shark->y;
	int i;
	int tmp_x, tmp_y;

	tmp_x = calc_next_x(to_x, to_y, n,0);
	tmp_y = calc_next_y(to_x, to_y, n,0);
	to_x = tmp_x;
	to_y = tmp_y;
	
	printf("[shark(%d,%d)->(%d,%d)\n", shark->x, shark->y, to_x, to_y);
	swap(to_x, to_y, shark->x, shark->y);
	
	int ret = step[shark->x][shark->y][0];
	
	step[shark->x][shark->y][0] = 99;

	shark->x = to_x;
	shark->y = to_y;

	//ignore eaten block
	if (ret >= 99) return 0;

	return ret;
}

int main() {

	int i, j;
	int tmp_value;
	int tmp_direction;

	sharks shark;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			scanf("%d", &tmp_value);
			scanf("%d", &tmp_direction);
			step[j][i][0] = tmp_value-1;
			step[j][i][1] = tmp_direction-1;
			if (i == 0 && j == 0) {
				shark.value = tmp_value - 1;
				shark.direction = tmp_direction - 1;
			}
			map[tmp_value-1][0] = j;
			map[tmp_value-1][1] = i;
			
		}
	}

	shark.x = 0;
	shark.y = 0;

	print_status();
	for (i = 0; i < 16; i++) {
		if (i == shark.value)continue;
		move_fish(i,shark);
		print_status();
	}

	int backup_step[4][4][2];
	int backup_map[17][2];
	sharks backup_shark;
	//backup origin map
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			backup_step[j][i][0] = step[j][i][0];
			backup_step[j][i][1] = step[j][i][1];
		}
	}
	for (i = 0; i < 17; i++) {
		backup_map[i][0] = map[i][0];
		backup_map[i][1] = map[i][1];
	}
	backup_shark = shark;






	int ret = 0;
	int tmp_ret = shark.value+1;
	if (shark.direction >= 4 && shark.direction <= 6) {
		
		//1-1-1
		tmp_ret = shark.value + 1;
		tmp_ret += move_shark(&shark,1) + 1;
		for (i = 0; i < 16; i++) {
			if (i == shark.value)continue;
			//ignore eaten block
			if (step[map[i][0]][map[i][1]][0] >= 99)continue;
			move_fish(i, shark);
			print_status();
		}
		tmp_ret += move_shark(&shark, 1) + 1;
		for (i = 0; i < 16; i++) {
			if (i == shark.value)continue;
			//ignore eaten block
			if (step[map[i][0]][map[i][1]][0] >= 99)continue;
			move_fish(i, shark);
			print_status();
		}
		tmp_ret += move_shark(&shark, 1) + 1;
		printf("[1-1-1]==>%d\n", tmp_ret);
		ret = maxx(ret, tmp_ret);
		

		//backup
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				step[j][i][0] = backup_step[j][i][0];
				step[j][i][1] = backup_step[j][i][1];
			}
		}
		for (i = 0; i < 17; i++) {
			map[i][0] = backup_map[i][0];
			map[i][1] = backup_map[i][1];
		}
		shark = backup_shark;
		print_status();

		//2-1
		tmp_ret = shark.value + 1;
		tmp_ret += move_shark(&shark, 2) + 1;
		for (i = 0; i < 16; i++) {
			if (i == shark.value)continue;
			//ignore eaten block
			if (step[map[i][0]][map[i][1]][0] >= 99)continue;
			move_fish(i, shark);
			print_status();
		}
		tmp_ret += move_shark(&shark, 1) + 1;
		printf("[2-1]==>%d\n", tmp_ret);
		ret = maxx(ret, tmp_ret);
		

		//backup
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				step[j][i][0] = backup_step[j][i][0];
				step[j][i][1] = backup_step[j][i][1];
			}
		}
		for (i = 0; i < 17; i++) {
			map[i][0] = backup_map[i][0];
			map[i][1] = backup_map[i][1];
		}
		shark = backup_shark;
		print_status();

		//1-2
		tmp_ret = shark.value + 1;
		tmp_ret += move_shark(&shark, 1) + 1;
		for (i = 0; i < 16; i++) {
			if (i == shark.value)continue;
			//ignore eaten block
			if (step[map[i][0]][map[i][1]][0] >= 99)continue;
			move_fish(i, shark);
			print_status();
		}
		tmp_ret += move_shark(&shark, 2) + 1;
		printf("[1-2]==>%d\n", tmp_ret);
		ret = maxx(ret, tmp_ret);
		

		//backup
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				step[j][i][0] = backup_step[j][i][0];
				step[j][i][1] = backup_step[j][i][1];
			}
		}
		for (i = 0; i < 17; i++) {
			map[i][0] = backup_map[i][0];
			map[i][1] = backup_map[i][1];
		}
		shark = backup_shark;
		print_status();

		//3
		tmp_ret = shark.value + 1;
		tmp_ret += move_shark(&shark, 3) + 1;
		printf("[3]==>%d\n", tmp_ret);
		ret = maxx(ret, tmp_ret);
		
		printf("%d", ret);
	}
	else {
		printf("0", ret);
	}

	return 0;

}