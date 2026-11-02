/*
 * Project: Drone Fleet Management System
 * Course: TCES 203 Autumn 2026
 * Instructor: Dr Damiano Torre
 * Team #: G14
 * Student 1 full name: Ali Arsalan Wafaee
 * Student 2 full name: put your name here please
 * Variation 1: 1B
 * Variation 2: 2C
 */

#include <stdio.h>

#define MAX_DRONES 5        /* Variation 1B: fleet limited to 5 drones */
#define MAX_LEN 40          /* max model name length, including '\0' */
#define MIN_BATTERY 0.0f
#define MAX_BATTERY 100.0f
#define EXIT_CHOICE 5

void clear_input(void);
void addDrone(int ids[], char models[][MAX_LEN], float batteries[],
              float positions[][2], int *count);
void displayDrones(const int ids[], const char models[][MAX_LEN],
                   const float batteries[], const float positions[][2],
                   int count);
int  searchDroneByID(const int ids[], int count, int targetID);
int  calculateAverageBattery(const float batteries[], int count, float *average);
void checkBatteryWarning(int id, float battery);

int main(void)
{
    int   ids[MAX_DRONES];
    char  models[MAX_DRONES][MAX_LEN];
    float batteries[MAX_DRONES];
    float positions[MAX_DRONES][2];
    int   count = 0;
    int   choice = 0;
    int   result;

    do {
        printf("\nDRONE FLEET MANAGEMENT SYSTEM\n");
        printf("1. Add a Drone\n");
        printf("2. Display All Drones\n");
        printf("3. Search for a Drone by ID\n");
        printf("4. Show Average Battery Level\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        result = scanf("%d", &choice);
        if (result == EOF) {            /* input closed: exit cleanly */
            printf("\nEnd of input. Exiting.\n");
            break;
        }
        if (result != 1) {
            choice = 0;                 /* forces the default case */
        }
        clear_input();             /* drop the rest of the line */

        switch (choice) {
        case 1: addDrone(ids, models, batteries, positions, &count); break;
        case 2: displayDrones(ids, models, batteries, positions, count); break;
        case 3: break;
        case 4: break;
        case EXIT_CHOICE: printf("Exiting Drone Fleet Management System.\n"); break;
        default: printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }
    } while (choice != EXIT_CHOICE);

    return 0;
}

/*
 * clear_input: discards every character left on the current input
 * line (up to and including '\n'). Also stops at EOF so it can never
 * loop forever.
 */
void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/*
 * addDrone: prompts for and validates a new drone's ID, model, battery
 * level and position, then stores it at index *count.
 *   ids, models, batteries, positions - fleet arrays (modified on success)
 *   count - POINTER to the caller's drone count. Read with *count to find
 *           the next free slot; incremented through the pointer only when
 *           the drone is successfully added.
 * All input is read into local variables first, so a failed add never
 * changes the arrays or the count.
 */
void addDrone(int ids[], char models[][MAX_LEN], float batteries[],
              float positions[][2], int *count)
{
    int   id;
    char  model[MAX_LEN];
    float battery;
    float x, y;
    int   i;
    int   ch;
    int   len = 0;
    int   tooLong = 0;

    /* Variation 1B: refuse to add when every slot is used */
    if (*count >= MAX_DRONES) {
        printf("Fleet is full. Cannot add more drones.\n");
        return;
    }

    /* ID: positive integer, not already in the fleet */
    printf("Enter drone ID (positive integer): ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input: ID must be an integer. Drone not added.\n");
        clear_input();
        return;
    }
    clear_input();
    if (id <= 0) {
        printf("Invalid ID: must be a positive integer. Drone not added.\n");
        return;
    }
    for (i = 0; i < *count; i++) {
        if (ids[i] == id) {
            printf("Duplicate ID: drone %d already exists. Drone not added.\n", id);
            return;
        }
    }

    /* Model: nonempty, at most MAX_LEN - 1 characters */
    printf("Enter model name (max %d characters): ", MAX_LEN - 1);
    /* Read the line one character at a time; keep at most MAX_LEN - 1
       characters so there is always room for the '\0' terminator. */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len < MAX_LEN - 1) {
            model[len] = ch;
            len++;
        } else {
            tooLong = 1;
        }
    }
    model[len] = '\0';
    if (tooLong) {
        printf("Invalid model: longer than %d characters. Drone not added.\n",
               MAX_LEN - 1);
        return;
    }
    if (len == 0) {
        printf("Invalid model: name cannot be empty. Drone not added.\n");
        return;
    }

    /* Battery: 0.0 to 100.0 */
    printf("Enter battery level (%.1f - %.1f): ", MIN_BATTERY, MAX_BATTERY);
    if (scanf("%f", &battery) != 1) {
        printf("Invalid input: battery must be a number. Drone not added.\n");
        clear_input();
        return;
    }
    clear_input();
    if (battery < MIN_BATTERY || battery > MAX_BATTERY) {
        printf("Invalid battery: must be between %.1f and %.1f. Drone not added.\n",
               MIN_BATTERY, MAX_BATTERY);
        return;
    }

    /* Position: two floats */
    printf("Enter position X and Y (e.g. 10.5 -3): ");
    if (scanf("%f %f", &x, &y) != 2) {
        printf("Invalid input: position must be two numbers. Drone not added.\n");
        clear_input();
        return;
    }
    clear_input();

    /* All input valid: store in the next free slot, then update count */
    ids[*count] = id;
    for (i = 0; i <= len; i++) {         /* copy name including '\0' */
        models[*count][i] = model[i];
    }
    batteries[*count] = battery;
    positions[*count][0] = x;
    positions[*count][1] = y;
    (*count)++;

    printf("Drone %d (%s) added successfully.\n", id, model);
    printf("Fleet slots occupied: %d/%d\n", *count, MAX_DRONES);  /* 1B */
}

/*
 * displayDrones: prints every stored drone in an aligned table, followed
 * by the total. Prints "No drones available." if the fleet is empty.
 *   ids, models, batteries, positions - fleet arrays (const: read only)
 *   count - number of drones currently stored
 */
void displayDrones(const int ids[], const char models[][MAX_LEN],
                   const float batteries[], const float positions[][2],
                   int count)
{
    int i;

    if (count == 0) {
        printf("No drones available.\n");
        return;
    }

    printf("%-6s %-20s %9s %9s %9s\n", "ID", "Model", "Battery", "X", "Y");
    for (i = 0; i < count; i++) {
        printf("%-6d %-20s %8.2f%% %9.2f %9.2f\n",
               ids[i], models[i], batteries[i],
               positions[i][0], positions[i][1]);
    }
    printf("Total drones: %d\n", count);
}

int searchDroneByID(const int ids[], int count, int targetID)
{
    return -1;
}

int calculateAverageBattery(const float batteries[], int count, float *average)
{
    return 0;
}

void checkBatteryWarning(int id, float battery)
{
}
