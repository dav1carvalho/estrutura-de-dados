

#include <iostream>
using namespace std;
typedef int data;

class Noh
{
friend class Stack;
private:
	Noh* mNext; // Pointer for the next Noh
	data mValue; // Value to be stored
public:
	Noh(data _Value) // Constructor of the Noh
	{
		mNext = nullptr;
		mValue = _Value;
	}
	~Noh(); // Deconstructor of the Noh
};

Noh::~Noh()
{
}
class Stack
{
private:
	Noh* mStart; // Initial pointer
	unsigned mSize; // Size of the stack
public:
	Stack(); // Constructor of the stack
	~Stack(); // Deconstructor of the stack
	void Push(data _Value); // Put values in the stack
	void Pop(); // Remove values from the stack
	bool EmptyStack(); // Return true if the stack empty, false if not
	void Print(); // Print the stack
};

Stack::Stack()
{
	mStart = nullptr;
	mSize = 0;
}

Stack::~Stack()
{
	while (!EmptyStack())
		Pop();
}

void Stack::Push(data _Value)
{
	Noh* newNoh = new Noh(_Value);

	if (EmptyStack())
		mStart = newNoh;
	else
	{
		newNoh->mNext = mStart->mNext;
		mStart = newNoh;
	}
	mSize++;
	Print();
}

void Stack::Pop()
{
	
	if (EmptyStack())
	{
		cerr << "The stack is empty!!";
	}else
	{
		Noh* trash = new Noh(0);
		trash = mStart;
		mStart = mStart->mNext;
		delete trash;
		mSize--;
		Print();
	}
	
	
}

bool Stack::EmptyStack()
{
	return (mSize <= 0)? true : false;
}

void Stack::Print()
{
    Noh* aux = mStart;
    while (aux != NULL) {
        cout << "<" << aux->mValue << ">" << endl;
        aux = aux->mNext;
    }
}

int main()
{
	Stack myStack;
	data value;
	char operation = 'k';
	cout << "Press 'm' to show the menu" << endl;

	
	while (operation != 'f')
	{
		cin >> operation;
		switch (operation)
		{
		case 'i': // Insertion on the stack
			cout << endl;
			cin >> value;
			myStack.Push(value);

			break;
		
		case 'r': // Remove a value on the stack
			cout << endl;
			myStack.Pop();
			break;

		case 'm': // Menu
			cout << endl;
			cout << "'i' - Insertion on the stack" << endl
			<< "'r' - Remove a value on the stack" << endl
			<<"'m' - Show the menu" << endl
			<< "'f' - Finish the program" << endl;
			break;

		default:
			break;
		}
	}
	return 0;
}