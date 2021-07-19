# C语言解决网络数据传输缓冲区大小不确定的问题

## 背景

在项目开发中，我们常常遇到这样的状况：网络通信时使用的数据缓冲大小不确定。需要我们动态开辟数据缓冲的空间；

## 解决方案

### 使用GUN C扩展的零长数组

尽管零长度数组的大小为零，但由于尾部填充，这种类型的数组成员可能会增加封闭类型的大小。零长度数组成员距封闭结构开头的偏移量与具有一个或多个相同类型元素的数组的偏移量相同。零长度数组的对齐方式与其元素的对齐方式相同。

### 代码实现

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct zero_length_array {
    int length;
    int contents[0];
} zero_length_array_t;

int main() {

    printf("zero_length_array = %d\n", sizeof (zero_length_array_t)); //  size = 4;

    zero_length_array_t * zero_arr = (zero_length_array_t*)malloc(sizeof(zero_length_array_t) * 5);
    zero_arr->length = 5;

    for (int i = 0; i < 5; i++) {
        zero_arr->contents[i] = i + 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d\n", zero_arr->contents[i]);  // output 1 2 3 4 5
    }


    free(zero_arr);
    zero_arr = NULL;

    return 0;
}
```

## 总结

* 使用零长数组只是一个占位符并不会增大结构体的空间
* 使用零长数组能非常灵活的处理网络数据参数的缓冲区大小不确定的问题

## 参考资料

[GNU官方文档](https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html#Zero-Length)