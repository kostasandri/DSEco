#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct notification {
	char message[500];
	char notification[50];
	char time[50];
	struct notification* next;
} note;

typedef struct people
{
	char firstName[50];
	char lastName[50];
	int birth;					//etos gennisis
	char gender;				//filo
	int id;						//tautotita
	char init_time[50];			//imerominia kai wra eggafis
	double original_amount;		//arxiko poso dwreas
	double final_amount;		//teliko poso dwreas
	struct notification notif;
	struct notification* headn; //deiktis pou mas deixnei sto head node tin eswteriki lista tipou notification struct
	struct people* next;
} person;

person* headp;

void swap(person* a, person* b);
int homeScreen(char* userType);
void donate();
void login();
void printAll();
void view(int username);
void notifications(int username);
void modify(int username);
char* getTime();	//epistrefei tin wra tou sistimatos
void adminView();
void search();
void delete();
void notify(int flag);
void ecogift();
void ecocheck();
void sort();

void main()
{

	char userType[50]; //usertype tha einai user i admin
	char username[50];
	char password[50];
	char action[50];

	int type = homeScreen(&userType);  // epistrefei 1 ean einai user, 2 ean einai admin me swsta credentials, 3 ean dwsei lathos stoixeia diaxeiristi

	while (1)
	{
		if (type == 1)
		{
			system("cls");
			printf("##################### User screen #####################\n");
			printf("Type <Donate> to donate or <Login> to login.\nType anything else to return to home screen.\n");
			scanf("%s", action);

			if (strcmp(action, "Login") == 0 || strcmp(action, "login") == 0)
			{
				login();
			}
			else if (strcmp(action, "Donate") == 0 || strcmp(action, "donate") == 0)
			{
				donate();
			}
			else
			{
				type = homeScreen(&userType);
				system("cls");
			}
		}
		else if (type == 2)
		{
			system("cls");
			printf("##################### Administrator screen #####################\n");
			printf("Type <View> to view users.\nType <Search> to search for a user.\nType <Delete> to delete a user.\nType <Notify> to send notification.\n");
			printf("Type <EcoGift> to raise the donation 10%.\nType <EcoCheck> to check if the total donation amount is more than 50.000.\nType <sort> for sorting the users.\n");
			printf("Type <Exit> to return to Home screen.\n");
			scanf("%s", action);

			if (strcmp(action, "View") == 0 || strcmp(action, "view") == 0)
			{
				adminView();
			}
			else if (strcmp(action, "Search") == 0 || strcmp(action, "search") == 0)
			{
				search();
			}
			else if (strcmp(action, "Delete") == 0 || strcmp(action, "delete") == 0)
			{
				delete();
			}
			else if (strcmp(action, "Notify") == 0 || strcmp(action, "notify") == 0)
			{
				notify(0);
			}
			else if (strcmp(action, "EcoGift") == 0 || strcmp(action, "ecogift") == 0)
			{
				ecogift();
			}
			else if (strcmp(action, "EcoCheck") == 0 || strcmp(action, "ecocheck") == 0)
			{
				ecocheck();
			}
			else if (strcmp(action, "Sort") == 0 || strcmp(action, "sort") == 0)
			{
				sort();
			}
			else if (strcmp(action, "Exit") == 0 || strcmp(action, "exit") == 0)
			{
				type = homeScreen(&userType);
			}
		}
		else
		{
			type = homeScreen(&userType);
		}
	}
}

