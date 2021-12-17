

#include <iostream>
#include<string.h>

using namespace std;


int main(int argc, char** argv)
{
       if (argc > 1) // if we pass arguments to function, argc will be more than 1 (depends on number of arguments)
       {
          int numWords = 0; // variable for counting number of words
          // check if first symbol is not empty 
          if (!(isspace(argv[1][0]) || argv[1][0] == '\n')){
             numWords++;
          }
          for(int i = 1; i < strlen(argv[1]); i++){
             if (
                // hceck if symbol is space or newline
                  (isspace(argv[1][i]) || argv[1][i] == '\n')  
                  && 
                  // check that next symbol is not space and not newline
                  !(isspace(argv[1][i + 1]) || argv[1][i + 1] == '\n')
                ){
                numWords++;
             } 
          };
             printf("Number of words = %d\n", numWords); // printing number of words
       }
       else
      {
         cout << "Not arguments were given" << endl;
      }
       return 0;
}