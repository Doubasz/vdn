import re

def add_zero_to_digits(file_path):
    # Read the content of the file
    with open(file_path, 'r') as file:
        content = file.read().replace(',', ' ')

    # Process each character and check for one-digit numbers
    updated_content = ''
    for i in range(len(content)):
        if content[i].isdigit() and (i == 0 or not content[i-1].isdigit()) and (i == len(content)-1 or not content[i+1].isdigit()):
            updated_content += '0' + content[i]
        else:
            updated_content += content[i]
        

    # Write the updated content back to the file
    with open(file_path, 'w') as file:
        file.write(updated_content)

    print("All one-digit numbers have been updated with a '0' behind them.")

# Example usage
file_path = 'map1.txt'
add_zero_to_digits(file_path)
