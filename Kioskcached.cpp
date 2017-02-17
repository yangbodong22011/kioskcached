/*************************************************************************
	> File Name: Kioskcached.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 16 Feb 2017 11:43:35 PM CST
 ************************************************************************/

#include<iostream>
#include"Kioskcached.h"
#include<assert.h>

Kioskcached::~Kioskcached()
{
}

bool Kioskcached::storeItem(const ItemPtr& item,Item::UpdatePolicy policy,bool *exists)
{
    ItemMap::const_iterator it = items.find(item);
    *exists = it != items.end();
    if(policy == Item::kSet) {
        if(*exists) {
            items.erase(it);
        }
        items.insert(item);
    }else {
        if(policy == Item::kAdd) {
            if(*exists) {
                return false;
            }else {
                items.insert(item);
            }
        }else if(policy == Item::kReplace) {
            if(*exists) {
                items.erase(it);
                items.insert(item);
            }else {
                return false;
            }
        }else {
            assert(false);
        }
    }
    return true;
}

ConstItemPtr Kioskcached::getItem(const ConstItemPtr& key) const
{
    ItemMap::const_iterator it = items.find(key);
    return it != items.end() ? *it : ConstItemPtr();
}

bool Kioskcached::deleteItem(const ConstItemPtr& key) 
{
    return items.erase(key) == 1;
}
