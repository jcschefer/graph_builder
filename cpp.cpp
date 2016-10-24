// Jack Schefer, Began 8/2/16
//
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <map>
#include <vector>
#include <chrono>
#include <unordered_set>
#include <algorithm>
//
using namespace std;
//
#define N 4969
//
typedef map< string, vector< string > > WordGraph;
//
WordGraph naive( string words[N] );
WordGraph reverse( string words[N] );
bool isNeighbor( string a, string b );
//
////////////////////////////////////////////////////////////////////////////////////////
//
int main()
{
   string words[N];
   //
   ifstream infile("words.txt");
   for ( int i = 0; i < N; i++ )
   {
      infile >> words[i];
   }
   //
   auto tic = chrono::high_resolution_clock::now();
   WordGraph g1 = naive( words );
   auto toc = chrono::high_resolution_clock::now();
   chrono::duration< double > time1 = chrono::duration_cast< chrono::duration< double > >(toc - tic);
   cout << "Naive approach: " << time1.count() << " seconds" << endl;
   //
   cout << "abased nbrs: "  << endl;
   vector<string> nb = g1["abased"];
   for(auto i : nb)
   {
      cout << "   " + i  << endl;
   }
   //
   tic = chrono::high_resolution_clock::now();
   WordGraph g2 = reverse( words );
   toc = chrono::high_resolution_clock::now();
   chrono::duration< double > time2 = chrono::duration_cast< chrono::duration< double > >(toc - tic);
   cout << "\n\nReverse approach: " << time2.count() << " seconds" << endl;
   //
   cout << "abased nbrs: "  << endl;
   vector< string > nb2 = g2["abased"];
   for( auto i : nb2 )
   {
      cout << "   " + i  << endl;
   }
   cout << "testing comlete" << endl;
   //
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
WordGraph naive( string words[N] )
{
   WordGraph g;
   //
   for ( int i = 0; i < N; i++ )
   {
      vector< string > nbrs;// = vector< string >();
      //
      for ( int j = 0; j < N; j++ )
      {
         if ( isNeighbor( words[i], words[j]) )
         {
            nbrs.push_back( words[j] );
         }
      }
      //
      g[ words[i] ] = nbrs;
   }
   //
   return g;
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
WordGraph reverse( string words[N] )
{
   const int WORD_LEN = words[0].length();
   char start = 'a';
   string letters[26];
   for ( int i = 0; i < 26; i++ )
   {
      letters[i] = string( 1, static_cast< char >( start + i ) );
   }
   //
   WordGraph g;
   unordered_set< string > wordSet;
   //
   for ( int i = 0; i < N; i++ )
   {
      //
      wordSet.insert( words[i] );   
      //
   }
   //
   for ( int i = 0; i < N; i++ )
   {
      vector< string > nbrs;
      string word = words[i];
      //
      for ( int j = 0; j < WORD_LEN; j++ )
      {
         for ( int k = 0; k < 26; k++ )
         {
            string newW = word.substr( 0, j ) + letters[k] + word.substr( j + 1 );
            if ( newW != word && find( nbrs.begin(), nbrs.end(), newW ) == nbrs.end() && wordSet.find( newW ) != wordSet.end() )
            {
               nbrs.push_back( newW );
            }
         }
      }
      //
      sort( nbrs.begin(), nbrs.end() );
      g[ word ] = nbrs;
   }
   //
   return g;
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
bool isNeighbor( string a, string b)
{
   int diff = 0;
   //
   for ( int i = 0; i < a.length(); i++ )
   {
      if (diff > 1)
      {
         return false;
      }
      //
      if ( a.at(i) != b.at(i) )
      {
         diff += 1;
      }
   }
   //
   return diff == 1;
}
//
// End of File
