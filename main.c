#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_INTERESTS 5
#define MAX_DESTINATIONS 5
#define MAX_STRING_LENGTH 50
#define MAX_TRAVELERS 10  // Max number of travelers

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[MAX_STRING_LENGTH];  // Use name instead of ID
    char interests[MAX_INTERESTS][MAX_STRING_LENGTH];  // Array of interest strings
    char destinations[MAX_DESTINATIONS][MAX_STRING_LENGTH];  // Array of destination strings
    int numInterests;
    int numDestinations;
    Date travelStartDate;  // Add travel start date
    Date travelEndDate;    // Add travel end date
} Traveler;

// Function to compare strings in a case-insensitive way
int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2 || tolower((unsigned char)*s1) == tolower((unsigned char)*s2))) {
        s1++;
        s2++;
    }
    return (unsigned char) *s1 - (unsigned char) *s2;
}

// Function to calculate the absolute difference in days between two dates
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
    
    // Calculate the difference in seconds and convert it to days
    double diffInSeconds = difftime(t1, t2);
    int diffInDays = diffInSeconds / (60 * 60 * 24);
    
    return (diffInDays < 0) ? -diffInDays : diffInDays; // Return absolute value
}

// Function to check if two travelers' dates overlap
int travelDatesOverlap(Traveler *t1, Traveler *t2) {
    // Check if the travel dates overlap (if start date of one is before or equal to end date of the other)
    // and the end date of one is after or equal to the start date of the other
    if ((dateDifference(t1->travelStartDate, t2->travelEndDate) <= 0) &&
        (dateDifference(t1->travelEndDate, t2->travelStartDate) <= 0)) {
        return 1; // Dates overlap
    }
    return 0; // No overlap
}

// Compatibility function
int calculateCompatibility(Traveler* t1, Traveler* t2) {
    int interestMatch = 0, destinationMatch = 0;
    int travelDateCompatibility = 0;

    // Interest matching
    for (int i = 0; i < t1->numInterests; i++) {
        for (int j = 0; j < t2->numInterests; j++) {
            if (strcasecmp(t1->interests[i], t2->interests[j]) == 0) {
                interestMatch++;
            }
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
        travelDateCompatibility = 50;  // Assign 50 points for date overlap
    }

    // Calculate overall compatibility score based on interests, destinations, and travel dates
    int maxInterests = (t1->numInterests > t2->numInterests) ? t1->numInterests : t2->numInterests;
    int maxDestinations = (t1->numDestinations > t2->numDestinations) ? t1->numDestinations : t2->numDestinations;
    int totalPossibleMatches = maxInterests + maxDestinations;

    if (totalPossibleMatches == 0) {
        return travelDateCompatibility; // Only travel date compatibility if no matches
    }

    int overallCompatibility = ((interestMatch + destinationMatch) * 100) / totalPossibleMatches;
    
    // Combine both compatibility scores (interest/destination and travel date)
    int finalCompatibility = (overallCompatibility + travelDateCompatibility) / 2;
    return finalCompatibility;
}

// Function to get a traveler input from the user
void getTravelerInput(Traveler* traveler) {
    printf("Enter traveler name: ");
    getchar(); // to clear the newline character
    fgets(traveler->name, MAX_STRING_LENGTH, stdin);
    traveler->name[strcspn(traveler->name, "\n")] = '\0';  // Remove newline character

    // Get number of interests
    printf("Enter number of interests (max %d): ", MAX_INTERESTS);
    scanf("%d", &traveler->numInterests);
    if (traveler->numInterests > MAX_INTERESTS) {
        traveler->numInterests = MAX_INTERESTS;
    }

    // Get the interests
    printf("Enter the interests (max %d characters per interest):\n", MAX_STRING_LENGTH);
    for (int i = 0; i < traveler->numInterests; i++) {
        printf("Interest %d: ", i + 1);
        getchar(); // to clear the newline character
        fgets(traveler->interests[i], MAX_STRING_LENGTH, stdin);
        traveler->interests[i][strcspn(traveler->interests[i], "\n")] = '\0';  // Remove newline
    }

    // Get number of destinations
    printf("Enter number of destinations (max %d): ", MAX_DESTINATIONS);
    scanf("%d", &traveler->numDestinations);
    if (traveler->numDestinations > MAX_DESTINATIONS) {
        traveler->numDestinations = MAX_DESTINATIONS;
    }

    // Get the destinations
    printf("Enter the destinations (max %d characters per destination):\n", MAX_STRING_LENGTH);
    for (int i = 0; i < traveler->numDestinations; i++) {
        printf("Destination %d: ", i + 1);
        getchar(); // to clear the newline character
        fgets(traveler->destinations[i], MAX_STRING_LENGTH, stdin);
        traveler->destinations[i][strcspn(traveler->destinations[i], "\n")] = '\0';  // Remove newline
    }

    // Get travel start date
    printf("Enter travel start date (dd mm yyyy): ");
    scanf("%d %d %d", &traveler->travelStartDate.day, &traveler->travelStartDate.month, &traveler->travelStartDate.year);

    // Get travel end date
    printf("Enter travel end date (dd mm yyyy): ");
    scanf("%d %d %d", &traveler->travelEndDate.day, &traveler->travelEndDate.month, &traveler->travelEndDate.year);
}

// Function to calculate and display compatibility for all traveler pairs
void calculateAllCompatibilities(Traveler* travelers, int numTravelers) {
    for (int i = 0; i < numTravelers; i++) {
        for (int j = i + 1; j < numTravelers; j++) {
            int result = calculateCompatibility(&travelers[i], &travelers[j]);
            printf("\nCompatibility between Traveler %s and Traveler %s: %d%%\n", travelers[i].name, travelers[j].name, result);
        }
    }
}

int main() {
    int numTravelers;

    // Get the number of travelers
    printf("Enter the number of travelers: ");
    scanf("%d", &numTravelers);

    // Check if there are insufficient travelers to compare
    if (numTravelers < 2) {
        printf("Insufficient number of travelers to compare compatibility. At least 2 travelers are required.\n");
        return 0;  // Exit the program
    }
    
    // Ensure numTravelers is within bounds
    if (numTravelers > MAX_TRAVELERS) {
        numTravelers = MAX_TRAVELERS;
        printf("Number of travelers limited to %d.\n", MAX_TRAVELERS);
    }

    // Declare an array to store all travelers
    Traveler travelers[numTravelers];

    // Get traveler data from the user
    for (int i = 0; i < numTravelers; i++) {
        printf("\nEnter details for Traveler %d:\n", i + 1);
        getTravelerInput(&travelers[i]);
    }

    // Calculate and display compatibility for all pairs
    printf("\nCalculating compatibility for all pairs of travelers:\n");
    calculateAllCompatibilities(travelers, numTravelers);

    return 0;
}