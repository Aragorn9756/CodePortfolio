/***********************************************************************
*pigLatinTranslator.java
*written by StephenRichardson
*
*This program is intended to take a word and change the 
*letters around and add some letters on the end in order to fit the
*parameters of pig latin as defined by wikipedia.
***********************************************************************/
import java.util.Scanner;

public class pigLatinTranslator
{

   public static void main (String[] args)
   {
      Scanner in = new Scanner (System.in);
      
      String userWord = "";
      String pLWord = "";//User's word translated into pig latin.
      
      char ch = ' ';//Temporary character holder
      
      System.out.println("Welcome to Ooglegay (;D) Pig Latin Translator!");
      System.out.println("Please enter a word to be translated.");
      userWord = in.nextLine();
      
      do
      {
         userWord = userWord.toLowerCase();
         
         switch (userWord.charAt(0))//sends word to vowel or consonant method based on first char
         {
            case 'a': case 'e': case 'i': case 'o': case 'u':
               pLWord = vowelTrans(userWord);
               break;
            case 'b': case 'c': case 'd': case 'f': case 'g': case 'h': case 'j': case 'k':
            case 'l': case 'm': case 'n': case 'p': case 'q': case 'r': case 's': case 't':
            case 'v': case 'w': case 'x': case 'y': case 'z':   
               pLWord = consonantTrans(userWord);
               break; 
            
            default://asks for reinput for nonletter first char
               System.out.println("\"" + userWord + "\" is an invalid input. Please enter a word to be translated.");
               userWord = in.nextLine();
         }//end switch
         
         System.out.println("Your word translated into pig latin is \"" + pLWord + "\".");
         
         System.out.println("Please enter another word, or press \"Q\" to quit.");
         userWord = in.nextLine();
      }while(!userWord.equalsIgnoreCase("Q"));//end do while loop

   }//end main method

      
   //Method for when the first letters are consonants.
   public static String consonantTrans(String untransWord)
   {
      String transWord = "";
      String consonants = "";//will hold a substring of consonants at the beginning of the untranslated word
      String wordRemains = "";//will hold a substring of the rest of the untranslated word
      
      int vowelIndex = 300;
      
      for ( int i = 0; i < untransWord.length() ; i++)
      {
         switch (untransWord.charAt(i))//searches for index value for vowel
         {
            case 'a': case 'e': case 'i': case 'o': case 'u':
               if (i < vowelIndex)
               {
                  vowelIndex = i;
               }
               break;
            
            default:      
         }//end switch   
      }//end for loop  
      
      //separate word into pieces for rearranging
      consonants = untransWord.substring(0, vowelIndex);
      wordRemains = untransWord.substring(vowelIndex, untransWord.length()); 
      
      //constructing translated word
      transWord = wordRemains + consonants + "ay";
      
      return transWord;
   }//end consonantTrans method
   
   //Method for when the first letter is a vowel.  
   public static String vowelTrans (String untransWord)
   {
      String transWord = "";
      
      transWord = untransWord + "way";
      
      return transWord;
   }//end vowelTrans method
}//end class