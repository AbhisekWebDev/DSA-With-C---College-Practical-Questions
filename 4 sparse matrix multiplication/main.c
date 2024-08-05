#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the sparse matrix linked list
typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int row, int col, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node in sorted order (by row, then by column)
void insertNode(Node** head, int row, int col, int value) {
    Node* newNode = createNode(row, col, value);
    if (*head == NULL || (*head)->row > row || ((*head)->row == row && (*head)->col > col)) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && (current->next->row < row || (current->next->row == row && current->next->col < col))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to multiply two sparse matrices
Node* multiplySparseMatrices(Node* mat1, Node* mat2, int mat2Cols) {
    Node* result = NULL;

    for (Node* ptr1 = mat1; ptr1 != NULL; ptr1 = ptr1->next) {
        for (Node* ptr2 = mat2; ptr2 != NULL; ptr2 = ptr2->next) {
            if (ptr1->col == ptr2->row) {
                int newRow = ptr1->row;
                int newCol = ptr2->col;
                int newValue = ptr1->value * ptr2->value;
                insertNode(&result, newRow, newCol, newValue);
            }
        }
    }

    // Combine terms with the same (row, col)
    Node* current = result;
    while (current != NULL) {
        Node* runner = current;
        while (runner->next != NULL) {
            if (runner->next->row == current->row && runner->next->col == current->col) {
                current->value += runner->next->value;
                Node* temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }

    return result;
}

// Function to print a sparse matrix
void printSparseMatrix(Node* head) {
    while (head != NULL) {
        printf("(%d, %d, %d) ", head->row, head->col, head->value);
        head = head->next;
    }
    printf("\n");
}

// Function to free the memory allocated for a sparse matrix
void freeSparseMatrix(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Example usage
int main() {
    Node* mat1 = NULL;
    insertNode(&mat1, 0, 0, 1);
    insertNode(&mat1, 0, 1, 2);
    insertNode(&mat1, 1, 0, 3);
    insertNode(&mat1, 1, 1, 4);

    Node* mat2 = NULL;
    insertNode(&mat2, 0, 0, 5);
    insertNode(&mat2, 0, 1, 6);
    insertNode(&mat2, 1, 0, 7);
    insertNode(&mat2, 1, 1, 8);

    Node* result = multiplySparseMatrices(mat1, mat2, 2);
    printf("Product: ");
    printSparseMatrix(result);

    // Free memory
    freeSparseMatrix(mat1);
    freeSparseMatrix(mat2);
    freeSparseMatrix(result);

    return 0;
}
