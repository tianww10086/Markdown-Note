## 2.1 JavaScript简介

​	HTML+CSS+JavaScript被称为前端三件套，其中，HTML负责结构层，CSS负责表现层，则JavaScript负责行为层。JavaScript是Web的编程语言



### 2.1.1 使用方法

​	**1. 内部引入**

```html
<script>
	alert("Hello JavaScript");
</script>
```

​	**2. 外部脚本**

​	引入外部的js文件。如下：

```html
<script src="js/demo.js"></script>	
```

​	**3.输出方法**

```html
window.alert("str"); //浏览器警告框
docment.write("str"); //写入HTML,再浏览器暂时
console.log("str");//控制台输出
```

​	

## 2.2 基础语法

​	与Java不同，`JavaScript`是一门弱类型语言，变量可以存放不同类型的值。

### 2.2.1 声明变量

​	使用`var`关键字声明变量：

```html
var a = 20;
a ="张三" //Iegal ✅
```

​	建议使用驼峰命名， 用该关键字声明的变量在全局有效，且可以重复定义。

​	`let`关键字来定义局部变量：

```html
{
	let x = 10;
}
alert(x); //ERROR
```

​	`const`关键字定义常量



### 2.2.2 运算符

​	大部分运算符和其他高级语言基本一致，除了`等于`运算。使用`===`表示严格等于运算。

```html
var a=10;
alert(a=="10"); //true;
alert(a==="10"); //false;
alert(a=== 10); //true;
```



### 2.2.3 函数

​	语法：

```html
function name(参数1，参数2){
	//code
}
```

​	形参和返回值都不需要定义类型

​	调用：函数名称（参数列表）





## 2.3 数组

​	定义数组方式有多种：

​	1:

```html
var arr = new Array(1,2,3,4,5);
```

​	2.

```html
var arr=[1,2,3,4];
```

​	数组长度可变，内容可变。





## 2.4 JSON

​	JSON和数组都属于JavaScript的对象。下面先介绍如何自定义对象：

```html
var className={
	属性名: 属性值
....
	函数名: function(形参){
	// code
	}
}
```

​	JSON是通过`JavaScript`对象标记法书写的文本。换句话说，JSON是表示文本的一个规则，而这个规则采用自定义对象的语法。下面是一段JSON

```json
{
  "project": "Gemini AI",
  "version": 3.0,
  "features": ["Text", "Image", "Video"],
  "isActive": true
}
```

​	JSON数据中，所有的Key要加双引号。现在多用于数据载体，在网络中进行数据传输。

​	

### 2.4.1 JSON定义

​	语法如下：

```html
var jsonText = '{"key": value,...,...}';
```

​	实例：

```html
var userStr = '{"name":"田","age":18,"addr":["西安","北京","上海"]}';
```

​	`value`的类型不同，使用的语法也不同。如下：

- 数字：整数或浮点数

- 字符串：双引号中

- 数组：方括号中

- 对象：花括号中

- null

  JSON对象中的文本，不能在文档中直接使用。下面的方式会输出`undefined`

```html
var userStr = '{"name":"田","age":18,"addr":["西安","北京","上海"]}';
alert(userStr.name);
```

​	必须使用`JSON.parse(json对象)`方法转换为JS对象之后才能使用

```html
var ojb = JSON.parse(userStr);
alert(ojb.name);
```

​	JS对象转换为JSON字符串

```html
var jsonStr = JSON.stringify(jsObject);
```





## 2.5 BOM 

​	BOM全称浏览器对象模型（**B**rowser **O**bject **M**odel）允许javaScript与浏览器对象，javaScript将浏览器的各个组成部分封装为对象。

​	组成：

- Window：浏览器窗口对象
- Navigator:浏览器对象
- Screen：屏幕对象
- History：历史记录对象
- Location：地址栏对象



### 2.5.1 Window对象

​	Window对象可以直接使用。其中`window.`可以省略：

```html
window.alert("Hello");
//可以省略为
alert("Hello");
```

​	它包含了三个属性，分别是history、location和navigator对象的只读引用。

​	**方法**

- `alert()`:显示一段消息和一个确认按钮的警告框。
- `boolean confrim()`: 包含确认和取消选项的警告框
- `setInterval(函数，毫秒):`按照指定的周期（毫秒）来调用函数或计算表达式。
- `setTimeout(函数，毫秒):`在指定的毫秒后调用函数或计算表达式。



### 2.5.2 Location

​	该对象是地址栏对象。可以通过`window`获取，由于`window`可以省略，所以：

```html
location.属性
```

​	**属性**

- `href`:设置或返回完整的URL





## 2.6 DOM

​	DOM是文档对象模型`(Document Object Model)`。将标记语言的各个组成部分封装为对象：

- Document: 整个文档对象
- Element：元素对象
- Attribute：属性对象
- Text：文本对象
- Comment:注释对象

​	Document对应整个HTML文件，Element对应标签，Attribute对应标签中的属性。Text对应文本。Comment对应注释对象

由整个模型组成的DOM，又被叫做DOM树

​	HTML中的`Element`对象可以通过Document对象获取。`Document`对象中提供了以下获取`Element`元素对象的函数：

**1. 根据id属性值获取，返回单个Element对象**

```html
var h1 = ducment.getElementById('h1');
```

**2. 根据标签名获取，返回Element数组**

```html
var divs = ducument.getElementsByTagName('div');
```

**3. 根据name属性值获取，返回Element对象数组**

```html
var hobbys = document.getElemetsByName('hobby');
```

**4. 根据class属性值返回，获取Element对象数组**

```html
var class = document.getElementsByClassName('cks');
```





## 2.7 事件绑定

​	事件是发生在HTML元素上的事情。比如：

- 按钮被点击
- 鼠标移动到元素上
- 按下键盘按键

​	事件监听：JavaScript可以在事件被侦测到时执行代码

**方式1：通过HTML标签中的事件属性进行绑定**

``` html
<input type ="button" onclick = "on()" value = "按钮1">
<script>
	function on(){
        alert("我被点击了!");
    }
</script>
```

**方式2：通过DOM元素绑定**

``` html
<input type ="button" id ="btn" value = "按钮2">

<script>
	ducument.getElementById('btn').onclick=function(){
        alert("我被点击了");
    }
</script>
```

