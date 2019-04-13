#include <iostream>
#include <fstream>
#include<time.h> 


	/*	Sorting algorithm "Quick sort"	*/
void QuickSort(int* arr, int left, int right) {

	int i = left;
	int j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	/* partition */

	while (i <= j) {
		while (arr[i] < pivot)
			i++;

		while (arr[j] > pivot)
			j--;

		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		QuickSort(arr, left, j);

	if (i < right)
		QuickSort(arr, i, right);
}



//CreatDataFile -> generates a sequence of random numbers of integers and save it to a file
void CreatDataFile(const char* fileName) {

	/*	Generating the random sequence	*/
	srand(time(0));//Use current time as seed for random generator

	int size = rand() % 100;//Number of elements in the sequence <100
	int* arr = new int[size + 1];
	*arr = size;//assign the size of the sequence to the first element of the  array 

	for (int i = 1; i <= size; i++) {
		arr[i] = rand() % 2000 - 1000;//sequence values -1000 < x < 1000
	}

	/*	Saving it in a file	*/	
	std::ofstream file;
	file.open(fileName);

	for (int i = 0; i <= size; i++) {
		file << arr[i] << "\n";
	}

	file.close();
}

//ReadDataFile -> reads a file with a sequence of  integers
int* ReadDataFile(const char* fileName) {

	std::ifstream file;
	file.open(fileName);

	int size;
	file >> size;	//	get the sequence size
	int* arr = new int[size + 1];
	*arr = size;	//	assign the size to the first element of the array

	for (int i = 1; i <= size; i++) {
		file >> arr[i];
	}

	file.close();

	return arr;
}

//WriteDataFile -> writes a sequence of integers to a text file in a formatted shape 
void WriteDataFile(const char* fileName, int* arr) {

	std::ofstream file;
	file.open(fileName);

	file << "The sequence contains " << *arr << " element(s):\n\n";

	for (int i = 1; i <= *arr; i++) {
		file << "#" << i << "\t----->\t" << arr[i] << "\n";
	}

	file.close();
}


// check if the array is sorted
bool ArrayIsSorted(int* arr) {

	for (int i = 2; i < *arr; i++) 
		if (arr[i] < arr[i - 1])
			return false;

	return true;
}

bool TestFile(const char* inputfile_name,const char* output_file_name)
{
	int* data=ReadDataFile(inputfile_name);	//	Get the array

	QuickSort(data, 1, *data);	//	sort the array

	WriteDataFile(output_file_name, data);	//	export the array

	return ArrayIsSorted(data);
}

int main()
{
	/*	Testing	*/
	{
		/*	Case 1:	Sorted sequence	*/
		bool passTest = TestFile("testCase1.txt", "outTestCase1.txt");

		if (passTest)
			std::cout << "Passed the 1st test...\n";
		else
			std::cout << "Code failed at the 1st test...\n";

		/*	Case 2:	Reversed sequence	*/
		passTest = TestFile("testCase2.txt", "outTestCase2.txt");

		if (passTest)
			std::cout << "Passed the 2nd test...\n";
		else
			std::cout << "Code failed at the 2nd test...\n";

		/*	Case 3:	Identical sequence	*/
		passTest = TestFile("testCase3.txt", "outTestCase3.txt");

		if (passTest)
			std::cout << "Passed the 3rd test...\n";
		else
			std::cout << "Code failed at 3rd first test...\n";

		/*	Case 4: Sequence with negative numbers	*/
		passTest = TestFile("testCase4.txt", "outTestCase4.txt");

		if (passTest)
			std::cout << "Passed the 4th test...\n";
		else
			std::cout << "Code failed at 4th first test...\n";

		/*	Case 0:	Random sequence	*/
		CreatDataFile("testCase5.txt");

		passTest = TestFile("testCase5.txt", "outTestCase5.txt");

		if (passTest)
			std::cout << "Passed the 5th test...\n";
		else
			std::cout << "Code failed at the 5th test...\n";
	}

	return 0;
}
