# Assignment: cw2


The program is built and managed using a Makefile, which automates the compilation and cleanup tasks.

---

## Prerequisites

- **C++ Compiler**: Ensure `g++` is installed.
- **Make Utility**: Verify that `make` is available in your environment.
- **Input File**: Provide a valid input file (e.g., `input1.txt`).

---

## Build Instructions

To build the project, follow these steps:

1. **Clean Previous Builds**: Run `make deepclean` to remove object files and temporary data.
2. **Compile the Project**: Use `make` to build the application.

Example command sequence:
```bash
make deepclean && make && clear
```

---

## Running the Application

After successfully building the project, execute the program as follows:

```bash
./main <input_file>
```

For example:
```bash
./main input1.txt
```

---
