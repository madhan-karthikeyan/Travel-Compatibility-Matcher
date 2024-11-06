#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_INTERESTS 5
#define MAX_DESTINATIONS 5
#define MAX_STRING_LENGTH 50
#define MAX_TRAVELERS 10
#define COMPATIBILITY_THRESHOLD 70 // Threshold for suggesting collaboration

// Date structure
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Trie Node for Interest Search
typedef struct TrieNode {
    struct TrieNode *children[26];
    int isEndOfWord;
} TrieNode;

TrieNode* getNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

void insertInterest(TrieNode* root, const char* interest) {
    TrieNode* pCrawl = root;
    while (*interest) {
        int index = tolower(*interest) - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
        interest++;
    }
    pCrawl->isEndOfWord = 1;
}

int searchInterest(TrieNode* root, const char* interest) {
    TrieNode* pCrawl = root;
    while (*interest) {
        int index = tolower(*interest) - 'a';
        if (!pCrawl->children[index])
            return 0;
        pCrawl = pCrawl->children[index];
        interest++;
    }
    return pCrawl->isEndOfWord;
}

// Traveler structure
typedef struct {
    char name[MAX_STRING_LENGTH];
    TrieNode *interestsTrie;
    char destinations[MAX_DESTINATIONS][MAX_STRING_LENGTH];
    int numDestinations;
    Date travelStartDate;
    Date travelEndDate;
    int numInterests; // New field to store the number of interests
} Traveler;

// Graph structure for Compatibility
int compatibilityGraph[MAX_TRAVELERS][MAX_TRAVELERS];

// Date Difference Calculation
int dateDifference(Date d1, Date d2) {
    struct tm tm1 = {0}, tm2 = {0};
    tm1.tm_year = d1.year - 1900;
    tm1.tm_mon = d1.month - 1;
    tm1.tm_mday = d1.day;

    tm2.tm_year = d2.year - 1900;
    tm2.tm_mon = d2.month - 1;
    tm2.tm_mday = d2.day;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    double diffInSeconds = difftime(t1, t2);
    int diffInDays = diffInSeconds / (60 * 60 * 24);

    return (diffInDays < 0) ? -diffInDays : diffInDays;
}

// Date Overlap Check
int travelDatesOverlap(Traveler* t1, Traveler* t2) {
    return (dateDifference(t1->travelStartDate, t2->travelEndDate) <= 0) &&
           (dateDifference(t1->travelEndDate, t2->travelStartDate) <= 0);
}

// Corrected Interest matching
int calculateCompatibility(Traveler* t1, Traveler* t2) {
    int interestMatch = 0, destinationMatch = 0;
    int travelDateCompatibility = 0;
    float interestWeight = 0.4, destinationWeight = 0.4, dateWeight = 0.2;

    // Interest matching using Trie
    for (int i = 0; i < t1->numInterests; i++) {
        if (searchInterest(t2->interestsTrie, t1->destinations[i])) {
            interestMatch++;
        }
    }

    // Destination matching
    for (int i = 0; i < t1->numDestinations; i++) {
        for (int j = 0; j < t2->numDestinations; j++) {
            if (strcasecmp(t1->destinations[i], t2->destinations[j]) == 0) {
                destinationMatch++;
            }
        }
    }

    // Check for travel date overlap
    if (travelDatesOverlap(t1, t2)) {
        travelDateCompatibility = 1;
    }

    // Calculate compatibility based on weights
    int totalPossibleMatches = MAX_INTERESTS + MAX_DESTINATIONS;
    int matchScore = (interestMatch + destinationMatch) * 100 / totalPossibleMatches;
    float overallCompatibility = (matchScore * (interestWeight + destinationWeight)) +
                                 (travelDateCompatibility * dateWeight * 100);

    return (int)overallCompatibility;
}

