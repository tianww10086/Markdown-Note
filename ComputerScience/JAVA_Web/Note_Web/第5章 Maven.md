## 1.1 Maven

​	**Maven是管理和构建Java项目的工具**，是`apache`旗下的一个开源项目。

​	Maven的主要作用：依赖管理（jar包）、项目构建、统一的项目结构

![image-20260228175605162](../IMG/image-20260228175605162.png)

#### 1.1.1 依赖管理

​	在之前，开发Java项目时，如果想要使用一些第三方的jar包，需要到对应的官网上下载，再到项目目录中创建一个lib文件夹，然后将jar包放在将lib文件夹内，才能使用

​	现在，使用Maven，可以很方便的导入jar包。比如如下：

```xml
<dependency>
	<groupId>commons-io</groupId>
    <artifactId>commons-io</artifactId>
    <version>2.11.0</version>
</dependency>
```

​	通过一个**POM.xml（Project Object Model 项目对象模型）文件**，声明这几段标签。Maven可以自动下载jar包，极大的优化了开发者的效率





#### 1.1.2 标准化项目构建

​	Maven提供了一些指令来帮助开发者进行编译、测试、打包以及发布等操作。在IDEA中打开Maven面板就可以看到。

<img src="../IMG/image-20260228175012711.png" alt="image-20260228175012711" style="zoom:50%;" />

- clean: 清理前一次构建生成的文件。
- validate: 验证项目是否正确且所有必要信息可用。
- compile: 编译项目的源代码。
- test: 使用单元测试框架测试编译后的代码，测试不需要打包或部署。
- package: 将编译后的代码打包成可分发的格式，如JAR、WAR。
- verify: 对集成测试的结果进行检查，以确保质量达标。
- install: 将包安装到本地仓库，供本地其他项目使用。
- site: 生成项目站点文档。
- deploy: 在构建环境中，将最终的包复制到远程仓库，供其他开发人员或项目共享。





#### 1.1.3 统一的项目结构

​	只要使用Maven构建的项目，目录结构都是统一的，可以跨平台使用

![image-20260301184417534](../IMG/image-20260301184417534.png)





#### 1.1.4 Maven本地仓库的配置

1. 第一步，从官网中下载`bin`版本。
2. 再Maven文件夹中创建`mvn_repo`作为本地仓库文件夹。
3. 复制`mvn_repo`文件夹路径
4. 打开conf文件夹，修改`settings.xml`文件夹
5. 找到` <localRepository>/path/to/local/repo</localRepository>`
6. 将mvn_repo文件夹路径复制到该标签中，并移出注释。如下

![image-20260228182703534](../IMG/image-20260228182703534.png)

​	

#### 1.1.5 配置阿里云的Maven私服

​	由于中央仓库在国外，有些jar包不一定能下载成功，还很缓慢，所以可以使用国内的私服。

​	同样的修改`settings.xml`文件，找到`<mirrors>`标签，将阿里云的私服标签复制进去

```xml
<mirror>
  <id>aliyunmaven</id>
  <mirrorOf>*</mirrorOf>
  <name>阿里云公共仓库</name>
  <url>https://maven.aliyun.com/repository/public</url>
</mirror>
```

​	要想在任意目录下使用Maven，就需要配置环境变量







## 1.2 POM文件解析

​	POM.xml是Maven的核心

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    
    ......
    
</project>
```

1. <?xml version="1.0"?> - 声明使用XML 1.0标准                                                                                                                                             
2. encoding="UTF-8" - 指定文件使用UTF-8字符编码     	
3. `<project></project`是POM文件的根元素，其他所有标签都写在这个标签里面
4. **`xmlns` 等**：声明 POM 的命名空间和 XML Schema，确保 Maven 能正确解析文件。

```xml

	<modelVersion>4.0.0</modelVersion>

    <groupId>org.example</groupId>
    <artifactId>z.ai</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>
```

​	上面这些标签用来描述当前项目的信息

- **`<modelVersion>`**：POM 模型的版本，Maven 2 及以后固定为 `4.0.0`。
- **`<groupId>`**：项目所属组织的唯一标识，通常采用反向域名，如 `com.example`。
- **`<artifactId>`**：项目的唯一名称，对应构建产物的文件名（如 `my-app.jar`）。
- **`<version>`**：项目版本号，`SNAPSHOT` 表示开发中的不稳定版本。`RELEASE`表示功能趋于稳定，可以发行的版本
- **`<packaging>`**：项目的打包方式，常见值：`jar`（默认）、`war`、`pom`（父模块）等。

```xml
<properties>
    <maven.compiler.source>11</maven.compiler.source>
    <maven.compiler.target>11</maven.compiler.target>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
