import re

def add_zero_to_digits(file_path):
    # Read the content of the file
    with open(file_path, 'r') as file:
        content = file.read().replace(',', ' ')

    # Process each character and check for one-digit numbers
    updated_content = ''
    temp = ""
    
    for i in range(len(content)):
        if content[i].isdigit():
            temp += content[i]
        else:
            # Process the number if temp is not empty
            if temp:
                temp2 = int(temp)

                if temp2 == 343:
                    updated_content += "0"
                elif temp2 == 0:
                    updated_content += "-1"
                elif temp2 == 2:
                    updated_content += "1"
                else:
                    updated_content += "?"
                
                temp = ""

            # Append the current character if it's not a digit
            updated_content += content[i]
    
    # Handle any remaining number at the end
    if temp:
        temp2 = int(temp)
        if temp2 == 343:
            updated_content += "0"
        elif temp2 == 0:
            print("roh tekhra")
            updated_content += "-1"
        elif temp2 == 2:
            updated_content += "1"
        else:
            updated_content += "?"
            

    # Write the updated content back to the file
    with open(file_path, 'w') as file:
        file.write(updated_content)

    print("All one-digit numbers have been updated with a '0' behind them.")

# Example usage
file_path = 'gameMap2.txt'
add_zero_to_digits(file_path)
