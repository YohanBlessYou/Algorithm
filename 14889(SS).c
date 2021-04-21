#include<stdio.h>

int N;
int start[20];
int link[20];
int flag[20];
int synergy[20][20];
int start_score;
int link_score;

int minn(int a, int b) {
	if (a == -1)return b;
	if (a < b)return a;
	else return b;
}

int calc_gap() {

	int i, j;

	int link_offset = 0;
	for (i = 0; i < N; i++) {
		if (flag[i] == 0)link[link_offset++] = i;
	}

	start_score = 0;
	link_score = 0;

	for (i = 0; i < N / 2; i++) {
		for (j = 0; j < N / 2; j++) {
			start_score += synergy[start[i]][start[j]];
		}
	}

	for (i = 0; i < N / 2; i++) {
		for (j = 0; j < N / 2; j++) {
			link_score += synergy[link[i]][link[j]];
		}
	}

	if (start_score - link_score < 0) return link_score - start_score;
	else return start_score - link_score;

}


void print_status() {
	int i, j;

	printf("[Start]\t");
	for (i = 0; i < N / 2; i++) {
		printf(" %d", start[i]);
	}
	printf("\t===> %d\n",start_score);

	printf("[Link]\t");
	for (i = 0; i < N / 2; i++) {
		printf(" %d", link[i]);
	}
	printf("\t===> %d\n", link_score);
	printf("\n");
}



int calc_min_gap(int num_member) {
	
	int ret = -1;

	if (num_member == N / 2) {
		ret = calc_gap();
		//print_status();
		return ret;
	}
	
	

	int i, j;
	for (i = 0; i < N; i++) {
		if (flag[i] == 1)continue;
		if (num_member != 0) {
			if (start[num_member - 1] <= i)continue;
		}
		start[num_member] = i;
		flag[i] = 1;
		ret = minn(ret, calc_min_gap(num_member + 1));
		flag[i] = 0;
	}

	return ret;
}


int main() {

	scanf("%d", &N);

	int i, j;
	int tmp;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			scanf("%d", &tmp);
			synergy[j][i] = tmp;
		}
	}

	//clean flag
	for (i = 0; i < N; i++) {
		flag[i] = 0;
	}

	int ret;
	ret=calc_min_gap(0);

	printf("%d", ret);

	return 0;
}