////////////////////////////////////////////////////////////////////////////////
//
// PermutationGenerator (Generic)
//
// Desc: Main.cpp
// Main program file.
//
// 04/06/2025 (BGM)
// File inception.
//
////////////////////////////////////////////////////////////////////////////////

#include "Main.h"
#include "sys_Utils.h"

////////////////////////////////////////////////////////////////////////////////
// Macros:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Types:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes:
////////////////////////////////////////////////////////////////////////////////

int GenerateCombinations(int* elements, int n, int r);
void GenerateCombinationsRecursive(int* elements, int n, int* combination, int r, int index, int start, int* count);
int FindMinimumSteps(int* initial, int* target, int size);
void LogResultsToCSV(const char* filename, int n, int r, int combinations_count, long execution_time_microseconds);
void InitializeCSVFile(const char* filename);

////////////////////////////////////////////////////////////////////////////////
// Globals:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Procedures:
////////////////////////////////////////////////////////////////////////////////

/**
 * Function 1: Generate all combinations of r elements from n elements
 * Measures execution time and returns count of combinations
 */
int GenerateCombinations(int* elements, int n, int r) {
  std::cout << "\n=== FUNCTION 1: GENERATING COMBINATIONS ===\n";
  std::cout << "Elements: ";
  PrintArray(elements, n);
  std::cout << "Generating combinations of size " << r << " from " << n << " elements\n\n";

  // Start timing
  auto start = std::chrono::high_resolution_clock::now();

  int* combination = new int[r];
  int count = 0;

  GenerateCombinationsRecursive(elements, n, combination, r, 0, 0, &count);

  // End timing
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "\nTotal combinations found: " << count << std::endl;
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  LogResultsToCSV("combination_results.csv", n, r, count, duration.count());

  delete[] combination;
  return count;
}

void GenerateCombinationsRecursive(int* elements, int n, int* combination, int r, int index, int start, int* count) {
  if (index == r) {
    (*count)++;
    std::cout << "Combination " << *count << ": ";
    PrintCombination(combination, r);
    return;
  }

  for (int i = start; i < n; i++) {
    combination[index] = elements[i];
    GenerateCombinationsRecursive(elements, n, combination, r, index + 1, i + 1, count);
  }
}

/**
 * Function 2: Find minimum steps to reach target sequence from initial sequence
 * Uses a simple approach with adjacent swaps
 */
int FindMinimumSteps(int* initial, int* target, int size) {
  std::cout << "\n=== FUNCTION 2: FINDING MINIMUM STEPS ===\n";
  std::cout << "Initial sequence: ";
  PrintArray(initial, size);
  std::cout << "Target sequence:  ";
  PrintArray(target, size);
  std::cout << "\nSearching for minimum steps...\n\n";

  int* current = new int[size];
  CopyArray(initial, current, size);

  int steps = 0;

  // For each position, find the target element and move it there
  for (int i = 0; i < size; i++) {

    // If current position already has correct element, continue
    if (current[i] == target[i]) {
      continue;
    }

    // Find the target element in the remaining part
    int targetPos = -1;
    for (int j = i + 1; j < size; j++) {
      if (current[j] == target[i]) {
        targetPos = j;
        break;
      }
    }

    // Move the element to correct position using adjacent swaps
    if (targetPos != -1) {
      while (targetPos > i) {
        Swap(&current[targetPos], &current[targetPos - 1]);
        targetPos--;
        steps++;

        std::cout << "Step " << steps << ": ";
        PrintArray(current, size);
      }
    }
  }

  std::cout << "\nMinimum steps required: " << steps << std::endl;

  // Verify if we reached the target
  if (ArraysEqual(current, target, size)) {
    std::cout << "Successfully reached target sequence!\n";
  } else {
    std::cout << "Warning: Could not reach target sequence with this approach.\n";
  }

  delete[] current;
  return steps;
}

/**
 * Initialize CSV file with headers
 */
void InitializeCSVFile(const char* filename) {
  FILE* file = fopen(filename, "w");
  if (file != NULL) {
    fprintf(file, "n_elements,r_combination_size,combinations_count,execution_time_microseconds\n");
    fclose(file);
    std::cout << "CSV file '" << filename << "' initialized with headers.\n";
  } else {
    std::cout << "Error: Could not create CSV file '" << filename << "'.\n";
  }
}

/**
 * Log results to CSV
 */
