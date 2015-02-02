struct Node{
	void* data;
	struct Node* next;
};

struct LinkedList{
	struct Node* head;
	struct Node* tail;
	int count;
};

typedef struct LinkedList LinkedList;
typedef struct Node Node; 
typedef struct student student;
typedef char* string;  

struct Stack{
	LinkedList* list;
	Node** top;
};

typedef struct Stack Stack;

LinkedList createList(void);
Node* create_node(void*);
int add_to_list(LinkedList*,Node*);
void *get_first_element(LinkedList);
void *get_last_element(LinkedList);
void traverse(LinkedList, void (*f)(void*));
void *getElementAt(LinkedList,int);
int indexOf(LinkedList,void*);
void *deleteElementAt(LinkedList*, int);
LinkedList *filter(LinkedList, int (*)(void *));
Stack createStack(void);
int push(Stack, void *);
void* pop(Stack);