### 生成固定返回随机数

```java

import java.util.Random;

public class Test {
    public static void main(String[] args) {
        // 生成 [0.0, 1.0) 之间的随机小数
        double randomDouble = Math.random();
        System.out.println("随机小数: " + randomDouble);

        // 生成 [0, 99] 之间的随机整数
        int randomInt = (int) (Math.random() * 100);
        System.out.println("0-99随机整数: " + randomInt);

        // 生成 [10, 20] 范围的随机整数（通用公式）
        int min = 10;
        int max = 20;
        int num = (int) (Math.random() * (max - min + 1)) + min;
        System.out.println("10-20随机整数: " + num);

        /*生成1-100的随机数*/
        Random r =new Random();
        int hurt = r.nextInt(100)+1;
        System.out.println("伤害："+hurt);
    }
}
```





### 使用+号拼接字符串

```java

public class StringDemo3 {
 
    public static void main(String[] args) {
        int arr[] ={1,2,3,4,5,6,7,8,9,10};
        String str = Int_toString(arr);
    }

    /*定义一个方法，将传入的数组的数据按照指定的格式拼接成一个字符串进行返回*/
    public static String Int_toString(int arr[]){
      if(arr.length==0 || arr==null)
          return "";
      //使用+号进行拼接操作
      String result = "[";
      for(int i=0;i<arr.length;i++){
          result = result +arr[i];
          result = result+",";
      }
        result += "]";
      System.out.println(result);
        return  result;
    }
}

```



### 反向输出字符串

```java
//反向输出字符串
public class StringDemo4 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        String str = in.next();

        for(int i=str.length()-1;  i>=0;i--){
            System.out.print(str.charAt(i));
        }

    }
```





### 金额转换

```java
package StringPractice;

import java.util.Scanner;

/*金额转换*/
public class StringDemo5 {
    public static final String RED = "\u001B[31m"; //用于设置输出字体颜色
    // 重置所有样式
    public static final String RESET = "\u001B[0m";
    public static final String unit = "佰拾万仟佰拾元";  // 百万 千万 万 仟 佰 拾 元
    public static void main(String[] args) {
         int money=0;
         Scanner in = new Scanner(System.in);
         System.out.println("请输入金额");
         //循环检测money值是否在理想范围内
         while(true){

             money = in.nextInt();
            if(money <=0 || money >9999999){
                System.out.println("请输入1到9999999范围的值");
            }else{
                break;
            }
         }

         String MoneyStr="";
        while(money >0){
            //循环获取个位数并传入方法中
            int ge = money %10;
            money /=10;
            MoneyStr = getCapitalNumber(ge)+MoneyStr;
        }
        System.out.println(MoneyStr);

        //进行补零，一个七位，不足七位就进行补零
        for(int i=MoneyStr.length(); i<7;i++){
            MoneyStr = "零"+MoneyStr;
        }
        System.out.println(MoneyStr);

        //插入单位
        String result="";
       for(int i=0;i<unit.length();i++){
           result = result +MoneyStr.charAt(i);
           result = result + unit.charAt(i);
1
       }
       System.out.println(result);
    }


    public static String getCapitalNumber(int number){
        String[] arr = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
        return arr[number];

    }
}

```



### 手机号屏蔽操作

```java
package StringPractice;

import java.util.Scanner;

//信息屏蔽操作
public class StringDemo6 {
    public static void main(String[] args) {
        String phNumber ;
        Scanner in =new Scanner(System.in);
        System.out.println("请输入手机号码");
        while(true){
            phNumber=in.next();

            if(phNumber.length()!=11){
                System.out.println("请输入有效的手机号码");
            }else
                break;
        }
        System.out.println("屏蔽后的手机号："+phoneNumberIgnore(phNumber));

    }


    public static String phoneNumberIgnore(String Number){
        String a = Number.substring(0,3);
        a=a+"****";
        a= a+Number.substring(7,11);
        return a;
    }
}

```



