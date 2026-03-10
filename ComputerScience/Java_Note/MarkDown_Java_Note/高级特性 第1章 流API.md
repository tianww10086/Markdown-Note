	Java 8引入了Stream API，与集合相比，流提供了一种让我们在更高的概念级别上指定计算任务的数据视图，通过使用流，可以指明想要完成的任务。Stream API提供了对集合、数组和文件等数据源的高效操作，支持过滤、排序、映射、聚合等功能。





## 1.1 从迭代到流的操作

​	在处理集合时，我们通常会迭代遍历它的元素，并在每个元素上执行某项操作。例如，假设我们想要对某本书中所有长单词进行计数。首先会将单词放到一个列表中：

```java
var contents = Files.readString(Path.of("alice.txt"));  //Read file into String
List<String> words = List.of(contends.split("\\PL+"));
```

现在迭代它：

```java
int count =0;
for(String w:words)
    if(w.length()>12)
        count++;
```

而下面是使用流的操作：

```java
long count = words.stream().filter(w->w.length()>12).count;
```

​	只需一步，便统计好了单词长度大于12的所有单词。现在我们不必扫描整个代码区查找过滤和计数操作，方法名就可以直接告诉我们其代码意欲何为。而且，循环需要非常详细地指定操作的顺序，而流却能够以其想要的任何方式来调度这些操作，只要结果是正确的即可。

​	仅将stream修改为paralleStream就可以让流库以并行方式来执行过滤和计数

```java
long count = words.paralleStream().filter(w->w.length()>12).count;
```

​	流遵循了"做什么而非怎么做"的原则。在流的示例中，我们描述了需要做什么：获取长单词，并对他进行计数。

​	流表面上看起来和集合很类似，都可以让我们转换和获取数据。但是，它们之间存在着显著的差异：

1. 流并不存储其元素。这些元素可能存储在底层的集合中，或者是按需生成的。
2. 流的操作不会修改其数据源。例如，==filter方法不会从流中移除元素，而是会生成一个新的流，其中不包含被过滤掉的元素。==
3. 流的操作是尽可能惰性执行的。这意外着直至需要结果时，操作才会执行。

​	回头看示例，stream和paralleStream方法会产生一个用于words列表的流。==filter方法会返回另一个流。其中只包含长度大于12的单词。count方法会将这个流约简为一个结果==

​	这个工作流是操作流的典型流程。我们建立了一个包含三个阶段的操作通道：

1. 创建一个流
2. 指定将初始流转换位其他流的中间操作，可能包含多个步骤。
3. 应用终止操作，从而参数结果。这个操作会强制执行之前的惰性操作。从此之后，这个流就再也不能用了。

下面的程序中，流是用stream或paralleStream方法创建的。filter方法对其进行转换，而count方法是终止操作。

```java
package SteamAPI;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class CountLongWord  {
    public static void main(String[] args) throws IOException {
        var contents = Files.readString(Path.of("resource\\Alice.txt"));
        List<String> words = List.of(contents.split("\\PL+"));

        long count = 0;
        //ForEach方法操作
        for(String w:words)
        {
            if(w.length()>12)
                count++;
        }
        System.out.println("count = "+count);
		
        //流API操作
        count = words.stream().filter(w-> w.length()>12).count();
        System.out.println("count = "+count);


		
        count = words.parallelStream().filter(w-> w.length()>12).count();
        System.out.println("count = "+count);
    }
}

```

​	在下一届中，你将会看到如何创建流；后续的三节将讨论流的转换；再后面的五节将讨论终止操作。

**`Java.util.stream.Stream<T>`**

```java
Stream<T> filter(Predicate<? super T> p)
    产生一个流，其中包含当前流中满足p的所有元素
long count()
    产生当前流中元素的数量。这是一个终止操作
```

**`Java.util.Collection<E>`**

```java
default String<E> stream();
default String<E> paralleStream();
	产生当前集合中所有元素的顺序流或并行流。
```



## 1.2 流的创建

​	==**`Collection`接口的stream方法可以将任何集合转换为一个流**==。如果你有一个数组，那么可以转而使用静态的Stream.of方法

```java
Stream<String> words = Stream.of(contents.split("\\PL+"));//contents是一个字符串
```

​	of方法具有可变长参数，因此我们可以构建具有任意数量的流：

```java
Stream<String> song = Stream.of("Gently","down","the","stream");
```

​	使用Array.stream(array,from,to)可以用数组中的一部分元素来创建一个流。

​	为了创建不包含任何元素的流，可以使用静态的Stream.empty方法：

```java
Stream<String> silence = Stream.empty();
```

​	**Stream接口有两个用于创建*无限流*的静态方法**。`generate`方法会接受一个不包含任何引元的函数（从技术上将，是一个`Supplier<T>`接口的对象。该接口用于表示**无需参数但返回结果**的供应者操作

```java
Stream<String> echos = Stream.generatr(()->"Echo"); //创建了一个无限重复自付出"Echo"的流
```

​	或者像下面这样获取一个随机数的流：

```java
Stream<Double> randoms = Stream.generate(Math::random); // 创建了一个无限生成随机数的流
```

​	

​	如果要产生像0 1 2 3 ...这样的序列，**可以使用iterate方法。它会接受一个种子，以及一个函数（从技术上将，是一个UnaryOperator\<T>接口，并且会反复地将该函数应用到之前的结果上。**UnaryOperator接口用于表示**对同一类型T的输入值进行转换，并返回相同类型T的结果**，例如：

```java
Stream<BigInteger> integers = Stream.iterate(BigInteger.ZERO, n ->n.add(BigInteger.ONE)); //创建了一个无限生成有序序列的流。
```

​	该序列中第一个元素是种子BigInteger.ZERO （0）,第二个元素是（0+BigInteger.ONE)1。后续以此类推

​	想要访问无限流中的元素，可以使用`forEach`方法遍历每个元素，forEach方法需要的是一个实现了Consumer接口的类，lambda表达式或匿名类。`Consumer`接口用于表示**接受单个输入参数且不返回结果的操作**

```java
        Stream<Integer> stream = Stream.iterate(0, n -> n + 1);
        stream.forEach(n ->System.out.println(n)); //forEach会遍历该流的每一个元素
```

​		

​	如果要产生一个有限序列，则需要添加一个谓词来描述迭代应该如何结束:

```java
var limit = new BigInteger("100000000");
Stream<BigInteger> integers = Stream.iterate(BigInteger.ZERO, n -> compareTo(limit) < 0,n -> n.add(BigInteger.ONE));
```

​	只要该谓词拒接了某个迭代生成的值，这个流即结束。

​	最后，`Stream.ofNullable`方法会用一个对象来创建一个非常短的流。如果该对象为null，那么这个流的长度就为0，否则这个流的长度为1，即只包含该对象。这个方法与flatMap相结合时最有用。

