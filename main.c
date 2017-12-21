#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isChar ( char c ){
  if ( (c > 64 && c < 91) || (c > 96 && c < 123) )
    return 1;
  return 0;
}

int getWordLength ( char * array, int adr ){
  int length = 0;
  while ( isChar(array[adr]) ){
    ++length;
    ++adr;
  }
  return length;
}

int main ( void ){
  int count = 1, count2 = 0;
  int inEnd = 0, inLine = 1;
  int found = 0;
  char * text = (char *) malloc((1000)*sizeof(char));
  char * searched_string = (char *) malloc((1000)*sizeof(char));
  int * lineMem = (int *) malloc((1000)*sizeof(int));
  text[0] = ' ';

  printf("Text:\n");

  while ( 1 ){

    text[count] = getchar();
    lineMem[count] = inLine;

    if ( text[count] > 64 && text[count] < 91 ){
      text[count] += 32;
    }




    if ( text[count] == EOF ){
      printf("Nespravny vstup.\n");
      free(text);
      free(searched_string);
      free(lineMem);
      return 0;
    }



    if ( text[count] == '\n' ){
      ++inLine;
      ++inEnd;
    }
    else{
      if ( inEnd > 0 )
        --inEnd;
    }

    if ( inEnd == 2 ){
      break;
    }


    //* deletes extra non-characters (2 or more), leaves new_lines (for line count)
    if ( isChar(text[count]) == 0
    && isChar(text[count-1]) == 0 ){
      if ( text[count] == '\n' || text[count-1] == '\n' )
        text[count-1] = '\n';
      --count;
    }
    //*

    if ( isChar(text[count]) == 0 && text[count] != '\n' )
      text[count] = ' ';

    ++count;

    if ( count % 1000 == 0 )
      text = (char *) realloc(text, (count+1000)*sizeof(char));

  }

  printf("Hledani:\n");

  int err = 0;
  while ( 1 ){

    searched_string[count2] = getchar();

    if ( searched_string[0] == '\n' ){
      printf("Neplatny dotaz\n");
    }

    if ( searched_string[count2] > 64 && searched_string[count2] < 91 ){
      searched_string[count2] += 32;
    }



    if ( searched_string[count2] == EOF ){
      free(text);
      free(searched_string);
      free(lineMem);
      return 0;
    }

    //* deletes extra non-characters (2 or more), leaves new_lines (for line count)
    if ( isChar(searched_string[count2]) == 0
    && isChar(searched_string[count2-1]) == 0 ){
      --count2;
    }

    ++count2;

    if ( count2 % 1000 == 0 ){
      searched_string = (char *) realloc(searched_string, (count2+1000)*sizeof(char));
      lineMem = (int *) realloc(lineMem, (count2+1000)*sizeof(int));
    }

    if ( isChar(searched_string[count2]) == 0 && searched_string[count2] != '\n' )
      searched_string[count2] = ' ';


    if ( searched_string[count2 - 1] == '\n' ){

      for ( int i = 0; i < count - 2; ++i ){

        if ( isChar(text[i]) == 0 && isChar(text[i+1]) == 1 && text[i+1] == searched_string[0] ){

          for ( int j = 0; j < count2 - 1; ++j ){
            if ( text[j+i+1] != searched_string[j] ){
              err = 1;
              break;
            }
          }
          if ( err == 0 && (count2 - 1) >= getWordLength(text, i+1)){
            ++found;
            if ( found == 1 ){
              printf("Nalezeno: ");
            }
            if ( found > 1 ){
              printf(", ");
            }

            printf("%d", lineMem[i+1]);

          }
          err = 0;
        }
      }
      if ( found == 0 )
        printf("Nenalezeno");
      printf("\n");
      count2 = 0;
      found = 0;
    }
  }

  free(lineMem);
  free(text);
  free(searched_string);
  return 0;
}
