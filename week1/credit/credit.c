#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get input as card number 
    long card_number = get_long("Number: ");
    
    //Count length of the number
    int i = 0;
    long num = card_number;
    while (num > 0)
    {
        num = num / 10;
        i++;
    }
    
    //Check the length to be 13,15 or 16
    if (i != 13 && i != 15 && i != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    
    //Checksum
    int sum = 0;
    int sum2 = 0;
    long n = card_number; 
    int total = 0; 
    int mod1;
    int mod2; 
    int dig1;
    int dig2;
    
    do
    {
        //Add last number to sum
        mod1 = n % 10;
        n = n / 10;
        sum = sum + mod1;
        
        //second last digit 
        mod2 = n % 10;
        n = n / 10;
        
        //multiply by two and sum 
        mod2 = mod2 * 2;
        dig1 = mod2 % 10;
        dig2 = mod2 / 10;
        sum2 = sum2 + dig1 + dig2;
    }
    while (n > 0);
    total = sum + sum2; 
    
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    //Find starting number 
    long star_num = card_number;
    do  
    {
        star_num = star_num / 10;
    }
    while (star_num > 100);
    
    if ((star_num / 10 == 5) && (star_num % 10 > 0 && star_num % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((star_num / 10 == 3) && (star_num % 10 == 4 || star_num % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (star_num / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}