#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
using Matrix = vector<vector<string>>;

// ����1: �� �Լ����� ������ å��. �Լ��� ��Ȯ�� ����� ��쿡 10��, �׷��� ������ 0�� 
// ����2: �α��ν� �������� ID: admin, ��й�ȣ :0000 
// �䱸����1: ÷�ε� ��������(MidtermProjectCoupang.exe)�� ���۽��� ������ ������ ����ǵ��� �ڵ��� ��
// �䱸����2: file�� ������ �߰�/�����Ǵ���(������� ȸ�� �߰�) �Ϲ������� ������ �� �ֵ��� �ڵ��� �� (���� ������ ���Ͽ� ���ؼ��� �����ϸ� ���� �Լ� ��� ����)
// �䱸����3: (�ּ��� �����ϰ�) �Ʒ� �̹� �ۼ����ڵ带 �����Ͻ� ����, �� �ڵ带 Ȱ���ؼ� �ۼ��� ��
// �䱸����4: �Ʒ��� define�� symol�� ����Ͽ� �������� ���� ��(���� ���, info_client[0] ��� info_client[CLIENT_ID]�� ���, info_item[1] ��� info_client[ITEM_NAME]�� ���)
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
void client_start(Matrix& info_client, Matrix& info_item); // �߰����� (�ִ� 15��)

void read_info(Matrix& info_client, Matrix& info_item, string filename_client, string filename_item);  //10��
void write_info(const Matrix& info_client, const Matrix& info_item, string filename_client, string filename_item); //10��

void print_all(const Matrix& info_client); //10��
void print_each(const Matrix& info_client, int index); //10��
int search_client_by_id(const Matrix& info_client, string& id); //10��
void add_client(Matrix& info_client); //10��
void delete_client(Matrix& info_client);// 10��

vector<string> extract_regions(const Matrix& info_client); //10��
void print_items_by_region(const Matrix& info_client, const Matrix& info_item); // 10��
int search_item_by_id(const Matrix& info_item, string& id); // 10��
void add_item(Matrix& info_item); //10��
void delete_item(Matrix& info_item); //10��

int main() {
	string command;
	Matrix info_client(4), info_item(4); //info_client�� ȸ������, info_item�� ��ǰ������ ����
	read_info(info_client, info_item, "clients.txt", "items.txt");

	while (true) {
		cout << "1. ������ �α���" << endl;
		cout << "2. ȸ�� �α���" << endl;
		cout << "0. ���� �� ����" << endl;
		cout << ">>";
		cin >> command;
		if (command == "1")
			admin_start(info_client, info_item);
		else if (command == "2")
			client_start(info_client, info_item);
		else if (command == "0")
			break;
		else
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
	}

	write_info(info_client, info_item, "clients.txt", "items.txt");

	return 0;
}


void get_id_pw(string& id, string& pw) {
	cout << "ID�� �Է��ϼ���>>";
	cin >> id;
	cout << "��ȣ�� �Է��ϼ���>>";
	cin >> pw;
}


string get_command_admin() {
	string command;
	cout << "1. ��� ȸ������ ���" << endl;
	cout << "2. ȸ�� �˻�         " << endl;
	cout << "3. ȸ�� �߰�         " << endl;
	cout << "4. ȸ�� ����         " << endl;
	cout << "---------------------" << endl;
	cout << "5. ��� ��ǰ���� ���" << endl;
	cout << "6. ������� ��ǰ ���" << endl;
	cout << "7. ��ǰ �˻�         " << endl;
	cout << "8. ��ǰ �߰�         " << endl;
	cout << "9. ��ǰ ����         " << endl;
	cout << "---------------------" << endl;
	cout << "0. ����              " << endl;
	cout << ">>";
	cin >> command;
	return command;
}


void admin_start(Matrix& info_client, Matrix& info_item) {
	string id, pw, command;
	get_id_pw(id, pw);
	if (id == "admin" && pw == "0000") {
		cout << "�α��� �Ϸ�." << endl << endl;
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
			else                     cout << "�߸� �Է��Ͽ����ϴ�." << endl << endl;
		}
	}
	else {
		cout << "ID �Ǵ� ��ȣ�� �߸��Ǿ����ϴ�." << endl << endl;
	}
}

