#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node{
  int key;
  int degree;
  struct node *parent,*child,*sibling;
};

struct node *H = NULL;
struct node *disp[10001]={NULL};

struct node * Create_Node(int val){
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = val;
  temp->parent = temp->child = temp->sibling = NULL;
  temp->degree = 0;
  return temp;
}

struct node * Merge(struct node *H1,struct node *H2){
  if(H1 == NULL){
    return H2;
  }
  if(H2 == NULL){
    return H1;
  }
  //Now both will be present then only we perform this
  struct node *S = NULL;
  if(H1->degree <= H2->degree){
    S = H1;
    H1 = S->sibling;
  }
  else{
    S = H2;
    H2 = S->sibling;
  }
  struct node *H_new = S;
  while(H1!=NULL && H2!=NULL){
    if(H1->degree <= H2->degree){
      S->sibling = H1;
      S = H1;
      H1 = S->sibling;
    }
    else{
      S->sibling = H2;
      S = H2;
      H2 = S->sibling;
    }
  }
  if(H1 == NULL){
    S->sibling = H2;
  }
  if(H2 == NULL){
    S->sibling = H1;
  }
  return H_new;
}

struct node * Link(struct node *x,struct node *y){
  if(x->key > y->key){
    x->sibling = y->child;
    y->child = x;
    x->parent = y;
    y->degree++;
    return y;
  }
  else{
    y->sibling = x->child;
    x->child = y;
    y->parent = x;
    x->degree++;
    return x;
  }
}

struct node * Union(struct node *H1,struct node *H2){
  struct node *prev,*cur,*next;
  struct node *H_new = Merge(H1,H2);
  if(H_new == NULL){
    return H_new;
  }
  prev = NULL;
  cur = H_new;
  next = cur->sibling;
  while(next != NULL){
    if((cur->degree < next->degree) || ((cur->degree == next->degree) && (next->sibling != NULL) && (next->degree == next->sibling->degree))){
      prev = cur;
      cur = next;
      next = next->sibling;
    }
    else{
      struct node *t,*b;
      t = next->sibling;
      b = Link(cur,next);
      if(prev == NULL){
        H_new = b;
      }
      else{
        prev->sibling = b;
      }
      b->sibling = t;
      cur = b;
      next = t;
    }
  }
  return H_new;
}

struct node * Insert(int val){
  struct node *new_node = Create_Node(val);
  return Union(H,new_node);
}

struct node * Minimum(){
  struct node *min = H,*cur = H;
  while(cur != NULL){
    if(cur->key < min->key){
      min = cur;
    }
    cur = cur->sibling;
  }
  return min;
}

struct node * Revert_list(struct node *H1){
  struct node *prev = NULL,*cur = H1,*next = H1->sibling;
  while(cur != NULL){
    cur->parent = NULL;
    cur->sibling = prev;
    prev = cur;
    cur = next;
    if(cur != NULL){
      next = cur->sibling;
    }
  }
  return prev;
}

struct node * Extract_Minimum(){
  //Find minimum
  struct node *min = Minimum(H);
  if(min == NULL){
    return min;
  }
  //Remove min from the root list
  if(min == H){
    H = H->sibling;
  }
  else{
    struct node *cur=H;
    while(cur->sibling != min){
      cur = cur->sibling;
    }
    cur->sibling = min->sibling;
  }
   min->sibling =  NULL;
  //Take union of subtrees of min and remaining root list
  struct node * q = min->child;
  if(q != NULL){
    q = Revert_list(q);
    H = Union(H,q);
    min->child = NULL;
  }
  return min;
}

struct node * Find(struct node *H1,int val){
  struct node *x = H1,*p = NULL;
  if(x->key == val){
    p = x;
    return p;
  }
  if(x->child != NULL && p == NULL){
     p = Find(x->child,val);
  }
  if(x->sibling != NULL && p == NULL){
    p = Find(x->sibling,val);
  }
  return p;
}

void Decrease_key(struct node *x,int val){
  if(x->key > val){
    x->key = val;
    struct node *y = x;
    struct node *z = x->parent;
    while((z != NULL) && (y->key < z->key)){
      int temp = y->key;
      y->key = z->key;
      z->key = temp;
      y = z;
      z = z->parent;
    }
  }
}

void Delete(int val){
  struct node * x = Find(H,val);
  if(x != NULL){
    Decrease_key(x,INT_MIN);
    struct node *y = Extract_Minimum();
  }
}

void Display(struct node *H1,FILE *fo){
  int c1=0;
  struct node *cur = H1;
  while(cur != NULL){
    disp[c1++] = cur;
    cur = cur->sibling;
  }
  int i=0;
  while(i<c1){
    fprintf(fo,"%d ",disp[i]->key);
    cur = disp[i]->child;
    while(cur != NULL){
      disp[c1++] = cur;
      cur = cur->sibling;
    }
    i++;
  }
}

int main(){
  FILE *fin = fopen("input.txt","r");
  FILE *fo = fopen("output.txt","w");
  char choice;
  do{
    //scanf("%c",&choice);
    fscanf(fin,"%c",&choice);
    if(choice == 'i'){
      int k;
      //scanf("%d",&k);
      fscanf(fin,"%d",&k);
      H = Insert(k);
    }
    else if(choice == 'x'){
      struct node *ex_min = Extract_Minimum();
      if(ex_min != NULL){
        //printf("%d\n",ex_min->key);
        //fprintf(fo,"%d\n",ex_min->key);
      }
      else{
        //printf("EMPTY\n");
        fprintf(fo,"EMPTY\n");
      }
    }
    else if(choice == 'm'){
      struct node *min = Minimum();
      if(min != NULL){
        //printf("%d\n",min->key);
        fprintf(fo,"%d\n",min->key);
      }
      else{
        //printf("EMPTY\n");
        fprintf(fo,"EMPTY\n");
      }
    }
    else if(choice == 'd'){
      int k;
      //scanf("%d",&k);
      fscanf(fin,"%d",&k);
      Delete(k);
      //printf("%d\n",Find(H,k)->key);
    }
    else if(choice == 'p'){
      Display(H,fo);
      //printf("\n");
      fprintf(fo,"\n");
    }
  }while(choice != 's');
}
