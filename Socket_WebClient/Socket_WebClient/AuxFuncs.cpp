#include"stdafx.h"
#include "AuxFuncs.h"
#include <string>
#include <vector>
#include <fstream>
#include<sstream>
#define USERAGENT "HTMLGET 1.0"	
#define USERAGENT1 "HTMLGET 1.1"
using namespace std;
#pragma warning(disable:4996)
char* get_ip(char* host)
{
	struct hostent* hent;
	int iplen = 15; //XXX.XXX.XXX.XXX
	char* ip = (char*)malloc(iplen + 1);
	memset(ip, 0, iplen + 1);
	if ((hent = gethostbyname(host)) == NULL)
	{
		//perror("Can't get IP\n");
		return "";
	}
	if (inet_ntop(AF_INET, (void*)hent->h_addr_list[0], ip, iplen) == NULL)
	{
		//perror("Can't resolve host\n");
		return "";
	}
	return ip;
}
vector <string> Black_list(vector <string> black_data) // lấy danh sách các trang bị cấm
{
	ifstream outfile;
	outfile.open("blacklist.conf", ios::in);
	char temp[255];
	while (!outfile.eof())
	{
		outfile.getline(temp, 255);
		black_data.push_back(temp);
	}
	outfile.close();
	return black_data;
}

void Error(CSocket & Server) //gửi về lỗi trang web truy cập bị cấm
{
	const char* c = "HTTP/1.1 403 Forbidden\r\n\r\n<html>\r\n<title>403 Forbidden</title>\r\n<body>\r\n"
		"<h1>Error 403: Forbidden</h1>\r\n<p>This page is blocked by proxy server.</p>\r\n"
		"<p>Do you wanna access the website, Direct me <3</p>"
		"</body>\r\n</html>\r\n";
	Server.Send(c, strlen(c));
	Server.Close();
}

char* build_get_query(char* host, char* page)
{
	string hostString = host;
	string pageString = page;
	//Xoa phan www trong host
	int pos = hostString.find("www.");
	/*if (pos != string::npos)
	{
		pos += 4;
		hostString = hostString.substr(pos);
	}*/
	//Chi lay phan page tu dau /
	pos = pageString.find(hostString);
	if (pos != string::npos)
	{
		pos += hostString.length();
		pageString = pageString.substr(pos);
		memset(page, 0, sizeof(page));
	}
	/*if (pageString.length()>1)
	{
		pageString.erase(pageString.begin());
	}*/

	string queryString = "GET " + pageString + " " + "HTTP/1.0\r\nHost: " + hostString + "\r\nUser-Agent: " + USERAGENT + "\r\n\r\n";
	char* query = new char[queryString.length()];

	for (int i = 0; i < queryString.length(); i++)
	{
		query[i] = queryString.at(i);
	}
	//query[queryString.length()] = '\0';      // Lỗi
	return query;
}