int homeScreen(char* userType)
{
	system("cls");
	printf("##################### Home screen #####################\n");
	printf("To connect as an administrator type <Admin>.\nTo connect as a regular user type <User>.\nType anything else to exit.\n");
	scanf("%s", userType);
	if (!(strcmp(userType, "admin") == 0 || strcmp(userType, "Admin") == 0 || strcmp(userType, "User") == 0 || strcmp(userType, "user") == 0))
	{
		printf("Program exited.\n");
		person* tmp1 = headp;
		person* tmp2 = headp;
		struct notification* tmp3;

		while (tmp1 != NULL) //kanoume free tin eswteriki lista prwta
		{
			while (tmp1->headn != NULL)
			{
				tmp3 = tmp1->headn;
				tmp1->headn = tmp1->headn->next;
				free(tmp3);
			}
			tmp1 = tmp1->next;
		}

		while (headp != NULL)
		{
			tmp2 = headp;
			headp = headp->next;
			free(tmp2);
		}
		exit(0);
	}

	if (strcmp(userType, "user") == 0 || strcmp(userType, "User") == 0)
	{
		return 1;
	}
	else if (strcmp(userType, "Admin") == 0 || strcmp(userType, "admin") == 0)
	{
		while (1) {
			char username[20], password[20], answer[20];
			printf("Please, enter your username: ");
			scanf("%s", username);
			printf("Please, enter your password: ");
			scanf("%s", password);
			if (strcmp(username, "adad") == 0 && strcmp(password, "11a11") == 0)
			{
				return 2;
			}
			else
			{
				printf("Wrong admin credentials.\nTry again? Yes/No\n");
				scanf("%s", answer);
				if (!(strcmp(answer, "Yes") == 0 || strcmp(answer, "yes") == 0))
				{
					return 0;
				}
			}
		}
	}
}

void login()
{
	person* tmp = headp;
	int username, password;
	int rev = 0, remainder;
	char action[50];

	printf("Enter your username: ");
	scanf("%d", &username);
	printf("Enter your password: ");
	scanf("%d", &password);
	while (password != 0) {
		remainder = password % 10;
		rev = rev * 10 + remainder;
		password /= 10;
	}

	while (tmp != NULL)
	{
		if (tmp->id == username)
		{
			if (tmp->birth == rev)
			{
				while (action != 6) {
					system("cls");
					printf("You are succesfully log on!!\n");
					printf("Type <View> to view your personal information.\nType <Notifications> to check if there 're notification from the admin.\nType <Modify> to modify your personal information.\nPress <Exit> to go back at home screen.\n");
					scanf("%s", action);

					if (strcmp(action, "Exit") == 0 || strcmp(action, "exit") == 0)
					{
						return;
					}
					else if (strcmp(action, "View") == 0 || strcmp(action, "view") == 0)
					{
						view(username);
					}
					else if (strcmp(action, "Notifications") == 0 || strcmp(action, "notifications") == 0)
					{
						notifications(username);
					}
					else if (strcmp(action, "Modify") == 0 || strcmp(action, "modify") == 0)
					{
						modify(username);
					}
				}
			}
			else {
				printf("Wrong credentials or user doesn't exist.\n");
				printf("Press Any Key to return at user's screen.\n");
				getch();
			}
		}
		tmp = tmp->next;
	}


}

void donate()
{
	person* tmp1;
	char firstname[50];
	char lastname[50];
	char gender;
	int id;
	int year;
	double donation;

	tmp1 = (person*)malloc(sizeof(person));
	tmp1->headn = NULL;
	if (tmp1 == NULL)
	{
		printf("error");
		exit(0);
	}

	printf("Enter your firstname.\n");
	scanf("%s", firstname);
	strcpy(tmp1->firstName, firstname);

	printf("Enter your lastname.\n");
	scanf("%s", lastname);
	strcpy(tmp1->lastName, lastname);

	printf("Enter your gender.\n");
	scanf(" %c", &gender);
	tmp1->gender = gender;

	printf("Enter your birth year.\n");
	scanf("%d", &year);
	tmp1->birth = year;

	printf("Enter your ID.\n");
	scanf("%d", &id);
	tmp1->id = id;

	printf("Enter your donation amount.\n");
	scanf("%lf", &donation);
	tmp1->original_amount = donation;
	tmp1->final_amount = donation - (donation * 0.1);

	strcpy(tmp1->init_time, asctime(getTime()));

	if (headp == NULL)  //dimiourgei neous komvous sto struct mas
	{
		tmp1->next = NULL;
		headp = tmp1;
	}
	else
	{
		tmp1->next = headp;
		headp = tmp1;
	}

	printf("Donation completed succesfully!\n");
	printf("Press Any Key to Continue\n");
	getch();
}

