#include <mysql/mysql.h>  // contains all the definations of mysql functions and structs...

MYSQL* connect1(MYSQL *conn, Auth auth);
MYSQL* fetch(MYSQL* conn, const char* query, int len);
MYSQL* add_courier(Auth auth, Args args);