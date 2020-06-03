#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <chrono>
#include "matrix.h"
#include <mutex>

std::mutex consolemut;
std::mutex avbmut;
std::mutex bvamut;
std::mutex aorbmut;
/*std::mutex fmut;
std::mutex dmut;
std::mutex orfmut;
std::mutex anddmut;
std::mutex orfanddmut;
*/
int Tackt;

double avb(double, double);
double bva(double, double);
double aorb(double, double);
double f(double, double, double);
double d(double, double);
double orf(std::vector<double>, std::vector<double>, std::vector<double>);
double andd(std::vector<double>, std::vector<double>);
double orfandd(std::vector<double>, std::vector<double>, std::vector<double>);
void TacktCount();

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));
	Tackt = -1;
	int p = 1;// + std::rand() % 5;
	int q = 2;// + std::rand() % 5;
	int m = 4;//1 + std::rand() % 5;
	Matrix matrixA(p, m), matrixB(m, q), matrixE(1, m), matrixG(p, q), matrixC(p, q);
	std::cout << "Матрица А : " << std::endl;
	matrixA.getMatrix();
	std::cout << "Матрица B : " << std::endl;
	matrixB.getMatrix();
	std::cout << "Матрица E: " << std::endl;
	matrixE.getMatrix();
	std::cout << "Матрица G : " << std::endl;
	matrixG.getMatrix();
	std::thread th0(TacktCount);
	th0.detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(13));
	for (auto i = 0; i < p; i++) {
		std::vector<double> tempA;
		std::vector<double> vec;
		tempA = matrixA.getmatrix()[i];
		for (auto j = 0; j < q; j++) {
			std::vector<double> tempB;
			for (auto k = 0; k < m; k++) {
				tempB.push_back(matrixB.getmatrix()[k][j]);
			}
			double c;

			double rezorf;
			//auto f1 = [&rezorf](std::vector<double> ai, std::vector<double> bi, std::vector<double> ei) {rezorf = orf(ai, bi, ei); };
			//std::thread th(f1, tempA, tempB, matrixE.getmatrix()[0]);

			rezorf = orf(tempA, tempB, matrixE.getmatrix()[0]);

			double rezandd;
			//auto f2 = [&rezandd](std::vector<double> ai, std::vector<double> bi) {rezandd = andd(ai, bi); };
			//std::thread th1(f2, tempA, tempB);
			rezandd = andd(tempA, tempB);

			double rezorfandd;
			//auto f3 = [&rezorfandd](std::vector<double> ai, std::vector<double> bi, std::vector<double> ei) {rezorfandd = orfandd(ai, bi,ei); };
			//std::thread th2(f3, tempA, tempB, matrixE.getmatrix()[0]);
			rezorfandd = orfandd(tempA, tempB, matrixE.getmatrix()[0]);

			//th.join();
			//th1.join();
			//th2.join();


			c = rezorf * (3 * matrixG.getmatrix()[i][j] - 2) * matrixG.getmatrix()[i][j] + (rezandd + (4 * (rezorfandd)-3 * rezandd) * matrixG.getmatrix()[i][j]) * (1 - matrixG.getmatrix()[i][j]);
			vec.push_back(c);
		}
		matrixC.setmatrix(vec, i);
	}
	consolemut.lock();
	std::cout << "Матрица C : " << std::endl;
	matrixC.getMatrix();
	consolemut.unlock();
	return 0;
}