void printAll()
{
	person* tmp = headp;
	int counter = 0;

	while (tmp != NULL)
	{
		counter++;
		tmp = tmp->next;
	}


	while (tmp != NULL)
	{
		printf("FN: %s\n", tmp->firstName);
		printf("LN: %s\n", tmp->lastName);
		printf("B: %d\n", tmp->birth);
		printf("G: %c\n", tmp->gender);
		printf("Original: %lf\n", tmp->original_amount);
		printf("Final: %lf\n", tmp->final_amount);
		printf("T: %s", tmp->init_time);
		printf("ID: %d\n", tmp->id);
		printf("\n");
		tmp = tmp->next;
	}

}

void notifications(int username)
{
	person* tmp1 = headp;
	note* tmp2;

	while (tmp1 != NULL)
	{
		if (tmp1->id == username)
		{
			printf("Messages from administrator.\n\n");
			tmp2 = tmp1->headn;
			while (tmp2 != NULL)
			{
				printf("Notifiacation type: %s\n", tmp2->notification);
				printf("Message: %s\n", tmp2->message);
				tmp2 = tmp2->next;
			}
		}
		tmp1 = tmp1->next;
	}
	printf("Press any key to continue.");
	getch();
}

void modify(int username)
{
	person* tmp = headp;
	int counter = 0;
	int option;

	while (tmp != NULL)
	{
		if (tmp->id == username) {
			printf("First name: %s\n", tmp->firstName);
			printf("Last name: %s\n", tmp->lastName);
			printf("Birthday: %d\n", tmp->birth);
			printf("Gender: %c\n", tmp->gender);
			printf("Original donation amount: %lf\n", tmp->original_amount);
			printf("Final donation amount: %lf\n", tmp->final_amount);
			printf("Timestamp of last change: %s", tmp->init_time);
			printf("ID: %d\n", tmp->id);
			printf("\n");

			printf("This is your current data. Please specify a number for which value want to change.\n");
			printf("1) First name\n");
			printf("2) Last name\n");
			printf("3) Gender\n");
			printf("4) Birth year\n");
			printf("5) ID\n");
			printf("6) Back\n");
			scanf("%d", &option);
			if (option == 1)
			{
				char fname[50];
				printf("Enter your First name.\n");
				scanf("%s", fname);
				strcpy(tmp->firstName, fname);
				strcpy(tmp->init_time, asctime(getTime()));
			}
			else if (option == 2)
			{
				char lname[50];
				printf("Enter your Last name.\n");
				scanf("%s", lname);
				strcpy(tmp->lastName, lname);
				strcpy(tmp->init_time, asctime(getTime()));
			}
			else if (option == 3)
			{
				char gender;
				printf("Enter your Gender M/F.\n");
				getch();
				scanf("%c", &gender);
				tmp->gender = gender;
				strcpy(tmp->init_time, asctime(getTime()));
			}
			else if (option == 4)
			{
				int year;
				printf("Enter your birthday year.\n");
				getch();
				scanf(" %d", &year);
				tmp->birth = year;
				strcpy(tmp->init_time, asctime(getTime()));
			}
			else if (option == 5)
			{
				int id;
				printf("Enter your ID.\n");
				getch();
				scanf("%d", &id);
				tmp->id = id;
				strcpy(tmp->init_time, asctime(getTime()));
			}
			else if (option == 6)
			{
				return;
			}
		}
		tmp = tmp->next;
	}
}

void view(int username)
{
	person* tmp = headp;

	while (tmp != NULL)
	{
		if (tmp->id == username) {
			printf("First name: %s\n", tmp->firstName);
			printf("Last name: %s\n", tmp->lastName);
			printf("Birthday: %d\n", tmp->birth);
			printf("Gender: %c\n", tmp->gender);
			printf("Original donation amount: %lf\n", tmp->original_amount);
			printf("Final donation amount: %lf\n", tmp->final_amount);
			printf("Timestamp of last change: %s", tmp->init_time);
			printf("ID: %d\n", tmp->id);
			printf("\n");
			printf("Press Any Key to Continue\n");
			getch();
		}
		tmp = tmp->next;
	}
}

char* getTime()
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return timeinfo;
}

