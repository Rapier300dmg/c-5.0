#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    Node* top;
    size_t size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        ++size;
    }

    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        --size;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    size_t getSize() const {
        return size;
    }
};

class LinkedList {
private:
    Node* head;

    Node* cloneHelper(Node* node) const {
        if (!node) return nullptr;
        Node* newHead = new Node(node->data);
        Node* current = newHead;
        Node* original = node->next;
        while (original) {
            current->next = new Node(original->data);
            current = current->next;
            original = original->next;
        }
        return newHead;
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "NULL" << std::endl;
    }

    Node* clone() const {
        return cloneHelper(head);
    }

    LinkedList operator+(const LinkedList& other) const {
        LinkedList result;
        Node* current = head;
        while (current) {
            result.insert(current->data);
            current = current->next;
        }
        current = other.head;
        while (current) {
            result.insert(current->data);
            current = current->next;
        }
        return result;
    }

    LinkedList operator*(const LinkedList& other) const {
        LinkedList result;
        Node* current1 = head;
        while (current1) {
            Node* current2 = other.head;
            while (current2) {
                if (current1->data == current2->data) {
                    result.insert(current1->data);
                    break;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }
        return result;
    }
};

int main() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top element: " << stack.peek() << std::endl;
    std::cout << "Popped element: " << stack.pop() << std::endl;
    std::cout << "Stack size: " << stack.getSize() << std::endl;

    LinkedList list1;
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);

    LinkedList list2;
    list2.insert(3);
    list2.insert(4);
    list2.insert(5);

    LinkedList clonedList;
    clonedList = list1.clone();

    std::cout << "Original list: ";
    list1.display();

    std::cout << "Cloned list: ";
    clonedList.display();

    LinkedList mergedList = list1 + list2;
    std::cout << "Merged list: ";
    mergedList.display();

    LinkedList commonList = list1 * list2;
    std::cout << "Common elements list: ";
    commonList.display();

    return 0;
}