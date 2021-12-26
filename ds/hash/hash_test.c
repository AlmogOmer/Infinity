#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "hash_table.h"
#include "doubly_linked_list.h"

#define UNUSED(x) (void)(x)


static void Test();
static void Test1(void);
size_t StringHash(const void *data, const void *param);
static int Strcmp(const void *data1, const void *data2, const void *param);
static int Print(const void *data, const void *param);
static int FreeStr(const void *data, const void *param);

int main()
{
    Test();
	Test1();
	return 0;
}

static void Test()
{
    hash_t *hash = NULL;
	size_t size = 10;

	char *s1 = NULL;
	char *s2 = NULL;
	char *s3 = NULL;
    
    hash = HashCreate(StringHash, Strcmp, size, NULL);

	if (!(HashSize(hash) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (0 == HashIsEmpty(hash))
	{
		printf("fail in %d\n", __LINE__);
	}

	s1 = (char *)malloc(20);
	if (!s1)
	{
		return;
	}
	strcpy(s1, "almog");
	HashInsert(hash, s1);

	s2 = (char *)malloc(20);
	if (!s2)
	{
		return;
	}
	strcpy(s2, "gomla");
	HashInsert(hash, s2);

	s3 = (char *)malloc(20);
	if (!s3)
	{
		return;
	}
	strcpy(s3, "omer");
	HashInsert(hash, s3);

	if (!(3 == HashSize(hash)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashIsEmpty(hash))
	{
		printf("fail in %d\n", __LINE__);
	}

	printf("*****Before removing*****\n");
	HashForEach(hash, Print, NULL);

	
	if (HashFind(hash, "aaaa"))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!HashFind(hash, "almog"))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(HashFind(hash, "almog"), "almog") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!HashFind(hash, "gomla"))
	{
		printf("fail in %d\n", __LINE__);
	}

	HashRemove(hash, s1);

	if (!(2 == HashSize(hash)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashFind(hash, "almog"))
	{
		printf("fail in %d\n", __LINE__);
	}

	HashRemove(hash, s3);

	if (!(1 == HashSize(hash)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashIsEmpty(hash))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	printf("*****After removing*****\n");
	HashForEach(hash, Print, NULL);

	free(s1);
	free(s2);
	free(s3);


    HashDestroy(hash);
}

static void Test1(void)
{
    size_t size = 100;
	char line[25] = {0};
    hash_t *dict_hash = HashCreate(StringHash, Strcmp, size, NULL);
    FILE *dict_file = fopen("/usr/share/dict/words", "r");
    if (!dict_hash)
    {
        puts("no dict hash");
        return;
    }
    if (!dict_file)
    {
        puts("no dict found");
        return;
    }

    while (fgets(line, 100, dict_file))
    {
        char *str = (char *) malloc(strlen(line));
        if (!str)
        {
            puts("string fail");
            return;
        }
		line[strlen(line) - 1] = '\0'; /*for removing the "/n"*/
        strcpy(str, line);
        assert(0 == HashInsert(dict_hash, str));
    }

	printf("pleas enter your word: ");
	scanf("%s", line);

	if (NULL == HashFind(dict_hash, line))
	{
		printf("no such word %s\n", line);
	}
	else
	{
		printf("word in dic: %s\n", line);
	}

	HashForEach(dict_hash, FreeStr, NULL);

    HashDestroy(dict_hash);
    fclose(dict_file);
    puts("SUCCESS");
}

size_t StringHash(const void *data, const void *param)
{
    char *str = (char *) data;
    size_t hash = 0;
    UNUSED(param);

    while (*str)
    {
        hash += *str;
        ++str;
    }

    return hash;
}


static int Strcmp(const void *data1, const void *data2, const void *param)
{
    UNUSED(param);
    return (0 == strcmp(data1, data2));
}


static int Print(const void *data, const void *param)
{
	UNUSED(param);

	printf("%s\n", (char *) data);

	return 1;
}

static int FreeStr(const void *data, const void *param)
{
    free((void*)data);
    UNUSED(param);
    return 1;
}



