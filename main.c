#include <stdio.h>
#include "stringFunctions.h"
#include <string.h>
int main(){
  char word[WORD];// = "fish";
  int wordIdx = 0;
  char text[TXT];// = "One, two, three, four, five,\nOnce I caught a fish alive,\nSix, seven, eight, nine, ten,\nThen I let go again.";
  int textIdx = 0;
  char current_char;

  scanf("%c",&current_char);
  while(current_char!=' ' && current_char!='\n' && current_char!='\t'){
    word[wordIdx] = current_char;
    scanf("%c",&current_char);
    wordIdx++;
  }
  while(current_char!='~'){
    text[textIdx] = current_char;
    scanf("%c",&current_char);
    textIdx++;
  }



  gematria(text,word);
  printf("\n");
  atbash(text,word);
  printf("\n");
  anagram(text,word);


  return 0;
}
