/* list.h --- 
  * 
  * Filename: list.h
  * Description: 链表抽象接口定义
  */
 
 /* Code: */
  
 #ifndef _list_h 
 #define _list_h
 
  
 
 #include "../commonlib/genlib.h"
 
 /*
  * struct :链表抽象类型,
  * listCDT:不完全类型，有待实现层去定义
  */
 typedef struct listCDT *listADT;
 
 
 
 /*
  * struct :链表单元结构定义
  * data:为了提高此属性的适用范围，特将它设为void *类型，在获取具体数据时，需要显式转换该指针类型为目标类型
  */
 typedef struct listCellT{
     void *data;              //此处用通用指针类型，便于存放各种指针类型的数据，只是在取指针类型时，需要强制转换一下指针类型。
     struct listCellT *next;  //指向下一个元素
 } *listCellP;
 
 /*************************************************************************
 *功能描述：创建新链表
 *参数列表： 
 *返回类型：
 **************************************************************************/
 listADT NewList(void);
 /*************************************************************************
 *功能描述：释放链表
 *参数列表：
 *返回类型：
 **************************************************************************/
 void FreeList(listADT list);
 
 /*************************************************************************
 *功能描述：在链表前端添加元素
 *参数列表：
 *返回类型：
 **************************************************************************/
 void AddCellAheadList(listADT list,listCellP cell);
 
 /*************************************************************************
 *功能描述：在链表后端添加元素
 *参数列表：
 *返回类型：
 **************************************************************************/
 void AddCellRearList(listADT list , listCellP cell);
 
 /*************************************************************************
 *功能描述：在链表前端删除元素
 *参数列表：
 *返回类型：
 **************************************************************************/
 listCellP RemoveCellAheadList(listADT list);
 
 /*************************************************************************
 *功能描述：在链表后端删除元素
 *参数列表：
 *返回类型：
 **************************************************************************/
 listCellP RemoveCellRearList(listADT list);
 
 /*************************************************************************
 *功能描述：链表长度
 *参数列表：
 *返回类型：
 **************************************************************************/
 int LenthList(listADT list);
 
 /*************************************************************************
 *功能描述：链表是否为空
 *参数列表：
 *返回类型：
 **************************************************************************/
 bool IsEmptyList(listADT list);
 
 /*************************************************************************
 *功能描述：回调函数（映射函数),用来在打印内容时，让客户端个性化信息
 *参数列表：
 *返回类型：
 **************************************************************************/
 typedef void (*printCell)(void *data);
  
 /*************************************************************************
 *功能描述：打印输出链表元素内容
 *参数列表：
 *返回类型：
 **************************************************************************/
 void PrintList(printCell printc,listADT list);
 
 
 #endif
 
 /* list.h ends here */
复制代码
链表单元结构定义

复制代码
/* list_impl.h --- 
 * 
 * Filename: list_impl.h
 * Description: 链表元素类型底层实现
 * Author: magc
 * Maintainer: 
 * Created: 五  8月 17 16:16:42 2012 (+0800)
 * Version: 
 * Last-Updated: 六  8月 18 00:39:43 2012 (+0800)
 *           By: magc
 *     Update #: 6
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* Code: */

#ifndef _list_impl_h
#define _list_impl_h

/*
 * struct :链表单元类型结构定义
 * 为了使这一种底层实现被多个抽象类型重用，特单独放到这个文件中，
 */
struct listCDT{
    int count;   //元素个数
    listCellP head;  //头部指针，指向链表的第一个元素
    listCellP rear;  ///尾部指针，指向链表最后个元素
};

#endif

/* list_impl.h ends here */
复制代码
注：将此类型定义单独出来，是为了让后面链表、堆栈和队列三个抽象类型都能引用到，都能重用这同一个类型定义。

链表抽象类型的实现：

复制代码
/* list.c --- 
 * 
 * Filename: list.c
 * Description:链表的实现 
 * Author: magc
 * Maintainer: 
 * Created: 五  8月 17 10:56:58 2012 (+0800)
 * Version: 
 * Last-Updated: 五  8月 17 23:50:32 2012 (+0800)
 *           By: magc
 *     Update #: 164
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 链表抽象类型的实现
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* Code: */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "../commonlib/genlib.h"
#include "../commonlib/strlib.h"
#include "list.h"
#include "list_impl.h"
/*************************************************************************
*功能描述：创建新链表
*参数列表：
*返回类型：
**************************************************************************/
listADT NewList(void){
    listADT list = New(listADT);
    list->count = 0;
    list->head = NULL;
    list->rear = NULL;
    return list;
    
}

