#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isChar ( char c ){
  if ( (c > 64 && c < 91) || (c > 96 && c < 123) )
    return 1;
  return 0;
}

int getWordLength ( char * array, int adr ){
  while ( isChar(array[adr]) )
    ++adr;
  return adr - 1;
}

int getLongerWord ( int a, int b ){
  if ( a > b )
    return a;
  else
    return b;
}

int main ( void ){
  int count = 1, count2 = 0, line = 1;
  char * text = (char *) malloc((1000)*sizeof(char));
  char * searched_string = (char *) malloc((1000)*sizeof(char));
  text[0] = ' ';

  printf("Text:\n");

  while ( 1 ){

    text[count] = getchar();

    if ( text[count] == EOF ){
      printf("Nespravny vstup.\n");
      free(text);
      free(searched_string);
      return 0;
    }



    if ( text[count] == '\n' && text[count-1] == '\n' ) {
      printf("%d\n", getWordLength(text, 1));
      break;
    }


    //* deletes extra non-characters (2 or more), leaves new_lines (for line count)
    if ( isChar(text[count]) == 0
    && isChar(text[count-1]) == 0
    && text[count] != '\n'
    && text[count-1] != '\n' ){
      --count;
    }
    //*

    ++count;

    if ( count % 1000 == 0 )
      text = (char *) realloc(text, (count+1000)*sizeof(char));

  }

  printf("Hledani:\n");
  int err = 0;
  while ( 1 ){
    searched_string[count2] = getchar();

    if ( searched_string[count2] == EOF ){
      free(text);
      free(searched_string);
      return 0;
    }

    ++count2;
    if ( count2 % 1000 == 0 )
      searched_string = (char *) realloc(searched_string, (count2+1000)*sizeof(char));

    if ( searched_string[count2 - 1] == '\n' ){

      printf("Nalezeno: ");
      for ( int i = 0; i < count - 2; ++i ){
        if ( text[i] == '\n' )
          ++line;
        if ( isChar(text[i]) == 0 && isChar(text[i+1]) == 1 && text[i+1] == searched_string[0] ){

          for ( int j = 0; j < count2 - 1; ++j ){
            if ( text[j+i+1] != searched_string[j] ){
              err = 1;
              break;
            }
          }
          if ( err == 0 ){
            printf("%d, ", line);
          }
          err = 0;
        }
      }
      printf("\n");
      line = 1;
      count2 = 0;
    }



  }

  printf("%s\n", text);

  free(text);
  free(searched_string);
  return 0;
}
