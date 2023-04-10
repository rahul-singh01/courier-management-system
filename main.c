#include <stdio.h>


int welcome() {
    printf("Welcome to the Courier Management System!\n\n");
    printf("1. Client\n2. User\n3. Track your order\n4. Exit\n:");
    // printf("1. Login\n2. Register\n3. Track your order\n4. Exit\n:");

    int input;
    scanf("%d", &input);
    printf("You entered: %d", input);

    // return input;
};

int main()
{
    // printf(welcome());
    welcome();

    // connect sql

    // ask for login or register

    // for user just give Id address and phone no. and all the details will be given

    // for client { ADD item, Update Item }


    return 0;
}