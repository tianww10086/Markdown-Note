package Data_Structure.Tree;

import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class ParentTree{
    private static final int CAPACITY=100;
    private Node nodes[];
    int root ,length;

    static class Node{
        private char data;
        private int parent;

        public Node(char data,int parent) {
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

    //返回该树结点数
    public int getLength(){
        return this.length;
    }

    //构造树结构
    public void createTree(int n) throws IOException {
        if(n<=0||n>CAPACITY)
            throw new IllegalArgumentException("非法参数:"+ n);

        Scanner in = new Scanner(System.in);
        //根节点处理。
        System.out.println("请输入根节点数据");
        nodes[0] = new Node((char)System.in.read(),-1);
        length++;
        System.out.println("输入子节点数据，格式：data parent");
        for(int i=1;i<n;i++){
            nodes[i] = new Node(in.next().charAt(0),in.nextInt());
           length++;
        }
    }

    //根据数组构造树
    public void  generate(char[] data,int[] parent, int n){
        if(n<=0 || n>CAPACITY || data.length!=n || parent.length!=n){
            throw  new IllegalArgumentException("非法参数");
        }

        for(int i=0;i<n;i++){
            nodes[i] = new Node(data[i],parent[i]);
            this.length++;
        }
    }

    //判断树是否未空
    public boolean treeEmpty(){
        return getLength()==0|| nodes==null;
    }

    //返回树的深度
    public int depth(){
        if(treeEmpty())
            throw new IllegalStateException("树为空");

        //游标通过parent向上爬
        int cursor =getLength()-1;//先指向最后节点的父节点
        int depth=0;
        while(cursor!=-1){
            cursor = nodes[cursor].getParent();
            depth++;
        }

        return depth;
    }

    //返回根节点
    public char root(){
        return nodes[0].getData();
    }

    /* 查找index节点的父结点数据
    * @ param index表示节点所在下标
    * @return 不存在则返回空字符，存在则返回其对应父节点的data域
    * */
    public char parent(int index){
        if(index<0||index>=length)
            return '\0';
        return nodes[nodes[index].getParent()].getData();
    }


    //查看树结构
    public void show(){
        if(getLength()<=0 || this.nodes==null)
            throw new NoSuchElementException("树为空");

        System.out.println("parent\tdata");
        for(int i=0;i<getLength();i++){
            System.out.println(nodes[i].getData()+"\t"+nodes[i].getParent());
        }
    }



    public static void main(String[] args) throws IOException {
        ParentTree tree = new ParentTree(); //创建空树
        char[] data = {'R','A','B','C','D','E','F','G','H','K'};
        int[] parent={-1,0,0,0,1,1,3,6,6,6};
        tree.generate(data,parent,10);
        tree.show();
        System.out.println("该树的深度为："+tree.depth());
        System.out.println("该树的根节点为:"+tree.root());
        System.out.printf("索引1的双亲节点data域为："+tree.parent(1));
    }
}