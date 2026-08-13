## 1 Redis简介

​	`Redis`是一个基于内存的`key-value`结构高性能数据库。

​	

### 1.1 Redis配置

​	reids配置在`reids-windows.config`文件中配置，也可以通过命令`CONFIG`查看或设置配置

​	下面是启动`Redis`服务的命令

```cmd
redis-server.exe  redis.windows.conf
```

​	如果不指定配置，将按照默认配置运行

​	配置项`requirepass`来设置密码，设置密码之后，`redis-cli.exe`程序的相关操作就需要密码，同下面的连接指定密码

```cmd
redis-cli.exe -h localhost -p 6379  -a 123456
```

​	`-a` ：密码

​	本机设置的密码为123456

​	



### 1.2 Redis数据类型

​	`Redis`存储的是`key-value`结构的数据类型，其中`key`是字符串类型，`value`有五种常用的数据类型：

- 字符串 `String` ：string是redis最基本的类型，你可以理解成与Memcached一模一样的类型，一个key对应一个value。

- 哈希 `hash` ：（类似于Java中的HashMap的结构 ）

- 列表`list` ：Redis 列表是简单的字符串列表，按照插入顺序排序。你可以添加一个元素导列表的头部（左边）或者尾部（右边）。

- 集合`set` ：是string类型的无序集合，通过哈希表实现，添加，删除，查找的时间复杂度都是O(1)

- 有序集合 `sorted set/zset`  ： 

  Redis zset 和 set 一样也是string类型元素的集合,且不允许重复的成员。

  不同的是每个元素都会关联一个double类型的分数。redis正是通过分数来为集合中的成员进行从小到大的排序。







## 2 Redis命令

​	执行`Redis`命令首先需要启动`reids`客户端。

​	打开终端并输入命令`reids-cli`，会连接本地的redis服务。

```cmd
redis-cli.exe
```

​	如果需要连接到远程redis服务身上执行命令，同样也是使用`redis-cli`命令

​	语法：

```cmd
$ redis-cli -h host -p port -a password
```

​	实例：

```cmd
redis-cli.exe -h localhost -p 6379  -a 123456
```

​	连接到本地的6379端口，密码为123456



### 2.1 字符串操作命令

​	Redis字符串类型常用命令

- `SET Key value`   设置指定key的值

  ```
  SET w3ckey redis
  ```

  ​	key为w3ckey,值为reids

- `GET key` :   获取指定key 的值

- `SETEX key seconds value`    设置指定key的值，并将key的过期时间设为seconds秒

- `SETNX key value`      只有在key不存在时设置`key`的值



### 2.2 Hash操作命令

​	`Redish hash`是一个`String`类型的`field`和`value`的映射表，适合用于存储对象。常用命令如下：

- `HSET key field value`   将哈希表中key的字段field的值设置为value
- `HGET key field`   获取存储在哈希表中指定字段的值
- `HDEL key field`   删除存储在哈希表中的指定字段
- `HKEYS key`            获取哈希表中所有字段
- `HVALS key`            获取哈希表中所有值



### 2.3 List操作命令

​	`Redis`列表是简单的字符串列表，按照插入顺序排序，常用命令：

- LPUSH key value1 [value2]   将一个或多个值插入到列表头部
- LRANGE key start stop          获取列表指定范围内的元素
- RPOP key                                移除并获取列表最后一个元素
- RPUSH key value1 [value2]   将一个或多个值插入到列表尾部
- LLEN key                                 获取列表长度



### 2.4 Set操作命令

​	`Redis set`是string类型的无序集合，集合成员是唯一的，集合中不能出现重复的数据，常用命令：

- SADD key member1 [member2]   向集合添加一个或多个成员
- SMEMBERS key                                返回集合中的所有成员
- SCARD key                                        获取集合的成员数
- SINTER key1 [key2]                         返回给定所有集合的交集
- SUNION key1 [key2]                       返回所有给定集合的并集
- SREM key member1 [member2]  删除集合中一个或多个成员



### 2.5 sorted set/zset  操作命令

​	`Redis`有序集合是String类型元素的集合，且不允许有重复成员。每个元素都会关联一个`double`类型的分数。常用命令:

- ZADD key score1 member1 [score2 member2]          向有序集合添加一个或多个成员
- ZRANGE key start stop [WITHSCORES]                         通过索引区间返回有序集合中指定区间内的成员
- ZINCRBY key increment member                                  有序集合中对指定成员的分数加上增量increment
- ZREM key member [member]                                         移除有序集合中的一个或多个成员



### 2.6 通用命令

​	Redis的通用命令是不分数据类型的，都可以使用的命令：

- KEYS pattern   查找所有符合给定模式（pattern）的key
- EXISTS key       检查给定key是否存在
- TYPE key          返回key所存储的值的类型
- DEL key            当key存在时删除该Key