void adminView()
{
	person* tmp = headp;
	int counter1 = 0;	//counter gia poso megalitero apo 50 eyrw
	int counter2 = 0;	//counter gia posotita andrwn
	int counter3 = 0;	//counter gia posotita ginaikwn

	while (tmp != NULL)
	{
		printf("First name: %s\n", tmp->firstName);
		printf("Last name: %s\n", tmp->lastName);
		printf("Birthday: %d\n", tmp->birth);
		printf("Gender: %c\n", tmp->gender);
		printf("ID:%d\n", tmp->id);
		printf("Original donation amount: %lf\n", tmp->original_amount);
		printf("Final donation amount: %lf\n", tmp->final_amount);
		printf("Timestamp of last change: %s\n", tmp->init_time);
		printf("\n");

		if (tmp->original_amount > 50)
		{
			counter1++;
		}
		if (tmp->gender == 'M')
		{
			counter2++;
		}
		else
		{
			counter3++;
		}
		tmp = tmp->next;
	}
	printf("Total users with donation up to 50 euro are: %d\n", counter1);
	printf("Total men are: %d\n", counter2);
	printf("Total women are: %d\n", counter3);
	printf("Press Any Key to Continue\n");
	getch();
}

void search()
{
	person* tmp = headp;
	char search;

	printf("Please enter a character.\n");
	scanf(" %c", &search);

	while (tmp != NULL)
	{
		if (search == tmp->lastName[0]) {
			printf("First name: %s\n", tmp->firstName);
			printf("Last name: %s\n", tmp->lastName);
			printf("Birthday: %d\n", tmp->birth);
			printf("Gender: %c\n", tmp->gender);
			printf("ID:%d\n", tmp->id);
			printf("Final donation amount: %lf\n", tmp->final_amount);
			printf("\n");
		}
		tmp = tmp->next;
	}

	printf("Press Any Key to Continue\n");
	getch();

}

void delete()
{
	char answer[50];
	char lastname[50];
	int flag = 0;

	printf("Please specify lastname of a user to delete.\n");
	scanf("%s", lastname);

	person* tmp = headp;

	while (tmp != NULL)
	{
		if (strcmp(tmp->lastName, lastname) == 0) {

			printf("Are you suer you want to delete user with lastname %s? Yes/No\n", lastname);
			scanf("%s", answer);
			if (strcmp(answer, "Yes") == 0 || (strcmp(answer, "yes") == 0))
			{
				flag = 1;
				strcpy(tmp->firstName, "-1");
				strcpy(tmp->lastName, "-1");
				tmp->birth = -1;
				tmp->gender = -1;
				tmp->id = -1;
				tmp->original_amount = -1;
				tmp->final_amount = -1;
				strcpy(tmp->init_time, "-1");
				printf("User deleted.\n");
			}
			else
			{
				return;
			}

			printf("Press Any Key to Continue\n");
			getch();
		}
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		printf("User doesn't exist.\n");
		printf("Press Any Key to Continue\n");
		getch();
	}
}

