#include "uid.h"
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

static size_t u_counter = 0;


/* aka BADUID */
const unique_id_t uid_null_uid; 

/* generate a unique identifier */ 
unique_id_t UIDGenerate(void)
{

	unique_id_t new_uid = {0};
	
	
	new_uid.counter = ++u_counter;
	new_uid.pid = getpid();
	new_uid.timestamp = time(NULL);
	
	if (NULL == &new_uid.timestamp)
	{
		return uid_null_uid;
	}
	
	return new_uid;
}



/* check two UIDs for equality */
bool_t UIDIsEqual(unique_id_t uid1, unique_id_t uid2)
{
	
	return	((uid1.counter == uid2.counter) && (uid1.pid == uid2.pid) &&
			(uid1.timestamp == uid2.timestamp));


} 


