#include<iostream>
#include"Header.h"
using namespace std;

node CreateNode(int value) {
	node temp; 
	// Cấp phát vùng nhớ dùng malloc()
	temp = (node)malloc(sizeof(struct LinkedList)); 
	temp->next = NULL;
	temp->data = value; 
	return temp;
}

node AddTail(node head, int value) {
	node temp, p;
	//Gọi hàm createNode() để khởi tạo node temp có next trỏ tới NULL và giá trị là value
	temp = CreateNode(value);if (head == NULL) {
		head = temp;    
	}
	else {
		p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = temp;
	}
	return head;
}

int Get(node head, int index) {
	int k = 0;
	node p = head;
	while (p->next != NULL && k != index) {
		++k;
		p = p->next;
	}
	return p->data;
}

int Search(node head, int value) {
	int position = 0;
	for (node p = head; p != NULL; p = p->next) {
		if (p->data == value) {
			return position;
		}
		++position;
	}
	return -1;
}

void Traverser(node head) {
	cout << endl;
	for (node p = head; p != NULL; p = p->next) {
		cout << p->data << "  ";
	}
}

node InitHead() {
	node head;
	head = NULL;
	return head;
}

// Hàm tính chiều dài danh sách liên kết
int Length(node head) {
	int length = 0;
	for (node p = head; p != NULL; p = p->next) {
		++length;
	}
	return length;
}

// Cộng 2 vector
node Plus_2_Vector(node head1, node head2)
{
	node res = InitHead();
	while (head1 != NULL)
	{
		res = AddTail(res, head1->data + head2->data);
		head1 = head1->next;
		head2 = head2->next;
	}
	return res;
}

// Nhân vector với 1 sô alpha
node Multi_Vector(node head1, int n)
{
	node res = InitHead();
	while (head1 != NULL)
	{
		res = AddTail(res, head1->data*n);
		head1 = head1->next;
	}
	return res;
}

// Hàm input nhập vào n số của vector
node Input(int n) {
	node head = InitHead();
	int value;

	for (int i = 0; i < n; ++i) {
		cout << "enter value of vector:\t";
		cin >> value;
		head = AddTail(head, value);
	}
	return head;
}

void Vector() 
{
	int n;
	do {
		cout << "Enter the number members of vector 1:\t";
		cin >> n;
	} while (n <= 0);
	node head_a = Input(n);
	int m;
	do {	
		cout << "Enter the number members of vector 2:\t";
		cin >> m;
	} while (m != n);
	node head_b = Input(m);
	cout << "\nvector 1:";
	Traverser(head_a);
	cout << "\nvector 2:";
	Traverser(head_b);	
	node node_plus = Plus_2_Vector(head_a, head_b);
	cout << "\nSum of 2 vectors:";
	Traverser(node_plus);
	int number;
	cout << "\nenter number:\t";
	cin >> number;
	node node_multi = Multi_Vector(head_a, number);
	cout << "\nMulti of vector:";
	Traverser(node_multi);
	cout << endl;
	system("pause");

}