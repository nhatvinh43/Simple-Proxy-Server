#pragma once
typedef struct Request {
	char* host;
	char* uri;
} Request;
Request* parse_request(const char* ori);
void free_request(struct Request* rq);
