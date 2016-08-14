//SENDER UDP MULTICAST

#define GROUP "239.137.194.111"
#define PORT 55501
#define BUF_LEN 100

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int sock;	//socket descriptor
	int ret;
	char* buf;
	
	struct sockaddr_in receiver_addr;
	
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock<0){
		printf("Error in socket()\n");
		exit(1);
	}
	
	bzero(&receiver_addr, sizeof(receiver_addr));
	receiver_addr.sin_family = AF_INET;
	receiver_addr.sin_port = htons(PORT);
	inet_aton(GROUP, &receiver_addr.sin_addr);
	
	buf = malloc(BUF_LEN);
	printf("\nInsert the message to send:\t");
	scanf("%s", buf);
	
	ret = sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&receiver_addr, sizeof(receiver_addr));
    	if (ret<0) {
        	printf("Error in sendto()\n");
		exit(1);
	}

	printf("Message sent: \"%s\"\n\n", buf);

	return 0;	
}
