#include<stdio.h>
#include<stdlib.h>

FILE *fp,*fs;

struct first_node{
  struct first_node *parent1;
  int data1;
};
//==================================================
struct second_node{
  struct second_node *parent2;
  int data2;
  int rank;
};
//==========================
struct data_set1{
struct first_node *head1;
};
struct data_set2{
struct second_node *head2;
};

struct data_set1 *a, *c;
struct data_set2 *b, *d;

int n1=0, n2=0, n3=0, n4=0, c1=0, c2=0, c3=0, c4=0;
struct first_node* get1(int p) 
{
  for(int i=0;i<n1;i++)
    if(a[i].head1->data1==p)
      return a[i].head1;
    return NULL;
}
struct second_node* get2(int p) 
{
  for(int i=0;i<n2;i++)
    if(b[i].head2->data2==p)
      return b[i].head2;
    return NULL;
}
struct first_node* get3(int p) 
{
  for(int i=0;i<n3;i++)
    if(c[i].head1->data1==p)
      return c[i].head1;
    return NULL;
}
struct second_node* get4(int p) 
{
  for(int i=0;i<n4;i++)
    if(d[i].head2->data2==p)
      return d[i].head2;
    return NULL;
}
void makedata_set1(int p)
{
  struct first_node* x;
  x=(struct first_node*)malloc(sizeof(struct first_node));
  x->data1=p;
  x->parent1=x;
  a = (struct data_set1 *) realloc(a, (n1+1)*sizeof(struct data_set1));         
  a[n1].head1=x;
  n1++;
}
void makedata_set2(int p)
{
  struct second_node* x;
  x=(struct second_node*)malloc(sizeof(struct second_node));
  x->data2=p;
  x->rank=0;
  x->parent2=x;
  b= (struct data_set2 *) realloc(b, (n2+1)*sizeof(struct data_set2));         
  b[n2].head2=x;
  n2++;
}
void makeset3(int p)
{
  struct first_node* x;
  x=(struct first_node*)malloc(sizeof(struct first_node));
  x->data1=p;
  x->parent1=x;
  c = (struct data_set1 *) realloc(c, (n3+1)*sizeof(struct data_set1));         
  c[n3].head1=x;
  n3++;
}

void makeset4(int p)
{
  struct second_node* x;
  x=(struct second_node*)malloc(sizeof(struct second_node));
  x->data2=p;
  x->rank=0;
  x->parent2=x;
  d = (struct data_set2 *) realloc(d, (n4+1)*sizeof(struct data_set2));         
  d[n4].head2=x;
  n4++;
}
struct first_node* finddata_set1(int p)
{
  c1++;
  struct first_node* x;
  x=get1(p);
  while(x->parent1!=x)
  {
    x=x->parent1;
    c1++;
  }
  return x;
}
struct second_node* finddata_set2(int p)
{
  c2++;
  struct second_node* x;
  x=get2(p);
  while(x->parent2!=x)
  {
    x=x->parent2;
    c2++;
  }
  return x;
}
struct first_node* findset3(int p)
{
  c3++;
  struct first_node* x;
  x=get3(p);
  if(x->parent1!=x)
  {
    x->parent1=findset3(x->parent1->data1);
  }
    return x->parent1;
  
  
}
struct second_node* findset4(int p)
{
  c4++;
  struct second_node* x;
  x=get4(p);
  if(x->parent2!=x)
  {
    x->parent2=findset4(x->parent2->data2);
  }
    return x->parent2;
  
  
}
void union1(int p, int q){
struct first_node *x, *y;
x = finddata_set1(p);
y = finddata_set1(q);
if(x == y)
  fprintf(fp,"%d ", x->data1);
else{
if(x != y)
   y->parent1 = x;
fprintf(fp,"%d ", x->data1);
}
}
//union two
void union2(int p, int q){
struct second_node *x, *y;
x = finddata_set2(p);
y = finddata_set2(q);
if(x == y)
  fprintf(fp,"%d ", x->data2);
else{
if(x->rank >= y->rank)
  {y->parent2 = x;
   fprintf(fp,"%d ", x->data2);
  }
else
  {x->parent2 = y;
   fprintf(fp,"%d ", y->data2);
  }

if(x->rank == y->rank)
  x->rank = x->rank + 1;
}
}
//=======================================================
void union3(int p, int q){
struct first_node *x, *y;
x = findset3(p);
y = findset3(q);
if(x == y)
  fprintf(fp,"%d ", x->data1);
else{
if(x != y)
   y->parent1 = x;
fprintf(fp,"%d ", x->data1);
}
}

