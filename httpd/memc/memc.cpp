#include"memc.h"
/********************************************************/
 /*Initialize and set memcached
  *Return val:a pointer to memcached_st structure that
  *	      will then be used by other libmemcached 
  *	      functions to communicate with the server */
 /*******************************************************/
memcached_st* memcache_init()
{
		memcached_st *memc;
		memcached_return rc;
		memcached_server_st* servers;

		memc = memcached_create(NULL);
		servers = memcached_server_list_append(NULL, (char*)"localhost", 11211, &rc);
		servers = memcached_server_list_append(servers, (char*)"localhost", 11212, &rc);
		//	servers = memcached_server_list_append(servers, (char*)"localhost", 1113, &rc);

		rc = memcached_server_push(memc, servers);
		memcached_server_free(servers);

		memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_DISTRIBUTION, MEMCACHED_DISTRIBUTION_CONSISTENT);
		memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_RETRY_TIMEOUT, 20);
		memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT, 5);
		return memc;
}
/*****************************************************************/
 /* Query data from memcached
  * Parameters:memcached_st pointer to communicate with the server
  *	       the buffer to save query result
  *	       the key for query
  * Return val 0 success     -1 failed */
 /****************************************************************/
int query_memcache(memcached_st* memc,char* page_info,char* page_name)
{
		size_t value_length = 0;
		//char* returned by memcached_get  must be free
		char *str_get_by_mem = memcached_get(memc, page_name, strlen(page_name), &value_length, (uint32_t)0, NULL);
		if (str_get_by_mem != NULL)
		{
			strcpy(page_info, str_get_by_mem);
			//printf("get data from cache success\n");
			free(str_get_by_mem);
			return 0;
		}
		else
		{
			printf("get data:<%s >from cache failed\n", page_name);
			free(str_get_by_mem);
			return -1;
		}
}

/****************************************/
/ * free the memcached*/
/ * *************************************/
void memcache_destroy(memcached_st* memc)
{
	memcached_free(memc);
}