​	下面是三个参数的`Stream.iterate`方法的正确签名：

```java
static <T> Stream<T> iterate(T seed,Predicate<T> hashNext,UnaryOperator<T> next);
```

**seed**  ：起始值（BigInteger.ZERO)

**hashNext**:一个断言（Predicate），判断是否继续生成元素

**next** : 一个函数（UnaryOperator)，用于生成下一个元素。

其中`Predicate`接口代表一个布尔值函数（判断条件），接受一个参数并返回`boolean`值。只有当hashNext为真时，才会继续生成元素



```java
注释：JavaAPI中有大量方法都可以产生流。例如，String类方法有一个lines方法，它会产生由一个字符串中所有的行构成的流。
    Stream<String> greetings = "Hello\nGuten Tag\nBonjour".lines();
	如果我们有一个Iterator对象，并且希望得到一个由它的结果构成的流，那么可以使用下面的语句：
    StreamSupport.stream(Spliterators.spliteratorUnknownSize(iterator,Spliterator.ORDERED),false);
```

​	要想查看本节流中的内容，可以使用**toList方法**。**它会将流中的元素收集到一个列表中。就像count一样，toList也是一个终止操作。如果流是无限的，那么首先要用limit方法截断它**：

```java
System.out.println(Stream.generate(Math::random).limit(10).toList());
```

​	可以使用==forEach方法遍历处理每一个元素，如输出==

```java
	    Stream<Integer> stream = Stream.iterate(0, n -> n + 1);
        stream.forEach(n ->System.out.println(n)); //forEach会遍历该流的每一个元素
```



下面的程序展示了创建流的各种方式

```	java
package StreamAPI;

import java.io.IOException;
import java.math.BigInteger;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.function.UnaryOperator;
import java.util.regex.Pattern;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class CreatingStreams {


    public static void main(String[] args) throws IOException {
        //打开一个文件
        Path path = Path.of("resource\\text\\Alice (Henry Christina) (Z-Library).txt");
        String contents = Files.readString(path); //从该文件中读取所有的字符串

       // 将一个字符串分割成单词，并创建一个字符串流（Stream）。
        Stream<String> words = Stream.of(contents.split("\\PL+"));
        show("words",words);

        //Stream.of方法会根据参数创建一个有限流
        Stream<String> song = Stream.of("gently","down","the","stream");
        show("song",song);

        //创建一个空流
        Stream<String> silence = Stream.empty();
        show("silence",silence);

        //创建一个无线流，该流的元素全是Echo
        Stream<String> echos = Stream.generate(() ->"Echo");
        show("echos",echos);

        //创建一个无限流，该流的元素又Math::random方法生成
        Stream<Double> randoms = Stream.generate(Math::random);
        show("randoms",randoms);

        //创建一个有序的无线流，从BigInteger.ZERO开始，每次都会将后面的函数应用到之前的结果
        Stream<BigInteger> integers = Stream.iterate(BigInteger.ZERO,
                n -> n.add(BigInteger.ONE));
        show("integers",integers);

        //String类的lines方法会参数一个由字符串中所有行构成的流
        Stream<String> greetings="Hello\nGuten tag\nBonjour".lines();
        show("greetings",greetings);

        //将字符串 contents 按非字母字符分割，并返回一个包含所有单词的流。
        Stream<String> wordsAnotherWay = Pattern.compile("\\PL+").splitAsStream(contents);
        show("wordsAnotherWay",wordsAnotherWay);

        //带资源的try语句，无论是否发生异常最后都会关闭该资源
        try(Stream<String> lines = Files.lines(path)){
            show("lines",lines);
        }
		
        Iterable<Path> iterable = FileSystems.getDefault().getRootDirectories();//获取windowns系统的跟目录迭代器
        Stream<Path> rootDirectories = StreamSupport.stream(iterable.spliterator(),false);
        show("rootDirectories",rootDirectories);


    }


    //展示流的前10个元素。
    public static <T> void show(String title,Stream<T> stream){
        final int SIZE=10;
        //通过toList和limit方法阶段无线流的前十个元素
        List<T> list = stream.limit(SIZE+1).toList();
        //便利输出该集合
        for(int i=0; i<list.size(); i++){

            if(i>0){
                System.out.print(",");
            }
            if(i<SIZE)
                System.out.print(list.get(i));
            else
                System.out.print("...");
        }
        System.out.println();
    }

}

//该接口用于给传入的参数做出处理并返回。
class IteratorUnaryOperator implements UnaryOperator<BigInteger>{

    @Override
    public BigInteger apply(BigInteger integer) {
        return integer.add(BigInteger.ONE);
    }
}


```



**`Java.util.stream.Stream`**	

```java
static <T> Stream<T> of(T....values)
    产生一个元素为给定值的流。
static <T> Stream<T> empty()
    产生一个不包含任何元素的流。
static <T> Stream<T> generate(Supplier<T> s)
    产生一个无限流，它的值是通过反复调用函数s而构成的
static <T> Stream<T> iterate(T seed, UnaryOperator<T> f)
    返回一个无线流，seed为初始值，f是变化函数 seed = f(seed);
static <T> Stream<T> iterate(T seed, Predicate<? super T> hashNext,UnaryOperator<T> f)
    返回一个无线流，seed为初始值，通过判断t是否是否某个条件，如果符合就使T产生变化，变化的结果由f决定。反正T不合法条件停止生成
static <T> Stream<T> ofNullable(T t)
    如果t为null，返回一个空流，否则返回包含t的流。
```

**`Java.util.Arrays`**

```java
static <T> Stream<T> stream(T[] array, int startInclusive, int endExclusive)
    产生一个流，它的元素是由数组中指定范围内的元素构成的。
```

**`Java.lang.String`**

```java
Static Stream<String> lines()
    产生一个流，它的元素是由该字符串中的所有行构成的。
```

**`Java.nio.file.Files`**

```java
static Stream<String> lines(Path path)
static Stream<String> lines(Path path,Charset cs)
    产生一个流，它的元素是指定文件中的行，该文件的字符集为UTF-8，或者为指定的字符集
```

**`Java.util.stream.StreamSupport`**

```java
static <T> Stream<T> stream(Spliterator<T> spliterator,boolean parallel)
    产生一个流，它包含了由给定的可分割迭代器产生的值
```

**`Java.Lang.Iterable`**

```java
Spliterator<T> spliterator()
    为这个Iterable产生一个可分割的迭代器，默认实现不分割也不报告尺寸。
```



## 1.3 filter、map和flatMap方法

#### 1.3.1 filter方法

​	==filter、map和flatmap都属于中间方法，会对一个流的所有元素进行某种操作==，这个操作由接口提供，作为使用者需要实现这个接口。

​	流的转换会产生一个新的流，它的元素派生自另一个流的元素。`filter`转换会产生一个新流，它的元素与某种条件相匹配：

