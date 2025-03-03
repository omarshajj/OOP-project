#include "TaskManager.h"
using namespace std;

int main() {
    TaskManager<Task> manager;
    int choice;

    while (true) {
        // show menu options
        cout << "TO DO LIST MENU \n";
        cout << "1. Add Task\n";
        cout << "2. Add Urgent Task\n";
        cout << "3. Display Tasks\n";
        cout << "4. Mark Task Completed\n";
        cout << "5. Change Task Priority\n";
        cout << "6. Exit\n";
        cout << "enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // get task details from user
            string title, description, dueDate;

            cout << "enter title: ";
            getline(cin, title);
            cout << "enter description: ";
            getline(cin, description);
            cout << "enter due date (eg. dd-mm-yyyy): ";
            getline(cin, dueDate);

            // create new task and add to manager
            Task* newTask = new Task(title, description, dueDate);
            manager.addTask(newTask);
        }
        else if (choice == 2) {
            // get  task details from user
            string title, description, dueDate;

            cout << "enter title: ";
            getline(cin, title);
            cout << "enter description: ";
            getline(cin, description);
            cout << "enter due date (eg. dd-mm-yyyy): ";
            getline(cin, dueDate);

            // create new task and add to manager
            Task* newUrgentTask = new UrgentTask(title, description, dueDate);
            manager.addTask(newUrgentTask);
        }
        else if (choice == 3) {
            // show all tasks
            manager.displayTasks();
        }
        else if (choice == 4) {
            // mark a task as completed
            int index;
            cout << "enter task number to mark completed: ";
            cin >> index;
            manager.markTaskCompleted(index - 1);
        }
        else if (choice == 5) {
            // change task priority
            if (manager.getSize() == 0) {
                cout << "no tasks available\n";
                continue;
            }

            cout << "current tasks:\n";
            manager.displayTaskTitles(); // show only titles

            int oldIndex, newIndex;
            cout << "enter task number to move: ";
            cin >> oldIndex;
            cout << "enter new priority position: ";
            cin >> newIndex;

            manager.changeTaskPriority(oldIndex - 1, newIndex - 1);
        }
        else if (choice == 6) {
            // exit program
            cout << "exiting\n";
            break;
        }
        else {
            // handle invalid input
            cout << "invalid try again\n";
        }
    }

    return 0;
}
