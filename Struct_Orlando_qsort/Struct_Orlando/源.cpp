#define _CRT_SECURE_NO_WARNINGS
#include"Orlando.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#include "direct.h"


SStu stu[10];
int Total;
void Load()
{
	FILE* pf = NULL;
	fopen_s(&pf, ".\\student.orlando", "r");
	if (!pf)
	{
		puts("Load file error!");
		return;
	}
	int i = 0;
	while (fread(&stu[i], 1, sizeof(stu[0]), pf) == sizeof(stu[0]))
		++i;
	fclose(pf);
}
void Save()
{
	FILE* pf = NULL;
	fopen_s(&pf, ".\\student.orlando", "w");
	if (!pf)
	{
		puts("Save file error!");
		return;
	}
	int i = 0;
	while (stu[i].nNum)
	{
		if (stu[i].nNum != -1)
		{
			fwrite(&stu[i], 1, sizeof(stu[0]), pf);
		}
		++i;
	}
	fclose(pf);
}


void Show_All()
{
	int i = 0;
	Total = 0;
	puts("\n\n\tNum\tName\tChi\tMath\tEng\n");

	while (stu[i].nNum)
	{
		if (stu[i].nNum != -1)
		{
			printf("\t%d\t%s\t%0.1f\t%0.1f\t%0.1f\n", stu[i].nNum, stu[i].sName, stu[i].fChi, stu[i].fMath, stu[i].fEng);
			Total++;
		}
		++i;

	}
	printf("\n\tThere is %d messages in total.\n", Total);
}

void Add()
{
	int i = 0;
	while (stu[i].nNum > 0)
		++i;
	puts("\nPlease input Number:");
	fflush(stdin);
	scanf_s("%d", &stu[i].nNum);

	puts("\nPlease input Name:");
	fflush(stdin);
	scanf_s("%s", stu[i].sName, sizeof(stu[i].sName));

	puts("\nChinese record:");
	fflush(stdin);
	scanf_s("%f", &stu[i].fChi);

	puts("\nMath record:");
	fflush(stdin);
	scanf_s("%f", &stu[i].fMath);

	puts("\nEnglish record:");
	fflush(stdin);
	scanf_s("%f", &stu[i].fEng);

	Save();
}
void Delete()
{
	puts("\nInput the Number you want to Delete:");
	int n = 0;
	scanf_s("%d", &n);
	int i = 0, flag = 0;
	while (stu[i].nNum)
	{
		if (stu[i].nNum == n)
		{
			stu[i].nNum = -1;
			flag = 1;
			break;
		}
		++i;
	}
	if (flag == 0)puts("Invalid input!");
	else puts("Delete OK!");
	Save();
}

void Modify()
{
	puts("\nInput the Number of one you want to modify:");
	int n = 0;
	scanf_s("%d", &n);
	int i = 0, flag = 0;
	while (stu[i].nNum)
	{
		if (stu[i].nNum == n)
		{
			flag = 1;

			puts("\nPlease input new Number:");
			fflush(stdin);
			scanf_s("%d", &stu[i].nNum);

			puts("\nPlease input new Name:");
			fflush(stdin);
			scanf_s("%s", stu[i].sName, sizeof(stu[i].sName));

			puts("\nNew Chinese record:");
			fflush(stdin);
			scanf_s("%f", &stu[i].fChi);

			puts("\nNew Math record:");
			fflush(stdin);
			scanf_s("%f", &stu[i].fMath);

			puts("\nNew English record:");
			fflush(stdin);
			scanf_s("%f", &stu[i].fEng);

		}
		++i;
	}
	if (flag == 0)puts("\nInvalid input!\n");
	else
		puts("\nModify OK!\n");
	Save();
}

void Search()
{
	puts("\nInput the Number of one you want to Search:");
	int n = 0;
	scanf_s("%d", &n);
	int i = 0, flag = 0;
	while (stu[i].nNum)
	{
		if (stu[i].nNum == n)
		{
			flag = 1;
			printf("\t%d\t%s\t%0.1f\t%0.1f\t%0.1f\n", stu[i].nNum, stu[i].sName, stu[i].fChi, stu[i].fMath, stu[i].fEng);
		}
		++i;
	}
	if (flag == 0)puts("\nInvalid input!\n");
}

