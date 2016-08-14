//RECEIVER UDP MULTICAST

#define GROUP "239.137.194.111"
#define PORT 55501

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

	struct sockaddr_in my_addr, sender_addr;
	struct ip_mreq m;
		
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock<0){
		printf("Error in socket()\n");
		exit(1);
	}
	
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr));
	if (ret<0){
		printf("Error in bind()\n");
		exit(1);
	}

	inet_aton(GROUP, &m.imr_multiaddr);
	m.imr_interface.s_addr = INADDR_ANY;
	
	ret = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &m, sizeof(m));
	if (ret<0){
		printf("Error in setsockopt()\n");
		exit(1);
	}
	
	bzero(&sender_addr, sizeof(sender_addr));
	buf = malloc(100);
	socklen_t size = sizeof(sender_addr);

	printf("\nWaiting for a message...\n");

        ret = recvfrom(sock, buf, 5, 0, (struct sockaddr*)&sender_addr, &size);
        if (ret<0) {
       		printf("Error in recvfrom()\n");
		exit(1);
        }
        printf("Message received: %s\n\n", buf);
	
	return 0;	
}
