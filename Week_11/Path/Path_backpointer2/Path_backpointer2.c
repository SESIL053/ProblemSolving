﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 0 // start
#define LEFT 1 // 왼쪽에서 옴
#define UP 2 // 위에서 옴

#define NOT_AVAILABLE 0 // 계산되지 않음(= 0)
#define AVAILABLE 1 // 계산되어서 값 바로 사용 가능

int matrixPath(int** m, int r, int c, int i, int j, int** M, int** M1, int** bp) {
    if (M1[i][j] != NOT_AVAILABLE) // 경로 값이 계산된 경우
        return M[i][j]; // 바로 사용
    M1[i][j] = AVAILABLE; // 경로 값이 계산되었음을 나타냄.

    if (i == 0 && j == 0) {
        M[i][j] = m[i][j];
        return m[i][j];
    }
    else if (i == 0) {
        M[i][j] = matrixPath(m, r, c, 0, j - 1, M, M1, bp) + m[i][j];
        bp[i][j] = LEFT;
        return M[i][j];
    }
    else if (j == 0) {
        M[i][j] = matrixPath(m, r, c, i - 1, 0, M, M1, bp) + m[i][j];
        bp[i][j] = UP;
        return M[i][j];
    }
    else {
        int a, b;
        a = matrixPath(m, r, c, i - 1, j, M, M1, bp);
        b = matrixPath(m, r, c, i, j - 1, M, M1, bp);
        M[i][j] = ((a < b) ? a : b) + m[i][j];
        if (a < b)
            bp[i][j] = UP;
        else
            bp[i][j] = LEFT;
        return M[i][j];
    }
}

void print_path(int r, int c, int i, int j, int** bp) { 
    if (bp[i][j] == DEFAULT)
        printf("<%d %d> ", i, j);

    if (bp[i][j] == LEFT) {
        print_path(r, c, i, j - 1, bp);
        printf("<%d %d> ", i, j);
    }
    else if (bp[i][j] == UP) {
        print_path(r, c, i - 1, j, bp);
        printf("<%d %d> ", i, j);
    }

    return;
}

int main(void) {
    int** m, ** M, ** M1, ** bp; // M은 메모
    int i, j, r, c;
    r = c = 4; // 4x4 matrix

    m = (int**)malloc(sizeof(int*) * r);
    M = (int**)malloc(sizeof(int*) * r);
    M1 = (int**)malloc(sizeof(int*) * r);
    bp = (int**)malloc(sizeof(int*) * r);

    for (i = 0; i < r; i++) {
        m[i] = (int*)malloc(sizeof(int) * c);
        M[i] = (int*)malloc(sizeof(int) * c);
        M1[i] = (int*)malloc(sizeof(int) * c);
        bp[i] = (int*)malloc(sizeof(int) * c);
    }

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &m[i][j]);
            M1[i][j] = NOT_AVAILABLE; // 계산 여부를 X로 초기화
            bp[i][j] = DEFAULT; // 백포인터를 start로 초기화
        }
    }

    printf("%d\n", matrixPath(m, r, c, 3, 3, M, M1, bp));
    print_path(r, c, 3, 3, bp);
    printf("\n");

    return 0;
}