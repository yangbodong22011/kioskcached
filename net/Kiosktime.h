/*************************************************************************
	> File Name: Kisoktime.h
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 02 Mar 2017 12:27:33 AM CST
 ************************************************************************/

#ifndef _KISOKTIME_H
#define _KISOKTIME_H

#include<chrono>

using namespace std;
using namespace std::chrono;

class Timer {
public:
    Timer(): m_begin (high_resolution_clock::now()) {}
   
    template<typename Duration=milliseconds>  //毫秒
    int64_t elapsed() const {
        return duration_cast<Duration>(high_resolution_clock::now()-m_begin).count();
    }

    int64_t elapsed_micro() const {    //微秒
        return elapsed<microseconds>();
    }

    int64_t elapsed_seconds() const {  //秒
        return elapsed<seconds>();
    }

private:
    time_point<high_resolution_clock> m_begin;
};


#endif
