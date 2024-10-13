// 
#ifndef AUTH_H
#define AUTH_H

typedef struct {
    char* server;
    char* user;
    char* password;
    char* database;
} Auth;

#endif /* AUTH_H */
// 

#ifndef ARGS_H
#define ARGS_H

typedef struct {
    struct
    {
        int unsigned from_person;
        int unsigned to_person;
        int unsigned status;
        char* detail_status;
        char* content;
        int unsigned company;
    } courier;
    struct
    {
        int unsigned sn;
        int unsigned status;
        char* detail_status;
    } up_courier;
    struct
    {
        char* full_name;
        char* address;
        char* city;
        char* state;
        int unsigned zip;
        long long unsigned phone;
        char* email;
        
        char* passwd;
    } user;
    struct
    {
        char* name;
        char* address;
        char* city;
        char* state;
        int unsigned zip;
        long long unsigned phone;
        char* fax;
        char* email;
        char* url;

        char* passwd;
    } client;

    struct
    {
        char* email;
        char* passwd;
    } auth;
    
    struct
    {
        int unsigned sn;
    } track;
    

    // int from_person;
    // int to_person;
    // int status;
    // char* detail_status;
    // char* content;
    // int company;
} Args;

#endif /* ARGS_H */

#ifndef ADV_SQL_FORMATTER_H
#define ADV_SQL_FORMATTER_H

typedef struct{
    char* settings;
    char* data;
} Query;

#endif /* ADV_SQL_FORMATTER_H */