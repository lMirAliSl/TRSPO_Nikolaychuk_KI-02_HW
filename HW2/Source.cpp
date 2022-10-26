#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <iomanip>

using namespace std;

mutex mutex1;
mutex mutex2;

class First_class {
private:
	double num1;
public:
	First_class() {
		num1 = 20;
	}
	void Write1(double number) {
		num1 = number;
	}
	double Read1() {
		return num1;
	}
	void Sum1(double number) {
		mutex1.lock();
		num1 += number;
		mutex1.unlock();
	}
};

class Second_class {
private:
	double num2;
public:
	Second_class() {
		num2 = 10;
	}
	void Write2(double number) {
		num2 = number;
	}
	double Read2() {
		return num2;
	}
	void Sum2(double number) {
		mutex2.lock();
		num2 += number;
		mutex2.unlock();
	}
};

void Func_Sum1(First_class* first, Second_class* second) {
	int num = std::rand() % 10000 + 10000;
	for (int i = 0; i < num; i++) {
		double rand1 = std::rand() % 10;
		first->Sum1(rand1);
		double rand2 = std::rand() % 10;
		second->Sum2(rand2);
	}
}

void Func_Sum2(First_class* first, Second_class* second) {
	int num = std::rand() % 10000 + 10000;
	for (int i = 0; i < num; i++) {
		double rand1 = std::rand() % 10;
		second->Sum2(rand1);
		double rand2 = std::rand() % 10;
		first->Sum1(rand2);
	}
}

int main() {
	srand(0);
	First_class First_class;
	Second_class Second_class;

	vector<thread> thread_arr;
	int n = rand() % 10 + 10;

	for (int i = 0; i < n; i++) {
		if (i < n / 2) {
			thread_arr.push_back(thread(Func_Sum1, &First_class, &Second_class));
		}
		else {
			thread_arr.push_back(thread(Func_Sum2, &First_class, &Second_class));
		}
	}
	for (int i = 0; i < n; i++) {
		thread_arr[i].join();
	}


	int end = 0;
	cout << "First class - " << First_class.Read1() << endl << "Second class - " << Second_class.Read2() << endl;
}