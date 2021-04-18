#include <stdio.h>
#include<stdbool.h>

int N;
int L;
int h[101][101];
int tmp_h[101][101];
int flag[101][101];


int calc_gap(int a, int b) {
	int ret = a - b;
	if (ret < 0) return -1 * ret;
	else return ret;
}

void print_status() {
	int i, j;

	printf("--------------------\n");
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			printf("%2d ", tmp_h[j][i]);
		}
		printf("\n");
	}
	printf("--------------------\n\n");
}

void copy_h_to_tmp_h() {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			tmp_h[j][i] = h[j][i];
		}
	}
}

bool check_sero_bingo(int n) {

	int current_value;
	int prev_value;
	int prev_cont;
	int i, j, k;


	current_value = h[n][1];
	prev_value = h[n][1];
	prev_cont = 1;
	for (i = 2; i <= N; i++) {

		current_value = h[n][i];
		//printf("[%d][%d][%d]\n", i, current_value, prev_cont);
		//case 1 : too many gap
		if (calc_gap(prev_value, current_value) > 1) {
			//printf(" --> case1\n");
			return false;
		}
		//case 2 : go up
		if (current_value - prev_value == 1) {
			if (prev_cont < L) {
				//printf(" --> case2\n");
				return false;
			}
			else {
				
				for (k = i - L; k <= i - 1; k++) {
					tmp_h[n][k] += 10;
				}
				//print_status();
				prev_cont = 0;
			}
		}
		//case 3 : go down
		if (current_value - prev_value == -1) {
			//over N
			if (i + L - 1 > N) {
				//printf(" --> case3-1\n");
				return false;
			}
			//check cont N
			for (j = 0; j <= L - 1; j++) {
				if (current_value != h[n][i + j]) {
					//printf(" --> case3-2\n");
					return false;
				}
			}

			for (j = 0; j <= L - 1; j++) {
				tmp_h[n][i + j] += 10;
			}
			//print_status();
			i = i + L - 1;
			prev_cont = -1;
		}
		//case 4 : flat
		prev_value = current_value;
		prev_cont++;
	}

	return true;
}

bool check_garo_bingo(int n) {

	int current_value;
	int prev_value;
	int prev_cont;
	int i, j, k;


	current_value = h[1][n];
	prev_value = h[1][n];
	prev_cont = 1;
	for (i = 2; i <= N; i++) {

		current_value = h[i][n];
		//printf("[%d][%d][%d]\n", i, current_value, prev_cont);
		//case 1 : too many gap
		if (calc_gap(prev_value, current_value) > 1) {
			//printf(" --> case1\n");
			return false;
		}
		//case 2 : go up
		if (current_value - prev_value == 1) {
			if (prev_cont < L) {
				//printf(" --> case2\n");
				return false;
			}
			else {

				for (k = i - L; k <= i - 1; k++) {
					tmp_h[k][n] += 10;
				}
				//print_status();
				prev_cont = 0;
			}
		}
		//case 3 : go down
		if (current_value - prev_value == -1) {
			//over N
			if (i + L - 1 > N) {
				//printf(" --> case3-1\n");
				return false;
			}
			//check cont N
			for (j = 0; j <= L - 1; j++) {
				if (current_value != h[i+j][n]) {
					//printf(" --> case3-2\n");
					return false;
				}
			}

			for (j = 0; j <= L - 1; j++) {
				tmp_h[i + j][n] += 10;
			}
			//print_status();
			i = i + L - 1;
			prev_cont = -1;
		}
		//case 4 : flat
		prev_value = current_value;
		prev_cont++;
	}

	return true;
}

int main() {

	int i, j;

	scanf("%d", &N);
	scanf("%d", &L);



	//input
	
	int tmp;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			scanf("%d", &tmp);
			h[j][i] = tmp;
		}
	}

	int ret = 0;

	//copy h[] to tmp_h[]
	copy_h_to_tmp_h();

	//check garo line
	for (i = 1; i <= N; i++) {
		if (check_garo_bingo(i) == true) {
			ret++;
			//printf("[BINGO] line%d\n", i);
		}

	}

	//copy h[] to tmp_h[]
	copy_h_to_tmp_h();

	//check sero line
	for (i = 1; i <= N; i++) {
		if (check_sero_bingo(i) == true) {
			ret++;
			//printf("[BINGO] line%d\n", i);
		}

	}

	printf("%d", ret);

	return 0;

}