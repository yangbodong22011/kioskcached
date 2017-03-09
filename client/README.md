# Kioskcached 性能测试工具


## 使用方法 

1:编译

```
$ gcc anet.c buffer.c protocol.c server_test.c -o client -std=c99

```

2:测试说明 

```
$ ./client [requests]  [valuelen]

eg: ./client  1000000  100
表示发起1000000个请求，每个的value为100字节

```

