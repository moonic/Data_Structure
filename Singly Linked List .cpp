//单链表定义
struct Node  
{  
  ElemType data;  
  struct Node *next;  
};  
typedef struct Node LNode;  
typedef struct Node *LinkedList;  


//初始化 

void LinkedListInit1(LinkedList L)  
{  
  L=NULL;  
}  
//带头结点的单链表的初始化  
void LinkedListInit2(LinkedList L)  
{   
  L=(LNode *)malloc(sizeof(LNode));  
  if(L==NULL)  
  {  
    printf("申请空间失败！");  
    exit(0);  
  }  
  L->next=NULL;  
}  


//带头结点的单链表求表长  
int LinkedListLength(LinkedList L)  
{  
  LNode *p;            //p需要声明为LNode类型  
  p=L->next;  
  int j=0;  
  while(p!=NULL)  
  {  
    j++;  
    p=p->next;         //将p向下移动一个结点  
  }  
  return j;  
}  


//带头结点的单链表取元素操作  
LinkedList LinkedListGetINode(LinkedList L, int i)  
{  
  LNode *p;  
  p=L->next;  
  int j=1;  
  while((p!=NULL)&&(j<i))  
  {  
    p=p->next;  
    j++;  
  }  
  return p;  
}  

//带头结点的单链表定位操作  
LNode LinkedListLocateE(LinkedList L, ElemType e)  
{  
  LNode *p;  
  p=L->next;  
  while((p!=NULL)&&(p->data!=e))  
  {  
    p=p->next;  
  }  
  return p;  
}  

//不带头结点的单链表的插入操作  
void LinkedListInertQE1(LinkedList L, LinkedList p, ElemType e)  
{  
  q=(LNode *)malloc(sizeof(LNode));        //创建一个新的结点q  
  if(q==NULL)  
  {  
    printf("申请空间失败！");  
    exit(0);  
  }  
  q->data=e;  
  
  if(p==L)   //在表头插入  
  {  
    q->next=L;  
    L=q;  
  }  
  else      //在表的中间进行插入  
  {  
    pre=L;  
    while((pre!=NULL)&&(pre->next!=p))           //寻找p的前驱  
       pre=pre->next;  
  
    q->next=pre->next;  
    pre->next=q;  
  }  
}  
  
//带头结点的单链表的插入操作  
void LinkedListInertQE2(LinkedList L, LinkedList p, ElemType e)  
{  
  q=(LNode *)malloc(sizeof(LNode));        //创建一个新的结点q  
  if(q==NULL)  
  {  
    printf("申请空间失败！");  
    exit(0);  
  }  
  q->data=e;  
  
  //插入新的结点  
  pre=L;  
  while((pre!=NULL)&&(pre->next!=p))           //寻找p的前驱  
    pre=pre->next;  
  
  q->next=pre->next;  
  pre->next=q;  
}  

//不带头结点的单链表的删除操作  
void LinkedListDeleteQE1(LinkedList L, LinkedList p, ElemType e)  
{  
   pre=L;  
   while((pre!=NULL)&&(pre->next->data!=e))      //查找元素e的前驱  
       pre=pre->next;  
   p=pre->next;  
  
   if(p!=NULL)                //找到需要删除的结点  
   {  
     if(p==L)                 //删除的是第一个结点  
       L=p->next;  
     else                     //删除的是其他结点  
       pre->next=p->next;  
     free(p);  
   }  
}  
//带头结点的单链表的删除操作  
void LinkedListDeleteQE2(LinkedList L, LinkedList p, ElemType e)  
{  
   pre=L;  
   while((pre!=NULL)&&(pre->next->data!=e))      //查找元素e的前驱  
       pre=pre->next;  
   p=pre->next;  
  
   if(p!=NULL)                //找到需要删除的结点  
   {  
     pre->next=p->next;  
     free(p);  
   }  
}  
