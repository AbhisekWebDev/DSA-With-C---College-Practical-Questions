#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the polynomial linked list
typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node in the polynomial linked list
void insertNode(Node** poly, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    newNode->next = *poly;
    *poly = newNode;
}

// Function to multiply two polynomials
Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    for (Node* p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (Node* p2 = poly2; p2 != NULL; p2 = p2->next) {
            int coeff = p1->coeff * p2->coeff;
            int exp = p1->exp + p2->exp;
            insertNode(&result, coeff, exp);
        }
    }

    return result;
}

// Function to print a polynomial
void printPolynomial(Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to free the memory allocated for a polynomial
void freePolynomial(Node* poly) {
    Node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

// Example usage
int main() {
    Node* poly1 = createNode(5, 2);
    poly1->next = createNode(4, 1);
    poly1->next->next = createNode(2, 0);

    Node* poly2 = createNode(5, 1);
    poly2->next = createNode(5, 0);

    Node* result = multiplyPolynomials(poly1, poly2);
    printf("Product: ");
    printPolynomial(result);

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
