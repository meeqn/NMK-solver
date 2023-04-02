#include <iostream>
#define PLAYER_ONE_SYMBOL 1
#define PLAYER_TWO_SYMBOL 2
#define MAX_COMM_LEN 33
#define BOTH_PLAYERS 0
using namespace std;


int returnPlayerSymbol(int chosenPlayer) {
    if (chosenPlayer == 1)
        return PLAYER_ONE_SYMBOL;
    if (chosenPlayer == 2)
        return PLAYER_TWO_SYMBOL;
    return 0;
}
void generate_NMK_board(int** board, int N, int M) {
    for (int i = 0; i < N; i++) {
        board[i] = new int[M];

    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            scanf_s("%d", &board[i][j]);

    }
}

void clear_NMK_board_memory(int** board, int N) {
    for (int i = 0; i < N; i++) {
        delete[] board[i];

    }
    delete[] board;
}

void draw_NMK_board(int** board, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf_s("%d ", board[i][j]);
        printf_s("\n");

    }
}

bool is_pos_in_boundaries(int x, int y, int N, int M) {
    if (x < 0)
        return false;
    else if (y < 0)
        return false;
    else if (y >= N)
        return false;
    else if (x >= M)
        return false;
    else
        return true;
}

bool search_for_line(int** board, int N, int M, int K, int searchedSymbol, int y, int x, int yChange, int xChange, int line) {
    y += yChange;
    x += xChange;
    if (is_pos_in_boundaries(x, y, N, M) && board[y][x] == searchedSymbol) {
        line++;
        if (line == K)
            return true;
        else
            return search_for_line(board, N, M, K, searchedSymbol, y, x, yChange, xChange, line);

    }
    return false;
}

bool is_there_line(int** board, int N, int M, int K, int searchedSymbol, int y, int x) {
    if (search_for_line(board, N, M, K, searchedSymbol, y, x, 0, 1, 1))
        return true;
    else if (search_for_line(board, N, M, K, searchedSymbol, y, x, 1, -1, 1))
        return true;
    else if (search_for_line(board, N, M, K, searchedSymbol, y, x, 1, 1, 1))
        return true;
    else if (search_for_line(board, N, M, K, searchedSymbol, y, x, 1, 0, 1))
        return true;
    return false;
}

bool is_game_finished(int** board, int N, int M, int K, int consideredPlayer) {
    int zeroCount = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 0) {
                zeroCount++;

            }
            else if (board[i][j] == PLAYER_ONE_SYMBOL && consideredPlayer != PLAYER_TWO_SYMBOL) {
                if (is_there_line(board, N, M, K, PLAYER_ONE_SYMBOL, i, j))
                    return true;

            }
            else if (board[i][j] == PLAYER_TWO_SYMBOL && consideredPlayer != PLAYER_ONE_SYMBOL) {
                if (is_there_line(board, N, M, K, PLAYER_TWO_SYMBOL, i, j))
                    return true;

            }

        }

    }
    if (zeroCount == 0 && consideredPlayer == 0)
        return true;
    return false;
}

int get_number_of_combinations(int** board, int N, int M) {
    int tmp = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 0)
                tmp++;

        }

    }
    return tmp;
}

void handle_pos_gen() {
    int N, M, K, chosenPlayer, currPlayerSymbol = 0, combinations = 0;
    scanf_s("%d %d %d %d", &N, &M, &K, &chosenPlayer);
    if (chosenPlayer == 1)
        currPlayerSymbol = PLAYER_ONE_SYMBOL;
    if (chosenPlayer == 2)
        currPlayerSymbol = PLAYER_TWO_SYMBOL;

    int** board = new int* [N];
    generate_NMK_board(board, N, M);

    if (!is_game_finished(board, N, M, K, BOTH_PLAYERS))
        combinations = get_number_of_combinations(board, N, M);
    printf_s("%d\n", combinations);
    if (combinations > 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = currPlayerSymbol;
                    draw_NMK_board(board, N, M);
                    board[i][j] = 0;

                }

            }

        }

    }
    clear_NMK_board_memory(board, N);
}

