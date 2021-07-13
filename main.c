#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* test_data = (char*)malloc(24);
	if (test_data == NULL) {
		printf("test data malloc failed\n");
		return 0;
	}
	
	bzero(test_data, 24);
	
	char test[] = "HelloT1mzhouCSDNTEST";
	strcpy(test_data, test);
	
	char buf[24];
	char* tmp =  test_data;	// 使用临时指针指向malloc的空间
	for (int i = 0; i < 24; i++) {
		buf[i] = *tmp++;	// 数据操作使用tmp指针
	}
	
	free(test_data);
	test_data = NULL;

	return 0;
}