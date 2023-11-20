#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <regex.h>

#define MESSAGE_LENGTH 256
#define USERNAME_LENGTH 32

typedef struct Message {
	char content[MESSAGE_LENGTH];
	char username[USERNAME_LENGTH];
	time_t timestamp;
	struct Message* next;
} Message;

typedef struct MessageBox {
	Message* head;
	size_t size;
} MessageBox;

// Function to create a message
Message* create_message(const char* username, const char* text) {
	Message* new_message = (Message*)malloc(sizeof(Message));
	if (new_message) {
		strncpy(new_message->username, username, USERNAME_LENGTH);
		new_message->username[USERNAME_LENGTH - 1] = '\0'; // Ensure null-termination
		strncpy(new_message->content, text, MESSAGE_LENGTH);
		new_message->content[MESSAGE_LENGTH - 1] = '\0'; // Ensure null-termination
		new_message->timestamp = time(NULL);
		new_message->next = NULL;
	}
	return new_message;
}

// Initialize the message box with no messages
void initialize_message_box(MessageBox* mbox) {
	mbox->head = NULL;
	mbox->size = 0;
}

// Function to add a message to the message box
void add_message(MessageBox* mbox, Message* message) {
	if (mbox->head == NULL) {
		mbox->head = message;
	} else {
		Message* temp = mbox->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = message;
	}
	mbox->size++;
}

// Function to display all messages in the message box
void display_messages(const MessageBox* mbox) {
	Message* temp = mbox->head;
	while (temp != NULL) {
		printf("Username: %s\n", temp->username);
		printf("Time: %s", ctime(&(temp->timestamp)));
		printf("Message: %s\n\n", temp->content);
		temp = temp->next;
	}
}

// Function to free all messages in the message box
void free_message_box(MessageBox* mbox) {
	Message* temp = mbox->head;
	while (temp != NULL) {
		Message* next = temp->next;
		free(temp);
		temp = next;
	}
	mbox->head = NULL;
	mbox->size = 0;
}

// Function to prompt user and send a message
void send_message(MessageBox* mbox) {
	char input[MESSAGE_LENGTH];
	char username[USERNAME_LENGTH];
	printf("Enter your username: ");
	fgets(username, USERNAME_LENGTH, stdin);
	username[strcspn(username, "\n")] = 0; // Remove trailing newline character

	printf("Enter your message (max 255 characters): ");
	fgets(input, MESSAGE_LENGTH, stdin);
	input[strcspn(input, "\n")] = 0; // Remove trailing newline character

	Message* message = create_message(username, input);
	add_message(mbox, message);
	printf("Message sent at %s\n", ctime(&(message->timestamp)));
}

// Function to search and display messages that match the regular expression
void search_messages(const MessageBox* mbox) {
	char pattern[MESSAGE_LENGTH];
	printf("Enter regex pattern to search for: ");
	fgets(pattern, MESSAGE_LENGTH, stdin);
	pattern[strcspn(pattern, "\n")] = 0; // Remove trailing newline character

	regex_t regex;
	int reti;
	reti = regcomp(&regex, pattern, REG_EXTENDED);
	if (reti) {
		printf("Could not compile regex\n");
		return;
	}

	Message* temp = mbox->head;
	while (temp != NULL) {
		reti = regexec(&regex, temp->content, 0, NULL, 0);
		if (!reti) {
			printf("Time: %sMessage: %s\n\n", ctime(&(temp->timestamp)), temp->content);
		}
		temp = temp->next;
	}

	regfree(&regex);
}

// Function to filter messages by username
void filter_messages_by_username(const MessageBox* mbox, const char* username) {
	Message* temp = mbox->head;
	while (temp != NULL) {
		if (strcmp(temp->username, username) == 0) {
			printf("Username: %s\n", temp->username);
			printf("Time: %s", ctime(&(temp->timestamp)));
			printf("Message: %s\n\n", temp->content);
		}
		temp = temp->next;
	}
}

int main() {
	MessageBox mbox;
	initialize_message_box(&mbox);

	int running = 1;
	while (running) {
		printf("1. Send a message\n");
		printf("2. Display all messages\n");
		printf("3. Search messages by regex\n");
		printf("4. Filter messages by username\n");
		printf("0. Exit\n");
		printf("Choose an option: ");

		int choice;
		scanf("%d", &choice);
		// Clear the input buffer
		while (getchar() != '\n');

		switch (choice) {
			case 1:
				send_message(&mbox);
			break;
			case 2:
				display_messages(&mbox);
			break;
			case 3:
				search_messages(&mbox);
			break;
			case 4: {
				char username[USERNAME_LENGTH];
				printf("Enter username to filter by: ");
				fgets(username, USERNAME_LENGTH, stdin);
				username[strcspn(username, "\n")] = 0; // Remove trailing newline character
				filter_messages_by_username(&mbox, username);
				break;
			}
			case 0:
				running = 0;
			break;
			default:
				printf("Invalid option. Please try again.\n");
		}
	}

	free_message_box(&mbox);

	return 0;
}
