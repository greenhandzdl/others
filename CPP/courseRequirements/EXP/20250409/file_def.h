#ifndef FILE_DEF_H
#define FILE_DEF_H

#include <cstdint>
#include <iostream>


namespace FILE_DEF {
    constexpr char DESTINATION[] = "ST1.DAT";
    constexpr int32_t BOOK_ID = 6;
    constexpr int32_t BOOK_NAME_LENGTH = 12;
    constexpr int32_t BOOK_Author = 8;
    struct Book{
        char BookID[BOOK_ID+1];
        char BookName[BOOK_NAME_LENGTH+1];
        char BookAuthor[BOOK_Author+1];
        double BookPrice;
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
        friend std::istream& operator>>(std::istream& is, Book& book);
    };
    
    
};
#endif