#include<stdio.h>
#include<stdlib.h>
struct first_list;
struct second_list;

struct node1{
	int data;
	struct first_list* set;
	struct node1* link;

};
struct node1* a[1000];
struct first_list
{
	struct node1* head;
	struct node1* tail;
};

struct node2{
	int data;
	struct node2* link;
	struct second_list* set;
};
struct node2* b[1000];
struct second_list
{
	struct node2* head;
	struct node2* tail;
	int size;
};
// function araeaaaaaaaa
struct second_list* union_1(int x,int y)
{
	struct node2* x1=b[x];
	struct node2* y1=b[y];
	struct second_list* l1=x1->set;
	struct second_list* l2=y1->set;
	l1->tail->link=l2->head;
	struct node2* z=l2->head;
	while(z!=NULL)
	{
		z->set=l1;
		z=z->link;
	}
	l1->tail=l2->tail;
	return l1;
}
//================================================
int make_set1(int key)
{
	struct node1* n=(struct node1*)malloc(sizeof(struct node1));
	struct first_list* l=(struct first_list*)malloc(sizeof(struct first_list));
	l->head=n;
	l->tail=n;
	n->link=NULL;
	n->data=key;
	n->set=l;
	a[key]=n;
	return key;
}	
int make_set2(int key)
{
	struct node2* n=(struct node2*)malloc(sizeof(struct node2));
	struct second_list* l=(struct second_list*)malloc(sizeof(struct second_list));
	l->head=n;
	l->tail=n;
	n->link=NULL;
	n->data=key;
	n->set=l;
	l->size=1;
	b[key]=n;
	return key;
}	
//================================================																							
int find_set1(int key)
{
	struct node1* n=a[key];
	return n->set->head->data;
}																						
int find_set2(int key)
{
	struct node2* n=b[key];
	return n->set->head->data; 
}
int union1(int x,int y)
{
	struct node1* a1=a[x];
	struct node1* a2=a[y];
	struct first_list* l1=a1->set;
	struct first_list* l2=a2->set;
	l1->tail->link=l2->head;
	struct node1* x1=l2->head;
	while(x1!=NULL)
	{
		x1->set=l1;
		x1=x1->link;
	}
	l1->tail=l2->tail;
	return l1->head->data;

}
//==========================================================
int union2(int x,int y)
{
	struct node2* a1=b[x];
	struct node2* a2=b[y];
	struct second_list* l1=a1->set;
	struct second_list* l2=a2->set;
	struct second_list*l=(struct second_list*)malloc(sizeof(struct second_list));
	if(l1->size>l2->size)
		l=union_1(x,y);
	else if(l1->size<l2->size)
		l=union_1(y,x);
	else
	{
		if(find_set2(x)>find_set2(y))
			l=union_1(y,x);
		else
			l=union_1(x,y);
	}
	l->size=l1->size+l2->size;
	return l->head->data;
}
//================================================
int main()
{

	char choice,ch;
	int x,y,l,k,p,q,m,n,key;
	FILE* fs=fopen("input.txt","r");
	FILE* fp=fopen("output.txt","w");
	for(int i=0;i<1000;i++)
	{
		a[i]=NULL;
		b[i]=NULL;
	}
	while(1)
	{
		fscanf(fs,"%c",&choice);
		if(choice=='m')
		{
			ch=getc(fs);
			fscanf(fs,"%d",&key);
			if(a[key]!=NULL)
				fprintf(fp,"PRESENT\n");
			else
			{
				p=make_set1(key);
				fprintf(fp,"%d\n",p);
				q=make_set2(key);
			}
		}
		else if(choice=='f')
		{
			ch=getc(fs);
			fscanf(fs,"%d",&key);
			if(a[key]==NULL)
				fprintf(fp,"NOT FOUND\n");
			else
			{
				m=find_set1(key);
				fprintf(fp,"%d ",m);
				n=find_set2(key);
				fprintf(fp,"%d\n",n);
			}


		}
		else if(choice=='u')
		{

			ch=getc(fs);
			fscanf(fs,"%d",&x);
			ch=getc(fs);
			fscanf(fs,"%d",&y);
			if(a[x]==NULL || a[y]==NULL)
				fprintf(fp,"ERROR\n");
			else
			{
				k=union1(x,y);
				fprintf(fp,"%d ",k);
				l=union2(x,y);
				fprintf(fp,"%d\n",l);
			}

		}
		else if(choice=='s')
			break;
	}



}