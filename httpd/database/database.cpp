#include"database.h"
/************************************************/
 /* query info by page_name from the database
  * Parameters: the buffer to save query result
  *		the key for query
  * return val  0:success -1:error */
 /***********************************************/
int query_database(char* page_info,char* page_name)
{
			char sql[100] = "select page from weather where cityname=";
			strcat(sql, "'");
			strcat(sql, page_name);
			strcat(sql, "'");
			MYSQL my_connection;
			MYSQL_ROW row;//
			int ret;
			MYSQL_RES *res;
			mysql_init(&my_connection);
			if (mysql_real_connect(&my_connection, "localhost", "root", "marker", "wea", 0, NULL, 0))
			{
				//printf("Connection database success\n");
				ret = mysql_query(&my_connection, sql);
				if (ret != 0)
				{
					printf("query error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
					mysql_close(&my_connection);
					return -1;
				}
				res = mysql_store_result(&my_connection);
				if (!res)
				{
					printf("query error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
					mysql_close(&my_connection);
					return -1;
				}
				row = mysql_fetch_row(res);//return NULL if no more row
				if (row == NULL)
				{
					printf("get data from database error\n");
					mysql_free_result(res);
					mysql_close(&my_connection);
					return -1;
				}
				printf("get data:<%s> from database success\n", page_name);
				//rc = memcached_set(memc, page_name, strlen(page_name), row[0], strlen(row[0]), (time_t)180, (uint32_t)0);
				//	if(rc)
				strcpy(page_info, row[0]);
				mysql_free_result(res);
				mysql_close(&my_connection);
			}
			else
			{
				printf("connect  error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
				mysql_close(&my_connection);
				return -1;
			}
			return 0;
}

