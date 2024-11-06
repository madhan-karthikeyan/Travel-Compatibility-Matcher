# Traveler Compatibility Program

This is a console-based program to calculate compatibility between travelers based on their interests, destinations, and travel dates. The program allows users to input traveler data, calculate compatibility between travelers, and save/load traveler data from a file.

## Features
- Add travelers and input their details such as name, interests, destinations, and travel dates.
- Calculate compatibility between all pairs of travelers based on shared interests, destinations, and travel date overlaps.
- Save traveler data to a file (`travellers.txt`) and load traveler data from the same file for later use.
- Compatibility calculation considers the following:
  - Matching interests
  - Matching destinations
  - Overlapping travel dates
- Ability to handle up to 10 travelers, with a maximum of 5 interests and 5 destinations per traveler.

## Program Structure

### Data Structures:
- **Traveler**: Stores the details of each traveler, including name, interests, destinations, and travel dates.
- **TravelerGroup**: Contains an array of travelers and keeps track of the total number of travelers.

### Menu Options:
1. **Add Travelers**: Allows you to add multiple travelers, including their details such as name, interests, destinations, and travel dates.
2. **Calculate Compatibility**: Calculates the compatibility between all pairs of travelers based on the stored data.
3. **Save Travelers to File**: Saves the current list of travelers to a file (`travellers.txt`).
4. **Load Travelers from File**: Loads traveler data from the `travellers.txt` file.
5. **Exit**: Exits the program.

### File Storage
1. The traveler data is saved in the travellers.txt file. Each time you choose to save, the current traveler data is overwritten in the file.
2. The program uses the travellers.txt file to load traveler data on startup.

### Limitations
1. The program is limited to handling up to 10 travelers at once.
2. A maximum of 5 interests and 5 destinations can be entered for each traveler.
3. Only basic compatibility criteria are considered (interest, destination, and travel date overlap).

## How to Use

1. **Compile the Program**:
   If you are using a C compiler like `gcc`, compile the program using the following command:
   ```bash
   gcc traveler_compatibility.c -o traveler_compatibility

2. **Run the Program**:
Run the compiled program with the following command:
   ```bash
   ./traveler_compatibility


3. **Interact with the Menu**:
- Choose from the options presented in the menu.
- For **Add Travelers**, enter the number of travelers and their respective details when prompted.
- For **Calculate Compatibility**, the program will calculate compatibility scores for all pairs of travelers.
- You can **Save** and **Load** traveler data to/from a file to persist the data between program runs.

## Example Output

   ```bash
   Menu:
   1. Add Travelers
   2. Calculate Compatibility
   3. Save Travelers to File
   4. Load Travelers from File
   5. Exit
   Enter your choice: 1
   Enter the number of travelers: 2
   
   Enter details for Traveler 1:
   Enter traveler name: Alice
   Enter number of interests (max 5): 3
   Enter interests:
   Interest 1: Hiking
   Interest 2: Photography
   Interest 3: Reading
   Enter number of destinations (max 5): 2
   Enter destinations:
   Destination 1: Paris
   Destination 2: Tokyo
   Enter travel start date (dd mm yyyy): 01 06 2024
   Enter travel end date (dd mm yyyy): 15 06 2024
   
   Enter details for Traveler 2:
   Enter traveler name: Bob
   Enter number of interests (max 5): 2
   Enter interests:
   Interest 1: Hiking
   Interest 2: Cooking
   Enter number of destinations (max 5): 1
   Enter destinations:
   Destination 1: Paris
   Enter travel start date (dd mm yyyy): 05 06 2024
   Enter travel end date (dd mm yyyy): 20 06 2024
   
   Calculating compatibility for all pairs of travelers:
   Compatibility between Alice and Bob: 80%
