package Data_Structure;

import java.util.NoSuchElementException;

public final class MyString {
    private final char[] data;

    public MyString(){
        data = new char[0];
    }


    //根据传入字符串构造串
    public MyString(String str){
        data = new char[str.length()];
        for(int i=0;i<str.length();i++){
            data[i]= str.charAt(i);
        }
    }

    //根据传入MyString构造字符串，等同于构造赋值方法
    public MyString(MyString str){
        if(str==null)
            throw new IllegalArgumentException("参数不能为null");
        data = new char[str.length()];
        for(int i=0;i<str.length();i++)
            data[i] = str.charAt(i);

    }

    public MyString(int  length){
        data = new char[length];
    }
    //该操作将覆盖目标原来的内存
    public  static MyString strCopy(MyString res){

        if(res==null)
            throw new IllegalArgumentException("参数不能为null");

        return new MyString(res);
    }

    //返回字符串长度
    public int length(){
        return this.data.length;
    }

    //返回索引所在字符
    public char charAt(int index){
        return this.data[index];
    }

    //空返回真，反之返回假
    public boolean empty(){
        if(this.length()==0)
            return true;
        else{
            return false;
        }
    }

    // 比较字符串大小
    public int compareTo(MyString str) {
        // 1. 异常选型建议：参数为空通常抛出 NullPointerException 或 IllegalArgumentException
        if (str == null) {
            throw new NullPointerException("Comparison target is null");
        }

        int len1 = this.length();
        int len2 = str.length();
        // 2. 核心：确定比较的边界限制
        int lim = Math.min(len1, len2);

        int i = 0;
        while (i < lim) {
            char c1 = this.charAt(i);
            char c2 = str.charAt(i);
            if (c1 != c2) {
                //                // 3. 发现不相等的字符，直接返回差值
                return c1 - c2;
            }
            i++;
        }
        // 4. 重要：如果运行到这里，说明在 min(len1, len2) 范围内字符全部相等
        // 此时根据长度判断，例如 "abc" < "abcd"，返回 -1
        return len1 - len2;
    }

    //静态工厂方法
    public static MyString valueOf(String str){
        if(str==null)
            throw new IllegalArgumentException("参数为空");

        return new MyString(str);
    }

    //将串2连接到串1后面
    public MyString concat(MyString string){


        int newLength = this.length() + string.length();
        MyString newStr = new MyString(newLength);
        //分配足额空间

        //先赋值原先的
        for(int i=0;i<this.length();i++){
            newStr.data[i] = this.data[i];
        }

        //再赋值附加的
        for(int i=newLength-string.length(),j=0;i<newLength;i++,j++){
            newStr.data[i] = string.charAt(j);
        }

        return newStr;
    }


    //返回从pos起len长度的串
    public MyString substring(int pos,int len){
        MyString sub = new MyString(len);

        if(this.data==null){
            throw new NoSuchElementException();
        }
        // 参数校验
        if (pos < 0 || len < 0) {
            throw new IllegalArgumentException("位置和长度不能为负数");
        }

        if (pos >= this.length()) {
            throw new IllegalArgumentException("起始位置超出字符串长度");
        }

        if (pos + len > this.length()) {
            throw new IllegalArgumentException("截取长度超出字符串范围");
        }


        for(int i=pos,j=0;i<pos+len;i++,j++){
            sub.data[j]=this.data[i];
        }

        return sub;
    }


    //从主串第pos位置开始，查找与sub相同的子串，返回位置,查找失败返回0 ,朴素算法
    public int index(MyString sub,int pos){

        if(pos<0 || pos>=length()){
            throw new IllegalArgumentException("pos参数越界");
        }

        if(this.data==null ||sub==null)
            throw new NoSuchElementException("主串或待查子串为空");

        int index=pos; //从pos起搜索主串

        int j=0; //遍历子串

        while(index<this.length() && j<sub.length()){
            //如果相等，继续匹配下一个
            if(this.data[index]==sub.data[j]){
                j++;
                index++;
            }else{
                //如果不匹配，让主串从下一个重新开始搜索
                index = index-j+1;
                j=0;
            }
        }

        //结束后，如果j的长度等于子串的长度， 则说明匹配成功
        if(j==sub.length())
            return index-j+1;
        else
            return  0;

    }



    //插入串
    public MyString insert(MyString str,int pos){
        if(str==null || pos<0 ||pos>this.length())
            throw new IndexOutOfBoundsException("串str为空或非法下标");

        int newLength = this.length()+str.length();
        MyString newStr = new MyString(newLength); //分配新长度

        //先复制原先的字符串
        for(int i=0;i<this.length();i++){
            newStr.data[i] = this.data[i];
        }

        //再通过新字符串依次后移str.length()个字符
        for(int i=this.length()-1;i>=pos;i--){
            //依次后移str.length位
            newStr.data[i+str.length()] = this.data[i];
        }

        //插入参数中的字符串
        for(int i=0;i<str.length();i++){
            newStr.data[i+pos]=str.data[i];
        }

        return newStr;
    }

    public MyString delete(int pos,int len){
        if(this.data==null)
            throw new NoSuchElementException();

        if(pos<0||pos+len>this.length())
            throw new IllegalArgumentException("非法参数");

        //由于字符数组构造之后，其length不可改变
        //所以要提前构造一个新的
        MyString deStr = new MyString(this.length()-len);

        //复制0到pos前的字符
        int i=0;
        for(i=0;i<pos;i++){
            deStr.data[i] =this.data[i];
        }

        //跳过pos到len的字符，为pos+len 到this.length;
        for(int j=pos+len;j<this.length();j++){
            deStr.data[i++] = this.data[j];
        }

       return deStr;
    }


    //类相等判断
    @Override
    public boolean equals(Object str){
      //向下转换

        //引用简称
        if(this==str)
            return true;
        //空引用简称
        if(str ==null)
            return false;

        // 比较是不是同类
       if(getClass()!=str.getClass())
           return false;

       MyString other =(MyString) str;

       //比较字符长度
        if(this.length()!=other.length())
            return false;

        //依次比较每个字符
        for(int i=0;i< other.length();i++){
            if(this.data[i]!=other.data[i])
                return false;
        }

        return true;
    }

    public String toString(){
        return new String(this.data);
    }

    public static void main(String[] args){
        MyString str =new MyString("String");
        str = MyString.valueOf("Hello");
        MyString str2=new MyString(" World");
        MyString str3 = str.concat(str2);
        System.out.println(str3);
        MyString test = new MyString("AI");
       str= str.insert(test,2);
      System.out.println(str);
       str = str3.delete(2,3);
       System.out.println(str);
    }
}
