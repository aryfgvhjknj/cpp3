# Library Management System

A console-based C++17 library management system for books, members, and borrowing records.

## Features

- Add books with title and author
- Register library members
- List books and members
- Search books by title or author, case-insensitively
- Issue available books to registered members
- Return issued books
- Validate missing records and invalid borrowing states

## Build and Run

### Windows with MinGW g++

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o library.exe
.\library.exe
```

### Linux or macOS

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o library
./library
```

Data is stored in memory for the current run and is reset when the application exits.
