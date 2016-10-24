package main
//
import (
   "fmt"
   "os"
   "bufio"
   "time"
)
//
type WordGraph map[string][]string
type StringSet map[string]bool
//
type ChannelRequest struct {
   baseword string
   nbrs     []string
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func main() {
   fmt.Println("Go:")
   //
   file, err := os.Open("words.txt")
   check(err)
   //
   var words []string
   scanner := bufio.NewScanner(file)
   for scanner.Scan() {
      words = append(words, scanner.Text())
   }
   check(scanner.Err())
   //
   tic := time.Now()
   naive(words)
   toc := time.Now()
   fmt.Printf("   Naive approach: %v seconds", toc.Sub(tic).Seconds())
   //
   //
   fmt.Println()
   tic = time.Now()
   reverse(words)
   toc = time.Now()
   fmt.Printf("   Reverse approach: %v seconds", toc.Sub(tic).Seconds())
   //
   //
   fmt.Println()
   tic = time.Now()
   naiveGoRoutines(words)
   toc = time.Now()
   fmt.Printf("   GoRoutine approach: %v seconds\n", toc.Sub(tic).Seconds())
   //
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func naive(words []string) {
   graph := make(WordGraph)
   //
   for _,w := range words {
      var nbrs []string
      for _,otherWord := range words {
         if isNeighbor(w, otherWord) {
            nbrs = append(nbrs, otherWord)
         }
      }
      graph[w] = nbrs
   }
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func reverse(words []string) {
   graph := make(WordGraph)
   set := make(StringSet)
   for _,w := range words {
      set[w] = true
   }
   //
   letters :=[]string{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}
   //
   for _,w := range words {
      var nbrs []string
      for i := 0; i < len(w); i++ {
         for _,letter := range letters {
            newW := w[:i] + letter + w[i + 1:]
            if w != newW && !contains(nbrs, newW)  && set[newW] {
               nbrs = append(nbrs, newW)
            }
         }
      }
      graph[w] = nbrs
   }
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func naiveGoRoutines(words []string) {
   graph := make(WordGraph)
   myChan := make(chan ChannelRequest)
   //
   for _,w := range words {
      go makeNbrs(words, w, myChan)
   }
   //
   for i := 0; i < len(words); i++ {
      req := <-myChan
      graph[req.baseword] = req.nbrs
   }
   //
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func makeNbrs(words []string, word string, achan chan ChannelRequest) {
   var nbrs []string
   for _,otherWord := range words {
      if isNeighbor(word, otherWord) {
         nbrs = append(nbrs, otherWord)
      }
   }
   achan <- ChannelRequest{word, nbrs}
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func isNeighbor(a string, b string) bool {
   var dif int = 0
   for i := 0; i < len(a); i++ {
      if dif > 1 {
         return false
      }
      if a[i] != b[i] {
         dif += 1
      }
   }
   return dif == 1
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func contains(arr []string, s string) bool {
   for _,str := range arr {
      if str == s {
         return true
      }
   }
   return false
}
//
/////////////////////////////////////////////////////////////////////////////////////////
//
func check(e error) {
   if e != nil {
      panic(e)
   }
}
