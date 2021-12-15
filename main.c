#include <stdio.h>
#include "stringFunctions.h"
int main(){
  char word[WORD];
  int wordIdx = 0;
  char text[TXT];
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
  char gem[TXT];
  gematria(text,word,gem);

  char atb[TXT];
  atbash(text,word,atb);

  char ana[TXT];
  anagram(text,word,ana);

  printf("Gematria Sequences: %s",gem);
  printf("Atbash Sequences: %s",atb);
  printf("Anagram Sequences: %s",ana);



  return 0;
}
