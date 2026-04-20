## 8.1 什么是Mybatis

​	`MyBatis`是一款优秀的持久层框架，用于简化JDBC开发。**持久层：负责将数据保存到数据库的那一层代码**。JavaEE三层架构：表现层（页面）、业务层（逻辑）、**持久层**（数据存储）。

​	JDBC的缺点比较明显的就是**硬编码**，像连接参数、SQL语句，都是使用字符串形式保存在变量中的。那如果后续想要修改他们，就需要重新编译、打包。比较麻烦。MyBatis可以很好的简化这些操作。

​	



## 8.2 快速入门

​	同样我们使用`Maven`坐标导入第三方jar包，下面是`Mybatis`对应的坐标

```java
  <!-- mybatis依赖 -->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.6</version>
        </dependency>
```

 	每个基于`MyBatis`的应用都是以一个`SqlSessionFactory`的实例为核心。而该实例通过`SqlSessionFactoryBuilder`获得，`SqlSessionFactoryBuilder`则是通过**XML配置文件**或者是**一个预先配置的`Configuration`实例**来构建出`SqlSessionFactory`实例。

​	从`XML`文件中构建出`SqlSessionFactory`实例非常简单，可以使用类路径下的资源文件配置，也可以使用输入流实例配置。我们首先介绍`XML`配置文件中对`Mybatis`系统的核心设置：比如**获取数据库连接实例的数据源（DataSource），以及决定事务作用域和控制方式的事务管理器**

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
  PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
  <environments default="development">
    <environment id="development">
      <transactionManager type="JDBC"/>
      <dataSource type="POOLED">
        <property name="driver" value="${driver}"/>
        <property name="url" value="${url}"/>
        <property name="username" value="${username}"/>
        <property name="password" value="${password}"/>
      </dataSource>
    </environment>
  </environments>
  <mappers>
    <mapper resource="org/mybatis/example/BlogMapper.xml"/>
  </mappers>
</configuration>
```

​	${}里面是需要你填入的对应信息。比如`driver`是数据库连接的驱动，`url`是数据库的定位地址。一般来说，该`XML`文件的名字是：`mybatis-config.xml`。mappers 元素则包含了一组映射器（mapper），这些映射器的 XML 映射文件包含了 SQL 代码和映射定义信息

​	除此之外，我们还需要创建一个xml文件，该文件与执行SQL语句息息相关，文件名一般为：`表名+Mapper`。比如对Student表操作就取名`StudentMapper.xml`。下面是简单示例

```java
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<!-- namespace :命名空间  -->
<mapper namespace="test">
    <select id="selectAll" resultType="com.tww.pojo.Student">
        select * from student;
    </select>
</mapper>
```

​	下面是每个标签对应的含义

| 标签/属性                                  | 含义                                                         |
| :----------------------------------------- | :----------------------------------------------------------- |
| `<?xml version="1.0" encoding="UTF-8" ?>`  | XML 声明，定义版本和字符编码，非 MyBatis 特有。              |
| `<!DOCTYPE mapper ...>`                    | 文档类型声明，引用 MyBatis 的 DTD 文件，用于校验 XML 语法正确性。 |
| `<mapper namespace="...">`                 | **根标签**，定义一个 SQL 映射块。`namespace` 通常设为 Mapper 接口的全限定名（如 `com.tww.mapper.StudentMapper`），用于绑定接口和 XML，实现动态代理。这里示例为 `org.mybatis.example.test`。 |
| `<select id="selectAll" resultType="...">` | 定义**查询语句**。`id` 在该命名空间下唯一，对应 Mapper 接口中的方法名（如 `selectAll`）。`resultType` 指定结果集每行数据映射到的 Java 类型（这里是 `com.tww.pojo.Student`），MyBatis 自动将列名与对象属性对齐。 |
| `select * from student;`                   | 标签体中的 **SQL 语句**，实际执行的查询逻辑。                |
| `</select>`                                | 结束 select 标签。                                           |
| `</mapper>`                                | 结束 mapper 标签。                                           |

​	从XML中构建`SeqSessionFactory`：

```java
        // 加载mybatis的核心配置文件，获取SqlSessionFactory
        String resource = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resource);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
