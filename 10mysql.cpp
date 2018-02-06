#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

MYSQL *g_conn; // mysql 连接
MYSQL_RES *g_res;
MYSQL_ROW g_row;
#define MAX_BUF_SIZE 1024
const char *g_host_name = "10.0.1.10";
const char *g_user_name = "game";
const char *g_password = "game";
const char *g_db_name = "ms";
const unsigned int g_db_port = 3306;

void print_mysql_error(const char *msg) {
    if (msg)
        printf("%s: %s\n", msg, mysql_error(g_conn));
    else
        puts(mysql_error(g_conn));
}

int executesql(const char * sql) {
    if (mysql_real_query(g_conn, sql, strlen(sql)))
        return -1;
    return 0;
}

int init_mysql() {
    g_conn = mysql_init(NULL);
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, g_db_port, NULL, 0)) // 如果失败
        return -1;
    if (executesql("set names utf8"))
        return -1;

    return 0;
}

int main(int argc,char **argv ) {

    if (init_mysql());
        print_mysql_error(NULL);
    char sqlstr[10000] ;
	//freopen("uu.txt","r",stdin);
	//freopen("test.txt","w",stdout);
	int x =0;
	int xx=0;
	//	char *num = argv[1];
	int uin = atoi(argv[1]);
	//while(scanf("%d",&x) != EOF)
	do
    {
        //int xx= x%16;
        //sprintf(sqlstr,"SELECT uin,FROM_UNIXTIME(last_login_time) FROM role_%d where last_login_time>1507824000 and coin>1000000",xx++);
		//sprintf(sqlstr,"select uin,collect_data from award_15;where uin= 16719",xx++);
		//sprintf(sqlstr,"select uin,skill_hanging_data from role_%d where uin=17827 ",xx++);
		sprintf(sqlstr,"select uin,skill_hanging_data from role_%d where uin=%d ",uin%16,uin);
        if (executesql(sqlstr))
        print_mysql_error(NULL);

        g_res = mysql_store_result(g_conn);

        while ((g_row=mysql_fetch_row(g_res)))
            printf("%s\t%s\t\n", g_row[0],g_row[1]);
        mysql_free_result(g_res);
    }while(0);
    mysql_close(g_conn);
}
