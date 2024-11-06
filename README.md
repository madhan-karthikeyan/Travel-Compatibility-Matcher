# Travel Compatibility Matcher

## Overview
The Travel Compatibility Matcher is a C application that calculates compatibility scores between travelers based on shared interests, destinations, and overlapping travel dates. Using structured data and an efficient scoring algorithm, it provides a quick and simple way to match compatible travel companions.

## Features
- **Interest Matching**: Compares and scores shared interests between travelers.
- **Destination Matching**: Identifies and scores common destinations.
- **Date Overlap Detection**: Awards additional compatibility points if travel dates align.

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
