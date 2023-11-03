﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int isSequence(int* a, int n) {
	int i = 0;
	int d = a[1] - a[0];

	for (i = 1; i < n - 1; i++) { // 길이가 n인 배열이므로 인덱스 번호는 n-1 까지임.
		if (d != a[i + 1] - a[i])
			return 0; // 등차수열이 아닌 경우
	}
	return 1; // 등차수열인 경우
}

int pick(int* operators, int n, int* bucket, int bucketSize, int k, int* num1, int* num2) { 
	int i, lastIndex, smallest, item;
	int count = 0;

	if (k == 0) {
		for (i = 0; i < bucketSize; i++) 
			num2[i] = num1[i] + operators[bucket[i]]; // num2 에 num1 + operator 값을 넣음.

		if (isSequence(num2, bucketSize) == 1) // num2가 등차수열인지 검사
			return 1; // count += 1
		else
			return 0; // count += 0
	}

	lastIndex = bucketSize - k - 1;
	smallest = 0;
	
	for (item = smallest; item < n; item++) {
		bucket[lastIndex + 1] = item;
		count += pick(operators, 3, bucket, bucketSize, k - 1, num1, num2); // count에 return 값 누적
	}

	return count; // 마지막에 return count
}

int main(void) {
	int operators[3] = { -1, 0, 1 };
	int bucketSize;
	int* bucket;
	int* num1;
	int* num2;

	printf("배열의 길이 입력: ");
	scanf("%d", &bucketSize);

	bucket = (int*)malloc(sizeof(int) * bucketSize);
	num1 = (int*)malloc(sizeof(int) * bucketSize); // 입력받은 등차수열
	num2 = (int*)malloc(sizeof(int) * bucketSize); // bucket + num1 한 결과
	
	printf("배열 입력: ");
	for (int i = 0; i < bucketSize; i++)
		scanf("%d", &num1[i]); // num1에 등차수열 입력
	
	printf("등차수열의 수: %d\n", pick(operators, 3, bucket, bucketSize, bucketSize, num1, num2));

	free(bucket);
	free(num1);
	free(num2);

	return 0;
}
