// for Linux to include mysql.h: apt install libmysqlclient-dev
// how to compile: gcc -o sql sql.c $(mysql_config --cflags) $(mysql_config --libs)

#include <mysql/mysql.h>  // contains all the definations of mysql functions and structs...
#include <stdio.h>

// header
char* str_formatter(const char* type, ...); // from utilities.c


MYSQL* connect1(MYSQL *conn, char* server, char* user, char* password, char* database) { /*
1. can't name connect, it exists somewhere in MYSQL, if name here linker will take this one and not find it there, when MYSQL calls for it... 
2. type must be MYSQL* not only MYSQL, because at defination of conn, it've type MYSQL pointer and throughout the whole operation mysql had make sure that the type of every variable define in mysql.h remain same. So, we have to return the same type of pointer...
*/

    conn = mysql_init(NULL);
   
    /* Connect to database */
    // mysql_real_connect() because mysql_connect() is deprecated
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    };
    // try catch???

    return conn;
};

void if_not() {

};

void run(MYSQL* conn, const char* query) {
    // to run the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    };
};

MYSQL* fetch(MYSQL* conn, const char* query, int len) {
    MYSQL_RES* res;
    MYSQL_ROW row;
 
    run(conn, query);
    
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

MYSQL* add_courier(MYSQL* conn, int from_person, int to_person, int status, char* detail_status, char* content, int company) {
    // default parameters are not supported(can be implemented with the help of variadic functions, func(int count, ...))


    char* stat[3] = {"Pending", "In Transit", "Delivered"};
    
    char* _query_s = "INSERT INTO courier (from_person, to_person, status, detail_status, content, company) VALUES (";
    char* _query_e = ");";
    
    char* query = str_formatter("ssdddssds", _query_s, " ", from_person, to_person, status, stat[status], content, company, _query_e);

    printf("%s", query);
    // printf("%lu", sizeof(content)); content is a pointer...

};

int main() {
    MYSQL* conn; // pointer to MYSQL object because mysql_real_connect() takes a pointer as a argument definded in mysql.h
 
 
    char* server = "localhost";
    char* user = "kay";
    char* password = "kush.mysql";
    char* database = "test";
 
    conn = connect1(conn, server, user, password, database); // new database connected conn
 
    // What is I fire two mysql query without returing the updated conn pointer???
    /* send SQL query */
    char* query1 = "SELECT * FROM test";
    char* query2 = "SELECT * FROM user";
 
    fetch(conn, query1, 10); // conn is updated
    fetch(conn, query2, 10); // conn is updated
 
    add_courier(conn, 1, 100, 0, "Pending", "Hello World", 1);
 
    mysql_close(conn); // close connection
}
