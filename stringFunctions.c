#include <stdio.h>
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

void gematria(char text[TXT], char word[WORD], char outText[TXT]){
  int wordValue = getNumerology(word);
  int textIdx = 0;
  int outIdx = 0;
  while(text[textIdx] < strlen(text)){
    char minSeq[strlen(text)];
    int minSeqIdx = 0;
    int seqValue = 0;
    //try to form a sequance only if the current character in the text is a letter
    if(getCharValue(text[textIdx]) != 0){
      do{
        minSeq[minSeqIdx] = text[textIdx+minSeqIdx];
        seqValue += getCharValue(text[textIdx+minSeqIdx]);
        minSeqIdx++;
      }while(seqValue < wordValue && text[textIdx+minSeqIdx] < strlen(text));
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
  }
}


void atbash(char text[TXT], char word[WORD], char outText[TXT]){
  //make the new word we are looking for
  char newWord[strlen(word)];
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
  while(text[textIdx] < strlen(text)){
    if(text[textIdx] != ' ' && text[textIdx] != '\n' && text[textIdx] != '\t'){
      char minSeq[strlen(text)];
      int charCount = 0;
      int minSeqIdx = 0;
      //generate all min sequances so that in each min sequance there are strlen(newWord) non empty characters
      while(charCount < strlen(newWord) && text[textIdx+minSeqIdx] < strlen(text)){
        minSeq[minSeqIdx] = text[textIdx+minSeqIdx];
        minSeqIdx++;
        if(text[textIdx+minSeqIdx] != ' ' && text[textIdx+minSeqIdx] != '\n' && text[textIdx+minSeqIdx] != '\t'){
          charCount++;
        }
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
          charCount = strlen(newWord)-1;
          valid = true;
          while(charCount >= 0 && valid == true){
            if(minSeq[minSeqIdx] != ' ' && minSeq[minSeqIdx] != '\n' && minSeq[minSeqIdx] != '\t'){
              if(minSeq[minSeqIdx] != newWord[charCount]){
                valid = 0;
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


  }



}

void anagram(char text[TXT], char word[WORD], char outText[TXT]){
  int textIdx = 0;
  int outIdx = 0;
  while(text[textIdx] < strlen(text)){
    if(text[textIdx] != ' ' && text[textIdx] != '\n' && text[textIdx] != '\t'){
      char minSeq[strlen(text)];
      int charCount = 0;
      int minSeqIdx = 0;
      //generate all min sequances so that in each min sequance there are strlen(word) non empty characters
      while(charCount < strlen(word) && text[textIdx+minSeqIdx] < strlen(text)){
        minSeq[minSeqIdx] = text[textIdx+minSeqIdx];
        minSeqIdx++;
        if(text[textIdx+minSeqIdx] != ' ' && text[textIdx+minSeqIdx] != '\n' && text[textIdx+minSeqIdx] != '\t'){
          charCount++;
        }
      }
      //validate word made
      int valid = true;
      if(charCount == strlen(word)){
        char newWord[strlen(word)];
        for(int i =0; i<strlen(word); i++){
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
      }
    }
    textIdx++;
  }
}
