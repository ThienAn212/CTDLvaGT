#pragma once
#include"Map.h"
#include<vector>

using namespace std;

// Lưu trữ giá trị của 1 cặp
struct Pairs {
	int i, j;
};

class Minimize
{
private:
	int matrix[4][4];
	KMap* map;
	string rows[4];
	string columns[4];
	// Tìm các bộ đơn thức của hàm Bool
	void pushUnsortedGroups(vector<vector <Pairs>> &groups, int i, int j);
	// Sắp xếp lại các bộ này theo kích thước giảm dần
	void sortUnsortedGroup(vector <Pairs> &group);
	// Xóa những bộ trùng hoặc bị chứa trong
	void removeDuplicateGroups(vector<vector <Pairs>> &groups);
	// Convert thành kết quả
	string generateStringFromGroup(vector <Pairs> &group);
	// In kết quả 
	void printGroups(vector<vector <Pairs>> &groups);
	// Kiểm tra 1 bộ có bị chứa trong bởi bộ lớn hơn
	bool isSubsetOf(vector <Pairs> &group1, vector <Pairs> &group2);
	// Kiểm tra bộ trùng
	bool hasCommonPair(Pairs pair, vector <vector <Pairs>> &groups, int skip);
public:
	Minimize(KMap *map);
	~Minimize(void);
	// Convert thành kiểu string
	string getParsedExpression();
	// Kết hợp các bộ lại thành đa thức tối tiểu
	string getSimplifiedExpression();
};

