
#ifndef __TEA_CURL_H
#define __TEA_CURL_H

#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <curl/curl.h>

class TeaCurl
{
public:
	TeaCurl(std::string url);
	void exec();
	std::string getBody();
	std::string getError();
	CURLcode getInfo(CURLINFO infoOpt, void *ptr);
	long getHttpCode();
	CURLcode getRes();
	void setOpt(CURLoption opt, const void *val);
	~TeaCurl();
protected:
private:
	CURL *ch;
	CURLcode res;
	long httpCode;
	long responseHeaderSize;
	char *responseHeader;
	std::string out;
	std::string url;
	std::string error;

	void setUp();
	void cleanUp();
};

#endif
