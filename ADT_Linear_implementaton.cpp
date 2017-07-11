#define ERROR 0 
#define OK 1 
struct STU
{ char name[20];
char stuno[10]; 
int age; int score; 
}stu[50]; 
struct LIST 
{ struct STU stu[50]; 
int length; 
}L; 

int printlist(struct LIST L)
{ int i;
printf("name stuno age score/n"); 
for(i=0;i<L.length;i++) 
printf("%s %s/t%d/t%d/n", L.stu[i].name, L.stu[i].stuno, L.stu[i].age, L.stu[i].score); 
printf("/n"); 
}

int listinsert(struct LIST *L,int i,struct STU e) 
{ struct STU *p,*q; 
if (i<1||i>L->length+1) 
return ERROR; 
q=&(L->stu[i-1]); 
for(p=&L->stu[L->length-1];p>=q;--p) 
*(p+1)=*p; *q=e; ++L->length; 
return OK; 
}/*ListInsert Before i */

main() 
{ struct STU e; 
L.length=0; 
strcpy(e.name,"zmofun"); 
strcpy(e.stuno,"100001"); 
e.age=80; 
e.score=1000; 
listinsert(&L,1,e); 
printlist(L); 
printf("List length now is %d./n/n",L.length);
strcpy(e.name,"bobjin"); 
strcpy(e.stuno,"100002"); 
e.age=80; 
e.score=1000; 
listinsert(&L,1,e); 
printlist(L); 
printf("List length now is %d./n/n",L.length); 
}
 
