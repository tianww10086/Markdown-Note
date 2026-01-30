package Data_Structure.Tree;

public class ParentTree{
    private static final int CAPACITY=100;
    private Node nodes[];
    int root ,length;

    static class Node{
        private char data;
        private int parent;

        public Node(int parent, char data) {
            this.parent = parent;
            this.data = data;
        }

        public char getData(){
            return data;
        }

        public int getParent(){
            return parent;
        }

        public void setParent(int index){
            
        }
    }


    //构造函数，给数组分配内存
    public ParentTree(){
        nodes  = new Node[CAPACITY];
        root=0;
        length=0;
    }

    //构造树结构
    public void createTree(int n){
        if(n<=0||n>CAPACITY)
            throw new IllegalArgumentException("非法参数:"+ n);

       
    }

}