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

#define MAX_DRONES 5
#define MAX_LEN 40

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

    do {
        printf("\nDRONE FLEET MANAGEMENT SYSTEM\n");
        printf("1. Add a Drone\n");
        printf("2. Display All Drones\n");
        printf("3. Search for a Drone by ID\n");
        printf("4. Show Average Battery Level\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n')
                ;
        }

        switch (choice) {
        case 1: addDrone(ids, models, batteries, positions, &count); break;
        case 2: displayDrones(ids, models, batteries, positions, count); break;
        case 3: /* TODO: search by ID */ break;
        case 4: /* TODO: average battery */ break;
        case 5: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

/* TODO: Problem 1 */
void addDrone(int ids[], char models[][MAX_LEN], float batteries[],
              float positions[][2], int *count)
{
}

/* TODO: Problem 1 */
void displayDrones(const int ids[], const char models[][MAX_LEN],
                   const float batteries[], const float positions[][2],
                   int count)
{
}

/* TODO: return index of targetID, or -1 */
int searchDroneByID(const int ids[], int count, int targetID)
{
    return -1;
}

/* TODO: store average in *average, return 1; return 0 if no drones */
int calculateAverageBattery(const float batteries[], int count, float *average)
{
    return 0;
}

/* TODO (2C): warn if battery < 20 */
void checkBatteryWarning(int id, float battery)
{
}
