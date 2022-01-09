#include <stdlib.h>		
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dhcp.h"

static void Test(void);
static void PrintIP(ip_t ip);


int main(void)
{
	Test();

	return 1;
}

static void Test(void)
{
	char net_addr[] = "192.10.20.0";
	size_t i = 0;
	ip_t temp = 0;
    dhcp_t *dhcp = DHCPCreate(net_addr, 24);
	printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
	for(;i < 10; ++i)
	{
		printf("[%lu] ", i);
		PrintIP(DHCPAllocIP(dhcp));
		printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
		
	}
	
	temp = DHCPAllocIP(dhcp);
	printf("last allocation (temp): ");
			PrintIP(temp);

	printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
	for(i = 0;i < 3; ++i)
	{
		printf("[%lu] IP to be free: ", i);
		PrintIP(temp-i);
		DHCPFreeIP(dhcp, temp-i);
		printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
	}
    
	
	for(i = 0;i < 3; ++i)
	{
		printf("[%lu] IP allocated again: ", i);
		PrintIP(DHCPAllocIP(dhcp));
		printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
	}
	
	PrintIP(DHCPAllocIP(dhcp));
	printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
    DHCPDestroy(dhcp);

	puts("SUCCESS");

}

static void PrintIP(ip_t ip)
{
	printf("%u.%u.%u.%u\n", (unsigned char)(ip>>24), (unsigned char)(ip>>16), (unsigned char)(ip>>8), (unsigned char)ip);
}