```java
List<String> words  = ....;
//只有当这个单词的长度大于12才会生成一个元素
Stream<String> longwords = words.stream().filter( w -> w.length() >12); 
```

​	`filter`的引元是一个`Predicate<T>`类型的对象，即一个从T映射到boolean值的函数。下面是匿名内部类的写法

```java    
List<String> words = "";
Stream<String> longwords = words.stream().filter(
	new Predicate<String>(){
        
    }
)
```



#### 1.3.2 map方法

​	==如果我们想要按照某种方式（函数）来转换流中的值，可以使用map方法并传递执行该转换的函数==。例如，我们可以将所有单纯转换为小写

```java
Stream<String> lowercaseWords = words.stream().map(String::toLowerCase);
```

​	这里使用的是方法引用来满足map参数，通常我们会使用lambda表达式来代替：

```java
Stream<String> firstLetters = words.stream().map(s ->substring(0,1)); //将每个元素生成为原来单词下标为0~1的单词
```

​	map方法的参数是一个`Function<T,R>`接口，而该接口用于处理一个T类型参数的函数，然后返回R参数。下面是用匿名内部类方法实现的代码；

```java
       //内部类实现接口
       Stream<String> firstLetters  = words.stream().map( new Function<String,String>(){
           @Override
           public String apply(String s) {
               return s.substring(0,1);
           }
       });
```





​	

​	现在，假设我们有这样一个映射函数，它返回的是一个任意的结果或多个结果。考虑下面这个示例，==`codePoints`方法会产生一个字符串中所有的编码点==，例如`codePoints("Hello🌏")`返回的流由`"H","e","l","l","o","🌏"`构成

​	`codePoints`如何收集多个结果？对于流API，最自然的方式是让方法返回一个`Stream<String>`对象，假设我们将`codePoints`方法映射到一个字符串流上：

```java
List<String> words = new ArrayList<>();
words.add("your");
 words.add("boat");
words.add("home");

//注意，假设有这么一个codePoints方法，它会返回一个流，这个流由该字符串各个单位构成
Stream<Stream<String>> result = words.stream.map(w -> codePoints(w));
```

​	那么会得到一个包含流的流， 就像`[ ["y","o","u","r"], [.....],...]`。 

​	==而使用flatMap方法，可以将其摊平为单个流`[...."y","o","u","r",....]`==

​	下面考虑`codePoints`方法的具体实现，`String`类有一个`codePoints`方法，它会产生一个由整数编码点构成的流：

```java
"Hello🌏".codePoints(); //A stream of Integers 72 101 108 108 111 32 127760
```

​	接下来，将每个整数都转换为一个字符串，其中包含了由给定的编码点的Unicode字符。遗憾的是，其技术是个难题。`codePoints`方法产生一个`IntStream`，可以使用`mapToObj`方法来转换这些元素。没有其他更便捷的方法可以将一个整数编码点转换成一个字符串吗？：

```java
    public static Stream<String> codePoints(String s){
        return s.codePoints().mapToObj(cp -> new String(new int[]{cp},0,1));
    }
/*
代码解析：
1. s.codePoints会返回一个IntStream流，其中的每一个元素是字符串中的一个Unicode代码点
2. mapToObj()函数需要一个IntFunction接口，该接口代表接受一个整数值作为参数并产生结果的函数
3. mapToObj(cp -> new String(new int[]{cp},0,1)) 这里cp代表每个代码点的整数值
	将每个代码点映射为一个字符串对象，这里使用了一个String的构造函数 ：String(int[] codePoints,int offset,int count); 这个函数通过一个代码点数组来创建字符串
*/
```

​	为了方便分析，我们先将这个方法转换为内部类实现的形式

```java

public static Stream<String> codePoints(String s){
    return s.codePoints().mapToObj(new IntFunction<String>() {
        @Override
          public String apply(int value) {
               String  str= new String(new int[]{ value},0,1);
                return str;
       }
 });
```

​	第一步由字符串方法codePoints返回包含整数码的一个流，然后用mapToObj中间方法来处理这个流。其中`mapToObj`方法的参数是一个`IntFunction<R>`接口，该接口的方法接受一个整型参数，并返回R类型值。

​	注意String类的构造方法，下面是这个构造方法的签名，该构造方法的作用是分配一个新的String，其中包含来自Unicode代码点数组参数的子数组的字符。offset参数是子数组的第一个代码点的索引，count参数指定子数组的长度。

```java
/*
	方法签名 : public String(int[] codePoints,int offset,int count)

*/
public class StringCodePoints {

    public static void main(String[] args) {
        int arr[] = {65,66,67,68,69};
        System.out.println(new String(arr,0,5)); //将输出ABCDE
    }
}
```

​	所以`codePoints`方法的功能是将一个字符串变为流的形势。

​	

​	下面是这个方法的整体示例：

```java
package StreamAPI;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.function.IntFunction;
import java.util.stream.Stream;

public class MapStream {
    public static void main(String[] args) throws IOException {
        //打开一个文件
        Path path = Path.of("resource\\text\\Alice.txt");
      List<String> words = Files.readAllLines(path); //将文件中的所有行存入集合
        Stream<String> LongWords = words.stream().filter( w -> w.length()>12 && w.length()<20);
        //LongWords.forEach(System.out::println);

        Stream<String> lowercaseWords = words.stream().map(String::toUpperCase);
     //  lowercaseWords.forEach(System.out::println);

       //内部类实现接口
       Stream<String> firstLetters  = words.stream().map( new Function<String,String>(){
           @Override
           public String apply(String s) {
               return s.substring(0,1);
           }
       });
        List<String> words2 = new ArrayList<>();
        words2.add("your");
        words2.add("boat");
        words2.add("home");


        //获取列表的流，然后进行中间操作map，要操作的元素是String类型，返回的结果则是Stream<String>
        Stream<Stream<String>> result = words2.stream().map(new Function<String, Stream<String>>() {
            @Override
            public Stream<String> apply(String s) {
                return codePoints(s);
            }
        });

        //现在result流有三个元素，每个元素是一个流
        result.forEach(word ->{
            word.forEach(System.out::print);
            System.out.println();
        });
    }

    public static Stream<String> codePoints(String s){
        return s.codePoints().mapToObj(new IntFunction<String>() {
            @Override
            public String apply(int value) {
                //从int数组中获取代码点，第二个参数是起始索引，第3个参数是构造字符串的长度
                //这个代码将构造value代码点对应的Unicode字符
                String  str= new String(new int[]{ value},0,1);
                return str;
            }
        });
    }
}

```

​	使用这个方法之后获取的流类似于二维数组的形式。

​	

#### 1.3.3 flatMap方法

​	在使用Map时，会有一个函数应用到每个元素上，并且其结果是包含了应用该函数后所参数的所有结果的流。这是一对一的转换。而当使用`flatMap`时，==需要提供一个方法，它会为每一个流元素产生一个新的流==。flatMap()操作的作用是对流的元素应用一对多转换，==然后将生成的元素展平为新流==，下面是方法签名

