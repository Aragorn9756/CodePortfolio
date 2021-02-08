/********************************************************************************
*connectFour.java
*Created by Stephen Richardson
*
*This program lets the user play Connect Four against a computer. It uses 
*separate methods to check for a winning layout after each turn. You can also
*choose to play against the computer or with a friend
********************************************************************************/
import java.util.*;

public class connectFour
{
   static char[][] gameboard = new char[6][7];
   
   public static void printBoard()
   {
      //print out the gameboard
      System.out.println("| " + gameboard[0][0] + " | " + gameboard[0][1] + " | " 
      + gameboard[0][2] + " | " + gameboard[0][3] + " | " + gameboard[0][4] + " | " 
      + gameboard[0][5] + " | " + gameboard[0][6] + " |");
      
      System.out.println("|---+---+---+---+---+---+---|");
      
      System.out.println("| " + gameboard[1][0] + " | " + gameboard[1][1] + " | " 
      + gameboard[1][2] + " | " + gameboard[1][3] + " | " + gameboard[1][4] + " | " 
      + gameboard[1][5] + " | " + gameboard[1][6] + " |");
      
      System.out.println("|---+---+---+---+---+---+---|");
      
      System.out.println("| " + gameboard[2][0] + " | " + gameboard[2][1] + " | " 
      + gameboard[2][2] + " | " + gameboard[2][3] + " | " + gameboard[2][4] + " | " 
      + gameboard[2][5] + " | " + gameboard[2][6] + " |");
      
      System.out.println("|---+---+---+---+---+---+---|");
      
      System.out.println("| " + gameboard[3][0] + " | " + gameboard[3][1] + " | " 
      + gameboard[3][2] + " | " + gameboard[3][3] + " | " + gameboard[3][4] + " | " 
      + gameboard[3][5] + " | " + gameboard[3][6] + " |");
      
      System.out.println("|---+---+---+---+---+---+---|");
      
      System.out.println("| " + gameboard[4][0] + " | " + gameboard[4][1] + " | " 
      + gameboard[4][2] + " | " + gameboard[4][3] + " | " + gameboard[4][4] + " | " 
      + gameboard[4][5] + " | " + gameboard[4][6] + " |");
      
      System.out.println("|---+---+---+---+---+---+---|");
      
      System.out.println("| " + gameboard[5][0] + " | " + gameboard[5][1] + " | " 
      + gameboard[5][2] + " | " + gameboard[5][3] + " | " + gameboard[5][4] + " | " 
      + gameboard[5][5] + " | " + gameboard[5][6] + " |");
      
      System.out.println("|___|___|___|___|___|___|___|");
   }//end printBoard method
   
