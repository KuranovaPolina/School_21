#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>


#define LENGTH 80                   // длина стола (горизоталь)
#define HEIGTH 25                   // ширина/высота стола (вертикаль)
#define END_Y_START 5               // отступы для рисования экрана завершения
#define END_X_START 28
#define WINNER_LINE 17

int game();                         // основная ф-я игры
void final_screen(int winner);      // завершающий экран
void welcome_screen();              // открывающий экран

int main() {
    system ("/bin/stty -icanon");   // меняем поведение терминала для игры без "Enter"
    welcome_screen();
    final_screen(game());           // ф-я завершающего экрана пользуется результатом работы основной функции игры
    system ("/bin/stty icanon");

    return 0;
}

int game() {
    const int pads_y = 12;          // начальная вертикальная координата ракеток
    const int pad_1_x0 = 10;        // горизотальная координата ракетки 1
    const int pad_2_x0 = 70;        // горизотальная координата ракетки 2
    const int pads_width = 3;       // ширина ракеток
    const int net = 40;             // координата сетки (центр)
    const int tab = 2;              // отступ сверху для рисования счёта
    const int ink = 35;             // символ-заполнитель

    int ball_y_0 = pads_y - 1;        // начальная вертикальная координата мячика
    int ball_x_p1 = pad_1_x0 + 1;       // начальная горизотальная координата мячика (подаёт первый игрок)
    int ball_x_p2 = pad_2_x0 - 1;       // начальная горизотальная координата мячика (подаёт второй игрок)

    int ball_y = pads_y + 1;          // рабочая вертикальная координата мячика
    int ball_x = pad_1_x0 + 1;         // рабочая горизонтальная координата мячика, подаёт левый игрок
    int pad_1 = pads_y;              // вертикальные координаты ракеток
    int pad_2 = pads_y;
    int b_x_dir, b_y_dir = 1;       // направление полёта мяча (1y - вниз, -1y - вверх, 1x - вправо, -1x - влево)
    int player_1_score = 0;
    int player_2_score = 0;
    char command;                   // переменная буфера комманд



    while (1) {
        printf("\e[1;1H\e[2J");                                     // очистка экрана
        if (player_1_score >= 21 || player_2_score >= 21) break;    // условие выхода из цикла   

        // ракетка 1 упирается в стенки
        pad_1 = (pad_1 < 1) ? 1 : pad_1;
        pad_1 = (pad_1 > (HEIGTH - pads_width - 1)) ? HEIGTH - pads_width - 1 : pad_1;

        // ракетка 2 упирается в стенки
        pad_2 = (pad_2 < 1) ? 1 : pad_2;
        pad_2 = (pad_2 > (HEIGTH - pads_width - 1)) ? HEIGTH - pads_width - 1 : pad_2;

        // при ударе об ракетку горизонтальное направление меняется
        if (ball_x == (pad_1_x0 + 1) && ball_y - pad_1 >= -1 && ball_y - pad_1 <= 3) { b_x_dir = 1; }
        if (ball_x == (pad_2_x0 - 1) && ball_y - pad_2 >= -1 && ball_y - pad_2 <= 3) { b_x_dir = -1; }

        // при ударе об угол ракетки:
        if (ball_x == pad_1_x0 + 1 && (ball_y - pad_1 == -1)) { b_y_dir = -1; }      // от верхнего ракетки 1 летит вверх
        if (ball_x == pad_1_x0 + 1 && (ball_y - pad_1 == 3)) { b_y_dir = 1; }        // от нижнего ракетки 1 летит вниз
        if (ball_x == pad_2_x0 - 1 && (ball_y - pad_2 == -1)) { b_y_dir = -1; }      // от верхнего ракетки 2 летит вверх
        if (ball_x == pad_2_x0 - 1 && (ball_y - pad_2 == 3)) { b_y_dir = 1; }        // от нижнего ракетки 1 летит вниз

        // при ударе об стенку вертикальнрое направление меняется
        if (ball_y == 1 || ball_y == HEIGTH - 2) { b_y_dir *= -1; }

        // мячик полетел
        ball_x += b_x_dir;
        ball_y += b_y_dir;

        // если мячик попал за горизотнальные пределы стола
        if (ball_x < 0 || ball_x >= LENGTH) {
            (ball_x < 0) ? ++player_2_score : ++player_1_score;     // начисляем очки в зависимости от стороны
            ball_y = ball_y_0;                                      // ставим мячик на начальные координаты
            (ball_x < 0) ? ball_x = ball_x_p2 : (ball_x = ball_x_p1);  // подачу делает тот, кто "забил"
            pad_1 = pad_2 = pads_y;                                 // ставим ракетки на начальные координаты
            b_y_dir *= -1;                                          // мячик в противоположном направлении относительно момента "гола"
        }

        // делим числа очков игроков на цифры для обображения на табло
        int d1 = player_1_score / 10;
        int d2 = player_1_score % 10;
        int d3 = player_2_score / 10;
        int d4 = player_2_score % 10;

        for (int y = 0; y < HEIGTH; ++y) {                                                      // рисуем поляну, цикл строк
            for (int x = 0; x < LENGTH; ++x) {                                                  // вложенный цикл столбцов
                    // пиксели, ряд 1
                    if ((x == net - 11) && (y == tab + 1) && (d1 == 2)) printf("%c%c", 8, ink);
                    if ((x == net - 10) && (y == tab + 1) && (d1 == 2)) printf("%c%c", 8, ink);
                    if ((x == net - 9) && (y == tab + 1) && (d1 == 1 || d1 == 2)) printf("%c%c", 8, ink);

                    if ((x == net - 6) && (y == tab + 1) && (d2 == 2 || d2 == 3 || d2 == 4 || d2 == 5 || d2 == 6 || d2 == 7 || d2 == 8 || d2 == 9 || d2 == 0)) printf("%c%c", 8, ink);
                    if ((x == net - 5) && (y == tab + 1) && (d2 == 2 || d2 == 3 || d2 == 5 || d2 == 6 || d2 == 7 || d2 == 8 || d2 == 9 || d2 == 0)) printf("%c%c", 8, ink);
                    if ((x == net - 4) && (y == tab + 1) && (d2 == 1 || d2 == 2 || d2 == 3 || d2 == 4 || d2 == 5 || d2 == 6 || d2 == 7 || d2 == 8 || d2 == 9 || d2 == 0)) printf("%c%c", 8, ink);
                    // ------
                    if ((x == net + 4) && (y == tab + 1) && (d3 == 2)) printf("%c%c", 8, ink);
                    if ((x == net + 5) && (y == tab + 1) && (d3 == 2)) printf("%c%c", 8, ink);
                    if ((x == net + 6) && (y == tab + 1) && (d3 == 1 || d3 == 2)) printf("%c%c", 8, ink);

                    if ((x == net + 9) && (y == tab + 1) && (d4 == 2 || d4 == 3 || d4 == 4 || d4 == 5 || d4 == 6 || d4 == 7 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    if ((x == net + 10) && (y == tab + 1) && (d4 == 2 || d4 == 3 || d4 == 5 || d4 == 6 || d4 == 7 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    if ((x == net + 11) && (y == tab + 1) && (d4 == 1 || d4 == 2 || d4 == 3 || d4 == 4 || d4 == 5 || d4 == 6 || d4 == 7 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    // ряд 2
                    // if( (x == net - 11) && (y == tab + 2) && (d1 == ())) { printf("%c%c", 8, ink); }
                    // if( (x == net - 10) && (y == tab + 2) && (d1 == ())) { printf("%c%c", 8, ink); }
                    if ((x == net - 9) && (y == tab + 2) && (d1 == 1 || d1 == 2)) printf("%c%c", 8, ink);

                    if ((x == net - 6) && (y == tab + 2) && (d2 == 4 || d2 == 5 || d2 == 6 || d2 == 8 || d2 == 9 || d2 == 0)) printf("%c%c", 8, ink);
                    if ((x == net - 5) && (y == tab + 2) && (d2 == 7)) printf("%c%c", 8, ink);
                    if ((x == net - 4) && (y == tab + 2) && (d2 == 1 || d2 == 2 || d2 == 3 || d2 == 4 || d2 == 8 || d2 == 9 || d2 == 0)) printf("%c%c", 8, ink);
                    // ------
                    // if( (x == net + 4) && (y == tab + 2) && (d3 == ())) { printf("%c%c", 8, ink); }
                    // if( (x == net + 5) && (y == tab + 2) && (d3 == ())) { printf("%c%c", 8, ink); }
                    if ((x == net + 6) && (y == tab + 2) && (d3 == 1 || d3 == 2)) printf("%c%c", 8, ink);

                    if ((x == net + 9) && (y == tab + 2) && (d4 == 4 || d4 == 5 || d4 == 6 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    if ((x == net + 10) && (y == tab + 2) && (d4 == 7)) printf("%c%c", 8, ink);
                    if ((x == net + 11) && (y == tab + 2) && (d4 == 1 || d4 == 2 || d4 ==  3 || d4 == 4 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    // ряд 3
                    if ((x == net - 11) && (y == tab + 3) && (d1 == 2)) printf("%c%c", 8, ink);
                    if ((x == net - 10) && (y == tab + 3) && (d1 == 2)) printf("%c%c", 8, ink);
                    if ((x == net - 9) && (y == tab + 3) && (d1 == 1 || d1 == 2)) printf("%c%c", 8, ink);

                    if ((x == net - 6) && (y == tab + 3) && (d2 == 2 || d2 == 4 || d2 == 5 || d2 == 6 || d2 == 7 || d2 == 8 || d2 == 9 || d2 == 0)) printf("%c%c", 8, ink);
                    if ((x == net - 5) && (y == tab + 3) && (d2 == 2 || d2 ==  3 || d2 == 4 || d2 == 5 || d2 == 6 || d2 == 8 || d2 == 9)) printf("%c%c", 8, ink);
                    if ((x == net - 4) && (y == tab + 3) && (d2 == 1 || d2 ==  2 || d2 ==  3 || d2 ==  4 || d2 ==  5 || d2 ==  6 || d2 ==  8 || d2 ==  9 || d2 ==  0)) printf("%c%c", 8, ink);
                    // ------
                    if ((x == net + 4) && (y == tab + 3) && (d3 == 2)) printf("%c%c", 8, ink);
                    if ((x == net + 5) && (y == tab + 3) && (d3 == 2)) printf("%c%c", 8, ink);
                    if ((x == net + 6) && (y == tab + 3) && (d3 == 1 || d3 == 2)) printf("%c%c", 8, ink);

                    if ((x == net + 9) && (y == tab + 3) && (d4 == 2 || d4 == 4 || d4 == 5 || d4 == 6 || d4 == 7 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    if ((x == net + 10) && (y == tab + 3) && (d4 == 2 || d4 == 3 || d4 == 4 || d4 == 5 || d4 == 6 || d4 == 8 || d4 == 9)) printf("%c%c", 8, ink);
                    if ((x == net + 11) && (y == tab + 3) && (d4 == 1 || d4 == 2 || d4 == 3 || d4 == 4 || d4 == 5 || d4 == 6 || d4 == 8 || d4 == 9 || d4 == 0)) printf("%c%c", 8, ink);
                    // ряд 4
                    if ((x == net - 11) && (y == tab + 4) && (d1 == 2)) printf("%c%c", 8, ink);
                    // if ((x == net - 10) && (y == tab + 4) && (d1 == ())) { printf("%c%c", 8, ink); }
                    if ((x == net - 9) && (y == tab + 4) && (d1 == 1)) printf("%c%c", 8, ink);

                    if ((x == net - 6) && (y == tab + 4) && (d2 == 2 || d2 == 6 || d2 == 7 || d2 == 8 || d2 == 0)) printf("%c%c", 8, ink);
                    if ((x == net - 5) && (y == tab + 4) && (d2 ==  9)) printf("%c%c", 8, ink);
                    if ((x == net - 4) && (y == tab + 4) && (d2 == 1 || d2 ==  3 || d2 == 4 || d2 == 5 || d2 == 6 || d2 == 8 || d2 == 0)) printf("%c%c", 8, ink);
                    // ------
                    if ((x == net + 4) && (y == tab + 4) && (d3 == 2)) printf("%c%c", 8, ink);
                    // if ((x == net + 5) && (y == tab + 4) && (d3 == ())) { printf("%c%c", 8, ink); }
                    if ((x == net + 6) && (y == tab + 4) && (d3 == 1)) printf("%c%c", 8, ink);

                    if ((x == net + 9) && (y == tab + 4) && (d4 == 2 || d4 ==  6 || d4 ==  7 || d4 ==  8 || d4 ==  0)) { printf("%c%c", 8, ink); }
                    if ((x == net + 10) && (y == tab + 4) && (d4 ==  9)) { printf("%c%c", 8, ink); }
                    if ((x == net + 11) && (y == tab + 4) && (d4 == 1 || d4 == 3 || d4 ==  4 || d4 ==  5 || d4 ==  6 || d4 ==  8 || d4 ==  0)) { printf("%c%c", 8, ink); }
                    // ряд 5
                    if ((x == net - 11) && (y == tab + 5) && (d1 == 2)) { printf("%c%c", 8, ink); }
                    if ((x == net - 10) && (y == tab + 5) && (d1 == 2)) { printf("%c%c", 8, ink); }
                    if ((x == net - 9) && (y == tab + 5) && (d1 == 1 || d1 == 2)) { printf("%c%c", 8, ink); }

                    if ((x == net - 6) && (y == tab + 5) && (d2 == 2 || d2 == 3 || d2 == 5 || d2 == 6 || d2 == 7 || d2 == 8 || d2 == 9 || d2 == 0)) { printf("%c%c", 8, ink); }
                    if ((x == net - 5) && (y == tab + 5) && (d2 == 2 || d2 == 3 || d2 == 5 || d2 == 6 || d2 == 8 || d2 == 0)) { printf("%c%c", 8, ink); }
                    if ((x == net - 4) && (y == tab + 5) && (d2 == 1 || d2 == 2 || d2 == 3 || d2 == 4 || d2 == 5 || d2 == 6 || d2 == 8 || d2 == 0)) { printf("%c%c", 8, ink); }
                    // ------
                    if ((x == net + 4) && (y == tab + 5) && (d3 == 2)) { printf("%c%c", 8, ink); }
                    if ((x == net + 5) && (y == tab + 5) && (d3 == 2)) { printf("%c%c", 8, ink); }
                    if ((x == net + 6) && (y == tab + 5) && (d3 == 1 || d3 == 2)) { printf("%c%c", 8, ink); }

                    if ((x == net + 9) && (y == tab + 5) && (d4 == 2 || d4 == 3 || d4 == 5 || d4 == 6 || d4 == 7 || d4 == 8 || d4 == 9 || d4 == 0)) { printf("%c%c", 8, ink); }
                    if ((x == net + 10) && (y == tab + 5) && (d4 == 2 || d4 == 3 || d4 == 5 || d4 == 6 || d4 == 8 || d4 == 0)) { printf("%c%c", 8, ink); }
                    if ((x == net + 11) && (y == tab + 5) && (d4 == 1 || d4 == 2 || d4 == 3 || d4 == 4 || d4 == 5 || d4 == 6 || d4 == 8 || d4 == 0)) { printf("%c%c", 8, ink); }

                // рисуем мячик поверх табло
                // if (x == ball_x && y == ball_y) { printf("%c%c", 8, 64); }

                if (y == 0 || y == HEIGTH - 1) { printf("%c", 61); }                                                // рисуем стенку
                else if (x == pad_1_x0 && y - pad_1 >= 0 && y - pad_1 < pads_width) { printf("%c", 72); }           // рисуем левую ракетку
                else if (x == pad_2_x0 && y - pad_2 >= 0 && y - pad_2 < pads_width) { printf("%c", 72); }           // рисуем правую ракетку
                else if (x == ball_x && y == ball_y) { printf("%c", 64); }                                          // рисуем мячик
                else if (x == net) { printf("%c", 124); }                                // рисуем сетку
                else                    // всё остальное белое
                    printf("%c", 32);
            }
            printf("\n");
        }

        fd_set rfds;
        struct timeval tv;
        int retval;

        FD_ZERO(&rfds);
        FD_SET(0, &rfds);

        tv.tv_sec = 0;
        tv.tv_usec = 75000;
        retval = select(1, &rfds, NULL, NULL, &tv);

        if (retval)
        {
            scanf("%c", &command);

            if (command == 'a'|| command == 'A') { --pad_1; }    // a - левая ракетка вверх
            else if (command == 'z' || command == 'Z') { ++pad_1; }    // z - левая ракетка вниз
            else if (command == 'k' || command == 'K') { --pad_2; }    // k - правая ракетка вверх
            else if (command == 'm' || command == 'M') { ++pad_2; }    // m - правая ракетка вниз
        }

        if (player_1_score >= 21 || player_2_score >= 21) break;
    }

    return player_1_score >= 21 ? 1 : 2;
}

void final_screen(int winner) {
    printf("\e[1;1H\e[2J");
    const int ink = 35;             // символ-заполнитель

    for (int y = 1; y <= HEIGTH; y++) {
        if (y == WINNER_LINE) printf("%29cTHE WINNER IS PLAYER %d", ' ', winner);
        else {
            for (int x = 1; x <= LENGTH; x++) {
                if (y == 1 || y == HEIGTH) printf("=");

                // end!
                else if (y == END_Y_START && ((x >= END_X_START && x <= END_X_START + 5) ||
                                            x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                            (x >= END_X_START + 16 && x <= END_X_START + 20) ||
                                            x == END_X_START + 24 || x == END_X_START + 25))
                                            printf("%c", ink);

                else if (y == END_Y_START + 1 && ((x >= END_X_START && x <= END_X_START + 5) ||
                                                x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                                (x >= END_X_START + 16 && x <= END_X_START + 21) ||
                                                x == END_X_START + 24 || x == END_X_START + 25))
                                                printf("%c", ink);

                else if ((y == END_Y_START + 2 || y == END_Y_START + 3) && (x == END_X_START || x == END_X_START + 1 ||
                                                                            x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                                                            x == END_X_START + 16 || x == END_X_START + 17 || x == END_X_START + 20 || x == END_X_START + 21 ||
                                                                            x == END_X_START + 24 || x == END_X_START + 25))
                                                                            printf("%c", ink);

                else if (y == END_Y_START + 4 && ((x >= END_X_START && x <= END_X_START + 5) ||
                                            x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                            x == END_X_START + 16 || x == END_X_START + 17 || x == END_X_START + 20 || x == END_X_START + 21 ||
                                            x == END_X_START + 24 || x == END_X_START + 25))
                                            printf("%c", ink);

                else if (y == END_Y_START + 5 && ((x >= END_X_START && x <= END_X_START + 5) ||
                                                x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 10 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                                x == END_X_START + 16 || x == END_X_START + 17 || x == END_X_START + 20 || x == END_X_START + 21 ||
                                                x == END_X_START + 24 || x == END_X_START + 25))
                                                printf("%c", ink);

                else if (y == END_Y_START + 6 && (x == END_X_START || x == END_X_START + 1 ||
                                                (x >= END_X_START + 8 && x <= END_X_START + 13) ||
                                                x == END_X_START + 16 || x == END_X_START + 17 || x == END_X_START + 20 || x == END_X_START + 21 ||
                                                x == END_X_START + 24 || x == END_X_START + 25))
                                                printf("%c", ink);

                else if (y == END_Y_START + 7 && (x == END_X_START || x == END_X_START + 1 ||
                                                (x >= END_X_START + 8 && x <= END_X_START + 13) ||
                                                x == END_X_START + 16 || x == END_X_START + 17 || x == END_X_START + 20 || x == END_X_START + 21))
                                                printf("%c", ink);

                else if (y == END_Y_START + 8 && ((x >= END_X_START && x <= END_X_START + 5) ||
                                                x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 11 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                                (x >= END_X_START + 16 && x <= END_X_START + 21) ||
                                                x == END_X_START + 24 || x == END_X_START + 25))
                                                printf("%c", ink);

                else if (y == END_Y_START + 9 && ((x >= END_X_START && x <= END_X_START + 5) ||
                                                x == END_X_START + 8 || x == END_X_START + 9 || x == END_X_START + 12 || x == END_X_START + 13 ||
                                                (x >= END_X_START + 16 && x <= END_X_START + 20) ||
                                                x == END_X_START + 24 || x == END_X_START + 25))
                                                printf("%c", ink);

                else printf(" ");
            }
            printf("\n");
        }
    }
}

void welcome_screen() {

        printf("\e[1;1H\e[2J");

        printf ("================================================================================\n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("                         ######    #####    ##  ##   #####                      \n");
        printf ("                         #######  #######   ##  ##  ######                      \n");
        printf ("                         ##   ##  ##   ##   ##  ##  ##  ##                      \n");
        printf ("                         ##   ##  ##   ##   ##  ##  ##                          \n");
        printf ("                         #######  ##   ##   ##  ##  ##  ##                      \n");
        printf ("                         ######   ##   ##   ### ##  ##  ##                      \n");
        printf ("                         ##       ##   ##   ######  ##   #                      \n");
        printf ("                         ##       ##   ##   ######  ##   #                      \n");
        printf ("                         ##       #######   ## ###  ######                      \n");
        printf ("                         ##        #####    ##  ##   ####                       \n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("                           LIVE VERSION V.99 BY ???? TEAM                        \n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("                          PRESS ANY KEY TO START THE GAME                       \n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("                                                                                \n");
        printf ("================================================================================\n");

    getchar();
}
