#include <stdio.h>

int main(int argc, char *argv[]) {
   printf("-- [[ Start of the program ]] --\n\n");
   for ( int i = 0; i < argc; i++ ) {
      printf("%s\n", argv[i]);
   }
   printf("\n-- [[ End of the program ]] --\n");

   return 0;
}