// Input function for travelers
void getTravelerInput(Traveler* traveler) {
    printf("Enter traveler name: ");
    getchar();
    fgets(traveler->name, MAX_STRING_LENGTH, stdin);
    traveler->name[strcspn(traveler->name, "\n")] = '\0';

    traveler->interestsTrie = getNode();
    traveler->numInterests = 0;
    printf("Enter interests (one per line, max %d interests). Enter blank to stop.\n", MAX_INTERESTS);
    for (int i = 0; i < MAX_INTERESTS; i++) {
        char interest[MAX_STRING_LENGTH];
        printf("Interest %d: ", i + 1);
        fgets(interest, MAX_STRING_LENGTH, stdin);
        if (interest[0] == '\n') break;  // Blank input ends the loop
        interest[strcspn(interest, "\n")] = '\0';
        insertInterest(traveler->interestsTrie, interest);
        traveler->numInterests++;  // Count the entered interests
    }

    printf("Enter number of destinations: ");
    if (scanf("%d", &traveler->numDestinations) != 1) {
        printf("Invalid input for destinations.\n");
        return;
    }
    getchar(); // Clear buffer

    printf("Enter destinations:\n");
    for (int i = 0; i < traveler->numDestinations; i++) {
        printf("Destination %d: ", i + 1);
        fgets(traveler->destinations[i], MAX_STRING_LENGTH, stdin);
        traveler->destinations[i][strcspn(traveler->destinations[i], "\n")] = '\0';
    }

    // Travel dates input
    printf("Enter travel start date (dd mm yyyy): ");
    if (scanf("%d %d %d", &traveler->travelStartDate.day, &traveler->travelStartDate.month, &traveler->travelStartDate.year) != 3) {
        printf("Invalid input for start date.\n");
        return;
    }

    printf("Enter travel end date (dd mm yyyy): ");
    if (scanf("%d %d %d", &traveler->travelEndDate.day, &traveler->travelEndDate.month, &traveler->travelEndDate.year) != 3) {
        printf("Invalid input for end date.\n");
        return;
    }
}

// Compatibility for all traveler pairs
void calculateAllCompatibilities(Traveler* travelers, int numTravelers) {
    printf("\nCompatibility suggestions for collaboration:\n");
    for (int i = 0; i < numTravelers; i++) {
        for (int j = i + 1; j < numTravelers; j++) {
            int compatibility = calculateCompatibility(&travelers[i], &travelers[j]);
            compatibilityGraph[i][j] = compatibility;
            compatibilityGraph[j][i] = compatibility;

            if (compatibility >= COMPATIBILITY_THRESHOLD) {
                printf("Suggested collaboration between %s and %s: %d%% compatibility\n", travelers[i].name, travelers[j].name, compatibility);
            }
        }
    }
}

// Save travelers to file
void saveTravelersToFile(Traveler* travelers, int numTravelers) {
    FILE* file = fopen("travelers.txt", "wb");
    if (file) {
        fwrite(&numTravelers, sizeof(int), 1, file); // Save the number of travelers
        for (int i = 0; i < numTravelers; i++) {
            fwrite(&travelers[i], sizeof(Traveler), 1, file);
        }
        fclose(file);
        printf("Traveler data saved to travelers.txt.\n");
    } else {
        printf("Error saving traveler data.\n");
    }
}

// Load travelers from file
void loadTravelersFromFile(Traveler* travelers, int* numTravelers) {
    FILE* file = fopen("travelers.txt", "rb");
    if (file) {
        fread(numTravelers, sizeof(int), 1, file);
        for (int i = 0; i < *numTravelers; i++) {
            fread(&travelers[i], sizeof(Traveler), 1, file);
        }
        fclose(file);
        printf("Traveler data loaded from travelers.txt.\n");
    } else {
        printf("Error loading traveler data.\n");
    }
}

int main() {
    int numTravelers;
    printf("Enter number of travelers (or 0 to load from file): ");
    if (scanf("%d", &numTravelers) != 1) {
        printf("Invalid input.\n");
        return 0;
    }

    Traveler travelers[MAX_TRAVELERS];

    if (numTravelers == 0) {
        loadTravelersFromFile(travelers, &numTravelers);
    } else {
        for (int i = 0; i < numTravelers; i++) {
            printf("\nEnter details for Traveler %d:\n", i + 1);
            getTravelerInput(&travelers[i]);
        }
        saveTravelersToFile(travelers, numTravelers);
    }

    calculateAllCompatibilities(travelers, numTravelers);

    return 0;
}
