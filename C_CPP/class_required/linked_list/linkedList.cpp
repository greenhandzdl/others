#include "linkedList.h"
#include<iostream>
namespace linked_list{
    linkedList::linkedList(wchar_t udata){
        head = new node;
        head->data = udata;
        head->prev = nullptr;
        head->next = nullptr;
        tail = head;
    }

    linkedList::~linkedList(){
        //head实际上是当前链表的头结点，所以需要一个临时指针来指向下一个结点，
        node* temp = head;
        while(temp != nullptr){
            temp = temp->next;
            delete head;
            head = temp;
        }
    }
    
    bool linkedList::elemExist(wchar_t udata) const{
        using std::cout;
        using std::endl;
        node* temp = head;
        while(temp != nullptr){
            if(temp->data == udata){
                cout << "The element " << udata << " exists in the list." << endl;
                return true;
            }
            temp = temp->next;
        }
        cout << "The element " << udata << " does not exist in the list." << endl;
        return false;
    }
    
    unsigned int linkedList::elemCount(wchar_t udata) const{
        using std::cout;
        using std::endl;
        unsigned int count = 0;
        node* cur = head;
        while(cur != nullptr){
            if(cur->data == udata){
                count++;
            }
            cur = cur->next;
        }
        cout << "There are " << count << " " << udata << " in the list." << endl;
        return count;
    }

    bool linkedList::insert(wchar_t udata){
        try {
            tail->next = new node;

        } catch (std::bad_alloc& e) {
            std::cerr << "内存分配失败: " << e.what() << std::endl;
            return false;
        }
        tail->next->prev = tail;
        tail->next->data = udata;
        tail->next->next = nullptr;
        tail = tail->next;
        return true;
    }

    bool linkedList::replaceF(wchar_t sdata,wchar_t target){
        node* temp = head;
        while(temp){
            if(temp->data == sdata){
                temp->data = target;
                return true;
            }
            temp = temp->next;
        }
        return false;

    }

    bool linkedList::deleteNode(){
        if(tail->prev){
            tail->prev->next = nullptr;
            delete tail;
            tail = tail->prev;
            return true;
        }else{
            return false;
        }
    }

    bool linkedList::deleteFNode(wchar_t udata){
        using std::cout;
        using std::endl;
        node* temp = head;
        while(true){
            if(temp->data == udata){
                cout << "Element found" << endl;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                return true;
            }
            else if(temp->next == nullptr){
                cout << "There is no " << udata << " in the list." << endl;
                return false;
            }
        }
    }
    bool linkedList::deleteLNode(wchar_t udata){
        using std::cout;
        using std::endl;
        node* temp = head;
        node* temp2 = nullptr;
        while(temp != nullptr){
            if(temp->data == udata){
                temp2 = temp;
            }
            temp = temp->next;
        }
        if(!temp2){
            cout << "There is no " << udata << " in the list." << endl;
            return false;
        }else{
            temp2->prev->next = temp2->next;
            temp2->next->prev = temp2->prev;
            delete temp2;
            return true;
        }
    }

    void linkedList::deleteANode(wchar_t udata){
        node* temp = head;
        while(temp){
            if(temp->data == udata){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                return;
            }
            temp = temp->next;
        }
    }
    

    std::ostream& operator<<(std::ostream& os,const linkedList& ll){
        using std::cout;
        using std::endl;
        node* cur = ll.head;
        while(cur != nullptr){
            os << (wchar_t)cur->data << " ";
            cur = cur->next;
        }
        return os;
    }
};