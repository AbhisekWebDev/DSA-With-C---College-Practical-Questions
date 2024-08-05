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

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node** lastPtrRef = &result;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            *lastPtrRef = createNode(poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            *lastPtrRef = createNode(poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sumCoeff = poly1->coeff + poly2->coeff;
            if (sumCoeff != 0) {
                *lastPtrRef = createNode(sumCoeff, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        if (*lastPtrRef != NULL) {
            lastPtrRef = &((*lastPtrRef)->next);
        }
    }

    while (poly1 != NULL) {
        *lastPtrRef = createNode(poly1->coeff, poly1->exp);
        poly1 = poly1->next;
        lastPtrRef = &((*lastPtrRef)->next);
    }

    while (poly2 != NULL) {
        *lastPtrRef = createNode(poly2->coeff, poly2->exp);
        poly2 = poly2->next;
        lastPtrRef = &((*lastPtrRef)->next);
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

    Node* result = addPolynomials(poly1, poly2);
    printf("Sum: ");
    printPolynomial(result);

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
