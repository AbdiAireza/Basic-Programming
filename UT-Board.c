#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Task {
    char taskName[50];
    char priority[20];
    char deadline[20];
    struct Task* next;
};

struct List {
    char listName[50];
    struct Task* tasks;
    struct List* next;
};

struct Board {
    char boardName[50];
    struct List* lists;
    struct Board* next;
};

struct User {
    char username[50];
    char password[50];
    struct Board* boards;
    struct User* next;
};

void signup(struct User** users, char* username, char* password);
struct User* login(struct User* users, char* username, char* password);
void showMenu();
void viewBoards(struct User* user);
void createNewBoard(struct User* user);
void deleteBoard(struct User* user);
void addDefaultBoards(struct User* user);
void viewBoardMenu(struct Board* board);
void viewLists(struct Board* board);
void createNewList(struct Board* board);
void deleteList(struct Board* board);
void addDefaultLists(struct Board* board);
void viewListMenu(struct List* list);
void viewTasks(struct List* list);
void addTask(struct List* list);
void editTask(struct List* list);
void deleteTask(struct List* list);
void moveTask(struct List* list, struct User* user);
void sortListByPriority(struct List* list);
void sortListByDeadline(struct List* list);
void saveUserData(struct User* users);
struct User* loadUserData();
void saveBoardData(struct Board* boards, FILE* file);
void saveListData(struct List* lists, FILE* file);
void saveTaskData(struct Task* tasks, FILE* file);
struct Board* loadBoardData(FILE* file);
struct List* loadListData(FILE* file);
struct Task* loadTaskData(FILE* file);