```java
//T ：原始流中的元素类型，R 新流中的元素类型
//mapper: 一个函数接口，它接受一个类型为T的参数，并返回一个Stream<R>
<R> Stream<R> flatMap(Function<? super T, ? extends Stream<? extends R>> mapper)
```

​	下面使用`flatMap`转换流中的元素。前面已经做好了将字符转换为字符流的工作，只需调用即可

```java
package StreamAPI;

import java.util.ArrayList;
import java.util.List;
import java.util.function.IntFunction;
import java.util.stream.Stream;


public class FlatMap {

    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("Hello");
        list.add("World");
        list.add("House");
        list.add("Alise");

        //Collection接口的stream方法能将任何的集合转换为一个流
        Stream<String> listStream = list.stream();
        listStream.forEach(System.out::println);


        //使用map方法操作，map方法会将流中的每一个元素按照接口返回的结果转换
        Stream<Stream<String>> result = list.stream().map(t->{
            return codePoints(t);
        });
        /*
       逻辑分析：
        map会对流中的每一个元素进行转换，转换结果由接口提供，
        由于该接口的实现方式的返回结果是一个Stream<String>流。
        所以最后Stream<Stream<String>>流存储了三个 Stream<String>流
        输出：
        java.util.stream.IntPipeline$1@6e8cf4c6
        java.util.stream.IntPipeline$1@12edcd21
        java.util.stream.IntPipeline$1@34c45dca
        java.util.stream.IntPipeline$1@52cc8049
        * */
        //result.forEach(System.out::println); 所以我们需要双重遍历方式
        result.forEach((w) ->{
            System.out.print("[");
            w.forEach((r)->{
                System.out.print(r+" ");
            });
            System.out.print("]\n");
        });


        /*flapMap很适合处理这种类似于双重数组的情况
        它可以将这个结果扁平化处理,结果：[HelloWorldHouseAlise]
         */
        Stream<String> flatMapStream= list.stream().flatMap(f->{
            return codePoints(f);
        });
        System.out.print("[");
        flatMapStream.forEach(System.out::print);
        System.out.print("]");
    }

    //该方法将字符串转换为一个字符流
    public static Stream<String> codePoints(String s) {
        return s.codePoints().mapToObj(new IntFunction<String>() {
            @Override
            public String apply(int value) {
                //从int数组中获取代码点，第二个参数是起始索引，第3个参数是构造字符串的长度
                //这个代码将构造value代码点对应的Unicode字符
                String str = new String(new int[]{value}, 0, 1);
                return str;
            }
        });
    }
}

```



**`Java.util.stream.Stream`**

```java
Stream<T> filter(Predicate<? super T> predicate)
    产生一个流，它包含当前流中所有满足谓词条件的元素。
<R> Stream<R> map(Function<? super T, ? extends R> mapper)
    产生一个流，它包含将mapper应用于当前流中所有元素产生的结果。
<R> Stream<R> flatMap(Function<? super T,?extends R> mapper)
    产生一个流，它是通过将mapper应用于当前流中所有元素产生的结果连接到一起而获得的（注意，这里的每一个结果都是一个流）。
<R> Stream<R> mapMulti(BiConsumer<? super T,? super Consumer<R>> mapper)
    每一个流元素都会调用mappper,并且所有在调用期间传递给Consumer的元素都会被添加到结果流中。
```





## 1.4 抽取子流和组合流

​	==调用`stream.limit(n)`会返回一个新的流，它在n个元素之后结束（如果原来的流比n短，那么就会在该流结束时结束）==。这个方法对于裁剪无限流的尺寸特别有用（limit为终止操作）。例如

```java
 public static void main(String[] args) {
		//产生包含0~99的一个流
        Stream<BigInteger> stream = Stream.iterate(BigInteger.ZERO, n-> 					n.add(BigInteger.ONE)).limit(100);
     
        stream.forEach(System.out::println);
    }
```

​	==调用`stream.skip(n)`则相反，它会丢弃前n个元素。== 按照`split`方法的工作方式，如果第一个元素是一个没用的空字符串，那么可以通过调用`skip`来跳过它：

```java
    public static void main(String[] args) {
        String str = " Hello";
        System.out.println(str);
        //跳过第一个空字符串
        Stream<String> words = Stream.of(str.split("\\PL+")).skip(1);
        words.forEach(System.out::print);
    }
```

​	

​	==`stream.takeWhile(predicate)`调用会在谓词为真时获取流中的所有元素。在断言（predicate）为假时停止==。：

```java
   public static void main(String[] args) {
        //创建一个列表
        List<String> words2 = new ArrayList<>();
        words2.add("your");
        words2.add("boat");
        words2.add("home");

        //takeWhile会从流中一直读取元素，直到条件为真时停止读取
        Stream<String> result =words2.stream().takeWhile(t -> !t.equals(words2.get(2)));

        result.forEach(System.out::println);
    }
```

​	==`dropWhile`方法的做法正好相反，它会在条件为真时丢弃元素，并产生一个由第一个时该条件为假的字符开始的所有元素构成的流==：

```java
package StreamAPI;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class WhileStream {
    public static void main(String[] args) {
        //创建一个列表
        List<String> words2 = new ArrayList<>();
        words2.add("height");
        words2.add("hi");
        words2.add("home");
        words2.add("house");
        words2.add("stop");
        words2.add("time");
        words2.add("current");
        words2.add("hello");
        words2.add("use");
        //获取断言条件为假之前的所有元素,这条代码将获取所有第一个字符为h的字符串，且在第一个元素被判断为false时停止读取
      Stream<String> takeWhileStream = words2.stream().takeWhile(t ->"h".equals(atFirstString(t)));
     takeWhileStream.forEach(System.out::println);

        //dropWhile会产生一个流，它的元素由第一个被判断为假的元素的后面全部元素组成
      Stream<String> dropWhileStream = words2.stream().dropWhile(t->"h".equals(atFirstString(t)));
      //dropWhileStream.forEach(System.out::println);
    }

    //获取字符串首个字符
    public static String atFirstString(String s){
        return s.substring(0,1);
    }
}

```

​	`dropWhile`会在条件为真时丢弃元素，并且后续元素第一个条件为假的元素开始后面的所有元素。也就是说，只要有一个元素被断言判断为假，就会把这个元素后面的所有元素添加到流中

​	

​	`Stream`类的静态`concat`方法可以将两个流连接起来（前提是第一个流不是无限流）：

```java
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("Hello");
        list.add("Double");

        Collection<String> collection = new HashSet<>();
        collection.add("HashSet");

        //将两个列表转换为流并且连接起来
        Stream<String> concatStream = Stream.concat(list.stream(),collection.stream());

        concatStream.forEach(System.out::println);
    }
```



