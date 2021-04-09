// trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
using namespace std;
#include "Queue.h"

struct queueLL{
	struct Queue *q;
	struct queueLL* next;
};




struct Node* createNode(int data){
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	if(!newnode){
	printf("memeory error");
	return NULL;
	}
	newnode->data = data;
	newnode->right = newnode->left = NULL;
	return newnode;
	
}

int height(struct Node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}
Node* insertNode(struct Node* root,struct Queue q, int data){
	
	
	if(!root){
	root = createNode(data);
	return root;
	}
	enqueue(&q,root);
	while(q.front!=q.rear){
		struct Node* temp;
		temp = dequeue(&q);

		if(temp->left==NULL){
			temp->left = createNode(data);
			return root;
		}
		else
		{
			enqueue(&q,temp->left);
		}
		if(!temp->right){
		temp->right = createNode(data);
		return root;		
		}
		else{
		enqueue(&q,temp->right);
		}
	
	}

}

Node* findRightDeepestNode(struct Node* root){
		while(root->right!=NULL){
		root = root->right;
	}
	return root;
}

struct Node* findNode(struct Node* root, int key){
	struct Node* temp;
	
	
	if(root->data == key){
	cout<<"the key value is present in binary search tree bst";

	temp = root;
	return temp;
	}


	if(root->right== NULL||root->left==NULL)
	{

			return temp;		
	}
	

	

	findNode(root->left,key);
	findNode(root->right,key);
	

	////else{

	////cout<<"the key value is not present in binary search tree";
	////}
	
	
}

struct Node* prevNode(struct Node* root, int key){
	while(root->right->data!=key){
		root = root->right;
	}
	return root;

}



void deleteDeepestNode(struct Node* root,int key){
	struct Node* deepnode;
	deepnode = findRightDeepestNode(root);
	struct Node* deletenode= findNode(root, key);
	if(deletenode==NULL)
		cout<<"error";
	deletenode->data= deepnode->data;
	struct Node* prev = prevNode(root,deepnode->data);
	prev->right = NULL;
	free(deepnode);
}

int* inorder(Node* temp)
{
	static int arr[20] ={0};
    static int i=0;
	if (temp == NULL)
        return arr;
 
    inorder(temp->left);
    arr[i]=temp->data;
	i++;
    inorder(temp->right);
}

void preorder(Node* temp){
	if(!temp){
		return;}

	cout<<temp->data<<" ";
	preorder(temp->left);
	preorder(temp->right);

}

void getLevelNodes(struct Node* root,struct Queue *q,int level){
	if(!root)
		return;
	if(level==1){
		enqueue(q,root);
	}
	else if(level>1){
		getLevelNodes(root->left,q,level-1);
		getLevelNodes(root->right,q,level-1);
	
	}

}

struct queueLL* levelOrder(struct Node* root, int level){
	struct queueLL* qll;
	struct queueLL* temp;
	qll = temp = (struct queueLL*)malloc(sizeof(struct queueLL));
	temp->next=temp;
	struct Queue *q1 = (struct Queue*)malloc(sizeof(Queue));
	initialiseQueue(q1,1);
	enqueue(q1,root);
	temp->q = q1;
	for(int i=2;i<level+1;i++){
		//making queue for level i
		struct Queue *q= (struct Queue*)malloc(sizeof(Queue));
		int size = (int)(pow(2.0,i-1));
		initialiseQueue(q, size);
		//entering data for level i in order into queue
		getLevelNodes(root, q,i);	
		//printing values level wise
			//printQueue(&q);
			//cout<<"\n";
		//creating newnode for ll queuell
		int arr=1;
		struct queueLL* newnode = (struct queueLL*)malloc(sizeof(struct queueLL));
		newnode->q = q;
		newnode->next = NULL;
		//linking with linked list queuell
		temp->next = newnode;
		temp = temp->next;
		
	}

	return qll;
}
	
