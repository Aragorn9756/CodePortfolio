/***************************************************
*nestedLoopRectangle.java
*Created by Stephen Richardson  
*
*This is my first attempt at making a nested loop.
*The program is intended to take input of width, height and a chosen
*character and take that and print out a rectangle with the indicated
*dimensions and character.
****************************************************/
import java.util.Scanner;

public class nestedLoopRectangle
{

   public static void main(String[] args)
   {
      
      Scanner stdIn = new Scanner(System.in);
      String row="";
      int height = 0, width = 0;
      char rectangleFiller;
      
      //Collects user's preferences
      System.out.print("Choose a height: ");
      height = stdIn.nextInt();
      stdIn.nextLine();
      
      System.out.print("Choose a width: ");
      width= stdIn.nextInt();
      stdIn.nextLine();
      
      System.out.print("choose a Character: ");
      rectangleFiller = stdIn.next().charAt(0);
      stdIn.nextLine();
      
      for(int i = 0; i < height; i++)
      {
      
         row="";
         
         for(int j = 0; j < width; j++)
         {
         
            row += rectangleFiller;
         
         }
         
      System.out.println(row);   
         
      }
   }

}