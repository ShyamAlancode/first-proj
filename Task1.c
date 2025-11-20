#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    char name[50];
    char author[50];
    int qty;
};

struct Borrower {
    int id;
    char name[50];
    int bookId;
    char due[15];
};

void addBook() {
    FILE *fp = fopen("books.dat", "ab");
    struct Book b;

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Book Name: ");
    scanf(" %[^\n]", b.name);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.qty);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("\nBook Added Successfully!\n");
}

void viewBooks() {
    FILE *fp = fopen("books.dat", "rb");
    struct Book b;

    printf("\n%-10s %-25s %-20s %-5s\n", "ID", "Name", "Author", "Qty");
    printf("---------------------------------------------------------------\n");

    while (fread(&b, sizeof(b), 1, fp))
        printf("%-10d %-25s %-20s %-5d\n", b.id, b.name, b.author, b.qty);

    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("books.dat", "rb");
    struct Book b;
    char find[50];
    int found = 0;

    printf("\nEnter Book Name to Search: ");
    scanf(" %[^\n]", find);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (strcasecmp(b.name, find) == 0) {
            printf("\nBook Found!\nID: %d\nAuthor: %s\nQuantity: %d\n",
                   b.id, b.author, b.qty);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nBook Not Found!\n");
    fclose(fp);
}

void deleteBook() {
    FILE *fp = fopen("books.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Book b;
    int id, found = 0;

    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id)
            fwrite(&b, sizeof(b), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("books.dat");
    rename("temp.dat", "books.dat");

    if (found) printf("\nBook Deleted Successfully!\n");
    else printf("\nBook Not Found!\n");
}

void addBorrower() {
    FILE *fp = fopen("borrowers.dat", "ab");
    struct Borrower br;

    printf("\nEnter Borrower ID: ");
    scanf("%d", &br.id);
    printf("Enter Borrower Name: ");
    scanf(" %[^\n]", br.name);
    printf("Enter Book ID: ");
    scanf("%d", &br.bookId);
    printf("Enter Due Date (DD/MM/YYYY): ");
    scanf(" %[^\n]", br.due);

    fwrite(&br, sizeof(br), 1, fp);
    fclose(fp);
    printf("\nBorrower Added Successfully!\n");
}

void viewBorrowers() {
    FILE *fp = fopen("borrowers.dat", "rb");
    struct Borrower br;

    printf("\n%-10s %-20s %-10s %-15s\n", "ID", "Name", "Book ID", "Due Date");
    printf("----------------------------------------------------------\n");

    while (fread(&br, sizeof(br), 1, fp))
        printf("%-10d %-20s %-10d %-15s\n", br.id, br.name, br.bookId, br.due);

    fclose(fp);
}

void searchBorrower() {
    FILE *fp = fopen("borrowers.dat", "rb");
    struct Borrower br;
    char find[50];
    int found = 0;

    printf("\nEnter Borrower Name: ");
    scanf(" %[^\n]", find);

    while (fread(&br, sizeof(br), 1, fp)) {
        if (strcasecmp(br.name, find) == 0) {
            printf("\nBorrower Found!\nID: %d\nBook ID: %d\nDue: %s\n",
                   br.id, br.bookId, br.due);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nBorrower Not Found!\n");
    fclose(fp);
}

void deleteBorrower() {
    FILE *fp = fopen("borrowers.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Borrower br;
    int id, found = 0;

    printf("\nEnter Borrower ID to Delete: ");
    scanf("%d", &id);

    while (fread(&br, sizeof(br), 1, fp)) {
        if (br.id != id)
            fwrite(&br, sizeof(br), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("borrowers.dat");
    rename("temp.dat", "borrowers.dat");

    if (found) printf("\nBorrower Deleted Successfully!\n");
    else printf("\nBorrower Not Found!\n");
}

int main() {
    int ch;

    while (1) {
        printf("\n\n===== Library Management System =====\n");
        printf("1. Add Book\n2. View Books\n3. Search Book\n4. Delete Book\n");
        printf("5. Add Borrower\n6. View Borrowers\n7. Search Borrower\n8. Delete Borrower\n");
        printf("9. Exit\nChoose: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: addBorrower(); break;
            case 6: viewBorrowers(); break;
            case 7: searchBorrower(); break;
            case 8: deleteBorrower(); break;
            case 9: return 0;
            default: printf("\nInvalid Choice!\n");
        }
    }
}

