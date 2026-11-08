#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// AI assistance: OpenAI ChatGPT.
// Prompt: "Provide a C++ worked implementation of the CodeLab II
// Book Manager challenge using a Book class, file handling,
// a menu, book searches, borrowing and returning."

class Book {
private:
    std::string title;
    std::string author;
    int pages;
    std::string id;
    bool borrowed;

public:
    Book(std::string t, std::string a, int p,
         std::string i, bool b)
        : title(t), author(a), pages(p), id(i), borrowed(b) {}

    std::string getID() const {
        return id;
    }

    bool isBorrowed() const {
        return borrowed;
    }

    void setBorrowed(bool status) {
        borrowed = status;
    }

    void display() const {
        std::cout << "\nTitle: " << title
                  << "\nAuthor: " << author
                  << "\nPages: " << pages
                  << "\nID: " << id
                  << "\nStatus: "
                  << (borrowed ? "Borrowed" : "Available")
                  << "\n";
    }

    std::string toFileString() const {
        return title + "," + author + "," +
               std::to_string(pages) + "," + id + "," +
               (borrowed ? "true" : "false");
    }
};
// Load books from the provided file
std::vector<Book> loadBooks(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << "\n";
        return books;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string title, author, pages, id, status;

        if (!std::getline(ss, title, ',') ||
            !std::getline(ss, author, ',') ||
            !std::getline(ss, pages, ',') ||
            !std::getline(ss, id, ',') ||
            !std::getline(ss, status)) {
            continue;
        }

        try {
            int pageCount = std::stoi(pages);

            if (pageCount <= 0 ||
                (status != "true" && status != "false")) {
                continue;
            }

            books.emplace_back(title, author, pageCount,
                               id, status == "true");
        }
        catch (const std::exception&) {
            std::cerr << "Skipping invalid book record.\n";
        }
    }

    return books;
}
// Save updated book information
bool saveBooks(const std::vector<Book>& books,
               const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot save book data.\n";
        return false;
    }
    for (const Book& book : books) {
        file << book.toFileString() << "\n";
    }
    file.close();
    return file.good();
}
// Search for a book using its ID
Book* findBook(std::vector<Book>& books,
               const std::string& id) {
    for (Book& book : books) {
        if (book.getID() == id) {
            return &book;
        }
    }
    return nullptr;
}
int main() {
    const std::string filename = "bookData.txt";
    std::vector<Book> books = loadBooks(filename);

    if (books.empty()) {
        std::cerr << "No books loaded. Check bookData.txt.\n";
        return 1;
    }
    std::string choice;
    while (true) {
        std::cout << "\n===== LIBRARY BOOK MANAGER =====\n";
        std::cout << "1. View all books\n";
        std::cout << "2. View individual book\n";
        std::cout << "3. Borrow a book\n";
        std::cout << "4. Return a book\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        if (!std::getline(std::cin, choice)) {
            break;
        }
        if (choice == "1") {
            for (const Book& book : books) {
                book.display();
            }
        }
        else if (choice == "2" ||
                 choice == "3" || choice == "4") {
            std::string id;
            std::cout << "Enter book ID: ";
            std::getline(std::cin, id);

            Book* book = findBook(books, id);

            if (book == nullptr) {
                std::cout << "Book not found.\n";
                continue;
            }

            if (choice == "2") {
                book->display();
            }
            else if (choice == "3") {
                if (book->isBorrowed()) {
                    std::cout << "Book is already borrowed.\n";
                }
                else {
                    book->setBorrowed(true);

                    if (saveBooks(books, filename)) {
                        std::cout << "Book borrowed successfully.\n";
                    } else {
                        std::cout << "Warning: Changes not saved.\n";
                    }
                }
            }
            else {
                if (!book->isBorrowed()) {
                    std::cout << "Book is already available.\n";
                }
                else {
                    book->setBorrowed(false);

                    if (saveBooks(books, filename)) {
                        std::cout << "Book returned successfully.\n";
                    } else {
                        std::cout << "Warning: Changes not saved.\n";
                    }
                }
            }
        }
        else if (choice == "5") {
            std::cout << "Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid option. Try again.\n";
        }
    }
    return 0;
}