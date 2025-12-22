# 🌟 Lumina Compiler: AST Tree Visualizer
![logo](assets/logo.svg)
Lumina is a native C++ compiler project. This stage of the project implements a Recursive Descent Parser and a high-fidelity terminal visualizer that mimics the Linux `tree` utility to display the Abstract Syntax Tree (AST).

## 🏗️ Technical Architecture

* **Lexer:** A cursor-based state machine that transforms source text into a token stream ($O(n)$ complexity).
* **Parser:** A hand-written Recursive Descent engine that enforces language grammar.
* **AST Nodes:** A polymorphic hierarchy using `std::unique_ptr` for automated memory management on aarch64 systems.
* **Logging:** Integrated with `spdlog` for real-time diagnostic reporting.

## 🌲 Tree Visualization Logic

The visualizer uses a recursive visitor pattern to draw the AST in the console. It utilizes Unicode box-drawing characters and ANSI color codes to provide a "Proper Compiler" debugging experience.



### Node Representation:
* **[VarDecl] (Green):** Represents variable initialization statements (`let`).
* **[Literal] (Blue):** Represents raw numeric data within an expression.
* **Branching:** Uses `├──` for intermediate nodes and `└──` for terminal leaf nodes.

## 🚀 Build & Execution

### Prerequisites:
* C++17 or higher.
* `spdlog` and `fmt` libraries installed.
* CMake build system.

### Steps:
1.  **Generate Build Files:**
    ```bash
    cmake -B build
    ```
2.  **Compile:**
    ```bash
    cmake --build build --target Lumina
    ```
3.  **Run:**
    ```bash
    ./build/Lumina
    ```

## 🛠️ Usage Example

Input:
`let x = 50;`

Output:
```text
AST Visualizer:
└── [VarDecl] name: x
    └── [Literal] value: 50