   public static void main (String[] args)
   {
      Random ran = new Random();
      Scanner in = new Scanner(System.in);
      
      boolean winner = false;
      boolean empty = true;//used when checking for empty spaces
      boolean error = true;//used to test for valid input
      boolean rightNum = true;//used to test for valid range of numbers.
      
      char player = '1';//values include 1 for player1 2 for player 2 and c for computer
      char whoWon = 'n';
      char marker1 = ' ';
      char marker2 = ' ';
      char useMarker = ' ';//which marker will be placed in the empty space
      
      int numOfPlayers = 0;
      int turn = 1;
      int columnDrop = -1;//which column to drop into.
      int lastEmpty = -1;
      
      String quit = "";
      String markerHolder = "";//holds the users input so that the program can parse a char
      
      System.out.println("Welcome to Stephen's Connect Four!");
      
      do
      {
         //initialize array
         for(int r = 0; r < 6; r++)
         {
            for(int c = 0; c < 7; c++)
            {
               gameboard[r][c] = ' ';
            }//end for
         }//end for
         
         //initialize variables
         winner = false;
         player = '1';
         marker1 = ' ';
         marker2 = ' ';
         turn = 0;
         
         //choose one or two players
         
         System.out.println("How many players are there? 1 or 2?" );
         do
         {
            try
            {
               System.out.println("Please make sure you enter either a \"1\" or a \"2\".");
               numOfPlayers = in.nextInt();
               error = false;
            }
            catch(InputMismatchException e)
            {
               System.out.println("Your input was not a viable option");
               System.out.println("Try again.");
               error = true;
               in.nextLine();
            }
            
            if(!error && !(numOfPlayers == 1) && !(numOfPlayers == 2))
            {
               rightNum = false;
               in.nextLine();
            }
            else
            {
               rightNum = true;
            }
         }while(!rightNum || error);
         
         //flush the buffer
         in.nextLine();
         
         //single player game
         if (numOfPlayers == 1)
         {
         player = 'c';
            do
            {
               //rotate whose turn it is
               if (player == 'c')
               {
                  player = '1';
                  
                  turn ++;
               }
               else if (player == '1')
               {
                  player = 'c';
               }
               
               //on player 1's turn
               if (player == '1')
               {
                  if (turn == 1)
                  {
                     //choosing a marker
                     System.out.println("Please choose a character to be your marker on the board.");
                     do
                     {
                        System.out.println("Only the first character you enter will be used");
                        markerHolder = in.nextLine();
                        error = false;
                        
                        if (markerHolder.charAt(0) == ' ')
                        {
                           System.out.println("I'm sorry, but \" \" is not a valid character." + 
                           " Choose another.");
                           error = true;
                        }
                     }while (error);
                     marker1 = markerHolder.charAt(0);
                     
                     //assign computer's marker
                     if (marker1 == 'B')
                     {
                        marker2 = 'R';
                     }
                     else
                     {
                        marker2 = 'B';
                     }
                     
                     //inform player of which markers will be used
                     System.out.println("Your marker will be \"" + marker1 +"\". The computer's " + 
                     "marker will be \"" + marker2 + "\".");
                  }//end if
                  
                  System.out.println("It's your turn.");
                  
                  printBoard();
                  
                  //choose which column to drop your piece into
                  columnDrop = chooseColumn() - 1;
                  
                  useMarker = marker1;
               }//end if
               
               //on computer's turn
               else if (player == 'c')
               {
                  System.out.println("It's the computer's turn");
                  
                  columnDrop = ran.nextInt(7);
                  
                  useMarker = marker2;
               }
               
               //drop piece into chosen column
               do
               {
                  lastEmpty = -1;
                  
                  for (int j = 0; j <= 5; j++)
                  {
                     if (gameboard[j][columnDrop] == ' ')
                     {
                        lastEmpty = j;
                     }
                  }
                  
                  //if the column is full
                  if (lastEmpty == -1)
                  {
                     if(player == '1')
                     {
                        System.out.println("I'm sorry, but that column is full.");
                        
                        printBoard();
                        
                        columnDrop = chooseColumn() - 1;
                     }
                     else if (player == 'c')
                     {
                        columnDrop = ran.nextInt(7);
                     }
                  }
               }while(lastEmpty == -1);
               
               gameboard[lastEmpty][columnDrop] = useMarker;
               
               printBoard();
               
               //check for winner
               winner = winCheckRow();
               
               if (!winner)
               {
                  winner = winCheckColumn();
               }
               
               if (!winner)
               {
                  winner = winCheckDiagonal();
               }
               
            }while (!winner);
         }//end single player if
         
         //2 player game
         if (numOfPlayers == 2)
         {
         player = '2';
            do
            {
               //rotate whose turn it is
               if (player == '2')
               {
                  player = '1';
                  
                  turn ++;
               }
               else if (player == '1')
               {
                  player = '2';
               }
               
               if (turn == 1 && player == '1')
               {
                  //choosing a marker
                  System.out.println("Player 1,please choose a character to be your marker on the board.");
                  do
                  {
                     System.out.println("Only the first character you enter will be used");
                     markerHolder = in.nextLine();
                     error = false;
                     
                     if (markerHolder.charAt(0) == ' ')
                     {
                        System.out.println("I'm sorry, but \" \" is not a valid character." + 
                        " Choose another.");
                        error = true;
                     }
                  }while (error);
                  
                  marker1 = markerHolder.charAt(0);
                  
                  System.out.println("Player 1's marker will be \"" + marker1 + "\".");
               }//end player 1 marker if
               
               if (turn == 1 && player == '2')
               {
                  //choosing a marker
                  System.out.println("Player 2, please choose a character to be your marker on the board.");
                  do
                  {
                     System.out.println("Only the first character you enter will be used");
                     markerHolder = in.nextLine();
                     error = false;
                     
                     if (markerHolder.charAt(0) == ' ')
                     {
                        System.out.println("I'm sorry, but \" \" is not a valid character." + 
                        " Choose another.");
                        error = true;
                     }
                     else if (markerHolder.charAt(0) == marker1)
                     {
                        System.out.println("Player 1 is already using that marker." 
                        + " Choose another");
                        error = true;
                     }
                  }while (error);
                  
                  marker2 = markerHolder.charAt(0);
                  
                  System.out.println("Player 2's marker will be \"" + marker2 + "\".");
               }//end player 2 marker if
               
               if (player == '1')
               {
                  System.out.println("It's Player 1's turn.");
               }
               else if (player == '2')
               {
                  System.out.println("It's Player 2's turn.");
               }
               
               printBoard();
               
               //choose which column to drop your piece into
               columnDrop = chooseColumn() - 1;
               
               if (player == '1')
               {
                  useMarker = marker1;
               }
               else if (player == '2')
               {
                  useMarker = marker2;
               }
               
               //drop piece into chosen column
               do
               {
                  lastEmpty = -1;
                  
                  for (int j = 0; j <= 5; j++)
                  {
                     if (gameboard[j][columnDrop] == ' ')
                     {
                        lastEmpty = j;
                     }
                  }
                  
                  //if the column is full
                  if (lastEmpty == -1)
                  {
                        System.out.println("I'm sorry, but that column is full.");
                        
                        printBoard();
                        
                        columnDrop = chooseColumn() - 1;
                  }
               }while(lastEmpty == -1);
               
               gameboard[lastEmpty][columnDrop] = useMarker;
               
               printBoard();
               
               //check for winner
               winner = winCheckRow();
               
               if (!winner)
               {
                  winner = winCheckColumn();
               }
               
               if (!winner)
               {
                  winner = winCheckDiagonal();
               }
               
            }while (!winner);
         }//end 2 player if
         
         if (player == '1')
         {
            System.out.println("Player 1 wins!");
         }
         else if (player == '2')
         {
            System.out.println("Player 2 wins!");
         }
         else if (player == 'c')
         {
            System.out.println("The computer wins...");
         }
         
         System.out.println("Would you like to play again? Y or N?");
         quit = in.nextLine();
         
         if (!(quit.equalsIgnoreCase("y") || quit.equalsIgnoreCase("n")))
         {
            do
            {
               System.out.println("Your input was not a viable option.");
               System.out.println("Try again. Please choose the letter \"Y\" or the letter \"N\".");
               quit = in.nextLine();
            }while(!(quit.equalsIgnoreCase("y") || quit.equalsIgnoreCase("n")));
         }
      }while (quit.equalsIgnoreCase("y"));
      
      System.out.println("Thanks for playing!");
         
   }//end main method
   
