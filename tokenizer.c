#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <string.h>
/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{
  return (delim != ((c >= '0'&& c<='9')||(c>= 'a'&& c<= 'z')||(c>= 'A'&& c<= 'Z')) && c==delim);
  //return (c==delim);
  //return(c == ' ' && c == '\0');
}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{
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
  int i = 0;
  while (non_delim_character(str[i],delim)){
    i++;
  }
  return &str[i];

}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim)
{
  int count = 0;
  int i=0;

  for (int i = 0; str[i]!='\0'; i++) {
    if(str[i]== ' '){
      count++;
    }
  }
  return count+1;
 printf( "Count is:%d\n",count);
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
  return copy;
  

}
//citation https://www.youtube.com/watch?v=yFboyOwk2oM

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

  char **array = (char**)malloc(sizeof(char*)*(numtokens));
  char *start = word_start(str,delim);
  char *end = end_word(str,delim);

  for(i=0; i<numtokens; i++){
    array[i]= copy_str(start,end-start,delim);
    printf("Token : %s\n",copy_str(start,end-start,delim));
    start = word_start(end,delim);
    end = end_word(start,delim);
    str = end;
  }

  return array;

}
//citation https://www.youtube.com/watch?v=yFboyOwk2oM

void print_all_tokens(char** tokens)
{
  int i =0;
  while(tokens[i]){
    printf("Tokens: %c",**tokens);
    tokens++;
  }
  return;

}

int main(void){
  char input[]= "Hello, World";  
  char *pinput =input;
  char deli = ',';

  char *x = word_start(pinput,deli);
  printf("The first letter is: %c\n",*x);

  char *y = end_word(pinput,deli);
  printf("The delimeter is: %c\n",*y);

  int count= count_tokens (pinput, deli);
  printf("Number of Tokens: %d\n" , count);

  char *copy = copy_str(pinput, strlen(pinput),deli);
  printf("Copied string:  %s\n",copy);

  char tokenizer = tokenize(pinput,deli);
  

}
