#include <stdio.h>
#include <string.h>
typedef struct Transaction {
    char type[10];
    float amount;
    struct Transaction* next;
} Transaction;

Transaction* head = NULL;
void addTransaction();
float calculateNetCashFlow();
void deleteTransaction();
void displayTransactions();
void freeTransactions();

int main() {
    int choice;

    do {
        printf("\nSimple Cash Flow Management\n");
        printf("1. Add Transaction\n");
        printf("2. Calculate Net Cash Flow\n");
        printf("3. Delete Last Transaction\n");
        printf("4. View All Transactions\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                printf("Net Cash Flow: %.2f\n", calculateNetCashFlow());
                break;
            case 3:
                deleteTransaction();
                break;
            case 4:
                displayTransactions();
                break;
            case 5:
                printf("Exiting program...\n");
                freeTransactions();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void addTransaction() {
    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));

    if (newTransaction == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter transaction type (Income/Expense): ");
    scanf("%s", newTransaction->type);
    if (strcmp(newTransaction->type, "income") != 0 && strcmp(newTransaction->type, "expense") != 0) {
        printf("Invalid transaction type. Please enter 'Income' or 'Expense'.\n");
        free(newTransaction);
        return;
    }

    printf("Enter amount: ");
    scanf("%f", &newTransaction->amount);

    newTransaction->next = head;
    head = newTransaction;

    printf("Transaction added successfully!\n");
}
float calculateNetCashFlow() {
    float netCashFlow = 0;
    Transaction* current = head;

    while (current != NULL) {
        if (strcmp(current->type, "income") == 0) {
            netCashFlow += current->amount;
        } else if (strcmp(current->type, "expense") == 0) {
            netCashFlow -= current->amount;
        }
        current = current->next;
    }

    return netCashFlow;
}
void deleteTransaction() {
    if (head == NULL) {
        printf("No transactions to delete.\n");
        return;
    }

    Transaction* temp = head;
    head = head->next;
    printf("Deleted transaction: %s of %.2f\n", temp->type, temp->amount);
    free(temp);
}
void displayTransactions() {
    if (head == NULL) {
        printf("No transactions recorded.\n");
        return;
    }

    printf("\nTransaction History:\n");
    Transaction* current = head;
    while (current != NULL) {
        printf("%s: %.2f\n", current->type, current->amount);
        current = current->next;
    }
}
void freeTransactions() {
    Transaction* current = head;
    while (current != NULL) {
        Transaction* temp = current;
        current = current->next;
        free(temp);
    }
}


