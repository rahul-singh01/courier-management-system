// for Linux to include mysql.h: apt install libmysqlclient-dev
/*
how to compile: {
    When using sql from main of same file use{
        gcc -o sql-output sql.c $(mysql_config --cflags) $(mysql_config --libs)

        with hash included in main:
        gcc -o sql-output sql.c $(mysql_config --cflags) $(mysql_config --libs) -lcrypto bin/utilities.o bin/hash.o
    },
    When using sql from main of different file use{
        gcc -c sql.c -o /bin/sql.o

        Why -> We don't need to give it all the files for to run sql until it's really not gonna run it but only the headers, we'll give all the real files in main.c
    }
}
*/ 

#include <mysql/mysql.h>  // contains all the definations of mysql functions and structs...
#include <stdio.h>

// header
#include "headers/utilities.h"
#include "headers/args.h"

// remove
// #include "headers/hash.h"



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

bool run(Auth auth, Args args, bool (*func)(MYSQL*, Args)) { // void (*func)(Args) is a defination of a function pointer, it'll point to a function which takes Args as argument and returns void
    printf("run");
    MYSQL* conn;
    conn = connect1(conn, auth); // new database connected conn
    bool status = (*func)(conn, args);

    mysql_close(conn); // close connection

    return status;
};
bool run_query(MYSQL* conn, const char* query) {
    // to run the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    };
    return 1;
};

void if_not() {

};

