13
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  int total_tries = 0;
  int limit, guess, reward;
  printf("Please choose the limit value:\n");
  scanf("%d", &limit);
  srand(time(NULL));
  reward = rand() % limit + 1;

  // printf("正确数值: %d\n", reward);
  while (total_tries < 7) {
    printf("Please guess the number\n");
    scanf("%d", &guess);
    // 检查是否猜对
    if (guess == reward) {
      printf("YOU WIN!\n");
      return 0;
    } else if (guess < reward) {
      printf("Smaller than the reward!\n");
    } else {
      printf("Larger than the reward!\n");
    }
    total_tries++; // number_of_tries = number_of_tries -1;
  }

  printf("YOU LOSE!\n");
  return 0;
}