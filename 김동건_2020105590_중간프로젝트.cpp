#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
using Matrix = vector<vector<string>>;

// 참고1: 각 함수별로 점수를 책정. 함수가 정확히 기술된 경우에 10점, 그렇지 않으면 0점 
// 참고2: 로그인시 관리자의 ID: admin, 비밀번호 :0000 
// 요구사항1: 첨부된 실행파일(MidtermProjectCoupang.exe)을 동작시켜 동일한 동작이 수행되도록 코딩할 것
// 요구사항2: file의 정보가 추가/삭제되더라도(예를들어 회원 추가) 일반적으로 동작할 수 있도록 코딩할 것 (현재 제공된 파일에 대해서만 동작하면 관련 함수 모두 감점)
// 요구사항3: (주석을 제외하고) 아래 이미 작성된코드를 삭제하시 말고, 그 코드를 활용해서 작성할 것
// 요구사항4: 아래에 define된 symol을 사용하여 가독성을 높일 것(예를 들어, info_client[0] 대신 info_client[CLIENT_ID]을 사용, info_item[1] 대신 info_client[ITEM_NAME]을 사용)
#define CLIENT_ID 0
#define CLIENT_PW 1
#define CLIENT_REGION 2
#define CLIENT_ORDER_LIST 3

#define ITEM_ID 0
#define ITEM_NAME 1
#define ITEM_PRICE 2
#define ITEM_QUANTITY 3


void admin_start(Matrix& info_client, Matrix& info_item);
void get_id_pw(string& id, string& pw);
string get_command_admin();
void client_start(Matrix& info_client, Matrix& info_item); // 추가점수 (최대 15점)

void read_info(Matrix& info_client, Matrix& info_item, string filename_client, string filename_item);  //10점
void write_info(const Matrix& info_client, const Matrix& info_item, string filename_client, string filename_item); //10점

void print_all(const Matrix& info_client); //10점
void print_each(const Matrix& info_client, int index); //10점
int search_client_by_id(const Matrix& info_client, string& id); //10점
void add_client(Matrix& info_client); //10점
void delete_client(Matrix& info_client);// 10점

vector<string> extract_regions(const Matrix& info_client); //10점
void print_items_by_region(const Matrix& info_client, const Matrix& info_item); // 10점
int search_item_by_id(const Matrix& info_item, string& id); // 10점
void add_item(Matrix& info_item); //10점
void delete_item(Matrix& info_item); //10점

int main() {
	string command;
	Matrix info_client(4), info_item(4); //info_client는 회원정보, info_item은 물품정보를 저장
	read_info(info_client, info_item, "clients.txt", "items.txt");

	while (true) {
		cout << "1. 관리자 로그인" << endl;
		cout << "2. 회원 로그인" << endl;
		cout << "0. 저장 및 종료" << endl;
		cout << ">>";
		cin >> command;
		if (command == "1")
			admin_start(info_client, info_item);
		else if (command == "2")
			client_start(info_client, info_item);
		else if (command == "0")
			break;
		else
			cout << "잘못 입력하였습니다." << endl;
	}

	write_info(info_client, info_item, "clients.txt", "items.txt");

	return 0;
}


void get_id_pw(string& id, string& pw) {
	cout << "ID를 입력하세요>>";
	cin >> id;
	cout << "암호를 입력하세요>>";
	cin >> pw;
}


string get_command_admin() {
	string command;
	cout << "1. 모든 회원정보 출력" << endl;
	cout << "2. 회원 검색         " << endl;
	cout << "3. 회원 추가         " << endl;
	cout << "4. 회원 삭제         " << endl;
	cout << "---------------------" << endl;
	cout << "5. 모든 물품정보 출력" << endl;
	cout << "6. 배송지별 물품 출력" << endl;
	cout << "7. 물품 검색         " << endl;
	cout << "8. 물품 추가         " << endl;
	cout << "9. 물품 삭제         " << endl;
	cout << "---------------------" << endl;
	cout << "0. 종료              " << endl;
	cout << ">>";
	cin >> command;
	return command;
}