**`Java.util.stream.Stream`**

```java
Stream<T> limit(long MaxSize)
    产生一个流，其中包含当前流中前maxSize元素。
Stream<T> skip(long n)
    产生一个流，它的元素是当前流中除了前n个元素之外的所有元素。
Stream<T> takeWhile(Predicate<? super T> predicate)
    产生一个流，它的元素是当前流中所有满足断言条件的元素，在遇见第一个断言条件为假的元素时停止。
Stream<T> dropWhile(Predicate<? super T> predicate)
    产生一个流，它的元素是当前流中
static<T> Stream<T> concat(Stream<? extends T> a, Stream<? extends T> b)
    产生一个流，它的元素是a的元素后面跟着b的元素
```



## 1.5 其他的流转换

​	**`distinct`方法会返回一个流，它的元素是从原有流中产生的，即原来的元素按照同样的顺序剔除重复元素后产生的**。

```java
public class DistinctStream {
    public static void main(String[] args) {
        //distinct会剔除流中重复的元素，使每个元素都是唯一的
        Stream<String> uniqueWords = Stream.of("merrily","merrily","merrily","gently").distinct();

        uniqueWords.forEach(System.out::println);
    }
}
```

​	

​	**`sorted`方法会产生一个新的流，它的元素是原有流中按照顺序排列的元素**。

```java
public class sortedStream {
    public static void main(String[] args) {
        //默认排序按照字母顺序排序
        Stream<String> stringStream = Stream.of("merrily","abandon","creat","bad","election","zero").sorted();
        stringStream.forEach(System.out::println);
    }
}
```

​	**对于流的排序，`sorted`方法能接受一个`comparator`接口，通过其他方式进行排序，比如通过字符串的长度排序，使最短的字符串排在最签名**

```java
public class sortedStream {
    public static void main(String[] args) {
        //按照字符串长度排序
        Stream<String> stringStream = Stream.of("merrily","abandon","creat","bad","election","zero").sorted(new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                //o1 小于 o2
                if(o1.length() < o2.length())
                    return 1;
                else if(o1.length()>o2.length())
                    return -1;
                else
                    return 0;
            }
        });
        stringStream.forEach(System.out::println);
    }
}

```



**`Java.util.stream.Stream`**

```java
Stream<T> distinct()
    产生一个流，包含当前流中所有不同的元素
Stream<T> sorted()
Stream<T> sorted(Comparator<? super T> comparator)
    产生一个流，它的元素是当前流中的所有元素按照顺序排列的。第二个方法要求传入的类实现了Comparable的类的实例
```





## 1.6 简单约简

​	**约简是一种终结操作，它们会将流约简为可以在程序中使用的非流值**

​	以前我们使用过一种简单约简：`count`方法会返回流中元素的数量。

```java
    public static void main(String[] args) {

        Stream<String> stream = Stream.of("Hello","Test","AGE");
        long count = stream.count(); //count方法将返回3,返回类型long
        System.out.println(count);
    }
```

​	

​	==其他的简单约简还有`max`和`min`，它们分别返回流中的最大值和最小值。这两个方法返回的是一个类型为`optional<T>`的值==，它要么在其中包含了答案，要么表示没有任何值（流为空的情况下）。**`optional`类型是一种用来表示缺少返回值的更好方式**。下面展示了如何获取流中的最大值：

```java
public class StreamTest {
    public static void main(String[] args) {
        String[] words = {"Hello","Test","AGE"};

        Optional<String> largest = Stream.of(words).max(new Comparator<String>(){
            @Override
           public int compare(String o1, String o2){
                if(o1.compareToIgnoreCase(o2)>0)
                    return 1;
                else if(o1.compareToIgnoreCase(o2)<0)
                    return -1;
                else{
                    return 0;
                }
            }
        });

        System.out.println(largest);//输出Optional[Test]
    }
}

```



​	==`findFirst`返回的是非空集合中的第一个值==,它通常与filter组合使用时很有用。例如，下面暂时了如何找到一个以字母Q开头的单词，提前是存在这样的单词：

```java
public class FindFirstStream {
    public static void main(String[] args) {
        String[] words = {"Hello","Test","AGE","Queen"};

        Optional<String> startElement = Stream.of(words).findFirst();
        System.out.println(startElement);//输出Optional[Hello]

        //startsWith方法会查找该字符串的首字母是否为参数prefix
        Optional<String> startWithQ = Stream.of(words).filter(s-> s.startsWith("Q")).findFirst();
        System.out.println(startWithQ);//输出Optional[Queen]
    }
}
```

​	

**`java.util.stream.Stream`**

```java
Optional<T> max(Comparator<? super T> comparator)
Optional<T> min(Comparator<? super T> comparator)
    分别产生这个流的最大元素和最小元素，由Comparator接口提供的比较器定义进行排序，如果这个流为空，会产生一个空的Optional对象。这些操作都是终结操作。
Optional<T> findFirst()
Optional<T> findAny()
    分别产生这个流的第一个和任意一个元素，如果这个流为空，会产生一个空的Optional对象。这些操作都是终结操作。
booealn anyMatch(Predicate<? super T> predicate);
booealn allMatch(Predicate<? super T> predicate);
booealn noneMatch(Predicate<? super T> predicate);
	分别在这个流中任意元素、所有元素和没有任何元素匹配给定断言条件时返回true。这些操作都是终结操作
```





## 1.7 Optional类型

​	==`Optional<T>`对象是一种包装器对象==，**要么包装了类型T的对象，要么没有包装任何对象**。`Optional<T>`类型被当作一种更安全的方式，用来代替类型T的引用，这种引用要么引元某个对象，要么为null。但是，它只有在正确使用的情况下才会更安全。



#### 1.7.1 获取Optional值

​	有效地使用Optional的关键是：==它的值不存在的情况下会产生一个可替代物，而只有在值存在的情况下才会使用这个值==。通常，在没有任何匹配时，我们会希望使用某种默认值，可能是空字符串：

```java
public class getOptional {
    public static void main(String[] args) {
        //创建一个流，通过max方法获取一个Optional包装器
        Stream<String> stringStream  = Stream.of("Hello","Time","abandon");
        Optional<String> optionalS = stringStream.max(String::compareTo);

        //获取Optional包装器中的对象
        String result = optionalS.orElse(""); //如果包装器中没有对象，则返回空字符串
        System.out.println(result);
    }
}
```

​	还可以调用代码来计算默认值：

```java
public class getOptional {
    public static void main(String[] args) {
        //创建一个流，通过max方法获取一个Optional包装器
        Stream<String> stringStream  = Stream.empty();
        Optional<String> optionalS = stringStream.max(String::compareTo);

        //getProperty方法用于获取系统属性,当流中没有任何元素时，orElesGet就会返回这个接口的实现方法的返回值
        String result = optionalS.orElseGet(() -> System.getProperty("myapp.default"));
        System.out.println(result); //输出null

    }
}
```

