// Rabin-Karp algorithm in C++

#include <string.h>

#include <iostream>
using namespace std;

#define d 10

void MyRabinKarp(char pattern[], char text[], int prime) {
  int pattern_len = strlen(pattern);
  int text_len = strlen(text);
  int i,j;
  int pattern_hash = 0;
  int text_hash = 0;
  int h = 1;

  for (i = 0; i <pattern_len - 1; i++)
    h = (h * d) % prime;

  // Calculate hash value for pattern and text
  for ( i = 0; i <pattern_len; i++) {
    pattern_hash = (d * pattern_hash + pattern[i]) % prime;
    text_hash = (d * text_hash + text[i]) % prime;
  }

  // Find thepattern_lenatch
  for (int i = 0; i <= text_len -pattern_len; i++) {
    if (pattern_hash == text_hash) {
      for ( j = 0; j <pattern_len; j++) {
        if (text[i + j] != pattern[j])
          break;
      }

      if (j ==pattern_len)
        cout << "Pattern is found at position: " << i + 1 << endl;
    }

    if (i < text_len -pattern_len) {
      text_hash = (d * (text_hash - text[i] * h) + text[i +pattern_len]) % prime;

      if (text_hash < 0)
        text_hash = (text_hash + prime);
    }
  }
}

int main() {
  char text[] = "vcbghgyyfg";
  char pattern[] = "fg";
  int prime = 13;
  MyRabinKarp(pattern, text, prime);
}