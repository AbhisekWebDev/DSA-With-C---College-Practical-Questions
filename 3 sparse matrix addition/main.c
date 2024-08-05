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

// Function to add two sparse matrices
Node* addSparseMatrices(Node* mat1, Node* mat2) {
    Node* result = NULL;

    while (mat1 != NULL && mat2 != NULL) {
        if (mat1->row < mat2->row || (mat1->row == mat2->row && mat1->col < mat2->col)) {
            insertNode(&result, mat1->row, mat1->col, mat1->value);
            mat1 = mat1->next;
        } else if (mat1->row > mat2->row || (mat1->row == mat2->row && mat1->col > mat2->col)) {
            insertNode(&result, mat2->row, mat2->col, mat2->value);
            mat2 = mat2->next;
        } else {
            int sum = mat1->value + mat2->value;
            if (sum != 0) {
                insertNode(&result, mat1->row, mat1->col, sum);
            }
            mat1 = mat1->next;
            mat2 = mat2->next;
        }
    }

    while (mat1 != NULL) {
        insertNode(&result, mat1->row, mat1->col, mat1->value);
        mat1 = mat1->next;
    }

    while (mat2 != NULL) {
        insertNode(&result, mat2->row, mat2->col, mat2->value);
        mat2 = mat2->next;
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
    insertNode(&mat1, 0, 1, 5);
    insertNode(&mat1, 1, 2, 8);
    insertNode(&mat1, 2, 0, 3);

    Node* mat2 = NULL;
    insertNode(&mat2, 0, 1, 6);
    insertNode(&mat2, 1, 2, 7);
    insertNode(&mat2, 2, 1, 4);

    Node* result = addSparseMatrices(mat1, mat2);
    printf("Sum: ");
    printSparseMatrix(result);

    // Free memory
    freeSparseMatrix(mat1);
    freeSparseMatrix(mat2);
    freeSparseMatrix(result);

    return 0;
}
