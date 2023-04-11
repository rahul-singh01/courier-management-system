#include <stdio.h>

int _func(int a, int b) {
    printf("Hello World from _func");
    printf("%d", a+b);
};

int func(int (*p)(int, int)) {
    (*p)(1, 2);
};


int main() {
    printf("Hello World from test");
    func(&_func);
    return 0;
}