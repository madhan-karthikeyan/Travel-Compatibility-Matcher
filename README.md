# Travel Compatibility Matcher

## Project Overview
The Travel Compatibility Matcher is a C program designed to help travelers find compatible companions based on shared interests, destinations, and overlapping travel dates. The system uses custom data structures and algorithms to calculate compatibility scores between travelers.

## Features
- **Interest Matching**: Compares travelers' interests to find common points.
- **Destination Matching**: Identifies overlapping destinations for better compatibility.
- **Date Overlap Detection**: Checks if travelers' schedules align.
- **Scoring System**: Generates a compatibility score based on interests, destinations, and dates.

## Technical Details
- **Data Structures**: Uses `Traveler` and `Date` structs to store traveler information.
- **Algorithm**: Calculates compatibility by combining normalized scores for interests, destinations, and date overlap.
- **Performance**: Static memory allocation with \(O(n^2)\) time complexity for pairwise compatibility calculations.

## How to Run
1. Compile the program:
   ```bash
   gcc travel_matcher.c -o travel_matcher
2. Run the program
   ```bash
   ./travel_matcher
3. Follow the prompts to enter traveler information and view compatibility scores.
   ```yaml
   Enter the number of travelers: 2
   Traveler 1: Alice, Interests: Hiking, Music, Destinations: Paris, Dates: 01/05/2024 - 10/05/2024
   Traveler 2: Bob, Interests: Music, Art, Destinations: Paris, Dates: 05/05/2024 - 15/05/2024
