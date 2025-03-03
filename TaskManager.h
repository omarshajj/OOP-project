#pragma once
#include <iostream>
#include <string>

// base Task class
class Task {
protected:
    std::string title;
    std::string description;
    std::string dueDate;
    bool completed;

public:
    Task(std::string t, std::string d, std::string date);
    virtual ~Task() {}

    virtual void display() const;
    void markCompleted();
    bool isCompleted() const;

    template <typename T>
    friend class TaskManager;  // let TaskManager access private members
};

// Derived UrgentTask class
class UrgentTask : public Task {
public:
    UrgentTask(std::string t, std::string d, std::string date);
    void display() const override; // Override the display method
};

// task manager (template + dynamic array expansion)
template <typename T>
class TaskManager {
private:
    T** tasks;   // pointer to an array of task pointers
    int size;    // current number of tasks
    int capacity; // max number of tasks before expansion

    void expandArray();  // doubles the capacity when full

public:
    TaskManager();
    ~TaskManager();

    void addTask(T* task); // adds a task to the list
    void displayTasks() const; // prints all tasks
    void markTaskCompleted(int index); // marks a task as completed
    void changeTaskPriority(int oldIndex, int newIndex); // moves task to new position
    void displayTaskTitles() const; // shows only task titles with numbers
    inline int getSize() const { return size; } // returns the current task count
};
