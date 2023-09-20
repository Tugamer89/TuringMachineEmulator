# Turing Machine Emulator

This is a C++ program that emulates a Turing Machine. It can read a program description from a file and operate on a memory tape based on the program's instructions.

## Features

- Emulates a Turing Machine with a configurable program and memory.
- Supports custom program and memory tape files.
- Provides detailed execution information for debugging purposes (enable with `_DEBUG`).

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++ or Visual Studio)
- Git (optional, for cloning the repository)

### Installation

1. Clone this repository (if you haven't already):

    ```bash
    git clone https://github.com/Tugamer89/TuringMachineEmulator.git
    cd TuringMachineEmulator
    ```

2. Compile the program:

    ```bash
    g++ -o turing-machine main.cpp
    ```

### Usage

To run the Turing Machine emulator, execute the compiled program with the desired program and memory tape files:

```bash
./turing-machine program.tm memory.mem
```

Replace `program.tm` and `memory.mem` with your program and memory tape file paths.

### Program Description
The program file (`program.tm`) contains instructions for the Turing Machine. It follows a specific format:

```
# Comment lines start with a hash (#) symbol and are ignored.

# Initial configuration line:
<current_status> <initial_memory_index> -

# Transition rules:
<current_status> <current_value> <new_status> <new_value> <move_direction>
```

- `<current_status>`: The current state of the Turing Machine.
- `<initial_memory_index>`: The initial index of the memory tape.
- `<current_value>`: The current value at the tape head.
- `<new_status>`: The new state to transition to.
- `<new_value>`: The new value to write to the tape.
- `<move_direction>`: The direction to move the tape head (`<`, `>`, or `-` for left, right, or stay, respectively).

## Contributing
Contributions are welcome! If you find any issues or have improvements to suggest, please open an issue or create a pull request.

## License

This project is open-source and available under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code for your purposes. See the [LICENSE](LICENSE) file for more details about the MIT License.

## Acknowledgments
- Special thanks to Alan Turing for pioneering the concept of Turing Machines and their significance in the field of computer science.
