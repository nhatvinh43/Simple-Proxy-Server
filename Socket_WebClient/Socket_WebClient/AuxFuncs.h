#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "afxsock.h"
#include <fstream>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
using namespace std;
char* get_ip(char* host);
char* build_get_query(char* host, char* page);
vector <string> Black_list(vector <string> black_data);
void Error(CSocket& Server);
char* build_get_query(char* host, char* page);