/*************************************************************************
*功能描述：释放链表
*参数列表：
*返回类型：
**************************************************************************/
void FreeList(listADT list){
    //遍历各元素，将元素释放
    listCellP cell = list->head;

    //每个指针类型的属性都是看作地雷，一定要处理好。否则后患无穷。
    while(cell != NULL){
        list->head = list->head->next;
        FreeBlock(cell);
        cell = list->head;
    }
    FreeBlock(list);
}

/*************************************************************************
*功能描述：在链表前端添加元素
*参数列表：
*返回类型：
**************************************************************************/
void AddCellAheadList(listADT list,listCellP cell){

    //链接上头部元素
    cell->next = list->head;
    list->head = cell;
    //若空链表，即尾部指针为空时，要处理一下
    if(list->rear == NULL){
        list->rear = cell;
    }
    list->count++;
    //    printf("add--%x\n",list->head);
    
}


/*************************************************************************
*功能描述：在链表后端添加元素
*参数列表：
*返回类型：
**************************************************************************/
void AddCellRearList(listADT list , listCellP cell){

    //若为空链表时即头指针为NULL ，要处理头部指针
    if(list->head == NULL){
        list->head = cell;
    }
    //链接尾部元素
    if(list->rear != NULL){
        list->rear->next = cell;
    }
    list->rear = cell;
    list->count++;
    
}

/*************************************************************************
*功能描述：在链表前端删除元素
*参数列表：
*返回类型：
**************************************************************************/
listCellP RemoveCellAheadList(listADT list){
    if(list->head == NULL) return NULL;
    listCellP cell = list->head;

    list->head = list->head->next;
    cell->next = NULL;  //注意置NULL的次序，再向上一行，就会影响到list->head了。
    //若当前头指针已经为空，说明当前链表已空，需要将rear指针也置NULL
    if(list->head == NULL){
        list->rear = NULL;
    }
    list->count--;
    
    return cell;
    
}


/*************************************************************************
*功能描述：在链表后端删除元素
*参数列表：
*返回类型：
**************************************************************************/
listCellP RemoveCellRearList(listADT list){
    if(list->rear == NULL) Error("链表已为空\n");
    //若从尾部删除元素，则需要找到倒数第二个元素
    listCellP cell = list->head;
    while(cell->next != list->rear){
        cell = cell->next;
    }
    list->rear = cell;
    cell = cell->next;
    list->count--;
    return cell;
}

/*************************************************************************
*功能描述：链表长度
*参数列表：
*返回类型：
**************************************************************************/
int LenthList(listADT list){
    return (list->count);
}


/*************************************************************************
*功能描述：链表是否为空
*参数列表：
*返回类型：
**************************************************************************/
bool IsEmptyList(listADT list){
    return (list->count == 0);
}


/*************************************************************************
*功能描述：打印输出链表元素内容
*参数列表：printc:回调函数名称
*返回类型：
**************************************************************************/
void PrintList(printCell printc,listADT list){

    listCellP cell = list->head;
    if(cell == NULL){
        printf("链表为空。\n");
    }
    while(cell!=NULL){
        printc(cell->data);   //具体打印格式交给回调函数处理，给予客户端个性化机会。
        cell = cell->next;
    }
}



/* list.c ends here */
复制代码
堆栈接口定义：

