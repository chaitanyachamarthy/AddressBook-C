# Address Book Management System in C

A console-based contact management application developed in **C**. The project supports creating, searching, editing, deleting, and listing contacts, with data saved to a CSV file so contacts can be loaded again when the application restarts.

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/chaitanyachamarthy/AddressBook-C?quickstart=1)

## Features

- **Create contacts** with a name, phone number, and email address.
- **Search contacts** to find existing records.
- **Edit contacts** to update stored information.
- **Delete contacts** that are no longer needed.
- **List contacts** with options to sort by name, phone number, or email address.
- **Validate input** using dedicated functions for names, phone numbers, and email addresses.
- **Save and load contacts** using `contacts.csv`.

## Technologies and concepts

- **Language:** C
- **Data structures:** Structures and arrays of structures
- **File handling:** Standard C file I/O and CSV text storage
- **Modular programming:** Separate source and header files
- **Other concepts:** Input validation, function pointers for comparison, sorting, and string handling

## Project structure

```text
AddressBook-C/
├── main.c          # Entry point and menu-driven interface
├── contact.c       # Contact operations, validation, and sorting
├── contact.h       # Contact structures, constants, and declarations
├── file.c          # Saving and loading contacts
├── file.h          # File operation declarations
├── contacts.csv     # Sample or saved contact records
├── .gitignore       # Files excluded from version control
└── README.md        # Project documentation
```

## Getting started

### Prerequisites

Install a C compiler such as GCC.

### Compile

From the project directory, run:

```bash
gcc -Wall -Wextra main.c contact.c file.c -o addressbook
```

### Run

On Windows (PowerShell):

```powershell
.\addressbook.exe
```

On Linux or macOS:

```bash
./addressbook
```

Run the program from the project directory because it reads and writes `contacts.csv` using a relative file path.

## Main menu

```text
==============================
         Address Book
==============================
1. Create Contact
2. Search Contacts
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Save & Exit
------------------------------
Enter your choice:
```

Choose an option to perform a contact operation. Select **6. Save & Exit** to save the current contacts to `contacts.csv` and exit.

## How it works

The application uses a `Contact` structure containing the name, phone number, and email address. An `AddressBook` structure holds an array of contacts and the current contact count. The configured capacity is **100 contacts** (`MAX_CONTACTS`).

`main.c` handles the menu and dispatches user choices to functions in `contact.c`. The application uses dedicated validation functions for contact fields. When listing contacts, comparison functions support sorting by different fields. The file-handling functions in `file.c` load and save contact records in CSV format.

## Data storage

Contact records are stored in `contacts.csv` as comma-separated fields:

```csv
Alex Kumar,9876543210,alex@example.com
Priya Shah,9123456780,priya@example.com
```

These are fictional example records. Avoid committing real people's contact information to a public repository.

## Scope and limitations

- Console-based application; no graphical interface.
- Supports up to 100 contacts using a fixed-size array.
- Uses a simple CSV representation rather than a database or a full CSV parsing library.
- Designed as a C programming and file-handling project.

## Learning outcomes

This project provided hands-on practice with modular C programming, structures, arrays, string manipulation, validation logic, sorting, and persistent file storage. It also highlighted the importance of handling invalid input, file errors, and array capacity limits.

## Author

**Chaitanya Chamarthy**
