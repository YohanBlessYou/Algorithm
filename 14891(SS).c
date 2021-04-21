#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
int chain[5][8];
int N;

typedef struct rotate {
	int chain_num;
	int is_clockwise;
}rotate;

rotate rt[100];


bool is_rotatable(int left, int right) {
	if (chain[left][2] != chain[right][6]) return true;
	else return false;
}


void rotation(int chain_num, int is_clockwise) {

	int tmp;
	int i, j;
	if (is_clockwise == 1) {
		tmp = chain[chain_num][7];
		for (i = 6; i >= 0; i--) {
			chain[chain_num][i + 1] = chain[chain_num][i];
		}
		chain[chain_num][0] = tmp;
	}
	else {
		tmp = chain[chain_num][0];
		for (i = 1; i <= 7; i++) {
			chain[chain_num][i - 1] = chain[chain_num][i];
		}
		chain[chain_num][7] = tmp;
	}

}

void rotate_chain(int chain_num, int is_clockwise) {

	int i, j;
	
	int left_side = 0;
	int right_side = 0;

	//check left side
	for (i = 1; chain_num - i >= 1; i++) {
		if (is_rotatable(chain_num - i, chain_num - i + 1) == true) {
			left_side++;
		}
		else break;
	}
	//check right side
	for (i = 1; chain_num + i <= 4; i++) {
		if (is_rotatable(chain_num + i-1, chain_num + i) == true) {
			right_side++;
		}
		else break;
	}


	//rotate left side
	for (i = chain_num - left_side; i < chain_num; i++) {
		if ((chain_num + i) % 2 == 0) rotation(i, is_clockwise);
		else rotation(i, (-1) * is_clockwise);
	}
	//rotate right side
	for (i = chain_num + right_side; i > chain_num; i--) {
		if ((chain_num + i) % 2 == 0) rotation(i, is_clockwise);
		else rotation(i, (-1) * is_clockwise);
	}
	//rotate self
	rotation(chain_num, is_clockwise);

}


int calc_score() {

	int i;
	int ret = 0;
	
	if (chain[1][0] == 1) ret += 1;
	if (chain[2][0] == 1) ret += 2;
	if (chain[3][0] == 1) ret += 4;
	if (chain[4][0] == 1) ret += 8;
	
	return ret;
}

int main() {

	int i, j;
	char* tmp = (char*)malloc(8*sizeof(char));

	scanf("%s", tmp);

	for (i = 0; i < 8; i++) {
		if (tmp[i]=='1') chain[1][i] = 1;
		else chain[1][i] = 0;
	}
	
	scanf("%s", tmp);

	for (i = 0; i < 8; i++) {
		if (tmp[i] == '1') chain[2][i] = 1;
		else chain[2][i] = 0;
	}
	scanf("%s", tmp);

	for (i = 0; i < 8; i++) {
		if (tmp[i] == '1') chain[3][i] = 1;
		else chain[3][i] = 0;
	}
	scanf("%s", tmp);

	for (i = 0; i < 8; i++) {
		if (tmp[i] == '1') chain[4][i] = 1;
		else chain[4][i] = 0;
	}


	int jang;

	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d", &jang);
		rt[i].chain_num = jang;
		scanf("%d", &jang);
		rt[i].is_clockwise = jang;
	}


	for (i = 0; i < N; i++) {
		rotate_chain(rt[i].chain_num, rt[i].is_clockwise);
	}

	int ret;
	ret=calc_score();
	printf("%d", ret);

	
	return 0;

}