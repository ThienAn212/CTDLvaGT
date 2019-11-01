#include "Simplifier.h"
#include<iostream>
#include<ctype.h>


Minimize::Minimize(KMap *map) :
	map(map)
{
}


Minimize::~Minimize(void)
{
}

string Minimize::getParsedExpression() {
	map->getMatrix(matrix);
	string rows[] = { "cd","cD","CD","Cd" };
	string columns[] = { "ab","aB","AB","Ab" };

	string result = "";

	// Các ký tự nối
	string connective1 = " + ";
	string connective2 = "";

	// Đánh dấu nhân tử đầu tiên
	bool firstExpression = true;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 1) {
				if (!firstExpression)
					result += connective1;
				else
					firstExpression = false;
					result += columns[j][0] + connective2 + columns[j][1] + connective2 +
					rows[i][0] + connective2 + rows[i][1];
			}
		}
	}

	return result;
}

string Minimize::getSimplifiedExpression() {
	map->getMatrix(matrix);
	string result = "";

	// Lưu trữ những bộ đơn thức (8/4/2)
	vector<vector <Pairs>> groups;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrix[i][j] == 1)
				// Tìm những bộ đơn thức từ vị trí i,j đưa vào vector groups
				pushUnsortedGroups(groups, i, j);
		}
	}

	// Sắp xếp các bộ đơn thức ưu tiên bộ có kích thước lớn hơn (8>4>2)
	for (int i = 0; i < groups.size(); i++)
		sortUnsortedGroup(groups[i]);

	// Loại bỏ các bộ đơn thức nhỏ bị chứa trong các bộ lớn hơn
	removeDuplicateGroups(groups);

	// In các bộ đơn thức còn lại
	printGroups(groups);

	// In ra đa thức tối tiểu của hàm bool
	for (int i = 0; i < groups.size(); i++)
		result += (i ? " + " : "") + generateStringFromGroup(groups[i]);

	return result;
}

