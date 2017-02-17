# kioskCached
    一款内存缓存型数据库，实现了基础的增、删、改、查功能。

## 模型
    采用Redis单线程、IO多路复用模型。单线程原子操作避免了锁的开销，使用c++11中unordered_set作为存储结构。
    
## 对比Memcached
