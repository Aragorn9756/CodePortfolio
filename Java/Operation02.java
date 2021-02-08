/******************************************************
*Operation02.java for Operation02 assignment
*Written by Stephen Richardson 01/23/17
*
*Takes the the user's birthdate and calculates the potential retirement date.
******************************************************/
import java.util.Scanner;

public class Operation02
{

   public static void main (String[] args)
   {
   
      Scanner in = new Scanner (System.in);
      
      //initialized variables
      String birthMonth = "hi";
      int birthDay = 0;
      int birthYear = 0;
      int retireYear = 0;
      
            
      //get user to enter in birth month
      System.out.println("Please enter the month of your birth. ex. June");
      birthMonth = in.nextLine();
      
      //get user to enter in birth day
      System.out.println("Please enter the day of your birth. ex. 04");
      birthDay = in.nextInt();
      
      //get user to enter birth year
      System.out.println("Please enter the year of your birth. ex. 1993");
      birthYear = in.nextInt();
      
      //Calculate the retirement year
      retireYear = birthYear + 67;
      
      //tell user their retirement year
      System.out.println("You will ostensibly retire on...\n" + birthMonth + " " + birthDay + ", " + retireYear +"!");
   
   }//end main

}//end class