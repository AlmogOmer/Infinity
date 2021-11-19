#include "uid.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void Test(void);

int main(void)
{
	Test();

	return 0;
}

static void Test(void)
{
	
	unique_id_t uid1 = uid_null_uid;
	unique_id_t uid2 = uid_null_uid;
	time_t now = time(NULL);
	pid_t thisProccess = getpid();
	
	if(!(UIDIsEqual(uid1, uid2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	uid1 = UIDGenerate();
	
	if(!(UIDIsEqual(uid1, uid2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid1.counter == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid1.timestamp == now))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid1.pid == thisProccess))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	sleep(3);

	uid2 = UIDGenerate();
	
	if(!(UIDIsEqual(uid1, uid2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid2.counter == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid2.timestamp == now+3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid2.pid == thisProccess))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid2.timestamp == uid1.timestamp +3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(uid2.pid == uid1.pid))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	
}
