#include <stdio.h>
#include <string.h> // for sprintf
#include <stdarg.h> // for string formater
#include <stdlib.h> // for malloc

char* str_formatter(const char* type, ...) {
    /*
    Types {
        d: int,
        c: char,
        f: float,
        s: string,
    }
    */

    va_list args;
    va_start(args, type);

    // char str[1000] = ""; // if not inicialized(like this: char star[1000]), it'll print garbage when strcat, Why? bcz when we use the strcat function to append the string "Hello" to str. However, since str is uninitialized, it may not contain a null terminator ('\0') at the end of the array, which is required by C to indicate the end of a string. If str does not contain a null terminator, strcat will continue to write the characters of "Hello" to str until it finds a null terminator somewhere in memory, which could result in undefined behavior...
    char* str = malloc(1000 * sizeof(char)); // The problem with returning a pointer to a local variable is that the memory allocated for the variable is deallocated when the function returns, so the pointer you return will be pointing to a location in memory that is no longer valid. Dereferencing this pointer can lead to undefined behavior.
    // But now why does it work without inicializing it with '\0' or "" ?

    char* d = "%d";
    char* c = "%c";
    char* f = "%f";
    char* s = "%s";

    char* second_btw = va_arg(args, char*);
    ++type;
 
    while (*type != '\0') {
        if (*type == 'd') {
            int i = va_arg(args, int);
            char temp[512];
            sprintf(temp, d, i);
            strcat(str, temp);
        } else if (*type == 'c') {
            // A 'char' variable will be promoted to 'int'
            // A character literal in C is already 'int' by itself
            int _c = va_arg(args, int);
            char temp[512];
            sprintf(temp, c, _c);
            strcat(str, temp);
        } else if (*type == 'f') {
            double d = va_arg(args, double);
            char temp[512];
            sprintf(temp, f, d);
            strcat(str, temp);
        }else if (*type == 's') {
            char* _s = va_arg(args, char*);
            char temp[512];
            sprintf(temp, s, _s);
            strcat(str, temp);
        }
        strcat(str, second_btw);
        ++type; // increment type pointer to next byte in memory via pointer arithmetics
    }
 
    va_end(args);

    // Poping the last character(extra btw char)
    int btw_len = strlen(second_btw);
    for (int i = 0; i < btw_len; i++) {
        *(str + strlen(str) - 1) = '\0';
        // str[strlen(str) - 1] = '\0'; // Same as above
    }

    return str;
};

char* sql_str_formatter(const char* type, ...) {
    /*
    Types {
        d: int,
        c: char,
        f: float,
        s: string,
    }
    */

    va_list args;
    va_start(args, type);

    // char str[1000] = ""; // if not inicialized(like this: char star[1000]), it'll print garbage when strcat, Why? bcz when we use the strcat function to append the string "Hello" to str. However, since str is uninitialized, it may not contain a null terminator ('\0') at the end of the array, which is required by C to indicate the end of a string. If str does not contain a null terminator, strcat will continue to write the characters of "Hello" to str until it finds a null terminator somewhere in memory, which could result in undefined behavior...
    char* str = malloc(1000 * sizeof(char)); // The problem with returning a pointer to a local variable is that the memory allocated for the variable is deallocated when the function returns, so the pointer you return will be pointing to a location in memory that is no longer valid. Dereferencing this pointer can lead to undefined behavior.
    // But now why does it work without inicializing it with '\0' or "" ?

    char* d = "%d";
    char* c = "%c";
    char* f = "%f";
    char* s = "%s";

    char* second_btw = va_arg(args, char*);
    ++type;

    int type_len = strlen(type);
 
    int count = 0;
    while (*type != '\0') {
        count++;
        if (*type == 'd') {
            int i = va_arg(args, int);
            char temp[512];
            sprintf(temp, d, i);
            strcat(str, temp);
        } else if (*type == 'c') {
            // A 'char' variable will be promoted to 'int'
            // A character literal in C is already 'int' by itself
            int _c = va_arg(args, int);
            char temp[512];

            // adding "" to the string
            if (count != 1 && count != type_len) {
                sprintf(temp, s, "\"");
                strcat(str, temp);
            }

            sprintf(temp, c, _c);
            strcat(str, temp);

            if (count != 1 && count != type_len) {
                sprintf(temp, s, "\"");
                strcat(str, temp);
            }
        } else if (*type == 'f') {
            double d = va_arg(args, double);
            char temp[512];
            sprintf(temp, f, d);
            strcat(str, temp);
        }else if (*type == 's') {
            char* _s = va_arg(args, char*);
            char temp[512];
            // adding "" to the string
            if (count != 1 && count != type_len) {
                sprintf(temp, s, "\"");
                strcat(str, temp);
            }

            sprintf(temp, s, _s);
            strcat(str, temp);

            if (count != 1 && count != type_len) {
                sprintf(temp, s, "\"");
                strcat(str, temp);
            }
        }
        if (count != 1 && count != type_len-1) {
        // if (count != 1) {
            strcat(str, second_btw);
        }
        ++type; // increment type pointer to next byte in memory via pointer arithmetics
    }
 
    va_end(args);

    // Poping the last character(extra btw char)
    int btw_len = strlen(second_btw);
    for (int i = 0; i < btw_len; i++) {
        *(str + strlen(str) - 1) = '\0';
        // str[strlen(str) - 1] = '\0'; // Same as above
    }

    return str;
};

// int main() {
//     char* a = "Hello World";

//     // str_formatter("dpc", 1, 2, "Hello World");
//     char* res = sql_str_formatter("sssdc", " ,", a, "KAY", 1, 'z');
//     // printf("%lu", sizeof(res)); 
//     printf("%s", res); // in printf we don't need to dereference the pointer, it'll do it for us, if there is %s in the string, it'll print the value of the pointer, not the address of the pointer. Dereferencing the pointer would give the function the value of the first char only in the string, and the pointer will be lost, which is not what we want, but the printf formatting is built to handle this for us by accepting a pointer.
//     return 0;
// };