void LogResultsToCSV(const char* filename, int n, int r, int combinations_count, long execution_time_microseconds) {
  FILE* file = fopen(filename, "a");
  if (file != NULL) {
    fprintf(file, "%d,%d,%d,%ld\n", n, r, combinations_count, execution_time_microseconds);
    fclose(file);
    std::cout << "Results logged to CSV: n=" << n << ", r=" << r << ", count=" << combinations_count << ", time=" << execution_time_microseconds << " μs\n";
  } else {
    std::cout << "Error: Could not open CSV file '" << filename << "' for writing.\n";
  }
}

int main() {
  std::cout << "PERMUTATION GENERATOR PROJECT\n";
  std::cout << "============================\n";

  InitializeCSVFile("combination_results.csv");

  std::cout << "\n=== RUNNING MULTIPLE COMBINATION EXAMPLES ===\n";

  // Test Case 1: Original example - 4 elements, combinations of size 2
  std::cout << "\n--- Test Case 1: C(4,2) ---";
  int elements1[] = {1, 2, 3, 4};
  GenerateCombinations(elements1, 4, 2);

  /*
  // Test Case 2: 3 elements, combinations of size 2
  std::cout << "\n--- Test Case 2: C(3,2) ---";
  int elements2[] = {1, 2, 3};
  GenerateCombinations(elements2, 3, 2);

  // Test Case 3: 5 elements, combinations of size 2
  std::cout << "\n--- Test Case 3: C(5,2) ---";
  int elements3[] = {1, 2, 3, 4, 5};
  GenerateCombinations(elements3, 5, 2);

  // Test Case 4: 4 elements, combinations of size 3
  std::cout << "\n--- Test Case 4: C(4,3) ---";
  int elements4[] = {1, 2, 3, 4};
  GenerateCombinations(elements4, 4, 3);

  // Test Case 5: 5 elements, combinations of size 3
  std::cout << "\n--- Test Case 5: C(5,3) ---";
  int elements5[] = {1, 2, 3, 4, 5};
  GenerateCombinations(elements5, 5, 3);

  // Test Case 6: 6 elements, combinations of size 2
  std::cout << "\n--- Test Case 6: C(6,2) ---";
  int elements6[] = {1, 2, 3, 4, 5, 6};
  GenerateCombinations(elements6, 6, 2);

  // Test Case 7: 6 elements, combinations of size 3
  std::cout << "\n--- Test Case 7: C(6,3) ---";
  int elements7[] = {1, 2, 3, 4, 5, 6};
  GenerateCombinations(elements7, 6, 3);

  // Test Case 8: 5 elements, combinations of size 4
  std::cout << "\n--- Test Case 8: C(5,4) ---";
  int elements8[] = {1, 2, 3, 4, 5};
  GenerateCombinations(elements8, 5, 4);

  // Test Case 9: 6 elements, combinations of size 4
  std::cout << "\n--- Test Case 9: C(6,4) ---";
  int elements9[] = {1, 2, 3, 4, 5, 6};
  GenerateCombinations(elements9, 6, 4);

  std::cout << "\n=== COMBINATION TESTING COMPLETED ===\n";
  std::cout << "Results saved to: combination_results.csv\n";

  // Extra Performance Tests - High Computational Load
  std::cout << "\n=== RUNNING EXTRA PERFORMANCE TESTS ===\n";
  std::cout << "WARNING: These tests may take significant time!\n";

  // Test Case 10: C(10,5) = 252 combinations
  std::cout << "\n--- Extra Test Case 10: C(10,5) ---";
  int elements10[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GenerateCombinations(elements10, 10, 5);

  // Test Case 11: C(12,6) = 924 combinations
  std::cout << "\n--- Extra Test Case 11: C(12,6) ---";
  int elements11[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  GenerateCombinations(elements11, 12, 6);

  // Test Case 12: C(15,7) = 6.435 combinations
  std::cout << "\n--- Extra Test Case 12: C(15,7) ---";
  int elements12[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  GenerateCombinations(elements12, 15, 7);

  // Test Case 13: C(18,9) = 48.620 combinations
  std::cout << "\n--- Extra Test Case 13: C(18,9) ---";
  int elements13[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
  GenerateCombinations(elements13, 18, 9);

  std::cout << "\n=== EXTREME PERFORMANCE TESTING COMPLETED ===\n";

   */

  // Function 2
  std::cout << "\n=== RUNNING PERMUTATION EXAMPLE ===\n";
  int initial[] = {1, 2, 3, 4};
  int target[] = {4, 3, 2, 1};
  int size = 4;

  FindMinimumSteps(initial, target, size);

  std::cout << "\n=== PROGRAM COMPLETED ===\n";

  return 0;
}
