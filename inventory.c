#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 64

// Single inventory batch node
typedef struct Node {
    int id;
    char name[MAX_NAME];
    int qty;
    struct Node *next;
} Node;

// Stack using linked list top pointer
typedef struct {
    Node *top;
    int size;
} Stack;

void stack_init(Stack *s) {
    s->top = NULL;
    s->size = 0;
}

// Push: add new batch on top
void push(Stack *s, int id, const char *name, int qty) {
    Node *n = malloc(sizeof(Node));
    if (!n) { fprintf(stderr, "Memory error.\n"); return; }
    n->id = id;
    strncpy(n->name, name, MAX_NAME - 1);
    n->name[MAX_NAME - 1] = '\0';
    n->qty = qty;
    n->next = s->top;
    s->top = n;
    s->size++;
}

// Pop: remove and show top batch
void pop(Stack *s) {
    if (!s->top) { printf("Stack is empty.\n"); return; }
    Node *rem = s->top;
    s->top = rem->next;
    s->size--;
    printf("\nDispatched:\n");
    printf("  ID       : %d\n", rem->id);
    printf("  Item     : %s\n", rem->name);
    printf("  Quantity : %d\n", rem->qty);
    free(rem);
}

// Peek: view top batch without removing
void peek(const Stack *s) {
    if (!s->top) { printf("Stack is empty.\n"); return; }
    printf("\nLatest stock (top):\n");
    printf("  ID       : %d\n", s->top->id);
    printf("  Item     : %s\n", s->top->name);
    printf("  Quantity : %d\n", s->top->qty);
}

// Display all batches from newest to oldest
void display_all(const Stack *s) {
    if (!s->top) { printf("Stack is empty.\n"); return; }
    printf("\nAll stock (%d batch%s) - newest to oldest:\n",
           s->size, s->size == 1 ? "" : "es");
    Node *cur = s->top;
    int pos = 1;
    while (cur) {
        printf("  [%d] ID: %d | %s | Qty: %d\n", pos, cur->id, cur->name, cur->qty);
        cur = cur->next;
        pos++;
    }
}

// Free all nodes before exit
void free_stack(Stack *s) {
    Node *cur = s->top;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    s->top = NULL;
    s->size = 0;
}

// Read a valid integer from stdin
int read_int(const char *prompt) {
    int val; char buf[64];
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%d", &val) == 1)
            return val;
        printf("Invalid input. Enter a whole number.\n");
    }
}

// Read a non-empty string from stdin
void read_str(const char *prompt, char *dest, int max) {
    while (1) {
        printf("%s", prompt);
        if (fgets(dest, max, stdin)) {
            dest[strcspn(dest, "\n")] = '\0';
            if (strlen(dest) > 0) return;
        }
        printf("Name cannot be empty.\n");
    }
}

void print_menu(int size) {
    printf("\n========================================\n");
    printf("  Inventory Management  |  Batches: %d\n", size);
    printf("========================================\n");
    printf("  1. Add New Stock       (Push)\n");
    printf("  2. Dispatch Stock      (Pop)\n");
    printf("  3. View Latest Stock   (Peek)\n");
    printf("  4. Display All Stock\n");
    printf("  5. Exit\n");
    printf("========================================\n");
}

int main(void) {
    Stack inv;
    stack_init(&inv);

    int choice, id, qty;
    char name[MAX_NAME];

    do {
        print_menu(inv.size);
        choice = read_int("Choice: ");

        switch (choice) {
            case 1:
                printf("\n-- Add Stock --\n");
                id  = read_int("Item ID   : ");
                read_str("Item Name : ", name, MAX_NAME);
                qty = read_int("Quantity  : ");
                if (qty <= 0) { printf("Quantity must be positive.\n"); break; }
                push(&inv, id, name, qty);
                printf("Stock added.\n");
                break;

            case 2:
                pop(&inv);
                break;

            case 3:
                peek(&inv);
                break;

            case 4:
                display_all(&inv);
                break;

            case 5:
                free_stack(&inv);
                printf("Memory freed. Goodbye.\n");
                break;

            default:
                printf("Invalid choice. Enter 1-5.\n");
        }

    } while (choice != 5);

    return 0;
}
