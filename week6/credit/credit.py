import cs50
from cs50 import get_int
from math import floor
import sys 


def main():
    
    d1 = 0
    total = 0
    odds = 0
    evens = 0
    
    # Card number input
    number = get_int("Number: ")
    sum_d = len(str(number))
    
    # Read number as string to access each digit 
    num_s = str(number)
    
    # Check number of digits
    if sum_d != 13 and sum_d != 15 and sum_d != 16:
        print("INVALID")
        sys.exit()
    
    while number > 0:
        # Initialize digits and start from the end
        d1 = number % 10
        
        # Sum even digits 
        if total % 2 == 0:
            evens += d1
        
        # Sum multiply odd digits by 2, separate two digits and sum each
        else:
            double = d1 * 2
            odds += (double // 10) + (double % 10)
        
        # Move to the next digit from the end
        number //= 10
        total += 1
    
    # Sum adds and evens and if checksum is even 
    checksum = (odds + evens)
    if checksum % 2 == 0:
        # Access first two digit, check and match to each card type
        if int(num_s[0]) == 3 and int(num_s[1]) == 4 or int(num_s[1]) == 7:
            print("AMEX")
            
        elif int(num_s[0]) == 5 and int(num_s[1]) == 1 or int(num_s[1]) == 2 or int(num_s[1]) == 3 or int(num_s[1]) == 4 or int(num_s[1]) == 5:
            print("MASTERCARD")
            
        elif int(num_s[0]) == 4:
            print("VISA")
            
        # Invalid if no match    
        else:
            ("INVALID")


if __name__ == "__main__":
    main()            