void union4(int p, int q){
struct second_node *x, *y;
x = findset4(p);
y = findset4(q);
if(x == y)
  fprintf(fp,"%d\n", x->data2);
else{
if(x->rank >= y->rank)
  {y->parent2 = x;
   fprintf(fp,"%d\n", x->data2);
  }
else
  {x->parent2 = y;
   fprintf(fp,"%d\n", y->data2);
  }

if(x->rank == y->rank)
  x->rank = x->rank + 1;
}
}
//==================================================================
int main()
{

fs=fopen("input.txt","r");
  fp=fopen("output.txt","w");
  if(fs==NULL)
  {
    printf("error opening the file\n");
    exit(0);
  }
  
struct first_node *g1, *g3;
struct second_node *g2, *g4;

a = (struct data_set1 *) malloc(sizeof(struct data_set1));
b = (struct data_set2 *) malloc(sizeof(struct data_set2));
c = (struct data_set1 *) malloc(sizeof(struct data_set1));
d = (struct data_set2 *) malloc(sizeof(struct data_set2));

  int key,key1,key2;
  char ch;
int i;
  while(1)
  {
    fscanf(fs,"%c",&ch);
    if(ch=='m')
    {
      fscanf(fs,"%d",&key);
      for( i=0; i<n1; i++)
   if(a[i].head1->data1 == key)
     break;

 if(i!= n1)
   fprintf(fp,"PRESENT\n");

 else
  {makedata_set1(key);
   makedata_set2(key);
   makeset3(key);
   makeset4(key);
   fprintf(fp,"%d\n", key);
  }

    }
    else if(ch=='f')
    {
      fscanf(fs,"%d", &key);
      for(i=0; i<n1; i++)
        if(a[i].head1->data1 == key)
          break;

      if(i!= n1)
      {
        g1 = finddata_set1(key);
        fprintf(fp,"%d ", g1->data1);
        g2 = finddata_set2(key);
        fprintf(fp,"%d ", g2->data2);
        g3 = findset3(key);
        fprintf(fp,"%d ", g3->data1);
        g4 = findset4(key);
        fprintf(fp,"%d\n", g4->data2);
      }
      else 
        fprintf(fp,"NOT FOUND\n");

      }
    else if(ch=='u')
    { 
      fscanf(fs,"%d %d", &key1, &key2);
      for(i=0; i<n1; i++)
        if(a[i].head1->data1 == key1)
          break;
        if(i==n1)
        {      
          fprintf(fp,"ERROR ERROR ERROR ERROR\n");
          continue;
        }
        for(i=0; i<n1; i++)
          if(a[i].head1->data1 == key2)
            break;
        if(i== n1 )
      {
        fprintf(fp,"ERROR ERROR ERROR ERROR\n");
        continue;
      }
     
      union1(key1, key2);
      union2(key1, key2);
      union3(key1, key2);
      union4(key1, key2);

    }
    else if(ch=='s')
    {
      fprintf(fp,"%d ", c1);
      fprintf(fp,"%d ", c2);
      fprintf(fp,"%d ", c3);
      fprintf(fp,"%d\n", c4);
      break;
    }

  }
  fclose(fp);
  fclose(fs);
  return 0;
}