复制代码
 /* stack.h --- 
  * 
  * Filename: stack.h
  * Description:抽象数据类型ADT--堆栈 
  * Author: magc
  * Maintainer: 
  * Created: 四  8月  9 08:59:34 2012 (+0800)
  * Version: 
  * Last-Updated: 六  8月 18 00:44:24 2012 (+0800)
  *           By: magc
  *     Update #: 88
  * URL: 
  * Keywords: 
  * Compatibility: 
  * 
  */
 
 /* Commentary: 
  * ADT 接口
  * 只定义行为，而不限制底层表示和实现
  * 
  */
 
 /* Change Log:
  * 2012-8-16 修改cellT结构，将其int属性改为carP类型，以适应栈内存放汽车信息
  * 2012-8-17 修改堆栈抽象类型基于链表抽象类型
  */
 
 /* Code: */
 #ifndef _stack_h
 #define _stack_h
 #include "../commonlib/genlib.h"
 #include "parking.h"
 #include "list.h"
 #include "list_impl.h"
 
 #define MaxStackSize 10
 
 
 
 typedef struct stackCDT *stackADT;
 
 // 堆栈单元类型重用链表抽象类型的单元类型，为了便于使用和理解，给它起了个本土名字。
 
 typedef listCellP stackElement;
 
 /** 2012-8-17  改为基于list单元结构的
 typedef struct cellT{  
     carP car;
     struct cellT *next;
 } * stackElement;
 
 
 **/
 /*************************************************************************
 *功能描述：创建新堆栈
 *参数列表：
 *返回类型：堆栈指针
 **************************************************************************/
 stackADT NewStack(void);
 
 /*************************************************************************
 *功能描述：释放堆栈内存空间
 *参数列表：
 *返回类型：
 **************************************************************************/
 void FreeStack(stackADT stack);
 
 /*************************************************************************
 *功能描述：压栈
 *参数列表：
 *返回类型：
 **************************************************************************/
 void Push(stackADT stack ,stackElement element );
 
 /*************************************************************************
 *功能描述：出栈
 *参数列表：
 *返回类型：弹出的元素
 **************************************************************************/
 stackElement Pop(stackADT stack);
 
 /*************************************************************************
 *功能描述：判断当前栈是否为空
 *参数列表：
 *返回类型：TRUE or FALSE
 **************************************************************************/
 bool StackIsEmpty(stackADT stack );
 
 /*************************************************************************
 *功能描述：判断当前栈是否已满
 *参数列表：
 *返回类型：
 **************************************************************************/
 bool StackIsFull(stackADT stack);
 
 /*************************************************************************
 *功能描述：获取当前栈的深度
 *参数列表：
 *返回类型：
 **************************************************************************/
 int StackDepth(stackADT stack);
 
 /*************************************************************************
 *功能描述：读取堆栈顶端元素值
 *参数列表：
 *返回类型：
 **************************************************************************/
 int StackTop(stackADT stack);
 
 /*************************************************************************
 *功能描述：打印堆栈元素的内容
 *参数列表：
 *返回类型：
 **************************************************************************/
 void StackPrint(stackADT stack);
 
 #endif
 /* stack.h ends here */
复制代码
堆栈抽象类型的实现：

