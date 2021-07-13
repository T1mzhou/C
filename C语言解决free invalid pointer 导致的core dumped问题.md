# C语言解决free invalid pointer 导致的core dumped问题

## 背景

在公司的项目中，编译运行后出来free invalid pointer的问题，导致程序运行直接段错误。

## 出现问题的代码片段

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char * test_data = (char*)malloc(24);
	if (test_data == NULL) {
		printf("test data malloc failed\n");
		return 0;
	}
	
	bzero(test_data, 24);
	
	char test[] = "HelloT1mzhouCSDNTEST";
	strcpy(test_data, test);
	
	char buf[24];
	for (int i = 0; i < 24; i++) {
		buf[i] = *test_data++;
	}
	
	free(test_data);
	test_data = NULL;

	return 0;
}
```

## 解决方案

```c
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
```

## 为什么需要这样处理？

todo;

malloc申请的空间，有元数据，保存申请空间的基本信息。