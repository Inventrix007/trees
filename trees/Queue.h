struct Node {
int data;
struct Node* right;
struct Node* left;
};

struct Queue {
	int size;
	int front;
	int rear;
	Node** arr;
};

void createQueue(struct Queue *q){
	
	cout<<"enter size of array";
	cin>>q->size;
	q->arr = (struct Node **)malloc(sizeof(Node *)*q->size);
	q->front = q->rear = -1;

}

void initialiseQueue(struct Queue *q, int size){
		q->size = size;
		q->arr = (struct Node **)malloc(sizeof(Node *)*q->size);
		q->front = q->rear = -1;

}

void enqueue(struct Queue *q,struct Node* data){
	//q->front = q->rear = -1;
	if(q->rear ==q->size){
		cout<<"queue is full";
		return;
	}
	else{
	q->rear++;
	q->arr[q->rear] = data;

	}

}

Node* dequeue(struct Queue *q){
	if(q->front == q->rear){
	cout<<"queue is empty";
	return NULL;
	}
	else{
	q->front++;	
	return q->arr[q->front];
	}

}

void printQueue(struct Queue *q){
	while(q->front != q->rear){
	q->front++;
	cout<<q->arr[q->front]->data<<" ";
	
	
	}

}

void printQueueSpecial(struct Queue *q, int height){
	while(q->front!=q->rear){
	q->front++;
	cout<<q->arr[q->front]->data;
	for(int i = 0;i<height*3;i++){
		cout<<" ";
	
	}
	
	
	}
}

