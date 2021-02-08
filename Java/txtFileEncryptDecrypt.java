/***********************************************************************
*txtFileEncryptDecrypt.java
*by Stephen Richardson
*
*This program will do a simple encryption or decryption on .txt files.
*It will increment ASCII characters when encrypting, and decrement them
*when decrypting.
***********************************************************************/
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class txtFileEncryptDecrypt
{
   public static void main (String[] args)
   {
      //instantiate tools and variables.
      File file;
      Scanner in = new Scanner(System.in);
      Scanner fileIn;
      PrintWriter fileOut;
      
      String quit = "";
      String userChoice = "";
      String fileName = "";
      String line = "";
      
      char currentChar = ' ';
      
      boolean fileFound = false;
      
      System.out.println("Welcome to my Text File Encryptor/Decryptor!");
      
      do
      {
         System.out.println("Would you like to perform an encryption or a decryption?");
         userChoice = in.nextLine();
         
         if(!(userChoice.equalsIgnoreCase("encryption") || userChoice.equalsIgnoreCase("decryption")))
         {
            do
            {
               System.out.println("I'm sorry, but your input was not viable. Please try again.");
               System.out.println("Please enter either \"encryption\" or \"decryption\".");
               userChoice = in.nextLine();
               
            }while (!(userChoice.equalsIgnoreCase("encryption") || userChoice.equalsIgnoreCase("decryption")));
         }//end viable input if
         
         if(userChoice.equalsIgnoreCase("encryption"))
         {
            System.out.println("Please choose which .txt file you would like encrypted.");
            
            do
            {
               //get the file to be encrypted
               try
               {
                  System.out.println("Please include the entire directory leading to the file"
                     + " and replace every \"\\\" with \"/\".");
                  fileName = in.nextLine();
                 
                  file = new File (fileName);
                  fileIn = new Scanner(file);
                  
                  fileFound = true; 
               }
               catch (FileNotFoundException e)
               {
                  System.out.println("Your file could not be found. Please check your keystrokes.");
                  
                  fileFound = false;
               }
            }while (!fileFound);
            

            //create encrypted file
            fileName = fileName + "Encrypted";
            try
            {
               fileOut = new PrintWriter(fileName);
            }
            catch (FileNotFoundException e)
            {
               System.out.println("File not found.");
            }
            
            while(fileIn.hasNextLine())
            {
                  line = fileIn.nextLine();
                  
                  for (int i = 0; i < line.length(); i++)
                  {
                     currentChar = line.charAt(i);
                     currentChar++;
                     fileOut.print(currentChar);
                  }
                  fileOut.println("");   
            }//end hasNextLine while   
               
            //tell user encryption is done
            System.out.println("Your encryption is done. Your encrypted file can be"
               + " found at:");
            System.out.println(fileName);
                
         }//end encryption if
         
         if(userChoice.equalsIgnoreCase("decryption"))
         {
            
         }//end decryption if
                  
         System.out.println("Would you like to encrypt or decrypt another file? Y or N?");
         quit = in.nextLine();
         
         if (!(quit.equalsIgnoreCase("y") || quit.equalsIgnoreCase("n")))
         {
            do
            {
               System.out.println("Your input was not a viable option.");
               System.out.println("Try again. Please choose the letter \"Y\" or the letter \"N\".");
               quit = in.nextLine();
            }while(!(quit.equalsIgnoreCase("y") || quit.equalsIgnoreCase("n")));
         }//end viable input if
         
      }while (quit.equalsIgnoreCase("y"));
      
      System.out.println("Thank you for using my program! I hope it was helpful.");
   }//end main method
   
}//end class