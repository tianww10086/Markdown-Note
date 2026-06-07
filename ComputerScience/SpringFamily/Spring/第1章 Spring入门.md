# 1 什么是Spring

​	Spring的核心是一个容器，成为`Spring`应用程序上下文，**用于创建和管理应用程序组建**，这些组件（或bean）在Spring应用程序上下文中连接在一起一次构成一个完整的应用程序。就像将砖、灰奖、木材等等组成房屋一样

> ​	bean是被Spring容器管理的对象，区别于自己创建、管理的Java对象

​	将bean连接在一起的行为是**基于一种称为==依赖注入（DI）==的模式**。**依赖项注入的应用程序，不是由组件自身创建和维护它们以来的其他bean的生命周期，而是依赖于单独的实体（容器）来创建和维护所有组件。**并将这些组件注入需要它们的bean，通常通过构造函数参数或属性访问器完成此操作。

​	

​	例如，有两个组件:`inventoryservice(库存信息)`和`product service(产品信息)`。库存信息依赖于产品信息，下图说明了`bean`和`Spring`应用程序上下文之间的关系

<img src="../IMG/image-20260601160553078.png" alt="image-20260601160553078" style="zoom:80%;" />

​		从历史上看，引导`Spring`应用程序上下文将`bean`连接在一起的方式是使用一个或多个XML文件，这些文件描述了组件及其于其他组件的关系。例如

​	以下XML声明两个bean，一个`InventoryService`Bean和一个`ProductService`bean，然后通过构造函数参数将`InventoryService`bean注入到`ProductService`中

```xml
<bean id="inventoryService" 
      class="com.example.InventoryService"/>
<bean id="productService"
      class = "com.example.ProductService">
	<constructor-arg ref = "inventoryService"/>
</bean>
```

​	在新版本中，基于`Java`的配置更为常见，下面基于Java的配置类等效XML配置：

```java
@Configuration
public class ServiceConfiguration{
    @Bean
    public InventoryService inventoryService(){
        return new InventoryService();
    }
    
    @Bean
    public ProductService productService(){
        return new ProductService(inventoryService());
    }
}
```

​	`@Configuration`注解向`Spring`表明这是一个配置类，它为`Spring application context`提供`beans`。配置的类方法带有`@Bean`注释，指示它们返回的对象应作为`bean`添加到应用程序上下文中。

​	基于Java的配置具有多个优点，包括更高的类型安全性和改进的可重构性。即使这样，仅当Spring无法自动配置组件时，才需要使用`Java`或`XML`进行显示配置，也就是说，**大部分时候Spring都是自动配置的**

​	

​	随着`Spring boot`的推出，自动配置的优势已经远远超过了组件扫描和自动装配，`Spring Boot`是`Spring`框架的扩展，它提供了多项生产力增强功能。这些增强功能最**著名的就是自动配置**

​	`Spring boot`自动配置大大减少了构建应用所需的显式配置，本章的示例中，甚至仅包含一行Spring配置代码。

​	`Spring Boot`极大地增强了`Spring`开发的能力，在学习时，将尽可能使用`Spring Boot`，并仅在必要时使用显式配置。



## 1.1 IDEA中使用Spring

​	使用Spring有多种方式，可以使用官方给出的快捷创建工程，也可以利用特定的工具创建，IDEA中也支持创建Spring项目。在这里，我们利用Maven依赖管理框架来使用Spring。

​	第一步，是创建一个普通的Maven项目，然后在`pom.xml`中导入`Spring`坐标。

```xml
       <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-context</artifactId>
            <version>6.2.14</version>
        </dependency>
```

​	第二步，在`resources`文件夹内，右键选择新建`xml配置文件`的选项中选择`spring`配置，命名为`applicationContext`。之后，便可以在里面通过`<bean/>`标签来声明`bean`：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
	
    <bean id = "hello" class="service.Hello"/>
</beans>
```

​	id是这个bean的唯一标识，也是通过容器获取bean的key，`class`指明了这个bean管理的类。

​	随后，我们就可以通过`Ioc`容器来获取这个bean（对象），`Hello`这个类有一个`Hi`方法，将打印`Hello`。在获取bean之前，当然呀先获取容器。在`Spring`中，使用`applicationContext`这个接口来代表Ioc容器，它有许多的实现类。这里我们使用实现类`	ClassPathXmlApplicationContext`

```java
public class App2 {
    public static void main(String[] args) {
            //获取Ioc容器（ApplicationContext）
        ApplicationContext ctx = new ClassPathXmlApplicationContext("applicationContext.xml");

        Hello h = (Hello) ctx.getBean("hello");
        h.hi();
    }
}
//运行结果：
Hello
```

​	

​		



# 2 IoC容器

​	使用对象时，由主动new产生对象转化为由外部提供对象，此过程中对象创建控制权由程序转移到**外部**，从而降低了耦合，此思想称为控制反转。

​	`Spring`提供了一个容器，成为`Ioc`容器，用来充当`IoC`思想中的外部。	



## 2.1 Spring IoC容器和Bean简介

​	`org.springframework.beans`和`org.springframework.context`包是`Spring Framework`的Ioc容器的基础，`BeanFactory`接口提供一种高级配置机制，能够管理任何类型的对象

​	**`ApplicationContext`**是`BeanFactory`的子接口，它增加了很多功能：

- 更容易于Spring的AOP功能集成
- `Message resource`处理（用于国际化）
- 事件发布
- 应用层的特定上下文，如`WebApplicationContext`，用于web应用

​	简而言之，`BeanFactory`提供了配置框架和基本功能，而`ApplicationContext`则增加了更多的企业特定功能。

​	在Spring中，构成你的应用程序的骨干并由Spring IOC容器管理的对象被称为Bean。`Bean`是一个由Spring Ioc容器实例化、组装和管理的对象。`Bean`以及它们之间的依赖关系都反映在容器使用的配置元数据（XML或注解）中。 





## 2.2 容器概述

​	`org.springframework.context.ApplicationContext`接口代表`Spring IoC`容器，负责**实例化、配置和组装bean**。容器通过读取配置元数据来获得关于要实例化、配置和组装哪些对象的知识。**配置元数据以XML、Java注解或Java代码标识**

​	Spring提供了几个`ApplicationContext`接口的实现。

1. **ClassPathXmlApplicationContext**

​	这个实现从类路径（classpath）加载XML配置。如：

```java
ApplicationContext contex =
    new ClassPathXmlApplicationContext("applicationContext.xml")
```

​	`Spring`会从`src/main/resources`下面寻找`applicationContext.xml`文件，然后读取元数据	

2. **FileSystemXmlApplicationContext**

​	从磁盘路径加载XML（相对或绝对路径都可以），例如：

```java
ApplicationContext context =
    new FileSystemXmlApplicationContext(
        "D:/spring/applicationContext.xml");
//或
ApplicationContext context2 =
    new FileSystemXmlApplicationContext(
        "config/applicationContext.xml");
