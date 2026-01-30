package Data_Structure;

import java.util.NoSuchElementException;
import java.util.Random;

//顺序队列
public class Queue {
    //队列，属于队头出，队尾进的线性表，先进先出。
    private int front; //队头指针
    private int rear;  //队尾指针。
    private int[] data; //数据区域
    private static final int MAXSIZE = 100; //队列最大存储空间
    private int size;
    //构造函数
    public Queue(){
        //起初，队尾队头指针都为0
        front=0;
        rear=0;
        size=0;
        data = new int[MAXSIZE];
    }

    //入队,在队尾入
    public void enQueue(int e){

        //队满条件为 (rear+1)%MAXSIZE=front
        if((rear+1)%MAXSIZE==front){
            throw new IllegalStateException("队列已满");
        }

        this.data[rear] = e; //入队
        this.rear = (rear+1)%MAXSIZE; //保证rear在0~MAXSIZE-1之间
        size++;
    }

    //出队
    public int deQueue(){
        if(rear==front){
            throw new NoSuchElementException("队列已空");
        }
        int x =  data[front];
        front = (front+1)%MAXSIZE;
        size--;
        return x;
    }


    public void show(){
        if(rear==front)
            throw new RuntimeException("队列为空");

        for(int i=front;i<size;i=(i+1)%MAXSIZE){
            System.out.print(this.data[i]+" ");
        }
    }

    public static void main(String[] args){
        Queue test = new Queue(); //创建一个空队列
        Random ran=new Random();
        for(int i=0;i<10;i++){
            int e = ran.nextInt(999-100+1)+100;
            test.enQueue(e);
        }

        test.show();
    }
}
