#ifndef FUNCTION_H
#define FUNCTION_H
#include<cstddef>
#include<map>
#include<string>
#include<set>
#include<iostream>

namespace oj
{
	struct String
	{
		std::string str;
		String(const std::string &);
		String(const String &);
		String& operator=(const String &);
	};

	std::ostream& operator<<(std::ostream &,const String &);

	void insert(std::map<int,String> &ma,int key,const std::string &str) {
        std::map<int,String>::iterator it = ma.find(key);
        std::string temp;
        if (it == ma.end())
            temp = str;
        else {
            temp = str + it->second.str;
            ma.erase(it);
        }
        ma.insert(std::pair<int,String>(key, String(temp)) );
    }
	void output(const std::map<int,String> &ma,int begin,int end) {
        for (auto &it:ma)
            if (it.first >= begin && it.first <= end)
                std::cout << it.second << ' ';
    }
    void erase(std::map<int,String> &ma,int begin,int end) {
        std::set<int> eraseKeys;
        for (auto &it : ma)
            if (it.first >= begin && it.first <= end)
                eraseKeys.insert(it.first);
        for (int key:eraseKeys)
            ma.erase(key);
    }
    std::ostream& operator<<(std::ostream &os,const std::map<int,String> &ma) {
        for (auto &it : ma)
            os << it.second << ' ';
        return os;
    }
}
#endif
