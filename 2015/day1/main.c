#include <assert.h>
#include <stdio.h>

/**
 * Simple question, only one function needed
 * @param char *file_name[], name of the file
 *
 * @return floor at the end of the instructions
 */
int get_floor(char *file_name) {
   FILE *file_ptr = fopen(file_name, "r");
   assert(file_ptr != NULL); // Error opening the file

   int count_open  = 0;
   int count_close = 0;

   while ( !feof(file_ptr) ) {
      char c = getc(file_ptr);
      if ( c == "("[0] ) {
         count_open++;
      } else if ( c == ")"[0] ) {
         count_close++;
      }
   }

   int floor = 0 + count_open - count_close;

   return floor;
}

/**
 * given first char pos is 1, get the position of the first char that makes
 * santa enter the basement
 * @param char *file_name, name of the file
 *
 * @return position of the first char that lead santa to the basement,
 * -1 if santa didnt reach the basement
 */
int get_pos_enter_basement(char *file_name) {
   FILE *file_ptr = fopen(file_name, "r");
   assert(file_ptr != NULL); // Error opening the file

   int floor = 0;
   int i     = 1;

   while ( !feof(file_ptr) ) {
      char c = getc(file_ptr);
      if ( c == "("[0] ) {
         floor++;
      } else if ( c == ")"[0] ) {
         floor--;

         // only check if we decrease floor
         if ( floor <= -1 ) {
            return i;
         }
      }

      i++;
   }

   return -1; // santa didnt reach basement
}

int main(int argc, char *argv[]) {
   printf("-- [[ Start of the program ]] --\n\n");

   int result = get_floor(argv[1]); // first argument is the filename
   printf("Santa ends up on floor : %d\n", result);

   result = get_pos_enter_basement(argv[1]); // first argument is the filename
   printf("Santa enters the basement on instruction no : %d\n", result);

   printf("\n-- [[ End of the program ]] --\n");

   return 0;
}
