#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vehicle
{
    int id;
    char brand[50];
    char model[100];
    int year;
    float price;
    int isSold;
};

struct Vehicle vehicles[200];
int vehicleCount = 0;

void displayVehicles();
void searchVehicle();
void sellVehicle();
void generateBill(struct Vehicle v);
void addVehicle();
void deleteVehicle();
void saveToFile();
void loadFromFile();

int main()
{
    int choice;

    loadFromFile();

    while (1)
    {
        printf("\nVehicle Management System\n");
        printf("1. Display All Vehicles\n");
        printf("2. Search Vehicle by ID\n");
        printf("3. Sell Vehicle\n");
        printf("4. Add Vehicle\n");
        printf("5. Delete Vehicle\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayVehicles();
            break;
        case 2:
            searchVehicle();
            break;
        case 3:
            sellVehicle();
            break;

        case 4:
            addVehicle();
            break;
        case 5:
            deleteVehicle();
            break;
        case 6:
            saveToFile();
            exit(0);
        default:
            printf("Invalid try again.\n");
        }
    }
    return 0;
}
void displayVehicles()
{
    if (vehicleCount == 0)
    {
        printf(" No vehicles found.\n");
        return;
    }
    printf("List of Vehicles\n\t");
    for (int i = 0; i < vehicleCount; i++)
    {
        printf(" \t ID: %d, \t Brand: %s, \t Model: %s, \t Year: %d, \t Price: %.2f, Status: %s \n\t",
               vehicles[i].id, vehicles[i].brand, vehicles[i].model,
               vehicles[i].year, vehicles[i].price,
               vehicles[i].isSold ? "Sold" : "Available");
    }
}
void searchVehicle()
{
    int id, found = 0;
    printf("Enter vehicle ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].id == id)
        {
            printf("Vehicle Found: ID: %d, Brand: %s, Model: %s, Year: %d, Price: %.2f, Status: %s\n",
                   vehicles[i].id, vehicles[i].brand, vehicles[i].model,
                   vehicles[i].year, vehicles[i].price,
                   vehicles[i].isSold ? " Already Sold" : "Available");
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Vehicle with ID %d not found.\n", id);
    }
}
void sellVehicle()
{
    int id, found = 0;
    printf("Enter vehicle ID to sell: ");
    scanf("%d", &id);

    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].id == id)
        {
            if (vehicles[i].isSold)
            {
                printf("Vehicle with ID %d is already sold\n", id);
                return;
            }
            vehicles[i].isSold = 1;
            generateBill(vehicles[i]);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Vehicle with ID %d not found.\n", id);
    }
}
void generateBill(struct Vehicle v)
{
    printf("\n--- Bill Receipt ---\n");
    printf("Vehicle ID: %d\n", v.id);
    printf("Vehicle Brand: %s\n", v.brand);
    printf("Vehicle Model: %s\n", v.model);
    printf("Sell Year: %d\n", v.year);
    printf("Vehicle Price: %.2f\n", v.price);
    printf("Status: Sold succesfully\n");
    printf("---------------------\n");
}

void addVehicle()
{
    struct Vehicle v;
    printf("Enter vehicle id: ");
    scanf("%d", &v.id);
    getchar();

    printf("Enter vehicle brand: ");
    fgets(v.brand, sizeof(v.brand), stdin);
    v.brand[strcspn(v.brand, "\n")] = 0;

    printf("Enter vehicle model: ");
    fgets(v.model, sizeof(v.model), stdin);
    v.model[strcspn(v.model, "\n")] = 0;

    printf("Enter sell year: ");
    scanf("%d", &v.year);

    printf("Enter vehicle price: ");
    scanf("%f", &v.price);
    v.isSold = 0;

    vehicles[vehicleCount++] = v;

    printf("Vehicle added successfully!\n");
}
void deleteVehicle()
{
    int id, found = 0;
    printf("Enter vehicle ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].id == id)
        {
            found = 1;
            for (int j = i; j < vehicleCount - 1; j++)
            {
                vehicles[j] = vehicles[j + 1];
            }
            vehicleCount--;
            printf("Vehicle with ID %d deleted successfully.\n", id);
            break;
        }
    }
    if (!found)
    {
        printf("Vehicle with ID %d not found.\n", id);
    }
}
void saveToFile()
{
    FILE *file = fopen("vehicles.dat", "w");
    if (file == NULL)
    {
        printf("Error to saving file.\n");
        return;
    }
    fwrite(&vehicleCount, sizeof(int), 1, file);

    fwrite(vehicles, sizeof(struct Vehicle), vehicleCount, file);
    fclose(file);

    printf("Vehicles saved successfully.\n");
}
void loadFromFile()
{
    FILE *file = fopen("vehicles.dat", "r");
    if (file == NULL)
    {
        printf("Previous data not found. Starting fresh.\n");
        return 0;
    }
    fread(&vehicleCount, sizeof(int), 1, file);

    fread(vehicles, sizeof(struct Vehicle), vehicleCount, file);

    fclose(file);

    printf("Vehicles loaded from file successfully.\n");
}
