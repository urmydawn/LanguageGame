#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 10000

void Load(const char* fileName)
{

	FILE* file = fopen(fileName, "r");

	char buffer[SIZE] = { 0, };

	// ù ��° �Ű����� : ���� �����͸� ������ �޸� ������ ������ ����
	// �� ��° �Ű����� : �� ������ �׸��� ũ��
	// �� ��° �Ű����� : �о�� �������� �׸��� ��
	// �� ��° �Ű����� : �����͸� �о�� ������ ������ ����

	//while (fgets(buffer, sizeof(buffer), file) != NULL) 
	//{

	fread(buffer, 1, SIZE, file);

	printf("%s", buffer);
	//}
	fclose(file);
}



int main()
{
#pragma region ���� �����

#pragma region ���� ����

	// ù ��° �Ű����� (������ �̸�)
	// �� ��° �Ű����� (������ ����� ���)
	//	FILE * file = fopen("data.txt", "w");
	//	
	//	fputs("Character Information", file);
	//	fputs("Health : \n", file);
	//	fputs("Attack : \n", file);
	//	fputs("Defense : \n", file);
	//	
	//	
	//	fclose(file);

#pragma endregion

#pragma region ���� �б�

	//Load("Bird.txt");


#pragma endregion



#pragma endregion



	return 0;
}