​	或者可以在没有任何值时抛出异常
```java
    public static void main(String[] args) {
        //创建一个流，通过max方法获取一个Optional包装器
        Stream<String> stringStream  = Stream.empty();
        Optional<String> optionalS = stringStream.max(String::compareTo);

    	//因为optionalS为空，它会抛出里面lambda表达式的结果
        String result = optionalS.orElseThrow(()->new IllegalStateException("该流为空"));
        System.out.println(result); //输出null

    }
```



**`Java.util.Optional`**

```java
T orElse(T other)
    产生这个Optional的值，或者在该Optional为空时，产生other。
T orElseGet(Supplier<? extedns T> other)
    产生这个Optional的值，或者在该Optional为空时，产生调用other的结果。
<X extends Throwable> T orElseThrow(Supplier<? extends X> exceptionSupplier)
    产生这个Optional的值，或者在该Optional为空时，抛出调用exceptionSupplier的结果。
```





#### 1.7.2 消费Optional值

​	在上一小节，我们学会了如何在包装类不存在任何值的情况下产生相应的替代物。另一条使用可选值的策略是只有在其存在的情况下才消费该值。

​	==`ifPresent`方法会接受一个函数。如果可选值存在，那么它会被传递给该函数，否则不会发生任何事情。==例如，如果在该值存在的情况下将其添加到某个集中：

```java
    public static void main(String[] args) {
        //生成一个流
        Stream<String> stream = Stream.of("Title","cancel","confirm");

        //通过该流生成一个Optional包装器，让这个包装器获取流中的第一个元素
        Optional<String> optionalS = stream.findFirst();
        //如果包装器中有值存在，则将这个值进行某种操作, 比如添加到一个集中
        ArrayList<String> arrayList=new ArrayList<>();
        optionalS.ifPresent(o-> arrayList.add(o));
        //或者直接调用方法引用：
        optionalS.ifPresent(arrayList::add);
		//输出集合中的元素
        arrayList.forEach(System.out::println);
    }
```

​	==如果想要在可选值存在时执行一种动作，在可选值不存在时执行另一种动作，可以使用`ifPresentOrElse`==:

```java
    public static void main(String[] args) {
        //生成一个流
        Stream<String> stream = Stream.of("Title","cancel","confirm");

        //通过该流生成一个Optional包装器，让这个包装器获取流中的第一个元素
        Optional<String> optionalS = stream.findFirst();
        optionalS.ifPresentOrElse(System.out::println,()->System.out.println("无参数"));
    }
```



**`Java.util.Optional`**

```java
void ifPresent(Consumer<?> action)
    如果该Optional不为空，就将它的值传递给action;
void ifPresentOrElse(Consumer<? super T> action, Runnable emptyAction)
    如果该Optional不为空，就将它的值传递给action，否则调用emptyAction。
```



#### 1.7.3 管道化Optional值

​	我们可以使用`map`方法来转换Optional内部的值

```java
 Optional<String> transformed = optionalS.map(String::toUpperCase)
```

​	或者将结果添加到列表中去；

```java
optionalValue.map(result::add);
```

​	

​	类似的，使用`filter`方法只处理满足特定属性的`Optional`值。如果不满足该属性，那么将产生空的结果：

```java
//将长度大于等于8的字母通过map方法转换为全大写字符串，并赋值给Optional
Optional<String> transformed = optionalString.filter(s->s.length()>=8).map(String::toUpperCase);
```

​	`or`方法将空Optional替换为一个可替代的Optional。

```java
Optional<String> result = optionalString.of(()->alternatives.stream().findFirst());
```

​	**如果`optionalString`的值存在，那么result为optionalString。如果值不存在，那么久会计算lambda表达式，并使用计算出来的结果。**



**`Java.util.Optional`**

```java
<U> Optional<U> map(Function<? super T, ? extends U> mapper)
    产生一个Optional，如果当前的Optional的值存在，那么所产生的Optional的值是通过给定的函数应用于当前的Optional的值而得到的；否则产生一个空的Optional;

Optional<T> filter(Predicate<? super T> predicate)
    产生一个Optional，如果当前的Optional的值满足给定的断言条件，那么所产生的Optional的值就是当前Optional的值；否则，产生一个空Optional。

Optional<T> or(Supplier<? extends Optional<? extends T>> supplier)
    如果当前Optional不为空，则产生当前的Optional；否则由supplier产生一个Optional。
```





#### 1.7.4 不适合使用Optional值的方式

​	`get`方法会在`Optional`值存在的情况下获得其包装的元素，或者在不存在的情况下抛出一个`NoSuchElementException`异常。因此，

```java
Optional<T> optionalValue=...;
optionalValue.get().someMethod();
```

并不下面的方式更安全：

```java
T value=...;
value.someMethod();
```

​	

​	`isPresent`方法和`isEmpty`方法会报告某个`Optional<T>`对象是否具有值。但是

```java
if(optionalValue.isPresent())
    optionalValue.get().someMethod();
```

​	并不比下面的方式更容易处理：

```java
if(value!=null)
    value.someMethod();
```

​	

​	下面是一些有关Optional类型的正确用法：

1. `Optional`类型的变量永远都不应该为null。
2. 不要使用`Optional`类型的域。因为其代价是额外多出来一个对象。在类的内部，一个使用null表示缺失的域更易于操作。
3. 类型为Optional的方法产生是有问题的。
4. 不要在集合中放置Optional对象，并且不要将它们用作map的键。应该直接收集其中的值

**`Java.util.Optional`**

```java
T get()
T orElseThrow()
    产生这个Optional的值，或者在该Optional为空时，抛出一个NoSuchElelentException异常
boolean isEmpty()
boolean isPresent()
    分别对应该Optional为空和不为空时，返回true。

```



#### 1.7.5 创建Optional值

​	如果想要编写方法来创建`Optional`对象，那么有多个方法可以用于此目的，包括`Optional.of(result)`和`Optional.empty()`。例如：

```java
public static Optional<Double> inverse(Double x)
{
    return x==0 ? Optional.empty() : Optional.of(1/x);
}
```

​	`ofNullable`方法被用来作为可能出现的null值和可选值之间的桥梁。==`Optional.ifNullable(obj)`会在obj不为null的情况下返回`Optional.of(obj)`, 否则会返回`Optional.empty()`==。

​	

**`Java.util.Optional`**

```java
static <T> Optional<T> of(T value)
static <T> Optional<T> ofNullable(T value)
    用给定值产生一个Optional。如果value为null，那么第一个方法会抛出一个NullPointerException异常，第二个方法会产生一个空Optional。
static <T> Optional<T> empty()
    产生一个空Optional。
```



#### 1.7.6 用flatMap构建Optional值的函数

​	看不懂，下一节



#### 1.7.7 将Optional转换为流

