#include <algorithm>
#include <set>
#include <iostream>
#include <windows.h>

using namespace std;

set<int> findValues(int j, int i, vector<vector<int>> &sudoku){ // найти допустимые значения для клетки по коодинатам i, j
	set<int> values;
	for(int i = 1; i < 10; i++){
		values.insert(i);
	}

	for(int k = 0; k < 9; k++){
		values.erase(sudoku.at(j).at(k));
		values.erase(sudoku.at(k).at(i));
	}

	int x_block = 3 * (i / 3), y_block = 3 * (j / 3);
	
	for(int k = 0; k < 3; k++){
		for(int g = 0; g < 3; g++){
			values.erase(sudoku.at(y_block + k).at(x_block + g));
		}
	}
	return values;
}

bool solve(vector<vector<int>> *sudoku)
{
	set<int> minValues; // возможные значения для первой свобдной клетки
	int minRow = -1; // координаты первой свободной клетки
	int minColumn = -1;
	
	while(1){
        minRow = -1;
            for(int j = 0; j < 9; j++) {
                for(int i = 0; i < 9; i++) {
                    if((*sudoku)[j][i] != 0) { // ищем первую свободную клетку
                        continue;
                    }
                    set<int> values = findValues(j, i, *sudoku); // находим допустимые значения для клетки

                    int valueCount = values.size();
                    if(valueCount == 0) { // если нет допустимых значений, то значит решений нет
                        return false;
                    }
                    if( valueCount == 1 ) { // если оно одно сразу записываем значение
                        (*sudoku)[j][i] = *values.begin();
                    }
                    
                    if(minRow < 0 || valueCount < minValues.size()){ // одновременно ищем клетку с минимальным количеством вариантов значения
                        minRow = j;
                        minColumn = i;
                        minValues = values;
                    }
                }
            }
            if(minRow == -1){ // если все клетки заполнены, то решение найдено
                return true;
            } else if(minValues.size() > 1){ // если у клетки с минимальным количеством вариантов значений больше одного возможного значения, то выходим из цикла и проходим к рекурсии
                break;
            }
        }
        for( int x : minValues ) {
            vector<vector<int>> sudokuCopy = *sudoku; // для каждого возможного значения создаем копию "таблицы" и записываем в клетку это значание
            sudokuCopy[minRow][minColumn] = x;
            if(solve(&sudokuCopy)){ // и рекурсивно запускаем решение для копии
                *sudoku = sudokuCopy;
                return true; // если там найдено решение, берем решенную копию и возвращаемся с этим результатом
            }
        }
    return false;
}


vector<vector<int>> getSolution(const vector<vector<int>> &sudoku){
	vector<vector<int>> solution = sudoku;
	if(solve(&solution)){
		return solution;
	}
	
	vector<vector<int>> temp;
	return temp;
}

void printSudoku(const vector<vector<int>> &sudoku){
	for(int j = 0; j < sudoku.size(); j++){
		for(int i = 0; i < sudoku.at(j).size(); i++){
			cout << sudoku.at(j).at(i) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	setlocale(LC_CTYPE, "rus");
	SetConsoleTitle(TEXT("Sudoku"));
	
	vector<vector<int>> sudoku ={
    { 3, 0, 0, 2, 0, 0, 0, 0, 0 },
    { 0, 7, 2, 6, 0, 1, 3, 0, 0 },
    { 5, 4, 0, 0, 0, 0, 0, 9, 2 },
    { 0, 0, 3, 1, 6, 0, 2, 8, 0 },
    { 0, 1, 0, 0, 5, 0, 0, 7, 0 },
    { 0, 9, 7, 0, 3, 8, 5, 0, 0 },
    { 7, 2, 0, 0, 0, 0, 0, 4, 8 },
    { 0, 0, 6, 7, 0, 4, 1, 3, 0 },
    { 0, 0, 0, 0, 0, 9, 0, 0, 6 }};
    
	vector<vector<int>> sudoku1 = {
    { 1, 0, 0, 4, 8, 9, 0, 0, 6 },
    { 7, 3, 0, 0, 0, 0, 0, 4, 0 },
    { 0, 0, 0, 0, 0, 1, 2, 9, 5 },
    { 0, 0, 7, 1, 2, 0, 6, 0, 0 },
    { 5, 0, 0, 7, 0, 3, 0, 0, 8 },
    { 0, 0, 6, 0, 9, 5, 7, 0, 0 },
    { 9, 1, 4, 6, 0, 0, 0, 0, 0 },
    { 0, 2, 0, 0, 0, 0, 0, 3, 7 },
    { 8, 0, 0, 5, 1, 2, 0, 0, 4 }};
    
    vector<vector<int>> sudoku2 = {
    { 0, 2, 0, 6, 0, 8, 0, 0, 0 },
    { 5, 8, 0, 0, 0, 9, 7, 0, 0 },
    { 0, 0, 0, 0, 4, 0, 0, 0, 0 },
    { 3, 7, 0, 0, 0, 0, 5, 0, 0 },
    { 6, 0, 0, 0, 0, 0, 0, 0, 4 },
    { 0, 0, 8, 0, 0, 0, 0, 1, 3 },
    { 0, 0, 0, 0, 2, 0, 0, 0, 0 },
    { 0, 0, 9, 8, 0, 0, 0, 3, 6 },
    { 0, 0, 0, 3, 0, 6, 0, 9, 0 }};
    
    
    printSudoku(sudoku);
    cout << endl;
	
    vector<vector<int>> result = getSolution(sudoku);
    if(result.empty()) cout << "Решение не найдено." << endl;
    else {
    	printSudoku(result);
	}
	cout << endl;
    system("PAUSE");
    return 0;
}
