#include <string.h>
#include "hangman-io.h"
#include "words.h"

// difference between lower case and upper case
const char lower_upper = 'a' - 'A';

int main(void) {
  char playagn = 'Y';
  do {
    int game_num = 0;
    printf(enter_game_number, max_words);
    scanf("%d", &game_num);
    
    // the game_number is invalid
    while (game_num < 1 || game_num > max_words) {
      printf("%s", invalid_game_number);
      printf(enter_game_number, max_words);
      scanf("%d", &game_num);
    }
    
    // the game_number is valid and start guessing
    const char *word = get_word(game_num);
    int word_len = strlen(word);
    
    // create a board with spaces and asterisks to update current guessed board 
    char currentboard[51] = {0};
    int initial_i = 0;
    const char *initial_cpyword = word;
    while (initial_i < word_len) {
      if (*initial_cpyword == ' ') {
        currentboard[initial_i] = ' ';
      } else {
        currentboard[initial_i] = '*';
      }
      ++initial_i, 
      ++initial_cpyword;
    }
    
    int strike = 0;
    bool guessed_letter[128] = {false};
    
    while (strike < max_strikes) {
      // check for currentboard is complete or not
      bool succeed = true;
      for(int i = 0; i < word_len; ++i) {
        if (currentboard[i] == '*') succeed = false;
      }
      if (succeed) break;
      
      // print out hangman, letter_prompt and the current board 
      print_hangman(strike);
      printf("%s",letter_prompt);
      for(int i = 0; i < word_len; ++i) {
        printf("%c", currentboard[i]);
      }
      printf("\n");
      
      // read in char and do different things based on the input
      char c = ' ';
      scanf("%c", &c);
      
      // ignore white spaces
      while (c == '\n' || c == ' ') {
        scanf("%c", &c);
      }
      
      // char is not a letter
      if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z') {
        printf(not_a_letter, c);
        continue;
      }
      
      // char is already guessed
      if (c >= 'A' && c <= 'Z') {
        if (guessed_letter[c - 1] || guessed_letter[c + lower_upper - 1]) {
          printf(already_guessed_letter, c);
          continue;
        } else {
          guessed_letter[c - 1] = true;
          guessed_letter[c + lower_upper - 1] = true;
        }
      } else {
        if (guessed_letter[c - 1] || guessed_letter[c - lower_upper - 1]) {
          printf(already_guessed_letter, c - lower_upper);
          continue;
        } else {
          guessed_letter[c - 1] = true;
          guessed_letter[c - lower_upper - 1] = true;
        }
      }
      
      // char is unguessed right number
      bool right = false;
      const char *cpy_word = word;
      for (int i = 0; *cpy_word; ++i, ++cpy_word) {
        if (*cpy_word == c || *cpy_word == c - lower_upper) {
          if (c >= 'A' && c <= 'Z') {
            currentboard[i] = c;
          } else {
            currentboard[i] = c - lower_upper;
          }
          right = true;
        }
      }
      if (right) continue;
      
      // char is unguessed wrong number
      if (c >= 'A' && c <= 'Z') {
        printf(not_in_word, c);
      } else {
        printf(not_in_word, c - lower_upper);
      }
      ++strike;
      if (strike == max_strikes) {
        print_hangman(max_strikes);
        printf(game_over, word);
        break;
      }
      printf(not_last_guess, max_strikes - strike);
    }
    
    // if all letters are guessed
    if (strike < max_strikes) {
      printf(congratulations, word);
    }
    
    // ask for whether to play again
    printf("%s",play_again);
    scanf("%c", &playagn);
    while (!(playagn == 'Y') && !(playagn == 'y') &&
           !(playagn == 'N') && !(playagn == 'n')) {
      if (playagn == '\n' || playagn == ' ') {
        scanf("%c", &playagn);
        continue;
      }
      printf("%s",invalid_play_again_response);
      printf("%s",play_again);
      scanf("%c", &playagn);
    }
  } while (playagn == 'Y' || playagn == 'y');
  
  return 0;
}
