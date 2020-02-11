#pragma once
#include "stdafx.h"
#include <unordered_map>
#include"AuxFuncs.h"
#include"ParseRequest.h"
using namespace std;
struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2> &p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);

		// Mainly for demonstration purposes, i.e. works but is overly simple
		// In the real world, use sth. like boost.hash_combine
		return h1 ^ h2;
	}
};
typedef unordered_map<pair<string, string>, vector<char>, pair_hash> cachemap;
cachemap caches;
vector<char> validate_cache(Request &request, cachemap& caches);
bool findCache(pair <string, string> str);// tìm trong cache
vector<char> getCache(pair <string, string> str, cachemap caches); // lấy reponse trong cache
void update_cache(Request &request, vector<char> reponse, cachemap& caches); // hàm thêm vào cache

vector<char> validate_cache(Request &request, cachemap& caches) //kiểm tra rồi trả về reponse nếu đã có trong cache
{
	//  Find Cache
	vector<char> ch;
	pair<string, string> str;
	str.first = request.host;
	str.second = request.uri;

	if (findCache(str) == true)
	{
		return getCache(str, caches);
	}
	else
	{
		return ch;
	}
}

bool findCache(pair <string, string> str) // tìm trong cache
{
	auto iter = caches.find(str);
	return iter == caches.end() ? false : true;

	if (iter == caches.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

vector<char> getCache(pair <string, string> str, cachemap caches) // lấy reponse trong cache
{
	std::unordered_map<pair<string, string>, vector<char>>::iterator iter = caches.find(str);
	return iter->second;
}

void update_cache(Request &request, vector<char> reponse, cachemap& caches) // hàm thêm vào cache
{
	pair<string, string> str;
	str.first = request.host;
	str.second = request.uri;
	if (findCache(str) == true)
	{
		return;
	}
	else
	{
		pair <pair<string, string>, vector<char>> newrep(str, reponse);
		caches.insert(newrep);
	}
}


