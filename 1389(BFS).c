#include <stdio.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
int N;
int M;
int edge[100][100];
int distance[100];

int min(int x, int y) {
    if (x > y) return y;
    else return x;
}

void find_distance(int start, int depth) {
    int i;
    for (i = 0; i < N; i++) {
        if (edge[start][i] == 1) {
            distance[i] = min(distance[i], depth + 1);
        }
    }
}

int find_bacon() {
    int i, depth;
    for (depth = 0; depth < N; depth++) {
        for (i = 0; i < N; i++) {
            if (distance[i] == depth) find_distance(i, depth);
        }

        //printf("\n");
        for (i = 0; i < N; i++) {
            //printf("%3d\t", distance[i]);
        }
        //printf("\n");

    }

    int ret = 0;
    for (i = 0; i < N; i++) {
        ret += distance[i];
    }
    return ret;
}

int main() {

    scanf("%d", &N);
    scanf("%d", &M);


    //Set-up relationship(edge)
    int i, j;
    int tmp_usr, tmp_edge;
    for (i = 0; i < M; i++) {

        scanf("%d", &tmp_usr);
        scanf("%d", &tmp_edge);
        edge[tmp_usr-1][tmp_edge-1] = 1;
        edge[tmp_edge - 1][tmp_usr - 1] = 1;
    }

    int ret = 0;
    int tmp_ret = 0;
    int who = 0;
    for (i = 0; i < N; i++) {

        //init distance from 'i'
        for (j = 0; j < N; j++) {
            distance[j] = N;
        }
        distance[i] = 0;
        //printf("[Step%d]\n", i);
        //find bacon number
        tmp_ret = find_bacon();
        //printf("[%d's bacon : %d\n", i, tmp_ret);
        //update minimum 
        if (ret == 0) {
            ret = tmp_ret;
            who = 0;
        }
        else if (ret > tmp_ret) {
            ret = tmp_ret;
            who = i;
        }
    }

    printf("%d", who+1);

    return 0;
}


