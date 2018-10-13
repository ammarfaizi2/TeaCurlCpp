
#include <cstdio>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "TeaCurl.h"

int main(int argc, char *argv[]) {

	// Prevent defunct
	signal(SIGCHLD, SIG_IGN);

	for(int i = 0; i < 3; i++) {
		int pid = fork();
		if (pid == 0) {

			char process_name[32];
			sprintf(process_name, "child_%d --daemon --no-tty", i);
			memcpy(argv[0], process_name, sizeof(process_name));

			std::string url = "https://www.google.com";
			
			TeaCurl tch(url);
			tch.setOpt(CURLOPT_COOKIEJAR, "/tmp/cookie");
			tch.setOpt(CURLOPT_COOKIEFILE, "/tmp/cookie");
			tch.exec();

			if (tch.getRes() == CURLE_OK) {
				std::string body = tch.getBody();
				char filename[10];
				sprintf(filename, "out_%d.txt", i);
				FILE *h = fopen(filename, "w");
				const char *cstrBody = body.c_str();

				size_t length = strlen(cstrBody);
				fwrite(cstrBody, length, 1, h);
				printf("Wrote %ld bytes to %s\n", length, filename);
				fclose(h);
				printf("Child %d has finished its execution\n", i);
			} else {
				printf("An error occued: %s\n", tch.getError().c_str());
			}
			sleep(4);
			return 0;
		}	
	}

	wait(NULL);

	return 0;
}
