# Car Speed Testing

## Project Overview

This project focuses on solving two distinct problems using dynamic programming and memoization techniques. The first problem involves determining the minimum number of tests required to check if a set of cars can reach a certain maximum speed. The second problem deals with calculating the number of ways to display a sequence of ads without repeating the same ad consecutively.

## Project Structure

### 1. **Coding Portion: Car Speed Testing**

#### Usage
To run the program, use the following command: dynamic.exe <number_of_cars> <max_speed>

#### How It Works
- **Recursive Approach**: The `minTests` function recursively explores each possible test speed in increments of 5, assessing two scenarios at each test speed:
  - **Success**: The car reaches the test speed, and the function continues to check higher speeds.
  - **Failure**: The car fails, resulting in removing one car from the pool and checking a lower speed.

- **Dynamic Programming and Memoization**: The solution uses a memoization array (`memArray`) to store already computed results, avoiding redundant calculations and speeding up the solution for large inputs.

- **Choice and Success Tracking**: The `speedChoice` array stores the optimal test speed for each car-speed combination, while `isSuccess` records whether each speed test was successful.

- **Base Cases**: Direct answers are provided for simple scenarios, such as when the speed is 0 or 5, or when only one car is left.

#### Run-time Testing
The program includes a run-time testing feature that keeps the number of cars constant (3) and runs 20 tests with max speeds starting from 0 up to 500, incrementing by 25 mph. The results are outputted to `timing_analysis_results.csv`.

#### Graphical Representation
The run-time analysis shows that the time complexity can be estimated as:
\[O \left( C \left( \frac{S}{s} \right)^2 \right)\]
where \( C \) is the number of cars and \( S \) is the max test speed.

### 2. **Written Portion: Ad Sequencing Problem**

#### Problem Statement
Given X different kinds of ads, each with a specific number of times they need to be displayed in a given time period, determine the number of ways to display them without showing the same ad two or more times in a row.

#### Solution Approach
- **Parameters**: The function `T(ad_counts[], last_ad)` is used, where `ad_counts` is an array of remaining counts for each ad type, and `last_ad` is the last ad displayed.
- **Optimal Substructure**: The problem reduces to selecting the next ad to display, ensuring it differs from `last_ad`.
- **Overlapping Subproblems**: Different sequences can lead to the same subproblem, indicating overlapping subproblems.
- **Base Case**: The smallest subproblem is when all counts in `ad_counts` are zero, representing a single valid sequence.
- **Recursive Formula**: The number of valid arrangements is calculated recursively by considering each ad type that is not the same as `last_ad` and has a positive count in `ad_counts`.

## Conclusion
This project demonstrates the application of dynamic programming and memoization to solve complex problems efficiently. The car speed testing problem showcases how to minimize the number of tests required, while the ad sequencing problem illustrates how to count valid sequences without repeating the same ad consecutively. Both solutions leverage recursive structures and memoization to achieve optimal results.