</properties>
```

​	这些也是用来描述当前项目的信息

- **`<maven.complier.source>`** ：基于JDK哪个版本开发
- **`<maven.complier.target>`**：最终运行的时候基于哪个版本运行
- **` <project.build.sourceEncoding>`** ：当前项目的字符集

​	上面介绍的这些标签，都属于`Project Object Model`**POM**的范围。



#### 1.2.1 Dependency （依赖管理模型）

​	依赖信息统一写进`<dependencies>`标签中，用来描述当前项目的依赖信息。

```xml
<dependencies>
		
        <dependency>
            <groupId>commons-io</groupId>
            <artifactId>commons-io</artifactId>
            <version>2.14.0</version>
        </dependency>
    
          <!-- 3. 日志实现 -->
        <dependency>
            <groupId>org.slf4j</groupId>
            <artifactId>slf4j-simple</artifactId>
            <version>2.0.17</version>
            <scope>runtime</scope>
        </dependency>

</dependencies>
```

​	一个依赖管理模型可以写入多个依赖的信息。

​	依赖通过仓库进行下载。它首先会在本地仓库中寻找该jar包，如果本地仓库没有，就会到中央仓库中下载。 

​	



## 1.3 依赖管理

​	依赖：指当前项目运行所需要的`jar`包，一个项目中可以引入多个依赖。

​	配置：

1. 在`pom.xml`中编写`<dependencies>`标签
2. 在`<dependencies>` 标签中，使用`<dependency>`引入坐标
3. 定义坐标的`gropId,artifactId,version`
4. 点击Maven刷新

​	例如：

```xml
     <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-context</artifactId>
            <version>6.2.14</version>
        </dependency>
```

​	如果导入的依赖还需要其他的依赖运行，则会自动导入其他依赖，这叫做**依赖传递**

<img src="../IMG/image-20260302185129703.png" alt="image-20260302185129703" style="zoom:50%;" />

#### 1.3.1 排除依赖

​	如果不想要某个依赖，可以使用`<exclusion>` 来指定要排除哪个依赖。比如

```xml
<dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-context</artifactId>
            <version>6.2.14</version>
            <scope>compile</scope>

            <exclusions>
                <exclusion>
                    <groupId>io.micrometer</groupId>
                    <artifactId>micrometer-commons</artifactId>
                </exclusion>
            </exclusions>
        </dependency>
```

​	被排除的依赖不需要指定版本





## 1.4 Maven生命周期

​	Maven中有3套互相独立的生命周期：

- clean :清理工作
- default : 核心工作，如，编译、测试、打包、按照、部署等。
- site：生成报告、发布站点。

​	在同一套生命周期中，运行后面的阶段时，前面的阶段都会运行。





## 1.5 单元测试

​	测试：是一种用来促进鉴定软件的正确性、完整性、安全性和质量的过程。

​	阶段划分：单元测试、集成测试、系统测试、验收测试。

​	<img src="../IMG/image-20260302190519277.png" alt="image-20260302190519277" style="zoom:50%;" />

​	单元测试：就是针对最小的功能单元（方法），编写测试代码对其正确性进行测试

​	`JUnit` :  最流行的JAVA测试框架，提供了一些功能，方便程序进行单元测试。

```java
public class UserService {

    /**
     * 给定一个身份证号, 计算出该用户的年龄
     * @param idCard 身份证号
     */
    public Integer getAge(String idCard){
        if (idCard == null || idCard.length() != 18) {
            throw new IllegalArgumentException("无效的身份证号码");
        }
        String birthday = idCard.substring(6, 14);
        LocalDate parse = LocalDate.parse(birthday, DateTimeFormatter.ofPattern("yyyyMMdd"));
        return Period.between(parse, LocalDate.now()).getYears();
    }

    /**
     * 给定一个身份证号, 计算出该用户的性别
     * @param idCard 身份证号
     */
    public String getGender(String idCard){
        if (idCard == null || idCard.length() != 18) {
            throw new IllegalArgumentException("无效的身份证号码");
        }
        return Integer.parseInt(idCard.substring(16,17)) % 2 == 1 ? "男" : "女";
    }

}
```

​	下面编写单元测试代码对这两个方法进行测试。

​	第一步：导入依赖

```xml
        <dependency>
            <groupId>org.junit.jupiter</groupId>
            <artifactId>junit-jupiter</artifactId>
            <version>5.9.1</version>
        </dependency>
```

​	第二步：在test/java目录下编写测试类，并编写对应的测试方法，并在方法上声明@Test注解。一般约定，测试类的名字是要测试类的名字+Test

​	第三步：编写测试方法。测试方法的名字是对应方法的前面+test。方法声明必须@Test，方法被public修饰，返回值为void

```java
public class UserServiceTest {
        @Test
        public void TestGetAge(){
                Integer age = new UserService().getAge("522225200312119034");
                System.out.println(age);
        }

        @Test
        public void TestGetGender(){
                String gender = new UserService().getGender("522225200312119034");
                System.out.println(gender);
        }
}