void admin_start(Matrix& info_client, Matrix& info_item) {
	string id, pw, command;
	get_id_pw(id, pw);
	if (id == "admin" && pw == "0000") {
		cout << "로그인 완료." << endl << endl;
		while (true) {
			command = get_command_admin();
			if (command == "1")		 print_all(info_client);
			else if (command == "2") search_client_by_id(info_client, id);
			else if (command == "3") add_client(info_client);
			else if (command == "4") delete_client(info_client);
			else if (command == "5") print_all(info_item);
			else if (command == "6") print_items_by_region(info_client, info_item);
			else if (command == "7") search_item_by_id(info_item, id);
			else if (command == "8") add_item(info_item);
			else if (command == "9") delete_item(info_item);
			else if (command == "0") break;
			else                     cout << "잘못 입력하였습니다." << endl << endl;
		}
	}
	else {
		cout << "ID 또는 암호가 잘못되었습니다." << endl << endl;
	}
}

void read_info(Matrix& info_client, Matrix& info_item, string filename_client, string filename_item)
{
	ifstream fin;
	fin.open(filename_client);
	if (!fin)
	{
		cout << "파일이 존재하지 않습니다" << endl;
		exit(100);
	}
	string a;
	int i = 0;
	string garbage;
	getline(fin, garbage);
	while (true)
	{
		fin >> a;
		if (fin.eof())
			break;
		if (i > 3)
		{
			info_client.push_back(vector<string>(4));
			info_client[i][0] = a;
			for (int j = 1; j < 4; j++)
			{
				fin >> a;
				info_client[i][j] = a;
			}
			i++;
		}
		else
		{
			info_client[i] = vector<string>(4);
			info_client[i][0] = a;
			for (int j = 1; j < 4; j++)
			{
				fin >> a;
				info_client[i][j] = a;
			}
			i++;
		}
	}
	fin.close();

	fin.open(filename_item);
	if (!fin)
	{
		cout << "파일이 존재하지 않습니다" << endl;
		exit(100);
	}
	string b;
	i = 0;
	string garbage2;
	getline(fin, garbage2);
	while (true)
	{
		fin >> b;
		if (fin.eof())
			break;
		if (i > 3)
		{
			info_item.push_back(vector<string>(4));
			info_item[i][0] = b;
			for (int j = 1; j < 4; j++)
			{
				fin >> b;
				info_item[i][j] = b;
			}
			i++;
		}
		else
		{
			info_item[i] = vector<string>(4);
			info_item[i][0] = b;
			for (int j = 1; j < 4; j++)
			{
				fin >> b;
				info_item[i][j] = b;
			}
			i++;
		}
	}
	fin.close();
	cout << "파일 읽기 완료." << endl << endl;
}

void write_info(const Matrix& info_client, const Matrix& info_item, string filename_client, string filename_item)
{
	fstream fout;
	fout.open(filename_client);
	filename_client.clear();
	fout << "ID" << "     " << "Password" << "     " << "Region" << "     " << "Order_Item_ID" << '\n';
	for (vector<string> row : info_client)
	{
		for (string elem : row)
			fout << elem << "     ";
		fout << '\n';
	}
	fout.close();

	fout.open(filename_item);
	filename_item.clear();
	fout << "ID" << "     " << "ItemName" << "     " << "Price" << "     " << "Quantity" << '\n';
	for (vector<string> row : info_item)
	{
		for (string elem : row)
			fout << elem << "     ";
		fout << '\n';
	}
	fout.close();

	cout << "저장완료 - 프로그램을 종료합니다." << endl;
}


void print_each(const Matrix& info, int index)
{
	for (auto elem : info[index])
		cout << setw(15) << elem;
}


void print_all(const Matrix& info)
{
	int i = 0;
	cout << setw(15) << "ID" << setw(15) << "Password" << setw(15) << "Region" << setw(15) << "Order_Item_ID" << endl;
	for (auto row : info)
	{
		print_each(info, i);
		cout << endl;
		i++;
	}
	cout << endl;
}


vector<string> extract_regions(const Matrix& info_client)
{
	vector<string> regions;
	for (auto elem : info_client)
	{
		bool a = true;
		for (string region : regions)
			if (elem[2] == region)
				a = false;
		if (a)
			regions.push_back(elem[2]);
	}
	return regions;
}


void print_items_by_region(const Matrix& info_client, const Matrix& info_item)
{
	vector<string> regions = extract_regions(info_client);
	for (string region : regions)
	{
		cout << setw(10) << region << ": ";
		for (auto elem : info_client)
		{
			int i = 0;
			if (region == elem[2])
				cout << info_item[i][0] << ',';
			i++;
		}
		cout << endl;
	}
	cout << endl;
}