double avb(double a, double b) {
	std::lock_guard<std::mutex> mut(avbmut);
	while (Tackt < 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "В процессорный элемент передана функция а -> b" << std::endl;
	consolemut.unlock();
	int time = Tackt;
	while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий функцию а -> b закончил подсчет" << std::endl;
	consolemut.unlock();
	if ((1 - a) > b) {

		return 1 - a;
	}
	else {
		return b;
	}
}

double bva(double a, double b) {
	std::lock_guard<std::mutex> mut(bvamut);
	while (Tackt < 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "В процессорный элемент передана функция b -> a" << std::endl;
	consolemut.unlock();
	int time = Tackt;
	while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий функцию b -> a закончил подсчет " << std::endl;
	consolemut.unlock();
	if ((1 - b) > a) {
		return 1 - b;
	}
	else {
		return a;
	}
}

double aorb(double a, double b) {
	std::lock_guard<std::mutex> mut(aorbmut);
	while (Tackt < 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "В процессорный элемент передана функция a ^ b " << std::endl;
	consolemut.unlock();
	int time = Tackt;
	while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий функцию a ^ b закончил подсчет" << std::endl;
	consolemut.unlock();
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

double f(double a, double b, double e) {
	/*std::lock_guard<std::mutex> mut(fmut);
	consolemut.lock();
	std::cout << "Вызван процессорный элемент считающий элемент матрицы f " << std::endl;
	consolemut.unlock();
	int time = Tackt;
	*/

	double fijk;

	double rezavb;
	auto f1 = [&rezavb](double a, double b) {rezavb = avb(a, b); };
	std::thread th(f1, a, b);

	double rezbva;
	auto f2 = [&rezbva](double a, double b) {rezbva = bva(a, b); };
	std::thread th1(f2, a, b);

	th.join();
	th1.join();

	fijk = rezavb * (2 * e - 1) + rezbva * (1 + (4 * rezavb - 2) * e) * (1 - e);
	/*while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий элемент матрицы f закончил подсчет" << std::endl;
	consolemut.unlock();
	*/
	return fijk;
}

double d(double a, double b) {
	/*std::lock_guard<std::mutex> mut(dmut);
	consolemut.lock();
	std::cout << "Вызван процессорный элемент считающий элемент матрицы d " << std::endl;
	consolemut.unlock();
	int time = Tackt;
	*/
	double dijk;
	double rezaorb;
	auto f1 = [&rezaorb](double a, double b) {rezaorb = aorb(a, b); };
	std::thread th(f1, a, b);
	th.join();

	dijk = rezaorb;
	/*while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий элемент матрицы d закончил подсчет" << std::endl;
	consolemut.unlock();
	*/
	return dijk;
}

double orf(std::vector<double> a, std::vector<double> b, std::vector<double> e) {
	/*std::lock_guard<std::mutex> mut(orfmut);
	consolemut.lock();
	std::cout << "Вызван процессорный элемент считающий функцию ^f " << std::endl;
	consolemut.unlock();
	int time = Tackt;
	*/
	double fijk = 1;
	for (int i = 0; i < a.size(); i++) {
		double rezf = f(a[i], b[i], e[i]);
		/*auto f1 = [&rezf](double ai, double bi,double ei) {rezf = f(ai, bi,ei); };
		std::thread th(f1, a[i], b[i],e[i]);
		th.join();
		*/
		fijk *= rezf;
	}
	/*while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий функцию ^f закончил подсчет" << std::endl;
	consolemut.unlock();
	*/
	return fijk;
}

double andd(std::vector<double> a, std::vector<double> b) {
	/*std::lock_guard<std::mutex> mut(anddmut);
	consolemut.lock();
	std::cout << "Вызван процессорный элемент считающий функцию vd " << std::endl;
	consolemut.unlock();
	int time = Tackt;
	*/
	double dijk = 1;
	for (int i = 0; i < a.size(); i++) {
		double rezd = d(a[i], b[i]);
		/*auto f1 = [&rezd](double ai, double bi) {rezd = d(ai, bi); };
		std::thread th(f1, a[i], b[i]);
		th.join();
		*/
		dijk *= (1 - rezd);
	}
	/*while (time + 1 > Tackt) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	consolemut.lock();
	std::cout << "Процессорный элемент считающий функцию vd закончил подсчет" << std::endl;
	consolemut.unlock();
	*/
	return 1 - dijk;
}

double orfandd(std::vector<double> a, std::vector<double> b, std::vector<double> e) {
	/*std::lock_guard<std::mutex> mut(orfanddmut);
	consolemut.lock();
	std::cout << "Вызван процессорный элемент считающий функцию ^fvd " << std::endl;
	consolemut.unlock();
	int time = Tackt;
	*/
	double fd = 1;

	double rezorf = orf(a, b, e);
	/*auto f1 = [&rezorf](std::vector<double> ai, std::vector<double> bi, std::vector<double> ei) {rezorf = orf(ai, bi,ei); };
	std::thread th(f1, a, b,e);
	*/
	double rezandd = andd(a, b);
	/*auto f2 = [&rezandd](std::vector<double> ai, std::vector<double> bi) {rezandd = andd(ai, bi); };
	std::thread th1(f2, a, b);

	th.join();
	th1.join();
	*/
	if (rezorf + rezandd - 1 > 0) {
		/*while (time + 1 > Tackt) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		consolemut.lock();
		std::cout << "Процессорный элемент считающий функцию ^fvd закончил подсчет" << std::endl;
		consolemut.unlock();
		*/
		return rezorf + rezandd - 1;
	}
	else {
		/*while (time + 1 > Tackt) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		consolemut.lock();
		std::cout << "Процессорный элемент считающий функцию ^fvd закончил подсчет" << std::endl;
		consolemut.unlock();
		*/
		return 0;
	}
}

void TacktCount() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		Tackt++;
		consolemut.lock();
		std::cout << "Такт :  " << Tackt << std::endl;
		consolemut.unlock();
		if (Tackt > 200) {
			break;
		}
	}
}