void fetch(MYSQL* conn, const char* query, int len) {
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

bool _add_courier(MYSQL* conn, Args args) {
    char* stat[3] = {"Pending", "In Transit", "Delivered"};
    
    char* _query_s = "INSERT INTO couriers (from_person, to_person, status, detail_status, content, company) VALUES (";
    char* _query_e = ");";
    
    char* query = sql_str_formatter("ssddsssds", " ,", _query_s, args.courier.from_person, args.courier.to_person, stat[args.courier.status], args.courier.detail_status, args.courier.content, args.courier.company, _query_e);
    char* temp = query+ 5;

    printf("%s", temp);
    
    bool status = run_query(conn, temp);
    // printf("%d", status);
    return status;
};

bool add_courier(Auth auth, Args args) {
    // default parameters are not supported(can be implemented with the help of variadic functions, func(int count, ...))

    return run(auth, args, _add_courier);
};

bool _update_courier(MYSQL* conn, Args args) {
    printf("before");
    char* stat[3] = {"Pending", "In Transit", "Delivered"};

    // UPDATE couriers SET status = 'new_status', detail_status = 'new_detail_status' WHERE sn = 'courier_sn';

    
    char* _query_1 = "UPDATE couriers SET status = ";
    char* _query_2 = ", detail_status = ";
    char* _query_3 = "WHERE sn = ";
    char* _query_e = ";";

    char* query = sql_str_formatter("ssssssss", " ,", _query_1, stat[args.up_courier.status], _query_2, args.up_courier.detail_status, _query_3, args.up_courier.sn, _query_e);
    char* temp = query+ 5;

    printf(" checking the query : %s", temp);
    
    bool status = run_query(conn, temp);

    free(query);
    free(args.up_courier.detail_status);

    // printf("%d", status);
    return status;
};

bool update_courier(Auth auth, Args args) {
    printf("in update_courier\n");

    bool status = run(auth, args, _update_courier);
    return status;
};

bool _add_user(MYSQL* conn, Args args) {
    char* _query_s = "INSERT INTO users (full_name, address, city, state, zip, phone, email, passwd_hash) VALUES (";
    char* _query_e = ");";

    // printf("%s", args.user.passwd);
    
    char* query = sql_str_formatter("ssssssugsss", " ,", _query_s, args.user.full_name, args.user.address, args.user.city, args.user.state, args.user.zip, args.user.phone, args.user.email, args.user.passwd, _query_e);

    // char* query = str_formatter("ssssss", _query_s, " ,", args.name, args.email, args.phone, args.address, args.password, _query_e);
    printf("%s", query);

    char* temp = query+ 5 + 2; // 5 extra bytes because of hash function + 1 space, I don't know why

    // free malloced memory
    free(args.user.full_name);
    free(args.user.address);
    free(args.user.city);
    free(args.user.state);
    free(args.user.email);
    free(args.user.passwd);

    printf("%s", temp);

    bool status = run_query(conn, temp);

    free(query);

    return status;
};
void add_user(Auth auth, Args args) {
    run(auth, args, _add_user);
};

bool _add_client(MYSQL* conn, Args args) {
    char* _query_s = "INSERT INTO companies (name, address, city, state, zip, phone, fax, email, url, passwd_hash) VALUES (";
    char* _query_e = ");";
    
    // char* query = sql_str_formatter("sss", " ,", _query_s, _query_e);
    char* query = sql_str_formatter("ssssssugsssss", " ,", _query_s, args.client.name, args.client.address, args.client.city, args.client.state, args.client.zip, args.client.phone, args.client.fax, args.client.email, args.client.url, args.client.passwd, _query_e);

    printf("%s\n", query);

    // printf("%lu\n", sizeof(*query));
    // printf("%c\n", *query);
    char* temp = query + 5 + 1; // 5 extra bytes because of hash function + 1 space, I don't know why
    // printf("%s\n", query);

    // free malloced memory
    free(args.client.name);
    free(args.client.address);
    free(args.client.city);
    free(args.client.state);
    free(args.client.fax);
    free(args.client.email);
    free(args.client.url);
    free(args.client.passwd);

    printf("%s\n", temp);
    bool status = run_query(conn, temp);

    free(query);

    return status;
};
void add_client(Auth auth, Args args) {
    run(auth, args, _add_client);
};

bool _track_cour(MYSQL* conn, Args args) {
    char* _query_s = "SELECT status from courier where sn=";
    char* _query_e = ";";

    char* query = sql_str_formatter("sss", " ", _query_s, args.track.sn, _query_e);

    char* temp = query+ 5 + 1;

    printf("%s\n", temp);
    bool status = run_query(conn, temp);

    free(query);

    return status;
};
void track_cour(Auth auth, Args args) {
    run(auth, args, _add_client);
};

bool _login(MYSQL* conn, Args args) {
    /*
    btw = between,
    yq = yes quotes,
    */
    Query query1 = {
        .settings = "btw",
        .data = "SELECT TRUE FROM users WHERE passwd_hash = "
    };

    Query query2 = {
        .settings = "btw",
        .data = "AND email = "
    };

    Query query3 = {
        .settings = "btw",
        .data = "UNION SELECT TRUE FROM companies WHERE passwd_hash ="
    };

    Query query4 = {
        .settings = "btw",
        .data = ";"
    };

    Query passwd = {
        .settings = "btw yq",
        .data = args.auth.passwd
    };
    Query email = {
        .settings = "btw yq",
        .data = args.auth.email
    };

    MYSQL_RES *res;
    int num_rows;

    char* query = adv_sql_str_formatter("ssssssssss", " ", query1, passwd, query2, email, query3, passwd, query2, email, query4);
    char* temp = query + 5 + 1;
    // char* temp = query;

    free(args.auth.passwd);
    free(args.auth.email);

    printf("%s\n", temp);
    bool status = run_query(conn, temp);

    free(query);

    res = mysql_store_result(conn);
    num_rows = mysql_num_rows(res);
    if (num_rows == 0) {
        return 0;
    }

    return status;
};    
bool login(Auth auth, Args args) {
    bool status = run(auth, args, _login);
    return status;
};

int main() {
    /*
    ERROR: There was a err in this code, I don't remember exactly, but when I was using hash function in main.c and sql.c both, it was adding some weird characters to the string of the string returned by sql_str_formatter function, remember only including this line not even using hash. NOW, I think it was because of scope of the returned value, what I was returning was inicialized on the stack, it goes out of scope when exited the function or it's scope ends, so I was returning a pointer to a value which was not there anymore, fix that. I don't have the knowledge earlier, so I was not able to fix it, improve your knowledge before taking such a big task.
    */


    // char* _query_s = "INSERT INTO companies (name, address, city, state, zip, phone, fax, email, url) VALUES (";
    // char* _query_e = ");";
    
    // char* query = sql_str_formatter("sss", " ,", _query_s, _query_e);

    // printf("%s", query);

    Auth auth = {
        "localhost",
        "rdj",
        "root",
        "courier"
    };
    Args args = {
        .track = {
            .sn = 4
        }
    };

    track_cour(auth, args);
}


// int main() {

//     char* name = malloc(255);
//     char* address = malloc(255);
//     char* city = malloc(255);
//     char* state = malloc(255);
//     int unsigned* zip = malloc(sizeof(int unsigned));
//     long long unsigned* phone = malloc(sizeof(long long unsigned));
//     char* fax = malloc(255);
//     char* email = malloc(255);
//     char* url = malloc(255);

//     char* passwd = malloc(255);
//     // char passwd[255];

//     printf("Enter your first name: ");
//     scanf("%s", name);
//     printf("Enter your address: ");
//     scanf("%s", address);
//     printf("Enter your city: ");
//     scanf("%s", city);
//     printf("Enter your state: ");
//     scanf("%s", state);
//     printf("Enter your zip: ");
//     scanf("%u", zip); // int check is missing, program will crash if int is not provided
//     printf("Enter your phone: ");
//     scanf("%llu", phone);
//     printf("Enter your fax: ");
//     scanf("%s", fax);
//     printf("Enter your email: ");
//     scanf("%s", email);
//     printf("Enter your url: ");
//     scanf("%s", url);

//     printf("Choose A Strong Password: ");
//     scanf("%s", passwd);

//     // char* temp = hash(passwd);
//     char* pass = hash(passwd); // only including it addind some weird characters to the string of the string returned by sql_str_formatter function, remember only including this line not even using hash

//     Args args = {
//         .client = {
//             .name = name,
//             .address = address,
//             .city = city,
//             .state = state,
//             .zip = *zip,
//             .phone = *phone,
//             .fax = fax,
//             .email = email,
//             .url = url,

//             .passwd = pass
//         }
//     };

//     Auth auth = {
//         "localhost",
//         "kay",
//         "kush.mysql",
//         "test"
//     };
//     add_client(auth, args);
//     return 0;
// };