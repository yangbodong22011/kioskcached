/*************************************************************************
	> File Name: Item.h
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Wed 15 Feb 2017 08:36:15 PM CST
 ************************************************************************/

#ifndef _ITEM_H
#define _ITEM_H

#include<memory>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>


class Item;
typedef std::shared_ptr<Item> ItemPtr;
typedef std::shared_ptr<const Item> ConstItemPtr;


class Item {

public: 

  enum UpdatePolicy
  {
    kInvalid,
    kSet,
    kAdd,
    kReplace,
  };
    static ItemPtr makeItem(std::string keyArg,
                            uint32_t flagsArg,
                            int exptimeArg,
                            int valuelen,
                            uint64_t casArg)
    {
        return std::make_shared<Item>(keyArg,flagsArg,exptimeArg,valuelen,casArg);
    }
    

    Item() = default;
    Item(std::string keyArg,
         uint32_t flagsArg,
         int exptimeArg,
         int valuelen,
         uint64_t casArg);
   
    ~Item() {
        free(data_);
    }

    std::string key() const {        //所有需要调用key的地方传递.size()方法.
        return std::string(data_);
    }
    
    uint32_t flags() const {
        return flags_;
    }
    
    int rel_exptime() const {
        return rel_exptime_;
    }
    
    const char* value() const {
        return data_+keylen_;
    }

    size_t valueLength() const {
        return valuelen_;
    }

    uint64_t cas() const {
        return cas_;
    }

    size_t hash() const {
        return hash_;
    }

    void setCas(uint64_t casArg) {
        cas_ = casArg;
    }
    
    size_t neededBytes() const {
        return totalLen() - receivedBytes_;
    }

    void append(const char* data,size_t len);

    bool endsWithCRLF() const {
        return receivedBytes_ == totalLen() 
        && data_[totalLen()-2] == '\r'
        && data_[totalLen()-1] == '\n';
    }

    void output() const {
        std::cout << "keylen_ : " << keylen_ << std::endl;
        std::cout << "flags : " << flags_ << std::endl;
        std::cout << "rel_exptime_ : " << rel_exptime_ << std::endl;
        std::cout << "valuelen_ : " << valuelen_ << std::endl;
        std::cout << "receivedBytes_ : " << receivedBytes_ << std::endl;
        std::cout << "cas_ : " << cas_ << std::endl;
        std::cout << "hash_ : " << hash_ << std::endl;
        std::cout << "data_ : " << data_ << std::endl;
    }

    void resetKey(std::string k);

private:
    int totalLen() const { return  keylen_ + valuelen_;}

    int            keylen_;
    const uint32_t flags_;
    const int      rel_exptime_;
    const int      valuelen_;
    int            receivedBytes_;
    uint64_t       cas_;
    size_t         hash_;
    char*          data_;
};

#endif
