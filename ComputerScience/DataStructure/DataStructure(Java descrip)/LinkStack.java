package Data_Structure;


//栈其实就是操作受限的单链表，只允许在栈顶操作
//我们设计头指针为栈顶。
public class LinkStack {
    private  int size;
    static class Node{
        private int data;
        private Node next;

        public Node(int val){
            this.data=val;
        }
        public Node getNext() {
            return next;
        }

        public void setNext(Node next) {
            this.next = next;
        }

        public int getData() {
            return data;
        }

        public void setData(int data) {
            this.data = data;
        }


    }


    private Node head;

    public LinkStack(){
        head=null;
        size=0;
    }

    //入栈
    public void push(int e){
        Node newNode = new Node(e);

        //头插法
        Node topNode = this.head; //保存当前栈顶
        newNode.setNext(topNode); //新元素指向旧栈顶
        head = newNode;
        this.size++;
    }

    //出栈
    public int pop(){
        if(head==null){
            throw new NullPointerException("链栈无元素");
        }
        int x = head.getData(); //获取栈顶元素

        Node oldTop = head; //记录旧栈顶
        head = head.getNext();

        oldTop.setNext(null);
        this.size--;
        return x;
    }

    //获取栈顶元素
    public int getTop(){
        if(head==null)
            throw  new NullPointerException("无元素");

        return head.getData();
    }

    public void show(){
        System.out.print("[");

        Node point = head;
        while(point!=null){

            System.out.print(point.getData());
            if(point.getNext()!=null){
                System.out.print(",");
            }
            point= point.getNext();

        }
        System.out.println("]");

    }

    public static void main(String[] args){
        LinkStack stack = new LinkStack(); //创建一个空链表
        for(int i=0;i<10;i++){
            stack.push((int)(Math.random()*100));
        }

        stack.show();
    }
}
