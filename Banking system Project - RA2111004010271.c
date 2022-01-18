#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkbalance(char*);
void transfer(void);
void display(char*);
void person(char*);
void login(void);
void account(void);
void logout(void);

struct pass {
	int date, month, year;
	char username[50];
	char phonenumber[15];
	char firstname[20];
	char lastname[20];
	char fathname[20];
	char mothname[20];
	char address[50];
};

struct money {
	char usernameto[50];
	char userpersonfrom[50];
	long int money1;
};

struct userpass {
	char password[50];
};

int main()
{
	int i, a, b, choice;
	printf("WELCOME TO INDIAN BANK\n");
	printf("1.Create Account\n");
	printf("2.Sign In\n");
	printf("3.Exit\n");
	printf("Enter Your Choice = ");
	scanf("%d", &choice);
	printf("\n---------------------------------------------------------\n");
	switch (choice)
	{
	case 1:
		account();
		break;

	case 2:
		login();
		break;

	case 3:
		exit(0);
		break;
		getch();
	}
}

void account(void)
{
	char password[20];
	int i;
	char ch;
	FILE *fp, *fu;
	struct pass u1;
	struct userpass p1;
	struct userpass u2;
	fp = fopen("username.txt", "ab");
	printf("\nCreate Account -");
	printf("\nEnter Firstname = ");
	scanf("%s", &u1.firstname);
	printf("Enter Lastname = ");
	scanf("%s", &u1.lastname);
	printf("Enter Father's Name = ");
	scanf("%s", &u1.fathname);
	printf("Enter Mother's Name = ");
	scanf("%s", &u1.mothname);
	printf("Enter Address = ");
	scanf("%s", &u1.address);
	printf("Enter Date Of Birth (in numbers only) -\n");
	printf("Date = ");
	scanf("%d", &u1.date);
	printf("Month = ");
	scanf("%d", &u1.month);
	printf("Year = ");
	scanf("%d", &u1.year);
	printf("Phone Number = ");
	scanf("%s", u1.phonenumber);
	printf("Enter Username = ");
	scanf("%s", &u1.username);
	printf("Enter Password = ");
	for (i = 0; i < 50; i++)
	{
		ch = getch();
		if (ch != 13)
		{
			password[i] = ch;
			ch = '*';
			printf("%c", ch);
		}
		else
			break;
	}
	fwrite(&u1,sizeof(u1),1,fp);
	fclose(fp);
	printf("\nAccount Created Successfully.");
	printf("\nPress enter to login");
	getch();
	printf("\n---------------------------------------------------------\n");
	login();
}

void login(void)
{
	char username[50];
	char password[50];
	int i, j, k;
	char ch;
	FILE *fp, *fu;
	struct pass u1;
	struct userpass u2;
	fp = fopen("username.txt","rb");
	if (fp == NULL)
	{
		printf("\nAccount Error\n");
	}
	else
	{
		printf("\nAccount Login -");
		printf("\nEnter Username =");
		scanf("%s", &username);
		printf("Enter Password =");
		for (i = 0; i < 50; i++)
		{
			ch = getch();
			if (ch != 13)
			{
				password[i] = ch;
				ch = '*';
				printf("%c", ch);
			}
			else
				break;
		}
		printf("\n---------------------------------------------------------\n");
		while (fread(&u1,sizeof(u1),1,fp))
		{
			if (strcmp(username,u1.username)== 0)
			{
				display(username);
			}
		}
	}
	fclose(fp);
}

void display(char username1[])
{
	FILE* fp;
	int choice, i;
	fp = fopen("username.txt", "rb");
	struct pass u1;
	if (fp == NULL)
	{
		printf("\nFile Error\n");
	}
	while (fread(&u1,sizeof(u1),1,fp))
	{
		if (strcmp(username1,u1.username) == 0)
		{
			printf("\nYour Account Information -");
			printf("\nName = %s %s",u1.firstname,u1.lastname);
			printf("\nFather's Name = %s %s",u1.fathname,u1.lastname);
			printf("\nMother's Name = %s",u1.mothname);
			printf("\nPhone Number = %s",u1.phonenumber);
			printf("\nDate of Birth = %d-%d-%d",u1.date, u1.month, u1.year);
			printf("\nAddress = %s", u1.address);
			printf("\n---------------------------------------------------------\n");
		}
	}
	fclose(fp);
	printf("\nHome Page -");
	printf("\n1. Check Balance.");
	printf("\n2. Deposit and Transfer Money.");
	printf("\n3. Log Out.");
	printf("\n4. Exit.");
	printf("\nEnter your choice =");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		checkbalance(username1);
		break;

	case 2:
		transfer();
		break;

	case 3:
		logout();
		login();
		break;

	case 4:
		exit(0);
		break;
	}
}

void transfer(void)
{
	int i;
	FILE *fm, *fp;
	struct pass u1;
	struct money m1;
	char usernamefrom[20];
	char usernameto[20];
	fp = fopen("username.txt", "rb");
	fm = fopen("mon.txt", "ab");
	printf("\n---------------------------------------------------------\n");
	printf("\nTransfer and Deposit Money page-");
	printf("\n1. Deposit Money.");
	printf("\n2. Transfer Money.");
	printf("\nEnter your choice = ");
	scanf("%d", &i);
	if (i==2)
	{
		printf("\nFrom (your username) = ");
		scanf("%s", &usernamefrom);
		printf("\nTo (username of recipent) = ");
		scanf("%s", &usernameto);
		while (fread(&u1,sizeof(u1),1,fp))
		{
			if (strcmp(usernameto,u1.username)	== 0)
			{
				strcpy(m1.usernameto,u1.username);
				strcpy(m1.userpersonfrom,usernamefrom);
			}
		}
		printf("\nEnter Amount to be transferred = ");
		scanf("%d", &m1.money1);
		fwrite(&m1,sizeof(m1),1,fm);
		printf("\nAmount Transferred Successfully.");
		printf("\nPress any key to continue.");
		getch();
		printf("\n---------------------------------------------------------\n");
	}
	else if (i==1)
	{
		printf("\nEnter amount to be deposited = ");
		scanf("%d",&m1.money1);
		fwrite(&m1,sizeof(m1),1,fm);
		printf("\nAmount Deposited Successfully.");
		printf("\nPress any key to continue.");
		getch();
		printf("\n---------------------------------------------------------\n");
	}
	fclose(fp);
	fclose(fm);
	display(usernamefrom);
}

void checkbalance(char username2[])
{
	FILE* fm;
	struct money m1;
	char ch;
	int i=1, sum=0;
	fm = fopen("mon.txt", "rb");
	printf("\nAccount Balance Information -");
	while (fread(&m1,sizeof(m1),1, fm))
	{
		if (strcmp(username2,m1.usernameto) == 0)
		{
			printf("\nTransaction Number = ");
			printf("%d", i);
			i++;
			printf("\nAmount = ");
			printf("%d", m1.money1);
			sum = sum + m1.money1;
		}
	}
	printf("\nTotal Amount = ");
	printf("%d", sum);
	getch();
	printf("\n---------------------------------------------------------\n");
	fclose(fm);
	display(username2);
}

void logout(void)
{
	printf("\nLogged out successfully.");
	printf("\nPress any key to continue.");
	getch();
	printf("\n---------------------------------------------------------\n");
}
