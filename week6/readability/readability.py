import cs50
from cs50 import get_string


def main():
    # Prompt for text input
    txt_input = get_string("Text: ")
    # Note the length of the text
    txt_len = len(txt_input)
    
    # Initialize l, w, s and i
    letter = 0
    # Split the text into words and count with len()
    word = len(txt_input.split())
    sent = 0
    i = 0
    
    # Loop itiration until done (length of text input)
    while i < txt_len:
        # If alphabetic add letters
        if txt_input[i].isalpha():
            letter += 1
        # If end of sentence add sent
        if txt_input[i] == "." or txt_input[i] == "!" or txt_input[i] == "?":
            sent += 1
        i += 1
        
    # Apply grading formula and round up 
    L = 100 * letter / word
    S = 100 * sent / word
    grade = round((0.0588 * L) - (0.296 * S) - 15.8)

    # Check grade and print out
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()                