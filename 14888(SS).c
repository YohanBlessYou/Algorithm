#include<stdio.h>
#include<stdbool.h>

int N;
int number[11];
int num_operator[4];
int array_operator[10];

int max = 0;
int min = -1;


int maxx(int a, int b) {
	if (a > b)return a;
	else return b;
}

int minn(int a, int b) {
	if (a == -1) return b;

	if (a < b) return a;
	else return b;
}

void print_path() {
	int i, j;
	printf("\n");
	for (i = 0; i < N - 1; i++) {
		printf("%d", number[i]);
		switch (array_operator[i]) {
		case 0:printf("+");
			break;
		case 1:printf("-");
			break;
		case 2:printf("¡¿");
			break;
		case 3:printf("¡À");
			break;
		}
	}
	printf("%d", number[N - 1]);
	//printf(" = %d", calc_result());
	printf("\n");
}

int calc_result() {

	int i, j;

	int tmp = number[0];

	for (i = 0; i < N - 1; i++) {
		switch (array_operator[i]) {
		case 0:tmp = tmp + number[i + 1];
			break;
		case 1: tmp = tmp - number[i + 1];
			break;
		case 2: tmp = tmp * number[i + 1];
			break;
		case 3: if (tmp < 0) tmp = (((-1) * tmp) / number[i + 1]) * (-1);
			  else tmp = tmp / number[i + 1];
			break;
		}
	}

	return tmp;

}


void go_ahead(int depth) {

	if (depth == N-1) {
		//print_path();
		int ret = calc_result();
		min = minn(min, ret);
		max = maxx(max, ret);
		return;
	}

	int i, j;

	if (num_operator[0] != 0) {
		num_operator[0]--;
		array_operator[depth] = 0;
		go_ahead(depth + 1);
		num_operator[0]++;
	}
	if (num_operator[1] != 0) {
		num_operator[1]--;
		array_operator[depth] = 1;
		go_ahead(depth + 1);
		num_operator[1]++;
	}
	if (num_operator[2] != 0) {
		num_operator[2]--;
		array_operator[depth] = 2;
		go_ahead(depth + 1);
		num_operator[2]++;
	}
	if (num_operator[3] != 0) {
		num_operator[3]--;
		array_operator[depth] = 3;
		go_ahead(depth + 1);
		num_operator[3]++;
	}

}





int main() {

	scanf("%d", &N);

	int i, j;
	int tmp;
	for (i = 0; i < N; i++) {
		scanf("%d", &tmp);
		number[i] = tmp;
	}

	for (i = 0; i < 4; i++) {
		scanf("%d", &tmp);
		num_operator[i]=tmp;
	}

	go_ahead(0);

	printf("%d\n%d", max, min);

	return 0;
}