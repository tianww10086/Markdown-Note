## 5.1 Spring Boot介绍

​	Spring Boot帮助你创建可以运行的独立的、基于Spring的生产级应用程序。对Spring平台和第三方库采取了有主见的观点，这样就能以最少的麻烦开始工作。**大多数SpringBoot应用程序只需要很少的Spring配置**



#### 5.1.1 系统要求

​	Spring Boot 3.2.0-SNAPSHOT需要Java17版本，可以兼容到Java20.构建工具Maven需要3.6.3及其以上，支持`Servelet容器 Tomcat`10.0 ，以及`Servlet`版本5.0



## 5.2 代码结构

​	Spring Boot对代码的布局没有特殊的要求，但是，有一些最佳实践，比如启动类的位置



#### 5.2.1 “default”包

​	当一个类不包括`package`的声明时，它被认为是在“default package”中。 通常应该避免对于使用下面了注解的类在“default package”包中：

​	`@ComponentScan、@ConfigurationPropertiesScan、@EntityScan或者@SpringBootApplication`注解的应用程序。如果对于这些程序在“default”包中，会造成一个问题：**项目中所有的jar里面的所有的class都会被读取（扫描）**

​	这是因为，`@ComponentScan`的作用是扫描Bean，而向上面的注解，如`SpringBootApplication`都包含这个注解，而这个注解的默认扫描规则是：

​	**从当前类所在的包开始，向下递归扫描**。



#### 5.2.2 启动类的位置

​	通常建议你将启动类放在一个根`package`中，高于其他的类，`@SpringBootApplication`注解一般都是注解在启动类上。**它会默认扫描当前类下的所有子包**。例如，你的`@Entity`类只有定义在启动类下的子包下才能被扫描加载到。这样的好处也显而易见，`@SpringBootApplication`默认只会扫描加载你项目工程的组件。

> ​	如果你不想使用`@SpringBootApplication`，它所导入的`@EnableAutoConfiguration`和`@ComponentScan`注解定义了该行为，所以也可以使用这些来代替。

​	一个项目典型的布局如下：

```tex
com
 +- example
     +- myapplication
         +- MyApplication.java
         |
         +- customer
         |   +- Customer.java
         |   +- CustomerController.java
         |   +- CustomerService.java
         |   +- CustomerRepository.java
         |
         +- order
             +- Order.java
             +- OrderController.java
             +- OrderService.java
             +- OrderRepository.java
```

​	`MyApplication.java` 文件声明了 `main` 方法，以及标识了基本的 `@SpringBootApplication` 注解，如下所示。

```java
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class MyApplication {

    public static void main(String[] args) {
        SpringApplication.run(MyApplication.class, args);
    }

}
```





## 5.3 Spring Bean和依赖注入

​	在之前，我们有多种方式来定义Bean，以及定义容器，比如最常见的一种方式是通过被`@Configuration`注解的配置类，在其中编写被`@Bean`注解的方法来定义Bean，并且还能通过`@Componentscan`来扫描指定包下的组件导入更多的Bean。

​	现在，`SpringBoot`将这些工作自动化了。你只需要按照上面的建议构造你的代码（将你的启动类定义在顶级包中），你也可以在启动类中添加`@Componentscan`（不过其实添加`@SpringbootApplication`包含了同样 的效果），你所有的应用组件（`@Component、@Service、@Repository、@Controller`和其他）都会自动注册为Spring Bean。

​	也可以直接使用`@SpringBootApplication`注解（该注解包含了`@ComponentScan`）。

​	下面的例子展示了一个`@Service`Bean。它使用构造器注入的方式注入了`RiskAssersor`Bean

```java
import org.springframework.stereotype.Service;

@Service
public class MyAccountService implements AccountService {

    private final RiskAssessor riskAssessor;

    public MyAccountService(RiskAssessor riskAssessor) {
        this.riskAssessor = riskAssessor;
    }

    // ...

}
```

​	之前提到过，只有一个构造函数的可以省略`@Autowired`。如果有多个构造函数，需要用`@Autowired`注解来告诉Spring该用哪个构造函数进行注入

```java
import java.io.PrintStream;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class MyAccountService implements AccountService {

    private final RiskAssessor riskAssessor;

    private final PrintStream out;

    @Autowired
    public MyAccountService(RiskAssessor riskAssessor) {
        this.riskAssessor = riskAssessor;
        this.out = System.out;
    }

    public MyAccountService(RiskAssessor riskAssessor, PrintStream out) {
        this.riskAssessor = riskAssessor;
        this.out = out;
    }

    // ...

}


```

​	此时，依赖注入的策略是优先选择被`@Autowired`标记的构造函数





## 5.4 使用`@SpringBootApplication`注解	

​	许多SpringBoot开发者希望他们的应用程序能够使用自动配置、组件扫描，并且能够在他们的`application class`上定义额外的配置。一个`@SprongBootApplication`注解可以用来启用三个功能，如下

- `@EnableAutoConfiguration`:启动Spring boot的自动配置机制
- `ComponentScan`: 对应用程序所在的包启用`@Component`扫描
- `@SpringBootConfigutation`:允许在`Context`中注册外地Bean或导入额外配置类。这是Spring标准的`@Configuration`的替代方案。

```java
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

// Same as @SpringBootConfiguration @EnableAutoConfiguration @ComponentScan
@SpringBootApplication 
public class MyApplication {
    public static void main(String[] args) {
        SpringApplication.run(MyApplication.class, args);
    }
}
```



​	
