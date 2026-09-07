#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Book {
    int id{};
    std::string title;
    std::string author;
    bool issued{false};
    int borrowerId{-1};
};

struct Member {
    int id{};
    std::string name;
    std::string email;
};

class Library {
public:
    void run() {
        std::cout << "\n=== Library Management System ===\n";
        bool running = true;
        while (running) {
            printMenu();
            switch (readInt("Choose an option: ")) {
            case 1:
                addBook();
                break;
            case 2:
                addMember();
                break;
            case 3:
                listBooks();
                break;
            case 4:
                listMembers();
                break;
            case 5:
                searchBooks();
                break;
            case 6:
                issueBook();
                break;
            case 7:
                returnBook();
                break;
            case 0:
                running = false;
                std::cout << "Goodbye.\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
            }
        }
    }

private:
    std::vector<Book> books;
    std::vector<Member> members;
    int nextBookId{1};
    int nextMemberId{1};

    static std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        return value;
    }

    static int readInt(const std::string& prompt) {
        while (true) {
            std::string input = readLine(prompt);
            try {
                std::size_t position = 0;
                int value = std::stoi(input, &position);
                if (position == input.size()) {
                    return value;
                }
            } catch (const std::exception&) {
            }
            std::cout << "Please enter a valid number.\n";
        }
    }

    static std::string lower(std::string value) {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char character) {
            return static_cast<char>(std::tolower(character));
        });
        return value;
    }

    Book* findBook(int id) {
        for (Book& book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr;
    }

    Member* findMember(int id) {
        for (Member& member : members) {
            if (member.id == id) {
                return &member;
            }
        }
        return nullptr;
    }

    void addBook() {
        std::string title = readLine("Title: ");
        std::string author = readLine("Author: ");
        if (title.empty() || author.empty()) {
            std::cout << "Title and author are required.\n";
            return;
        }

        books.push_back({nextBookId++, title, author});
        std::cout << "Book added with ID " << books.back().id << ".\n";
    }

    void addMember() {
        std::string name = readLine("Member name: ");
        std::string email = readLine("Email: ");
        if (name.empty() || email.empty()) {
            std::cout << "Name and email are required.\n";
            return;
        }

        members.push_back({nextMemberId++, name, email});
        std::cout << "Member registered with ID " << members.back().id << ".\n";
    }

    void listBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }

        std::cout << "\nBooks\n-----\n";
        for (const Book& book : books) {
            std::cout << "ID: " << book.id << " | " << book.title << " by " << book.author
                      << " | " << (book.issued ? "Issued" : "Available");
            if (book.issued) {
                std::cout << " to member " << book.borrowerId;
            }
            std::cout << '\n';
        }
    }

    void listMembers() const {
        if (members.empty()) {
            std::cout << "No members registered.\n";
            return;
        }

        std::cout << "\nMembers\n-------\n";
        for (const Member& member : members) {
            std::cout << "ID: " << member.id << " | " << member.name << " | " << member.email << '\n';
        }
    }

    void searchBooks() const {
        std::string query = lower(readLine("Search title or author: "));
        if (query.empty()) {
            std::cout << "Search text is required.\n";
            return;
        }

        bool found = false;
        for (const Book& book : books) {
            if (lower(book.title).find(query) != std::string::npos ||
                lower(book.author).find(query) != std::string::npos) {
                if (!found) {
                    std::cout << "\nSearch results\n--------------\n";
                }
                found = true;
                std::cout << "ID: " << book.id << " | " << book.title << " by " << book.author
                          << " | " << (book.issued ? "Issued" : "Available") << '\n';
            }
        }
        if (!found) {
            std::cout << "No matching books found.\n";
        }
    }

    void issueBook() {
        if (books.empty() || members.empty()) {
            std::cout << "Add at least one book and one member before issuing.\n";
            return;
        }

        int bookId = readInt("Book ID: ");
        Book* book = findBook(bookId);
        if (book == nullptr) {
            std::cout << "Book not found.\n";
            return;
        }
        if (book->issued) {
            std::cout << "That book is already issued.\n";
            return;
        }

        int memberId = readInt("Member ID: ");
        Member* member = findMember(memberId);
        if (member == nullptr) {
            std::cout << "Member not found.\n";
            return;
        }

        book->issued = true;
        book->borrowerId = member->id;
        std::cout << "Book issued to " << member->name << ".\n";
    }

    void returnBook() {
        int bookId = readInt("Book ID to return: ");
        Book* book = findBook(bookId);
        if (book == nullptr) {
            std::cout << "Book not found.\n";
            return;
        }
        if (!book->issued) {
            std::cout << "That book is already available.\n";
            return;
        }

        book->issued = false;
        book->borrowerId = -1;
        std::cout << "Book returned successfully.\n";
    }

    static void printMenu() {
        std::cout << "\n1. Add book\n"
                  << "2. Register member\n"
                  << "3. List books\n"
                  << "4. List members\n"
                  << "5. Search by title or author\n"
                  << "6. Issue book\n"
                  << "7. Return book\n"
                  << "0. Exit\n";
    }
};

int main() {
    Library library;
    library.run();
    return 0;
}
