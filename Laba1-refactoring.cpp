#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void matrix_first (int** array, int n, int m ) {
	for (int i = 0; i < n; i++) {
		array[i] = new int[m]; 
	}
}

void matrix_choice(int** array, int n, int m, int k) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (k == 1)
				cin >> array[i][j];
			else if (k == 2)
				array[i][j] = rand() % 10;
			else
				cout << "Wrong choice. Enter 1 or 2.";
}

void matrix_print(int** array, int n, int m) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
}

int** matrix_reduction(int l, int** array, int n, int m) {
	int** M = new int* [l];
	for (int i = 0; i < l; i++)
	{
		M[i] = new int[l];
		for (int j = 0; j < l; j++)
			M[i][j] = 0;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i][j] = array[i][j];
	return M;
}

void partion_matrix(int** matrix, int l, int** mat1, int** mat2, int** mat3, int** mat4) {

	for (int i = 0; i < l / 2; i++)
	{
		mat1[i] = new int[l / 2];
		for (int j = 0; j < l / 2; j++)
			mat1[i][j] = matrix[i][j];
	}

	for (int i = 0; i < l / 2; i++)
	{
		mat2[i] = new int[l / 2];
		for (int j = 0; j < l / 2; j++)
			mat2[i][j] = matrix[i][j + l / 2];
	}

	for (int i = 0; i < l / 2; i++)
	{
		mat3[i] = new int[l / 2];
		for (int j = 0; j < l / 2; j++)
			mat3[i][j] = matrix[i + l / 2][j];
	}

	for (int i = 0; i < l / 2; i++)
	{
		mat4[i] = new int[l / 2];
		for (int j = 0; j < l / 2; j++)
			mat4[i][j] = matrix[i + l / 2][j + l / 2];
	}
}
void matrix_delete(int*** matrix, int m_size, int m_elem) {
	for (int i = 0; i < m_size; i++)
		for (int j = 0; j < m_elem; j++)
			delete[] matrix[i][j];
	for (int i = 0; i < m_size; i++)
		delete[] matrix[i];

}
int main()
{
   
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int n1, m1, n2, m2, l = 2;
	system("chcp 1251");
	cout << "You are welcomed by the program" << endl << 
		"of fast matrix multiplication by the Strassen method\n\n";

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Enter size of matrix////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	do {
		cout << "Enter size of first matrix\n";
		cin >> n1 >> m1;
	}
	while (n1 <= 0 || m1 <= 0);
   
	do {
		cout << "Enter size of second matrix\n";
		cin >> n2 >> m2;
	}
	while (n2 <= 0 || m2 <= 0);


	int** M1 = new int* [n1];
	matrix_first(M1, n1, m1);
	int** M2 = new int* [n2];
	matrix_first(M1, n2, m2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения и заполнение матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	int k = 0;
	do {
		cout << "Select a metod of filling matrix\n" <<
			"1 - By hand \n2 - Random\n";
		cin >> k;
	} while (k < 1 || k > 2);

	matrix_choice(M1, n1, m1, k);
	matrix_choice(M2, n2, m2, k);
	cout << "First matrix:" << endl;
	matrix_print(M1, n1, m1);
	cout << "Second matrix:" << endl;
	matrix_print(M2, n2, m2);

	
	///////////////////////////////////////////////////////////////////////////////
	/////////////////Приведение матриц к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	while (l < n1 || l < n2 || l < m1 || l < m2)
		l *= 2;


	int** M3 = matrix_reduction(l, M1, n1, m1);
	int** M4 = matrix_reduction(l, M2, n2, m2);
	cout << "Reduced matrix\n";
	cout << "\nFirst matrix: \n\n";
	matrix_print(M3, l, l);
	
	cout << "\nSecond matrix: \n\n";
	matrix_print(M4, l, l);

	///////////////////////////////////////////////////////////////////////////////
	///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** mat1 = new int* [l / 2];
	int** mat2 = new int* [l / 2];
	int** mat3 = new int* [l / 2];
	int** mat4 = new int* [l / 2];
	partion_matrix(M3, l, mat1, mat2, mat3, mat4);
	int** mat5 = new int* [l / 2];
	int** mat6 = new int* [l / 2];
	int** mat7 = new int* [l / 2];
	int** mat8 = new int* [l / 2];
	partion_matrix(M4, l, mat5, mat6, mat7, mat8);

	int*** partion = new int** [8];
	for (int i = 0; i < 8; i++)
	{
		partion[i] = new int* [l / 2];
		for (int j = 0; j < l / 2; j++)
			partion[i][j] = new int[l / 2];
	}

	for (int i = 0; i < l / 2; i++)
		for (int j = 0; j < l / 2; j++) {
			partion[0][i][j] = M3[i][j];
			partion[1][i][j] = M3[i][j + l / 2];
			partion[2][i][j] = M3[i + l / 2][j];
			partion[3][i][j] = M3[i + l / 2][j + l / 2];
			partion[4][i][j] = M4[i][j];
			partion[5][i][j] = M4[i][j + l / 2];
			partion[6][i][j] = M4[i + l / 2][j];
			partion[7][i][j] = M4[i + l / 2][j + l / 2];
		}

	///////////////////////////////////////////////////////////////////////////////
	//////////////////////////Создание массива промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int*** p = new int** [7];
	for (int i = 0; i < 7; i++)
	{
		p[i] = new int* [l / 2];
		for (int j = 0; j < l / 2; j++)
			p[i][j] = new int[l / 2];
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < l / 2; j++)
			for (int k = 0; k < l / 2; k++)
				p[i][j][k] = 0;

	for (int i = 0; i < l / 2; i++)
		for (int j = 0; j < l / 2; j++)
			for (int z = 0; z < l / 2; z++) {
				p[0][i][j] += (partion[0][i][z] + partion[3][i][z]) * (partion[4][z][j] + partion[7][z][j]);
				p[1][i][j] += (partion[2][i][z] + partion[3][i][z]) * partion[4][z][j];
				p[2][i][j] += partion[0][i][z] * (partion[5][z][j] - partion[7][z][j]);
				p[3][i][j] += partion[3][i][z] * (partion[6][z][j] - partion[4][z][j]);
				p[4][i][j] += (partion[0][i][z] + partion[1][i][z]) * partion[7][z][j];
				p[5][i][j] += (partion[2][i][z] - partion[0][i][z]) * (partion[4][z][j] + partion[5][z][j]);
				p[6][i][j] += (partion[1][i][z] - partion[3][i][z]) * (partion[6][z][j] + partion[7][z][j]);
			}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Ñîçäàíèå âñïîìîãàòåëüíûõ ìàòðèö/////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int*** aux_m = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		aux_m[i] = new int* [l / 2];
		matrix_first(aux_m[i], l/2, l/2);

	}

	///////////////////////////////////////////////////////////////////////////////
	////////////Ïîäñ÷åò çíà÷åíèé âñïîìîãàòåëüíûõ ìàòðèö èç ïðîìåæóòî÷íûõ///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			aux_m[0][i][j] = p[0][i][j] + p[3][i][j] - p[4][i][j] + p[6][i][j];
			aux_m[1][i][j] = p[2][i][j] + p[4][i][j];
			aux_m[2][i][j] = p[1][i][j] + p[3][i][j];
			aux_m[3][i][j] = p[0][i][j] - p[1][i][j] + p[2][i][j] + p[5][i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** M5 = new int* [l];
	for (int i = 0; i < l; i++)
	{
		M5[i] = new int[l];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из списка вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			M5[i][j] = aux_m[0][i][j];
			M5[i][j + l / 2] = aux_m[1][i][j];
			M5[i + l / 2][j] = aux_m[2][i][j];
			M5[i + l / 2][j + l / 2] = aux_m[3][i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5[i][j] != 0)
			{
				x++;
				f = 100;
			}
		}
		if (x == 0 && i < f)
		{
			f = i;
		}
	}
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5[j][i] != 0)
			{
				x++;
				s = 100;
			}
		}
		if (x == 0 && i < s)
		{
			s = i;
		}
	}

	int** result = new int* [f];
	for (int i = 0; i < f; i++)
	{
		result[i] = new int[s];
		for (int j = 0; j < s; j++)
			result[i][j] = M5[i][j];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "\nResult matrixn\n";
	for (int i = 0; i < f; i++)
	{
		for (int j = 0; j < s; j++)
			cout << result[i][j] << " ";
		cout << endl;
	}

	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < n1; i++)
		delete[] M1[i];
	for (int i = 0; i < n2; i++)
		delete[] M2[i];
	for (int i = 0; i < l; i++)
	{
		delete[] M3[i];
		delete[] M4[i];
		delete[] M5[i];
	}
	for (int i = 0; i < f; i++)
		delete[] result[i];
	for (int i = 0; i < l / 2; i++)
	{
		delete[] mat1[i];
		delete[] mat2[i];
		delete[] mat3[i];
		delete[] mat4[i];
		delete[] mat5[i];
		delete[] mat6[i];
		delete[] mat7[i];
		delete[] mat8[i];
	}

	matrix_delete(aux_m, 4, l / 2);
	matrix_delete(p, 7, l / 2);
	matrix_delete(partion, 8, l / 2);
	delete[] M1, M2, M3, M4, M5, result;
	delete[] mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8;
	delete[] p, aux_m, partion;
}