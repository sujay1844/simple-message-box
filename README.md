# Simple Message Box
This simple message box system was designed with a focus on using data structures that are efficient for the common operations one would expect to perform on such a system, namely appending messages, iterating over messages, and searching through messages.

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
