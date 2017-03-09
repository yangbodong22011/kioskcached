# kioskCached


        一款内存缓存型数据库，实现了基础的增、删、改、查功能。由于Memcached是多线程网络模型，锁的使用势必会降低性能。
        本项目旨在使用单线程模型提供高性能的GET/SET方法。项目采用C/C++开发，参考Redis网络架构设计自行封装AeEvent
        事件处理框架，单线程IO多路复用模型避免了锁的争用，保证了操作的原子性。使用C++11 unordered_set管理内存数据
        结构。采用Memcached客户端协议作为标准协议。


## 一、对比Memcached和Redis

### 1：测试环境： 

> OS ： RedHat 7 
Kernel : Linux version 3.10.0-514.el7.x86_64   
>
CPU : Intel(R) Core(TM) i5 CPU M 520  @ 2.40GHz  
>
Mem : 8G
>
//备注：除了测试三个数据库的QPS，我还使用Google的  [gperftools](http://www.cnblogs.com/caosiyang/archive/2013/01/25/2876244.html)  工具我的项目做了`CPU PROFILER`，找出了代码中占用CPU最多的函数，并考虑优化它。

### 2 ：测试条件：
- 100000条 key-value 数据，每条大概100字节大小


### 3： Memcached 测试结果

- set 性能：22891.8 QPS

![](/image/memcached_set.png)

- get 性能：25262.8 QPS

![](/image/memcached_get.png)

### 4： Redis 测试结果

- set 性能：30156.82 QPS

![](/image/redis_set.png)

- get 性能：31007.75 QPS

![](/image/redis_get.png)


### 5： Kioskcached 测试结果


### （1）当value的值为**100字节**时 ： QPS  = 316275

![这里写图片描述](http://img.blog.csdn.net/20170309085017711)

使用`gperftools`找出使用CPU前几位的函数为：

![这里写图片描述](http://img.blog.csdn.net/20170309004137410)

```
$ cat output.txt 

Total: 259 samples
      34  13.1%  13.1%       56  21.6% std::_Hashtable::_M_find_before_node
      21   8.1%  21.2%       22   8.5% _int_malloc
      17   6.6%  27.8%       23   8.9% std::_Hashtable::_M_rehash_aux

...... 

```

输出结果说明（按照列数往下）：




| 序号 | 说明 |
| --- | --- |
|1| 分析样本数量（不包含其他函数调用）|
|2|分析样本百分比（不包含其他函数调用）| 
|3| 目前为止的分析样本百分比（不包含其他函数调用）|
|4|分析样本数量（包含其他函数调用）|
|5|分析样本百分比（包含其他函数调用）|
|6|函数名|    

  
 

### （2）当value的值为**1000字节**时 ： QPS  = 203203

![这里写图片描述](http://img.blog.csdn.net/20170309085142451)

使用`gperftools`找出使用CPU前几位的函数为：

```
Total: 426 samples
      78  18.3%  18.3%       78  18.3% __read_nocancel
      64  15.0%  33.3%       70  16.4% _int_malloc
      28   6.6%  39.9%       57  13.4% std::_Hashtable::_M_find_before_node

......
可以发现与100字节相比较，此时read系统调用占用CPU已经成为了第一。
```


### （3）当value的值为10000字节时



![这里写图片描述](http://img.blog.csdn.net/20170309085237043)  



使用`gperftools`找出使用CPU前几位的函数为：

```
Total: 521 samples
     102  19.6%  19.6%      102  19.6% __read_nocancel
      79  15.2%  34.7%       83  15.9% _int_malloc
      42   8.1%  42.8%       42   8.1% __GI_epoll_wait
      29   5.6%  48.4%       52  10.0% std::_Hashtable::_M_find_before_node
      
malloc 还是我们的难题和瓶颈。
......  剩余的省略

```



### （4）： 总结 

通过上面的测试，可以发现下面这几个函数是主要的CPU性能瓶颈

```
_int_malloc
std::_Hashtable::_M_find_before_node
std::_Hashtable::_M_rehash_aux
__read_nocancel
```

这些都消耗非常多的CPU，要是优化的话先从它们入手，我自己可以处理的是`malloc` 和 `std::_Hashtable::_M_find_before_node`。


# 二、改进方法

- 使用tcmalloc等第三方性能优于glibc ptmalloc的内存分配器。[正在完成]
- 重新找寻Hash函数，做适配替代目前的Hash函数。[未完成]


