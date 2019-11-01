#include<iostream>
#include<stdio.h>
#include"Simplifier.h"

using namespace std;

void Bool() {

	string line;
	KMap map;
	Minimize minimize(&map);

	
	// Nhập vào các vị trí trong bảng đồ Karnaugh
	cout << "Enter positions of Karnaugh Map:  ";
	cin.ignore();
	getline(cin, line);

	// Đọc dòng vừa nhập và đưa các vị trí đó vào mảng
	map.parseLine(line);

	// Vẽ bản đồ ra console
	map.drawMap();

	// In đa thức đã nhập vào
	printf("\nInput: %s\n", minimize.getParsedExpression().c_str());

	// In đa thức tối tiểu 
	printf("Output: %s\n", minimize.getSimplifiedExpression().c_str());

	system("pause");

}