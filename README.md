=====================================================
STUDENT GRADEBOOK SYSTEM: INSTRUCTIONS AND GUIDE
=====================================================


-----------------------------------------------------
PART 1: BUILD AND RUN INSTRUCTIONS
-----------------------------------------------------


### A. How to Build (Compile)

1.  **Placement:** Make sure all .c, .h, and the 'Makefile' are in the same directory.
2.  **Terminal:** Open your command-line interface (terminal, bash, etc.) and navigate to that directory.
3.  **Command:** Execute the following commands to compile the project:

    make clean
    make

    * The **make** command links all source files (main.c, storage.c, sort.c, stats.c, student.c) and creates the executable file named **gradebook**.

### B. How to Run

After a successful build, run the program from the same directory:

1.  **Default Run:** Uses the default data file, **gradebook.csv**.
    ./gradebook

2.  **Custom File:** Use a specific file name for loading/saving data.
    ./gradebook [your_file_name.csv]

    * The program will automatically attempt to load data from the specified file on startup.

-----------------------------------------------------
PART 2: USAGE AND INPUT FORMATS
-----------------------------------------------------

### A. Interactive Menu Commands

This program uses single-character commands in the main loop:

| Command | Description |
| :--- | :--- |
| **a** | **Add** a new student record. |
| **f** | **Find** a student by ID. |
| **u** | **Update** an existing student record. |
| **d** | **Delete** a student record. |
| **l** | **List** all students currently in memory. |
| **s** | **Sort** students (prompts for sorting by ID, Name, or Average). |
| **t** | **Show Statistics** (class averages, min/max). |
| **w** | **Save** the current data to the configured file. |
| **r** | **Load** data from the file, replacing current memory. |
| **q** | **Quit** the program (prompts to save if changes were made). |

### B. Data File (CSV) Format

This program uses a CSV (Comma Separated Values) format for persistent storage.

**Record Structure (Strict):** `[ID],"[Name]",[Score 1],[Score 2],[Score 3]`

* Name fields must be enclosed in quotes (`" "`).
* Scores must be numeric (double-precision floating point).

Example:
1001,"Alice Johnson",85.50,92.00,88.50
1002,"Bob Smith",78.00,82.50,80.00

-----------------------------------------------------
PART 3: KNOWN LIMITATIONS (CONSTRAINTS)
-----------------------------------------------------

1.  **Maximum Capacity:** The database is limited to a maximum of **1000 students** (`MAX_STUDENTS`).
2.  **Number of Scores:** Each student record is fixed to only **3 scores** (score1, score2, score3).
3.  **Name Length:** Student names are limited to **63 characters** (`MAX_NAME_LEN` is 64, including the null terminator).
4.  **Score Range:** All scores must be between **0.0 and 100.0**. Scores outside this range are rejected during data validation.
5.  **Data Persistence:** Saving is done via **Atomic Write** (write to .tmp then rename) to prevent file corruption.

-----------------------------------------------------
PART 4: WORK BREAKDOWN / CONTRIBUTOR MAP
-----------------------------------------------------

| Member | Module | Files | Primary Features/Functions |
| :--- | :--- | :--- | :--- |
| **Yoon** | Student Module | `student.c`, `student.h` | Data model, student validation, CSV parsing/formatting, average calculation. |
| **Justin** | Sort Module | `sort.c`, `sort.h` | Implementation of Insertion Sort algorithm (by ID, Name, Avg). |
| **Andrew**| Storage Module | `storage.c`, `storage.h` | File I/O (load/save), Atomic Write safety implementation. |
| **Jerry** | Stats Module | `stats.c`, `stats.h` | Computation and printing of class statistics (averages, min/max). |
| **All** | Main UI/Logic | `main.c` | Program loop, menu display, command handling (Add, Find, Update, Delete, List). |