   public static int chooseColumn()
   {
      Scanner in = new Scanner(System.in);
      
      int columnDrop = 0;
      boolean error = false;
      boolean rightNum = true;
      
      System.out.println("Please choose a column to drop your marker into.");
      
      do
      {
         try
         {
            System.out.println("Numbering the columns from left to right, please" + 
               " enter an integer from 1-7.");
            columnDrop = in.nextInt();
            error = false;
         }
         catch(InputMismatchException e)
         {
            System.out.println("Your input was not a viable option");
            System.out.println("Try again.");
            error = true;
            in.nextLine();
         }
         
         if(!error && !((columnDrop > 0) && (columnDrop < 8)))
         {
            rightNum = false;
            in.nextLine();
         }
         else
         {
            rightNum = true;
         }
      }while(!rightNum || error);
      
      //flush the buffer
      in.nextLine();
      return columnDrop;
   }//end chooseColumn method
   
   public static boolean winCheckRow()
   {
      boolean winner = false;
      
      for (int row = 5; row >= 0; row --)
      {
         for(int column = 0; column <= 3; column ++)
         {
            if(gameboard[row][column] != ' ' && gameboard[row][column] == gameboard[row][column + 1]
               && gameboard[row][column + 1] == gameboard[row][column + 2] 
               && gameboard[row][column + 2] == gameboard[row][column + 3])
            {
               winner = true;
            } //if  
         }//column for
      }//row for
      
      return winner;
   }// winCheckRow method
   
   public static boolean winCheckColumn()
   {
      boolean winner = false;
      
      for (int column = 0; column <= 6; column ++)
      {
         for(int row = 5; row >= 0; row --)
         {
            if(gameboard[row][column] != ' ' && gameboard[row][column] == gameboard[row - 1][column]
               && gameboard[row - 1][column] == gameboard[row - 2][column] 
               && gameboard[row - 1][column] == gameboard[row - 3  ][column])
            {
               winner = true;
            } //end if  
         }//end row for
      }// end column for
      
      return winner;
   }// end winCheckColumn method   
   
   public static boolean winCheckDiagonal()
   {
      boolean winner = false;
      
      for (int column = 0; column <= 3; column++)
      {
         for (int row = 0; row <= 2; row++)
         {
            if (gameboard[row][column] != ' ' && gameboard[row][column] == gameboard[row + 1][column + 1] 
               && gameboard[row + 1][column + 1] == gameboard[row + 2][column + 2] 
               && gameboard[row + 2][column + 2] == gameboard[row + 3][column + 3])
            {
               winner = true;
            }// end if
         }// end row for
      }//end column for
      
      for (int column = 3; column <= 6; column++)
      {
         for (int row = 0; row <= 2; row++)
         {
            if (gameboard[row][column] != ' ' && gameboard[row][column] == gameboard[row + 1][column - 1] 
               && gameboard[row + 1][column - 1] == gameboard[row + 2][column - 2] 
               && gameboard[row + 2][column - 2] == gameboard[row + 3][column - 3])
            {
               winner = true;
            }// end if
         }//end row for
      }//end column for
      
      return winner;
   }//end winCheckDiagonal method
}//end class