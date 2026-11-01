/*
 * Project: Drone Fleet Management System
 * Course: TCES 203 Autumn 2026
 * Instructor: Dr Damiano Torre
 * Team #:
 * Student 1 full name:
 * Student 2 full name:
 * Variation 1: 1B
 * Variation 2: 2C
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DRONES 5
#define MAX_LEN 40
#define INPUT_LEN 128

/* Function prototypes */
void addDrone(int ids[], char models[][MAX_LEN], float batteries[],
              float positions[][2], int *count);
void displayDrones(const int ids[], const char models[][MAX_LEN],
                   const float batteries[], const float positions[][2],
                   int count);
int  searchDroneByID(const int ids[], int count, int targetID);
int  calculateAverageBattery(const float batteries[], int count, float *average);
void checkBatteryWarning(int id, float battery);
void readLine(const char *prompt, char *buf, int size);
void printMenu(void);

int main(void)
{
    int   ids[MAX_DRONES];
    char  models[MAX_DRONES][MAX_LEN];
    float batteries[MAX_DRONES];
    float positions[MAX_DRONES][2];
    int   count = 0;
    int   choice = 0;
    char  line[INPUT_LEN];

    do {
        printMenu();
        readLine("Enter your choice: ", line, sizeof line);
        if (sscanf(line, "%d", &choice) != 1)
            choice = 0;

        switch (choice) {
        case 1:
            addDrone(ids, models, batteries, positions, &count);
            break;
        case 2:
            displayDrones(ids, models, batteries, positions, count);
            break;
        case 3:
            /* TODO: search by ID */
            printf("Not implemented yet.\n");
            break;
        case 4:
            /* TODO: average battery */
            printf("Not implemented yet.\n");
            break;
        case 5:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter 1-5.\n");
        }
    } while (choice != 5);

    return 0;
}

/* Function definitions */

/* Prints the main menu. */
void printMenu(void)
{
    printf("\nDRONE FLEET MANAGEMENT SYSTEM\n");
    printf("1. Add a Drone\n");
    printf("2. Display All Drones\n");
    printf("3. Search for a Drone by ID\n");
    printf("4. Show Average Battery Level\n");
    printf("5. Exit\n");
}

/* Reads one line into buf; on EOF returns "5" so the menu exits. */
void readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        strcpy(buf, "5");
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

/* Adds a validated drone. count is a pointer to the caller's drone count,
   incremented only on success. */
void addDrone(int ids[], char models[][MAX_LEN], float batteries[],
              float positions[][2], int *count)
{
    char  line[INPUT_LEN], extra;
    int   id, i;
    float battery, x, y;

    if (*count >= MAX_DRONES) {
        printf("Fleet is full. Cannot add more drones.\n");
        return;
    }

    readLine("Enter drone ID: ", line, sizeof line);
    if (sscanf(line, "%d %c", &id, &extra) != 1 || id <= 0) {
        printf("Invalid ID. Must be a positive integer.\n");
        return;
    }
    for (i = 0; i < *count; i++) {
        if (ids[i] == id) {
            printf("Duplicate ID. A drone with ID %d already exists.\n", id);
            return;
        }
    }

    char model[INPUT_LEN];
    readLine("Enter model name: ", model, sizeof model);
    if (model[0] == '\0' || strlen(model) > MAX_LEN - 1) {
        printf("Invalid model name. Must be 1-%d characters.\n", MAX_LEN - 1);
        return;
    }

    char battLine[INPUT_LEN];
    readLine("Enter battery level (0-100): ", battLine, sizeof battLine);
    if (sscanf(battLine, "%f %c", &battery, &extra) != 1 ||
        battery < 0.0f || battery > 100.0f) {
        printf("Invalid battery level. Must be between 0.0 and 100.0.\n");
        return;
    }

    char posLine[INPUT_LEN];
    readLine("Enter position X Y: ", posLine, sizeof posLine);
    if (sscanf(posLine, "%f %f %c", &x, &y, &extra) != 2) {
        printf("Invalid position. Enter two numbers, e.g. 10 20.\n");
        return;
    }

    ids[*count] = id;
    strcpy(models[*count], model);
    batteries[*count] = battery;
    positions[*count][0] = x;
    positions[*count][1] = y;
    (*count)++;

    printf("Drone %d added successfully. Fleet slots used: %d/%d\n",
           id, *count, MAX_DRONES);
}

/* TODO: print table, total, or "No drones available." */
void displayDrones(const int ids[], const char models[][MAX_LEN],
                   const float batteries[], const float positions[][2],
                   int count)
{
    (void)ids; (void)models; (void)batteries; (void)positions; (void)count;
    printf("displayDrones not implemented yet.\n");
}

/* TODO: return index of targetID, or -1 */
int searchDroneByID(const int ids[], int count, int targetID)
{
    (void)ids; (void)count; (void)targetID;
    return -1;
}

/* TODO: store average in *average, return 1; return 0 if no drones */
int calculateAverageBattery(const float batteries[], int count, float *average)
{
    (void)batteries; (void)count; (void)average;
    return 0;
}

/* TODO (2C): warn if battery < 20; call from addDrone() after a successful add */
void checkBatteryWarning(int id, float battery)
{
    (void)id; (void)battery;
}
