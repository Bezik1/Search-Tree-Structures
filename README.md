# 🌳 Search Tree Structure

## 💡 Overview

This project implements a self-balancing binary search tree known as the Red-Black Tree (RBT).
The goal of the project is to provide an efficient data structure supporting logarithmic time complexity for insertion, deletion, and lookup operations.

The implementation is written in modern C++ with focus on:
• correctness of the Red-Black Tree invariants
• performance and memory efficiency
• clear separation between the core data structure and testing utilities

The project also includes unit tests and automatically generated documentation.

## ⚙️ Building Commands

```bash
# Initialize build directory
cmake -S . -B build

# Builds project
cmake --build build --target main

# Run project
./build/main

# Builds tests
cmake --build build --target tests

# Run tests
./build/tests
```

## 📚 Documentation

Generate Documentation Template

```bash
# Generates documentation
doxygen -g

# Updates documentation
doxygen

# Run documentation
./docs/html/index.html
```

## 🔧 Git Hooks

The repository supports custom Git hooks for development automation.

```bash
# Enables git hooks
chmod u+x .git/hooks/*
```

## 🛠 Technologies

<p align="center">
    <a href="https://skillicons.dev">
        <img src="https://skillicons.dev/icons?i=cpp,vscode,github,git,cmake" />
    </a>
</p>