void notify(int flag)
{
	person* tmp1 = headp;
	note* tmp2;
	note* tmp3;
	char lastname[50];
	char notification[20];
	char message[50];

	if (flag == 1)						//ean tin kalesei i ecoCheck
	{
		while (tmp1 != NULL)
		{
			tmp2 = (note*)malloc(sizeof(note));
			if (tmp2 == NULL)
			{
				printf("error");
				exit(0);
			}

			strcpy(tmp2->notification, "OK");
			strcpy(tmp2->message, "THANK YOU");
			strcpy(tmp2->time, asctime(getTime()));

			if (tmp1->headn == NULL)
			{
				tmp2->next = NULL;
				tmp1->headn = tmp2;
			}
			else
			{
				tmp2->next = tmp1->headn;
				tmp1->headn = tmp2;
			}

			tmp1 = tmp1->next;
		}
	}
	else
	{
		printf("Please enter user's lastname.\n");
		scanf(" %s", lastname);

		while (tmp1 != NULL)
		{
			if (strcmp(lastname, tmp1->lastName) == 0) {
				flag = 1;
				printf("User found!\nPlease specify the type of notification.\n");
				scanf("%s", notification);
				if (strcmp(notification, "OK") == 0 || strcmp(notification, "PROB") == 0)
				{
					printf("Specify your message.\n");
					getchar();							//katharismos buffer gia na mi diavasei allagi grammis kai eisagei to keno <message>
					gets(message);

					tmp2 = (note*)malloc(sizeof(note));
					if (tmp2 == NULL)
					{
						printf("error");
						exit(0);
					}

					strcpy(tmp2->notification, notification);
					strcpy(tmp2->message, message);
					strcpy(tmp2->time, asctime(getTime()));

					if (tmp1->headn == NULL)
					{
						tmp2->next = NULL;
						tmp1->headn = tmp2;
					}
					else
					{
						tmp2->next = tmp1->headn;
						tmp1->headn = tmp2;
					}

					tmp3 = tmp1->headn;
					printf("Notification history.\n\n");
					while (tmp3 != NULL)
					{
						printf("Notification type: %s\n", tmp3->notification);
						printf("Message: %s\n", tmp3->message);
						printf("Messate timestamp: %s\n", tmp3->time);
						tmp3 = tmp3->next;
					}
				}
				else
				{
					printf("Wrong notification.\n");
				}
			}
			tmp1 = tmp1->next;
		}
		if (flag == 1)
		{
			printf("Press Any Key to Continue\n");
			getch();
		}

	}
	if (flag == 0)
	{
		printf("User not found.\n");
		printf("Press Any Key to Continue\n");
		getch();
	}


}

void ecogift()
{
	int number, sum = 0;
	person* tmp = headp;

	do {
		printf("Specify a number between 0-9.\n");
		scanf("%d", &number);
	} while (number < 0 && number > 9);

	while (tmp != NULL)
	{
		if (number == (tmp->id % 10)) {
			tmp->final_amount = tmp->final_amount + (tmp->final_amount * 0.1);
			sum++;
		}
		tmp = tmp->next;
	}

	printf("%d users found with ID ending to %d\n", sum, number);
	printf("Press Any Key to Continue.\n");
	getch();

}

void ecocheck()
{
	int sum = 0;
	person* tmp = headp;

	while (tmp != NULL)
	{
		sum = sum + tmp->final_amount;
		tmp = tmp->next;
	}

	if (sum > 50000)
	{
		tmp = headp;
		printf("Total donation is up to 50000!!\n");
		notify(1);
	}
	printf("Press Any Key to continue.\n");
	getch();
}

void sort()
{
	int swapped, i;
	person* ptr1, * ptr2;
	person* lptr = NULL;

	do
	{
		swapped = 0;
		ptr1 = headp;

		while (ptr1->next != lptr)
		{
			if (ptr1->final_amount < ptr1->next->final_amount)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	ptr2 = headp;
	while (ptr2 != NULL)
	{
		printf("First name: %s\n", ptr2->firstName);
		printf("Last name: %s\n", ptr2->lastName);
		printf("Birthday: %d\n", ptr2->birth);
		printf("Gender: %c\n", ptr2->gender);
		printf("ID: %d\n", ptr2->id);
		printf("Final donation amount: %lf\n", ptr2->final_amount);
		printf("\n");
		ptr2 = ptr2->next;
	}

	printf("Press any key to continue.");
	getch();

}

void swap(person* a, person* b)
{
	char tempS[50];
	char gender;
	int temp;

	temp = a->final_amount;				//swap final amount
	a->final_amount = b->final_amount;
	b->final_amount = temp;

	strcpy(tempS, a->firstName);		//swap firstName
	strcpy(a->firstName, b->firstName);
	strcpy(b->firstName, tempS);

	strcpy(tempS, a->lastName);			//swap lastName
	strcpy(a->lastName, b->lastName);
	strcpy(b->lastName, tempS);

	temp = a->birth;					//swap birth
	a->birth = b->birth;
	b->birth = temp;

	gender = a->gender;						//swap gender
	a->gender = b->gender;
	b->gender = gender;

	temp = a->original_amount;				//swap original amount
	a->original_amount = b->original_amount;
	b->original_amount = temp;

	strcpy(tempS, a->init_time);			//swap init_time
	strcpy(a->init_time, b->init_time);
	strcpy(b->init_time, tempS);

	temp = a->id;							//swap ID
	a->id = b->id;
	b->id = temp;
}
