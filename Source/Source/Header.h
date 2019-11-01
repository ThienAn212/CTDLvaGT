#pragma once
struct LinkedList {
	int data;
	struct LinkedList *next;
};
typedef struct LinkedList* node;

//Tạo node mới từ data
node CreateNode(int);
// Thêm vào cuối dslk
node AddTail(node, int );
// Lấy node có data=k
int Get(node , int );
// Tìm kiếm node có data=k
int Search(node , int e);
// Duyệt dslk đơn
void Traverser(node);
//Khởi tạo dslk
node InitHead();
// Tính độ dài hiện tại của dslk
int Length(node );
// Hàm cộng 2 vector
node Plus_2_Vector(node , node );
// Hàm nhân vector với alpha
node Multi_Vector(node , int );
// Hàm nhập các phần tử của dslk
node Input(int);
// Hàm tổng hợp các chức năng với vector
void Vector();

