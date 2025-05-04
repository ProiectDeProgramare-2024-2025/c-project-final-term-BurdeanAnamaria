#include <stdio.h>
#include <string.h>

typedef struct
{
    char car_number[50];
    char zone[20];
    int duration;
    float cost;
}ParkingTransaction;


   void add_transaction()
{
    ParkingTransaction t;
    FILE *f = fopen("parking_data.txt", "a");
    if (!f)
    {
        printf("Error opening file!\n");
        return;
    }


    printf("Enter car number (e.g., B123XYZ): ");
    scanf(" %[^\n]", t.car_number);


    int valid_zone = 0;
    while (!valid_zone)
    {
        printf("Enter zone (yellow/red/white): ");
        scanf("%s", t.zone);

        if (strcmp(t.zone, "yellow") == 0 || strcmp(t.zone, "red") == 0 || strcmp(t.zone, "white") == 0)
            valid_zone = 1;
        else
            printf("Invalid zone! Please enter 'yellow', 'red', or 'white'.\n");
    }

    do
    {
        printf("Enter duration in hours (positive integer): ");
        scanf("%d", &t.duration);
        if (t.duration <= 0)
            printf("Invalid duration! Duration must be greater than 0.\n");
    } while (t.duration <= 0);


    if (strcmp(t.zone, "yellow") == 0) t.cost = 1.5 * t.duration;
    else if (strcmp(t.zone, "red") == 0) t.cost = 2.0 * t.duration;
    else if (strcmp(t.zone, "white") == 0) t.cost = 1.0 * t.duration;

    fprintf(f, "%s %s %d %.2f\n", t.car_number, t.zone, t.duration, t.cost);
    fclose(f);


    if (strcmp(t.zone, "red") == 0)
        printf("Payment successful! Cost: \033[1;31m%.2f RON\033[0m\n", t.cost);
    else if (strcmp(t.zone, "yellow") == 0)
        printf("Payment successful! Cost: \033[1;33m%.2f RON\033[0m\n", t.cost);
    else
        printf("Payment successful! Cost: \033[1;37m%.2f RON\033[0m\n", t.cost);
}

void view_history() {
    ParkingTransaction t;
    FILE *f = fopen("parking_data.txt", "r");

    printf("\nTransaction History:\n");
    while (fscanf(f, "%49s %19s %d %f", t.car_number, t.zone, &t.duration, &t.cost) == 4)
    {
        printf("%s - %s Zone - %d hours - %.2f RON\n", t.car_number, t.zone, t.duration, t.cost);
    }
    fclose(f);
}

int main()
{
    int choice;
    do {
        printf("\n1. Pay for parking\n2. View history\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) add_transaction();
        else if (choice == 2) view_history();
        else if (choice == 3) printf("Goodbye!\n");
        else printf("Invalid choice.\n");
       }while (choice != 3);

    return 0;
}
