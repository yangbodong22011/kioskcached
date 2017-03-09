/*************************************************************************
	> File Name: Kioskcached.cpp
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 16 Feb 2017 11:43:35 PM CST
 ************************************************************************/

#include<iostream>
#include"Kioskcached.h"
#include<assert.h>

/*Kioskcached::~Kioskcached()
{
    std::cout << "hello " << std::endl;
}*/

int Kioskcached::storeItem(const ItemPtr& item,Item::UpdatePolicy policy,int exists)
{

    items.insert(item);
    /*ItemMap::const_iterator it = items.find(item);
    *exists = it != items.end();
    if(policy == Item::kSet) {
        if(!exists) {
            items.erase(it);
        }
        items.insert(item);
    }else {
        if(policy == Item::kAdd) {
            if(!exists) {
                return 0;
            }else {
                items.insert(item);
            }
        }else if(policy == Item::kReplace) {
            if(exists) {
                items.erase(it);
                items.insert(item);
            }else {
                return 0;
            }
        }else {
        }
    }*/
    return 1;
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
