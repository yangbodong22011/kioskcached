/*************************************************************************
	> File Name: Item.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Wed 15 Feb 2017 11:44:26 PM CST
 ************************************************************************/

#include"Item.h"
#include<iostream>
#include<unordered_set>
#include<string.h>
#include<stdio.h>
#include<assert.h>

Item::Item(std::string keyArg,
           uint32_t flagsArg,
           int exptimeArg,
           int valuelen,
           uint64_t casArg)
    :keylen_(keyArg.size()),
    flags_(flagsArg),
    rel_exptime_(exptimeArg),
    valuelen_(valuelen),
    receivedBytes_(0),
    cas_(casArg),
    hash_(std::hash<std::string>{}(keyArg)),
    data_(static_cast<char*>(malloc(totalLen())))
    {
        assert(valuelen_ >= 2);
        assert(receivedBytes_ < totalLen());
        append(keyArg.c_str(),keylen_);
    }

void Item::append(const char* data,size_t len) 
{
    assert(len <= neededBytes());
    memcpy(data_ + receivedBytes_,data,len);
    receivedBytes_ += static_cast<int>(len);
    assert(receivedBytes_ <= totalLen());
}

void Item::resetKey(std::string k)
{
    assert(k.size() <= 250);
    keylen_ = k.size();
    receivedBytes_ = 0;
    append(k.c_str(),k.size());
    hash_ = std::hash<std::string>{}(k);
}
