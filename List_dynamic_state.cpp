#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20      //线性表的初始大小
typedef int ElemType;   //线性表中的元素类型

  
typedef struct
{
    ElemType *data;
    int length;
}SqList;                //通过动态数组定义线性表结构体
 
void InitList(SqList *L)
//初始化操作，建立一个空的线性表L 
{
    L->data=(ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    if(!L->data)
        exit(-1);       //内存分配失败
    L->length=0;
    return;
}
void GetElem(SqList L, int i, ElemType *e)      
//将线性表L的第i个位置元素值返回给e 
{
    if ( (L.length==0)||(i<1)||(i>L.length) )
    {
        printf("出错\n");
        return;
    }
    *e=L.data[i-1];
    return;
}
void ListInsert(SqList *L,int i,ElemType e)
//在线性表L的第i个位置插入新元素e 
{
    if(L->length==MAXSIZE)
    {
        printf("线性表已满\n");   //这里可以通过realloc函数扩展线性表的大小，略
        return;
    }
    if(i<1||i>L->length+1)
    {
        printf("插入位置出错\n");
        return;
    }
    for(int k=L->length;k>=i;k--)
    {
        L->data[k]=L->data[k-1];
    }
    L->data[i-1]=e;
    L->length++;
    return;
}
 
void ListDelete(SqList *L,int i,ElemType *e)
//删除线性表L中的第i个位置元素，并用e返回其值 
{
    if(L->length==0)
    {
        printf("线性表为空\n");
        return;
    }
    if(i<1||i>L->length)
    {
        printf("位置出错\n");
        return;
    }
    *e=L->data[i-1];
    for(int k=i;k<l->length;k++)
    {
        L->data[k-1]=L->data[k];
    }
    L->length--;
    return; 
}
int ListLength(SqList L)
//返回线性表的元素个数 
{
    return L.length;
}
void show(SqList L)
{
    for(int i=0;i<l.length;i++) code="" d="" elemtype="" sqlist="" void=""></l.length;i++)></l->
 
