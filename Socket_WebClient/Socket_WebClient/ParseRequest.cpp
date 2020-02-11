#include"stdafx.h"
#include"ParseRequest.h"
#include<stdlib.h>
#include<string>
Request* parse_request(const char* ori)
{
	Request* rq = NULL;
	rq = (Request*)malloc(sizeof(Request));
	if (!rq)
	{
		return NULL;
	}

	// METHOD
	size_t len = strcspn(ori, " ");
	ori = ori + (len + 1);

	// Request-URI
	size_t uri_len = strcspn(ori, " ");
	rq->uri = (char*)malloc(uri_len + 1);
	if (!rq->uri)
	{
		free_request(rq);
		return NULL;
	}
	memcpy(rq->uri, ori, uri_len);
	rq->uri[uri_len] = '\0';
	ori = ori + (uri_len + 1);

	// HTTP-Version, dong thoi ket dong Request line
	size_t ver_len = strcspn(ori, "\r\n");
	char* temp = (char*)malloc(ver_len + 1);
	memcpy(temp, ori, ver_len);
	ori = ori + (ver_len + 2);

	// HEADER , HOST
	while (ori[0] != 'H')
	{
		size_t temp_len = strcspn(ori, "\r\n");
		ori = ori + (temp_len + 1);
	}
	size_t host_len = strcspn(ori, ":");
	ori = ori + (host_len + 1);
	while (*ori == ' ')
	{
		ori++;
	}
	size_t value_len = strcspn(ori, "\r\n");
	rq->host = (char*)malloc(value_len + 1);
	if (!rq->host)
	{
		free_request(rq);
		return NULL;
	}
	memcpy(rq->host, ori, value_len);
	rq->host[value_len] = '\0';
	return rq;
}

void free_request(struct Request* req)
{
	free(req->uri);
	free(req->host);
	free(req);
}
