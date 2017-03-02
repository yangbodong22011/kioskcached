# kioskCached
    一款内存缓存型数据库，实现了基础的增、删、改、查功能。由于Memcached是多线程网络模型，锁的使用势必会降低性能。本项目旨在使用单线程模型提供高性能的GET/SET方法。项目采用C/C++开发，参考Redis网络架构设计自行封装AeEvent事件处理框架，单线程IO多路复用模型避免了锁的争用，保证了操作的原子性。使用C++11 unordered_set管理内存数据结构。采用Memcached客户端协议作为标准协议。


## 对比Memcached和Redis

### 1：测试环境： 
- RedHat 7  
- Intel(R) Core(TM) i5 CPU       M 520  @ 2.40GHz
- 8G 内存

###2 ：测试条件：
- 100000条 key-value 数据，每条大概1Kb大小


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

- set 性能：26422.9 QPS

![](/image/kiosk_set.png)

- get 性能：26224.9 QPS

![](/image/kiosk_get.png)



## 总结




|name | set (QPS)| get  （QPS）| 
|---|---|---|
|Memcached|22891.8|25262.8|
|redis|30156.8|31007.7|
|Kioskcached|26422.9|26224.9|
