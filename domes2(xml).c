#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 10
#define MAX_LENGTH 100

typedef struct {
    char* book_id;
    char* author;
    char* title;
    char* genre;
    char* price;
    char* publish_date;
} Book;

int main(void) {
    Book books[MAX_BOOKS];
    int bookCount = 0;

    char line[MAX_LENGTH];
    char file[100];

    printf("Enter the XML file name: ");
    scanf("%s", file);

    FILE* fptr;
    if ((fptr = fopen(file, "r")) == NULL) {
        printf("Error! File cannot be opened: %s\n", file);
        exit(1);
    }

    while (fgets(line, MAX_LENGTH, fptr)) {
        if (strstr(line, "<book>")) {
            Book book;
            bookCount = bookCount < MAX_BOOKS ? bookCount + 1 : MAX_BOOKS;
            int i = 0;

            while (fgets(line, MAX_LENGTH, fptr) && !strstr(line, "</book>")) {
                if (strstr(line, "<book_id>")) {
                    char* p = strchr(line, '>');
                    if (p != NULL) {
                        p++;
                        book.book_id = strdup(p);
                    }
                }
                else if (strstr(line, "<author>")) {
                    char* p = strchr(line, '>');
                    if (p != NULL) {
                        p++;
                        book.author = strdup(p);
                    }
                }
                else if (strstr(line, "<title>")) {
                    char* p = strchr(line, '>');
                    if (p != NULL) {
                        p++;
                        book.title = strdup(p);
                    }
                }
                else if (strstr(line, "<genre>")) {
                    char* p = strchr(line, '>');
                    if (p != NULL) {
                        p++;
                        book.genre = strdup(p);
                    }
                }
                else if (strstr(line, "<price>")) {
                    char* p = strchr(line, '>');
                    if (p != NULL) {
                        p++;
                        book.price = strdup(p);
                    }
                }
                else if (strstr(line, "<publish_date>")) {
                    char* p = strchr(line, '>');
                    if (p != NULL) {
                        p++;
                        book.publish_date = strdup(p);
                    }
                }
                i++;
            }

            books[bookCount - 1] = book;
        }
    }

    fclose(fptr);

    for (int i = 0; i < bookCount; i++) {
        printf("\nBook %d:\n", i + 1);
        printf("Book ID: %.*s\n", strchr(books[i].book_id, '<') - books[i].book_id, books[i].book_id);
        printf("Author: %.*s\n", strchr(books[i].author, '<') - books[i].author, books[i].author);
        printf("Title: %.*s\n", strchr(books[i].title, '<') - books[i].title, books[i].title);
        printf("Genre: %.*s\n", strchr(books[i].genre, '<') - books[i].genre, books[i].genre);
        printf("Price: %.*s\n", strchr(books[i].price, '<') - books[i].price, books[i].price);
        printf("Publish Date: %.*s\n", strchr(books[i].publish_date, '<') - books[i].publish_date, books[i].publish_date);
    }

    // Free allocated memory
    for (int i = 0; i < bookCount; i++) {
        free(books[i].book_id);
        free(books[i].author);
        free(books[i].title);
        free(books[i].genre);
        free(books[i].price);
        free(books[i].publish_date);
    }

    return 0;
}
