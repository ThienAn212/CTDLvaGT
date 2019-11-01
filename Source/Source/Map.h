#pragma once
#include<string>

class KMap {
private:
	// Mảng 4x4 lưu trữ các vị trí đã nhập vào
	int matrix[4][4];

	// Đọc line và đưa vào mảng
	int parseToArray(std::string line, int numbers[16]);

public:

	// Constructor
	KMap();

	// Đọc dãy số từ console
	void parseLine(std::string line);

	// Sao chép ma trận
	void getMatrix(int m[4][4]);

	// Vẽ bản đồ Karnaugh
	void drawMap();
};
// Hàm tổng hợp các chức năng 
void Bool();