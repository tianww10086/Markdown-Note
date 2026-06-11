# Spring IoC 容器学习路线建议

> 适用对象：民办专升本大三学生，2026年6月，找实习中，正在学习 Spring Framework 基础框架。

---

## 当前学习进度

IoC 容器章节共 16 节，目前学到 **1.9 基于注解的容器配置**。

| 章节 | 内容 |
|------|------|
| 1.1 | IoC容器和Bean简介 |
| 1.2 | 容器概述 |
| 1.3 | Bean概览 |
| 1.4 | 依赖 |
| 1.5 | Bean Scope |
| 1.6 | 自定义Bean的性质 |
| 1.7 | Bean定义的继承 |
| 1.8 | 容器扩展点 |
| **1.9** | **基于注解的容器配置** ← 当前位置 |
| 1.10 | Classpath扫描和管理的组件 |
| 1.11 | 使用JSR 330标准注解 |
| 1.12 | 基于Java的容器配置 |
| 1.13 | Environment 抽象 |
| 1.14 | LoadTimeWeaver |
| 1.15 | ApplicationContext 附加功能 |
| 1.16 | BeanFactory API |

---

## 一、实习生面试和日常工作必备（必须吃透）

### 1.1 IoC容器和Bean简介

- IoC 是什么、DI 是什么——面试必问。要能用自己的话讲清楚"对象创建控制权从程序转移到容器"。
- Bean 的定义：由 Spring 容器实例化、组装、管理的对象。

### 1.2 容器概述

- `ApplicationContext` 是核心接口。
- **重点掌握 `AnnotationConfigApplicationContext`**，`ClassPathXmlApplicationContext` 知道历史存在即可。
- 理解容器做的事情：读取配置 → 实例化 Bean → 注入依赖。

### 1.3 Bean 概览

- Bean 的命名规则（id / name）。
- Bean 的实例化方式（构造器、静态工厂方法）。
- 面试偶尔会问"Bean 有几种实例化方式"。

### 1.4 依赖 —— 整个 Spring 的灵魂

- **构造器注入 vs Setter 注入**，各自优缺点（面试高频）。
- 循环依赖问题（面试高频）。
- `ref` 引用其他 Bean。
- 集合注入（List / Map / Set）了解即可。

### 1.5 Bean Scope

- **singleton**（默认，整个容器只有一个实例）。
- **prototype**（每次获取都新建）。
- request / session / application（Web 环境下的 Scope，知道存在即可）。

### 1.9 基于注解的容器配置 —— 当前章节，必须吃透

- **`@Autowired`**：最核心的自动注入注解。
- **`@Qualifier`**：多个同类型 Bean 时指定名称。
- **`@Value`**：注入外部属性值。
- **`@Resource`**：JSR-250 标准注解，与 `@Autowired` 的区别（面试高频）。
- `@Autowired` 可以用在构造器、Setter、字段上。**构造器注入是现代最佳实践**。

### 1.10 Classpath扫描和管理组件

- **`@Component`、`@Service`、`@Repository`、`@Controller`**：日常工作的基础，天天写。
- `@ComponentScan`：组件扫描。

### 1.12 基于Java的容器配置

- **`@Configuration` + `@Bean`**：用 Java 代码替代 XML 配置。
- `@Bean` 方法的返回值自动注册到容器。
- 与 Spring Boot 自动配置紧密相关。

### 1.13 Environment 抽象（挑重点）

- `@PropertySource` 加载 .properties 文件。
- `@Profile` 区分环境（dev / test / prod），实际项目必用。

---

## 二、目前用不上，可以跳过/了解的

| 章节 | 原因 |
|------|------|
| **1.6 自定义Bean的性质** | `InitializingBean` / `DisposableBean` 等生命周期回调，实际开发中很少自己实现。了解 `@PostConstruct` / `@PreDestroy` 即可。 |
| **1.7 Bean定义的继承** | XML 时代的产物，注解时代几乎没人用。直接跳过。 |
| **1.8 容器扩展点** | `BeanPostProcessor` / `BeanFactoryPostProcessor` 是框架层面的东西，框架开发者才需要。业务开发基本不写，实习生不用深究。 |
| **1.11 JSR 330标准注解** | `@Inject` / `@Named` 是 Java 标准注解，实际开发 99% 的人用 `@Autowired` / `@Qualifier`。知道存在即可。 |
| **1.14 LoadTimeWeaver** | 非常冷门，与 AOP 和 AspectJ 的加载时织入有关。完全跳过。 |
| **1.15 ApplicationContext 附加功能** | 国际化（MessageSource）、事件发布等。用到时再学。 |
| **1.16 BeanFactory API** | 知道 `BeanFactory` 是 `ApplicationContext` 的底层父接口即可，日常开发直接用 `ApplicationContext`。 |

---

## 三、现代开发的地基（需要形成肌肉记忆）

### 1. 依赖注入思想本身

不管你未来用 Spring、Guice 还是 Quarkus，IoC/DI 是现代 Java 框架的共同基石。**理解"不是我 new 你，而是别人把你给我"这个思想**，比记住注解更重要。

### 2. 构造器注入 > 字段注入

```java
// 推荐：构造器注入（Spring 4.3+ 单构造器时可省略 @Autowired）
@Service
public class UserService {
    private final UserRepository userRepository;

    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }
}

// 不推荐但常见：字段注入
@Service
public class UserService {
    @Autowired
    private UserRepository userRepository;
}
```

构造器注入的好处：字段可声明为 final（不可变）、测试友好（可手动 new 并传入 mock）、不会出现 NPE。

### 3. 从 XML → 注解 → 自动配置的演进脉络

```text
XML 配置  →  注解配置（@Component / @Autowired）  →  自动配置（Spring Boot，几乎不用写配置）
```

理解这个演进，你就能理解 Spring Boot 到底在"自动"什么——它帮你做了组件扫描和默认 Bean 注册。

### 4. 分层注解体系

```text
@Controller   → 表现层（接收 HTTP 请求）
@Service      → 业务逻辑层
@Repository   → 数据访问层（自动转换 JDBC 异常）
@Component    → 通用组件（以上三个本质都是 @Component 的特化）
```

这四个注解是日常写代码的起点。

### 5. 配置的优先级和覆盖关系

实际项目中经常需要"默认配置 + 按环境覆盖"。理解 `@Profile`、`application.properties` → `application-dev.properties` 的覆盖关系，是进入项目的必备前置知识。

---

## 四、给你的学习顺序建议

```text
1.4 依赖        ──→ 当前最重要，反复看、反复写代码
1.9 注解配置    ──→ 当前章节，动手写 Demo 验证每个注解的效果
1.10 组件扫描   ──→ 学完立刻和 1.9 结合使用
1.12 Java配置   ──→ 学会用 @Configuration + @Bean 替代 XML
1.13 环境抽象   ──→ 重点看 @Profile 和 @PropertySource
然后              ──→ 立刻转向 Spring Boot，写一个能放到简历上的项目
```

### 关于 XML 配置

只练到"能读懂老项目代码"的程度即可，不需要自己手写。2018 年以后的新项目基本不会再新建 XML 配置。

### 最重要的建议

啃完 1.4、1.9、1.10、1.12 之后，**不要继续深挖 IoC 的犄角旮旯**。立刻转身去学 Spring Boot，写一个完整的小项目（比如一个带数据库的 REST API），放到简历上。一个能跑的 Spring Boot 项目，抵得过你把 IoC 容器 16 个章节全部背下来。
