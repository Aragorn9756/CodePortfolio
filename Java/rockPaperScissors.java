/*******************************************************
*rockPaperScissors.java
*Written by Stephen Richardson
*
*This program is a simple rock, paper, scissors game.
*The user inputs their choice, then the computer generates
*a choice and a winner is determined. This goes for a set
*number of rounds with a record of user and computer wins kept.
********************************************************/
import java.util.Random;
import java.util.Scanner;

public class rockPaperScissors
{
   public static void main(String[] args)
   {
      //calling in scanner and random
      Random ran = new Random();
      Scanner in = new Scanner(System.in);
      
      //initializing variables
      int numOfRounds = 0;
      int user = 0;//holds the users choice i.e. rock, paper, or scissors
      int com = 0;//holds computers choice
      int userWins = 0;
      int comWins = 0;
      double winPer = 0.0;
      double lossPer = 0.0;
      
      String userInput = "";
      String comChoice = "";//holds the statement for the computers choice
      String outcome = "";// holds the statement for who wins
      
      //welcome statement
      System.out.println("Welcome to Stephen's Rock, Paper or Scissors!");
      
      do
      {
         //re-initialize variables
         userWins = 0;
         comWins = 0;
         user = 0;
         
         //choose the number of rounds
         System.out.println("How many rounds would you like to play? Choose an odd number: ");
         userInput = in.nextLine();
         
         numOfRounds = evenOddCheck(userInput);
         
         //start the game
         for(int i = 1; i <= numOfRounds; i++)
         {
            System.out.println("Round " + i);
            System.out.println("Please choose Rock, Paper or Scissors: ");
            userInput = in.nextLine();
            
            //check for invalid input
            userInput = inputCheck(userInput);
            
            //convert user input into #
            do
            {
               if (userInput.equalsIgnoreCase("Spock"))
               {
                  System.out.println("Spock is the ultimate, but maintains an unfair" + 
                  " advantage and is, therefore, not allowed.");
                  System.out.println("Please choose Rock, Paper or Scissors: ");
                  userInput = in.nextLine();
            
                  //check for invalid input
                  userInput = inputCheck(userInput);
               }
               else if (userInput.equalsIgnoreCase("Rock"))
               {
                  user = 1;
               }
               else if (userInput.equalsIgnoreCase("Paper"))
               {
                  user = 2;
               }
               else if (userInput.equalsIgnoreCase("Scissors"))
               {
                  user = 3;
               }
            }while (user == 0);//end while loop
            
            //decides computers pick
            com = ran.nextInt(3) + 1;
            
            //determines and saves statement of computers choice
            if(com == 1)
            {
               comChoice = "Computer chooses Rock. ";
            }
            else if (com == 2)
            {
               comChoice = "Computer chooses Paper. ";
            }
            else if (com == 3)
            {
               comChoice = "Computer chooses Scissors. ";
            }//end if statement
            
            //determines winner, tracks # of wins and saves results statement
            if ((user == 1 && com == 3) || (user == 2 && com == 1) || (user == 3 && com == 2))
            {
               outcome = "You win!";
               userWins++;
            }
            else if ((user == 1 && com == 2) || (user == 2 && com == 3) || (user == 3 && com == 1))
            {
               outcome = "You lost.";
               comWins++;
            }
            else if (user == com)
            {
               outcome = "It's a tie...";
            }//end if statement
            
            //print round results
            System.out.println(comChoice + outcome);
         
         }//end for loop
         
         //calculate win and loss percentage
         winPer = (userWins * 100.0) / numOfRounds;
         lossPer = (comWins * 100.0) / numOfRounds;
         
         //posting results
         System.out.println("You won " + userWins + " time(s).");
         System.out.println("The computer won " + comWins + " time(s).");
         
         //determines final winner
         if (userWins > comWins)
         {
            System.out.println("You won, winning " + winPer + "% of the time!");
         }
         else if (userWins < comWins)
         {
            System.out.println("You lost, losing " + lossPer + "% of the time.");
         }
         else if (userWins == comWins)
         {
            System.out.println("It's a tie....");
         }//end for statement
         
         System.out.println("Would you like to play again? Press" + 
         "\"Y\" to continue or \"Q\" to quit: ");
         userInput = in.nextLine();
         
         //check for invalid input
         userInput = inputCheck(userInput);
         
      }while (!userInput.equalsIgnoreCase("Q"));//end do/while loop
      
      System.out.println("Thanks for playing! Come again!");
   
   }//end main method
   
   public static String inputCheck (String input)//checks for input validity
   {
      Scanner in = new Scanner(System.in);
      
      //initialize variable
      String reply = "";
      
      do
      {
         if(input.equalsIgnoreCase("Rock"))
         {
            reply = input;
         }
         else if(input.equalsIgnoreCase("Paper"))
         {
            reply = input;
         }
         else if(input.equalsIgnoreCase("Scissors"))
         {
            reply = input;
         }
         else if(input.equalsIgnoreCase("Spock"))
         {
            reply = input;
         }
         else if(input.equalsIgnoreCase("Q"))
         {
            reply = input;
         }
         else if(input.equalsIgnoreCase("Y"))
         {
            reply = input;
         }
         else
         {
            System.out.println("Sorry, that is not a valid input. Please check your spelling" + 
            " and try again.: ");
            input = in.nextLine();
         }
      }while(reply.equals(""));//end do/while loop
      
      return reply;
   }//end inputCheck method
   
   public static int evenOddCheck(String number)
   {
      Scanner in = new Scanner(System.in);
      
      int integer = -1;
      int lastInt = -1;
      int lastIndex = -1;//holds index of last character
      
      char holder = ' ';//acts as placeholder until character can be converted to string
      String lastChar = "";
      
      do//determining whether number is odd or even
      {
         //finding last number and converting to int
         lastIndex = number.length() - 1;
         holder = number.charAt(lastIndex);
         lastChar = Character.toString(holder);
         lastInt = Integer.parseInt(lastChar);
         
         if(lastInt == 1)
         {
            integer = Integer.parseInt(number);
         }
         else if (lastInt == 3)
         {
           integer = Integer.parseInt(number);
         }
         else if (lastInt == 5)
         {
           integer = Integer.parseInt(number);
         }
         else if (lastInt == 7)
         {
           integer = Integer.parseInt(number);
         }
         else if (lastInt == 9)
         {
           integer = Integer.parseInt(number);
         }
         else//prompt user to try again
         {
            System.out.println("That is not an odd number. Please choose an odd number: ");
            number = in.nextLine();
         }
      }while(integer <= 0);
         
      return integer;
   }
}//end class