void print(queueLL *qo ,int maxlevel){
	int count=0;
	struct queueLL* temp; 
	temp =qo;
	//while(qo!= NULL){
	//count++;
	//qo = qo->next;
	//}
	//count-=1;
	//double maxval = pow(2.0,maxlevel);
	for(int i=0;1<maxlevel;i++){
		for(int j = i;j<maxlevel;j++){
			cout<<" ";
		}
			temp->q->front++;

		cout<<temp->q->arr[temp->q->front]->data;

		//printQueueSpecial(temp->q, maxlevel);
		while(temp->q->front != temp->q->rear){
			for(int j = i;j<maxlevel;j++){
			cout<<"   ";
			}
			temp->q->front++;
			cout<<temp->q->arr[temp->q->front]->data;
			
		}
		
		for(int j = 0; j<maxlevel-1;j++){
		cout<<"\n";
		}
		temp = temp->next;
	}



	//for(int i=0 ; i< maxlevel ; i++){
	//	printQueue(temp->q);
	//	temp =temp->next;
	//	cout<<"\n";
	//}

}
	

void nthInorder(struct Node* root,struct Queue *q,int n){
	
	if(!root){
	return;
	}


	//count++;

	nthInorder(root->left,q,n);
	enqueue(q,root);
	if(q->rear == n-1){
	
	cout<<q->arr[n-1]->data<<" ";
	
	}
	nthInorder(root->right,q,n);
	
}

void printCorner(struct queueLL* qll, int level){
	struct queueLL* temp = qll;
	for(int i=1;i<=level;i++){
		cout<<temp->q->arr[temp->q->front+1]->data<<" ";
		cout<<temp->q->arr[temp->q->rear]->data<<"\n";
		temp = temp->next;
	}

}

int searchRoot(int in[], int key, int start, int end){
	int i;
	for(i=start;i<end+1;i++){
		if(in[i]==key){
		return i;
		}
	
	}

}

struct Node* buildTreeFromInPre(int in[], int pre[], int start, int end){
	
	if(start>end){
	return NULL;
	}
	
	struct Node* root = (Node*)malloc(sizeof(Node));
	static int i=0;
	root->data = pre[i];
	i++;
	if(start == end){
	root->left =NULL;
	root->right = NULL;
	return root;
	}
	int root_index = searchRoot(in, root->data, start, end);
	root->left = buildTreeFromInPre(in , pre, start, root_index-1);
	root->right = buildTreeFromInPre(in, pre, root_index+1, end);
	return root;


}


//struct Node* buildTreeInLevel(int in[], int level[],int start, int end){
//	struct Node* root = (Node*)malloc(sizeof(Node));
//	static int i =0;
//	root->data = level[i];
//	i++;
//	root->left = NULL;
//	root->right =NULL;
//	root->left = buildTreeInLevel(in, level, start, end );
//}

//struct Node* buildTreeFromArr(int arr[], int len){
//	struct Node* root;
//	struct Node* temp;
//	root = temp = (Node*)malloc(sizeof(Node));
//	root->data= arr[0];
//	root->left = root;
//	root->right = root;
//	for(int i =1;i<len;i++){
//		struct Node* newnode = (Node*)malloc(sizeof(Node));
//		newnode->data = arr[i];
//		temp->left = newnode;
//		struct Node* newnode1 = (Node*)malloc(sizeof(Node));
//		newnode1->data = arr[i+1];
//		temp->right=newnode1;
//	
//	}
//
//}

int fun(struct Node* p){
	int x,y;

	while(p!=NULL){
		x = fun(p->left);
		y = fun(p->right);
		if(x>y)
			return x+1;
		else
			return y+1;
	}
	return 0;
	
}


struct Node* insertBst(struct Node* root,int data){
	struct Node* temp;
	struct Node* prev;
	struct Node* newnode = (Node*)malloc(sizeof(Node));
		temp = prev = root;
	if(root==NULL){
	root = newnode;
	root->data = data;
	root->left = NULL;
	root->right = NULL;
	return root;
	}
	
	while(temp!=NULL){
		prev = temp;
		if(temp->data == data){
		cout<<"node already exists";
		return NULL;
			}
		else if(temp->data < data){
			
			temp = temp->right;
				
			}
		else{
			
			temp = temp->left;
			}
	}
	
	if(temp==NULL){
		newnode->data = data;
		newnode->left = NULL;
		newnode->right = NULL;
		if(prev->data< data){
			prev->right = newnode;
		}
		else
			prev->left = newnode;
		return root;
	}
}

