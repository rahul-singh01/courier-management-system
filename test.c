#include <stdio.h>


int main() {
    printf("Hello World");
    // char str[1000];

    // strcat(str, 1);
    // int a = 5;
    // printf("%d", a);
    // a = take(a);
    // printf("%d", a);

    char* str_formater(const char* type, ...);

    char* res = str_formater("ssdc", "Hello World", " ", 1, 'z');
    printf("%s", res);

    return 0;
}