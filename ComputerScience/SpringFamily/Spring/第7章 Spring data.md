## 7.1 Spring Data Redis

​	下面是在Java中使用Spring data redis的方式：

1.  导入Spring Data Redis 的坐标

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
```

2. 配置Redis数据源

```yaml
Spring:
  redis:
    port: 6379
    host: localhost
    password: 123456
    database: 0
```

3. 编写配置类，创建RedisTemplate对象

```java
@Configuration
public class RedisConfiguration {
    @Bean
    public RedisTemplate redisTemplate(RedisConnectionFactory redisConnectionFactory){
        RedisTemplate redisTemplate = new RedisTemplate<>();

        //设置redis的连接工厂对象
        redisTemplate.setConnectionFactory(redisConnectionFactory);

        //设置redis key 的序列化器
        redisTemplate.setKeySerializer(new StringRedisSerializer());

        return redisTemplate;
    }
}

```

4. 通过RedisTemplate对象操作Redis

```java
@SpringBootTest
public class SpringDataRedisTest {

    @Autowired
    @Qualifier("myRedisTemplate")
    RedisTemplate template;

    @Test
    public void testRedisTemplate(){
        if(template!=null){
            System.out.println("MyRedisTemplate "+template+"配置成功");
        }
       var valuesOperations=  template.opsForValue(); //获取字符串类型操作对象
        var hashOperations = template.opsForHash(); //获取哈希类型操作对象
        var ListOperations = template.opsForList();
        var setOperations = template.opsForSet();
        var zsetOperations =template.opsForZSet();
    }
}
```

​	



### 7.1.1 Templdate操作字符串类型

```java
    @Test
    public void testString(){
        //set get setex setnx
        var valuesOperations = template.opsForValue(); //获取字符串类型的操作对象

        // 设置键值对
        valuesOperations.set("city","北京");

        //获取键对应的值
        Object value = valuesOperations.get("city");
        System.out.println((String)value); //输出

        //设置键值对，以及过期时间 :120秒
        valuesOperations.set("code","1234",120, TimeUnit.SECONDS);
        System.out.println((String)valuesOperations.get("code"));

        //setnx :  setIfAbsent 只有在key不存在时才设置key的值 ,也能设置过期时间 ，由于上面已经设置过了
        //所以这里不会设置成功
        valuesOperations.setIfAbsent("city","贵州",120,TimeUnit.SECONDS);
        System.out.println((String)valuesOperations.get("city")); //输出
    }
```





### 7.1.2 操作Hash类型

```java
    @Test
    public void testHash(){
        var hashOperations = template.opsForHash();

        //hset
        hashOperations.put("Person","name","田韦韦");
        hashOperations.put("Person", "age",22);

        //hget
        String name = (String)hashOperations.get("Person","name");
        System.out.println(name);

        // hkeys 获取这个Hash的 键集(field)
        Set keys = hashOperations.keys("Person");
        System.out.println(keys);
        // hvalues 获取这个Hash的 value集
        List values = hashOperations.values("Person");
        System.out.println(values);

        hashOperations.delete("Person","age");
    }
```

