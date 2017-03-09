/*************************************************************************
	> File Name: Kioskcached.h
	> Author: YangBodong
	> Mail: ybd@xiyoulinux.org
	> Created Time: Thu 16 Feb 2017 11:18:14 PM CST
 ************************************************************************/

#ifndef _KIOSKCACHED_H
#define _KIOSKCACHED_H

#include"Item.h"
#include<unordered_set>


class Kioskcached {

public:
    Kioskcached()=default;
    
    int storeItem(const ItemPtr& item,Item::UpdatePolicy policy,int exists);
    ConstItemPtr getItem(const ConstItemPtr& key) const;
    bool deleteItem(const ConstItemPtr& key);

    struct Hash {
        size_t operator()(const ConstItemPtr& x) const {
            return x->hash();
        }
    };

    struct Equal {
        bool operator()(const ConstItemPtr& x,const ConstItemPtr& y) const {
            return x->key() == y->key();
        }
    };
    
    typedef std::unordered_set<ConstItemPtr,Hash,Equal> ItemMap;
    ItemMap items;

};

#endif
