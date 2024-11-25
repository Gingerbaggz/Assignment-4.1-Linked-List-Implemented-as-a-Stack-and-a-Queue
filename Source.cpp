#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Node class for doubly linked list
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Stack implementation using doubly linked list (LIFO)
class Stack {
public:
    Node* head;

    Stack() : head(nullptr) {}

    // Insert push into stack (LIFO)
    void insert(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Remove pop from stack (LIFO)
    int remove() {
        if (head == nullptr) {
            std::cerr << "Stack is empty, cannot remove." << std::endl;
            return -1;
        }
        Node* temp = head;
        int removedData = head->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        return removedData;
    }

    // Print stack elements
    void print_stack() {
        Node* current = head;
        if (!current) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "None" << std::endl;
    }
};

// Queue implementation using doubly linked list (FIFO)
class Queue {
public:
    Node* head;
    Node* tail;

    Queue() : head(nullptr), tail(nullptr) {}

    // Insert enqueue into queue (FIFO)
    void insert(int data) {
        Node* newNode = new Node(data);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Remove dequeue from queue (FIFO)
    int remove() {
        if (head == nullptr) {
            std::cerr << "Queue is empty, cannot remove." << std::endl;
            return -1;
        }
        Node* temp = head;
        int removedData = head->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;  // If the queue becomes empty, reset tail to nullptr
        }
        delete temp;
        return removedData;
    }

    // Print queue elements
    void print_queue() {
        Node* current = head;
        if (!current) {
            std::cout << "Queue is empty." << std::endl;
            return;
        }
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "None" << std::endl;
    }
};

// Function to generate random integers and measure insertion time
void test_insert(int n) {
    Stack stack;
    Queue queue;

    // Measure time to insert into stack
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        stack.insert(rand() % 10000);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto stack_insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Measure time to insert into queue
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        queue.insert(rand() % 10000);
    }
    end = std::chrono::high_resolution_clock::now();
    auto queue_insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Insertion time for " << n << " elements:" << std::endl;
    std::cout << "Stack: " << stack_insert_time << " ms, Queue: " << queue_insert_time << " ms" << std::endl;
}

// Function to measure removal time
void test_remove(int n) {
    Stack stack;
    Queue queue;

    // Insert random integers into stack and queue for remove testing
    for (int i = 0; i < n; ++i) {
        stack.insert(rand() % 10000);
        queue.insert(rand() % 10000);
    }

    // Measure time to remove from stack
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        stack.remove();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto stack_remove_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Measure time to remove from queue
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        queue.remove();
    }
    end = std::chrono::high_resolution_clock::now();
    auto queue_remove_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Removal time for " << n << " elements:" << std::endl;
    std::cout << "Stack: " << stack_remove_time << " ms, Queue: " << queue_remove_time << " ms" << std::endl;
}

int main() {
    // Seed for random number generation
    srand(time(0));

    int sizes[] = { 100, 1000, 10000 };
    for (int size : sizes) {
        test_insert(size);
        test_remove(size);
    }

    return 0;
}
