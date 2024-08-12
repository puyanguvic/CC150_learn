#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Book {
public:
    Book(std::string id, std::string title, std::string author, std::string content)
        : m_id(id), m_title(title), m_author(author), m_content(content) {}

    std::string getId() const { return m_id; }
    std::string getTitle() const { return m_title; }
    std::string getAuthor() const { return m_author; }
    std::string getContent() const { return m_content; }

private:
    std::string m_id;
    std::string m_title;
    std::string m_author;
    std::string m_content;
};

class User {
public:
    User(std::string id, std::string name, std::string email)
        : m_id(id), m_name(name), m_email(email) {}

    std::string getId() const { return m_id; }
    std::string getName() const { return m_name; }
    std::string getEmail() const { return m_email; }

private:
    std::string m_id;
    std::string m_name;
    std::string m_email;
};

class Library {
public:
    void addBook(const Book& book) {
        m_books[book.getId()] = book;
    }

    Book* getBook(const std::string& bookId) {
        auto it = m_books.find(bookId);
        return it != m_books.end() ? &(it->second) : nullptr;
    }

    std::vector<Book*> searchBooks(const std::string& query) {
        // 实现搜索逻辑
        std::vector<Book*> results;
        for (auto& pair : m_books) {
            if (pair.second.getTitle().find(query) != std::string::npos ||
                pair.second.getAuthor().find(query) != std::string::npos) {
                results.push_back(&pair.second);
            }
        }
        return results;
    }

private:
    std::unordered_map<std::string, Book> m_books;
};

class UserManager {
public:
    void addUser(const User& user) {
        m_users[user.getId()] = user;
    }

    User* getUser(const std::string& userId) {
        auto it = m_users.find(userId);
        return it != m_users.end() ? &(it->second) : nullptr;
    }

private:
    std::unordered_map<std::string, User> m_users;
};

class Display {
public:
    void showBook(const Book& book) {
        std::cout << "Title: " << book.getTitle() << std::endl;
        std::cout << "Author: " << book.getAuthor() << std::endl;
        std::cout << "Content: " << book.getContent() << std::endl;
    }

    void showUser(const User& user) {
        std::cout << "Name: " << user.getName() << std::endl;
        std::cout << "Email: " << user.getEmail() << std::endl;
    }
};

class ReadingSession {
public:
    ReadingSession(User* user, Book* book)
        : m_user(user), m_book(book), m_currentPage(0) {}

    void nextPage() {
        // 实现翻到下一页的逻辑
        m_currentPage++;
    }

    void previousPage() {
        // 实现翻到上一页的逻辑
        if (m_currentPage > 0) m_currentPage--;
    }

    int getCurrentPage() const { return m_currentPage; }

private:
    User* m_user;
    Book* m_book;
    int m_currentPage;
};

class OnlineReaderSystem {
public:
    OnlineReaderSystem() : m_activeUser(nullptr), m_activeBook(nullptr) {}

    void setActiveUser(User* user) { m_activeUser = user; }
    void setActiveBook(Book* book) { m_activeBook = book; }

    User* getActiveUser() const { return m_activeUser; }
    Book* getActiveBook() const { return m_activeBook; }

    void displayActiveBook() {
        if (m_activeBook) {
            m_display.showBook(*m_activeBook);
        } else {
            std::cout << "No active book" << std::endl;
        }
    }

    void displayActiveUser() {
        if (m_activeUser) {
            m_display.showUser(*m_activeUser);
        } else {
            std::cout << "No active user" << std::endl;
        }
    }

    Library& getLibrary() { return m_library; }
    UserManager& getUserManager() { return m_userManager; }

private:
    Library m_library;
    UserManager m_userManager;
    Display m_display;
    User* m_activeUser;
    Book* m_activeBook;
};

int main() {
    OnlineReaderSystem system;

    // 添加用户
    system.getUserManager().addUser(User("1", "John Doe", "john@example.com"));
    system.getUserManager().addUser(User("2", "Jane Smith", "jane@example.com"));

    // 添加书籍
    system.getLibrary().addBook(Book("101", "The Great Gatsby", "F. Scott Fitzgerald", "Content of The Great Gatsby..."));
    system.getLibrary().addBook(Book("102", "To Kill a Mockingbird", "Harper Lee", "Content of To Kill a Mockingbird..."));

    // 设置活跃用户和书籍
    system.setActiveUser(system.getUserManager().getUser("1"));
    system.setActiveBook(system.getLibrary().getBook("101"));

    // 显示当前用户和书籍
    system.displayActiveUser();
    system.displayActiveBook();

    // 搜索书籍
    std::vector<Book*> searchResults = system.getLibrary().searchBooks("Kill");
    std::cout << "Search results for 'Kill':" << std::endl;
    for (const auto& book : searchResults) {
        std::cout << book->getTitle() << " by " << book->getAuthor() << std::endl;
    }

    return 0;
}