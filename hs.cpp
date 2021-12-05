#include<iostream>
using namespace std;
enum kind{Active,Empty,Deleted};
class ArrayHashTable//闭散列法
{
    public:
        ArrayHashTable(const int d,int sz=20)
		{
            tableSize=sz;
            divitor=d;
            table=new int[tableSize];
            info=new kind[tableSize];
            for(int i=0;i<tableSize;i++)
			{
                table[i]=0;
                info[i]=Empty;
            }
        }
        ~ArrayHashTable()
		{
            delete[] table;
            delete[] info;
        }
        bool findPos(int k,int &i)//寻找k关键码所在位置i
		{
            i=k%divitor;
            int j=i;
            do
			{
                if(info[i]==Active&&table[i]==k)
                    return true;
                if(info[i]==Empty)
                    return false;
                i=(i+1)%tableSize;
            }
            while(j!=i);
            return false;
        }
        bool insert(int k)//插入关键码k
		{
            int i;
            if(findPos(k,i))
                return false;
            if(info[i]!=Active)
			{
                table[i]=k;
                info[i]=Active;
                return true;
            }else
                return false;
        }
        bool remove(int k)//删除关键码k
		{
            int i;
            if(!findPos(k,i))
                return false;
            table[i]=Deleted;
            return true;
        }
        int *getArray()
		{
            return table;
        }
    private:
        int divitor;
        int tableSize;
        int *table;
        kind *info;
};


class Node
{
    public:
        int data;
        Node *next;
        Node(int d,Node *n=NULL)
		{
            data=d;
            next=n;
        }
};
class LinkedHashTable//开散列法
{
    public:
        LinkedHashTable(int d,int sz=20)
		{
            tableSize=sz;
            divitor=d;
            hs=new Node*[sz];
            for(int i=0;i<sz;i++)
            hs[i]=new Node(0);
        }
        ~LinkedHashTable()
		{
            delete []hs;
        }
        bool findPos(int k,Node *&p,Node *&last)
		{
            int i=k%divitor;
            last=hs[i];
            p=hs[i]->next;
            while(p!=NULL&&p->data!=k)
			{
                p=p->next;
                last=last->next;
            }
            if(p!=NULL&&p->data==k)
                return true;
             else
                 return false;
        }
        bool insert(int k)
		{
            Node *p,*last;
            int i=k%divitor;
            if(findPos(k,p,last))
                return false;
            last->next=new Node(k);
            return true;
        }
        bool remove(int k)
		{
            Node *p,*last;
            if(!findPos(k,p,last))
                return false;
            last->next=p->next;
            return true;
        }
        Node **getArray()
		{
            return hs;
        }
    private:
        int divitor;
        int tableSize;
        Node **hs;
};

void test(Node *&q)
{
    q=new Node(4);
}
int main()
{
    //闭散列法
    ArrayHashTable *hs=new ArrayHashTable(11,12);
    int a[]={37,25,14,36,49,68,57,11};
    for(int i=0;i<8;i++)
        hs->insert(a[i]);
    int *array=hs->getArray();
    for(int i=0;i<12;i++){
        cout<<array[i]<<" ";
    }
    delete hs;

    //开散列法
//    LinkedHashTable *hs=new LinkedHashTable(11,12);
//    int a[]={37,25,14,36,49,68,57,11};
//    for(int i=0;i<8;i++)
//        hs->insert(a[i]);
//    Node **array=hs->getArray();
//    for(int i=0;i<12;i++){
//        Node *p=array[i]->next;
//        while(p!=NULL){
//            cout<<p->data<<" ";
//            p=p->next;
//        }
//        cout<<endl;
//    }
//    delete hs;
    return 0;
}
