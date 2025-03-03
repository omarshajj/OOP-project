#include "TaskManager.h"
using namespace std;

// Task implementation
Task::Task(string t, string d, string date)
    : title(t), description(d), dueDate(date), completed(false) {}

void Task::display() const {
    std::cout << (completed ? "✅" : "❌") << " " << title
              << " (Due: " << dueDate << ")\n"
              << "    " << description << "\n";
}

void Task::markCompleted() { completed = true; }
bool Task::isCompleted() const { return completed; }

// UrgentTask implementation
UrgentTask::UrgentTask(string t, string d, string date)
    : Task(t, d, date) {}

void UrgentTask::display() const {
    std::cout << (isCompleted() ? "✅" : "❌") << " URGENT! " << title
              << " (Due: " << dueDate << ")\n"
              << "    " << description << "\n";
}

// TaskManager implementation
template <typename T>
TaskManager<T>::TaskManager() : size(0), capacity(2) {
    // start with a small capacity to save memory
    tasks = new T*[capacity];
}

template <typename T>
TaskManager<T>::~TaskManager() {
    // clean up memory when task manager is destroyed
    for (int i = 0; i < size; i++)
        delete tasks[i];
    delete[] tasks;
}

template <typename T>
void TaskManager<T>::expandArray() {
    // double the capacity when the array is full
    int newCapacity = capacity * 2;
    T** newTasks = new T*[newCapacity];

    // copy old tasks to new array
    for (int i = 0; i < size; i++)
        newTasks[i] = tasks[i];

    delete[] tasks;
    tasks = newTasks;
    capacity = newCapacity;
}

template <typename T>
void TaskManager<T>::addTask(T* task) {
    // check if array is full and expand if needed
    if (size >= capacity)
        expandArray();

    tasks[size] = task;  // add task at the end
    size++;
}

template <typename T>
void TaskManager<T>::displayTasks() const {
    // if there are no tasks, let the user know
    if (size == 0) {
        cout << "no tasks\n";
        return;
    }
    
    cout << "your to-do list:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        tasks[i]->display();
    }
}

template <typename T>
void TaskManager<T>::displayTaskTitles() const {
    // show only task titles with their numbers
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << tasks[i]->title << "\n";
    }
}

template <typename T>
void TaskManager<T>::markTaskCompleted(int index) {
    // check if index is valid
    if (index < 0 || index >= size) {
        cout << "invalid task number\n";
        return;
    }

    tasks[index]->markCompleted();
    cout << "task marked as completed\n";
}

template <typename T>
void TaskManager<T>::changeTaskPriority(int oldIndex, int newIndex) {
    // check if indices are valid
    if (oldIndex < 0 || oldIndex >= size || newIndex < 0 || newIndex >= size) {
        cout << "invalid move\n";
        return;
    }

    T* temp = tasks[oldIndex];

    // move tasks down if shifting up
    if (oldIndex < newIndex) {
        for (int i = oldIndex; i < newIndex; i++)
            tasks[i] = tasks[i + 1];
    }
    // move tasks up if shifting down
    else {
        for (int i = oldIndex; i > newIndex; i--)
            tasks[i] = tasks[i - 1];
    }

    tasks[newIndex] = temp;
    cout << "task priority updated\n";
}

// explicit template instantiation
template class TaskManager<Task>;
