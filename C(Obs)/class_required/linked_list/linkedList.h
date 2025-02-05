#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
    namespace linked_list{
        struct node{
                wchar_t data;
                node* prev;
                node* next;
            };

        // 仅仅支持wchar_t类型
        class linkedList{
            private:
                node* head;
                node* tail;
            public:
                linkedList(wchar_t = '\0');
                ~linkedList();

                bool elemExist(wchar_t) const;
                unsigned int elemCount(wchar_t) const;

                bool insert(wchar_t = '\0');

                bool replaceF(wchar_t, wchar_t);//第一个是目标元素，第二个是要替换的元素

                bool deleteNode();//删除末位元素
                bool deleteFNode(wchar_t);//删除第一个与元素匹配的节点
                bool deleteLNode(wchar_t);//删除最后一个与元素匹配的节点
                void deleteANode(wchar_t);//删除所有与元素匹配的节点

                //void walkTheList();遍历链表(弃用)

                friend std::ostream& operator<<(std::ostream&,const linkedList&);

                //TODO:排序
        };
    };
#endif