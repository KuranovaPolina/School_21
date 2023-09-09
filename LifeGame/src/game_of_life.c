#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define LENGTH_X 80  // m
#define HEIGHT_Y 25  // n

#define WHITE 32
#define BLACK 42
#define MULT 1000000

void my_malloc(int ***matrix, int length, int height);
void fill_field(int **matrix, int length, int height);
void output(int **a, int n, int m);
int field_update(int ***matrix, int length, int height);
int counter(int i, int j, int **A);
void start_menu();
void finish_screen(int reason);
int fatal(int **old, int **new);
void printer(char symb, int count);

int main() {
    int **field;
    double speed;

    my_malloc(&field, LENGTH_X, HEIGHT_Y);

    start_menu();

      scanf("%lf\n", &speed);

      fill_field(field, LENGTH_X, HEIGHT_Y);

      if (freopen("/dev/tty", "r", stdin)) printf("Console turn on\n");
      system("/bin/stty -icanon");


        usleep(5 * MULT);
        printf("\e[1;1H\e[2J");
    printf(" speed pause - %lf\n", speed);
      output(field, HEIGHT_Y, LENGTH_X);
        usleep(speed * MULT);

      while (1) {
        char c;

        fd_set rfds;
        struct timeval tv;
        int retval;

        FD_ZERO(&rfds);
        FD_SET(0, &rfds);

        tv.tv_sec = 0;
        tv.tv_usec = (speed * MULT);

        retval = select(1, &rfds, NULL, NULL, &tv);

        if (retval) {
          scanf("%c", &c);
            if (c == 'c') {
              speed += 0.01;
            } else if (c == 'm') {
              speed -= 0.01;
              if (speed <= 0) {
                speed = 0.01;
              }
            }
        }

        int end = field_update(&field, LENGTH_X, HEIGHT_Y);


          printf("\e[1;1H\e[2J");
        printf(" speed pause - %lf\n", speed);
        output(field, HEIGHT_Y, LENGTH_X);

          if (end) {
              printf("\e[1;1H\e[2J");
              finish_screen(end);
              break;
          }
      }

    free(field);

    system("/bin/stty icanon");

    return 0;
}


void my_malloc(int ***matrix, int length, int height) {
    *matrix = malloc(height * sizeof(int *) + height * length * sizeof(int));
    for (int i = 0; i < height; i++)
      (*matrix)[i] = (int *)((*matrix) + height) + length * i;
}

void fill_field(int **matrix, int length, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            scanf("%1d", &matrix[i][j]);
        }
    }
}

void output(int **a, int n, int m) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < m - 1; j++) {
      if (a[i][j] == 0) {
      printf("%c", WHITE);
      } else {printf("%c", BLACK);}
    }
    if (a[i][m - 1] == 0) {
      printf("%c\n", WHITE);
      } else { printf("%c\n", BLACK);}
  }

  for (int j = 0; j < m - 1; j++) {
    if (a[n - 1][j] == 0) {
      printf("%c", WHITE);
      } else {printf("%c", BLACK);}
  }
  if (a[n - 1][m - 1] == 0) {
      printf("%c", WHITE);
      } else {printf("%c", BLACK);}
}

int field_update(int ***matrix, int length, int height) {
    int **u_field;

    my_malloc(&u_field, length, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            int neighbor = counter(i, j, *matrix);
            if ((*matrix)[i][j] == 0 && neighbor == 3) {
                u_field[i][j] = 1;
            } else if ((*matrix)[i][j] == 1 && (neighbor < 2 || neighbor > 3)) {
                u_field[i][j] = 0;
            } else {
                u_field[i][j] = (*matrix)[i][j];
            }
        }
    }

    output(u_field, HEIGHT_Y, LENGTH_X);

    int finish = fatal(u_field, *matrix);

    free(*matrix);
    (*matrix) = u_field;

    return finish;
}

void start_menu() {
    printer('-', 80);
    for (int i = 0; i < 7; i++) {
        printer(' ', 80);
    }
    printf("                                  WELCOME");
    printf("                                       \n");
    printer(' ', 80);
    printf("                                GAME OF LIFE");
    printf("                                    \n");
    printer(' ', 80);
    printf("                              TO CONTINUE PRESS");
    printf("                                 \n");
    printer(' ', 80);
    printf("                                BUTTON  SPACE");
    printf("                                   \n");
    printer(' ', 80);
    printer(' ', 80);
    printf("                        M - speed UP / C - speed DOWN ");
    printf("                           \n");
    for (int i = 0; i < 6; i++) {
        printer(' ', 80);
    }
    printer('-', 80);
}


void finish_screen(int reason) {
    printer('-', 80);
    printer(' ', 80);
    printf("                          ******  **  **  *****   **");
    printf("                           \n");
    printf("                          ******  **  **  ******  **");
    printf("                           \n");
    printf("                          **      **  **  **  **  **");
    printf("                           \n");
    printf("                          **      **  **  **  **  **");
    printf("                           \n");
    printf("                          ******  **  **  **  **  **");
    printf("                           \n");
    printf("                          ******  *** **  **  **  **");
    printf("                           \n");
    printf("                          **      ******  **  **  **");
    printf("                           \n");
    printf("                          **      ******  **  **");
    printf("                               \n");
    printf("                          ******  ** ***  ******  **");
    printf("                           \n");
    printf("                          ******  **  **  *****   **");
    printf("                           \n");
    printer(' ', 80);
    printer(' ', 80);
    if (reason == 1) {
        printf("                                Nothing changed");
        printf("                                \n");
    } else if (reason == 2) {
        printf("                                 Everyone died");
        printf("                                 \n");
    }
    for (int i = 0; i < 9; i++) {
        printer(' ', 80);
    }

    printer('-', 80);
}

int counter(int i, int j, int **A) {
    int count = 0;
    int a = i + 1;
    int b = j - 1;
    int c = i - 1;
    int d = j + 1;
    if (i == HEIGHT_Y - 1) {a = 0;}
    if (j == 0) {b = LENGTH_X - 1;}
    if (i == 0) {c = HEIGHT_Y - 1;}
    if (j == LENGTH_X - 1) {d = 0;}
    if (A[a][j] == 1)  count++;
    if (A[a][b] == 1)  count++;
    if (A[i][b] == 1) count++;
    if (A[c][b] == 1) count++;
    if (A[c][j] == 1) count++;
    if (A[c][d] == 1) count++;
    if (A[i][d] == 1) count++;
    if (A[a][d] == 1)  count++;
    return count;
}

int fatal(int **old, int **new) {
    int flag = 0;
    int count_dif = 0;
    int count_live = 0;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (old[i][j] == 1) {
                count_live++;
            }
            if (old[i][j] != new[i][j]) {
                count_dif++;
            }
        }
    }
    if (count_dif == 0)    {
        flag = 1;
    } else if (count_live == 0) {
        flag = 2;
    }
    return flag;
}

void printer(char symb, int count) {
    for (int i = 0; i < count; i++) {
        printf("%c", symb);
    }
    printf("\n");
}

