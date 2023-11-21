# Simple Message Box
This simple message box system was designed with a focus on using data structures that are efficient for the common operations one would expect to perform on such a system, namely appending messages, iterating over messages, and searching through messages.

# Explaination
The provided C code implements a simple console-based message box system, featuring the ability to send messages, display all messages, search messages using regular expressions, and filter messages by username. The main data structure used is a singly linked list, with each node representing a message. Here is a breakdown of its components and functionalities:

## Struct Definitions
- `Message`: Represents a single message with fields for content, username, a timestamp generated at the time of creation, and a pointer to the next message in the list.
- `MessageBox`: Represents the message box itself, holding a pointer to the head of the linked list of messages (`head`) and a size variable tracking the number of messages.

## Functions
- `create_message`: Allocates memory for a new message, copies the username and message text into the newly created message, sets the current timestamp, and initializes the next pointer to NULL. It returns a pointer to the new message.
- `initialize_message_box`: Initializes a message box with no messages and a size of 0.
- `add_message`: Adds a new message to the end of the linked list in the message box and increments the size.
- `display_messages`: Iterates over the linked list of messages and prints out the details of each message.
- `free_message_box`: Frees the memory allocated for all messages in the message box and resets the head and size.
- `send_message`: Prompts the user to input a username and a message, then passes this information to create_message and add_message to add the new message to the message box.
- `search_messages`: Prompts the user to input a regular expression pattern, then searches the messages using this regex and displays the matching messages.
- `filter_messages_by_username`: Iterates over the list of messages and displays those where the username matches the given username.
- `main`: Provides an interactive shell where the user can choose to send a message, display all messages, search messages by regex, filter messages by username, or exit the application.

## Main Program Loop
In `main`, the program initializes the message box and enters an interactive loop, where it provides a menu to the user. The user can select an action by inputting the corresponding number. After executing the chosen action, the loop continues until the user selects the option to exit (`0`). Before exiting, the program frees all allocated memory for messages.

## I/O Considerations and Input Handling
- The program uses `fgets` to read input strings from the standard input (`stdin`), which avoids potential buffer overflow issues associated with `gets`.
After reading input using `fgets`, it removes the trailing newline character using `strcspn`.
It uses `scanf` to read integers for the menu selection and clears the input buffer afterward to avoid any leftover input interfering with subsequent reads.

## Potential Improvements
- The `add_message` function could be optimized by maintaining a pointer to the last element in the list. This would avoid having to iterate through the whole list every time a new message is added.
Regular expressions are compiled with each search operation in `search_messages`, which can be optimized if the same pattern is used multiple times.
Error handling for memory allocation (`malloc`) should be improved. If memory allocation fails (`malloc` returns `NULL`), the code should handle this gracefully instead of proceeding with a `NULL` pointer.

# Data Structure Usage and Justification:
For storing messages, a singly linked list was chosen. This data structure allows for efficient append operations, as new messages can be added to the end of the list without the need to resize an underlying array, which would be required if a dynamic array or similar structure were used. The linked list also ensures that we can iterate over the messages in a straightforward manner, which is necessary for displaying messages to users and for implementing user-friendly search functionality.
The linked list provides constant time insertion and deletion from the front, which may also be beneficial if future features require such operations. However, the downside is that it doesn't provide constant-time random access, but since our application does not require this feature frequently, the linked list is a justified choice.

# Abstract Data Types (ADTs) Used:
The Message and MessageBox types serve as the ADTs in this system. The Message type encapsulates the content of a message along with a sender's username and a timestamp. The MessageBox type represents the overall collection of messages and abstracts the underlying linked list data structure from the user.

# Features and Functionalities:
The message box provides several features:
- **Sending Messages**: Users can add new messages to the system. Each message includes the text entered by the user, a timestamp for when it was sent, and the username of the sender.
- **Receiving/Displaying Messages**: Users can view all messages sent in the system sorted by the order in which they were received.
- **Searching Messages**: Users can search through the message history using regular expressions. This powerful feature allows users to find messages that match complex patterns, rather than just simple string searches.
- **Filtering Messages by Username**: Users can filter the messages to only view the ones sent by a particular user, which can be useful when the message history grows large and conversations become interwoven.

# Assumptions Made:
Several assumptions have been made throughout the design and implementation of the message box:
- Messages will be primarily appended at the end, and the history will not require frequent deletions. This assumption justified the choice of a linked list over other structures, such as balanced trees.
- The search operation is not the primary function used in the system; thus, sub-optimal search time complexity (linear) was acceptable in favor of easier implementation and understanding.
- Users interacting with the system have some knowledge of regular expressions for the search functionality to be fully utilized.
- The username provided by the user is accurate. No additional verification mechanism (such as user authentication) has been implemented in this simple system.
- Memory usage is sufficient to store all messages in a linked list structure. There is no need for persisting messages across system shutdowns, so database storage or serialization was not considered.

This message box system is an example of applying distinct data structures to address specific requirements of an application, balancing memory usage, system efficiency, and user-friendliness. The data structure choice ensures an extensible foundation upon which additional features and scalability improvements could be built.
