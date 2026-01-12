#include <assert.h>
#include <stdio.h>

struct box {
   int l; // lenght of the box
   int w; // width of the box
   int h; // height of the box
};

/**
 * transform a char to a int if possible otherwise returns -1
 *
 * @param char c, char we want to transform
 *
 * @return int, -1 if not a number,
 */
int char_to_int(char c) {
   int value = c - '0';

   if ( value < 0 ) {
      return -1;
   }
   if ( value > 9 ) {
      return -1;
   }

   return value;
}

/**
 * Read the content of the line and populate the box parameter
 *
 * @param struct box ptr_box, pointer to box to populate
 * @param char *line_content, string with the values inside, values are
 * positive, and separated by the char x (eg: 13x2x6)
 */
void boxify(struct box *ptr_box, char *line_content) {
   int cursor_pos = 0;
   int char_value;
   int value;
   int final_values[3];

   for ( int i = 0; i < 3; i++ ) {
      value = 0;

      char_value = char_to_int(line_content[cursor_pos]);
      cursor_pos++;

      while ( char_value != -1 ) {
         value *= 10;
         value += char_value;

         char_value = char_to_int(line_content[cursor_pos]);
         cursor_pos++;
      }
      final_values[i] = value;
   }

   ptr_box->l = final_values[0];
   ptr_box->w = final_values[1];
   ptr_box->h = final_values[2];
}

/**
 * Calculate the surface aera of wrapping paper needed for one box
 *
 * @param struct box my_box, data of one box
 *
 * @return int surface area of the box plus some extra needed by the elves
 */
int calc(struct box my_box) {
   int side1 = my_box.l * my_box.w;
   int side2 = my_box.w * my_box.h;
   int side3 = my_box.h * my_box.l;

   // extra is equal to the smallest side
   int extra = side1;
   if ( extra > side2 ) {
      extra = side2;
   }
   if ( extra > side3 ) {
      extra = side3;
   }

   int tot = 2 * side1 + 2 * side2 + 2 * side3;

   return tot + extra;
}

/**
 * Calculate the total surface of wrapping paper needed
 *
 * @param char *file_name, name of the input file
 *
 * @return int, total surface of the wrapping paper needed
 */
int tot_wrapping_paper(char *file_name) {
   FILE *file_ptr = fopen(file_name, "r");
   assert(file_ptr != NULL);

   char       line[256];
   struct box my_box;
   int        tot = 0;

   while ( fgets(line, sizeof(line), file_ptr) ) {
      boxify(&my_box, line); // 1: Populate my_box with the content of the line
      tot += calc(my_box);   // 2: Compute the surface of my_box and adds to the
                             // total
   }
   fclose(file_ptr);

   return tot;
}

/**
 * Calculate the lenght of ribbon needed for one box
 *
 * @param struct box my_box, data of one box
 *
 * @return int, lenght of ribbon needed for one box
 */
int calc_ribbon(struct box my_box) {
   int bigest = my_box.l;
   if ( bigest < my_box.h ) {
      bigest = my_box.h;
   }
   if ( bigest < my_box.w ) {
      bigest = my_box.w;
   }

   // if we remove 2*biggest we will have only the two smallest remaining
   int tot = 2 * my_box.l + 2 * my_box.h + 2 * my_box.w - 2 * bigest;

   int extra = my_box.l * my_box.h * my_box.w;

   return tot + extra;
}

/**
 * Calculate the total lenght of ribbon needed
 *
 * @param char *file_name, name of the input file
 *
 * @return int, total lenght of ribbon needed
 */
int tot_ribbon(char *file_name) {
   FILE *file_ptr = fopen(file_name, "r");
   assert(file_ptr != NULL);

   char       line[256];
   struct box my_box;
   int        tot = 0;

   while ( fgets(line, sizeof(line), file_ptr) ) {
      boxify(&my_box, line); // 1: Populate my_box with the content of the line
      tot += calc_ribbon(my_box); // 2: Compute the surface of my_box and adds
                                  // to the total
   }
   fclose(file_ptr);

   return tot;
}

int main(int argc, char *argv[]) {
   printf("-- [[ Start of the program ]] --\n\n");

   int result = tot_wrapping_paper(argv[1]);
   printf("The elves need %d squares feet of wrapping paper\n", result);
   result = tot_ribbon(argv[1]);
   printf("The elves need %d feet of ribbon\n", result);

   printf("\n-- [[ End of the program ]] --\n");

   return 0;
}
