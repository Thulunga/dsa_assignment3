#include<stdio.h>
#include<stdlib.h>

struct node{
  int key;
  struct node *left,*right;
  int height;
};

struct node * createnode(int element){
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = element;
  temp->left = temp->right = NULL;
  temp->height = 0;
  return temp;
}

int height(struct node * r){
  if(r == NULL){
    return -1;
  }
  return r->height;
}

int getbalance(struct node *r){
  return (height(r->left)-height(r->right));
}

int max(int a,int b){
  if(a>b){
    return a;
  }
  return b;
}

struct node * minimum(struct node *r){
  if(r->left == NULL){
    return r;
  }
  else{
    return minimum(r->left);
  }
}

void parent(struct node *root,struct node *x,struct node *p){
  if(x->key < root->key){
     p = root;
    parent(root->left,x,p);
  }
  else if(x->key > root->key){
    p = root;
    parent(root->right,x,p);
  }
}

struct node * rotate_left(struct node *x){
  struct node *y = x->right;
  if(y != NULL){
    x->right = y->left;
    x->height = 1 + max(height(x->left),height(x->right));
    y->left = x;
    y->height = 1 + max(height(y->left),height(y->right));
    return y;
  }
  return x;
}

struct node * rotate_right(struct node *x){
  struct node *y = x->left;
  if(y != NULL){
    x->left = y->right;
    x->height = 1 + max(height(x->left),height(x->right));
    y->right = x;
    y->height = 1 + max(height(y->left),height(y->right));
    return y;
  }
  return x;
}

struct node * insert(struct node *root,int element){
  if(root == NULL){
    return createnode(element);
  }
  else{
    if(element < root->key){
      root->left = insert(root->left,element);
    }
    else{
      root->right = insert(root->right,element);
    }
    int balance = getbalance(root);
    if(balance > 1 && element < root->left->key){
      root = rotate_right(root);
    }
    if(balance < -1 && element > root->right->key){
      root = rotate_left(root);
    }
    root->height = 1 + max(height(root->left),height(root->right));
    return root;
  }
}

struct node * search(struct node *root,int element){
  if(root == NULL || root->key == element){
    return root;
  }
  else if(root->key > element){
    return search(root->left,element);
  }
  else{
    return search(root->right,element);
  }
}

//==================================
// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 
struct node * delete_node(struct node *root, int key) 
{ 
    // STEP 1: PERFORM STANDARD BST DELETE 
  
    if (root == NULL) 
        return root; 
  
    // If the key to be deleted is smaller than the 
    // root's key, then it lies in left subtree 
    if ( key < root->key ) 
        root->left = delete_node(root->left, key); 
  
    // If the key to be deleted is greater than the 
    // root's key, then it lies in right subtree 
    else if( key > root->key ) 
        root->right = delete_node(root->right, key); 
  
    // if key is same as root's key, then This is 
    // the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct node *temp = root->left ? root->left : 
                                             root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            struct node* temp = minimum(root->right); 
  
            // Copy the inorder successor's data to this node 
            root->key = temp->key; 
  
            // Delete the inorder successor 
            root->right = delete_node(root->right, temp->key); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return root; 
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getbalance(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && getbalance(root->left) >= 0) 
        return rotate_right(root); 
  
    // Left Right Case 
    if (balance > 1 && getbalance(root->left) < 0) 
    { 
        root->left =  rotate_left(root->left); 
        return rotate_right(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getbalance(root->right) <= 0) 
        return rotate_left(root); 
  
    // Right Left Case 
    if (balance < -1 && getbalance(root->right) > 0) 
    { 
        root->right = rotate_right(root->right); 
        return rotate_left(root); 
    } 
  
    return root; 
} /*
//=================================
struct node * delete_node(struct node *root,struct node *x){
  if(root == NULL){
    return root;
  }
  else{
    if(root->key != x->key){
      if(x->key < root->key){
        root->left = delete_node(root->left,x);
       // if(getbalance(root)<-1){
          //return rotate_left(root);
        //}
        return root;
      }
      else if(x->key > root->key){
        root->right = delete_node(root->right,x);
        //if(getbalance(root)>1){
         // return rotate_right(root);
        //}
        return root;
      }
    }
    else{
      if(root->left == NULL && root->right == NULL){
        return NULL;
      }
      else{
        if(root->left == NULL){
          return root->right;
        }
        else if(root->right == NULL){
          return root->left;
        }
        else{
          struct node *y = minimum(root->right);
          struct node *z  = delete_node(root->right,y);
          y->right = z;
          y->left = root->left;
          y->height = 1 + max(height(y->right),height(y->left));
          return y;
        }
      }
    }
  }
}*/

int isAVL(struct node *root){
  if(root == NULL){
    return 1;
  }
  else{
    int balance = getbalance(root);
    if(balance >= -1 && balance <= 1){
      if(isAVL(root->left)==1 && isAVL(root->right)==1){
        return 1;
      }
      else{
        return 0;
      }
    }
    else{
      return 0;
    }
  }
}

void preorder(struct node *root,FILE *fo){
  if(root == NULL){
    fprintf(fo,"()");
  }
  else{
    fprintf(fo,"(");
    fprintf(fo,"%d",root->key);
    if(root->left != NULL || root->right != NULL){
      preorder(root->left,fo);
      preorder(root->right,fo);
    }
    fprintf(fo,")");
  }
}

int main(){
  FILE *fin = fopen("input.txt","r");
  FILE *fo = fopen("output.txt","w");
  int k;
  struct node *root = NULL;
  do{
    fscanf(fin,"%d",&k);
    switch (k) {
      case 1:{
      int element;
      fscanf(fin,"%d",&element);
      root = insert(root,element);
      break;
      }
      case 2:{
        int element;
        fscanf(fin,"%d",&element);
        struct node *x = search(root,element);
        if(x != NULL){
          root = delete_node(root,element);
        }
        break;
      }
      case 3:{
        int element;
        fscanf(fin,"%d",&element);
        struct node *x = search(root,element);
        if(x != NULL){
          struct node *p=NULL;
          parent(root,x,p);
          if(p==NULL){
            root = rotate_left(root);
          }
          else{
            p = rotate_left(x);
          }
        }
        break;
      }
      case 4:{
        int element;
        fscanf(fin,"%d",&element);
        struct node *x = search(root,element);
        if(x != NULL){
          struct node *p=NULL;
          parent(root,x,p);
          if(p==NULL){
            root = rotate_right(root);
          }
          else{
            p = rotate_right(x);
          }
        }
        break;
      }
      case 5:{
        int element;
        fscanf(fin,"%d",&element);
        struct node *x = search(root,element);
        if(x != NULL){
          fprintf(fo,"%d\n",getbalance(x));
        }
        break;
      }
      case 6:{
        preorder(root,fo);
        fprintf(fo,"\n");
        break;
      }
      case 7:{
        if(isAVL(root)==1){
          fprintf(fo,"TRUE\n");
        }
        else{
          fprintf(fo,"FALSE\n");
        }
        break;
      }
      case 8:{
        int element;
        fscanf(fin,"%d",&element);
        if(search(root,element)==NULL){
          fprintf(fo,"FALSE\n");
        }
        else{
          fprintf(fo,"TRUE\n");
        }
        break;
      }
    }
  }while(k != 9);
}
