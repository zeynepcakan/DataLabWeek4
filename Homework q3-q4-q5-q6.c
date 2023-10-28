#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int studentNumber;
    char name[50];
    int age;
    struct Student* next;
};

struct Student* head = NULL; // Baðlý listenin baþlangýç düðümü

// Yeni bir öðrenci düðümü oluþturur
struct Student* createStudent(int number, const char* studentName, int studentAge) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->studentNumber = number;
    strcpy(newStudent->name, studentName);
    newStudent->age = studentAge;
    newStudent->next = NULL;
    return newStudent;
}

// Öðrenci düðününü listeye ekler
void addStudent(struct Student* student) {
    if (head == NULL) {
        head = student;
        student->next = head; // Tek baðlý doðrusal liste olduðu için kendisiyle döngü oluþturur.
    } else {
        struct Student* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = student;
        student->next = head;
    }
}

// Aranan öðrenci adýnýn yer aldýðý düðümden bir sonraki düðümü silen fonksiyon
void deleteNextStudent(const char* studentName) {
    struct Student* current = head;

    while (current != NULL) {
        if (strcmp(current->name, studentName) == 0) {
            struct Student* nextStudent = current->next;
            if (nextStudent != head) {
                current->next = nextStudent->next;
                free(nextStudent); // Belleði serbest býrak
                return;
            }
        }
        if (current->next == head) {
            break; // Döngüyü sonlandýr
        }
        current = current->next;
    }
}

// En uzun ismi bulan fonksiyon
const char* findLongestName() {
    if (head == NULL) {
        return NULL; // Liste boþsa NULL döndür
    }

    struct Student* current = head;
    struct Student* longestNameStudent = head;
    int maxLength = strlen(head->name);

    do {
        int currentLength = strlen(current->name);
        if (currentLength > maxLength) {
            maxLength = currentLength;
            longestNameStudent = current;
        }
        current = current->next;
    } while (current != head);

    return longestNameStudent->name;
}

// Öðrenci bilgilerini ekrana yazan fonksiyon
void printStudents() {
    struct Student* current = head;

    printf("student information:\n");
    do {
        printf("Student number: %d, name: %s, age: %d\n", current->studentNumber, current->name, current->age);
        current = current->next;
    } while (current != head);
}

int main() {
    // Öðrenci düðümleri oluþturulur
    struct Student* student1 = createStudent(101, "Ali", 20);
    struct Student* student2 = createStudent(102, "Mehmet", 22);
    struct Student* student3 = createStudent(103, "Ayse", 21);

    // Öðrenci düðümleri listeye eklenir
    addStudent(student1);
    addStudent(student2);
    addStudent(student3);

    printf("First situation:\n");
    printStudents();

    const char* searchName = "Mehmet";
    struct Student* foundStudent = NULL;
    struct Student* current = head;

    // Öðrenci adýný ara ve bul
    do {
        if (strcmp(current->name, searchName) == 0) {
            foundStudent = current;
            break;
        }
        current = current->next;
    } while (current != head);

    if (foundStudent != NULL) {
        printf("\n%s student was found:\n", searchName);
        printf("Student number: %d, name: %s, age: %d\n", foundStudent->studentNumber, foundStudent->name, foundStudent->age);
        
        // Öðrenciyi sil
        deleteNextStudent(searchName);
        printf("\nnext student deleted:\n");
    } else {
        printf("\n%s student not found.\n", searchName);
    }

    const char* longestName = findLongestName();
    if (longestName != NULL) {
        printf("\nLongest name in the list: %s\n", longestName);
    } else {
        printf("\nList is empty.\n");
    }

    printf("\nlast situation:\n");
    printStudents();

    return 0;
}

