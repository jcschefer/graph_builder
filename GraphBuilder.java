// Jack Schefer, 3/13/17
//
import java.io.BufferedReader ;
import java.io.FileReader     ;
import java.io.IOException    ;
import java.util.ArrayList    ;
import java.util.List         ;
import java.util.Date         ;
import java.util.HashMap      ;
import java.util.Map          ;
import java.util.HashSet      ;
import java.util.Set          ;
//
class GraphBuilder
{
   //////////////////////////////////////////////////////////
   //
   private static List<String> words ;
   private static char[] letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'} ;
   //
   //////////////////////////////////////////////////////////
   //
   public static void main( String[] args ) throws IOException
   {
      System.out.println( "Java:" ) ;
      //
      FileReader freader = new FileReader( "words.txt" ) ;
      BufferedReader breader = new BufferedReader( freader ) ;
      words = new ArrayList<String>() ;
      String l = null ;
      //
      while( (l = breader.readLine()) != null )
      {
         //
         words.add( l ) ;
         //
      }
      //
      breader.close() ;
      //
      long tic = System.currentTimeMillis() ;
      Map<String, Set<String>> g1 = naive() ;
      long toc = System.currentTimeMillis() ;
      System.out.println( "   Naive Approach: " + (toc - tic) / 1000.0 + " seconds" ) ;
      //
      tic = System.currentTimeMillis() ;
      Map<String, Set<String>> g2 = reverse() ;
      toc = System.currentTimeMillis() ;
      System.out.println( "   Reverse Approach: " + (toc - tic) / 1000.0 + " seconds" ) ;
   }
   //
   //////////////////////////////////////////////////////////
   //
   private static Map<String, Set<String>> naive()
   {
      Map<String, Set<String>> graph = new HashMap<String, Set<String>>() ;
      //
      for( String w : words )
      {
         Set<String> nbrs = new HashSet<String>() ;
         //
         for( String temp : words)
         {
            if( isNeighbor( w, temp )) 
               nbrs.add( temp ) ;
         }
         //
         graph.put( w, nbrs ) ;
      }
      //
      return graph ;
   }
   //
   //////////////////////////////////////////////////////////
   //
   private static Map<String, Set<String>> reverse()
   {
      Map<String, Set<String>> graph = new HashMap<String, Set<String>>() ;
      Set<String> wordSet = new HashSet<String>( words ) ;
      //
      for( String w : words )
      {
         Set<String> nbrs = new HashSet<String>() ;
         //
         for( int i = 0; i < w.length(); i++ )
         {
            for( char letter : letters )
            {
               String newWord = w.substring( 0, i ) + letter + w.substring( i + 1 ) ;
               if( wordSet.contains( newWord ) && !newWord.equals( w ) )
                  nbrs.add( newWord ) ;
            }
         }
         //
         graph.put( w, nbrs ) ;
      }
      //
      return graph ;
   }
   //
   //////////////////////////////////////////////////////////
   //
   private static boolean isNeighbor( String a, String b )
   {
      int diff = 0 ;
      for( int i = 0; i < a.length(); i++ )
      {
         if( diff > 1 ) return false ;
         if( a.charAt( i ) != b.charAt( i ) ) diff++ ;
      }
      return diff == 1 ;
   }
   //
   //////////////////////////////////////////////////////////
   //
}
//
// End of file.
