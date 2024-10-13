#include <mysql/mysql.h>  // contains all the definations of mysql functions and structs...

MYSQL* connect1(MYSQL *conn, Auth auth);

void fetch(MYSQL* conn, const char* query, int len);
bool add_courier(Auth auth, Args args);
void add_user(Auth auth, Args args);
void add_client(Auth auth, Args args);

bool update_courier(Auth auth, Args args);
void track_cour(Auth auth, Args args);

bool login(Auth auth, Args args);