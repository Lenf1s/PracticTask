// НачалоString.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

bool palindrom(std::string s) {
	size_t l = 0; size_t r = s.size() - 1;
	while (l < r) {
		if (s[l] != s[r]) {
			return false;
		}
		++l; --r;
	}
	return true;
}

size_t words_counter(std::string s, std::string del) {
	std::string::size_type k{ 0 };
	size_t count = 0;
	k = s.find_first_not_of(del, k);
	while (k != -1) {
		k = s.find_first_of(del, k);
		k = s.find_first_not_of(del, k);
		++count;
	}
	return count;
}
void arr_words(std::string s, std::string del, std::string* words)
{
	std::string::size_type nw{ 0 };
	std::string::size_type ew{ 0 };
	nw = s.find_first_not_of(del);
	int i = 0;
	while (nw != -1 && ew != -1) {
		ew = s.find_first_of(del, nw);
		words[i] = s.substr(nw, ew - nw);
		nw = s.find_first_not_of(del, ew);
		++i;
	}
}

size_t len_arr_dels(std::string s, std::string del){
	size_t k = 0;
	size_t len_arr = 0;
	k = s.find_first_of(del);
	while (k != -1) {
		++len_arr;
		k = s.find_first_of(del, k+1);
	}
	return len_arr;
}
void arr_dels(std::string s, std::string del, std::string* dels) {
	std::string::size_type nw{ 0 };
	std::string::size_type ew{ 0 };
	nw = s.find_first_of(del);
	int i = 0;
	while (nw != -1 && ew != -1) {
		ew = s.find_first_not_of(del, nw);
		dels[i] = s.substr(nw, ew - nw);
		nw = s.find_first_of(del, ew);
		++i;
	}
}

void solution_ids(std::string s, std::string del, std::string* words, size_t n, int* ids, size_t e) {
	size_t l = 0; size_t g = 0;
	int j = 0;
	g = s.find_first_of(del);
	if (g != 0) {
		++j;
	}
	while(l!=-1) {
		ids[j] = -1;
		l = g;
		g = s.find_first_of(del, l + 1);
		if (g - l == 1) {
			++j;
			continue;
		}
		++++j;
	}

	j = 0;
	for (int i = 0; i < e; ++i) {
		if (ids[i] != -1) {
			if (palindrom(words[j])) {
				ids[i] = words[j].size();
			}
			++j;
		}
	}
}

void solution_top(std::string s, std::string del, std::string* words, size_t n, std::string* top, size_t k, int* ids, size_t e) {
	//заполнение массива top
	size_t id_maxlen{ 0 };
	int h = 0;
	for (int i = 0; i < k; ++i) {
		h = 0;
		id_maxlen = 0;
		for (int j = 0; j < e; ++j) {
			if (ids[id_maxlen] < ids[j])
			{
				id_maxlen = j;
			}
		}
		for (int i = 0; i < id_maxlen;++i) {
			if (ids[i] == -1) {
				++h;
			}
		}
		top[i] = words[id_maxlen-h];
		ids[id_maxlen] = 0;
	}
	//сортировка массива top
	bool puls = true;
	while (puls) {
		puls = false;
		for (int i = 0; i < k - 1; ++i) {
			if (top[i] > top[i + 1]) {
				top[i].swap(top[i + 1]);
				puls = true;
			}
		}
	}
}

void peresborka_s(std::string &s, std::string* words, size_t n, std::string* top, size_t k, std::string* dels, size_t m, int* ids, size_t e) {
	s.clear();
	int c = 0;
	int p = 0;
	bool puls = true;
	if (ids[p] == -1) {
		s += dels[p];
		++p;
	}
	for (int i = 0; i < n; ++i) {
		puls = true;
		for (int g = 0; g < k; ++g) {
			if (words[i] == top[g]) {
				s += top[c];
				++c;
				s += dels[p];
				++p;
				puls = false;
			}
		}
		if (puls) {
			s += words[i];
			s += dels[p];
			++p;
		}
	}

}

int main()
{
	std::string s = "    // The//tactical, :radar detected a, fast racecar while the,   civic leader used a kayak to cross;the river";
	std::string del = "/ .,:;";

	int n = words_counter(s, del); size_t m = len_arr_dels(s, del);
	int k = 3; size_t e = n + m;

	std::string* words = new std::string[n];
	std::string* dels = new std::string[m];
	std::string* top = new std::string[k];
	int* ids = new int[e] {0};

	arr_words(s, del, words);
	arr_dels(s, del, dels);
	solution_ids(s, del, words, n, ids, e);
	solution_top(s, del, words, n, top, k, ids, e);

	std::cout << s << '\n';
	peresborka_s(s, words, n, top, k, dels, m, ids, e);
	std::cout << s;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
