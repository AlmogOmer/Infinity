#include <stdlib.h>		/* for malloc 	  */
#include <string.h>		/* for strtok	  */
#include <assert.h>		/* for assertions */
#include "dhcp.h"

#define POWER2(exp) (((size_t) 0x1) << (exp))		/* 2 ^ exp */
typedef struct dhcp_node dhcp_node_t;

struct dhcp_node
{
    dhcp_node_t *parent;
	dhcp_node_t *child_right;
    dhcp_node_t *child_left;
    int is_full;
};

struct dhcp
{
    dhcp_node_t *root;
    ip_t net_addr;
	ip_t broadcast_addr;
	ip_t server_addr;
    unsigned int net_mask;
};

static ip_t StringToIP(char *ip);
static dhcp_node_t *CreateNode(dhcp_node_t *parent);
static void DestroyRec(dhcp_node_t *root);
static void UpdateFull(dhcp_node_t *node);
static void FreeRec(dhcp_node_t *node, int height, ip_t ip_add);
static ip_t AllocRec(dhcp_node_t *node, int height);
static void ReserveIPs(dhcp_t *dhcp, ip_t ip);
static void CountRec(dhcp_node_t *node, size_t *count, int height);

/* complexity- O(net_mask) */
dhcp_t *DHCPCreate(char *net_addr, unsigned int net_mask)
{
	dhcp_t *dhcp = (dhcp_t *) malloc(sizeof(dhcp_t));
	if (!dhcp)
	{
		return NULL;
	}
	dhcp->root = (dhcp_node_t*)malloc(sizeof(dhcp_node_t));
    if(!dhcp->root)
    {
        free(dhcp);
        return NULL;
    }
    dhcp->root->parent = NULL;
    dhcp->root->child_left = NULL;
    dhcp->root->child_right = NULL;
    dhcp->root->is_full = 0;

	dhcp->net_addr = StringToIP(net_addr);
	dhcp->net_mask = net_mask;
	dhcp->broadcast_addr = (dhcp->net_addr | (0xFFFFFFFF>>dhcp->net_mask));
	dhcp->server_addr = dhcp->broadcast_addr - 1;
	
	ReserveIPs(dhcp, dhcp->net_addr);
	ReserveIPs(dhcp, dhcp->broadcast_addr);
	ReserveIPs(dhcp, dhcp->server_addr);
	
	return dhcp;
}

static dhcp_node_t *CreateNode(dhcp_node_t *parent)
{
	dhcp_node_t *node = (dhcp_node_t *) malloc(sizeof(dhcp_node_t));
	if (!node)
	{
		return NULL;
	}

    node->child_right= NULL;
    node->child_left = NULL;
	node->parent = parent;
    node->is_full = 0;

	return node;
}


void DHCPDestroy(dhcp_t *dhcp)
{
	assert(dhcp);

	DestroyRec(dhcp->root);
	dhcp->root = NULL;
	free(dhcp);
}

static void DestroyRec(dhcp_node_t *root)
{
	if (NULL == root)
	{
		return;
	}
	DestroyRec(root->child_left);
	root->child_left = NULL;
	DestroyRec(root->child_right);
	root->child_right = NULL;
	free(root);
}


static ip_t StringToIP(char *ip)
{
    char *token = NULL;
    size_t i = 3;
    const char s[2] = ".";
    ip_t num = 0;

    token = strtok(ip, s);

    while(token != NULL)
    {
        num |= atoi(token)<<(i*8);
        token = strtok(NULL, s);
        --i;
    }

    return num;
}

ip_t DHCPAllocIP(dhcp_t *dhcp)
{
	int height; 
	assert(dhcp);
	
	height = 32 - dhcp->net_mask;

	if (dhcp->root->is_full)
	{	
		return 0;
	}

	return dhcp->net_addr | AllocRec(dhcp->root,height);
	
}


static ip_t AllocRec(dhcp_node_t *node, int height)
{
	ip_t ip = 0;

	if (0 == height)
	{	/* found an empty leaf */
		node->is_full = 1;
		return 0;
	}

	if (!node->child_left)
	{	/* create child if not allocated already */
		node->child_left= CreateNode(node);
	}

	if (!node->child_left->is_full)
	{
		ip |= AllocRec(node->child_left, height - 1);
		UpdateFull(node);
		return ip;
	}
	
	if(!node->child_right)
	{
		node->child_right = CreateNode(node);
	}

	if(!node->child_right->is_full)
	{
		ip |= AllocRec(node->child_right, height - 1) | (1<<(height-1));  
		UpdateFull(node);
		return ip;

	}
	
	return ip;
	
}


static void UpdateFull(dhcp_node_t *node)
{
	if(node->child_left && node->child_left->is_full)
	{
		if (node->child_right && node->child_right->is_full)
		{
			node->is_full = 1;
		}
	}
	
}

void DHCPFreeIP(dhcp_t *dhcp, ip_t ip_add)
{
	int height; 
	assert(dhcp);
	
	height = 32 - dhcp->net_mask;

	if (ip_add == dhcp->net_addr ||
	ip_add == dhcp->broadcast_addr ||
	ip_add == dhcp->server_addr)
	{	/* reserved ip's */
		return;
	}

	FreeRec(dhcp->root, height, ip_add);
}


static void FreeRec(dhcp_node_t *node, int height, ip_t ip_add)
{

	if (0 == height)
	{
		node->is_full = 0;
		return;
	}
	
	if (ip_add>>(height - 1) & 1)
	{
		node->is_full = 0;
		FreeRec(node->child_right, height - 1, ip_add);
	}
	else 
	{
		node->is_full = 0;
		FreeRec(node->child_left, height - 1, ip_add);
	}
	
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	int height; 
	size_t max_num_of_ip;
	assert(dhcp);
	
	height = 32 - dhcp->net_mask;
	max_num_of_ip = POWER2(height);
	
	if (dhcp->root->is_full)
	{	
		return 0;
	}
	
	CountRec(dhcp->root, &max_num_of_ip, height);
	
	return max_num_of_ip;

}

static void CountRec(dhcp_node_t *node, size_t *count, int height)
{

	if (node->is_full || (height == 0 && node->is_full))
	{	
		*count -= POWER2(height);
		return;
	}

	if(node->child_left)
	{
		CountRec(node->child_left, count, height - 1);
	}
	
	if(node->child_right)
	{
		CountRec(node->child_right, count, height - 1);
	}

}


static void ReserveIPs(dhcp_t *dhcp, ip_t ip)
{
    dhcp_node_t *node = dhcp->root;
    size_t height = 32 - dhcp->net_mask;;
    
    for (;height>0; --height)
    {
        if (ip>>(height - 1) & 1)
		{
			if (!node->child_right)
			{
				node->child_right = CreateNode(node);
				if (!node->child_right)
				{
					return;
				}
			}
			node = node->child_right;

		}
		else
		{
			if (!node->child_left)
			{
				node->child_left = CreateNode(node);
				if (!node->child_left)
				{
					return;
				}
			}
			node = node->child_left;
		}
		
    }

	node->child_left = NULL;
	node->child_right = NULL;
	node->is_full = 1;
	UpdateFull(node->parent);

}

 