int main() {
    struct User* users = loadUserData(); // Load user data at the beginning

    char input[100];
    char command[20];
    char username[50];
    char password[50];

    while (1) {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", command);

        if (strcmp(command, "signup") == 0) {
            sscanf(input, "%*s %s %s", username, password);
            signup(&users, username, password);
            saveUserData(users); // Save user data after signup
        } else if (strcmp(command, "login") == 0) {
            sscanf(input, "%*s %s %s", username, password);
            struct User* loggedInUser = login(users, username, password);

            if (loggedInUser != NULL) {
                while (1) {
                    showMenu();
                    int choice;
                    printf("Enter choice: ");
                    scanf("%d", &choice);
                    getchar(); // Consume the newline character

                    switch (choice) {
                        case 1:
                            viewBoards(loggedInUser);
                            break;
                        case 2:
                            createNewBoard(loggedInUser);
                            saveUserData(users); // Save user data after creating a new board
                            break;
                        case 3:
                            deleteBoard(loggedInUser);
                            saveUserData(users); // Save user data after deleting a board
                            break;
                        case 4:
                            // Logout
                            printf("Logged out successfully.\n");
                            saveUserData(users); // Save user data after logout
                            break;
                        default:
                            printf("Invalid choice\n");
                    }

                    if (choice == 4) {
                        break; // Break the inner loop to logout
                    }
                }
            }
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}

void signup(struct User** users, char* username, char* password) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->boards = NULL;
    newUser->next = *users;
    *users = newUser;

    // Add default boards for the new user
    addDefaultBoards(newUser);

    printf("User %s successfully registered and logged in.\n", username);
}

struct User* login(struct User* users, char* username, char* password) {
    while (users != NULL) {
        if (strcmp(users->username, username) == 0 && strcmp(users->password, password) == 0) {
            printf("Welcome, %s!\n", username);
            return users; // Return the logged-in user
        }
        users = users->next;
    }

    printf("Invalid username or password\n");
    return NULL; // Return NULL if login fails
}

void showMenu() {
    printf("\nMenu:\n");
    printf("1. View Boards\n");
    printf("2. Create New Board\n");
    printf("3. Delete Board\n");
    printf("4. Logout\n");
}

void viewBoards(struct User* user) {
    printf("\nAvailable Boards:\n");

    int index = 1;
    struct Board* currentBoard = user->boards;

    while (currentBoard != NULL) {
        printf("%d. %s\n", index++, currentBoard->boardName);
        currentBoard = currentBoard->next;
    }
    int choice;
    printf("Enter the number of the board to view (or 0 to go back): ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    if (choice > 0 && choice <= index - 1) {
        currentBoard = user->boards;
        for (int i = 1; i < choice; i++) {
            currentBoard = currentBoard->next;
        }
        viewBoardMenu(currentBoard);
    }
}

void createNewBoard(struct User* user) {
    char boardName[50];
    printf("Enter board name: ");
    fgets(boardName, sizeof(boardName), stdin);
    boardName[strcspn(boardName, "\n")] = '\0';

    struct Board* newBoard = (struct Board*)malloc(sizeof(struct Board));
    strcpy(newBoard->boardName, boardName);
    newBoard->lists = NULL;
    newBoard->next = user->boards;
    user->boards = newBoard;

    // Add default lists for the new board
    addDefaultLists(newBoard);

    printf("Board %s created successfully!\n", boardName);
}

void deleteBoard(struct User* user) {
    char boardName[50];
    printf("Enter board name to delete: ");
    fgets(boardName, sizeof(boardName), stdin);
    boardName[strcspn(boardName, "\n")] = '\0';

    struct Board* currentBoard = user->boards;
    struct Board* prevBoard = NULL;

    while (currentBoard != NULL) {
        if (strcmp(currentBoard->boardName, boardName) == 0) {
            if (prevBoard == NULL) {
                user->boards = currentBoard->next;
            } else {
                prevBoard->next = currentBoard->next;
            }

            free(currentBoard);
            printf("Board %s deleted successfully!\n", boardName);
            return;
        }

        prevBoard = currentBoard;
        currentBoard = currentBoard->next;
    }

    printf("Board %s not found\n", boardName);
}
void addDefaultBoards(struct User* user) {
    char defaultBoards[][50] = {"work", "personal", "study"};

    for (int i = sizeof(defaultBoards) / sizeof(defaultBoards[0]) - 1; i >= 0; i--) {
        struct Board* newBoard = (struct Board*)malloc(sizeof(struct Board));
        strcpy(newBoard->boardName, defaultBoards[i]);
        newBoard->lists = NULL;
        newBoard->next = user->boards;
        user->boards = newBoard;

        // Add default lists for the new board
        addDefaultLists(newBoard);
    }
}

void viewBoardMenu(struct Board* board) {
    int choice;
    while (1) {
        printf("\nBoard Menu for %s:\n", board->boardName);
        printf("1. View Lists\n");
        printf("2. Create New List\n");
        printf("3. Delete List\n");
        printf("4. Go back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                viewLists(board);
                break;
            case 2:
                createNewList(board);
                break;
            case 3:
                deleteList(board);
                break;
            case 4:
                printf("Going back to the main menu.\n");
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void viewLists(struct Board* board) {
    printf("\nLists in %s:\n", board->boardName);

    int index = 1;
    struct List* currentList = board->lists;

    while (currentList != NULL) {
        printf("%d. %s\n", index++, currentList->listName);
        currentList = currentList->next;
    }

    int choice;
    printf("Enter the number of the list to view (or 0 to go back): ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    if (choice > 0 && choice <= index - 1) {
        currentList = board->lists;
        for (int i = 1; i < choice; i++) {
            currentList = currentList->next;
        }
        viewListMenu(currentList);
    }
}

void createNewList(struct Board* board) {
    char listName[50];
    printf("Enter list name: ");
    fgets(listName, sizeof(listName), stdin);
    listName[strcspn(listName, "\n")] = '\0';

    struct List* newList = (struct List*)malloc(sizeof(struct List));
    strcpy(newList->listName, listName);
    newList->tasks = NULL;
    newList->next = board->lists;
    board->lists = newList;

    printf("List %s created successfully!\n", listName);
}

void deleteList(struct Board* board) {
    char listName[50];
    printf("Enter list name to delete: ");
    fgets(listName, sizeof(listName), stdin);
    listName[strcspn(listName, "\n")] = '\0';

    struct List* currentList = board->lists;
    struct List* prevList = NULL;

    while (currentList != NULL) {
        if (strcmp(currentList->listName, listName) == 0) {
            if (prevList == NULL) {
                board->lists = currentList->next;
            } else {
                prevList->next = currentList->next;
            }

            free(currentList);
            printf("List %s deleted successfully!\n", listName);
            return;
        }

        prevList = currentList;
        currentList = currentList->next;
    }

    printf("List %s not found\n", listName);
}

void addDefaultLists(struct Board* board) {
    char defaultLists[][50] = {"To Do", "In Progress", "Completed"};

    for (int i = sizeof(defaultLists) / sizeof(defaultLists[0]) - 1; i >= 0; i--) {
        struct List* newList = (struct List*)malloc(sizeof(struct List));
        strcpy(newList->listName, defaultLists[i]);
        newList->tasks = NULL;
        newList->next = board->lists;
        board->lists = newList;
    }
}


void viewListMenu(struct List* list) {
    int choice;
    while (1) {
        printf("\nList: %s\n", list->listName);
        viewTasks(list);
        printf("Options:\n");
        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Delete Task\n");
        printf("4. Move Task to Another List\n");
        printf("5. Sort by Priority\n");
        printf("6. Sort by Deadline\n");  // Added option to sort by priority
        printf("7. Go Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                addTask(list);
                break;
            case 2:
                editTask(list);
                break;
            case 3:
                deleteTask(list);
                break;
            case 4:
                moveTask(list, NULL); // Pass NULL for the user parameter for now
                break;
            case 5:
                sortListByPriority(list);
                printf("List sorted by Priority.\n");
                break;
                 case 6:
                sortListByDeadline(list);
                printf("List sorted by Deadline.\n");
                break;
            case 7:
                printf("Going back to the board menu.\n");
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}
void viewTasks(struct List* list) {
    printf("Tasks:\n");

    // Count the number of tasks
    int taskCount = 0;
    struct Task* currentTask = list->tasks;

    while (currentTask != NULL) {
        taskCount++;
        currentTask = currentTask->next;
    }

    // Create an array to store tasks
    struct Task** taskArray = (struct Task**)malloc(taskCount * sizeof(struct Task*));

    // Populate the array with tasks
    currentTask = list->tasks;
    for (int i = 0; i < taskCount; i++) {
        taskArray[i] = currentTask;
        currentTask = currentTask->next;
    }

    // Display tasks in reverse order
    for (int i = taskCount - 1; i >= 0; i--) {
        printf("%d. Task: %s, Priority: %s, Deadline: %s\n", taskCount - i, taskArray[i]->taskName, taskArray[i]->priority, taskArray[i]->deadline);
    }

    // Free the allocated memory for the taskArray
    free(taskArray);
}


void addTask(struct List* list) {
    char taskName[50];
    char priority[20];
    char deadline[20];

    printf("Enter task name: ");
    fgets(taskName, sizeof(taskName), stdin);
    taskName[strcspn(taskName, "\n")] = '\0';

    printf("Enter priority: ");
    fgets(priority, sizeof(priority), stdin);
    priority[strcspn(priority, "\n")] = '\0';

    printf("Enter deadline: ");
    fgets(deadline, sizeof(deadline), stdin);
    deadline[strcspn(deadline, "\n")] = '\0';

    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    strcpy(newTask->taskName, taskName);
    strcpy(newTask->priority, priority);
    strcpy(newTask->deadline, deadline);
    newTask->next = list->tasks;
    list->tasks = newTask;

    printf("Task added successfully!\n");
}

void editTask(struct List* list) {
    int taskIndex;
    printf("Enter the index of the task to edit: ");
    scanf("%d", &taskIndex);
    getchar(); // Consume the newline character

    struct Task* currentTask = list->tasks;

    for (int i = 1; i < taskIndex && currentTask != NULL; i++) {
        currentTask = currentTask->next;
    }

    if (currentTask != NULL) {
        char taskName[50];
        char priority[20];
        char deadline[20];

        printf("Enter new task name: ");
        fgets(taskName, sizeof(taskName), stdin);
        taskName[strcspn(taskName, "\n")] = '\0';

        printf("Enter new priority: ");
        fgets(priority, sizeof(priority), stdin);
        priority[strcspn(priority, "\n")] = '\0';

        printf("Enter new deadline: ");
        fgets(deadline, sizeof(deadline), stdin);
        deadline[strcspn(deadline, "\n")] = '\0';

        strcpy(currentTask->taskName, taskName);
        strcpy(currentTask->priority, priority);
        strcpy(currentTask->deadline, deadline);

        printf("Task edited successfully!\n");
    } else {
        printf("Task not found\n");
    }
}

void deleteTask(struct List* list) {
    int taskIndex;
    printf("Enter the index of the task to delete: ");
    scanf("%d", &taskIndex);
    getchar(); // Consume the newline character

    struct Task* currentTask = list->tasks;
    struct Task* prevTask = NULL;

    for (int i = 1; i < taskIndex && currentTask != NULL; i++) {
        prevTask = currentTask;
        currentTask = currentTask->next;
    }

    if (currentTask != NULL) {
        if (prevTask == NULL) {
            list->tasks = currentTask->next;
        } else {
            prevTask->next = currentTask->next;
        }

        free(currentTask);
        printf("Task deleted successfully!\n");
    } else {
        printf("Task not found\n");
    }
}
void moveTask(struct List* list, struct User* user) {
    int taskIndex;

    printf("Which task do you want to move?\n");

    // Display tasks in the current list
    viewTasks(list);

    printf("Enter the number of the task to move (or 0 to go back): ");
    scanf("%d", &taskIndex);
    getchar(); // Consume the newline character

    if (taskIndex == 0) {
        // User chose to go back
        return;
    }

    struct Task* currentTask = list->tasks;
    struct Task* prevTask = NULL;

    for (int i = 1; i < taskIndex && currentTask != NULL; i++) {
        prevTask = currentTask;
        currentTask = currentTask->next;
    }

    if (currentTask != NULL) {
        printf("Which list would you like to move the task to?\n");

        int index = 1;
        struct List* currentList = list;

        while (currentList != NULL) {
            printf("%d. %s\n", index++, currentList->listName);
            currentList = currentList->next;
        }

        int listChoice;
        printf("Enter the number of the list to move the task to (or 0 to go back): ");
        scanf("%d", &listChoice);
        getchar(); // Consume the newline character

        if (listChoice == 0) {
            // User chose to go back
            return;
        }

        if (listChoice > 0 && listChoice <= index - 1) {
            currentList = list;
            for (int i = 1; i < listChoice; i++) {
                currentList = currentList->next;
            }

            // Remove the task from the original list
            if (prevTask == NULL) {
                list->tasks = currentTask->next;
            } else {
                prevTask->next = currentTask->next;
            }

            // Add the task to the selected list
            currentTask->next = currentList->tasks;
            currentList->tasks = currentTask;

            // Display a message indicating the task movement
            printf("Moving task '%s' to '%s'.\n", currentTask->taskName, currentList->listName);
            return;
        } else {
            printf("Invalid list choice. Task movement canceled.\n");
        }
    } else {
        printf("Task not found\n");
    }
}
void sortListByPriority(struct List* list) {
    // Define a priority order: high, medium, low
    char priorityOrder[][20] = {"high", "medium", "low"};

    // Bubble sort for simplicity
    struct Task *current, *next;
    char tempName[50], tempPriority[20], tempDeadline[20];

    for (current = list->tasks; current != NULL; current = current->next) {
        for (next = current->next; next != NULL; next = next->next) {
            // Compare priorities based on their order
            int currentPriorityIndex = -1, nextPriorityIndex = -1;

            for (int i = 0; i < sizeof(priorityOrder) / sizeof(priorityOrder[0]); i++) {
                if (strcmp(current->priority, priorityOrder[i]) == 0) {
                    currentPriorityIndex = i;
                }

                if (strcmp(next->priority, priorityOrder[i]) == 0) {
                    nextPriorityIndex = i;
                }
            }

            // Swap tasks based on priority order
            if (currentPriorityIndex < nextPriorityIndex) {
                // Swap tasks
                strcpy(tempName, current->taskName);
                strcpy(tempPriority, current->priority);
                strcpy(tempDeadline, current->deadline);

                strcpy(current->taskName, next->taskName);
                strcpy(current->priority, next->priority);
                strcpy(current->deadline, next->deadline);

                strcpy(next->taskName, tempName);
                strcpy(next->priority, tempPriority);
                strcpy(next->deadline, tempDeadline);
            }
        }
    }
}

void sortListByDeadline(struct List* list) {
    // Bubble sort for simplicity
    struct Task *current, *next;
    char tempName[50], tempPriority[20], tempDeadline[20];

    for (current = list->tasks; current != NULL; current = current->next) {
        for (next = current->next; next != NULL; next = next->next) {
            // Compare deadlines in ascending order
            if (strcmp(current->deadline, next->deadline) > 0) {
                // Swap tasks
                strcpy(tempName, current->taskName);
                strcpy(tempPriority, current->priority);
                strcpy(tempDeadline, current->deadline);

                strcpy(current->taskName, next->taskName);
                strcpy(current->priority, next->priority);
                strcpy(current->deadline, next->deadline);

                strcpy(next->taskName, tempName);
                strcpy(next->priority, tempPriority);
                strcpy(next->deadline, tempDeadline);
            }
        }
    }
}
void saveUserData(struct User* users) {
    FILE* file = fopen("users.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    while (users != NULL) {
        fprintf(file, "%s,%s\n", users->username, users->password);
        saveBoardData(users->boards, file);
        users = users->next;
    }

    fclose(file);
}

struct User* loadUserData() {
    FILE* file = fopen("users.csv", "r");
    if (file == NULL) {
        printf("No user data found. Starting with an empty user list.\n");
        return NULL;
    }

    struct User* head = NULL;
    struct User* tail = NULL;

    char username[50];
    char password[50];

    while (fscanf(file, "%49[^,],%49[^\n]\n", username, password) == 2) {
        struct User* newUser = (struct User*)malloc(sizeof(struct User));
        strcpy(newUser->username, username);
        strcpy(newUser->password, password);
        newUser->boards = loadBoardData(file);
        newUser->next = NULL;

        if (tail == NULL) {
            head = newUser;
            tail = newUser;
        } else {
            tail->next = newUser;
            tail = newUser;
        }
    }

    fclose(file);
    return head;
}
void saveBoardData(struct Board* boards, FILE* file) {
    while (boards != NULL) {
        fprintf(file, "%s\n", boards->boardName);
        saveListData(boards->lists, file);
        boards = boards->next;
    }
}

struct Board* loadBoardData(FILE* file) {
    struct Board* head = NULL;
    struct Board* tail = NULL;

    char boardName[50];

    while (fscanf(file, "%49[^\n]\n", boardName) == 1) {
        struct Board* newBoard = (struct Board*)malloc(sizeof(struct Board));
        strcpy(newBoard->boardName, boardName);
        newBoard->lists = loadListData(file);
        newBoard->next = NULL;

        if (tail == NULL) {
            head = newBoard;
            tail = newBoard;
        } else {
            tail->next = newBoard;
            tail = newBoard;
        }
    }

    return head;
}
void saveListData(struct List* lists, FILE* file) {
    while (lists != NULL) {
        fprintf(file, "%s\n", lists->listName);
        saveTaskData(lists->tasks, file);
        lists = lists->next;
    }
}

struct List* loadListData(FILE* file) {
    struct List* head = NULL;
    struct List* tail = NULL;

    char listName[50];

    while (fscanf(file, "%49[^\n]\n", listName) == 1) {
        struct List* newList = (struct List*)malloc(sizeof(struct List));
        strcpy(newList->listName, listName);
        newList->tasks = loadTaskData(file);
        newList->next = NULL;

        if (tail == NULL) {
            head = newList;
            tail = newList;
        } else {
            tail->next = newList;
            tail = newList;
        }
    }

    return head;
}
void saveTaskData(struct Task* tasks, FILE* file) {
    while (tasks != NULL) {
        fprintf(file, "%s,%s,%s\n", tasks->taskName, tasks->priority, tasks->deadline);
        tasks = tasks->next;
    }
}

struct Task* loadTaskData(FILE* file) {
    struct Task* head = NULL;
    struct Task* tail = NULL;

    char taskName[50];
    char priority[20];
    char deadline[20];

    while (fscanf(file, "%49[^,],%19[^,],%19[^\n]\n", taskName, priority, deadline) == 3) {
        struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
        strcpy(newTask->taskName, taskName);
        strcpy(newTask->priority, priority);
        strcpy(newTask->deadline, deadline);
        newTask->next = NULL;

        if (tail == NULL) {
            head = newTask;
            tail = newTask;
        } else {
            tail->next = newTask;
            tail = newTask;
        }
    }

    return head;
}
