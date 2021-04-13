#include <stdio.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

int color_array[100][100];
int flag_array[100][100];
int N;
int ret;
int current_start_node[2];

bool find_start_node(int x,int y) {
    int i = y;
    int j = x;
    for (; i < N; i++) {
        for (; j < N; j++) {
            if (flag_array[j][i] == 0) {
                current_start_node[0] = j;
                current_start_node[1] = i;
                ret++;
                return true;
            }
        }
        j = 0;
    }
    return false;
}

void spread_for_flag(int x, int y, int color) {
    if (flag_array[x][y] == 1) return;
    if (x != current_start_node[0] || y != current_start_node[1]) {
        if(color != color_array[x][y]) return;
    }

    flag_array[x][y] = 1;
    if(x != N-1) spread_for_flag(x + 1, y,color);
    if(y != N-1) spread_for_flag(x, y + 1, color);
    if (x != 0) spread_for_flag(x - 1, y, color);
    if (y != 0) spread_for_flag(x, y - 1, color);
}

void spread_for_flag_ab(int x, int y, int color) {
    if (flag_array[x][y] == 1) return;
    if (x != current_start_node[0] || y != current_start_node[1]) {
        if (color <= 1) {
            if (color_array[x][y] == 2) return;
        }
        else {
            if (color_array[x][y] < 2) return;
        }
    }

    flag_array[x][y] = 1;
    if (x != N - 1) spread_for_flag_ab(x + 1, y, color);
    if (y != N - 1) spread_for_flag_ab(x, y + 1, color);
    if (x != 0) spread_for_flag_ab(x - 1, y, color);
    if (y != 0) spread_for_flag_ab(x, y - 1, color);
}

void main() {
    int result_normal;
    int result_abnormal;
    int current_color = color_array[0][0]; //R=0,G=1,B=2
    ret = 0;
    current_start_node[0] = 0;
    current_start_node[1] = 0;

    scanf("%d", &N);
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            flag_array[j][i] = 0;
        }
    }

    char tmp[100];
    for (i = 0; i < N; i++) {
        scanf("%s", tmp);
        for (j = 0; j < N; j++) {
            if (tmp[j] == 'R')color_array[j][i] = 0;
            if (tmp[j] == 'G')color_array[j][i] = 1;
            if (tmp[j] == 'B')color_array[j][i] = 2;
        }
    }


    while (find_start_node(current_start_node[0], current_start_node[1])) {
        current_color = color_array[current_start_node[0]][current_start_node[1]];
        spread_for_flag(current_start_node[0], current_start_node[1], current_color);
    }
    printf("%d ", ret);


    ret = 0;
    current_start_node[0] = 0;
    current_start_node[1] = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            flag_array[j][i] = 0;
        }
    }
    while (find_start_node(current_start_node[0], current_start_node[1])) {
        current_color = color_array[current_start_node[0]][current_start_node[1]];
        spread_for_flag_ab(current_start_node[0], current_start_node[1], current_color);
    }
    printf("%d", ret);


    return;
}