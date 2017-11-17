/*
Sean McGuire,	G00330886.

*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

// define struct
struct node
{
	int IRFU;
	char firstName[20];
	char secondName[20];
	int age;
	float height;
	float weight;
	char club[20];
	char email[30];
	char pos[10];
	int tacklesMissed;
	int meters;
	struct node* NEXT;
};

void menu();

void parseChoice(int choice);

void addPlayer();

int search(struct node* headptr, char newIRFU[]);

void addPlayerToList(struct node* headptr, char newIRFU[]);

void main()
{
	// Initialize all local variables.
	char buffer[256] = { 0 };
	char username[6];
	char password[6];
	char c;
	char line[1000];
	int pos = 0;
	int found = 0;
	int lineNumber = 1;
	int choice = 0;
	// Declare and open the files used.
	FILE * fp;
	fp = fopen("users.txt", "r");

	// Firstly, ask the user for their username, if it's valid, it will ask for their password.
	printf("Enter username: ");
	scanf("%s", username);

	// Enter this while loop for every line the file has,
	// The file contains a list of usernames followed by their passwords directly after.
	while (fgets(line, sizeof(line), fp)) 
	{
		lineNumber++;
		// Each line ends with an end of line \n, so using strtok removes it, allowing strcmp to compare the strings 
		strtok(line, "\n");
		// Check if the username entered is equal to the current lines string,
		// And make sure the line number is divisible by 2 as the usernames  in the file are always followed by the password.
		if (strcmp(username, line) == 0 && lineNumber%2 == 0)
		{
			// If a username is found, call fgets to move to the next line, call strtok again, and assign the password to the current line.
			fgets(line, sizeof(line), fp);
			strtok(line, "\n");
			strcpy(password, line);
			// Then print that it was found, and break the while loop.
			printf("\nUsername found, Please Enter password: ");
			found += 1;
		}
	}

	if (found == 0)
	{
		printf("\nnot found\n");
		main();
	}
	// Enter the do while loop for the password
	do {
		c = _getch();
		// Check if the character entered is a valid char, and for that character, print a "*" character.
		if (isprint(c))
		{
			buffer[pos++] = c;
			printf("%c", '*');
		}
		else if (c == 8 && pos)
		{
			buffer[pos--] = '\0';
			printf("%s", "\b \b");
		}
	} while (c != 13);
	// If the buffer and password are equal, print a succesfull login, and call other methods
	if (!strcmp(buffer, password)) {
		printf("\n%s\n", "Logged on succesfully!");
		menu();
		scanf("%d", &choice);
		parseChoice(choice);
	}

	else {
		printf("\n%s\n", "Incorrect login!, Please try again");
		main();
	}

	fclose(fp);
	_getch();
}

void menu() 
{
	printf("\n1) Add Player");
	printf("\n2) Display Players");
	printf("\n3) Display Players Details");
	printf("\n4) Update a Player’s statistic");
	printf("\n5) Delete a Player");
	printf("\n6) Generate Statistics");
	printf("\n7) Print Players Details to File");
	printf("\n8) Display Players order of Height\n");
}

void parseChoice(int choice) 
{
	while (choice != -1)
	{
		switch (choice)
		{
		case 1:
			printf("\nAdding Player");
			addPlayer();
			break;
		case 2:
			printf("\nDisplaying Players");
			break;
		case 3:
			printf("\nDisplaying Players Details");
			break;
		case 4:
			printf("\nUpdating Players stats");
			break;
		case 5:
			printf("\nDeleting a Player");
			break;
		case 6:
			printf("\nGeneraing stats");
			break;
		case 7:
			printf("\nPrinting Players to File...");
			break;
		case 8:
			printf("\nDisplaying Players in order of Height\n");
			break;
		default:
			printf("\nInvalid\n");
			menu();
			scanf("%d", &choice);
			parseChoice(choice);
			break;
		}
	}

	
}

void addPlayer() 
{
	int IRFUNumber = 0;
	struct node* head_ptr;
	head_ptr = NULL;
	printf("\nPlease Enter IRFU Number");
	scanf("%d", IRFUNumber);

	// check if the IRFU is unique
	if (search(head_ptr, IRFUNumber) == 0)
	{
		// is unique, so add a node
		addPlayerToList(&head_ptr, IRFUNumber);
	}
	else
	{
		printf("This ID is already used.....\n");
	}
}

int search(struct node* headptr, char newIRFU[]) 
{
	struct node *temp;
	int found = 0;
	int i = 0;

	temp = (struct node*)malloc(sizeof(struct node));
	// loop through the ID's to find a match
	temp = headptr;
	while (temp != NULL)
	{
		if (strcmp(newIRFU, temp->IRFU) == 0)
		{
			i++;
			found = i;
		}
		// asign temp to temp->NEXT to incriment it
		temp = temp->NEXT;
	}

	return found;
}

void addPlayerToList(struct node* headptr, char newIRFU[]) 
{
	// add to end
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp = headptr;
	while (temp->NEXT != NULL) // go to the last node
	{
		temp = temp->NEXT;
	}
	struct node *newNode;
	newNode = (struct node*)malloc(sizeof(struct node));

	strcpy(newNode->IRFU, newIRFU);

	printf("\nPlease enter your name:\n");
	scanf("%s", newNode->firstName);

	printf("\nPlease enter your second name:\n");
	scanf("%s", newNode->secondName);

	printf("\nPlease enter your age:\n");
	scanf("%d", &newNode->age);

	printf("\nPlease enter your height:\n");
	scanf("%d", &newNode->height);

	printf("\nPlease enter your weight:\n");
	scanf("%d", &newNode->weight);

	printf("\nPlease enter your club name:\n");
	scanf("%s", newNode->club);

	printf("\nPlease enter your email:\n");
	scanf("%s", newNode->email);

	printf("\nPlease enter your player Position:\n");
	scanf("%s", newNode->pos);
	

	printf("\nPlease enter your missed tackles per match:\n");
	scanf("%d", &newNode->tacklesMissed);


	printf("\nPlease enter your meters made:\n");
	scanf("%d", &newNode->meters);

	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}