int byNumber(const void *pS1, const void *pS2)
{
	return ((SStu*)pS1)->nNum - ((SStu*)pS2)->nNum;
}

int byName(const void *pS1, const void *pS2)
{//如果名字相同，则按学号比较
	if (((SStu*)pS1)->sName != ((SStu*)pS2)->sName)
		return strcmp(((SStu*)pS1)->sName, ((SStu*)pS2)->sName);
	else
		return ((SStu*)pS1)->nNum - ((SStu*)pS2)->nNum;
}

int byChinese(const void *pS1, const void *pS2)
{//如果该科成绩相同，则按学号比较
	if ((int)((SStu*)pS2)->fChi != (int)((SStu*)pS1)->fChi)
		return (int)((SStu*)pS2)->fChi - (int)((SStu*)pS1)->fChi;
	else
		return ((SStu*)pS1)->nNum - ((SStu*)pS2)->nNum;
}

int byMath(const void *pS1, const void *pS2)
{//如果该科成绩相同，则按学号比较
	if((int)((SStu*)pS2)->fMath != (int)((SStu*)pS1)->fMath)
	return (int)((SStu*)pS2)->fMath - (int)((SStu*)pS1)->fMath;
	else 
		return ((SStu*)pS1)->nNum - ((SStu*)pS2)->nNum;
}

int byEnglish(const void *pS1, const void *pS2)
{//如果该科成绩相同，则按学号比较
	if((int)((SStu*)pS2)->fEng != (int)((SStu*)pS1)->fEng)
	return (int)((SStu*)pS2)->fEng - (int)((SStu*)pS1)->fEng;
	else 
		return ((SStu*)pS1)->nNum - ((SStu*)pS2)->nNum;
}

void Sort(char sortby)
{//快速排序
	int i = 0;
	while (stu[i].nNum)++i;
	//若直接用_countof(stu)作数目，内容为0的条目也参与比较
	//出现倒序时0在上，数据在最最最下面

	if (sortby == '1')
		qsort(stu, i, sizeof(stu[0]), byNumber);

	if (sortby == '2')
		qsort(stu, i, sizeof(stu[0]), byName);

	if (sortby == '3')
		qsort(stu, i, sizeof(stu[0]), byChinese);

	if (sortby == '4')
		qsort(stu, i, sizeof(stu[0]), byMath);

	if (sortby == '5')
		qsort(stu, i, sizeof(stu[0]), byEnglish);

	Save();
	Show_All();
}


char SortMenu()
{
	puts("\n\n\t1.  Sort by number");
	puts("\t2.  Sort by name");
	puts("\t3.  Sort by Chinese record");
	puts("\t4.  Sort by Math record");
	puts("\t5.  Sort by English record");
	puts("\t0.  Exit");

	printf("\n\tPlease enter 0-5:");

	char c = 0;
	c = _getche();
	switch (c)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		Sort(c);
		break;

	case '0':
		puts("Back to main menu...\n\n");
		break;

	default:
		puts("\nInvalid entering,choose again.\n");
	}

	return c;
}


char Menu()
{
	puts("\n\n\t1.  Show all");
	puts("\t2.  Add");
	puts("\t3.  Delete");
	puts("\t4.  Modify");
	puts("\t5.  Search");
	puts("\t6.  Sort");
	puts("\t0.  Exit");

	printf("\n\tPlease enter 0-6:");

	char c = 0;
	c = _getche();
	switch (c)
	{
	case '1':
		Show_All();
		break;
	case '2':
		Add();
		break;
	case '3':
		Delete();
		break;
	case '4':
		Modify();
		break;
	case '5':
		Search();
		break;
	case '6':
		while (SortMenu() != '0');
		break;
	case '0':
		puts("Exit...\n\n");
		break;
	default:
		puts("\nInvalid entering,choose again.\n");
	}
	return c;
}


int main()
{
	//system("color 0c");
	//一更改就是全局变色
	FILE* pf = nullptr;
	fopen_s(&pf, ".\\student.orlando", "a");
	if (!pf)
	{
		puts("Initialize failed！");
		return -1;
	}
	fclose(pf);

	Load();


	while (Menu() != '0');

	system("pause");
	return 0;
}