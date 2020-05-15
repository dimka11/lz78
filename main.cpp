#include <list>
#include <map>
#include <string>
#include <iterator>
#include <iostream>

#include "Node.h"

using namespace std;

list<Node> encodeLZ78(string s)
{
	string buffer = ""; // текущий префикс
	map<string, int> dict = map<string, int>(); // словарь
	list<Node> ans = list<Node>(); // ответ

	for (size_t i = 0; i <= s.length() - 1; i++)
	{
		if (dict.count( buffer + s[i]) > 0) // можем ли мы увеличить префикс
		{
			buffer += s[i];
		}
		else
		{
			ans.push_back({ dict[buffer], s[i] }); // добавл€ем пару в ответ
			dict[buffer + s[i]] = dict.size(); // добавл€ем слово в словарь
			buffer = ""; // сбрасываем буфер
		}
	}

	if (!buffer.empty()) // если буффер не пуст - этот код уже был, нужно его добавить в конец словар€
	{
		char last_ch = buffer[buffer.size() - 1]; // берем последний символ буффера, как "новый" символ

		buffer.erase(buffer.size() - 1, 1); // удал€ем последний символ из буфера
		ans.push_back({ dict[buffer], last_ch }); // добавл€ем пару в ответ 
	}
	return ans;
}

string decodeLZ78(list<Node> encoded)
{
	list<string> dict = list<string>();
	dict.push_back(""); // словарь, слово с номером 0 Ч пуста€ строка
	string ans = "";
	for (auto node : encoded)
	{
		auto it1 = std::next(dict.begin(), node.pos);
		
		//auto word = dict[node.pos] + node.next; 
		auto word = (*it1) + node.next; // составл€ем слово из уже известного из словар€ и новой буквы
		
		ans += word;  // приписываем к ответу
		dict.push_back(word); // добавл€ем в словарь
	}
	return ans;
}

void show_codes(string phrase, list<Node> enc, string dec)
{
	cout << " \n phrase for encode:" << phrase << "\n";
	cout << " \n encoded: \n";
	for (auto item : enc)
	{
		cout << item.pos << " " << item.next << "\n";
	}

	cout << " \n decoded: \n" << dec << "\n";
}

string enter_from_console()
{
	cout << "vvedite slovo \n";
	string entered = "";
	getline(cin, entered);
	return entered;
}



int main(int argc, char* argv[])
{
	// auto phrase = "abacababacabc"s;
	// auto phrase = "hello world!!!";
	auto phrase = enter_from_console();
	auto encoded = encodeLZ78(phrase);
	auto enc_corr = list<Node>();
	enc_corr.push_back({0,'a' });
	enc_corr.push_back({0,'b' });
	enc_corr.push_back({1,'c' });
	enc_corr.push_back({1,'b' });
	enc_corr.push_back({4,'a' });
	enc_corr.push_back({0,'c' });
	enc_corr.push_back({4,'c' });
	auto decoded = decodeLZ78(encoded);
	//auto decoded = decodeLZ78(enc_corr); //       abacababacabc .


	show_codes(phrase, encoded, decoded);

	system("pause");
	return 0;
}
