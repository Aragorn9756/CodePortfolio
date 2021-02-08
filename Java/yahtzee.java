 n/************************************************************************
*yahtzee.java
*created by Stephen Richardson
*
*This program is modified version of yahtzee. It will roll 5 dice, print
*out the results and let the user decide what dice they want to reroll.
*the program will then look at the final numbers and interpret them as
*a yahtzee, large straight, small straight, full house, 4 of a kind and
*3 of a kind. there is also a cheaters mode accessed by pressing "c" when
*asked whether or not they would like to play another round.
************************************************************************/
//import necessary elements
import java.util.Random;
import java.util.ArrayList;
import java.util.Scanner;

public class yahtzee
{

   public static void main(String[] args)
   {
      //declare ArrayList Random and Scanner
      ArrayList <String> diceValues = new ArrayList <String> ();
      Random roll = new Random();
      Scanner in = new Scanner(System.in);
      
      //declaration
      int roundNum = 1;
      int die = -1;//placeholder for number rolled between generating and placement in array
      int rollNum = 0;//how many rolls the player has performed
      int points = 0;//players points
      int orderedHand = 0;//hand after it has been ordered by finalHandOrder method
      
      String cheatersHand = "";//where user input numbers are held in cheater's mode
      String quit = "";
      String endRoll = "";
      String outcome = "";
      String currentHand = "";
      
      //initialize diceValues ArrayList
      for (int h = 0; h < 5; h++)
      {
         diceValues.add("0");
      }// end for
      
      System.out.println("Welcome to Stephen's Modified Yahtzee!\n");
      System.out.println("This version of Yahtzee plays similarly to regular Yahtzee, however\n"
      + "you will only be able to score a Yahtzee, Large Straight, Small Straight,\nFull House,"
      + " 4 of a Kind, or 3 of a Kind. \n\nHere we go!");
      
      do
      {
         //re-initialize rollNum
         rollNum = 1;
      
         System.out.println("Round " + roundNum);
         
         //roll die initially and save them into array list
         for (int i = 0; i < 5; i++)
         {
            die = (roll.nextInt(6) + 1);
            diceValues.set(i, Integer.toString(die));
         }//end for
         
         do
         {
            System.out.println("Roll # " + rollNum);
            System.out.println("You rolled: " + diceValues);
            
            //get current hand
            currentHand = "[" +diceValues.get(0) + ", " + diceValues.get(1) + ", " + diceValues.get(2) + 
            ", " + diceValues.get(3) + ", " + diceValues.get(4) + "]";
            
            //determine whether or not to re-roll
            System.out.println("Would you like to roll any dice again? Y or N?");
            endRoll = in.nextLine();
            
            if (endRoll.equalsIgnoreCase("N"))
            {
               rollNum = 3;
            }//end if
            
            //decide which dice to re-roll
            else
            {
               for (int j = 1; j <=5; j++)
               {
                  System.out.println("Numbering the values from left to right going 1-5,\n"
                  + "would you like to reroll die # " + j + "? Y or N? \n Here is your current"
                  + " hand: " + currentHand + ".");
                  endRoll = in.nextLine();
                  
                  //re-roll designated die, if so desired
                  if (endRoll.equalsIgnoreCase("Y"))
                  {
                     die = (roll.nextInt(6) + 1);
                     diceValues.set((j-1), Integer.toString(die));
                  }//end if
               }//end for
               
               rollNum++;  
            }//end else
         }while (rollNum < 3);//end do while
         
         //display final hand
         System.out.println("Your final hand is: " + diceValues);
        
         orderedHand = finalHandOrder(diceValues.get(0), diceValues.get(1), diceValues.get(2), 
         diceValues.get(3), diceValues.get(4));
        
         // get outcome of hand
         outcome = finalOutcome(orderedHand);
         
         //configure points
         if (outcome.equals("a Yahtzee!!!"))
         {
            points += 50;
         }
         else if (outcome.equals("a Large Straight!!"))
         {
            points += 45;
         }
         else if (outcome.equals("a Small Straight!!"))
         {
            points += 40;
         }
         else if (outcome.equals("a Full House!"))
         {
            points += 35;
         }
         else if (outcome.equals("4 of a Kind!"))
         {
            points += 30;
         }
         else if (outcome.equals("3 of a Kind!"))
         {
            points += 25;
         }
         
         // print outcome
         System.out.println("You scored " + outcome);
        
         roundNum++;
         
         System.out.println("Would you like to play another round? Y or N?");
         quit = in.nextLine();//press "c" to enter cheaters mode
         
      }while (quit.equalsIgnoreCase("Y"));//end do while
      
      //cheaters mode
      if (quit.equalsIgnoreCase("C"))
      {
         System.out.println("Welcome to Cheater's Mode!");
         
         do
         {
         //collect numbers from user
         System.out.println("Please enter five integers from 1-6.");
         cheatersHand = in.nextLine();
         
         //order numbers and get outcome
         orderedHand = finalHandOrder(Character.toString(cheatersHand.charAt(0)), Character.toString(cheatersHand.charAt(1)),
         Character.toString(cheatersHand.charAt(2)), Character.toString(cheatersHand.charAt(3)), 
         Character.toString(cheatersHand.charAt(4)));
         
         outcome = finalOutcome(orderedHand);
         
         // print outcome
         System.out.println("You scored " + outcome);
         
         System.out.println("Would you like to play another round? Y or N?");
         quit = in.nextLine();
         
         }while (quit.equalsIgnoreCase("Y"));
      }//end if
      
      //goodbye statement
      System.out.println("Your final score was " + points + " points. \n Thanks for playing!");
   }//main method
   
