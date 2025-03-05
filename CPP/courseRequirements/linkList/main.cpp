#include <iostream>
#include <stdexcept>

template<typename T>
class LinkList {
private:
    class Node {
    private:
        T data;
        Node* prev;
        Node* next;
    public:
        Node(T data, Node* prev = nullptr, Node* next = nullptr) 
            : data(data), prev(prev), next(next) {}

        // 返回可修改的引用（非const版本）
        T& getData() { return data; }
        
        // 返回只读的常量引用（const版本）
        const T& getData() const { return data; }

        Node* getNext() { return next; }
        const Node* getNext() const { return next; }
        void setNext(Node* newNext) { next = newNext; }

        Node* getPrev() { return prev; }
        const Node* getPrev() const { return prev; }
        void setPrev(Node* newPrev) { prev = newPrev; }
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

    void clear() {
        while (!isEmpty()) {
            Delete();
        }
    }

public:
    LinkList() = default;

    LinkList(const T& data) {
        head = new Node(data);
        tail = head;
        count = 1;
    }

    ~LinkList() {
        clear();
    }

    LinkList(const LinkList& other) {
        if (other.isEmpty()) {
            head = tail = nullptr;
            count = 0;
        } else {
            head = new Node(other.head->getData());
            Node* current = head;
            const Node* otherCurrent = other.head->getNext();
            while (otherCurrent) {
                current->setNext(new Node(otherCurrent->getData(), current));
                current = current->getNext();
                otherCurrent = otherCurrent->getNext();
            }
            tail = current;
            count = other.count;
        }
    }

    LinkList(LinkList&& other) noexcept {
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = other.tail = nullptr;
        other.count = 0;
    }

    LinkList& operator=(const LinkList& other) {
        if (this == &other) return *this;

        clear();

        if (!other.isEmpty()) {
            head = new Node(other.head->getData());
            Node* current = head;
            const Node* otherCurrent = other.head->getNext();
            while (otherCurrent) {
                current->setNext(new Node(otherCurrent->getData(), current));
                current = current->getNext();
                otherCurrent = otherCurrent->getNext();
            }
            tail = current;
            count = other.count;
        }
        return *this;
    }

    LinkList& operator=(LinkList&& other) noexcept {
        if (this == &other) return *this;

        clear();

        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = other.tail = nullptr;
        other.count = 0;
        return *this;
    }

    int getCount() const { return count; }
    bool isEmpty() const { return head == nullptr; }

    bool isExisted(const T& data) const {
        for (auto it = cbegin(); it != cend(); ++it) {
            if (*it == data) return true;
        }
        return false;
    }

    bool Modify(const T& oldData, const T& newData) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == oldData) {
                *it = newData;
                return true;
            }
        }
        return false;
    }

    bool Add(const T& data) {
        if (isEmpty()) {
            head = new Node(data);
            tail = head;
        } else {
            Node* newNode = new Node(data, tail);
            tail->setNext(newNode);
            tail = newNode;
        }
        ++count;
        return true;
    }

    bool push_back(const T& data) {
        if (isEmpty()) {
            head = new Node(data);
            tail = head;
        } else {
            Node* newNode = new Node(data, tail);
            tail->setNext(newNode);
            tail = newNode;
        }
        ++count;
        return true;
    }

    bool push_front(const T& data) {
        if (isEmpty()) {
            head = new Node(data);
            tail = head;
        } else {
            Node* newNode = new Node(data, nullptr, head);
            head->setPrev(newNode);
            head = newNode;
        }
        ++count;
        return true;
    }

    bool Delete() {
        if (isEmpty()) return false;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->getNext();
            head->setPrev(nullptr);
            delete temp;
        }
        --count;
        return true;
    }

    class Iterator {
        Node* current;
        LinkList<T>* list;
    public:
        Iterator(Node* node, LinkList<T>* list) : current(node), list(list) {}

        T& operator*() const {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return current->getData();
        }

        Iterator& operator++() {
            if (current) current = current->getNext();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            if (current) current = current->getPrev();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

        bool Add(const T& data) {
            if (!current) return false;

            Node* newNode = new Node(data, current, current->getNext());
            if (current->getNext()) {
                current->getNext()->setPrev(newNode);
            }
            current->setNext(newNode);

            if (current == list->tail) {
                list->tail = newNode;
            }
            ++list->count;
            return true;
        }

        bool Delete() {
            if (!current || !current->getNext()) return false;

            Node* temp = current->getNext();
            current->setNext(temp->getNext());
            if (temp->getNext()) {
                temp->getNext()->setPrev(current);
            }
            if (temp == list->tail) {
                list->tail = current;
            }
            delete temp;
            --list->count;
            return true;
        }

        bool Modify(const T& newData) {
            if (!current) return false;
            current->setData(newData);
            return true;
        }

        Iterator Find(const T& data) {
            Iterator it = *this;
            while (it != list->end()) {
                if (*it == data) return it;
                ++it;
            }
            return list->end();
        }
    };

    class ConstIterator {
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}

        const T& operator*() const {
            if (!current) throw std::runtime_error("Dereferencing null iterator");
            return current->getData();
        }

        ConstIterator& operator++() {
            if (current) current = current->getNext();
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        ConstIterator& operator--() {
            if (current) current = current->getPrev();
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ConstIterator& other) const { return current == other.current; }
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }
    };

    Iterator begin() { return Iterator(head, this); }
    Iterator end() { return Iterator(nullptr, this); }
    Iterator rbegin() { return Iterator(tail, this); }
    Iterator rend() { return Iterator(nullptr, this); }

    ConstIterator cbegin() const { return ConstIterator(head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }
    ConstIterator begin() const { return cbegin(); }
    ConstIterator end() const { return cend(); }

    void Print() const {
        for (auto it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkList<T>& list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            os << *it << " ";
        }
        return os;
    }
};

int main() {
    LinkList<int> list;
    list.Add(1);
    list.Add(2);
    list.Add(3);
    std::cout << "Forward traversal: " << list << std::endl;

    std::cout << "Backward traversal: ";
    for (auto it = list.rbegin(); it != list.rend(); --it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    list.Modify(2, 20);
    std::cout << "After modification: " << list << std::endl;

    list.Delete();
    std::cout << "After deletion: " << list << std::endl;

    LinkList<int> list2 = list;
    std::cout << "Copied list: " << list2 << std::endl;

    LinkList<int> list3 = std::move(list);
    std::cout << "Moved list: " << list3 << std::endl;
    std::cout << "Original list empty? " << std::boolalpha << list.isEmpty() << std::endl;

    return 0;
}