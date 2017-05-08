#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

string get_suffix(string word,int n)
{
	return word.substr(word.length() - n , n);
}


int cmp1(const pair<string, int>& x, const pair<string, int>& y)
{
	if (x.second == y.second)
		return x.first > y.first;
	else
		return x.second > y.second;
}

int cmp2(const string& x, const string& y)
{
	return x > y;
}

void sortMapByValue(map<string, int>& tMap, vector<pair<string, int> >& tVector)
{
	for (map<string, int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));

	sort(tVector.begin(), tVector.end(), cmp1);
}

int main()
{
	int n, count=0;
	string tmp, str;
	map<string, int> dic;
	vector<pair<string, int> > map_vect;
	vector<string> suffix_vect;
	ifstream in("dict.txt");
	ifstream in2("dict.txt");
	cout << "input the number of letters of suffix:";
	cin >> n;
	while (!in.eof())
	{
		getline(in, tmp);
		if (tmp.length() >= n)
		{
			if (!dic.count(get_suffix(tmp, n)))
				dic.insert(map<string, int>::value_type(get_suffix(tmp, n), 1));
			else
				dic[get_suffix(tmp, n)]++;
		}
	}
	sortMapByValue(dic,map_vect);
	if (map_vect.size() < 10)
		for (int i = 0;i < map_vect.size();i++)
			cout << map_vect[i].first << ": " << map_vect[i].second << endl;
	else
		for (int i = 0;i < 10;i++)
			cout << map_vect[i].first << ": " << map_vect[i].second << endl;



	cout << "input the suffix:";
	cin >> str;
	while (!in2.eof())
	{
		getline(in2, tmp);
		if (tmp.length() >= str.length() && get_suffix(tmp, str.length()) == str)
		{
			suffix_vect.push_back(tmp);
			count++;
		}
	}

	cout << "number of words:" << count << endl;

	sort(suffix_vect.begin(),suffix_vect.end(),cmp2);
	for (int i = 0;i < suffix_vect.size();i++)
		cout << suffix_vect[i] << endl;

	system("pause");
}