复制代码
 /* stack1.c --- 
  * 
  * Filename: stack.c
  * Description: 堆栈ADT的实现（链表实现方式）
  * Author: magc
  * Maintainer: 
  * Created: 三  8月 15 08:49:21 2012 (+0800)
  * Version: 
  * Last-Updated: 六  8月 18 00:47:35 2012 (+0800)
  *           By: magc
  *     Update #: 297
  * URL: 
  * Keywords: 
  * Compatibility: 
  * 
  */
 
 /* Commentary: 
  * 底层采用链表的形式实现堆栈
  * 同样实现stack.h接口中的行为
  * 堆栈的行为，基于链表抽象类型的行为来实现。即重用链表类型
  */
 
 /* Change Log:
  * 2012-8-16 修改Push和PoP,压栈和出栈参数为栈单元类型，
  * 2012-8-17 修改Pop方法，将弹出的元素next属性适时置NULL
  */
 
 /* Code: */
 #include <assert.h>
 #include <ctype.h>
 #include <errno.h>
 #include <limits.h>
 #include <string.h>
 #include <stdarg.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include "../commonlib/genlib.h"
 #include "stack.h"
 
 // 为了重用链表的类型和行为，使链表作为堆栈类型的一个属性，将它包装起来，所以它的行为都是可以重用链表的。
 struct stackCDT {
     listADT list;
 };
     
 /*************************************************************************
 *功能描述：创建新堆栈实例 
 *参数列表：
 *返回类型：空堆栈
 **************************************************************************/
 stackADT NewStack(void){
     stackADT stack = New(stackADT);
     listADT list = NewList();
     stack->list = list;
     return stack;
 }
 
 /*************************************************************************
 *功能描述：释放堆栈内存空间(每个元素的空间都需要释放)
 *参数列表：
 *返回类型：
 **************************************************************************/
 void FreeStack(stackADT stack){
     FreeList(stack->list);
     FreeBlock(stack);
 }
 
 
 /*************************************************************************
 *功能描述：压栈 head始终指向栈顶，压栈是从head端添加元素
 *参数列表：
 *返回类型：
 **************************************************************************/
 void Push(stackADT stack ,stackElement element){
     AddCellAheadList(stack->list,element);
 }
 
 /*************************************************************************
 *功能描述：出栈(将栈顶元素弹出)
 *参数列表：
 *返回类型：弹出的元素
 **************************************************************************/
 stackElement Pop(stackADT stack){
     if(stack == NULL){
         Error("堆栈为NULL");
     }
     //printf("test---%d\n",stack->list->count);
     
     stackElement temp = RemoveCellAheadList(stack->list);
     return temp;
 }
 
 /*************************************************************************
 *功能描述：判断当前栈是否为空
 *参数列表：
 *返回类型：TRUE or FALSE
 **************************************************************************/
 bool StackIsEmpty(stackADT stack ){
     return (stack->list->count == 0);
     
 }
 /*************************************************************************
 *功能描述：判断当前栈是否已满
 *参数列表：
 *返回类型：
 **************************************************************************/
 bool StackIsFull(stackADT stack){
     return (stack->list->count == MaxStackSize);
 }
 
 
 /*************************************************************************
 *功能描述：获取当前栈的深度
 *参数列表：
 *返回类型：
 **************************************************************************/
 int StackDepth(stackADT stack){
     return stack->list->count;
 }
 
 /*************************************************************************
 *功能描述：读取堆栈顶端元素值
 *参数列表：
 *返回类型：
 **************************************************************************/
 int StackTop(stackADT stack){
     if(stack->list->count == 0)return NULL;
     return stack->list->head;
 }
 /*************************************************************************
 *功能描述：打印单元信息（作为回调函数）
 *参数列表：
 *返回类型：
 **************************************************************************/
 
 
 static void printCar(void *data){
     printf("%s,",((carP)data)->number_id);
     
  }
 
 
 /*************************************************************************
 *功能描述：打印堆栈元素的内容
 *参数列表：
 *返回类型：
 **************************************************************************/
 void StackPrint(stackADT stack){
     if(stack->list->count == 0) return ;
     printf("共%d个元素:",StackDepth(stack));
     PrintList( printCar,stack->list);
     
     /***
     stackElement element = NULL;
     for(element = stack->list->head;element!=NULL;element = element->next){
         printf("%s,",((carP)element->data)->number_id);
     }
     *****/
     
     printf("\n");
     
 }
 
 
 /*************************************************************************
 *功能描述：主函数
 *参数列表：
 *返回类型：
 
 int main(int argc, char * argv[])
 {
     stackADT stack = NewStack();
     Push(stack,45);
     Push(stack,55);
     Push(stack,66);
     Pop(stack);
     
     StackPrint(stack);
     printf("\n");
     
     
 }
 **************************************************************************/
 
 
 
 
 
 
 /* stack1.c ends here */
复制代码
队列抽象类型的接口定义：

复制代码
 /* queue.h --- 
  * 
  * Filename: queue.h
  * Description:队列抽象类型 接口 
  * Author: magc
  * Maintainer: 
  * Created: 三  8月 15 15:48:10 2012 (+0800)
  * Version: 
  * Last-Updated: 六  8月 18 00:48:43 2012 (+0800)
  *           By: magc
  *     Update #: 69
  * URL: 
  * Keywords: 
  * Compatibility: 
  * 
  */
 
 /* Commentary: 
  * 以一个整数队列为例
  * 定义队列的行为：创建/销毁/入队/出队等，遵守先进先出，队首出，队尾入规则。
  * 
  */
 
 /* Change Log:
  * 2012-8-17 修改队列抽象类型基于链表抽象类型
  * 
  */
 
 /* Code: */
 #ifndef _queue_h
 #define _queue_h
 
 #include "../commonlib/genlib.h"
 #include "list.h"
 #include "parking.h"
 #include "list_impl.h"
 
 #define MaxQueueLenth 100
 
     
 /*
  * struct :队列抽象类型结构定义
  * 
  */
 typedef struct queueCDT *queueADT;
 
 //队列的单元重用链表的，为了便于使用，给它起了一个本土名字。
 
 typedef listCellP qcellP ;
 
 /* 2012-8-17 注释，此结构定义改为重用链表list.h中的单元结构
  * struct :队列单元结构定义
  * 
 
 typedef struct qcellT{
     carP car;
     struct qcellT *next;
     
 } *qcellP;
  */
 /*************************************************************************
 *功能描述：创建一个新队列
 *参数列表：
 *返回类型：
 **************************************************************************/
 queueADT NewQueue(void);
 
 /*************************************************************************
 *功能描述：销毁一个队列
 *参数列表：
 *返回类型：
 **************************************************************************/
 void FreeQueue(queueADT queue);
 
 /*************************************************************************
 *功能描述：进入队列（自队尾进入）
 *参数列表：queue:队列实例，num:要进入队列的一个整数
 *返回类型：
 **************************************************************************/
 void EnQueue(queueADT queue , qcellP cell);
 
 /*************************************************************************
 *功能描述：出队列（自队首出）
 *参数列表：
 *返回类型：队列单元
 **************************************************************************/
 qcellP DeQueue(queueADT queue);
 
 /*************************************************************************
 *功能描述：判断队列是否已满
 *参数列表：
 *返回类型：
 **************************************************************************/
 bool QueueIsFull(queueADT queue);
 
 /*************************************************************************
 *功能描述： 判断是否为空队列
 *参数列表：
 *返回类型：
 **************************************************************************/
 bool QueueIsEmpty(queueADT queue);
 
 /*************************************************************************
 *功能描述：打印输出队列内容（由队首到队尾排列）
 *参数列表：
 *返回类型：
 **************************************************************************/
 void PrintQueue(queueADT queue);
 
 #endif
 /* queue.h ends here */
