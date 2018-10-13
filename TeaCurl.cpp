#include "TeaCurl.h"

static size_t __teaCurlWriteFunc(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)contents, size*nmemb);
	return size*nmemb;
}

TeaCurl::TeaCurl(std::string _url) {
	url = _url;
	ch = curl_easy_init();
	setUp();
}

void TeaCurl::exec() {
	res = curl_easy_perform(ch);
	if(res == CURLE_OK) {
		curl_easy_getinfo(ch, CURLINFO_RESPONSE_CODE, &httpCode);
	} else {
		error = curl_easy_strerror(res);
	}
}

CURLcode TeaCurl::getRes() {
	return res;
}

std::string TeaCurl::getError() {
	return error;
}

std::string TeaCurl::getBody() {
	return out;
}

long TeaCurl::getHttpCode() {
	return httpCode;
}

void TeaCurl::setOpt(CURLoption opt, const void *val) {
	curl_easy_setopt(ch, opt, val);
}

void TeaCurl::setUp() {
	curl_easy_setopt(ch, CURLOPT_URL, url.c_str());
	curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(ch, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, __teaCurlWriteFunc);
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, &out);
}

void TeaCurl::cleanUp() {
	curl_easy_cleanup(ch);
}

TeaCurl::~TeaCurl() {
	cleanUp();
}
