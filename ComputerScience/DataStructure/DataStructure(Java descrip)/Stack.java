package Data_Structure;

public class Stack {
    private final static int MAXSIZE=100;
    private int top;
    private final int[] data;

    public Stack(){
        top=0;
        data = new int[MAXSIZE];
    }

    //入栈，栈顶指示器始终指向栈顶的下一个元素
    public void push(int e){
        if(top==MAXSIZE)
            throw new IllegalStateException("栈已满");

        data[top]=e;
        top++;
    }

    //出栈
    public int pop(){
        return data[--top];
    }

    public void show(){
        System.out.print("[");
        for(int i=top-1;i>=0;i--){
            System.out.print(data[i]);
            if(i>0)
                System.out.print(",");
        }
        System.out.println("]");
    }

    public static void main(String[] args){
        Stack stack = new Stack();

        for(int i=0;i<10;i++){
            stack.push(i+1);
        }

        stack.show();

    }
}
