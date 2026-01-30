package Data_Structure;

import java.util.NoSuchElementException;
import java.util.Random;

//链队列，附设头结点
public class LinkQueue<T> {
    //内部结点类
     private static class Node<T>{
          T data;
          Node<T> next;

        public Node(T val){
            data=val;
        }

        public Node(){}
        public T getData() {
            return data;
        }


        public Node<T> getNext() {
            return next;
        }

        public void setNext(Node<T> next) {
            this.next = next;
        }
    }
    private final Node<T> head; //头指针
    private Node<T> tail; //尾指针
    private int size; //队列大小

    //初始化
    public LinkQueue(){
        head = tail = new Node<>(); //创建头结点，不存储具体数据
        //空队列为head和tail指向头结点
    }

    //入队
    public void enQueue(T val){
        Node<T> newNode = new Node<T>(val); //创建新结点

        tail.setNext(newNode); //指向新结点
        newNode.setNext(null); //队尾的next必为空
        tail = newNode; // 设置新队尾。
        size++;
    }

    //出队
    public T deQueue(){
        //处理队空
        if(head==tail){
            throw new NoSuchElementException("队列中没有元素");
        }

        T val = head.getNext().getData(); //获取队头元素

        head.setNext( head.getNext().getNext()); //出队

        //出队后，如果head.getNext为空，则代表队列中只有一个元素，则需更新尾指针
        if(head.getNext()==null){
            tail = head;
        }
        size--;
        return val;
    }

    // 查看队头元素（不移除）
    public T peek() {
        if (head==tail) {
            throw new NoSuchElementException("队列为空，无法获取队头元素");
        }
        return head.getNext().getData();  // 使用getter方法
    }

    //清空队列
    public void clear(){
        Node<T> p = head.getNext();

        while(p!=null){
            Node<T> temp = p.getNext();
            p.setNext(null);
            p=temp;
        }
        head.setNext(null);
        tail = head;
        size= 0;
    }


    // 查看队列元素

    public void show(){
        if(head==tail)
            throw new NoSuchElementException("队列为空");

        Node<T> current = head.getNext(); //获取首元结点
        while(current!=null){
            System.out.print(current.getData()+" ");
            current = current.getNext();
        }
        System.out.println();
    }


    public static void main(String[] args){
        LinkQueue<Integer> linkQueue =new LinkQueue<Integer>();

        for(int i=0;i<10;i++){
            Random ran = new Random();
            Integer val = ran.nextInt(999 - 100 + 1) + 100; //自动装箱
            linkQueue.enQueue(val);
        }

        linkQueue.show();
        System.out.println(linkQueue.peek());
        System.out.println("被出队的元素:"+linkQueue.deQueue());
        linkQueue.show();
    }

}
