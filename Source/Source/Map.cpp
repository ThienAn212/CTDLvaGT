#include"Map.h"
#include<iostream>

using namespace std;

KMap::KMap(){}


void KMap::parseLine(string line) {

	// Mảng lưu trữ các vị trí
	int numbers[16];

	// Tách các số từ line vào mảng numbers
	int length = parseToArray(line, numbers);

	// Khởi tạo mảng matrix
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = 0;

	// Chuyển các vị trí trong mảng numbers thành mảng nhị phân matrix (chứa hai giá trị 0 hoặc 1)
	for (int i = 0; i < length; i++) {		
		int rowIndex = (numbers[i] / 4);
		int columnIndex = (numbers[i] % 4);
		if (columnIndex == 2) columnIndex++;
		else if (columnIndex == 3) columnIndex--;
		matrix[rowIndex][columnIndex] = 1;
	}
}


void KMap::drawMap() {
	cout << endl;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int KMap::parseToArray(string line, int numbers[16]) {
	line += " ";
	int count = 0, lastSpace = 0;
	for (unsigned int i = 0; i < line.length(); i++) {
		
		if (line[i] == ' ') {
			// Convert char thành int
			int temp = stoi(line.substr(lastSpace, i - lastSpace), nullptr);
			lastSpace = i;
			if (temp < 0 || temp > 15) continue;
			numbers[count++] = temp;
		}
	}
	return count;
}

void KMap::getMatrix(int m[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = matrix[i][j];
}