```

​	获取到`SqlSessionFactory`后，就可以从该类中获取到`SqlSession`的实例了。**SqlSession**提供了在数据库执行SQL命令所需的所有方法`openSession()`，可以通过`SqlSession`实例来直接执行已映射的SQL语句。如：

```java
     SqlSession session = sqlSessionFactory.openSession();
        List<Student> arrayList  = session.selectList("test.selectAll");
        System.out.println(arrayList);
        session.close();
```

​	`selectList`方法是针对返回多条记录的SQL语句方法，它返回一个`List<E>`集合，E的类型通过映射文件中`resultType`指定。在这里，它指定为`com.tww.pojo.`包下的`Student`类。参数需指定该语句所在的`namespace`。和定义查询语句标签中指定的id，在这里表现为：`test.selectAll`



## 8.3 Mapper代理开发

​	在上面的调用中，我们通过`命名空间.id`去执行对应的SQL语句，还需要对SQL语句返回的结果做适应。现在，有了更快捷的方法，让我们像调用方法一样调用执行SQL语句：

```java
        StudentMapper mapper = session.getMapper(StudentMapper.class);
       List<Student> list = mapper.selectAll();
```

​	不过，在那之前，必须做一些准备工作，

1. 定义与SQL映射文件同名的`Mapper`接口（在这里SQL映射文件是StudentMapper.xml），并且让`Mapper`接口和SQL映射文件编译后放置在同一目录，具体做法是，现找到Mapper接口编译后在哪个文件夹下。在到`resource`创建同样的包结构，注意，`resource`李创建包，分层需要使用\符号，然后将SQL映射放到该包下，编译后。Mapper接口的class文件就与SQL映射在同一文件夹下了，才会生效。目录结构大概如下图：

   ![image-20260411170035076](../IMG/image-20260411170035076.png)

​	

2. 设置SQL映射文件的`namespace`属性为Mapper接口全限定名（是指包名+类名的完整名称，用于唯一标识一个类，避免同名类的冲突）

   3. 在`Mapper`接口中定义方法， 方法名就是SQL映射文件的sql语句中的id，并保持参数类型和返回值类型一直。

      在这里，我们需要编写如下方法：

      ```java
      public interface StudentMapper {
          List<Student> selectAll();
      }
      ```

      为什么是List，因为`selectAll`id对应的SQL语句，返回的是一个多条记录，明显需要一个集合来存储。

4. 编码
   1. 通过SqlSession的getMapper方法获取Mapper接口的代理对象
   2. 调用对应方法完成sql的执行。

​	另外，如果SQL映射文件与`Mapper`接口同名，就比如我们上面的示例，那么可以使用包扫描的方式加载SQL映射，在之前，我们是通过：

```xml
      <!--加载Sql映射文件-->
        <mapper resource="com/tww/mapper/StudentMapper.xml"/>
```

​	的方式来加载SQL映射，如果有多个SQL映射，就需要一条一条标签去写。包扫描则可以更快捷的，一次性加载包下面所有的映射：

```xml
 <!-- Mapper代理方式 ：包扫描 -->
        <package name="com.tww.mapper"/>