void read_info(Matrix& info_client, Matrix& info_item, string filename_client, string filename_item)
{
	ifstream fin;
	fin.open(filename_client);
	if (!fin)
	{
		cout << "������ �������� �ʽ��ϴ�" << endl;
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
		cout << "������ �������� �ʽ��ϴ�" << endl;
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
	cout << "���� �б� �Ϸ�." << endl << endl;
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

	cout << "����Ϸ� - ���α׷��� �����մϴ�." << endl;
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
	cout << "ID�� �Է��ϼ���>>";
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
	cout << "ID�� �Է��ϼ���>>";
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
		cout << endl << endl << "������ ID�� �����մϴ�." << endl << endl;
	else
	{
		int p = info_client.size();
		string pw, region;
		info_client.push_back(vector<string>(4));
		info_client[p][CLIENT_ID] = id;
		cout << endl << "��й�ȣ�� �Է��ϼ���>>";
		cin >> pw;
		info_client[p][CLIENT_PW] = pw;
		cout << "������ �Է��ϼ���>>";
		cin >> region;
		info_client[p][CLIENT_REGION] = region;
		info_client[p][CLIENT_ORDER_LIST] = "N/A";
		cout << "�߰� �Ϸ�." << endl << endl;
	}
}


void delete_client(Matrix& info_client) 
{
	string id;
	int index = search_client_by_id(info_client, id);
	if (index != -1)
	{
		cout << endl << endl << "�����Ǿ����ϴ�." << endl << endl;
		int i = info_client.size();
		for (int j = index; j < i - 1; j++)
			for (int k = 0; k < 4; k++)
				info_client[j][k] = info_client[j + 1][k];
		info_client.pop_back();
	}
	else
	{
		cout << endl << "ID�� �������� �ʽ��ϴ�." << endl << endl;
	}
}


void add_item(Matrix& info_item) {
	/* ���: id�� Ű����� ���� �Է¹޾�, �ش� id�� ���� ���� info_item�� �̹� �����ϸ� "������ ID�� �����մϴ�"�� ȭ�鿡 ���
			 �׷��� ������ �߰��� ��ǰ��� ������ �Է����� �޾� vector���� ���� ������ �κп� �߰�(��ǰ��, ������ ���ڵ� ��� string���ڿ��� ó���� ��)
			 �䱸����: search_client_by_id()�� ����ؼ� id�� �����ϴ��� ã�� ��
	*/
	string id;
	int index = search_item_by_id(info_item, id);
	if (index != -1)
		cout << endl << endl << "������ ID�� �����մϴ�." << endl << endl;
	else
	{
		int p = info_item.size();
		string name, price, quantity;
		info_item.push_back(vector<string>(4));
		info_item[p][ITEM_ID] = id;
		cout << endl << "��ǰ���� �Է��ϼ���>>";
		cin >> name;
		info_item[p][ITEM_NAME] = name;
		cout << "������ �Է��ϼ���>>";
		cin >> price;
		info_item[p][ITEM_PRICE] = price;
		cout << "������ �Է��ϼ���>>";
		cin >> quantity;
		info_item[p][ITEM_QUANTITY] = quantity;
		cout << "�߰� �Ϸ�." << endl << endl;
	}
}


void delete_item(Matrix& info_item)
{
	string id;
	int index = search_item_by_id(info_item, id);
	if (index != -1)
	{
		cout << endl << endl << "�����Ǿ����ϴ�." << endl << endl;
		int i = info_item.size();
		for (int j = index; j < i - 1; j++)
			for (int k = 0; k < 4; k++)
				info_item[j][k] = info_item[j + 1][k];
		info_item.pop_back();
	}
	else
	{
		cout << endl << "ID�� �������� �ʽ��ϴ�." << endl << endl;
	}
}



void client_start(Matrix& info_client, Matrix& info_item) {

}