复制代码
队列抽象类型的实现 ：

复制代码
/* queue.c --- 
 * 
 * Filename: queue.c
 * Description:队列模型的实现 
 * Author: magc
 * Maintainer: 
 * Created: 三  8月 15 16:26:17 2012 (+0800)
 * Version: 
 * Last-Updated: 六  8月 18 00:51:18 2012 (+0800)
 *           By: magc
 *     Update #: 167
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 2012-8-17 修改代码，基于并重用链表抽象类型的。
 * 
 */

/* Code: */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "../commonlib/genlib.h"
#include "queue.h"
    //为了统一队列与链表抽象类型，将链表类型作为它的一个属性,它的行为也就可以重用链表的了。
struct queueCDT{
    listADT list;
};


/*
 * struct :定义队列类型的具体结构,跟实现方式相关
 * 

struct queueCDT{
    qcellP head;              //队首
    qcellP end;               //队尾
    int lenth;               //队列成员个数
};

*****/
/*************************************************************************
*功能描述：创建新队列 
*参数列表：
*返回类型：
**************************************************************************/
queueADT NewQueue(void){
    queueADT queue = New(queueADT);
    listADT list = NewList();
    queue->list = list;
    return queue;
}
/*************************************************************************
*功能描述：销毁队列
*参数列表：
*返回类型：
**************************************************************************/
void FreeQueue(queueADT queue){
    //销毁每个成员 
}

/*************************************************************************
*功能描述：进入队列（自队尾进入）
*参数列表：queue:队列实例，cell:要进入队列的一个整数
*返回类型：
**************************************************************************/
void EnQueue(queueADT queue , qcellP cell){
    //    qcellP cell = New(qcellP);
    //    cell->data = num;
    //    cell->next = NULL;
    AddCellRearList(queue->list,cell);

}

/*************************************************************************
*功能描述：出队列（自队首出）
*参数列表：
*返回类型：队列的成员类型
**************************************************************************/
qcellP DeQueue(queueADT queue){
    if(QueueIsEmpty(queue))return NULL;
    qcellP temp = RemoveCellAheadList(queue->list);
    return temp;
}

/*************************************************************************
*功能描述：判断队列是否已满
*参数列表：
*返回类型：
**************************************************************************/
bool QueueIsFull(queueADT queue){
    return (queue->list->count == MaxQueueLenth);
}


/*************************************************************************
*功能描述： 判断是否为空队列
*参数列表：
*返回类型：
**************************************************************************/
bool QueueIsEmpty(queueADT queue){
    return (queue->list->count == 0);
}
/*************************************************************************
*功能描述：打印单元信息（作为回调函数）
*参数列表：
*返回类型：
**************************************************************************/

static void printCar(void *data){
    printf("%s,",((carP)data)->number_id);
    
 }

