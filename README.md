# Library Management System

A console-based Library Management System built in C, featuring book management, student waitlists, transaction history, and persistent data storage using a hash table, queue, and stack data structures.

---

## Features

| Feature | Description |
|---------|-------------|
| Add Book | Add new books with ID, title, and author |
| Display All Books | View the complete library catalog |
| Search by ID | Find a book using its unique ID |
| Search by Title | Find a book using its title |
| Issue Book | Issue a book to a student with due date |
| Return Book | Return an issued book with fine calculation |
| Display Issued Books | View all currently issued books |
| Waitlist | Add students to a waitlist for unavailable books |
| Transaction History | View complete issue/return history (stack-based) |
| Last N Transactions | View recent transactions |
| Save & Exit | Persist data to `library.dat` |

---

## Data Structures Used

| Structure | File | Purpose |
|-----------|------|---------|
| **Hash Table** | `hash.c` / `hash.h` | Fast O(1) book lookup by ID |
| **Linked List** | `book.c` / `book.h` | Collision handling in hash table |
| **Queue** | `queue.c` / `queue.h` | Student waitlist management |
| **Stack** | `stack.c` / `stack.h` | LIFO transaction history |

---

## File Structure




---

## Prerequisites

- **GCC Compiler** (MinGW for Windows)
- **Make** (optional, for using Makefile)
- **Git** (for version control)

---

## Compilation

### Using Make (Linux/Mac/MinGW)
```bash
make



===== LIBRARY MANAGEMENT SYSTEM =====
1.  Add Book
2.  Display All Books
3.  Search Book by ID
4.  Search Book by Title
5.  Issue Book
6.  Return Book
7.  Display Issued Books
8.  Add to Waitlist
9.  Display Waitlist
10. View Transaction History
11. View Last N Transactions
12. Save and Exit


Enter choice: 1
Enter Book ID: 101
Enter Title: The C Programming Language
Enter Author: Dennis Ritchie

Enter choice: 5
Enter Book ID to issue: 101
Enter Student ID: 1001
Enter Student Name: Alice
Enter Due Date (YYYY-MM-DD): 2026-06-20
Book issued successfully.

Enter choice: 12
Goodbye!

