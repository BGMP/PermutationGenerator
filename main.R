# R Script for Comparing C++ vs Python itertools Performance
# Load and analyze the CSV results from both implementations

library(ggplot2)
library(dplyr)
library(readr)

cat("Loading CSV files...\n")

cpp_results <- read_csv("combination_results.csv")
cpp_results$implementation <- "C++ Impl"

python_itertools <- read_csv("python_itertools_results.csv")
python_itertools$implementation <- "Python itertools"

all_results <- rbind(cpp_results, python_itertools)

cat("\n=== GENERATING PLOTS ===\n")

# Plot 1: Execution time comparison by test case (LOG SCALE)
# Create ordered factor for test cases based on combinations count
all_results$test_case <- paste("C(", all_results$n_elements, ",", all_results$r_combination_size, ")", sep="")

test_case_order <- all_results %>%
  select(test_case, combinations_count) %>%
  distinct() %>%
  arrange(combinations_count) %>%
  pull(test_case)

all_results$test_case <- factor(all_results$test_case, levels = test_case_order)

p1 <- ggplot(all_results, aes(x = test_case, 
                              y = execution_time_microseconds, 
                              fill = implementation)) +
  geom_bar(stat = "identity", position = "dodge", alpha = 0.8) +
  scale_y_log10() +
  labs(title = "Execution Time Comparison (LOG SCALE): C++ Impl vs Python itertools",
       subtitle = "Test cases ordered by complexity (left to right: increasing execution time)",
       x = "Test Case (ordered by complexity)",
       y = "Execution Time (microseconds) - LOG SCALE",
       fill = "Implementation") +
  theme_minimal() +
  theme(axis.text.x = element_text(angle = 45, hjust = 1),
        legend.position = "top") +
  scale_fill_manual(values = c("C++ Impl" = "#FF6B6B", 
                               "Python itertools" = "#4ECDC4"))

# Plot 2: Exponential growth visualization
p2 <- ggplot(all_results, aes(x = combinations_count, 
                              y = execution_time_microseconds, 
                              color = implementation)) +
  geom_point(size = 4, alpha = 0.8) +
  geom_line(aes(group = implementation), size = 1.2, alpha = 0.7) +
  scale_x_log10() +
  scale_y_log10() +
  labs(title = "Exponential Growth: Combinations vs Execution Time (LOG-LOG SCALE)",
       subtitle = "Shows how performance degrades with problem size",
       x = "Number of Combinations Generated (LOG SCALE)",
       y = "Execution Time (microseconds, LOG SCALE)",
       color = "Implementation") +
  theme_minimal() +
  theme(legend.position = "top") +
  scale_color_manual(values = c("C++ Impl" = "#FF6B6B", 
                                "Python itertools" = "#4ECDC4"))

print(p1)
print(p2)

ggsave("cpp_vs_python_performance_log.png", p1, width = 14, height = 8, dpi = 300)
ggsave("cpp_vs_python_exponential_growth.png", p2, width = 12, height = 8, dpi = 300)