/*************************************************************************
*功能描述：打印输出队列内容（由队首到队尾排列）
*参数列表：
*返回类型：
**************************************************************************/
void PrintQueue(queueADT queue){
    printf("当前队列共%d个成员：",queue->list->count);
    PrintList(printCar,queue->list);
    /****
    while(cursor != NULL){
        printf("%s,",((carP)cursor->data)->number_id);
        cursor = cursor->next;
    }
    ****/
    printf("\n");
}


/**
int main(int argc, char * argv[])
{
    queueADT queue = New(queueADT);
    EnQueue(queue,100);
    EnQueue(queue,200);
    EnQueue(queue,300);
    EnQueue(queue,400);
    DeQueue(queue);
    
    PrintQueue(queue);

    FreeQueue(queue);
    
    
}
**/

/* queue.c ends here */
复制代码
停车场管理主模块：

头文件：

复制代码
 /* parking.h --- 
  * 
  * Filename: parking.h
  * Description: 停车场头文件
  * Author: magc
  * Maintainer: 
  * Created: 四  8月 16 11:41:41 2012 (+0800)
  * Version: 
  * Last-Updated: 四  8月 16 16:37:40 2012 (+0800)
  *           By: magc
  *     Update #: 15
  * URL: 
  * Keywords: 
  * Compatibility: 
  * 
  */
 
 /* Commentary: 
  * 
  * 
  * 
  */
 
 /* Change Log:
  * 
  * 
  */
 
 /* Code: */
 
 #ifndef _parking_h
 #define _parking_h
 
 
 
 /*
  * struct :汽车结构类型定义
  * 
  */
 typedef struct carT{
     string start_time;           //进停车场时间
     string end_time;             //出停车场时间
     string number_id;            //车牌
     
 } *carP;
 
 
 #endif
 
 /* parking.h ends here */
复制代码
复制代码
/* parking.c --- 
 * 
 * Filename: parking.c
 * Description: 停车场管理仿真
 * Author: magc
 * Maintainer: 
 * Created: 四  8月 16 09:41:13 2012 (+0800)
 * Version: 
 * Last-Updated: 六  8月 18 01:14:52 2012 (+0800)
 *           By: magc
 *     Update #: 475
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* Code: */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "../commonlib/genlib.h"
#include "../commonlib/random.h"
#include "../commonlib/strlib.h"
#include "stack.h"
#include "queue.h"
#include "parking.h"
#define MaxParkNumber 10         //停车场内车位总数
#define UnitPrice 10             //每小时收费10


/*
 * struct :停车场结构定义
 * 
 */
typedef struct parkT{
    int car_total;               //当前停车场内车量总数
    int income_total;            //当前停车场的收入总数
    stackADT car_stack;          //停车场内车位
    queueADT car_queue;          //停车场外便道
} * parkP;


static string GenCarNumber(void);
static parkP NewPark(void);
static carP NewCar();
static void EnPartingStack(parkP park,carP car);
static void EnParking(parkP park,carP car);
static void EnParkingQueue(parkP park , carP car);
static bool IsFullParking(parkP park);
static bool IsEmptyParking(parkP park);
static void DeParking(parkP park,carP car);
static void ChargeParking(carP car);
static void PrintParking(parkP park);
/*************************************************************************
*功能描述： 主函数
*参数列表：
*返回类型：
**************************************************************************/
int main(int argc, char * argv[])
{
    
    parkP park = NewPark();
    int i;
    for (i = 0; i < 15; i++) {
        carP car = NewCar();
        EnParking(park,car);
    }
    PrintParking(park);
    //以下为模拟数据
    carP car_out = NewCar();
    car_out->number_id = "TJ48812";
    DeParking(park,car_out);

    car_out->number_id = "TJ87694";
    DeParking(park,car_out);

    car_out->number_id = "TJ93196";
    DeParking(park,car_out);

    car_out->number_id = "TJ59759";
    DeParking(park,car_out);
    
    car_out->number_id = "TJ44388";
    DeParking(park,car_out);

    car_out->number_id = "TJ82153";
    DeParking(park,car_out);

    //PrintList(printCar,park->car_stack);
    PrintParking(park);
    
    return 0;
}
/*************************************************************************
*功能描述：打印输出当前停车场的车辆信息
*参数列表：
*返回类型：
**************************************************************************/
static void PrintParking(parkP park){
    printf("停车场内");
    
    printf("\n");
    StackPrint(park->car_stack);
    printf("停车场便道");
    
    printf("\n");
    PrintQueue(park->car_queue);
    
}
/*************************************************************************
*功能描述：新进汽车
*参数列表：
*返回类型：
**************************************************************************/
static carP NewCar(){
    carP car = New(carP);
    car->number_id = GenCarNumber();
    return car;
}
/*************************************************************************
*功能描述：生成随机车牌号
*参数列表：
*返回类型：
**************************************************************************/
static string GenCarNumber(void){
    int num = RandomInteger(23000,99999);
    string number = IntegerToString(num);
    string prex = "TJ";
    string cn = Concat(prex,number);
    return cn;
}
/*************************************************************************
*功能描述：创建停车场 
*参数列表：
*返回类型：
**************************************************************************/
static parkP NewPark(void){
    parkP park = New(parkP);
    park->car_total = 0;
    park->income_total = 0;
    park->car_queue = NewQueue();
    park->car_stack = NewStack();
    return park;
}
/*************************************************************************
*功能描述：进入停车场
*参数列表：
*返回类型：
**************************************************************************/
static void EnParking(parkP park,carP car){
    if(IsFullParking(park)){
        //场内满时
        EnParkingQueue(park , car);
    }
    else{
        //场内有空位时
        EnPartingStack(park,car);
    }
    
}
/*************************************************************************
*功能描述：判断停车场内是否占满
*参数列表：
*返回类型：
**************************************************************************/
static bool IsFullParking(parkP park){
    return (park->car_total >= MaxParkNumber);
}
/*************************************************************************
*功能描述：判断停车场内是否为空
*参数列表：
*返回类型：
**************************************************************************/
static bool IsEmptyParking(parkP park){
     return (park->car_total == 0);
 }
