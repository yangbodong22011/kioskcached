/*************************************************************************
	> File Name: testItem1.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 16 Feb 2017 12:41:20 AM CST
 ************************************************************************/

#include"Kiosktime.h"
#include"MemCachedClient.h"

#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<sys/types.h>
#include<unistd.h>
#include<string>
#include<assert.h>
#include<gperftools/profiler.h>
#include<stdio.h>


int main(int argc,char *argv[])
{
    //ProfilerStart("./testFoot.prof");
    
    MemCachedClient mc;


    int items = argc > 1 ? atoi(argv[1]) : 1000;
    int keylen = argc > 2 ? atoi(argv[2]) : 10;
    int valuelen = argc > 3 ? atoi(argv[3]) : 1000;
    
    char key_t[256] = {0};
    std::string key;
    std::string value;
   
    Timer t;
    for(int i = 0;i < items;++i) {
        snprintf(key_t,sizeof(key_t),"%0*d",keylen,i);
        key = key_t;
        value.assign(valuelen,"0123456789"[i%10]);

        //mc.Insert(key.c_str(),value.c_str(),0);
        mc.Get(key.c_str());
    }
    
    int time = t.elapsed_micro();

    std::cout << "===== Memcached GET ===== " << std::endl;
    std::cout << "requests number : "<< items  << std::endl;
    std::cout << "use time : " << 1.0 * time / 1000 / 1000 << " seconds" << std::endl;
    double qps = (1.0 * items) / (1.0 * time / 1000 / 1000);
    std::cout << qps << " QPS" << std::endl;
    //HeapProfilerStop();

    return 0;
}