​	`stream`方法会将一个`Optional<T>`对象转换为一个具有0个或1个元素的`Stream<T>`对象。这会使返回`Optional`结果的方法变得很有用。假设有一个用户ID流和下面的方法；

```java
Optional<User> lookup(String id)
```

​	我们可以过滤掉无效ID，然后将get方法应用于剩余的ID：

```java
看不懂
```



**`Java.util.Optional`**

```java
<U> Optional<T> flatMap(Function<? super T, Optional<U>> mapper)
    产生将mapper应用于当前Optional值的结果，或者在当Optional为空时，返回一个空Optional。
```





下面的示例程序演示了`Optional API`的使用方式

```java
package APIOptional;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Optional;

public class OptionalTest {
    public static void main(String[] args) throws IOException {
        //读取文件中的所有字符
       String contents =  Files.readString( Path.of("E:\\JavaProgram_Project\\Practice\\resource\\text\\Alice.txt"));
        List<String> wordList = List.of(contents.split("\\PL+"));//将字符串按空格分开，依次存入集合

        //在这个集合中找到第一个单词中含有fred字母的字符串
        Optional<String> optionalValue = wordList.stream().filter(s->s.contains("fred")).findFirst();
        System.out.println(optionalValue.orElse("No word")+" contains fred");

        Optional<String> optionalString = Optional.empty(); //获取一个空包装器
        //由于这个包装器是空的，所有orElse会返回"N/A"
        String result = optionalString.orElse("N/A");
        System.out.println("result: "+result);

        //orElseGet会在包装器为空时执行里面的函数
        result = optionalString.orElseGet( ()-> Locale.getDefault().getDisplayName());
        System.out.println("result:"+result);

        try{
           // result = optionalString.orElseThrow(()-> new IllegalStateException("包装器为空"));
        }catch (Throwable t){
            t.printStackTrace();
        }

        //从集合的流中寻找到第一个red字母的字符串
        optionalValue = wordList.stream().filter(s-> s.contains("red")).findFirst();
        //如果该包装器不为空，则将它的值传给该函数
        optionalValue.ifPresent(s->System.out.println(s+"contains red"));



        HashSet<String> result2 = new HashSet<>();
        //如果包装器有值，就将该值添加到result2集合中
        optionalValue.ifPresent(result2::add);
        Optional<Boolean> added = optionalValue.map(result2::add);
        System.out.println(added);


        System.out.println(inverse(4.0).flatMap(OptionalTest::squareRoot));
    }

    //将传入的Double类通过Optional类的方法转换为Optional包装器
    public static Optional<Double> inverse(Double x){
        //如果x值为0，则返回的包装器为空。反之返回的包装器值为1/x;
        return x==0 ? Optional.empty() : Optional.of(1/x);
    }

    //通过包装器更安全的计算一个值的根
    public static Optional<Double> squareRoot(Double x){
        return x>0 ? Optional.empty() :Optional.of(Math.sqrt(x));
    }
}
```





## 1.8 收集结果

​	处理完流之后，可以调用`iterator`方法查看结果，会它产生用来访问元素的旧式风格的迭代器。

```java
   public static void main(String[] args) {
        String[] words = {"Hello","Test","AGE"};

        Iterator<String> iterator = Arrays.stream(words).iterator();//获取流的迭代器
        while(iterator.hasNext())
            System.out.println(iterator.next());
       
    }
```

​	或是调用`forEach`方法，将某个函数应用于每个元素：

```java
    public static void main(String[] args) {
        String[] words = {"Hello","Test","AGE"};

        Stream<String> stream = Stream.of(words);
        stream.forEach(System.out::println);
    }
```

​	输出都为：

```java
Hello
Test
AGE
```

​	

​	`toList`可以获取流元素构成的列表。

```java
        List<String> list = Stream.of(words).toList();
```

​	==调用toArray可以获取流的元素构成的数组。`stream.toArray()`会返回一个`Object[]`数组，如果想要让数组具有正确的类型，可以向其传递数组构造器==：

```java
        String[] result = Stream.of(words).toArray(String[]::new);
```

​	

​	`collect`方法可以将流中的元素收集到另一个目标的需求。它会接受一个`Collector`接口的实例，==而`Collectors`提供了大量用于生成常见收集器的工厂方法==。

```java
List<String> result = stream.collect(Collectors.toList()); //将流中的元素收集到List表中
```

​	或是收集到集中

```java
Set<String> result = stream.collect(Collectors.toSet);
```

​	假设想要通过连接操作来收集流中的所有字符串。可以调用

```java
    public static void main(String[] args) {
        String[] words = {"Hello","Test","AGE"};

        String result = Stream.of(words).collect(Collectors.joining());
        System.out.println(result);
    }
//输出：HelloTestAGE
```

​	将分隔符传递给`joining`方法，可以在元素之间添加分隔符

```java
    public static void main(String[] args) {
        String[] words = {"Hello","Test","AGE"};

        String result = Stream.of(words).collect(Collectors.joining(","));
        System.out.println(result);
    }

//输出：Hello,Test,AGE
```

​	如果流中包含除字符串以外的其他对象，那么先需要将其转换为字符串：

```java
    public static void main(String[] args) {
        Integer[] arr={1,2,3,4,5,6,7,8,9,10};
        Stream<Integer> stream = Stream.of(arr);//获取这个整数流
        //将这个流转换为字符串并收集起来
        String str = stream.map(Object::toString).collect(Collectors.joining(","));
        System.out.println(str);
    }
```

​	

​	如果想要将流的结果约简为总和、数量、平均值、最大值或最小值，可以使用`summarizing（Int|Long|Double`方法中的某一个。**这些方法会接受一个将流对象映射为数值的函数，产生类型为`(Int|Long|Double)SummaryStatistics`结果，同时计算总和、数量、平均值、最大值和最小值**。

```java
    public static void main(String[] args) {
        Integer[] arr={1,2,3,4,5,6,7,8,9,10};
        Stream<Integer> stream = Stream.of(arr);//获取这个整数流
        //将这个流转换为字符串并收集起来
        IntSummaryStatistics summary = stream.collect(Collectors.summarizingInt(Integer::valueOf));
        double average = summary.getAverage();
        double max=summary.getMax();
        System.out.println("average = "+average); //输出5.5
        System.out.println("max = "+max); //输出max
    }
```

​	`summarizingInt`要求传入一个实现了`ToIntFunction<T>`接口的类，它的主要作用是从对象中提取一个`int`类型值，所以这里我们传入`Integer`对象的整数值。

​	下面是匿名内部类的实现方式