void Minimize::pushUnsortedGroups(vector<vector <Pairs>> &groups, int i, int j) {
	vector<Pairs> group;
	Pairs temp;
	bool foundGroups = false;
	int d[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };

	temp.i = i; 
	temp.j = j;
	group.push_back(temp);

	for (int k = 0; k < 4; k++) {
		// Kiểm tra trường hợp 2 ô
		if (matrix[(i + d[k][0] + 4) % 4][(j + d[k][1] + 4) % 4] == 1) {
			temp.i = (i + d[k][0] + 4) % 4; temp.j = (j + d[k][1] + 4) % 4;
			group.push_back(temp);

			// Kiểm tra trường hợp 4 ô đầu-cuối
			if (matrix[(i + 2 * d[k][0] + 4) % 4][(j + 2 * d[k][1] + 4) % 4] == 1 &&
				matrix[(i + 3 * d[k][0 + 4]) % 4][(j + 3 * d[k][1] + 4) % 4] == 1) {
				temp.i = (i + 2 * d[k][0] + 4) % 4; temp.j = (j + 2 * d[k][1] + 4) % 4;
				group.push_back(temp);

				temp.i = (i + 3 * d[k][0] + 4) % 4; temp.j = (j + 3 * d[k][1] + 4) % 4;
				group.push_back(temp);

				// Kiểm tra trường hợp 8 ô 
				if (matrix[(i + 0 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4][(j + 0 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4] == 1 &&
					matrix[(i + 1 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4][(j + 1 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4] == 1 &&
					matrix[(i + 2 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4][(j + 2 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4] == 1 &&
					matrix[(i + 3 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4][(j + 3 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4] == 1) {

					temp.i = (i + 0 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4; temp.j = (j + 0 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4;
					group.push_back(temp);

					temp.i = (i + 1 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4; temp.j = (j + 1 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4;
					group.push_back(temp);

					temp.i = (i + 2 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4; temp.j = (j + 2 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4;
					group.push_back(temp);

					temp.i = (i + 3 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4; temp.j = (j + 3 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4;
					group.push_back(temp);
				}

				groups.push_back(group);
				group.clear();
				foundGroups = true;
				break;
			}

			// Kiểm tra trường hợp 4 ô tạo hình vuông
			if (matrix[(i + 0 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4][(j + 0 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4] == 1 &&
				matrix[(i + 1 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4][(j + 1 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4] == 1) {
				temp.i = (i + 0 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4; temp.j = (j + 0 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4;
				group.push_back(temp);

				temp.i = (i + 1 * d[k][0] + d[(k + 1) % 4][0] + 4) % 4; temp.j = (j + 1 * d[k][1] + d[(k + 1) % 4][1] + 4) % 4;
				group.push_back(temp);
			}
			groups.push_back(group);
			group.clear();
			temp.i = i; temp.j = j;
			group.push_back(temp);
			foundGroups = true;
		}
	}
	// Nếu không có cặp nào thì lấy các điểm riêng biệt
	if (!foundGroups)
		groups.push_back(group);
}

void Minimize::sortUnsortedGroup(vector <Pairs> &group) {

	for (int i = 0; i < group.size(); i++) {
		for (int j = 0; j < group.size() - i - 1; j++) {
			if (group[j].i * 4 + group[j].j > group[j + 1].i * 4 + group[j + 1].j) {
				Pairs temp = group[j];
				group[j] = group[j + 1];
				group[j + 1] = temp;
			}
		}
	}

}
void Minimize::removeDuplicateGroups(vector<vector <Pairs>> &groups) {
	vector<string> temp;

	// Đưa các đơn thức vào vector temp
	for (int i = 0; i < groups.size(); i++) {
		temp.push_back("");
		for (int j = 0; j < groups[i].size(); j++) {
			temp[i] += to_string(groups[i][j].i * 4 + groups[i][j].j) + " ";
		}
	}

	// Xóa các đơn thức bị trùng lắp
	for (int i = 0; i < temp.size(); i++) {
		for (int j = i + 1; j < temp.size(); j++) {
			if (temp[i].compare(temp[j]) == 0) {
				temp.erase(temp.begin() + j);
				groups.erase(groups.begin() + j);
			}
		}
	}

	// Xóa các đơn thức nhỏ
	for (int i = 0; i < groups.size(); i++) {
		vector<Pairs> group = groups[i];
		for (int j = 0; j < groups.size(); j++) {
			if (i == j) continue;
			if (isSubsetOf(groups[j], group)) {
				groups.erase(groups.begin() + j);
				j--;
			}
		}
	}
	// Xóa các đơn thức dư thừa
	bool allCommon;
	for (int i = 0; i < groups.size(); i++) {
		vector<Pairs> group = groups[i];
		allCommon = true;
		for (int j = 0; j < group.size(); j++) {
			if (!hasCommonPair(group[j], groups, i)) {
				allCommon = false;
				break;
			}
		}
		if (allCommon) {
			groups.erase(groups.begin() + i);
			i--;
		}
	}
}
bool Minimize::hasCommonPair(Pairs pair, vector <vector <Pairs>> &groups, int skip) {
	for (int i = 0; i < groups.size(); i++) {
		
		if (i == skip) continue;
		for (int j = 0; j < groups[i].size(); j++) {
			if (groups[i][j].i * 4 + groups[i][j].j == pair.i * 4 + pair.j)
				return true;
		}
	}
	return false;
}


bool Minimize::isSubsetOf(vector <Pairs> &group1, vector <Pairs> &group2) {
	bool found;

	
	for (int i = 0; i < group1.size(); i++) {
		found = false;
		for (int j = 0; j < group2.size(); j++) {
			if (group1[i].i * 4 + group1[i].j == group2[j].i * 4 + group2[j].j) {
				found = true;
				break;
			}
		}
		if (!found) return false;
	}
	return true;
}

void Minimize::printGroups(vector<vector <Pairs>> &groups) {
	cout << endl;
	for (int i = 0; i < groups.size(); i++) {
		switch (groups[i].size()) {
		case 1: cout << "1:   "; break;
		case 2: cout << "2:   "; break;
		case 4: cout << "4:   "; break;
		case 8: cout << "8:   "; break;
		}
		for (int j = 0; j < groups[i].size(); j++) {
			int pos_i = groups[i][j].i;
			int pos_j = groups[i][j].j;
			if (pos_j == 2) pos_j++;
			else if (pos_j == 3) pos_j--;
			cout << pos_i * 4 + pos_j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

string Minimize::generateStringFromGroup(vector <Pairs> &group) {
	string result;
	string rows[] = { "cd","cD","CD","Cd" };
	string columns[] = { "ab","aB","AB","Ab" };

	string temp2 = columns[group[0].j] + rows[group[0].i];

	
	if (group.size() == 1) {
		result = temp2;
	}
	else {
		
		for (int i = 1; i < group.size(); i++) {
			result = "";
			string temp1 = columns[group[i].j] + rows[group[i].i];

			for (int j = 0; j < temp2.size(); j++) {
				if (temp1.find(temp2[j]) != string::npos) {
					result += temp2[j];
				}
			}
			temp2 = result;
		}
	}
	
	return result;
}