int search_item_by_id(const Matrix& info_item, string& id)
{
	cout << "ID를 입력하세요>>";
	cin >> id;
	int i = 0;
	for (auto item : info_item)
	{
		if (id == item[0])
		{
			cout << setw(15) << "ID" << setw(15) << "ItemName" << setw(15) << "Price" << setw(15) << "Quantity" << endl;
			for (string elem : item)
				cout << setw(15) << elem;
			cout << endl << endl;
			return i;
		}
		i++;
	}
	cout << endl;
	return -1;
}


int search_client_by_id(const Matrix& info_client, string& id)
{
	cout << "ID를 입력하세요>>";
	cin >> id;
	int i = 0;
	for (auto client : info_client)
	{
		if (id == client[0])
		{
			cout << setw(15) << "ID" << setw(15) << "Password" << setw(15) <<
				"Region" << setw(15) << "Order_Item_ID" << endl;
			for (string elem : client)
				cout << setw(15) << elem;
			cout << endl << endl;
			return i;
		}
		i++;
	}
	cout << endl;
	return -1;
}


void add_client(Matrix& info_client)
{
	string id;
	int index = search_client_by_id(info_client, id);
	if (index != -1)
		cout << endl << endl << "동일한 ID가 존재합니다." << endl << endl;
	else
	{
		int p = info_client.size();
		string pw, region;
		info_client.push_back(vector<string>(4));
		info_client[p][CLIENT_ID] = id;
		cout << endl << "비밀번호를 입력하세요>>";
		cin >> pw;
		info_client[p][CLIENT_PW] = pw;
		cout << "지역을 입력하세요>>";
		cin >> region;
		info_client[p][CLIENT_REGION] = region;
		info_client[p][CLIENT_ORDER_LIST] = "N/A";
		cout << "추가 완료." << endl << endl;
	}
}


void delete_client(Matrix& info_client) 
{
	string id;
	int index = search_client_by_id(info_client, id);
	if (index != -1)
	{
		cout << endl << endl << "삭제되었습니다." << endl << endl;
		int i = info_client.size();
		for (int j = index; j < i - 1; j++)
			for (int k = 0; k < 4; k++)
				info_client[j][k] = info_client[j + 1][k];
		info_client.pop_back();
	}
	else
	{
		cout << endl << "ID가 존재하지 않습니다." << endl << endl;
	}
}


void add_item(Matrix& info_item) {
	/* 기능: id를 키보드로 부터 입력받아, 해당 id를 가진 고객이 info_item에 이미 존재하면 "동일한 ID가 존재합니다"를 화면에 출력
			 그렇지 않으면 추가로 상품명과 수량을 입력으로 받아 vector들의 가장 마지막 부분에 추가(상품명, 수량등 숫자도 모두 string문자열로 처리할 것)
			 요구사항: search_client_by_id()를 사용해서 id가 존재하는지 찾을 것
	*/
	string id;
	int index = search_item_by_id(info_item, id);
	if (index != -1)
		cout << endl << endl << "동일한 ID가 존재합니다." << endl << endl;
	else
	{
		int p = info_item.size();
		string name, price, quantity;
		info_item.push_back(vector<string>(4));
		info_item[p][ITEM_ID] = id;
		cout << endl << "상품명을 입력하세요>>";
		cin >> name;
		info_item[p][ITEM_NAME] = name;
		cout << "가격을 입력하세요>>";
		cin >> price;
		info_item[p][ITEM_PRICE] = price;
		cout << "수량을 입력하세요>>";
		cin >> quantity;
		info_item[p][ITEM_QUANTITY] = quantity;
		cout << "추가 완료." << endl << endl;
	}
}


void delete_item(Matrix& info_item)
{
	string id;
	int index = search_item_by_id(info_item, id);
	if (index != -1)
	{
		cout << endl << endl << "삭제되었습니다." << endl << endl;
		int i = info_item.size();
		for (int j = index; j < i - 1; j++)
			for (int k = 0; k < 4; k++)
				info_item[j][k] = info_item[j + 1][k];
		info_item.pop_back();
	}
	else
	{
		cout << endl << "ID가 존재하지 않습니다." << endl << endl;
	}
}



void client_start(Matrix& info_client, Matrix& info_item) {

}