```java
    public static void main(String[] args) {
        Integer[] arr={1,2,3,4,5,6,7,8,9,10};
        Stream<Integer> stream = Stream.of(arr);//获取这个整数流
        //将这个流转换为字符串并收集起来
        IntSummaryStatistics summary = stream.collect(Collectors.summarizingInt(new ToIntFunction<Integer>() {
            @Override
            public int applyAsInt(Integer value) {
                return value.intValue();
            }
        }));
        double average = summary.getAverage();
        double max=summary.getMax();
        System.out.println("average = "+average); //输出5.5
        System.out.println("max = "+max); //输出max
    }
```

​	

​	下面的示例程序展示了如何从流中收集元素

```java
package StreamAPI;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.function.ToIntFunction;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class CollectionResults {
    public static void main(String[] args) throws IOException{

        Iterator<Integer> iter = Stream.iterate(0,n->n+1).limit(10).iterator();
        while(iter.hasNext())
            System.out.println(iter.next());

        Object[] numbers = Stream.iterate(0, new UnaryOperator<Integer>() {
            @Override
            public Integer apply(Integer integer) {
                return integer+1;
            }
        }).limit(10).toArray();
        System.out.println("Object Array:"+numbers);

        try{
            var number = (Integer) numbers[0];
            System.out.println("number: "+ number);
            System.out.println("The following statements throws an exception");
            //var number2= (Integer[]) numbers; //Throws exception
        }catch(ClassCastException e){
            System.out.println(e);
        }


        Integer[] numbers3 = Stream.iterate(0, n->n+1).limit(0).toArray(Integer[]::new);
        System.out.println("Integer array:"+numbers3);

        Set<String> noVoweSet = noVowels().collect(Collectors.toSet());
        show("noVoweSet",noVoweSet);

        TreeSet<String> noVowelTreeSet = noVowels().collect(Collectors.toCollection(TreeSet::new));
        show("noVowelTreeSet",noVowelTreeSet);

        String result = noVowels().limit(10).collect(Collectors.joining());
        System.out.println("Joining:"+result);

        result = noVowels().limit(10).collect(Collectors.joining(","));
        System.out.println("Joining: "+result);


        IntSummaryStatistics summary = noVowels().collect(Collectors.summarizingInt(new ToIntFunction<String>(){
            @Override
            public int applyAsInt(String value){
                return value.length();
            }
        }));

        double averageWordLength = summary.getAverage();
        double maxWordLength = summary.getMax();
        System.out.println("Average word Length:"+averageWordLength);
        System.out.println("Max word Length: "+ maxWordLength);
        System.out.println("forEach:");
        noVowels().limit(10).forEach(System.out::println);
    }

    //这个方法读取一个文件，将里面所有的单词转换为流，并且将单词带有元音字母的全部替换为空
    public static Stream<String> noVowels() throws IOException {
        String contents = Files.readString(Path.of("E:\\JavaProgram_Project\\Practice\\resource\\text\\Alice.txt"));
        List<String> wordList = List.of(contents.split("\\PL+")); //将该字符串按单词分割传入List表s
        //将该表转换为流
        Stream<String> words = wordList.stream();

        //将每个单词的元音字母替换成空字符串
        return words.map(s-> s.replaceAll("[aeiouAEIOU]",""));
    }


    public static <T> void show(String label, Set<T> set){
        System.out.println(label + ": "+ set.getClass().getName());
        System.out.println("[" +
                set.stream().limit(10).map(Object::toString).collect(Collectors.joining(","))+"]");
    }
}

```



**`Java.util.stream.BaseStream`**

```java
Iterator<T> iterator()
    产生一个用于获取当前流中各个元素的迭代器。这是一种终结操作
```

**`Java.util.stream.Stream`**

```java
List<T> toList()
    产生一个由这个流中所有元素构成的列表
void forEach(Consumer<? super T> action)
    在流的每个元素上调用action
Object[] toArray()
<A> A[] toArray(IntFunction<A[]> generator)
    产生一个对象数组，或者在传递了构造器引用A[]::new时，返回一个A类型的数组。这些操作都是终结操作
<R,A> R collect(Collector<? super T,A,R>collector)
    使用给定的收集器来收集当前流中的元素。Collectors类有用于多种收集器的工厂方法。
```

**`Java.util.stream.Collectors`**

```java
static <T> Collector<T,?,List<T>> toList();
static <T> Collector<T,?,List<T>> toUnmodifiableList()
static <T> Collector<T,?,Set<T>> toSet();
static <T> Collector<T,?,Set<T>> toUnmodifiableList();
产生一个将元素收集到列表或集合中的收集器
 
static <T,C extends Collection<T>> Collector<T,?,C> toCollection(Supplier<C> collecitonFactory)
    产生一个将元素收集到任意集合中的收集器。可以传递一个诸如TreeSet::new的构造器引用
        
static Collecotr<CharSequence , ? String> joining()
static Collecotr<CharSequence , ? String> joining(CharSequence delimiter);
static Collecotr<CharSequence , ? String> joining(CharSequence delimiter,CharSequence prefix,
                                                 CharSequence suffix);
产生一个连接字符串的收集器。分隔符（delimiter)会置于字符串之间。而第一个字符串之前可以有前缀（prefix），最后一个字符串之后可以有后缀（suffix）。如果没有指定，那么它们都为空
    
static <T> Collector<T, ?,IntSummaryStatistics> summarizingInt(ToFunction<? super T> mapper);
    
static <T> Collector<T, ?,LongSummaryStatistics> summarizingLong(ToFunction<? super T> mapper)
        
static <T> Collector<T, ?,DoubleSummaryStatistics> summarizingDouble(ToFunction<? super T> mapper)
    产生能够生成(Int|Long|Double)SummaryStatistics对象的收集器，通过它们可以获得将mapper应用于每个元素后所产生的结果的数量、总和、平均值、最大值和最小值
IntSummaryStatistics;
LongSummaryStatistics;
DoubleSummaryStatistics;
long getCount()
    产生汇总后的元素的个数
(int|long|double) getSum()
double getAverage()
    产生汇总后的元素的总和或平均值，或是在没有任何元素时返回0
(int|long|double) getMax()
(int|long|double) getMin()
    产生汇总后的元素的最大值和最小值，卓是在没有任何元素时，产生（Integer| Long| Double).(MAX|MIN)_VALUE。
```





## 1.9 收集到映射表中

​	假设我们有一个`Stream<Person>`，并且想要将其元素收集到一个映射表中，这样后续就可以通过它们的ID来查找人员。==`Collectors.toMap`方法有两个函数引元，它们用来产生映射表的键和值==

```java
    public static void main(String[] args) {
        Stream<Person> person= Stream.of(new Person(1,"张三"),new Person(2,"李四"),new Person(3,"王五"));

        //将流中的元素收集到映射表中
        Map<Integer,String> idToName= person.collect(Collectors.toMap(Person::getId,Person::getName));
        idToName.forEach(new BiConsumer<Integer, String>() {
            @Override
            public void accept(Integer integer, String s) {
                System.out.print("Key = "+integer);
                System.out.println(" Value = "+s);
            }
        });
    }
```