```

​	第四步：点击运行。或点击Maven中的test

![image-20260302192257831](../IMG/image-20260302192257831.png)



​	 

#### 1.5.1 断言

​	1. 普通断言

| 方法                                      | 说明                                               |
| :---------------------------------------- | :------------------------------------------------- |
| `assertEquals(expected, actual)`          | 判断两个值是否相等（对对象调用 `equals()` 比较）。 |
| `assertEquals(expected, actual, message)` | 可自定义失败信息。                                 |
| `assertNotEquals(unexpected, actual)`     | 判断两个值不相等。                                 |
| `assertSame(expected, actual)`            | 判断两个对象引用指向同一个对象（`==`）。           |
| `assertNotSame(unexpected, actual)`       | 判断两个对象引用不同。                             |
| `assertTrue(condition)`                   | 判断条件为 `true`。                                |
| `assertFalse(condition)`                  | 判断条件为 `false`。                               |
| `assertNull(object)`                      | 判断对象为 `null`。                                |
| `assertNotNull(object)`                   | 判断对象不为 `null`。                              |
| `fail(message)`                           | 直接使测试失败，常用于标记未完成的测试或异常分支。 |

**示例：**

java

```
@Test
void testAssertions() {
    assertEquals(5, calculator.add(2, 3), "加法结果应为5");
    assertTrue(list.isEmpty(), "列表应该为空");
    assertNotNull(user, "用户对象不应为null");
}
```



------

2. 数组断言

| 方法                                            | 说明                                           |
| :---------------------------------------------- | :--------------------------------------------- |
| `assertArrayEquals(expectedArray, actualArray)` | 判断两个数组内容是否相等（依次比较每个元素）。 |

**示例：**

java

```
@Test
void testArray() {
    int[] expected = {1, 2, 3};
    int[] actual = new int[]{1, 2, 3};
    assertArrayEquals(expected, actual);
}
```



------

3. 异常断言

| 方法                                     | 说明                                                         |
| :--------------------------------------- | :----------------------------------------------------------- |
| `assertThrows(expectedType, executable)` | 执行代码块，预期抛出指定类型的异常，返回异常对象供进一步断言。 |
| `assertDoesNotThrow(executable)`         | 执行代码块，预期不抛出任何异常。                             |

**示例：**

java

```
@Test
void testException() {
    Exception exception = assertThrows(IllegalArgumentException.class, 
        () -> userService.register(null));
    assertEquals("用户信息不能为空", exception.getMessage());
}

@Test
void testNoException() {
    assertDoesNotThrow(() -> userService.register(validUser));
}
```



------

4. 超时断言

| 方法                                              | 说明                                                         |
| :------------------------------------------------ | :----------------------------------------------------------- |
| `assertTimeout(duration, executable)`             | 在指定时间内执行完成，超时则失败（执行完成后才判断）。       |
| `assertTimeoutPreemptively(duration, executable)` | 在指定时间内执行完成，超时则立即中断执行并失败（在单独线程中运行）。 |

**示例：**

java

```
@Test
void testTimeout() {
    assertTimeout(Duration.ofMillis(100), 
        () -> Thread.sleep(50)); // 通过
    assertTimeoutPreemptively(Duration.ofMillis(100), 
        () -> Thread.sleep(200)); // 失败，超时立即中断
}
```







#### 1.5.2 注解

1. 核心测试注解

| 注解                 | 说明                                                         |
| :------------------- | :----------------------------------------------------------- |
| `@Test`              | 标记一个方法为测试方法。                                     |
| `@ParameterizedTest` | 标记一个方法为参数化测试，需要配合参数来源注解（如 `@ValueSource`）使用。 |
| `@RepeatedTest`      | 标记一个方法为重复测试，可指定重复次数。                     |
| `@TestFactory`       | 标记一个方法为动态测试工厂，返回 `DynamicNode` 实例（如 `Stream<DynamicTest>`）。 |
| `@TestTemplate`      | 用于定义测试模板，通常与 `@TestTarget` 等扩展结合使用。      |

------

2. 生命周期注解

用于在测试执行前后执行特定代码。

| 注解          | 说明                                                  |
| :------------ | :---------------------------------------------------- |
| `@BeforeEach` | 在每个测试方法执行前运行。                            |
| `@AfterEach`  | 在每个测试方法执行后运行。                            |
| `@BeforeAll`  | 在所有测试方法执行前运行一次（方法必须是 `static`）。 |
| `@AfterAll`   | 在所有测试方法执行后运行一次（方法必须是 `static`）。 |

------

3. 显示名称注解

控制测试类/方法在报告中的显示名称。

| 注解                     | 说明                                                         |
| :----------------------- | :----------------------------------------------------------- |
| `@DisplayName`           | 为测试类或方法声明一个自定义显示名称（支持空格、中文、表情等）。 |
| `@DisplayNameGeneration` | 使用 `DisplayNameGenerator` 生成显示名称，例如 `ReplaceUnderscores` 可将下划线替换为空格。 |





## 1.6 依赖范围

​	依赖的jar包，默认情况下，可以在任何地方使用。可以通过`<scope>...</scope>`设置起作用范围。

​	作用范围：

- 主程序范围有效（main文件夹范围内）
- 测试程序范围有效（test文件夹范围内）
- 是否参与打包运行（package指令范围内）

如:

```xml
        <dependency>
            <groupId>org.junit.jupiter</groupId>
            <artifactId>junit-jupiter</artifactId>
            <version>5.9.1</version>
            <scope>test</scope>
        </dependency>
```

​	使该jar包只在test文件夹内有效

<img src="../IMG/image-20260303194131393.png" alt="image-20260303194131393" style="zoom:50%;" />