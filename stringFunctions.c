#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringFunctions.h"


int getCharValue(char c){
  if(c >= 'a' && c <= 'z'){
    return c-'a'+1;
  }
  else if(c >= 'A' && c <= 'Z'){
    return c-'A'+1;
  }
  return 0;
}

int getNumerology(char word[WORD]){
  int sum = 0;
  for(int idx = 0; idx<strlen(word); idx++){
    sum+=getCharValue(word[idx]);
  }
  return sum;
}

void gematria(char text[TXT], char word[WORD]){
  int wordValue = getNumerology(word);
  int textIdx = 0;
  int outIdx = 0;

  char *minSeq;
  char *outText;
  outText = (char *)calloc(strlen(text),sizeof(char));
  while(textIdx < strlen(text)){
    minSeq = (char *)calloc(strlen(text),sizeof(char));
    int minSeqIdx = 0;
    int seqValue = 0;
    //try to form a sequance only if the current character in the text is a letter
    if(getCharValue(text[textIdx]) != 0){
      do{
        minSeq[minSeqIdx] = text[textIdx+minSeqIdx];
        seqValue += getCharValue(text[textIdx+minSeqIdx]);
        minSeqIdx++;
      }while(seqValue < wordValue && textIdx+minSeqIdx < strlen(text));
    }

    if(seqValue == wordValue){
      //add  ~ character before each new sequance
      if(outIdx > 0){
        outText[outIdx] = '~';
        outIdx++;
      }
      //add the sequance to the out array
      minSeqIdx = 0;
      while(minSeqIdx < strlen(minSeq)){
        outText[outIdx] = minSeq[minSeqIdx];
        outIdx++;
        minSeqIdx++;
      }
    }
    textIdx++;
    free(minSeq);
  }
  printf("Gematria Sequences: %s\n",outText);
  free(outText);
}


void atbash(char text[TXT], char word[WORD]){
  //make the new word we are looking for
  char *newWord;
  newWord = (char *)calloc(strlen(word),sizeof(char));
  for(int i =0; i<strlen(word); i++){
    char newChar = word[i];
    if(word[i] >= 'a' && word[i] <= 'z'){
      newChar = 'z' - getCharValue(newChar)+1;
    }
    else if(word[i] >= 'A' && word[i] <= 'Z'){
      newChar = 'Z' - getCharValue(newChar)+1;
    }
    newWord[i] = newChar;
  }

  int textIdx = 0;
  int outIdx = 0;
  char *minSeq;
  char *outText;
  outText = (char *)calloc(strlen(text),sizeof(char));

  while(textIdx < strlen(text)){
    minSeq = (char *)calloc(strlen(text),sizeof(char));
    if(text[textIdx] != ' ' && text[textIdx] != '\n' && text[textIdx] != '\t'){
      int charCount = 0;
      int minSeqIdx = 0;
      //generate all min sequances so that in each min sequance there are strlen(newWord) non empty characters
      while(charCount < strlen(newWord) && textIdx+minSeqIdx < strlen(text)){
        minSeq[minSeqIdx] = text[textIdx+minSeqIdx];
        if(text[textIdx+minSeqIdx] != ' ' && text[textIdx+minSeqIdx] != '\n' && text[textIdx+minSeqIdx] != '\t'){
          charCount++;
        }
        minSeqIdx++;
      }

      //validate word made
      int valid = true;
      if(charCount == strlen(newWord)){
        charCount = 0;
        minSeqIdx = 0;
        //check that min sequance contains the new word
        while(charCount < strlen(newWord) && valid == true){
          if(minSeq[minSeqIdx] != ' ' && minSeq[minSeqIdx] != '\n' && minSeq[minSeqIdx] != '\t'){
            if(minSeq[minSeqIdx] != newWord[charCount]){
              valid = false;
            }
            charCount++;
          }
          minSeqIdx++;
        }
        //check if the min sequance contains the new word in reversed order
        if(valid == false){
          minSeqIdx = 0;
          charCount = strlen(newWord)-1;
          valid = true;

          while(charCount >= 0 && valid == true){
            if(minSeq[minSeqIdx] != ' ' && minSeq[minSeqIdx] != '\n' && minSeq[minSeqIdx] != '\t'){
              if(minSeq[minSeqIdx] != newWord[charCount]){
                valid = false;
              }
              charCount--;
            }
            minSeqIdx++;
          }
        }

        //add new min sequance
        if(valid == true){

          if(outIdx > 0){
            outText[outIdx] = '~';
            outIdx++;
          }
          minSeqIdx = 0;
          while(minSeqIdx < strlen(minSeq)){
            outText[outIdx] = minSeq[minSeqIdx];
            outIdx++;
            minSeqIdx++;
          }
        }
      }
    }
    textIdx++;
    free(minSeq);
  }
  printf("Atbash Sequences: %s\n",outText);
  free(outText);
  free(newWord);

}

void anagram(char text[TXT], char word[WORD]){
  int textIdx = 0;
  int outIdx = 0;
  char *minSeq;
  char *outText;
  outText = (char *)calloc(strlen(text),sizeof(char));
  while(textIdx< strlen(text)){
    minSeq = (char *)calloc(strlen(text),sizeof(char));

    if(text[textIdx] != ' ' && text[textIdx] != '\n' && text[textIdx] != '\t'){
      int charCount = 0;
      int minSeqIdx = 0;

      //generate all min sequances so that in each min sequance there are strlen(word) non empty characters
      while(charCount < strlen(word) && textIdx+minSeqIdx < strlen(text)){
        minSeq[minSeqIdx] = text[textIdx+minSeqIdx];

        if(text[textIdx+minSeqIdx] != ' ' && text[textIdx+minSeqIdx] != '\n' && text[textIdx+minSeqIdx] != '\t'){
          charCount++;
        }
        minSeqIdx++;
      }

      //validate word made
      int valid = true;
      if(charCount == strlen(word)){
        char *newWord;
        newWord = (char *)calloc(strlen(word),sizeof(char));
        for(int i = 0; i<strlen(word); i++){
          newWord[i] = word[i];


        }
        charCount = 0;
        minSeqIdx = 0;
        //check that min sequance contains only the characters of our word
        while(charCount < strlen(word) && valid == true){
          if(minSeq[minSeqIdx] != ' ' && minSeq[minSeqIdx] != '\n' && minSeq[minSeqIdx] != '\t'){
            int contains_char = false;
            for(int i=0; i<strlen(newWord) && contains_char == false;i++){
              if(newWord[i] == minSeq[minSeqIdx]){
                contains_char= true;
                newWord[i] = ' ';
              }
            }
            if(contains_char==false){
              valid = false;
            }

            charCount++;
          }
          minSeqIdx++;
        }

        //add new min sequance
        if(valid == true){

          if(outIdx > 0){
            outText[outIdx] = '~';
            outIdx++;
          }
          minSeqIdx = 0;
          while(minSeqIdx < strlen(minSeq)){
            outText[outIdx] = minSeq[minSeqIdx];
            outIdx++;
            minSeqIdx++;
          }
        }

        free(newWord);
      }
    }
    textIdx++;
    free(minSeq);
  }

  printf("Anagram Sequences: %s\n",outText);
  free(outText);
}
