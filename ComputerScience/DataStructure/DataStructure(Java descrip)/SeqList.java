package Data_Structure;

import java.util.Scanner;

public class SeqList<T> {
    private int length;
    static  private int MAXSIZE =100;
    private Object[] data;

    // 0<=i<=length，允许在末尾的下一个位置插入
    @SuppressWarnings("unchecked")
    public  void InsertList(int i,T data) throws IllegalStateException{
        //保证其插入位置合法以及还有插入位置
        if(length == MAXSIZE ){
          throw new IllegalStateException("该表已满");
        }
        if(i<0 || i>length){
            throw new IllegalArgumentException("非法参数");
        }

        //从最后一个元素开始，依次将元素后移
        for(int k = length-1; k>=i;k--){
           this.data[k+1] = this.data[k];
        }
        //然后直接插入
        this.data[i] = data;
        this.length++;
        System.out.println("索引"+i+"位置成功插入元素"+data);
    }

    //删除索引位置i的元素, 0<=i<length
    @SuppressWarnings("unchecked")
    public  T DeleteList(int i) {
        if(length==0){
            throw new IllegalStateException("非法操作");
        }

        if(i<0||i>=length){
            throw new IllegalStateException("非法参数");
        }
        T element = (T)this.data[i];
        //元素依次迁移，覆盖掉原本的位置。
        for(int k=i;k<length-1;k++){
            this.data[k]=this.data[k+1];
        }
        this.length--;
        this.data[length] = null;
        return element;
    }






    public SeqList() {
        this.length=0;
        this.data = new Object[MAXSIZE];
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length){
        this.length=length;
    }

    @SuppressWarnings("unchecked")
    public  T getDataForIndex(int i) {
        return (T)this.data[i];
    }

    public void showList(){
        System.out.print("[");

        for(int i=0;i<length;i++){
            System.out.print(this.<T>getDataForIndex(i));
            if(i<length-1)
                System.out.print(",");
        }
        System.out.println("]");
    }



    public static void main(String[] args){
      SeqList<String> stringSeqList = new SeqList<>();
        Scanner in = new Scanner(System.in);
        for (int i = 0; i < 10; i++) {
            System.out.println("请输入字符串：");
            String str = in.next();
            stringSeqList.<String>InsertList(i,str);
        }

        stringSeqList.<String>showList();
    }
}
