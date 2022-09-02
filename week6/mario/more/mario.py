import cs50
from cs50 import get_int


def main():
    # Prompts the user input between 1 & 8
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break
        
    # Goes through each row 
    for row in range(0, height):
        
        # Inserts spaces on the left 
        for space in range(1, height - row):
            print(" ", end="")
            
        #  Fills the left side
        for left in range(height - row, height + 1):
            print("#", end="")
        
        # Adds spaces    
        print(" ", end="")
        print(" ", end="")
        
        #  Fills the right side
        for right in range(height - row, height + 1):
            print("#", end="")
        
        # Prints new line
        print()


main()