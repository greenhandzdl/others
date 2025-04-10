#include "file_def.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace FILE_DEF {
    std::ostream& operator<<(std::ostream& os, const FILE_DEF::Book& book) {
        os << std::setw(BOOK_ID) << std::left << book.BookID << " "
           << std::setw(BOOK_NAME_LENGTH) << std::left << book.BookName  << " "
           << std::setw(BOOK_Author) << std::left << book.BookAuthor << " "
           << std::fixed << std::setprecision(2) << book.BookPrice;
        return os;
    }

    std::istream& operator>>(std::istream& is, FILE_DEF::Book& book) {
        is >>  book.BookID
        >>  book.BookName 
        >> book.BookAuthor 
        >>  book.BookPrice;
        return is;
    }
}