// How to Compile:
// gcc -o bin/main main/main.c bin/sql.o bin/hash.o bin/utilities.o $(mysql_config --cflags) $(mysql_config --libs)

// Force package configuration: If the installation script failed to configure MySQL properly, you can try forcing the configuration using the --configure option with dpkg:
// sudo dpkg --configure -a

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// header
#include "headers/args.h"
#include "headers/sql.h"
#include "headers/hash.h"


int welcome() {
    printf("Welcome to the Courier Management System!\n\n");
    // printf("1. Client\n2. User\n3. Track your order\n4. Exit\n:");
    printf("1. Login\n2. Register\n3. Track your order\n4. Exit\n:");
};


int main()
{
    bool run = 1;

    Auth auth = {
        "localhost",
        "rdj",
        "root",
        "courier"
    };

    while (run) {
        welcome();

        int input;
        scanf("%d", &input);
        printf("You entered: %d\n", input); // int check is missing

        if (input == 1) { // login for both client and user it'll return the id of the user or client
            // allocate 100 bytes of memory for 
            char* email = malloc(255); // malloc because of scanf and memory will be freed in sql.c
            char* password = malloc(100);
            printf("Enter your Email: ");
            scanf("%s", email);
            printf("Enter your password: ");
            scanf("%s", password);

            Args args = {
                .auth = {
                    .email = email,
                    .passwd = hash(password)
                }
            };

            bool status = login(auth, args);
            if (status) {
                printf("Login Successful!\n");

                int input;
                printf("1. Add Courier\n2. Update Courier\n3. Exit\n:");
                scanf("%d", &input);
                if (input == 1) {
                    int unsigned* from_person = malloc(sizeof(int unsigned));
                    int unsigned* to_person = malloc(sizeof(int unsigned));
                    int unsigned* status = malloc(sizeof(int unsigned));
                    char* detail_status = malloc(255);
                    char* content = malloc(255);
                    int unsigned* company = malloc(sizeof(int unsigned));

                    printf("From Person: ");
                    scanf("%u", from_person);
                    printf("To Person: ");
                    scanf("%u", to_person);
                    printf("Status [0=Pending, 1=In Transit, 2=Delivered]: ");
                    scanf("%u", status);
                    printf("Detail Status: ");
                    scanf("%s", detail_status);
                    printf("Content: ");
                    scanf("%s", content);
                    printf("Company: ");
                    scanf("%u", company);
                
                    Args args = {
                        .courier = {
                            .from_person = *from_person,
                            .to_person = *to_person,
                            .status = *status,
                            .detail_status = detail_status,
                            .content = content,
                            .company = *company
                        }
                    };
                    bool q_status = add_courier(auth, args);
                    if (q_status) {
                        printf("Courier Added Successfully!\n");
                    } else {
                        printf("Courier Added Failed!\n");
                    }
                } else if (input == 2) {
                    // update courier
                    int unsigned* sn = malloc(sizeof(int unsigned));
                    int unsigned* status = malloc(sizeof(int unsigned));
                    char* detail_status = malloc(255);

                    printf("Id No: ");
                    scanf("%u", sn);
                    printf("New Status [0=Pending, 1=In Transit, 2=Delivered]: ");
                    scanf("%u", status);
                    printf("Detail Status: ");
                    scanf("%s", detail_status);

                    Args args = {
                        .up_courier = {
                            .sn = *sn,
                            .status = *status,
                            .detail_status = detail_status,
                        }
                    };

                    bool q_status = update_courier(auth, args);
                    free(sn);
                    free(status);
                    if (q_status) {
                        printf("Courier Updated Successfully!\n");
                    } else {
                        printf("Courier Updated Failed!\n");
                    }
                } else if (input == 3) {
                    run = 0;
                } else {
                    // invalid input
                }       
            } else {
                printf("Login Failed!\n");
            }
        } else if (input == 2) {
            // REGISTER
            int input;
            printf("1. Register as User\n2. Register as Client\n3. Exit\n:");
            scanf("%d", &input);

            if (input == 1) {
                // register as user
                char* full_name = malloc(255);

                char* first_name = malloc(100);
                char* last_name = malloc(100);
                char* address = malloc(255);
                char* city = malloc(255);
                char* state = malloc(255);
                int unsigned* zip = malloc(sizeof(int unsigned));
                long long unsigned* phone = malloc(sizeof(long long unsigned));
                char* email = malloc(255);

                char* passwd = malloc(100);

                printf("Enter your first name: ");
                scanf("%s", first_name);
                printf("Enter your last name: ");
                scanf("%s", last_name);
                printf("Enter your address: ");
                scanf("%s", address);
                printf("Enter your city: ");
                scanf("%s", city);
                printf("Enter your state: ");
                scanf("%s", state);
                printf("Enter your zip: ");
                scanf("%u", zip); // int check is missing, program will crash if int is not provided
                printf("Enter your phone: ");
                scanf("%llu", phone);
                printf("Enter your email: ");
                scanf("%s", email);

                printf("Choose A Strong Password: ");
                scanf("%s", passwd);

                sprintf(full_name, "%s %s", first_name, last_name);

                Args args = {
                    .user = {
                        .full_name = full_name,
                        .address = address,
                        .city = city,
                        .state = state,
                        .zip = *zip,
                        .phone = *phone,
                        .email = email,

                        .passwd = hash(passwd) // only including it addind some weird characters to the string of the string returned by sql_str_formatter function, remember only including this line not even using hash
                    }
                };

                add_user(auth, args);

                printf("Account Created successfully!\n");

            } else if (input == 2) {
                // register as client
                char* name = malloc(255);
                char* address = malloc(255);
                char* city = malloc(255);
                char* state = malloc(255);
                int unsigned* zip = malloc(sizeof(int unsigned));
                long long unsigned* phone = malloc(sizeof(long long unsigned));
                char* fax = malloc(255);
                char* email = malloc(255);
                char* url = malloc(255);

                char* passwd = malloc(100);

                printf("Enter your first name: ");
                scanf("%s", name);
                printf("Enter your address: ");
                scanf("%s", address);
                printf("Enter your city: ");
                scanf("%s", city);
                printf("Enter your state: ");
                scanf("%s", state);
                printf("Enter your zip: ");
                scanf("%u", zip); // int check is missing, program will crash if int is not provided
                printf("Enter your phone: ");
                scanf("%llu", phone);
                printf("Enter your fax: ");
                scanf("%s", fax);
                printf("Enter your email: ");
                scanf("%s", email);
                printf("Enter your url: ");
                scanf("%s", url);

                printf("Choose A Strong Password: ");
                scanf("%s", passwd);

                Args args = {
                    .client = {
                        .name = name,
                        .address = address,
                        .city = city,
                        .state = state,
                        .zip = *zip,
                        .phone = *phone,
                        .fax = fax,
                        .email = email,
                        .url = url,

                        .passwd = hash(passwd)
                    }
                };

                add_client(auth, args);
            } else if (input == 3) {
                // exit
            } else {
                // invalid input
            }
        } else if (input == 3) {
            int unsigned* sn = malloc(sizeof(int unsigned));

            printf("Enter Courier ID: ");
            scanf("%u", sn); 

            Args args = {
                .track = {
                    .sn = *sn
                }
            };

            // track_cour(auth, args);        
        } else if (input == 4) {
            run = 0;
        } else {
            // invalid input
        }
    };

    // for user just give Id address and phone no. and all the details will be given

    // for client { ADD item, Update Item }


    return 0;
};