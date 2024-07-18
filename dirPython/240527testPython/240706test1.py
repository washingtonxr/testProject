def classify_values(original_data):
    # Create a set of the original data for quick lookup
    original_set = set(original_data)
    
    # Create a dictionary to store the sums and their coordinates
    sum_dict = {}
    
    # Iterate through all possible pairs of elements
    for i in range(len(original_data)):
        for j in range(i + 1, len(original_data)):
            new_sum = original_data[i] + original_data[j]
            
            # Add the sum to the dictionary with its coordinates if it's not already present
            if new_sum not in original_set:
                sum_dict[new_sum] = (i, j)
    
    # Function to classify a value
    def classify_value(value):
        if value in original_set:
            return 'Original data'
        elif value in sum_dict:
            return f'Sum of indices {sum_dict[value]}'
        else:
            return 'Unknown value'
    
    return classify_value

# Initial data
original_data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

# Get the classification function
classify_value = classify_values(original_data)

# Example usage
test_values = [2, 12, 15, 21]  # 2: original, 12: sum, 15: sum, 21: unknown
results = {value: classify_value(value) for value in test_values}

print(results)
