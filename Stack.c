#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef int MyType;
 
enum COMPONENTS
{
	MAX = INT_MAX
};

enum ERRORS
{
	STACK_IS_NULL  =-1,
	DATA_IS_NULL   = 1,
	CUR_POS_IS_NEG = 2,
	VERY_BIG_VALUE = 3,
	STACK_IS_FULL  = 4,
	STACK_IS_EMPTY = 5,
};

struct Stack
{
	MyType size;
	MyType cur_position;
	MyType *data;
};

MyType InitStack(struct Stack* stack);
void Push(struct Stack* stack, MyType value);
MyType OK(struct Stack* stack, MyType *data, MyType cur_position, MyType size, MyType myErrno, MyType value);
void Dump(struct Stack* stack, MyType myErrno);
void Pop(struct Stack* stack);
MyType StackTop(struct Stack* stack);

int main() 
{
	MyType myErrno = 0;
	MyType value = 0;
	struct Stack stack  = {};

	stack.size = InitStack(&stack);

	for(int i=0; i < (stack.size); i++)
	{
		Push(&stack, value);
	}
	Pop(&stack);
	MyType elem = StackTop(&stack);
	printf("%d\n", elem);
	Dump(&stack, myErrno);
	return 0;
}

MyType InitStack(struct Stack* stack)
{	
	MyType myErrno = 0;
	MyType value = 0;
	printf("Enter size of stack\t");
	scanf("%d", &stack->size);
	stack->cur_position = 0;
	stack->data = (MyType*)calloc(sizeof(MyType), stack->size);
	OK(stack, stack->data, stack->cur_position, stack->size, myErrno, value);
	return (stack->size);
}

void Push(struct Stack* stack, MyType value)
{
	MyType myErrno;
	OK(stack, stack->data, stack->cur_position, stack->size, myErrno, value);
	printf("Enter value:\t");
	scanf("%d", &value);
	stack->data[stack->cur_position] = value;
	stack->cur_position++;
}


MyType OK(struct Stack* stack, MyType *data, MyType cur_position, MyType size, MyType myErrno, MyType value)
{
	if(stack == NULL)
	{
		myErrno = STACK_IS_NULL; 
	}
	if(data == NULL)
	{
		myErrno = DATA_IS_NULL; 
	}
	if(stack->cur_position < 0)
	{
		myErrno = CUR_POS_IS_NEG;
	}
	if(value >= MAX)
	{
		myErrno = VERY_BIG_VALUE;
	}
	if(stack->cur_position >= size)
	{
		myErrno = STACK_IS_FULL;
	}
	if(stack->size <= 0)
	{
		myErrno = STACK_IS_NULL;
	}
	if((stack->cur_position) <= 0)
	{
		myErrno = STACK_IS_EMPTY;
	}
}

void Dump(struct Stack* stack, MyType myErrno)
{
	if(myErrno == STACK_IS_NULL)
	{
		printf("STACK POINTER IS NULL\n");
	}
	if(myErrno == DATA_IS_NULL)
	{
		printf("ARRAY DATA IS NULL\n");
	}
	if(myErrno == CUR_POS_IS_NEG)
	{
		printf("CURRENT POSITION IS NEGATIVE\n");
	}
	if(myErrno == VERY_BIG_VALUE)
	{
		printf("VALUE IS VERY BIG\n");
	}
	if(myErrno == STACK_IS_FULL)
	{
		printf("STACK IS FULL\n");
	}
	if(myErrno == STACK_IS_EMPTY)
	{
		printf("STACK IS EMPTY\n");
	}
	else
	{	
		stack->cur_position++;
		for(int i = 0; i < (stack->cur_position); i++)
		{
			printf("%d ", stack->data[i]);
		}
	}
}

void Pop(struct Stack* stack)
{
	MyType myErrno;
	MyType value;
	OK(stack, stack->data, stack->cur_position, stack->size, myErrno, value);
	stack->cur_position--;
}

MyType StackTop(struct Stack* stack)
{
	MyType myErrno;
	MyType value;
	OK(stack, stack->data, stack->cur_position, stack->size, myErrno, value);
	MyType elem = 0;
	stack->cur_position--;
	elem = stack->data[stack->cur_position];
	return elem;
}







