/*
日期类包括年、月、日。
作者类author，其数据成员包括姓名、年龄和写作时间。
书类book，其数据包括书号、书名、定价、出版社、出版时间和作者。
设计类及相关操作，实现书的管理操作如添加、删除、查询、列表显示等。 
*/
#include<iostream>
#include<string>
#include<type_traits>
#include<algorithm>
#include<list>


struct Date {
    short int year {2000}, month {1}, day {1};
    Date() = default;
    template<typename T1, typename T2, typename T3>
    Date(T1&& _year, T2&& _month, T3&& _day)
        : year(std::forward<T1>(_year)),
        month(std::forward<T2>(_month)),
        day(std::forward<T3>(_day)) {
        static_assert(std::is_same_v<std::decay_t<T1>, short int>, "Year must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T2>, short int>, "Month must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T3>, short int>, "Day must be of type short int");
    }
};
std::ostream& operator<<(std::ostream& os, const Date& date) {
    return os << date.year << "-" << date.month << "-" << date.day;
}
std::istream& operator>>(std::istream& is, Date& date) {
    is >> date.year >> date.month >> date.day;
    return is;
}
struct Author {
    std::string name {"unknown"};
    short int age {0};
    Date date;
    Author() = default;
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    Author(T1&& _name, T2&& _age, T3&& _year, T4&& _month, T5&& _day, T6&& _date)
        : name(std::forward<T1>(_name)),
          age(std::forward<T2>(_age)),
          date(std::forward<T3>(_year), std::forward<T4>(_month), std::forward<T5>(_day)) {
        static_assert(std::is_same_v<std::decay_t<T1>, std::string>, "Name must be of type std::string");
        static_assert(std::is_same_v<std::decay_t<T2>, short int>, "Age must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T3>, short int>, "Year must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T4>, short int>, "Month must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T5>, short int>, "Day must be of type short int");
    }
};
std::ostream& operator<<(std::ostream& os, const Author& author) {
    return os << "Author[" << author.name << ", " << author.age << " year old ], started at " << author.date;
}
std::istream& operator>>(std::istream& is, Author& author) {
    return is >> author.name >> author.age >> author.date;
}
struct Book {
    int id {0}; // 书号？
    std::string name {"unknown"};
    double price {0.0};
    std::string publisher {"unknown"};
    Date publish_date;
    Author author;
    Book() = default;
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    Book(T1&& _id, T2&& _name, T3&& _price, T4&& _publisher, T5&& _year, T6&& _month, T7&& _day, T8&& _author_name, T9&& _author_age, T10&& _author_date)
        : id(std::forward<T1>(_id)),
          name(std::forward<T2>(_name)),
          price(std::forward<T3>(_price)),
          publisher(std::forward<T4>(_publisher)),
          publish_date(std::forward<T5>(_year), std::forward<T6>(_month), std::forward<T7>(_day)),
          author(std::forward<T8>(_author_name), std::forward<T9>(_author_age), std::forward<T10>(_author_date)) {
        static_assert(std::is_same_v<std::decay_t<T1>, int>, "ID must be of type int");
        static_assert(std::is_same_v<std::decay_t<T2>, std::string>, "Name must be of type std::string");
        static_assert(std::is_same_v<std::decay_t<T3>, double>, "Price must be of type double");
        static_assert(std::is_same_v<std::decay_t<T4>, std::string>, "Publisher must be of type std::string");
        static_assert(std::is_same_v<std::decay_t<T5>, short int>, "Year must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T6>, short int>, "Month must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T7>, short int>, "Day must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T8>, std::string>, "Author name must be of type std::string");
        static_assert(std::is_same_v<std::decay_t<T9>, short int>, "Author age must be of type short int");
        static_assert(std::is_same_v<std::decay_t<T10>, Date>, "Author date must be of type Date");
    }
};
std::ostream& operator<<(std::ostream& os, const Book& book) {
    return os << book.id << ":\n"
              << book.name << "\n"
              << book.author << "\n"
              << book.publisher << "released at" << book.publish_date << "\n"
              << book.price << "USD\n";
}
std::istream& operator>>(std::istream& is, Book& book) {
    return is >> book.id >> book.name >> book.author >> book.publisher >> book.publish_date >> book.price;
}

class BookShelfAdmin{
    private:
        std::list<Book> books;
    public:
        BookShelfAdmin() = default;
        BookShelfAdmin(const BookShelfAdmin&) = delete;
        BookShelfAdmin& operator=(BookShelfAdmin&) = delete;

        void display_books() const{
            for(auto& book : books){
                std::cout << book <<std::endl;
            }
        }
        bool add_book_from_tui() {
            static Book TempBook;
            std::cout << "Enter Book Here:"
                << R"(
                例如，你应该这样写：
                    book.id >> book.name 
                    >> book.author (author.name >> author.age >> author.date [ year >> month >> day ] )
                    >> book.publisher 
                    >> book.publish_date  (year >>  month >> day)
                    >> book.price;
)";
            if(std::cin >> TempBook){
                add_book(TempBook);
                return true;
            }
            return false;
        }
        bool find_book_according_name(std::string name ,Book** Result ){
            for(auto& book : books){
                if(book.name == name){
                    std::cout << book << std::endl;
                    *Result = &book;
                    return true;
                }
            }
            return false;
        }
        bool find_book_according_id(int id, Book** Result) {
            for (auto& book : books) {
                if (book.id == id) {
                    std::cout << book << std::endl;
                    *Result = &book;
                    return true;
                }
            }
            return false;
        }
        void remove_book_according_name(std::string name){
            auto it = std::find_if(books.begin(), books.end(), [&name](const Book& book) {
                return book.name == name;
            });
            if (it != books.end()) {
                books.erase(it);
            }
        }
        void remove_book_according_id(int id) {
            auto it = std::find_if(books.begin(), books.end(), [id](const Book& book) {
                return book.id == id;
            });
            if (it != books.end()) {
                books.erase(it);
            }
        } 
    protected:
        void add_book(Book& book){
            books.emplace_back(std::move(book));//空间不够应该会抛出异常
        }
};

int main(){
    BookShelfAdmin admin;
    while(admin.add_book_from_tui());
    admin.display_books();
    admin.remove_book_according_id(1);
    admin.display_books();
}