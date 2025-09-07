#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
};

void addBook();
void displayBooks();
void searchBook();
void deleteBook();

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("-------------------------\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void addBook() {
    struct Book b;
    FILE *fp = fopen("books.dat", "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Book Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) {
        printf("No books available.\n");
        return;
    }

    printf("\nList of Books:\n");
    printf("ID\tTitle\tAuthor\n");
    printf("---------------------------\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%d\t%s\t%s\n", b.id, b.title, b.author);
    }
    fclose(fp);
}

void searchBook() {
    int id;
    struct Book b;
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) {
        printf("No books available.\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    int found = 0;

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("Book Found:\nID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }

    if (!found) printf("Book not found!\n");
    fclose(fp);
}

void deleteBook() {
    int id;
    struct Book b;
    FILE *fp = fopen("books.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    int found = 0;

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id) {
            fwrite(&b, sizeof(b), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("books.dat");
    rename("temp.dat", "books.dat");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book not found!\n");
}

