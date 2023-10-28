#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int studentNumber;
    char name[50];
    int age;
    struct Student* next;
};

struct Student* head = NULL; // Ba�l� listenin ba�lang�� d���m�

// Yeni bir ��renci d���m� olu�turur
struct Student* createStudent(int number, const char* studentName, int studentAge) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->studentNumber = number;
    strcpy(newStudent->name, studentName);
    newStudent->age = studentAge;
    newStudent->next = NULL;
    return newStudent;
}

// ��renci d���n�n� listeye ekler
void addStudent(struct Student* student) {
    if (head == NULL) {
        head = student;
        student->next = head; // Tek ba�l� do�rusal liste oldu�u i�in kendisiyle d�ng� olu�turur.
    } else {
        struct Student* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = student;
        student->next = head;
    }
}

// Aranan ��renci ad�n�n yer ald��� d���mden bir sonraki d���m� silen fonksiyon
void deleteNextStudent(const char* studentName) {
    struct Student* current = head;

    while (current != NULL) {
        if (strcmp(current->name, studentName) == 0) {
            struct Student* nextStudent = current->next;
            if (nextStudent != head) {
                current->next = nextStudent->next;
                free(nextStudent); // Belle�i serbest b�rak
                return;
            }
        }
        if (current->next == head) {
            break; // D�ng�y� sonland�r
        }
        current = current->next;
    }
}

// En uzun ismi bulan fonksiyon
const char* findLongestName() {
    if (head == NULL) {
        return NULL; // Liste bo�sa NULL d�nd�r
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

// ��renci bilgilerini ekrana yazan fonksiyon
void printStudents() {
    struct Student* current = head;

    printf("student information:\n");
    do {
        printf("Student number: %d, name: %s, age: %d\n", current->studentNumber, current->name, current->age);
        current = current->next;
    } while (current != head);
}

int main() {
    // ��renci d���mleri olu�turulur
    struct Student* student1 = createStudent(101, "Ali", 20);
    struct Student* student2 = createStudent(102, "Mehmet", 22);
    struct Student* student3 = createStudent(103, "Ayse", 21);

    // ��renci d���mleri listeye eklenir
    addStudent(student1);
    addStudent(student2);
    addStudent(student3);

    printf("First situation:\n");
    printStudents();

    const char* searchName = "Mehmet";
    struct Student* foundStudent = NULL;
    struct Student* current = head;

    // ��renci ad�n� ara ve bul
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
        
        // ��renciyi sil
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

