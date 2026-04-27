# Inventory Management System — Stack (LIFO)

A terminal-based inventory manager written in C. Stock batches are managed using a **Stack (LIFO)** built on a dynamically allocated singly linked list — no fixed array size, just pointers.

---

## Features

- **Push** — add a new stock batch (ID, name, quantity) to the top
- **Pop** — dispatch and remove the most recently added batch
- **Peek** — inspect the top batch without touching the stack
- **Display All** — list every batch from newest to oldest
- **Clean exit** — frees every heap-allocated node before closing

---

## Why a Stack for Inventory?

The newest batch sits on top and is the first to be dispatched. That's LIFO by definition. Push and pop both run in O(1) since the stack always operates at the head of the linked list — no traversal needed.

```
TOP     →  [ Batch C | Apples  | 200 ]
           [ Batch B | Oranges | 150 ]
BOTTOM  →  [ Batch A | Mangoes | 300 ]
```

A new delivery gets pushed on top. A dispatch pops from the top. The list grows and shrinks dynamically with no upper limit.

---

## How to Compile and Run

**Compile**
```bash
gcc -Wall -Wextra -std=c11 -o inventory inventory.c
```

**Run on Linux / macOS**
```bash
./inventory
```

**Run on Windows (MinGW)**
```bash
inventory.exe
```

---

## Project Structure

```
inventory-management-stack/
├── inventory.c
└── README.md
```
