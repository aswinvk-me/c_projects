# Address Book

A simple command-line address book application written in C.  
It supports creating, searching, editing, deleting and listing contacts and persists data to a CSV file (`contacts.csv`).

This project is intended as a small, educational CLI program demonstrating basic file I/O, string handling and simple validation in C.

---

## Features

- Create a new contact (Name, Phone, Email)
- Search contacts by name, phone or email
- Edit contact fields (name, phone, email)
- Delete contacts
- List all contacts in a neat table
- Save/load contacts to/from `contacts.csv`

---

## Project structure

- `main.c` — Program entrypoint and menu loop
- `contact.h` / `contact.c` — Contact and address-book logic (create, search, edit, delete, list, validation)
- `file.h` / `file.c` — File persistence (save/load to `contacts.csv`)
- `populate.h` / `populate.c` — Helper to pre-fill the address book with dummy contacts (optional)
- `contacts.csv` — Example/data file used to persist contacts
- `a.out` — Compiled binary (if present). Should not be committed to source control.

---

## Requirements

- C compiler (gcc or clang recommended)
- POSIX / Unix-like environment recommended for the build commands shown
- No external libraries required

---

## Build

Compile all source files into an executable (example uses gcc):

```bash
# from AddressBook-NewDesign directory
gcc main.c contact.c file.c populate.c -o addressbook
```

Notes:
- You can omit `populate.c` if you don't want the populate helper compiled in.
- The repository currently includes a prebuilt `a.out`; it's recommended to build your own executable and remove committed binaries.

---

## Run

```bash
./addressbook
```

When launched, the program displays a menu:

- 1 → Create contact
- 2 → Search contact
- 3 → Edit contact
- 4 → Delete contact
- 5 → List all contacts
- 6 → Save contacts (and exit)
- 7 → Exit

When you choose to save (option 6) the program writes to `contacts.csv`. Exiting with option 7 will not auto-save — use option 6 to persist changes.

---

## Data persistence and CSV format

The program reads/writes `contacts.csv` in the working directory.

Expected format used by the program:

- First line: number of contacts (integer)
- Second line: CSV header (Name,Phone,Email)
- Next lines: contacts as `Name,Phone,Email`

Example `contacts.csv`:

```csv
2
Name,Phone,Email
aswin chandra,1234567890,siwn@gmail.com
Adidas,8888888888,sdf@gmail.com
```

The program uses `fscanf` with format `"%[^,],%[^,],%[^\n]\n"` to parse each contact line.

---

## Validation rules

- Phone:
  - Must be exactly 10 characters long
  - All characters must be digits
  - Must be unique among contacts

- Email:
  - Must contain the '@' character
  - Must have at least one character before '@'
  - Must contain `.com` and `.com` must be at the end of the email
  - Local part (before '@') must be lowercase only (program enforces no uppercase)
  - Must be unique among contacts

If validation fails, the program will print an error and prompt again.

---

## Usage examples

Create a contact:
- Choose menu option 1
- Enter full name (press Enter)
- Enter phone (digits only, 10 digits)
- Enter email (lowercase, must end with `.com`)

Search:
- Choose option 2, then select search by name/number/email and provide search term.

Edit:
- Choose option 3, perform a search to get matching results, then enter the serial number displayed to edit the correct contact.

Delete:
- Choose option 4, perform a search to pick the contact then confirm deletion.

List:
- Choose option 5 to display all stored contacts.

Save:
- Choose option 6 to write the in-memory contacts to `contacts.csv` and exit the program.

---


## Aswinvk-me

- Repo: https://github.com/aswinvk-me/c_projects