struct Node* insertBstRecur(struct Node* root, int data){
	//if(root==NULL){
	//root= newnode;
	//root->data = data;
	//root->left = NULL;
	//root->right = NULL;
	//return root;
	//}
	struct Node* temp;
	if(root== NULL){
		 temp = (Node*)malloc(sizeof(Node));

		temp->data = data;
		temp->left =temp->right= NULL;
		return temp;
	}

	if(root->data < data){
		root->right = insertBstRecur(root->right,data);
	}
	else{
		root->left = insertBstRecur(root->left,data);
	}
	return root;
}

void minValBst(struct Node* root){
	while(root->left!= NULL){
		root= root->left;
	}
	cout<<root->data;

}

void getCountRange(struct Node* root, int min, int max){
	int *arr= inorder(root);
	int result[15];
	int j =0;
	for(int i=0; i<20;i++){
		if(arr[i]>min && arr[i]<max)
		{	
			result[j]= arr[i];
			j++;
		}
	}
	for(int i=0;i<15;i++){
		cout<<result[i];
	}

}

struct Node* inPre(struct Node* n){
	while(n->right!=NULL){
		n = n->right;
	}
	return n;
}

struct Node* inSuc(struct Node* n){
	while(n->left!=NULL){
		n = n->left;
	}
	return n;
}

struct Node* deleteNodeBst(struct Node* root, int key){
	struct Node* p = root;
	struct Node* temp;
	
	if(p->left == NULL && p->right== NULL){
		if(p==root)
			return NULL;
		free(p);
	
	}
	if(p->data > key){
		p->left = deleteNodeBst(p->left,key);
	}
	else if(p->data < key){
		p->right = deleteNodeBst(p->right, key);
	}
	else{
		if(height(p->left)> height(p->right)){
			temp = inPre(p->left);
			p->data = temp->data;
			p->left = deleteNodeBst(p->left, temp->data);
		}
		else{
			temp = inSuc(p->right);
			p->data = temp->data;
			p->right = deleteNodeBst(p->right, temp->data);
		}
		
	
	}
	return root;

}

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	//struct Queue q;
	//createQueue(&q);
	//enqueue(&q,1);
	//enqueue(&q,2);
	//enqueue(&q,3);
	//enqueue(&q,4);
	//enqueue(&q,5);
	//dequeue(&q);
	//printQueue(&q);
	struct Node* root=NULL;
	struct Node* root1=(Node*)malloc(sizeof(Node));
	int arr[8] ={30,20,40,10,25,9,45,29};
	root1->data = 30;
	root1->left = NULL;
	root1->right = NULL;
	for(int i=1;i <8;i++){
	root1= insertBstRecur(root1,arr[i]);
	}
	preorder(root1);cout<<"\n";
	root1= deleteNodeBst(root1,30);
	preorder(root1);
	//getCountRange(root1,25,40);
	//cout<<height(root1);
	//preorder(root1);
	//minValBst(root1);
	//int in[6]= {4,2,5,1,3,6};
	//int pre[6] = {1,2,4,5,3,6};
	//root= buildTreeFromInPre(in,pre,0,5);
	////inorder(root);
	//for(int i=1;i <20;i++){
	//root= insertNode(root,q,i);
	//}
	//cout<<fun(root);
	//findNode(root,9);
	//findRightDeepestNode(root);
	//deleteDeepestNode(root,5);
	//cout<<height(root);
	struct queueLL* qll = (struct queueLL*)malloc(sizeof(struct queueLL));
	qll = levelOrder(root1,height(root1));cout<<"\n";
	//printCorner(qll,height(root));
	print(qll,height(root1));
	//struct Queue *q1 = (struct Queue*)malloc(sizeof(struct Queue));
	//initialiseQueue(q1,10);
	//nthInorder(root,q1,6);

	/*struct Queue* a;
	a = (struct )*/
	/*int *arr;
	arr = (int *)malloc(sizeof(int)*4);
	*(arr+1) =2;
	printf("%d",*(arr+1));*/
	//preorder(root);
	return 0;
}