```

3. **AnnotationConfigApplicationContext**

   最常用的元数据配置方式，读取Java配置类。例如：

   ```java
   @Configuration
   public class AppConfig {
   
       @Bean
       public UserService userService(){
           return new UserService();
       }
   
   }
   ```

   @Configuration表明它是一个配置类，@Bean表明这个构造方法是一个bean。

   然后创建applicationContext:

   ```java
   ApplicationContext context =
       new AnnotationConfigApplicationContext(
           AppConfig.class);
   ```



​	但实际上，在大多数时候都工作环境中，你都不需要去手动创建容器，这部分工作被Spring自动完成了。到Spring Boot时代，甚至只有一句：

```java
SpringApplication.run(...)
```

​	



#### 2.2.1 配置元数据 

​	配置元数据传统上是以简单直观的XML格式提供的。

​	Spring的配置包括至少一个，通常是一个以上的`Bean`定义，容器必须管理这些定义。基于XML的配置元数据将这些`Bean`配置为顶层`<beans/>`元素内的`<bean/>`元素。而`Java`配置通常使用`@Configuration`类的`@Bean`注解的方法

​	这些`Bean`的定义对应应用构成你的应用程序的实际对象，下面的例子显示了基于XML的配置元数据的基本结构

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean id="..." class="..."> (1) (2)
        <!-- 这个bean的合作者和配置在这里 -->
    </bean>

    <bean id="..." class="...">
        <!-- c这个bean的合作者和配置在这里 -->
    </bean>

    <!-- 更多bean 定义在这里 -->

</beans>

```

- id属性是一个字符串，用于识别单个Bean定义
- class属性定义了Bean的类型，并使用类的全路径明

`id` 属性的值可以用来指代协作对象。但本例中没有显示用于引用协作对象的XML。在之后会介绍协作对象。

> 协作对象：在实际开发中更多的被称为：
>
> 依赖对象
> 依赖Bean
> 关联Bean
>
> 例如，如果一个类中的成员包含另一个类，那个类就被称为协作对象。



#### 2.2.2 实例化一个容器

​	提供给`ApplicationContext`构造函数的一条或多条路径是资源字符串，它让容器从各种外部资源（如本地文件系统、JavaCLASSPATH等）加载配置元数据

```xml
ApplicationContext context = new ClassPathXmlApplicationContext("services.xml","daos.xml");
```

​	



**构建基于XML的配置元数据**

​	让Bean的定义跨越多个XML文件很有用。通常情况下，每个单独的XML配置文件代表了你架构中的一个逻辑层或模块。你可以使用`applicationcontext`构造函数从所有这些XML片段中加载Bean定义，这个构造函数需要多个`Resource`位置，如上一节所示。

​	或是使用一个或多个`<import/>`元素来从另一个或多个文件加载Bean定义：

```xml
<beans>
    <import resource="services.xml"/>
    <import resource="resources/messageSource.xml"/>
    <import resource="/resources/themeSource.xml"/>

    <bean id="bean1" class="..."/>
    <bean id="bean2" class="..."/>
</beans>

```

​	在前面的例子中，外部Bean定义从三个文件中加载：`services.xml`、`messageSource.xml` 和 `themeSource.xml`。所有的位置路径都是相对于进行导入的定义文件而言的，所以 `services.xml` 必须与进行导入的文件在同一目录或 classpath 位置，而 `messageSource.xml` 和 `themeSource.xml` 必须在导入文件的位置以下的 `resources` 位置。正如你所看到的，前导斜线会被忽略。然而，鉴于这些路径是相对的，最好不要使用斜线。被导入文件的内容，包括顶层的 `<beans/>` 元素，必须是有效的XML Bean定义



#### 2.2.3 使用容器

​	`ApplicationContext` 是一个高级工厂的接口，能够维护不同Bean及其依赖关系的注册表。通过使用方法 `T getBean(String name, Class<T> requiredType)`，你可以检索到Bean的实例。

`ApplicationContext` 可以让你读取Bean定义（definition）并访问它们，如下例所示。

```java
public class App2 {
    public static void main(String[] args) {
            //获取Ioc容器（ApplicationContext）
        ApplicationContext ctx = new ClassPathXmlApplicationContext("applicationContext.xml");

        Hello h = ctx.getBean("hello",Hello.class);
        h.hi();
    }
}
```

​	可以使用`getBean`来检索Bean的实例，接口`PpplicationContext`还有一些其他检索Bean的方法。但在理想情况下，不应该使用这些方法，本质上还是自己获取对象的方式，这不符合`IOC`的思想。

​	更推荐通过 `@Autowired`、构造器注入等依赖注入方式获得 Bean，而不是让业务代码主动去容器里查找 Bean。



## 2.3 Bean概览

​	一个Spring IoC容器管理着一个或多个Bean。这些Bean是用你提供给容器的配置元数据创建的（例如，以XML <bean/> 定义的形式）。

在容器本身中，这些Bean定义被表示为 `BeanDefinition` 对象，它包含（除其他信息外）以下元数据。

- 一个全路径类名：通常，被定义的Bean的实际实现类。
- Bean的行为配置元素，它说明了Bean在容器中的行为方式（scope、生命周期回调，等等）。
- 对其他Bean的引用，这些Bean需要做它的工作。这些引用也被称为合作者或依赖。
- 要在新创建的对象中设置的其他配置设置—例如，pool的大小限制或在管理连接池的Bean中使用的连接数。

这个元数据转化为构成每个Bean定义的一组属性。下表描述了这些属性。

