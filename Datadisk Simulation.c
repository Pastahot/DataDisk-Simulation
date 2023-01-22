#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 50
#define MAX_CONTENT_LENGTH 1000

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char content[MAX_CONTENT_LENGTH];
} File;

File datadisk[MAX_FILES];
int num_files = 0;

// Vytvorenie zálohy 
void create_backup(File* backup) {
    memcpy(backup, datadisk, sizeof(datadisk));
}

void delete_file(char* filename) {
    // Vyhladavanie položky na Disku na vymazanie
    int file_index = -1;
    for (int i = 0; i < num_files; i++) {
        if (strcmp(datadisk[i].filename, filename) == 0) {
            file_index = i;
            break;
        }
    }

    if (file_index == -1) {
        printf("Error: file not found\n");
        return;
    }

    // Posun Indexu
    for (int i = file_index; i < num_files - 1; i++) {
        strcpy(datadisk[i].filename, datadisk[i + 1].filename);
        strcpy(datadisk[i].content, datadisk[i + 1].content);
    }

    num_files--;
}

void read_file(char* filename) {
    // Vyhladavanie položky na Disku na čitanie
    int file_index = -1;
    for (int i = 0; i < num_files; i++) {
        if (strcmp(datadisk[i].filename, filename) == 0) {
            file_index = i;
            break;
        }
    }

    if (file_index == -1) {
        printf("Error: file not found\n");
        return;
    }

    printf("%s\n", datadisk[file_index].content);
}

void show_disk_content() {
    printf("Files on the datadisk:\n");
    for (int i = 0; i < num_files; i++) {
        printf("- %s\n", datadisk[i].filename);
    }
}

int main() {
    // Pridanie položiek na Datadisk
    strcpy(datadisk[num_files].filename, "file1.txt");
    strcpy(datadisk[num_files].content, "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\nsed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
    num_files++;

    strcpy(datadisk[num_files].filename, "file2.txt");
    strcpy(datadisk[num_files].content, "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");
    num_files++;

    // Volanie Zalohy
    File backup[MAX_FILES];
    create_backup(backup);

    // Zobrazenie obsahu Datadisku
    show_disk_content();

    // Citanie obsahu polozky
    read_file("file1.txt");

    // Vymazanie polozky
    delete_file("file1.txt");

    // Zobrazenie obsahu Datadisku
    show_disk_content();

    return 0;
}
