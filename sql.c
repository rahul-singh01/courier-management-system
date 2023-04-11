// for Linux to include mysql.h: apt install libmysqlclient-dev
/*
how to compile: {
    When using sql from main of same file use{
        gcc -o sql-output sql.c $(mysql_config --cflags) $(mysql_config --libs)
    },
    When using sql from main of different file use{
        gcc -c sql.c

        Why -> We don't need to give it all the files for to run sql until it's really not gonna run it but only the headers, we'll give all the real files in main.c
    }
}
*/ 

#include <mysql/mysql.h>  // contains all the definations of mysql functions and structs...
#include <stdio.h>

// header
#include "headers/utilities.h"
#include "headers/args.h"


MYSQL* connect1(MYSQL *conn, Auth auth) { /*
1. can't name connect, it exists somewhere in MYSQL, if name here linker will take this one and not find it there, when MYSQL calls for it... 
2. type must be MYSQL* not only MYSQL, because at defination of conn, it've type MYSQL pointer and throughout the whole operation mysql had make sure that the type of every variable define in mysql.h remain same. So, we have to return the same type of pointer...
*/

    conn = mysql_init(NULL);
   
    /* Connect to database */
    // mysql_real_connect() because mysql_connect() is deprecated
    if (!mysql_real_connect(conn, auth.server, auth.user, auth.password, auth.database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    };
    // try catch???

    return conn;
};

void if_not() {

};

void run_query(MYSQL* conn, const char* query) {
    // to run the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    };
};

MYSQL* fetch(MYSQL* conn, const char* query, int len) {
    MYSQL_RES* res;
    MYSQL_ROW row;
 
    run_query(conn, query);
    
    res = mysql_use_result(conn); // why didn't we use *res but res, it'll save a pointer, not the value of it, maybe mysql_use_result() returns a pointer...
    
    /* output fields of each row based on len mentioned */
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int i=0; i<len; i++) { // till len
            printf("%s ", row[i]);
        };
        printf("\n");
    };
    printf("\n\n");
 
    /* Release memory used to store results*/
    mysql_free_result(res);
};

void _add_courier(int from_person, int to_person, int status, char* detail_status, char* content, int company) {
    char* stat[3] = {"Pending", "In Transit", "Delivered"};
    
    char* _query_s = "INSERT INTO courier (from_person, to_person, status, detail_status, content, company) VALUES (";
    char* _query_e = ");";
    
    char* query = str_formatter("ssdddssds", _query_s, " ", from_person, to_person, status, stat[status], content, company, _query_e);

    printf("%s", query);
    // printf("%lu", sizeof(content)); content is a pointer...
};
MYSQL* add_courier(Auth auth, Args args) {
    // default parameters are not supported(can be implemented with the help of variadic functions, func(int count, ...))


    MYSQL* conn;
    conn = connect1(conn, auth); // new database connected conn

    _add_courier(args.from_person, args.to_person, args.status, args.detail_status, args.content, args.company);

    mysql_close(conn); // close connection

};

// void run(int (*func)(), arg) {
//     MYSQL* conn;
//     conn = connect1(conn, auth); // new database connected conn

//     (*func)(arg);

//     mysql_close(conn); // close connection
// };

// int main() {
//     // MYSQL* conn; // pointer to MYSQL object because mysql_real_connect() takes a pointer as a argument definded in mysql.h

//     // definig Auth type here throws error: "error: unknown type name ‘Auth’", Why???
//     // typedef struct {
//     //     char* server;
//     //     char* user;
//     //     char* password;
//     //     char* database;
//     // } Auth;

//     Auth auth = {
//         "localhost",
//         "kay",
//         "kush.mysql",
//         "test"
//     };
 
//     // conn = connect1(conn, auth); // new database connected conn
 
//     // What is I fire two mysql query without returing the updated conn pointer???
//     /* send SQL query */
//     // char* query1 = "SELECT * FROM test";
//     // char* query2 = "SELECT * FROM user";
 
//     // fetch(conn, query1, 10); // conn is updated
//     // fetch(conn, query2, 10); // conn is updated
    
//     Args args = {
//         1,
//         100,
//         0,
//         "Pending",
//         "Hello World",
//         1
//     };
//     add_courier(auth, args);
 
//     // mysql_close(conn); // close connection
// }
