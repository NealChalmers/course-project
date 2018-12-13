#include <stdio.h>
#ifndef uu
#define uu

/*users*/

typedef struct users
{
	char username[30];								/*username*/
	char nickname[30];								/*nickname*/
	char password[30];								/*password*/
	char studentid[30];								/*studentID*/
	double changebalance;							/*balance*/
	int rpsend, rpreceive;							/*send/recevie number of redpacket*/
}USERS;


/*declaration*/

void sendrp(USERS *);
void receiverp(USERS *);
void inquiryb(USERS *);
void inquiryr(USERS *);
void newuser(int);

#endif