void handle_advanced_pos_gen() {
    int N, M, K, chosenPlayer, currPlayerSymbol = 0, combinations = 0;
    scanf_s("%d %d %d %d", &N, &M, &K, &chosenPlayer);

    currPlayerSymbol = returnPlayerSymbol(chosenPlayer);

    int** board = new int* [N];
    generate_NMK_board(board, N, M);

    if (!is_game_finished(board, N, M, K, BOTH_PLAYERS))
        combinations = get_number_of_combinations(board, N, M);
    if (combinations > 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = currPlayerSymbol;
                    if (is_game_finished(board, N, M, K, BOTH_PLAYERS)) {
                        printf_s("1\n");
                        draw_NMK_board(board, N, M);
                        clear_NMK_board_memory(board, N);
                        return;

                    }
                    board[i][j] = 0;

                }

            }

        }
        printf_s("%d\n", combinations);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = currPlayerSymbol;
                    draw_NMK_board(board, N, M);
                    board[i][j] = 0;

                }

            }

        }

    }
    else
        printf_s("0\n");
    clear_NMK_board_memory(board, N);
}

int minimax(int** board, int mainPlayer, int otherPlayer, int N, int M, int K, bool isMaximizing) {
    if (is_game_finished(board, N, M, K, 0)) {
        if (is_game_finished(board, N, M, K, mainPlayer))
            return 1;
        else if (is_game_finished(board, N, M, K, otherPlayer))
            return -1;
        else if (get_number_of_combinations(board, N, M) == 0)
            return 0;

    }

    if (isMaximizing) {
        int currPlayerSymbol = returnPlayerSymbol(mainPlayer);
        int topScore = -10;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = currPlayerSymbol;
                    int score = minimax(board, mainPlayer, otherPlayer, N, M, K, false);
                    board[i][j] = 0;
                    if (score > topScore) {
                        topScore = score;
                        if (score == 1)
                            return topScore;

                    }

                }

            }

        }

        return topScore;

    }
    else {
        int currPlayerSymbol = returnPlayerSymbol(otherPlayer);
        int topScore = 10;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = currPlayerSymbol;
                    int score = minimax(board, mainPlayer, otherPlayer, N, M, K, true);
                    board[i][j] = 0;
                    if (score < topScore) {
                        topScore = score;
                        if (score == -1)
                            return topScore;

                    }

                }

            }

        }

        return topScore;

    }
}

void handle_solve_game() {
    int N, M, K, chosenPlayer, currPlayerSymbol = 0;
    scanf_s("%d %d %d %d", &N, &M, &K, &chosenPlayer);

    int** board = new int* [N];
    generate_NMK_board(board, N, M);
    bool gameEnded = false;

    if (is_game_finished(board, N, M, K, 1)) {
        printf_s("FIRST_PLAYER_WINS\n");
        gameEnded = true;

    }
    else if (is_game_finished(board, N, M, K, 2)) {
        printf_s("SECOND_PLAYER_WINS\n");
        gameEnded = true;

    }
    else if (!get_number_of_combinations(board, N, M)) {
        printf_s("BOTH_PLAYERS_TIE\n");
        gameEnded = true;

    }

    while (!gameEnded) {
        int topScore = -10;
        int topX = 0, topY = 0;

        currPlayerSymbol = returnPlayerSymbol(chosenPlayer);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = currPlayerSymbol;
                    int score = minimax(board, chosenPlayer, (chosenPlayer % 2) + 1, N, M, K, false);
                    board[i][j] = 0;
                    if (score > topScore) {
                        topScore = score;
                        topX = j;
                        topY = i;
                        if (score == 1) {
                            i = N;
                            j = M;
                            break;

                        }

                    }

                }

            }

        }

        board[topY][topX] = currPlayerSymbol;
        if (is_game_finished(board, N, M, K, chosenPlayer)) {
            if (chosenPlayer == 1)
                printf_s("FIRST_PLAYER_WINS\n");
            else
                printf_s("SECOND_PLAYER_WINS\n");
            gameEnded = true;
            break;

        }
        else if (!get_number_of_combinations(board, N, M)) {
            printf_s("BOTH_PLAYERS_TIE\n");
            gameEnded = true;
            break;

        }
        chosenPlayer = (chosenPlayer % 2) + 1;


    }
    clear_NMK_board_memory(board, N);
}

int main() {
    char comm[MAX_COMM_LEN] = { NULL
    };

    while (true) {
        if (feof(stdin) != 0) {
            break;

        }
        else {
            scanf_s("%s", comm, (unsigned)_countof(comm));
            if (!strcmp(comm, "GEN_ALL_POS_MOV")) {
                handle_pos_gen();

            }
            else if (!strcmp(comm, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
                handle_advanced_pos_gen();

            }
            else if (!strcmp(comm, "SOLVE_GAME_STATE")) {
                handle_solve_game();

            }
            comm[0] = '\0';

        }

    }
    return 0;
}