#pragma once
#include<string>
#include<iostream>
using namespace std;
const int LenthMAX = 30, ListLenth = 62;
const char ArrSecret[] = "qwertyuiHIJKLMNop[ABCDEFG]asdUVWXYZfghjkOPQRSTl;zxcvbnm,.?{}:|";
const char ArrObvious[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz";
//从输入框读取内容
string informationget(CEdit& tempedit)
{
	CString s;
	tempedit.GetWindowTextW(s);
	string result = (CStringA)s;
	return result;
}
//char * CStringTOchar(CString  str)
//{
//	char* temp;
//	LPCTSTR p = str.GetBuffer(0);
//	str.ReleaseBuffer();
//	temp = new char[str.GetLength() + 1];
//	strcpy_s(temp, str.GetLength() + 1, CT2CA(p));
//	char result[50];
//	memset(result, '\0', sizeof(result));
//	strcpy_s(result, (char*)temp);
//	return result;
//}
void  setcode(char ArrCIN[LenthMAX])
{
	int l = strlen(ArrCIN);
	FILE* txt;
	txt = fopen("secret.txt", "w+");
	for (int Order = 0; Order < l; Order++)
	{
		int CheckTimes = 0;
		while (CheckTimes < ListLenth)
		{
			if (ArrCIN[Order] == ArrObvious[CheckTimes])
			{
				fprintf(txt, "%c", ArrSecret[CheckTimes]);
				CheckTimes = ListLenth;
				break;
			}
			CheckTimes++;
		}
	}
	fclose(txt);
}
bool checkcode(char ArrCIN[])
{
	FILE* txt;
	char ArrFIN[LenthMAX]="\0";
	ArrFIN[LenthMAX - 1] = '\0';
	txt = fopen("secret.txt", "r");
	fscanf_s(txt, "%s", ArrFIN, LenthMAX);
	fclose(txt);
	/*CFile File;
	char* temp01 = "secere.txt";
	CString temp(temp01);
	File.Open(temp, CFile::modeRead);
	File.Read(ArrFIN, LenthMAX);
	File.Close();*/
	int LenthArrFIN = strlen(ArrFIN);
	int LenthArrCIN = strlen(ArrCIN);
	if (LenthArrFIN == LenthArrCIN)
	{
		int CorrectTimes = 0;
		for (int Order = 0; Order < LenthArrFIN; Order++)
		{
			int CheckTimes = 0;
			while (CheckTimes < ListLenth)
			{
				if (ArrFIN[Order] == ArrSecret[CheckTimes])
				{
					if (ArrCIN[Order] == ArrObvious[CheckTimes])
						CorrectTimes++;
					CheckTimes = ListLenth;
				}
				else
					CheckTimes++;
			}
		}
		if (CorrectTimes == LenthArrFIN)
			return 1;
	}
	return 0;
}

/*#include<string>
#include<cstdio>
#include<iostream>
using namespace std;

//定义联系人
struct contact
{
	string name;
	string phonenumber;
	int age;
	string sex;
	string address;
};

//定义数组
contact array2[1000] = { };

//按照年龄排列联系人 并 输出最近的空联系人下标 
int line()
{

	//按照年龄从大到小冒泡排序
	for (int Order = 0; Order < 999; Order++)
	{
		for (int j1 = 0; j1 < 999 - Order; j1++)
		{

			//两两交换
			if (array2[j1].age < array2[j1 + 1].age)
			{
				struct contact temp = array2[j1];
				array2[j1] = array2[j1 + 1];
				array2[j1 + 1] = temp;
			}
		}
	}
	int num1=0;
	//找到最近的空联系人下标 并赋给num1
	for (int m1 = 0; m1 < 999; m1++)
	{
		if (array2[m1].age == 0)
		{
			num1 = m1;
			break;
		}
	}

	//输出最近的空联系人下标 
	return num1;
}

//定义值
int b1 = 0, CorrectTimes = 0, a7 = 0;
string a5 = "empty";

//删除联系人信息
void del(int a6)
{
	array2[a6].address = a5;
	array2[a6].age = 0;
	array2[a6].name = a5;
	array2[a6].phonenumber = a5;
	array2[a6].sex = a5;
}

//联系人输出 
void output(int a1)
{
	if (a1 != -1)
	{
		if (array2[a1].age != 0)
		{
			cout << "\t姓名：" << array2[a1].name << endl
				<< "\t电话：" << array2[a1].phonenumber << endl
				<< "\t性别：" << array2[a1].sex << endl
				<< "\t年龄：" << array2[a1].age << endl
				<< "\t住址：" << array2[a1].address << endl;
		}
		else
			cout << "查无此人!" << endl;
	}
	//cout << a1 << endl;						//测试代码

}

//联系人输入
void input()
{
	do
	{
		int b4 = line();

		cout << "请输入联系人姓名：";
		cin >> array2[b4].name;

		cout << "请输入联系人电话：";
		cin >> array2[b4].phonenumber;

		cout << "请输入联系人性别：";
		cin >> array2[b4].sex;
		//判断性别输入是否正确
		while (array2[b4].sex != "男" && array2[b4].sex != "女")
		{
			cout << "输入内容错误！" << endl
				<< "请重新输入联系人性别：";
			cin >> array2[b4].sex;
		}

		cout << "请输入联系人年龄：";
		cin >> array2[b4].age;
		//判断年龄输入是否正确
		while (array2[b4].age > 150 || array2[b4].age <= 0)
		{
			cout << "输入内容错误！" << endl
				<< "请重新输入联系人年龄：";
			cin >> array2[b4].age;
		}

		cout << "请输入联系人住址：";
		cin >> array2[b4].address;

		cout << endl << "\n请确认信息是否正确：" << endl;
		output(b4);
		cout << "\n1.正确并返回菜单" << "\t2.不正确并重新写入" << endl;
		cin >> b1;
		if (b1 == 2)
		{
			del(b4);
		}
	} while (b1 == 2);
}

//查找联系人 （下标a7）
void search(string a2)
{

	//判断联系人是否存在
	for (int Order = 0; Order <= 999; Order++)
	{
		a7 = Order;
		if (array2[Order].name == a2 || array2[Order].phonenumber == a2)
		{
			output(Order);
			break;
		}
	}
	//cout << a7 << endl;					//测试代码 
	if (a7 == 999)
	{
		cout << "查无此人" << endl;
	}
	system("pause");
}

//判断是否
void YoN()
{
	cout << "1.是\t2.否" << endl;
	cin >> CorrectTimes;
}

//空联系人返回文字
void empty()
{
	cout << "您还没有添加联系人！";
	system("pause");
}

//输出菜单
void menu0()
{
	cout << "欢迎使用“通讯录0.90 ” " << endl << endl;

	cout << "\t\t\t\t菜单       当前联系人数量：" << line() << " 人" << endl
		<< "请输入对应数字获取对应功能：" << endl
		<< "\t\t\t  ********************" << endl
		<< "\t\t\t  ****1.新建联系人****" << endl
		<< "\t\t\t  ****2.查找联系人****" << endl
		<< "\t\t\t  ****3.修改联系人****" << endl
		<< "\t\t\t  ****4.删除联系人****" << endl
		<< "\t\t\t  ****5.清空联系人****" << endl
		<< "\t\t\t  ****6.联系人列表****" << endl
		<< "\t\t\t  ****7.设/重置密码****" << endl
		<< "\t\t\t  ****0.同步并退出 ****" << endl
		<< "\t\t\t  ********************" << endl;
}*/