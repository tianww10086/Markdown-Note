## 3.1 Ajax

​	全称：**Asynchronous JavaScript And XML** 异步的JavaScript和XML

​	Ajax是一种用于创建快速、动态网页的技术。**它允许网页在不重新加载整个页面的情况下，与服务器交换数据并更新部分网页内容。**

​	使用步骤：

1. 准备数据地址：`https://api.agify.io/?name=michael`(示例)

2. 创建`XMLHttpRequest`对象：用于和服务器交换数据
3. 想服务器发送请求
4. 获取服务器响应数据

示例如下：

```HTML
	<input type="button" value ="获取数据" onclick="getData()">
	<div id="div1">

	</div>

<script>
   
    function getData(){
		console.log("获取数据");
		//创建XMLHttpRequst对象
		var XMLHttp = new XMLHttpRequest();

		//发送异步请求
		XMLHttp.open('GET','https://api.agify.io/?name=michael');
		XMLHttp.send();// 发送请求

		//获取服务响应数据
		XMLHttp.onreadystatechange = function(){
			if(XMLHttp.readyState==4 && XMLHttp.status==200)
			{
				document.getElementById('div1').innerHTML=XMLHttp.responseText;
			}
		}
	}
</script>
```

​	

#### 3.1.1 XMLHttpRequst对象方法

| 方法                                          | 描述                                                         |
| :-------------------------------------------- | :----------------------------------------------------------- |
| new XMLHttpRequest()                          | 创建新的 XMLHttpRequest 对象。                               |
| abort()                                       | 取消当前请求。                                               |
| getAllResponseHeaders()                       | 返回头部信息。                                               |
| getResponseHeader()                           | 返回特定的头部信息。                                         |
| open(*method*, *url*, *async*, *user*, *psw*) | 规定请求。*method*：请求类型 GET 或 POST*url*：文件位置*async*：true（异步）或 false（同步）*user*：可选的用户名*psw*：可选的密码 |
| send()                                        | 向服务器发送请求，用于 GET 请求。                            |
| send(string)                                  | 向服务器发送请求，用于 POST 请求。                           |
| setRequestHeader()                            | 将标签/值对添加到要发送的标头。                              |



#### 3.1.2 XMLHttpRequest 对象属性

| onload             | 定义接收到（加载）请求时要调用的函数。                       |
| ------------------ | ------------------------------------------------------------ |
| onreadystatechange | 定义当 readyState 属性发生变化时调用的函数。                 |
| readyState         | 保存 XMLHttpRequest 的状态。<br />0：请求未初始化<br />1：服务器连接已建立<br />2：请求已收到<br />3：正在处理请求<br />4：请求已完成且响应已就绪 |
| responseText       | 以字符串形式返回响应数据。                                   |
| responseXML        | 以 XML 数据返回响应数据。                                    |
| status             | 返回请求的状态号200: "OK"<br />403: "Forbidden"<br />404: "Not Found"<br />如需完整列表请访问 [Http 消息参考手册](https://www.w3school.com.cn/tags/html_ref_httpmessages.asp) |
| statusText         | 返回状态文本（比如 "OK" 或 "Not Found"）                     |

`onreadstatechange`属性定义了一个回调函数，当`readyState`改变时执行该函数。

`onload`属性定义了一个回调函数。**在请求收到答复时执行**







## 3.2 Axios

​	Axios对原生的Ajax进行了封装，简化书写，快速开发。

​	官网：https://www.axios-http.cn/

​	

### 3.2.1 Axios入门

​	1.引入Axios的js文件

```HTML
<script src="js/axios-0.18.0.js"></script>
```

​	2.使用`Axios`发送请求，并获取响应结果

```HTML
```