```



## 8.4 MyBatis核心配置文件详解

​	什么是`MyBatis`核心配置文件，其实就是`mybatis-config.xml`文件，可以通过配置里面的各项属性去影响MyBatis的行为

配置文档的顶层结构如下：

- configuration（配置）
  - [properties（属性）](https://mybatis.net.cn/configuration.html#properties)
  - [settings（设置）](https://mybatis.net.cn/configuration.html#settings)
  - [typeAliases（类型别名）](https://mybatis.net.cn/configuration.html#typeAliases)
  - [typeHandlers（类型处理器）](https://mybatis.net.cn/configuration.html#typeHandlers)
  - [objectFactory（对象工厂）](https://mybatis.net.cn/configuration.html#objectFactory)
  - [plugins（插件）](https://mybatis.net.cn/configuration.html#plugins)
  - environments（环境配置）
    - environment（环境变量）
      - transactionManager（事务管理器）
      - dataSource（数据源）
  - [databaseIdProvider（数据库厂商标识）](https://mybatis.net.cn/configuration.html#databaseIdProvider)
  - [mappers（映射器）](https://mybatis.net.cn/configuration.html#mappers)

​	在上面两节，简单介绍了`dataSource`和`mappers`。`dataSource`用来设置数据库连接的各项属性，而`mappers`映射器用来加载各类SQL映射文件。

​	



#### 8.4.1 enviroments

​	顾名思义，是用来配置数据库环境的标签，而且可以配置多个数据库环境。如：

```xml
<enviroments>
    <!--数据库1 -->
	<enviroment>
    ...
    </enviroment>
    
    <!-- 数据库2 -->
    <enviroment>
        ....
    </enviroment>
</enviroments>
```

​	不过，尽管可以配置多个环境，但每个`SqlSessionFactory`实例只能选择一种环境。所以，如果你想要连接两个数据库，就要创建两个`SqlSessionFactory`实例，每个数据库对应一个

​	为了指定创建哪种环境，只要将它的可选参数`id`传递给`SqlSessionFactoryBuilder`即可。如果忽略了`environment`这项参数，则会加载默认环境，默认环境由<environments default="development"\> 里的default选项指定。

​	**方法重载1**：

```xml
        // 加载mybatis的核心配置文件，获取SqlSessionFactory
String resource = "mybatis-config.xml";
InputStream reader = Resources.getResourceAsStream(resource);
String environment = "development"; //数据库环境的id
SqlSessionFactory factory = new SqlSessionFactoryBuilder().build(reader, environment);
```

​	`reader`就是从`mybatis-config.xml`文件中读取的文件流读取器，读取文件中的配置。而environment则是配置文件中的id，以便区分加载的是哪个数据库。

​	

​	**方法重载2**：

```xml
SqlSessionFactory factory = new SqlSessionFactoryBuilder().build(reader, environment, properties);
```

​	区别在`properties`，我们知道properties文件是Java里很常见的配置文件，用来提供各项参数，文件的内容通常以键值对出现：key=value。在这里，它主要负责给`environment`中的数据源里的占位符提供数据，例如有如下数据源：

```xml
  <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="${driver}"/>
                <property name="url" value="${url}"/>
                <property name="username" value="${username}"/>
                <property name="password" value="${password}"/>
            </dataSource>
        </environment>
```

​	占位符指的是`${}`里面的变量名，对应`properties`文件中key，而具体的值是`properties`的与key对应的`value`；我们假设已经有了一个`properties`文件。现在用Java代码来加载环境并运行代码。

```java
       // 加载mybatis的核心配置文件，获取SqlSessionFactory
        String resource = "mybatis-config.xml"; //配置文件
        InputStream inputStream = Resources.getResourceAsStream(resource); //加载配置文件
        Properties properties = new Properties(); //创建properties类
		//设置输入流
        InputStream proStream = Thread.currentThread().getContextClassLoader().getResourceAsStream("MysqlDataBaseSource.properties");	
        //通过输入流加载该类
		properties.load(proStream);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream,"development",properties);
```

​	除了这个方法可以指定数据源的参数，还可以通过配置文件指定数据源

​	

​	**方法二**：

​	通过配置文件`<properties resource = "...">` 或`<properties url = "...">`加载的属性

​	第一种方式希望你通过**类路径**的方式来加载properties文件：

```xml
<properties resource="config/db.properties" />
```

​	第二张希望你通过url来加载`properties`文件：

```xml
<properties url="file:///G:/myconfig/db.properties" />
```

​	注意类路径和url不等同，他们是互斥的，只能使用其中一个。

​	**方法三**：配置文件`<properties>`子标签`<property>`中直接写死的属性。

​	当你使用build传入了`Properties`对象，而且配置文件中也有`<properties>`时，build传入的对象优先级更高。

#### 8.4.2 properties

​	 