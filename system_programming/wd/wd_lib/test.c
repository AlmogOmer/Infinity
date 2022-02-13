
const char *inet_ntop (const void *addrptr);

int main()
{
    const char *addrptr1 = {192,12,0,0}; 
    const char *addrptr2 = {192,13,0,0};
    
    printf("%s, %s",inet_ntop (addrptr1),inet_ntop (addrptr2) );

    return 0;
}


const char *inet_ntop (const void *addrptr)
{
  unsigned char *p = (unsigned char *) addrptr;
  
  char temp[INET_ADDRSTRLEN];

  snprintf(temp, sizeof(char)*INET_ADDRSTRLEN, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

  return temp;

}




