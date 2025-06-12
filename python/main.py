#!/usr/bin/env python3
"""
Python Combination Generator using itertools

Desc: Python implementation using itertools.combinations
Compares performance with C++ basic implementation.

04/06/2025 (BGM)
Python itertools implementation.
"""

import itertools
import time
import csv
from typing import List, Tuple

def print_array(arr: List[int]) -> None:
    """Print array in same format as C++ version"""
    print(' '.join(map(str, arr)))

def print_combination(combination: Tuple[int, ...]) -> None:
    """Print combination in same format as C++ version"""
    print(''.join(map(str, combination)))

def generate_combinations_itertools(elements: List[int], n: int, r: int) -> int:
    """
    Generate all combinations using itertools.combinations
    Measures execution time and returns count of combinations
    """
    print(f"\n=== PYTHON ITERTOOLS: GENERATING COMBINATIONS ===")
    print("Elements: ", end="")
    print_array(elements)
    print(f"Generating combinations of size {r} from {n} elements\n")

    # Start timing (using time.perf_counter for microsecond precision)
    start_time = time.perf_counter()

    # Generate combinations using itertools
    combinations_list = list(itertools.combinations(elements, r))

    # End timing
    end_time = time.perf_counter()
    execution_time_seconds = end_time - start_time
    execution_time_microseconds = int(execution_time_seconds * 1_000_000)

    # Display results (similar to C++ format)
    count = 0
    for combination in combinations_list:
        count += 1
        print(f"Combination {count}: ", end="")
        print_combination(combination)

    print(f"\nTotal combinations found: {count}")
    print(f"Execution time: {execution_time_microseconds} microseconds")

    # Log results to CSV
    log_results_to_csv("../python_itertools_results.csv", n, r, count, execution_time_microseconds)

    return count

def initialize_csv_file(filename: str) -> None:
    """Initialize CSV file with headers (same format as C++ version)"""
    try:
        with open(filename, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['n_elements', 'r_combination_size', 'combinations_count', 'execution_time_microseconds'])
        print(f"CSV file '{filename}' initialized with headers.")
    except IOError:
        print(f"Error: Could not create CSV file '{filename}'.")

def log_results_to_csv(filename: str, n: int, r: int, combinations_count: int, execution_time_microseconds: int) -> None:
    """Log results to CSV file (same format as C++ version)"""
    try:
        with open(filename, 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([n, r, combinations_count, execution_time_microseconds])
        print(f"Results logged to CSV: n={n}, r={r}, count={combinations_count}, time={execution_time_microseconds} μs")
    except IOError:
        print(f"Error: Could not open CSV file '{filename}' for writing.")

def main():
    """Main function with same test cases as C++ implementation"""
    print("PYTHON COMBINATION GENERATOR - ITERTOOLS IMPLEMENTATION")
    print("=====================================================")

    # Initialize CSV file with headers
    initialize_csv_file("../python_itertools_results.csv")

    print("\n=== RUNNING MULTIPLE COMBINATION EXAMPLES ===")

    # Test Case 1: C(4,2) - Same as C++ original example
    print("\n--- Test Case 1: C(4,2) ---")
    generate_combinations_itertools([1, 2, 3, 4], 4, 2)

    # Test Case 2: C(3,2)
    print("\n--- Test Case 2: C(3,2) ---")
    generate_combinations_itertools([1, 2, 3], 3, 2)

    # Test Case 3: C(5,2)
    print("\n--- Test Case 3: C(5,2) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5], 5, 2)

    # Test Case 4: C(4,3)
    print("\n--- Test Case 4: C(4,3) ---")
    generate_combinations_itertools([1, 2, 3, 4], 4, 3)

    # Test Case 5: C(5,3)
    print("\n--- Test Case 5: C(5,3) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5], 5, 3)

    # Test Case 6: C(6,2)
    print("\n--- Test Case 6: C(6,2) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6], 6, 2)

    # Test Case 7: C(6,3)
    print("\n--- Test Case 7: C(6,3) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6], 6, 3)

    # Test Case 8: C(5,4)
    print("\n--- Test Case 8: C(5,4) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5], 5, 4)

    # Test Case 9: C(6,4)
    print("\n--- Test Case 9: C(6,4) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6], 6, 4)

    print("\n=== BASIC COMBINATION TESTING COMPLETED ===")

    # Extra Performance Tests - High Computational Load
    print("\n=== RUNNING EXTRA PERFORMANCE TESTS ===")
    print("WARNING: These tests may take significant time!")

    # Test Case 10: C(10,5) = 252 combinations
    print("\n--- Extra Test Case 10: C(10,5) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 10, 5)

    # Test Case 11: C(12,6) = 924 combinations
    print("\n--- Extra Test Case 11: C(12,6) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], 12, 6)

    # Test Case 12: C(15,7) = 6.435 combinations
    print("\n--- Extra Test Case 12: C(15,7) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15], 15, 7)

    # Test Case 13: C(18,9) = 48.620 combinations
    print("\n--- Extra Test Case 13: C(18,9) ---")
    generate_combinations_itertools([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18], 18, 9)

    print("\n=== EXTREME PERFORMANCE TESTING COMPLETED ===")

    print("\n=== COMBINATION TESTING COMPLETED ===")
    print("Results saved to: python_itertools_results.csv")

if __name__ == "__main__":
    main()
