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
    int from_person;
    int to_person;
    int status;
    char* detail_status;
    char* content;
    int company;
} Args;

#endif /* ARGS_H */