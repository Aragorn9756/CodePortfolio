/******************************************************
*HigherLowerGame.java
*Written by Stephen Richardson
*
*This is a program created for Operation 03. It is a
*simple game where a random number is generated and the user
*tries to guess it. The program will prompt the user to guess
*higher or lower until the correct number is guessed as well 
*as track the number of guesses.
******************************************************/
import java.util.Scanner;
import java.util.Random;

public class HigherLowerGame
{
   public static void main (String[] args)
   {
      Scanner in = new Scanner (System.in);
      Random r = new Random();
      
      int numberToGuess = 0;
      int guessedNumber = 0;
      int numberOfGuesses = 0;
      String playAgain = "";
      
      //Greeting
      System.out.println("Welcome to the Higher or Lower game!");
      
      //Playing the game
      do
      {
         //resetting number of guesses
         numberOfGuesses = 0;
         
         //generating our number
         numberToGuess = r.nextInt(100) + 1;
         
         //collecting user input
         System.out.println("Try to guess correct number!");
         System.out.println("Please choose a number between 1 and 100.");
         guessedNumber = in.nextInt();
         
         //flushing the buffer
         in.nextLine();
         
         //checking for valid input
         while (guessedNumber < 1 || guessedNumber > 100)
         {
            System.out.println("I'm sorry, but that is not a valid input.");
            System.out.println("Please choose a number between 1 and 100.");
            guessedNumber = in.nextInt();
            
            //flushing the buffer
            in.nextLine();
         }//end while loop
         
         numberOfGuesses++;
         
         //if guess is wrong
         while (guessedNumber != numberToGuess)
         {
            //if the answer is lower
            if (guessedNumber > numberToGuess)
            {
               System.out.println("Nope. The number is lower. Try again.");
               System.out.println("Please choose a number between 1 and 100.");
               guessedNumber = in.nextInt();
               
               //flushing the buffer
               in.nextLine();
               
              //checking for valid input
               while (guessedNumber < 1 || guessedNumber > 100)
               {
                  System.out.println("I'm sorry, but that is not a valid input.");
                  System.out.println("Please choose a number between 1 and 100.");
                  guessedNumber = in.nextInt();
                  
                  //flushing the buffer
                  in.nextLine();
               }//end while loop 
               
               numberOfGuesses++;   
            }// end if loop
            
            //if the answer is higher
            else if (guessedNumber < numberToGuess)
            {
               System.out.println("Nope. The number is higher. Try again.");
               System.out.println("Please choose a number between 1 and 100.");
               guessedNumber = in.nextInt();
               
               //flushing the buffer
               in.nextLine();
               
              //checking for valid input
               while (guessedNumber < 1 || guessedNumber > 100)
               {
                  System.out.println("I'm sorry, but that is not a valid input.");
                  System.out.println("Please choose a number between 1 and 100.");
                  guessedNumber = in.nextInt();
                  
                  //flushing the buffer
                  in.nextLine();
               }//end while loop
               
               numberOfGuesses++;   
            }//end else if loop
         }//end while loop
         
         //when guessed correctly
         System.out.println("Congratulations! You guessed correctly!");
         System.out.println("The number was " + numberToGuess + 
            " and it took you " + numberOfGuesses + " guesses.");
         
         //Continue?
         System.out.println("Would you like to play again? Y or N?");
         playAgain = in.nextLine();
         
         //Checking for valid input
         while (!(playAgain.equalsIgnoreCase("Y") || playAgain.equalsIgnoreCase("N")))
         {
            System.out.println("I'm sorry, but that is not a valid input.");
            System.out.println("Would you like to play again? Y or N?");
            playAgain = in.nextLine();
         }
      }while (playAgain.equalsIgnoreCase("Y"));
      
      //Thanking the user for using my program
      System.out.println("Thank you for playing! Please come again!");
   }//end main 
}//end class HigherLowerGame.java