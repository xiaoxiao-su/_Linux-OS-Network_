#ifndef _MEMC_
#define _MEMC_

#include <libmemcached/memcached.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
memcached_st* memcache_init();
int query_memcache(memcached_st*,char*,char*);
void memcache_destroy(memcached_st*);
#endif
