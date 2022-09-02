import cs50
import csv
from sys import argv
from sys import exit
from cs50 import get_string 


# Function to find maximum number of value matches
def max_num_match(sq, key):
    
    # Initialize zero values with length of given sequence 
    match = [0] * len(sq)
    
    # Go through each str from the end
    for i in range(len(sq) - len(key), -1, -1):
        # If lenght of the str and if does not go beyong the length of the sequence, increment match
        if sq[i: i + len(key)] == key:
            if i + len(key) > len(sq) - 1:
                match[i] = 1
            else:
                match[i] = 1 + match[i + len(key)]
    # Return the max matched value            
    return max(match)


# Find matches of str counts from csv file
def find_match(db, count):
    for row in db:
        name = row[0]
        data = [int(num) for num in row[1:]]
        if data == count:
            print(name)
            return
    print("No match")
 
    
# Main function
def main():
    # Check correct input, otherwise exit
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()
    
    # Open and read the csv file
    dbs = argv[1]
    with open(dbs, "r") as csv_file:
        db = csv.reader(csv_file)
        
        # Include values from the second position
        key_head = next(db)[1:]
        
        # Open and read the text file
        sqs = argv[2]
        with open(sqs, "r") as txt_file:
            sq = txt_file.read()
            
            # Sum matches of str, take key from csv file and count in text file
            count = [max_num_match(sq, key) for key in key_head]
        
        # Apply function of finding matches of numbers in csv file and counts in text file 
        find_match(db, count)
 
 
if __name__ == "__main__":
    main() 