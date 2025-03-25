# Function to read, process, and write the file
def process_file(input_file, output_file=None):
    try:
        # Read the file
        with open(input_file, 'r') as file:
            content = file.read()
        
        # Replace -1 with 01
        processed_content = content.replace('-','').replace('1', '01').replace('2','01')

        # Write to the output file or overwrite the original file
        if output_file:
            with open(output_file, 'w') as file:
                file.write(processed_content)
        else:
            with open(input_file, 'w') as file:
                file.write(processed_content)

        print("File processed successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
input_file = "gameMap3.txt"  # Replace with your input file path
output_file = "map2.txt"  # Optional: Replace with your desired output file path
process_file(input_file, output_file)
