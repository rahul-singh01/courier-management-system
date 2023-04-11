// How to Compile:
// gcc -o bin/main main.c bin/utilities.o bin/sql.o $(mysql_config --cflags) $(mysql_config --libs)


#include <stdio.h>

// header
#include "headers/args.h"
#include "headers/sql.h"


int welcome() {
    printf("Welcome to the Courier Management System!\n\n");
    printf("1. Client\n2. User\n3. Track your order\n4. Exit\n:");
    // printf("1. Login\n2. Register\n3. Track your order\n4. Exit\n:");
};

void login() {

}

int main()
{
    // printf(welcome());
    welcome();

    int input;
    scanf("%d", &input);
    printf("You entered: %d", input); // int check is missing

    if (input == 1) {
        // allocate 100 bytes of memory for 
        char* user = malloc(100);
        char* password = malloc(100);
        printf("Enter your username: ");
        scanf("%s", user);
        printf("Enter your password: ");
        scanf("%s", password);

        // login
        // free the memory allocated
        free(user);
        free(password); 


        // if login successful
        printf("Login successful!\n");
        int input;
        printf("1. Add Courier\n2. Update Courier\n3. Exit\n:");
        scanf("%d", &input);
        if (input == 1) {
            // add courier
            Auth auth = {
                "localhost",
                "kay",
                "kush.mysql",
                "test"
            };
            Args args = {
                1,
                10,
                0,
                "Pending",
                "Hello World",
                1
            };
            add_courier(auth, args);
        } else if (input == 2) {
            // update courier
        } else if (input == 3) {
            // exit
        } else {
            // invalid input
        }       

    } else if (input == 2) {
        // register
    } else if (input == 3) {
        // track
    } else if (input == 4) {
        // exit
    } else {
        // invalid input
    }

    // connect sql

    // ask for login or register

    // for user just give Id address and phone no. and all the details will be given

    // for client { ADD item, Update Item }


    return 0;
}