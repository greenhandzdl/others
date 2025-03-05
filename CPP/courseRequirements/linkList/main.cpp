#include <iostream>
#include <stdexcept>

/**
 * @brief 双向链表模板类
 * @tparam T 链表元素类型
 */
template<typename T>
class LinkList {
private:
    /**
     * @brief 链表节点内部类
     */
    class Node {
    private:
        T data;         // 节点存储的数据
        Node* prev;     // 前驱节点指针
        Node* next;     // 后继节点指针
        
    public:
        /**
         * @brief 节点构造函数
         * @param data 节点数据
         * @param prev 前驱节点指针（默认nullptr）
         * @param next 后继节点指针（默认nullptr）
         */
        Node(T data, Node* prev = nullptr, Node* next = nullptr) 
            : data(data), prev(prev), next(next) {}

        // 数据访问接口
        T& getData() { return data; }                ///< 获取可修改的数据引用
        const T& getData() const { return data; }    ///< 获取只读数据引用

        // 指针操作接口
        Node* getNext() { return next; }             ///< 获取后继节点指针
        const Node* getNext() const { return next; } ///< 获取只读后继节点指针
        void setNext(Node* newNext) { next = newNext; }

        Node* getPrev() { return prev; }             ///< 获取前驱节点指针
        const Node* getPrev() const { return prev; } ///< 获取只读前驱节点指针
        void setPrev(Node* newPrev) { prev = newPrev; }
    };

    // 链表属性
    Node* head = nullptr; ///< 链表头节点指针
    Node* tail = nullptr; ///< 链表尾节点指针
    int count = 0;        ///< 链表元素计数器

    /**
     * @brief 清空链表所有元素
     */
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
    public:
    // 构造/析构函数
    LinkList() = default; ///< 默认构造函数

    /**
     * @brief 单元素初始化构造函数
     * @param data 初始化元素
     */
    explicit LinkList(const T& data) {
        head = new Node(data);
        tail = head;
        count = 1;
    }

    ~LinkList() { clear(); } ///< 析构函数

    // 拷贝控制成员
    LinkList(const LinkList& other) { ///< 拷贝构造函数
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

    LinkList(LinkList&& other) noexcept { ///< 移动构造函数
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = other.tail = nullptr;
        other.count = 0;
    }

    LinkList& operator=(const LinkList& other) { ///< 拷贝赋值运算符
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

    LinkList& operator=(LinkList&& other) noexcept { ///< 移动赋值运算符
        if (this == &other) return *this;

        clear();

        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = other.tail = nullptr;
        other.count = 0;
        return *this;
    }

    // 基础功能接口
    int getCount() const { return count; }  ///< 获取元素数量
    bool isEmpty() const { return head == nullptr; } ///< 判断链表是否为空

    /**
     * @brief 检查元素是否存在
     * @param data 要查找的元素
     * @return true 元素存在
     */
    bool isExisted(const T& data) const {
        for (auto it = cbegin(); it != cend(); ++it) {
            if (*it == data) return true;
        }
        return false;
    }

    /**
     * @brief 修改元素值
     * @param oldData 要修改的元素值
     * @param newData 新的元素值
     * @return true 修改成功
     */
    bool modify(const T& oldData, const T& newData) {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == oldData) {
                *it = newData;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 在链表尾部添加元素
     * @param data 要添加的元素
     * @return true 添加成功
     */
    bool pushBack(const T& data) {
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

    /**
     * @brief 在链表头部插入元素
     * @param data 要插入的元素
     * @return true 插入成功
     */
    bool pushFront(const T& data) {
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
    /**
     * @brief 在链表尾部删除元素
     * @return true 删除成功
     */
    bool popBack() {
        if (isEmpty()) return false;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            --count;
            return true;
        }else{
            Node* temp = tail;
            tail = tail->getPrev();
            delete temp;
            tail->setNext(nullptr);
            --count;
            return true;
        }
        return false;
    }
    /**
     * @brief 删除头部元素
     * @return true 删除成功
     */
    bool popFront() {
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

    /**
     * @brief 迭代器类（非常量版本）
     */
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

        /**
         * @brief 在当前节点后插入新元素
         * @param data 要插入的数据
         * @return true 插入成功
         */
        bool insertAfter(const T& data) {
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

        /**
         * @brief 删除当前节点的下一个节点
         * @return true 删除成功
         */
        bool deleteNext() {
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

        /**
         * @brief 修改当前节点数据
         * @param newData 新数据
         * @return true 修改成功
         */
        bool modify(const T& newData) {
            if (!current) return false;
            current->getData() = newData;
            return true;
        }

        /**
         * @brief 从当前节点开始查找元素
         * @param data 要查找的数据
         * @return 找到的节点迭代器，未找到返回end()
         */
        Iterator find(const T& data) {
            Iterator it = *this;
            while (it != list->end()) {
                if (*it == data) return it;
                ++it;
            }
            return list->end();
        }
    };

    /**
     * @brief 常量迭代器类
     */
    class ConstIterator {
        const Node* current;
    public:
        explicit ConstIterator(const Node* node) : current(node) {}

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

    // 迭代器访问方法
    Iterator begin() { return Iterator(head, this); }        ///< 获取起始迭代器
    Iterator end() { return Iterator(nullptr, this); }      ///< 获取结束迭代器
    Iterator rbegin() { return Iterator(tail, this); }      ///< 获取反向起始迭代器
    Iterator rend() { return Iterator(nullptr, this); }     ///< 获取反向结束迭代器

    ConstIterator cbegin() const { return ConstIterator(head); }  ///< 常量起始迭代器
    ConstIterator cend() const { return ConstIterator(nullptr); } ///< 常量结束迭代器
    ConstIterator begin() const { return cbegin(); }         ///< 常量版本迭代器
    ConstIterator end() const { return cend(); }             ///< 常量版本结束迭代器

    /**
     * @brief 打印链表内容（调试用）
     */
    void print() const {
        for (auto it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief 重载输出运算符
     */
    friend std::ostream& operator<<(std::ostream& os, const LinkList<T>& list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            os << *it << " ";
        }
        return os;
    }
};

int main() {
    LinkList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    std::cout << "Forward traversal: " << list << std::endl;

    std::cout << "Backward traversal: ";
    for (auto it = list.rbegin(); it != list.rend(); --it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    list.modify(2, 20);
    std::cout << "After modification: " << list << std::endl;

    list.popFront();
    std::cout << "After deletion: " << list << std::endl;

    LinkList<int> list2 = list;
    std::cout << "Copied list: " << list2 << std::endl;

    LinkList<int> list3 = std::move(list);
    std::cout << "Moved list: " << list3 << std::endl;
    std::cout << "Original list empty? " << std::boolalpha << list.isEmpty() << std::endl;

    return 0;
}