#include <stdio.h>
#include<stdbool.h>

typedef struct blk {
	int number;
	int A;
	bool is_robot;
}blk;

int N;
int K;
int first_convey;

int get_next_blk(int i, int step) {

	if (i + step > 2 * N) {
		return (i + step) % (2 * N);
	}
	else {
		return i + step;
	}
}

void move_convey(blk* blk) {

	if (first_convey == 1) first_convey = 2 * N;
	else first_convey = first_convey - 1;

	//remove last_blk's robot
	blk[get_next_blk(first_convey, N - 1)].is_robot = false;

}



bool moving_robot(blk* blk, int i) {
	//@last blk
	if (i == get_next_blk(first_convey,N-1)) return false;
	//robot at next blk
	if (blk[get_next_blk(i,1)].is_robot == true) return false;
	//no A at next blk
	if (blk[get_next_blk(i, 1)].A == 0) return false;

	blk[get_next_blk(i, 1)].A--;
	blk[get_next_blk(i, 1)].is_robot = true;
	blk[i].is_robot = false;

	blk[get_next_blk(first_convey, N - 1)].is_robot = false;
	return true;
}


void move_robot(blk* blk) {
	int i;
	int index = get_next_blk(first_convey, N - 1);
	for (i = N; i >= 1; i--) {
		if (blk[index].is_robot == true) {
			moving_robot(blk, index);
		}

		if (index - 1 == 0) index = 2 * N;
		else index--;
	}
}

void print_status(blk* blk) {
	int i;
	printf("\n");
	int index = first_convey;
	for (i = 0; i < N ; i++) {
		printf("[%d]%d(%d) ",index, blk[index].is_robot,blk[index].A);
		if (index + 1 > 2 * N) index = 1;
		else index++;
	}
	printf("\n");
}

void put_on_robot(blk* blk) {
	if (blk[first_convey].A == 0)return;
	blk[first_convey].A--;
	blk[first_convey].is_robot = true;


}

bool check_K(blk* blk) {
	int i;
	int zero_blk_num = 0;
	for (i = 1; i <= 2 * N; i++) {
		if (blk[i].A == 0) zero_blk_num++;
	}
	if (zero_blk_num >= K)return false;
	else return true;
}

int main() {

	blk blk[201];

	scanf("%d", &N);
	scanf("%d", &K);
	int i;

	//init blk / convey
	int tmp_A;
	for (i = 1; i <= 2 * N; i++) {
		blk[i].number = i;
		scanf("%d", &tmp_A);
		blk[i].A = tmp_A;
		blk[i].is_robot = false;
		
	}
	first_convey = 1;
	//print_status(blk);
	int step = 0;

	do {
		step++;

		//move 1step right conveyer
		move_convey(blk);
		
		//move robot 
		move_robot(blk);

		//put up robot
		put_on_robot(blk);

		//print_status(blk);
	} while (check_K(blk));

	printf("%d", step);

	return 0;

}