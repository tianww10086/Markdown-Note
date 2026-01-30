package Data_Structure;


// 双向链表
public class LinkList {
    private final Node head; //头结点
    private Node tail; //尾指针，用于优化尾插法
    private int size; //链表长度

    static class Node{
        private int val;// 数据
        private Node next; //next指针域
        private Node front; //front指针域
        public Node(){
            val=0;
            this.next=null;
        }

        public Node(int val)
        {
            this.val=val;
            this.next =null;
        }
        public int getVal() {
            return val;
        }

        public void setVal(int val) {
            this.val = val;
        }

        public Node getNext() {
            return next;
        }

        public void setNext(Node next) {
            this.next = next;
        }

        public Node getFront() {
            return front;
        }

        public void setFront(Node front) {
            this.front = front;
        }
    }


    //创建带头结点的双向链表
    public LinkList(){
        /*
        * 无头结点初始化如下：
        * head = null;
        * front =null;
        * */
        head = new Node(); //头结点
        tail  =head;
        head.setNext(null);
        head.setFront(null);
        this.size=0;
    }


    //返回第i个元素
    public int getElem(int i){
        if(i<1||i>size)
            throw new IllegalArgumentException();

        Node point = head.getNext();

        for(int j=1;j<i;j++){
            point=point.getNext();
        }

        return point.getVal();
    }


    //1<=i<=size+1; 在第i个位置插入元素val
    public void insertList(int i,int val){
       if(i<1 || i>size+1)
           throw new IllegalArgumentException("下标参数错误");
       Node newNode =  new Node(val);

       int j=0;
       Node Prev=this.head;

       //寻找第i-1个元素
        while(Prev!=null && j<i-1){
            Prev=Prev.getNext();
            j++;
        }
        Node tempPoint;
        assert Prev != null;
        tempPoint = Prev.getNext();



        Prev.setNext(newNode); //前结点向后连
        newNode.setFront(Prev); //新结点向前连

        newNode.setNext(tempPoint); //新结点向后连

        //temPoint为空代表是在尾部插入元素，此时维护尾指针
        if(tempPoint!=null){
            tempPoint.setFront(newNode); //后结点想前连接新结点
        }else
            tail=newNode;

        this.size++;


    }

    //头插法创建整表
    public void headInsert(int i){
        if(i<1)
            throw new IllegalArgumentException("方法参数需为正整数");

        for(int j=0;j<i;j++){
            int x = (int)(Math.random()*1000);
            Node newNode = new Node(x);
            Node firstNode = head.getNext();
            //将新结点与头结点连接
            newNode.setFront(head);
            head.setNext(newNode);
            if(firstNode!=null){
                firstNode.setFront(newNode);
            }else
                tail = newNode;
            newNode.setNext(firstNode);
            this.size++;
        }
    }



    //尾插法创建正表
    public void tailInsert(int n){
        if(n<1)
            throw new IllegalArgumentException("方法参数需为正整数");


        for(int i=0;i<n;i++){
            //找到最后一个结点

            int x = (int)(Math.random()*1000);
            Node newNode = new Node(x);

            newNode.setFront(tail);
            tail.setNext(newNode);
            tail = newNode;
            size++;
        }
    }

    //删除 1<=i<=size
    public void deleteList(int i){

        if(i<1||i>size)
            throw new IllegalArgumentException("非法参数i");

        Node prev = this.head;
        int j=0;
        while(prev!=null &&j<i-1){
            prev = prev.getNext();
            j++;
        }


        Node remove = prev.getNext();//被删除的元素
        prev.setNext(remove.getNext());

        if(remove.getNext()!=null)
            remove.getNext().setFront(prev);
        else
            tail=prev;
        remove.setFront(null);
        remove.setNext(null);
        remove=null;
        //跳过第i个元素
        this.size--;

    }

    //查看链表所有元素
    public static void show(LinkList list){
        if(list.size==0)
        {
            System.out.println("空链表");
            return;
        }

        Node point = list.head.getNext(); //获取首元元素
        System.out.print('[');

        for(int i=0;i<list.size;i++){
            System.out.print(point.getVal());
            point=point.getNext();
            if(i<list.size-1)
                System.out.print(",");
        }
        System.out.println(']');
    }



    public void clearList() {
        // 从第一个实际节点开始遍历
        Node current = head.getNext();

        // 遍历所有节点，断开它们的连接
        while (current != null) {
            Node nextNode = current.getNext();

            // 断开当前节点的连接
            current.setNext(null);
            current.setFront(null);

            // 移动到下一个节点
            current = nextNode;
        }

        // 清空头结点的连接
        head.setNext(null);
        head.setFront(null);

        // 重置大小
        size = 0;
    }


    //测试函数
    public static void main(String[] args){
        LinkList list = new LinkList(); //创建一个空链表
        list.tailInsert(15);

        show(list);
    }


}



