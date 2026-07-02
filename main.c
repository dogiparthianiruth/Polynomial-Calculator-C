#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

typedef struct Node {
    double coeff;
    int exp;
    struct Node *next;
} Node;

Node *createNode(double coeff, int exp) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

int isZero(double x) {
    return fabs(x) < EPS;
}

void freePoly(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

Node *clonePoly(Node *head) {
    Node *copy = NULL, *tail = NULL;

    while (head) {
        Node *node = createNode(head->coeff, head->exp);
        if (!copy)
            copy = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
        head = head->next;
    }
    return copy;
}

void insertTerm(Node **head, double coeff, int exp) {
    if (isZero(coeff))
        return;

    Node *prev = NULL, *cur = *head;

    while (cur && cur->exp > exp) {
        prev = cur;
        cur = cur->next;
    }

    if (cur && cur->exp == exp) {
        cur->coeff += coeff;

        if (isZero(cur->coeff)) {
            if (prev)
                prev->next = cur->next;
            else
                *head = cur->next;

            free(cur);
        }
    } else {
        Node *newNode = createNode(coeff, exp);
        newNode->next = cur;

        if (prev)
            prev->next = newNode;
        else
            *head = newNode;
    }
}

void displayPoly(Node *head) {
    if (!head) {
        printf("0");
        return;
    }

    int first = 1;

    while (head) {
        double c = head->coeff;
        int e = head->exp;
        double absC = fabs(c);

        if (!first)
            printf(c > 0 ? " + " : " - ");
        else if (c < 0)
            printf("-");

        if (e == 0 || !isZero(absC - 1.0))
            printf("%.2lf", absC);

        if (e > 0) {
            printf("x");
            if (e > 1)
                printf("^%d", e);
        }

        first = 0;
        head = head->next;
    }
}

Node *readPolynomial() {
    Node *poly = NULL;
    int n;

    printf("Enter number of terms: ");

    if (scanf("%d", &n) != 1) {
        while (getchar() != '\n');
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        double coeff;
        int exp;

        printf("Term %d (coeff exp): ", i + 1);

        if (scanf("%lf %d", &coeff, &exp) == 2)
            insertTerm(&poly, coeff, exp);
    }

    return poly;
}

Node *addPoly(Node *p1, Node *p2) {
    Node *result = clonePoly(p1);

    while (p2) {
        insertTerm(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

Node *subtractPoly(Node *p1, Node *p2) {
    Node *result = clonePoly(p1);

    while (p2) {
        insertTerm(&result, -p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

Node *multiplyPoly(Node *p1, Node *p2) {
    Node *result = NULL;

    for (Node *a = p1; a; a = a->next)
        for (Node *b = p2; b; b = b->next)
            insertTerm(&result, a->coeff * b->coeff, a->exp + b->exp);

    return result;
}

Node *derivativePoly(Node *p) {
    Node *result = NULL;

    while (p) {
        if (p->exp != 0)
            insertTerm(&result, p->coeff * p->exp, p->exp - 1);

        p = p->next;
    }

    return result;
}

double evaluatePoly(Node *p, double x) {
    double result = 0;

    while (p) {
        result += p->coeff * pow(x, p->exp);
        p = p->next;
    }

    return result;
}

Node *dividePoly(Node *dividend, Node *divisor, Node **remainderOut) {
    if (!divisor) {
        printf("Error: Division by zero polynomial.\n");
        *remainderOut = NULL;
        return NULL;
    }

    Node *quotient = NULL;
    Node *remainder = clonePoly(dividend);

    while (remainder && remainder->exp >= divisor->exp) {
        double qCoeff = remainder->coeff / divisor->coeff;
        int qExp = remainder->exp - divisor->exp;

        insertTerm(&quotient, qCoeff, qExp);

        for (Node *d = divisor; d; d = d->next)
            insertTerm(&remainder, -(qCoeff * d->coeff), qExp + d->exp);
    }

    *remainderOut = remainder;
    return quotient;
}

int main() {
    Node *P1 = NULL, *P2 = NULL;
    int choice;

    while (1) {
        printf("\n--- Polynomial Calculator ---\n");
        printf("1. Enter P1\n");
        printf("2. Enter P2\n");
        printf("3. Display\n");
        printf("4. Add\n");
        printf("5. Subtract\n");
        printf("6. Multiply\n");
        printf("7. Divide\n");
        printf("8. Derivative of P1\n");
        printf("9. Evaluate P1\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                freePoly(P1);
                P1 = readPolynomial();
                break;

            case 2:
                freePoly(P2);
                P2 = readPolynomial();
                break;

            case 3:
                printf("P1: ");
                displayPoly(P1);
                printf("\nP2: ");
                displayPoly(P2);
                printf("\n");
                break;

            case 4: {
                Node *res = addPoly(P1, P2);
                printf("Result: ");
                displayPoly(res);
                printf("\n");
                freePoly(res);
                break;
            }

            case 5: {
                Node *res = subtractPoly(P1, P2);
                printf("Result: ");
                displayPoly(res);
                printf("\n");
                freePoly(res);
                break;
            }

            case 6: {
                Node *res = multiplyPoly(P1, P2);
                printf("Result: ");
                displayPoly(res);
                printf("\n");
                freePoly(res);
                break;
            }

            case 7: {
                Node *rem = NULL;
                Node *quo = dividePoly(P1, P2, &rem);

                if (P2) {
                    printf("Quotient: ");
                    displayPoly(quo);
                    printf("\nRemainder: ");
                    displayPoly(rem);
                    printf("\n");
                }

                freePoly(quo);
                freePoly(rem);
                break;
            }

            case 8: {
                Node *res = derivativePoly(P1);
                printf("Derivative: ");
                displayPoly(res);
                printf("\n");
                freePoly(res);
                break;
            }

            case 9: {
                double x;
                printf("Enter x: ");
                scanf("%lf", &x);
                printf("P1(%.2lf) = %.2lf\n", x, evaluatePoly(P1, x));
                break;
            }

            case 0:
                freePoly(P1);
                freePoly(P2);
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}