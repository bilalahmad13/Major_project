//the c program of first semister
//so basically its a mood logger and mental health tracker
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void addMood();
void viewLogs();
void searchByDate();

int main() {
    int choice;

    while (1) {
        printf("\n >DAILY MOOD LOGGER< \n");
        printf("1 add Today's Mood\n");
        printf("2 Mental health tracker\n");
        printf("3 search logs by date\n");
        printf("4 Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addMood(); break;
            case 2: viewLogs(); break;
            case 3: searchByDate(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void addMood() {
    FILE *fp = fopen("mood_data.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    char nm[40];
    int mood, i;
    char note[200];
    printf("PLEASE ENTER YOUR NAME : ");
    scanf("%s", nm);
    printf("\nHow do you feel today?\n");
    printf("1. Happy\n2. Sad\n3. Stressed\n4. Angry\n5. Neutral\n6. Anxious\n");
    printf("Enter mood number: ");
    scanf("%d", &mood);
    printf("enter the intensity (ON A SCALE OF 1 TO 10):");
    scanf("%d",&i);
    getchar();
    printf("Enter a short naote describing it :");
    fgets(note, sizeof(note), stdin);

    // Get today's date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", tm);

    char *moodStr;
    switch (mood) {
        case 1: moodStr = "Happy"; break;
        case 2: moodStr = "Sad"; break;
        case 3: moodStr = "Stressed"; break;
        case 4: moodStr = "Angry"; break;
        case 5: moodStr = "Neutral"; break;
        case 6: moodStr = "anxious" ; break;
        default: moodStr = "Unknown";
    }

    fprintf(fp, "%s | %s | %s | %d | %s", dateStr , nm ,  moodStr , i , note );

    fclose(fp);
    printf("\nMood saved successfully!\n");
}

void viewLogs() {
    FILE *fp = fopen("mood_data.txt", "r");
    if (!fp) {
        printf("No logs found!\n");
        return;
    }

    char line[300];
    printf("\n====== ALL MOOD LOGS ======\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void searchByDate() {
    char searchDate[20];
    printf("Enter date to search (YYYY-MM-DD): ");
    scanf("%s", searchDate);

    FILE *fp = fopen("mood_data.txt", "r");
    if (!fp) {
        printf("No logs found!\n");
        return;
    }

    char line[300];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, searchDate)) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) printf("No entry found for this date.\n");

    fclose(fp);
} 