/*************************************************************************
*功能描述：进入停车场内部
*参数列表：
*返回类型：
**************************************************************************/
static void EnPartingStack(parkP park,carP car){
    car->start_time = "234";//为了简化问题，这里随便设置一个时间
    stackElement element = New(stackElement);
    
    element->data = car;
    element->next = NULL;
    park->car_total ++;
    
    Push(park->car_stack,element);
    printf("车辆：%s进入停车场内\n",car->number_id);
}
/*************************************************************************
*功能描述：进入便道队列
*参数列表：
*返回类型：
**************************************************************************/
static void EnParkingQueue(parkP park , carP car){
    qcellP cell = New(qcellP);
    cell->data = car;
    cell->next = NULL;
    EnQueue(park->car_queue,cell);
    printf("车辆：%s进入便道队列\n",car->number_id);
}
/*************************************************************************
*功能描述：出场
*参数列表：
*返回类型：
**************************************************************************/
static void DeParking(parkP park,carP car){
    printf("%s出场\n",car->number_id);
    
    stackADT stack_temp = NewStack();   ///创建一个临时栈，用来为车让道时暂存。
    stackElement elem_temp = NULL;  
    elem_temp = Pop(park->car_stack);
    //比较当前临时弹出的车辆号码
    while(elem_temp->data!=NULL){
        if (StringEqual(((carP)elem_temp->data)->number_id,car->number_id)){
            break;// 当找到要走的车辆时，终止循环
        }
        Push(stack_temp,elem_temp);//将让道的车辆放入临时栈中
        
        elem_temp = Pop(park->car_stack);  //继续弹出

    }
    if(elem_temp == NULL){
        printf("在停车场内未找到%s\n",car->number_id);
    }
    ((carP)elem_temp->data)->end_time = "2343";//为了简化问题，这里随便设置一个时间
    ChargeParking((carP)(elem_temp->data));
    //将临时栈中车辆依次放回停车场内
    elem_temp = Pop(stack_temp);
    while(elem_temp!=NULL){
        ///    elem_temp->next = NULL;
        Push(park->car_stack,elem_temp);
        elem_temp = Pop(stack_temp);

    }
    //要從便道上隊首的車開進停車場內
    elem_temp = DeQueue(park->car_queue);  //是否可以统一单元类型
    if(elem_temp!=NULL){
        //        elem_temp->next = NULL;  //置NULL的过程应该由queue.c来完成
        Push(park->car_stack,elem_temp);
        
    }
    
    
}
/*************************************************************************
*功能描述：出场，收费
*参数列表：
*返回类型：
**************************************************************************/
static void ChargeParking(carP car){
    printf("车辆：%s 出场时间：%s,入场时间：%s\n",car->number_id,car->end_time,car->start_time);
    
}
/* parking.c ends here */