| 属性                     | 解释…                                                        |
| :----------------------- | :----------------------------------------------------------- |
| Class                    | [实例化 Bean](https://springdoc.cn/spring/core.html#beans-factory-class) |
| Name                     | [Bean 命名](https://springdoc.cn/spring/core.html#beans-beanname) |
| Scope                    | [Bean Scope](https://springdoc.cn/spring/core.html#beans-factory-scopes) |
| Constructor arguments    | [依赖注入](https://springdoc.cn/spring/core.html#beans-factory-collaborators) |
| Properties               | [依赖注入](https://springdoc.cn/spring/core.html#beans-factory-collaborators) |
| Autowiring mode          | [注入协作者（Autowiring Collaborators）](https://springdoc.cn/spring/core.html#beans-factory-autowire) |
| Lazy initialization mode | [懒加载的Bean](https://springdoc.cn/spring/core.html#beans-factory-lazy-init) |
| Initialization method    | [初始化回调](https://springdoc.cn/spring/core.html#beans-factory-lifecycle-initializingbean) |
| Destruction method       | [销毁回调](https://springdoc.cn/spring/core.html#beans-factory-lifecycle-disposablebean) |



#### 2.3.1  Bean命名

​	每个`Bean`都有一个或多个标识符（identifier）。这些标识符在承载Bean的容器中必须是唯一的。一个Bean通常只有一个标识符。然而，如果它需要一个以上的标识符，多余的标识符可以被视为别名。

​	在基于XML的配置元数据中，你可以使用 `id` 属性、`name` 属性或两者来指定Bean标识符。`id` 属性允许你精确地指定一个 `id`。传统上，这些名字是字母数字（'myBean'、'someService’等），但它们也可以包含特殊字符。如果你想为Bean引入其他别名，你也可以在 `name` 属性中指定它们，用逗号（`,`）、分号（`;`）或空格分隔。尽管 `id` 属性被定义为 `xsd:string` 类型，但 bean id 的唯一性是由容器强制执行的，尽管不是由 XML 解析器执行。

​	你不需要为Bean提供一个 `name` 或 `id`。如果你不明确地提供 `name` 或 `id`，容器将为该 Bean 生成一个唯一的名称。然而，如果你想通过使用 `ref` 元素或服务定位器风格的查找来引用该 bean 的名称，你必须提供一个名称。

​	**Bean的命名规则**

> 惯例是在命名Bean时使用标准的Java惯例来命名实例字段名。也就是说，Bean的名字以小写字母开始，然后以驼峰字母开头。这种名称的例子包括 `accountManager`、`accountService`、`userDao`、`loginController` 等等。
>
> 统一命名Bean使你的配置更容易阅读和理解。另外，如果你使用Spring AOP，在对一组按名称相关的Bean应用 advice 时，也有很大的帮助。

​	



**在 Bean Definition 之外对Bean进行别名**

​	在 Bean 定义中，你可以为Bean提供一个以上的名字，通过使用由 `id` 属性指定的最多一个名字和 `name` 属性中任意数量的其他名字的组合。这些名字可以是同一个Bean的等效别名，在某些情况下很有用，比如让应用程序中的每个组件通过使用一个特定于该组件本身的Bean名字来引用一个共同的依赖关系。

​	然而，在实际定义Bean的地方指定所有别名并不总是足够的。有时，为一个在其他地方定义的Bean引入别名是可取的。这种情况通常发生在大型系统中，配置被分割到每个子系统中，每个子系统都有自己的对象定义集。在基于XML的配置元数据中，你可以使用 `<alias/>` 元素来实现这一点。下面的例子展示了如何做到这一点。

```xml
<alias name="fromName" alias="toName"/>
```

​	在这种情况下，一个名为 `fromName` 的bean（在同一个容器中）在使用这个别名定义后，也可以被称为 `toName`。

​	例如，子系统A的配置元数据可以引用一个名为 `subsystemA-dataSource` 的数据源。子系统B的配置元数据可以引用一个名为 `subsystemB-dataSource` 的数据源。当组成使用这两个子系统的主应用程序时，主应用程序以 `myApp-dataSource` 的名字来引用数据源。为了让这三个名字都指代同一个对象，你可以在配置元数据中添加以下别名定义。

```xml
<alias name="myApp-dataSource" alias="subsystemA-dataSource"/>
<alias name="myApp-dataSource" alias="subsystemB-dataSource"/>
```

​	现在，每个组件和主应用程序都可以通过一个独特的名称来引用dataSource，并保证不与任何其他定义冲突（有效地创建了一个命名空间），但它们引用的是同一个bean。





#### 2.3.2 实例化Bean

​	`bean`定义本质是创建一个或多个对象的“配方”。容器在被要求时查看命名的`Bean`的“配方”。并使用该Bean定义所封装的配置元数据来创建（或获取）一个实际的对象

​	如果你使用基于XML的配置元数据，要在`<bean/>`元素的`class`属性中指定要实例化的对象的类型（或class）。这个`class`属性通常是强制的。可以以两种方式之一使用`Class`属性

- 通常，在容器本身通过反射式的调用构造函数直接创建`Bean`的情况下，指定要构造的`Bean`类，有点相当于`Java`代码中的`new`操作
- 在不太常见的情况下，即容器在一个类上调用`static`工厂方法来创建`bean`时，要指定包含被调用的`static`工厂方法的实际类。从`static`工程方法调用中返回的对象类型可能是同一个类或完全是另一个类



> **嵌套类名**
>
> 如果你为一个嵌套类配置一个Bean定义，你可以使用嵌套类的二进制名称或源名称。
>
> 例如，在`com.example`包中有一个叫做`SomeThing`的类，而这个`SomeThing`类有一个叫做`OtherThing`的静态嵌套类，它们可以用美元符号（$）或点（.）分开，因此在Bean定义中的class属性的指将是
>
> `com.example.SomeThing$OtherThing`或`com.example.SomeThing.OtherThing`





##### 1.用构造函数进行实例化

​	当你用构造函数的方法创建一个`Bean`时，所有普通的类都可以被Spring使用并与之兼容。**也就是说，被开发的类不需要实现任何特定的接口，也不需要以特定的方式进行编码，只需要指定Bean类就足够了**。

​	Spring Ioc容器几乎可以管理任何你希望它管理的类。大多数Spring用户更喜欢真正的JavaBean，它有一个默认的无参构造函数，以及按照容器中的属性建模适当的`setter`和`getter`。也可以在你的容器中拥有更多奇特的非`bean`风格的类。

​	基于XML的配置元数据，可以按以下方式指定你的`bean`类：

```java
<bean id="exampleBean" class="examples.ExampleBean"/>

<bean name="anotherExample" class="examples.ExampleBeanTwo"/>

```

​	

##### 2. 用静态工厂方法进行实例化

​	在定义一个静态工厂方法来创建`Bean`时，使用`class`属性来指定包含`static`工厂方法的类。并使用名为`factory-method`的属性来指定工厂方法本身的名称。Spring 可以通过静态工厂方法获得对象。获得对象之后，它会像对待普通 `new` 出来的对象一样管理它。这个功能主要是为了兼容那些已经存在的大量老代码和老框架，因为它们经常使用静态工厂方法而不是构造函数来创建对象。

​	下面的`Bean`定义规定，`Bean`将通过调用工厂方法来创建。该定义没有指定返回对象的类型（`class`）。而是指定了包含工厂方法的类，在这个例子中，`createInstance()`必须是一个`static`方法，下面的例子显示如何指定一个工厂方法

```java
<bean id="clientService"
    class="examples.ClientService"
    factory-method = "createInstance"/>
```

​	下面的例子显示了一个可以与前面的`Bean`定义一起工作的类：

```java
public class ClientService {
    private static ClientService clientService = new ClientService();
    private ClientService() {}

    public static ClientService createInstance() {
        return clientService;
    }
}
//一个单例模式的对象
```

​	

##### 3. 用实例工厂方法进行实例化

​	用实例工厂方法进行的实例化从容器中调用现有bean的非静态方法来创建一个新的bean。要使用这种机制，请将`class`属性留空，并在`factory-bean`属性中指定当前（或父代）容器中的一个Bean的名称。该容器包含要被调用来创建对象的实例方法。用`facotyr-method`属性设置工厂方法本身的名称。下面的例子显示了如何配置这样的一个Bean。

```java
<!-- the factory bean, which contains a method called createInstance() -->
<bean id="serviceLocator" class="examples.DefaultServiceLocator">
    <!-- inject any dependencies required by this locator bean -->
</bean>

<!-- the bean to be created via the factory bean -->
<bean id="clientService"
    factory-bean="serviceLocator"
    factory-method="createClientServiceInstance"/>

```

​	下面的例子显示了对应的工厂类：

```java
public class DefaultServiceLocator {

    private static ClientService clientService = new ClientServiceImpl();

    public ClientService createClientServiceInstance() {
        return clientService;
    }
}
```

​	一个工厂类也可以容纳一个以上的工厂方法。如下所示：

```java
<bean id="serviceLocator" class="examples.DefaultServiceLocator">
    <!-- inject any dependencies required by this locator bean -->
</bean>

<bean id="clientService"
    factory-bean="serviceLocator"
    factory-method="createClientServiceInstance"/>

<bean id="accountService"
    factory-bean="serviceLocator"
    factory-method="createAccountServiceInstance"/>

```

​	对应的工厂类：

```java
public class DefaultServiceLocator {

    private static ClientService clientService = new ClientServiceImpl();

    private static AccountService accountService = new AccountServiceImpl();

    public ClientService createClientServiceInstance() {
        return clientService;
    }

    public AccountService createAccountServiceInstance() {
        return accountService;
    }
}
```





## 2.4 依赖

​	一个典型的企业应用程序并不是由单一的对象（或Spring术语中的bean）组成的。即使是最简单的应用也是一些对象组成，它们一起工作，呈现出最终用户所看到的连贯的应用。

​	下面将解释如何从定义一些单独的`Bean`定义到一个完全实现的应用，在这个应用中，**各对象相互协作以实现一个目标**





#### 2.4.1 依赖注入

​	**依赖注入（DI）是一个过程**，对象仅通过构造参数、工厂方法的参数，或在对象实例被构造，或从工厂方法返回后在其上设置的属性来定义来的**依赖（即与它们一起工作的其他对象）**。

​	然后，容器在创建`bean`时注入这些依赖，这个过程从根本上说是**Bean本身通过使用类的直接构造或服务定位模式来控制其依赖的实例化或位置的逆过程（因此被称为控制反转）**

​	采用DI原则，代码会更干净，当对象被提供其依赖时，解耦会更有效，对象不会查找其依赖，也不知道依赖的位置或类别。因此类变得更容易测试。

​	DI主要有两个变体：基于构造器的依赖注入和基于setter的依赖注入。




##### 1.基于构造器的依赖注入

​	基于构造函数的DI是通过容器调用带有许多参数的构造函数来完成的，每个参数代表一个依赖。调用带有特定参数的`static`工厂方法来构造`bean`几乎是等价的。本讨论对构造函数的参数和`static`工厂方法的参数进行类似处理。下面的例子显示了一个只能用构造函数注入的依赖注入的类。

```java
public class SimpleMovieLister {

    // the SimpleMovieLister has a dependency on a MovieFinder
    private final MovieFinder movieFinder;

    // a constructor so that the Spring container can inject a MovieFinder
    public SimpleMovieLister(MovieFinder movieFinder) {
        this.movieFinder = movieFinder;
    }

    // business logic that actually uses the injected MovieFinder is omitted...
}


```

​	注意，这个类并没有什么特别之处，它是一个POJO，对容器的特定接口、基类或注解没有依赖。

> 构造器注入就是 Spring 在创建对象时，通过调用构造函数，把对象需要的依赖传进去；而业务类本身只是普通 Java 类（POJO），完全不需要继承 Spring 的类或实现 Spring 的接口。这样业务代码和 Spring 框架保持解耦。





2.**构造函数参数解析**

​	构造函数解析匹配是通过使用参数的类型进行的。构造器参数在bean定义中的定义顺序就是这些参数bean被实例化时被提供给适当的构造器顺序。考虑下面这个类。

```java
package x.y;
public class ThingOne{
    public ThingOne(ThingTwo thingTwo,ThingThree thingThree){
        //..
    }
}
```

​	假设`ThingTwo`和`ThingThree`类没有继承关系。在下面的配置中，不需要在`<constructor-arg/>`元素中明确指定构造函数参数的索引或类型，因为它引用了其他`bean`

```xml
<beans>
    <bean id="beanOne" class="x.y.ThingOne">
        <constructor-arg ref="beanTwo"/>
        <constructor-arg ref="beanThree"/>
    </bean>

    <bean id="beanTwo" class="x.y.ThingTwo"/>

    <bean id="beanThree" class="x.y.ThingThree"/>
</beans>

```

​	当引用另一个Bean时，类型是已知的，并且可以进行匹配（就像前面的例子那样）。当使用一个简单的类型时，比如 `<value>true</value>`，Spring不能确定值的类型，所以在没有帮助的情况下不能通过类型进行匹配。考虑一下下面这个类。

```java
package examples;

public class ExampleBean {

    // Number of years to calculate the Ultimate Answer
    private final int years;

    // The Answer to Life, the Universe, and Everything
    private final String ultimateAnswer;

    public ExampleBean(int years, String ultimateAnswer) {
        this.years = years;
        this.ultimateAnswer = ultimateAnswer;
    }
}

```

​	在这个类里面的构造函数中，它的参数是两个基本类型。所以可以通过`type`属性显式地指定构造函数的类型，容器就可以使用简答的类型匹配：

```java
<bean id="exampleBean" class="examples.ExampleBean">
    <constructor-arg type="int" value="7500000"/>
    <constructor-arg type="java.lang.String" value="42"/>
</bean>
```

​	

​	可以使用`index`属性来明确指定构造函数参数的索引，如下例所示：

```java
<bean id="exampleBean" class="examples.ExampleBean">
    <constructor-arg index="0" value="7500000"/>
    <constructor-arg index="1" value="42"/>
</bean>

```

​	`index="0"`表示该参数对应构造器函数的第一个参数，`index="1"`表示该参数对应构造器函数的第2个参数，指定一个索引可以解决构造函数有两个相同类型的参数的歧义。	

```java
public class Person {

    private String name;
    private String address;

    public Person(String name, String address) {
        this.name = name;
        this.address = address;
    }
}
```

​	对于正常使用的构造函数，Spring不会出错，但是如果是这样使用：

```java
new Person("贵州", "田");
```

​	原本期望的值被错误的填入成员了，指定索引可以解决这个问题：

```java
<bean id="person" class="Person">
    <constructor-arg index="0" value="田"/>
    <constructor-arg index="1" value="贵州"/>
</bean>
```

​	明确的告诉第一个参数是：“田”，第二个参数是：“贵州”

​	**也可以使用构造函数的参数名称来进行消歧**：

```java
<bean id="person" class="Person">
    <constructor-arg name="name" value="田"/>
    <constructor-arg name="address" value="贵州"/>
</bean>
```

​	但要使用这种形式，代码在编译时必须启用`debug`标志，因为java在编译时并不会保存构造函数的参数名称，更类似`person(String,String)`。`Spring`需要知道构造器的参数名称，所以在开启`debug`标志后可以获得这些名称。

​	不过，有另一种办法解决这个问题，那就是使用`@ConstructorProperties`JDK注解来明确命名你的构造函数参数。这样依赖，示例类就得如下：

```java
package examples;

public class ExampleBean {

    // Fields omitted

    @ConstructorProperties({"years", "ultimateAnswer"})
    public ExampleBean(int years, String ultimateAnswer) {
        this.years = years;
        this.ultimateAnswer = ultimateAnswer;
    }
}
```



##### 3.基于Setter的依赖注入

​	基于Setter的DI是通过容器在调用无参数的构造函数或无参数的`static`工厂方法来实例化你的`bean`之后调用`Setter`方法来实现的。

​	下面的例子显示了一个只能通过使用纯`setter`注入的类的依赖注入。

```java
public class SimpleMovieLister {

    // the SimpleMovieLister has a dependency on the MovieFinder
    private MovieFinder movieFinder;

    // a setter method so that the Spring container can inject a MovieFinder
    public void setMovieFinder(MovieFinder movieFinder) {
        this.movieFinder = movieFinder;
    }

    // business logic that actually uses the injected MovieFinder is omitted...
}


```

​	`ApplicationContext`支持它所管理的`Bean`基于构造器和基于Setter的`DI`，它还支持在一些依赖已经通过构造器方法注入后的基于setter的DI。

​	你以`BeanDefinition`的形式配置依赖关系，将其与`PropertyEditor`实例一起使用，将属性从一种格式转化为另一种。然而大多数Spring用户并不直接使用这些类。而是`XML bean`定义、注解组件（即用`@Component、@Controller`等注解的类），或基于Java的`@Configuration`类中的`Bean`方法。然后这些来源在内部转化为`BeanDefinition`的实例，并用于加载整个`Spring IoC`实例。

> **基于构造器的DI还是基于setter的DI？**
>
> ​	由于你可以混合使用基于构造函数的DI和基于setter的DI，一个好的经验法则是对强制依赖使用构造函数，对可选依赖使用setter方法或配置方法。请注意，在setter方法上使用 [@Autowired](https://springdoc.cn/spring/core.html#beans-autowired-annotation) 注解可以使属性成为必须的依赖；然而，带有参数程序化验证的构造器注入是更好的。
>
> ​	Spring团队通常提倡构造函数注入，因为它可以让你将应用组件实现为不可变的对象，并确保所需的依赖不为 `null`。此外，构造函数注入的组件总是以完全初始化的状态返回给客户端（调用）代码。顺便提一下，大量的构造函数参数是一种不好的代码气味，意味着该类可能有太多的责任，应该重构以更好地解决适当的分离问题。
>
> ​	Setter注入主要应该只用于在类中可以分配合理默认值的可选依赖。否则，必须在代码使用依赖的所有地方进行非null值检查。Setter注入的一个好处是，Setter方法使该类的对象可以在以后重新配置或重新注入。因此，通过 [JMX MBean](https://springdoc.cn/spring/integration.html#jmx) 进行管理是setter注入的一个引人注目的用例。
>
> ​	对于一个特定的类，使用最合理的DI风格。有时，在处理你没有源代码的第三方类时，你会做出选择。例如，如果一个第三方类没有暴露任何setter方法，那么构造函数注入可能是唯一可用的DI形式。







##### 4.依赖的解析过程

​	容器按如下方式执行 bean 依赖解析。

- ApplicationContext 是用描述所有bean的配置元数据创建和初始化的。配置元数据可以由XML、Java代码或注解来指定。

- 对于每个Bean来说，它的依赖是以属性、构造函数参数或静态工厂方法的参数（如果你用它代替正常的构造函数）的形式表达的。在实际创建Bean时，这些依赖被提供给Bean。

- 每个属性或构造函数参数都是要设置的值的实际定义，或对容器中另一个Bean的引用。

- 每个作为值的属性或构造函数参数都会从其指定格式转换为该属性或构造函数参数的实际类型。默认情况下，Spring 可以将以字符串格式提供的值转换为所有内置类型，如 int、long、String、boolean 等等。


​	当容器被创建时，Spring容器会验证每个Bean的配置。然而，在实际创建Bean之前，Bean的属性本身不会被设置。当容器被创建时，那些具有单例作用域并被设置为预实例化的Bean（默认）被创建。作用域在 Bean Scope 中定义。否则，Bean只有在被请求时才会被创建。创建 bean 有可能导致创建 bean 图（graph），因为 bean 的依赖关系和它的依赖关系（等等）被创建和分配。请注意，这些依赖关系之间的解析不匹配可能会出现得很晚—也就是说，在第一次创建受影响的Bean时。

> **循环依赖**
>
> ​	如果你使用主要的构造函数注入，就有可能产生一个无法解决的循环依赖情况。
>
> ​	比如说。类A通过构造函数注入需要类B的一个实例，而类B通过构造函数注入需要类A的一个实例。如果你将A类和B类的Bean配置为相互注入，Spring IoC容器会在运行时检测到这种循环引用，并抛出一个 `BeanCurrentlyInCreationException`。
>
> ​	一个可能的解决方案是编辑一些类的源代码，使其通过setter而不是构造器进行配置。或者，避免构造器注入，只使用setter注入。换句话说，虽然不推荐这样做，但你可以用setter注入来配置循环依赖关系。
>
> ​	与典型的情况（没有循环依赖关系）不同，Bean A和Bean B之间的循环依赖关系迫使其中一个Bean在被完全初始化之前被注入到另一个Bean中（一个典型的鸡生蛋蛋生鸡的场景）。



##### 5.依赖注入的例子

​	下面的例子将基于XML的配置元数据用于基于setter的DI。

```xml
<bean id="exampleBean" class="examples.ExampleBean">
    <!-- setter injection using the nested ref element -->
    <property name="beanOne">
        <ref bean="anotherExampleBean"/>
    </property>

    <!-- setter injection using the neater ref 	attribute -->
    <property name="beanTwo" ref="yetAnotherBean"/>
    <property name="integerProperty" value="1"/>
</bean>

<bean id="anotherExampleBean" class="examples.AnotherBean"/>
<bean id="yetAnotherBean" class="examples.YetAnotherBean"/>

```

​	相应的`ExampleBean`类：

```java
public class ExampleBean {

    private AnotherBean beanOne;

    private YetAnotherBean beanTwo;

    private int i;

    public void setBeanOne(AnotherBean beanOne) {
        this.beanOne = beanOne;
    }

    public void setBeanTwo(YetAnotherBean beanTwo) {
        this.beanTwo = beanTwo;
    }

    public void setIntegerProperty(int i) {
        this.i = i;
    }
}


```

​	setter被声明为与XML文件中指定的属性相匹配



​	下面的例子使用基于构造函数的DI

```xml
<bean id = "exampleBean" class="examples.ExampleBean">
    <constructor-arg>
        <ref bean = "anotherExampleBean"/>
    </constructor-arg>
    
    <!-- 简洁写法 -->
    <constructor-arg ref = "yetAnotherBean"/>
    
    <constructor-arg type = "int" value = "1" />
</bean>
<bean id="anotherExampleBean" class="examples.AnotherBean"/>
<bean id="yetAnotherBean" class="examples.YetAnotherBean"/>
```

​	相应的`ExampleBean`类

```java
public class ExampleBean {

    private AnotherBean beanOne;

    private YetAnotherBean beanTwo;

    private int i;

    public ExampleBean(
        AnotherBean anotherBean, YetAnotherBean yetAnotherBean, int i) {
        this.beanOne = anotherBean;
        this.beanTwo = yetAnotherBean;
        this.i = i;
    }
}
```

​	还记得前面说过的，`static`工厂方法返回对象实例与构造的DI类似，下面这个例子，则是一个使用工厂方法返回对象的实例：

```xml
<bean id="exampleBean" class="examples.ExampleBean" factory-method="createInstance">
    <constructor-arg ref="anotherExampleBean"/>
    <constructor-arg ref="yetAnotherBean"/>
    <constructor-arg value="1"/>
</bean>

<bean id="anotherExampleBean" class="examples.AnotherBean"/>
<bean id="yetAnotherBean" class="examples.YetAnotherBean"/>

```

​	对应`ExampleBean`类

```java
public class ExampleBean {

    // a private constructor
    private ExampleBean(...) {
        ...
    }

    // a static factory method; the arguments to this method can be
    // considered the dependencies of the bean that is returned,
    // regardless of how those arguments are actually used.
    public static ExampleBean createInstance (
        AnotherBean anotherBean, YetAnotherBean yetAnotherBean, int i) {

        ExampleBean eb = new ExampleBean (...);
        // some other operations...
        return eb;
    }
}

```

​	`static`工厂方法的参数由`<constructor-ar/>`元素提供，**与实际使用的构造函数完全相同**。被工厂方法返回的类的类型不一定与包含`static`工厂方法的类的类型相同。实例工厂方法可以以基本相同的方式使用（除了使用`factory-bean`属性，而不是`class`属性这点之外）

​	

#### 2.4.2 依赖和配置的细节

​	在上一节中，我们将`Bean`属性和构造函数参数定义为其他`Bean`的引用，或者定义为内联的值。是使用`XML`配置的元数据`<property/>`和`<constructor-arg>`实现的



##### 1.字面值（基本类型、String等）

​	在上一节中，我们大多数是引用其他`Bean`作为参数使用，这一节将学习如何注入字面值。

​	`<property/>`元素的`value`属性 ，将属性或构造函数参数指定为可读的字符串表示。`Spring`的转换服务被用来将这些值从`String`转化成属性或参数的实际类型。下面的例子显示了各种值的设置

```xml
<bean id="myDataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
    <!-- results in a setDriverClassName(String) call -->
    <property name="driverClassName" value="com.mysql.jdbc.Driver"/>
    <property name="url" value="jdbc:mysql://localhost:3306/mydb"/>
    <property name="username" value="root"/>
    <property name="password" value="misterkaoli"/>
    <property name = "int_value" value = "11"/> 转换成整型
    <property name = "double_value " value = "18.8"/> 转换成浮点型
</bean>

```

​	`Spring`的转换服务可以正确的将可读字符串转化成里面对应的类型。

​	下面的例子使用`p-namespace`来实现更简洁的XML配置

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans

    <!-- 默认命名空间：Spring Bean配置使用的标签 -->
    xmlns="http://www.springframework.org/schema/beans"

    <!-- XML Schema标准命名空间 -->
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"

    <!-- p命名空间，用于简化property注入写法 -->
    xmlns:p="http://www.springframework.org/schema/p"

    <!--
        指定命名空间对应的校验规则(XSD)

        前半部分：
        http://www.springframework.org/schema/beans
        表示要校验的命名空间

        后半部分：
        https://www.springframework.org/schema/beans/spring-beans.xsd
        表示该命名空间对应的规则文件

        IDEA等IDE会根据这里提供自动提示、检查标签是否合法
    -->
    xsi:schemaLocation="
        http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- Bean定义 -->
    <bean id="myDataSource"
          class="org.apache.commons.dbcp.BasicDataSource"
          destroy-method="close"

          <!-- p命名空间写法，相当于：
               <property name='driverClassName' value='...'/>
          -->
          p:driverClassName="com.mysql.jdbc.Driver"

          <!-- 数据库连接地址 -->
          p:url="jdbc:mysql://localhost:3306/mydb"

          <!-- 数据库用户名 -->
          p:username="root"

          <!-- 数据库密码 -->
          p:password="misterkaoli"/>

</beans>
```

​	也可以配置一个`java.util.Properties`实例
```xml
<bean id="mappings"
    class="org.springframework.context.support.PropertySourcesPlaceholderConfigurer">

    <!-- typed as a java.util.Properties -->
    <property name="properties">
        <value>
            jdbc.driver.className=com.mysql.jdbc.Driver
            jdbc.url=jdbc:mysql://localhost:3306/mydb
        </value>
    </property>
</bean>

```

​	`Spring`容器通过使用`JavaBean`的`PropertyEditor`机制将`<value/>`元素中的文本转化为`java.util.Properties`实例。







##### 2.idref元素

​	`idref`元素仅仅将容器中另一个`bean`的id（一个字符串而不是一个引用）传递给`<constructor-arg/>`或`<property/>`元素的一种防错机制。

```xml
<bean id="theTargetBean" class="..."/>

<bean id="theClientBean" class="...">
    <property name="targetName">
        <idref bean="theTargetBean"/>
    </property>
</bean>
```

​	Spring容器可以提前检查容器中是否有这个bean的id，如果没有就可以提前报错。下面的`Bean`定义片段完全等同于（在运行时）下面的片段

```xml
<bean id="theTargetBean" class="..." />

<bean id="client" class="...">
    <property name="targetName" value="theTargetBean"/>
</bean>

```

​	第一中种形式比第二种形式好。因为`idref`标签可以让容器在部署时验证被引用的、命名的`bean`是否真的存在。在第二种变体中，没有对传递的`client`Bean的`targetName`属性进行验证（因为只认为是一个字符串）。只有在`client`Bean实际被实例化时，才会发现错误。

​	



##### 3.对其他Bean的引用（合作者或依赖）

​	`ref`元素是`<constructor-arg/>`或`<property/>`定义元素的最后的一个元素，在这里，你可以把一个bean的指定属性的值设置为对容器所管理的另一个`bean`的引用。大白话说就是，让该`bean`依赖注入另一个`bean`。被依赖的`bean`它在属性被设置之前根据需要被初始化。

​	所有的引用最终都是对另一个对象的引用，`scope`和验证取决于你是否通过`bean`或`parent`属性来指定其他对象的ID或名称，`bean`从全局去找（自己+父容器）。`parent`只找父容器。

​	

​	通过`<ref/>`标签的`bean`属性指定目标`bean`是最一般的形式。**它允许创建对同一容器或父容器中的任何bean引用**，不管它是否在同一个`XML`文件中，`Bean`属性的值是可以与目标bean的`id`属性相同，或与目标`bean`的`name`属性的一个值相同。下面的例子显示了如何使用一个`ref`元素

```xml
<ref bean = "someBean"/>
<!--这个someBean可以是另一个bean的id或name中的一个值 -->
```

​	通过`parent`属性创建目标Bean，可以创建对当前容器的父容器中的`Bean`的引用，`parent`属性的值可以与目标`Bean`的`id`属性或目标Bean的`name`属性中的一个值相同。**目标`Bean`必须在当前容器的一个父容器中。**当你有一个分层的容器（如MVC），你想用一个与父级Bean同名的代理来包装父级容器中的现有Bean时，应该使用这种Bean引用变体。下面的一对列表展示了如何使用`parent`属性

```xml
<!-- in the parent context -->
<bean id="accountService" class="com.something.SimpleAccountService">
    <!-- insert dependencies as required here -->
</bean>

```

```xml
<!-- in the child (descendant) context -->
<bean id="accountService" <!-- bean name is the same as the parent bean -->
    class="org.springframework.aop.framework.ProxyFactoryBean">
    <property name="target">
        <ref parent="accountService"/> <!-- notice how we refer to the parent bean -->
    </property>
    <!-- insert other configuration and dependencies as required here -->
</bean>

```



##### 4.内部Bean

​	在`<property/>`或`<constructor-arg/>`元素内的`<bean/>`元素定义了一个内部`Bean`
```xml
<bean id="outer" class="...">
    <!-- 而不是使用对目标Bean的引用，只需在行内定义目标Bean即可 -->
    <property name="target">
        <bean class="com.example.Person"> <!-- 这是内部Bean -->
            <property name="name" value="Fiona Apple"/>
            <property name="age" value="25"/>
        </bean>
    </property>
</bean>
```

​	内部bean定义不需要ID或名称。内部Bean是Spring在解析配置时创建的匿名对象，然后通过`setter`或构造器注入到外部Bean中。





##### 5.集合（Collection）

​	`<list/>`、`<set/>`、`<map/>` 和 `<props/>` 元素分别设置Java `Collection` 类型 `List`、`Set`、`Map` 和 `Properties` 的属性和参数。下面的例子展示了如何使用它们。

```xml
<bean id="moreComplexObject" class="example.ComplexObject">
    <!-- results in a setAdminEmails(java.util.Properties) call -->
    <property name="adminEmails">
        <props>
            <prop key="administrator">administrator@example.org</prop>
            <prop key="support">support@example.org</prop>
            <prop key="development">development@example.org</prop>
        </props>
    </property>
    <!-- results in a setSomeList(java.util.List) call -->
    <property name="someList">
        <list>
            <value>a list element followed by a reference</value>
            <ref bean="myDataSource" />
        </list>
    </property>
    <!-- results in a setSomeMap(java.util.Map) call -->
    <property name="someMap">
        <map>
            <entry key="an entry" value="just some string"/>
            <entry key="a ref" value-ref="myDataSource"/>
        </map>
    </property>
    <!-- results in a setSomeSet(java.util.Set) call -->
    <property name="someSet">
        <set>
            <value>just some string</value>
            <ref bean="myDataSource" />
        </set>
    </property>
</bean>

```

​	map的key值或value值，或set值，也可以是以下任何元素

```xml
bean | ref | idref | list | set | map | props | value | null
```





##### 6. Null and Empty String Values

​	Spring将属性等的空参数视为空字符串。下面这个基于XML的配置元数据片段将`email`属性设置为空字符串值（“”）

```xml
<bean class="ExampleBean">
	<property name="email" value=""/>
</bean>
```

​	前面的例子相等于下面的Java代码
```java
ExampleBean exampleBean = new ExampleBean();
exampleBean.setEmail("");
```

​	`<null/>`元素处理`null`值

```xml
<bean class="ExampleBean">
    <property name="email">
        <null/>
    </property>
</bean>

```

​	上面的配置等同于以下Java代码

```java
exampleBean.setEmail(null);
```

​	





##### 7. 使用p命名空间的XML快捷方式

​	`p-namespace`（命名空间）让你使用`bean`元素的属性来描述你的属性值合作Bean，或者两种都是

​	`Spring`支持具有命名空间的可扩展配置格式，这些命名空间是基于`XML Schema`定义的。`p-namespace`没有在XSD文件中定义，只存在于Spring的核心（core）中

​	下面的例子显示了两个XML片段（第一个使用标准的XML格式，第二个使用p-namespace），它们的解析结果相同：

```xml
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:p="http://www.springframework.org/schema/p"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean name="classic" class="com.example.ExampleBean">
        <property name="email" value="someone@somewhere.com"/>
    </bean>

    <bean name="p-namespace" class="com.example.ExampleBean"
        p:email="someone@somewhere.com"/>
</beans>

```

​	接下来的例子包括了另外两个Bean定义，它们都有对另一个Bean的引用

```xml
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:p="http://www.springframework.org/schema/p"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean name="john-classic" class="com.example.Person">
        <property name="name" value="John Doe"/>
        <property name="spouse" ref="jane"/>
    </bean>

    <bean name="john-modern"
        class="com.example.Person"
        p:name="John Doe"
        p:spouse-ref="jane"/>

    <bean name="jane" class="com.example.Person">
        <property name="name" value="Jane Doe"/>
    </bean>
</beans>

```

​	注意第二个Bean定义使用`p:spouse-ref="jane"`作为对另一个bean的引用



##### 8. 使用c命名空间的XML快捷方式

​	忽略不看，与上面类似，只不过c命名空间用于简化`<constructor-arg/>`



##### 9.复合属性名

​	当你设置Bean属性时，可以使用复合或嵌套的属性名。只要路径中除最终属性名外的所有组件不为null

```xml
<bean id="something" class ="things.ThingOne">
    <property name = "fred.bob.sammy" value = "123"/>
</bean>
```

​	`something` Bean有一个 `fred` 属性，它有一个 `bob` 属性，它有一个 `sammy` 属性，最后的 `sammy` 属性被设置为 `123` 的值。为了使这个方法奏效，`something` 的 `fred` 属性和 `fred` 的 `bob` 属性在构建 bean 后不能为 `null`。否则就会抛出一个 `NullPointerException`。



#### 2.4.3 使用depends-on

​	`depends-on`属性可以明确地强制一个或多个Bean在使用次元素的Bean被初始化之前初始化。下面的例子使用`depends-on`属性来表达单个`bean`的依赖性

```xml
<bean id="beanOne" class="ExampleBean" depends-on="manager"/>
<bean id="manager" class="ManagerBean" />
```

​	`depends-on`是一种“强制初始化顺序和销魂顺序的控制机制“，上面的例子流程如下：

```xml
初始化：
manager → beanOne

销毁：
beanOne → manager
```

​	depends-on 不改变对象关系，只控制 Bean 初始化和销毁的执行顺序。

​	要表达多个Bean的依赖，请提供一个`Bean`名称的列表作为`depends-on`属性的值（逗号、空格和封号是有效的分隔符）

```xml
<bean id="beanOne" class="ExampleBean" depends-on="manager,accountDao">
    <property name="manager" ref="manager" />
</bean>

<bean id="manager" class="ManagerBean" />
<bean id="accountDao" class="x.y.jdbc.JdbcAccountDao" />

```

​	`<depends-on>`只保证这些Bean必须在我（`beanOne`）之前初始化，并不保证`manager`和`accountDao`之间的顺序，同样的，销毁也是，只保证先销毁`bean`，再销毁`<depends-on>指定的Bean`列表（不保证顺序）



#### 2.4.4 懒加载的Bean	

​	默认情况下，`ApplicationContext` 的实现会急切地创建和配置所有的 单例 Bean，作为初始化过程的一部分。一般来说，这种预实例化是可取的，因为配置或周围环境中的错误会立即被发现，而不是几小时甚至几天之后。当这种行为不可取时，你可以通过将Bean定义标记为懒加载来阻止单例Bean的预实例化。**懒加载的 bean 告诉IoC容器在第一次被请求时创建一个bean实例，而不是在启动时**。

​	在XML中，这种行为是由`<bean/>`元素上的`lazy-init`属性控制的

```xml
<bean id="lazy" class="com.something.ExpensiveToCreateBean" lazy-init="true"/>
<bean name="not.lay" class="com.something.AnotherBean"/>
```

​	当前面的配置被 `ApplicationContext` 消耗时，当 `ApplicationContext` 启动时，`lazy` Bean不会被急切地预实化，而 `not.lazy` Bean则被急切地预实化了

​	然而，当懒加载Bean是未被懒加载的单例Bean的依赖关系时，`ApplicationContext` 会在启动时创建懒加载 Bean，因为它必须满足单例的依赖关系。懒加载的 Bean 被注入到其他没有被懒加载的单例 Bean中。**也就是说，如果懒加载的Bean被依赖，`lazy-init会失效`**

​	也可以通过使用`<beans/>`元素上的`default-lazy-init`属性来控制容器级的懒加载：

```xml
<beans default-lazy-init="true">
    <!-- no beans will be pre-instantiated... -->
</beans>
```

​	





#### 2.4.5 注入协作者（Autowiring Collaborators）

​	`Spring`容器可以自动连接协作Bean之间的关系。你可以让`Spring`通过检查`ApplicationContext`的内容为你的Bean自动解决协作者（其他Bean或依赖）

​	自动注入有以下优点：**自动注入可以大大减少对指定属性或构造函数参数的需要。自动注入可以随着你的对象的发展而更新配置。如果你需要给一个类添加一个依赖，这个依赖可以自动满足，而不需要你修改配置。**

​	当使用基于XML的配置元数据时，可以使用`<bean/>`元素的`autowire`属性来指定bean定义的自动注入模式。自动注入模式有4种功能，你可以为每个Bean指定自动注入，从而选择哪些要自动注入：

1. **no**

​	（默认）没有自动注入。Bean引用必须由`ref`元素来定义，对于大型部署来说，不建议改变默认设置，因为明确协作者（依赖）会带来更大的控制力和清晰度。在某种程度上，它记录了一个系统的结构

2. **byName**

​	通过属性名称进行自动注入，`Spring`寻找一个需要自动注入的属性同名的Bean。例如，一个`Bean`定义被设置为按名称自动注入，并且它包含一个`master`属性（也就是说，它有一个`setMaster(...)`方法），Spring会寻找一个名为`master`的Bean定义并使用它来设置该属性。

​	假设这是一个包含`master`属性的类，并且只能通过Setter依赖注入，也就是有一个`setMaster`的set方法

```java
public class ExampleBean{
    private  Master master;
    
    public void setMaster(Master master){
        this.master = master;
    }
}
```

​	在之前使用XML进行依赖注入的过程是这样。

```xml
<bean id ="exampleBean" class="ExampleBean">
	<property name="master" ref ="masterBean"/>
</bean>
<bean id="masterBean" class ="Master"/>
```

​	现在使用按名称自动注入，变体是这样

```xml
<bean id ="exampleBean" class="ExampleBean" autowire="byName">
</bean>
<bean id="master" class ="Master"/>
```

​	Spring会反射扫描这个类。找到`setter`方法：`setMaster(...)` ,然后Spring会根据名字`Master`去寻找id为`master`的bean，注入到这个Bean中

​	`autowire="byName"`的过程是：

```xml
1. 解析 Bean：ExampleBean
2. 找 setter 方法：setMaster(...)
3. 提取属性名：master
4. 在容器中查找 Bean id = master
5. 找到则注入，没有则不处理
```



3.**byType**

​	如果容器中正好有一个`property`类型的`bean`存在，就可以自动注入该属性。如果存在一个以上的`bean`，就会抛出一个致命的`exception`。如果没有匹配的`bean`，就不会发送任何事情

​	`byType`和`byName`的区别是，一个是通过反射查看setter方法属性，一个是通过反射查看setter方法的名字。	

​	核心逻辑总结：

```xml
1. 找 setter 方法
2. 提取参数类型
3. 在容器中按类型查 Bean
4. 判断结果：
   - 1个 → 注入
   - 多个 → 报错
   - 0个 → 不注入
```

> Notice : byType自动注入只针对于Bean

4.**constructor**

​	类似于byType，但适用于构造函数参数。如果容器中没有构造函数参数类型的bean，就会产生一个致命的错误。

​	如果有这么一个类：

```java
public class ExampleBean{
    private  Master master;
    
    public ExampleBean(Master master){
        this.master = master;
    }
}
```

​	那么它对应的自动注入XML元数据配置则是：

```xml
<bean id = "exampleBean" class="ExampleBean" autowire= "constructor"/>

<bean id="master" class ="Master"/>
```

​	`Spring`会通过反射读取类的结构，识别到构造函数需要一个`Master.class`的参数，就会去容器中寻找类型为`Master.class`的bean（也就是`class="Master"`），然后注入进去。

> byName      → 按 Bean id 匹配
> byType      → 按 Bean 类型匹配（setter）
> constructor → 按 Bean 类型匹配（构造器）

​	通过 `byType` 或 `constructor` 自动注入模式，你可以给数组（array）和泛型集合（collection）注入。在这种情况下，容器中所有符合预期类型的自动注入候选者都被提供来满足依赖。如果预期的key类型是 `String`，你可以自动注入强类型的 `Map` 实例。自动注入的 `Map` 实例的值由符合预期类型的所有 bean 实例组成，而 `Map` 实例的key包含相应的 bean 名称。

​	例如，有一个类：

```java
public class ExampleBean2{
    private  List<Master> list;
    
    public ExampleBean2(List<Master> list){
       this.list = list;
    }
}
```

​	对应的XML配置元数据

```xml
<bean id = "exampleBean2" class = "ExampleBean" autowire = "constructor"/>

<bean id = "master1" class = "Master"/>
<bean id = "master2" class = "Master"/>
<bean id = "master3" class = "Master"/>
<bean id = "master4" class = "Master"/>
```

​	这种情况下，这4个类型为`Master`的Bean都将被注入到id为`exampleBean2`的Bean中去。

​	而`Map`注入，只需要记住，`key`是bean的`id`，`value`是bean实例。例如：

```java
private Map<String, Master> masters;
```

```xml
<bean id="a" class="Master"/>
<bean id="b" class="Master"/>
```

​	Spring注入结果：

```xml
masters = {
  "a" → a对象,
  "b" → b对象
}
```

​	

##### 1. 自动注入的限制和缺点

​	当自动注入在整个项目中被一致使用时，它的效果最好。如果自动注入没有被普遍使用，那么只用它来注入一个或两个Bean定义可能会让开发者感到困惑。

考虑自动注入的限制和弊端。

- `property` 和 `constructor-arg` 设置中的明确依赖关系总是覆盖自动注入。你不能自动注入简单的属性，如基本数据、`String` 和 `Class`（以及此类简单属性的数组）。这个限制是设计上的。
- 自动注入不如显式注入精确。尽管正如前面的表格中所指出的，Spring很小心地避免在模糊不清的情况下进行猜测，这可能会产生意想不到的结果。你的Spring管理的对象之间的关系不再被明确地记录下来。
- 对于可能从Spring容器中生成文档的工具来说，注入信息可能无法使用。
- 容器中的多个Bean定义可以与setter方法或构造参数指定的类型相匹配，以实现自动注入。对于数组、集合或 `Map` 实例，这不一定是个问题。然而，对于期待单一值的依赖关系，这种模糊性不会被任意地解决。如果没有唯一的Bean定义，就会抛出一个异常。

在后一种情况下，你有几种选择。

- 放弃自动注入，改用明确注入。
- 通过将bean定义的 `autowire-candidate` 属性设置为 `false` 来避免bean定义的自动注入，如 [下一节](https://springdoc.cn/spring/core.html#beans-factory-autowire-candidate) 所述。
- 通过将 `<bean/>` 元素的 `primary` 属性设置为 `true`，将单个Bean定义指定为主要候选者。
- 实现基于注解的配置所提供的更精细的控制，如 [基于注解的容器配置]() 中所述。



##### 2.从自动注入中排除一个Bean

​	在每个`Bean`的基础上，你可以将一个bean排除在自动注入外。在`Spring`的XML格式中，将`<bean/>`元素的`autowire-candidate`属性设置为false。**容器使特定的Bean定义对自动注入基础设施不可用（包括注解配置，如`@Autowired`）**

> Note
>
> `autowire-candidate` 属性被设计为只影响基于类型的自动注入。它不影响通过名称的显式引用，即使指定的 bean 没有被标记为 autowire 候选者，它也会被解析。因此，如果名称匹配，通过名称进行的自动注入还是会注入一个Bean。

​	也可以根据对Bean名称的模式匹配来现在`autowire`候选人，顶层的`<beans/>`元素在其`default-autowire-candidates`属性接收一个或多个模式。例如，要将自动注入候选状态限制在名称以`Repository`结尾的任何`bean`，请提供`*Respository`的值。要提供多个这样的模式，请用逗号分隔的列表定义它们。***Bean定义的`autowire-candidate`属性的明确值为true或false，这样的设置优先级高于模式匹配规则。**

​	**这并不意味着排除在外的Bean本身不能使用`autowiring`进行配置，相反，Bean本身不是自动注入到其他Bean的候选人**。
