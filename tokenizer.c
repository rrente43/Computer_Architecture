#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{
  delim = (!((c >= '0'&& c<='9')||(c>= 'a'&& c<= 'z')||(c>= 'A'&& c<= 'Z')));
  return (c==delim);

}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{
  //delim = ((c >= '0'&& c<='9')||(c>= 'a'&& c<= 'z')||(c>= 'A'&& c<= 'Z'));
  return !(delim_character(c,delim));

}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char* str,char delim)
{
  int i = 0;
  while(delim_character(str[i],delim)){
    i++;
  }
  return &str[i];

}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char* str,char delim)
{
  str= word_start(str,delim);
  int i = 0;
  while (non_delim_character(str[i],delim)){
    i++;
  }
  return &str[i];

}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim)
{
  int count;
  for(count=0; str!=end_word(str,delim); count++){
    str=end_word(str,delim);
  }
  return count;

}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim)
{
  int i;
  char* copy = (char*)malloc(sizeof(char)*(len+1));
  for(i=0; i<len; i++){
    copy[i]=inStr[i];
  } 
  copy[i]= '\0';
  return copy;

}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   delimiter-separated tokens from zero-terminated str.
   For example, tokenize("hello world string"), with a character delimiter
   of a space " " would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char** tokenize(char* str, char delim)
{
  int i;
  int numtokens = count_tokens(str,delim);

  char **array = malloc(sizeof(char*)*(numtokens));
  char *start = word_start(str,delim);
  char *end = end_word(str,delim);

  for(i=0; i<numtokens; i++){
    array[i]= copy_str(start,end-start,delim);
    start = word_start(end,delim);
    end = end_word(start,delim);

  }
  array[i]=0;
  return array;

}

void print_all_tokens(char** tokens)
{
  int i =0;
  while(tokens[i]){
    printf(i,tokens[i]);
    i++;
  }
  return;

}

int main(){
  char input[]= "Hello, World";
  char *pinput =input;
  char deli = ',';

  char *x = word_start(pinput,deli);
  printf("The first letter is: %c\n",*x);

  x = end_word(pinput, deli) ;
  printf ("The delimeter is: %c",* x);

}