   //this method puts the final number into numerical order
   public static int finalHandOrder (String die1, String die2, String die3, String die4, String die5)
   {
      ArrayList <String> diceValues = new ArrayList <String> ();
      
      String orderedString;//The ordered number in a string
      
      int index = 0;
      int orderedNum;
      
      //recreating ArrayList
      diceValues.add(die1);
      diceValues.add(die2);
      diceValues.add(die3);
      diceValues.add(die4);
      diceValues.add(die5);
      
      //ordering the array
      for (int i = 1; i <= 6; i++)
      {
         for (int j = 0; j < 5; j++)
         {
            if (Integer.parseInt(diceValues.get(j)) == i)
            {
               diceValues.add(index, Integer.toString(i));
               diceValues.remove(j+1);
            }//end if  
         }//end for
         
         //check for next int 
         if (diceValues.contains(Integer.toString(i)))
         {
            index = diceValues.lastIndexOf(Integer.toString(i)) + 1; 
         }//end if
      }//end for
      
      //getting ordered array into a continuous number
      orderedString = diceValues.get(0) + diceValues.get(1) + diceValues.get(2) + 
      diceValues.get(3) + diceValues.get(4);
      
      orderedNum = Integer.parseInt(orderedString);
      
      return orderedNum;
   }//end finalhHandOrder method
   
   public static String finalOutcome (int orderedHand)
   {
      String outcome = "";
      
      //switch statement to determine outcome
      switch (orderedHand)
      {
         case 11111: case 22222: case 33333: case 44444: case 55555: case 66666:
            outcome = "a Yahtzee!!!";
            break;
         case 12345: case 23456:
            outcome = "a Large Straight!!";
            break;
         case 11234: case 12234: case 12334: case 12344: case 12346: case 22345: case 23345: case 23445:
         case 23455: case 13456: case 33456: case 34456: case 34556: case 34566:
            outcome = "a Small Straight!!";
            break;
         case 11222: case 11333: case 11444: case 11555: case 11666: case 11122: case 11133: case 11144:
         case 11155: case 11166: case 22333: case 22444: case 22555: case 22666: case 22233: case 22244:
         case 22255: case 22266: case 33444: case 33555: case 33666: case 33344: case 33355: case 33366:
         case 44555: case 44666: case 44455: case 44466: case 55666: case 55566:
            outcome = "a Full House!";
            break;
         case 11112: case 11113: case 11114: case 11115: case 11116: case 12222: case 22223: case 22224:
         case 22225: case 22226: case 13333: case 23333: case 33334: case 33335: case 33336: case 14444:
         case 24444: case 34444: case 44445: case 44446: case 15555: case 25555: case 35555: case 45555:
         case 55556: case 16666: case 26666: case 36666: case 46666: case 56666:
            outcome = "4 of a Kind!";
            break;
         case 11123: case 11124: case 11125: case 11126: case 11134: case 11135: case 11136: case 11145:
         case 11146: case 11156: case 12223: case 12224: case 12225: case 12226: case 22234: case 22235: 
         case 22236: case 22245: case 22246: case 22256: case 12333: case 13334: case 13335: case 13336:
         case 23334: case 23335: case 23336: case 33345: case 33346: case 33356: case 12444: case 13444:
         case 14445: case 14446: case 23444: case 24445: case 24446: case 34445: case 34446: case 44456:
         case 12555: case 13555: case 14555: case 15556: case 23555: case 24555: case 25556: case 34555:
         case 35556: case 45556: case 12666: case 13666: case 14666: case 15666: case 23666: case 24666:
         case 25666: case 34666: case 35666: case 45666:
            outcome = "3 of a Kind!";
            break;
         default:
            outcome = "nothing...";                     
      }//end switch
      
      return outcome;
   }//end finalOutcome method
}//end class