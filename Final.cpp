#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// Constants for Tic-Tac-Toe
#define SIZE 3

// Function prototypes for Tic-Tac-Toe
struct Cell
{
    char symbol;
};
Cell* create_board();
void free_board(Cell* board);
void draw_board(Cell* board);
bool is_valid_move(Cell* board, int row, int col);
bool is_board_full(Cell* board);
int check_win(Cell* board, char symbol);
int play_game(int againstComputer);
void make_move(Cell* board, int player, int row, int col);
void player_move(Cell* board, int player);
void computer_move(Cell* board);
int get_random_move(Cell* board);
char get_player_symbol(int player);

// Function prototypes for Quiz Game
void quiz_game();

// Function prototypes for Rock Paper Scissor Game
void rock_paper_scissor_game();

// Function prototypes for Snake Game
void snake_game();

// Main Menu function
void display_menu()
{
    cout << "Select a game to play: " << endl;
    cout << "1. Tic-Tac-Toe" << endl;
    cout << "2. Quiz Game" << endl;
    cout << "3. Rock Paper Scissor" << endl;
    cout << "4. Snake Game" << endl;
    cout << "5. Exit" << endl;
    cout << "Which game do you want to play? Enter your choice: ";
}

int main()
{
    int choice;
    do
    {
        display_menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            char playAgain = 'y';
            while (playAgain == 'y' || playAgain == 'Y')
            {
                int againstComputer;
                cout << "Do you want to play against the computer (1) or another player (2)?or get (0) Enter 1 or 2 or 0: ";
                cin >> againstComputer;
                if(againstComputer==0) break;
                if (againstComputer != 1 && againstComputer != 2)
                {
                    cout << "Invalid choice. Exiting..." << endl;
                    return 1;
                }

                int winner = play_game(againstComputer);
                if (winner)
                {
                    cout << "Player " << winner << " (" << get_player_symbol(winner) << ") wins!" << endl;
                }
                else
                {
                    cout << "The game is a draw." << endl;
                }

                cout << "Do you want to play again? (y/n): ";
                cin >> playAgain;
            }
            break;
        }
        case 2:
            quiz_game();
            break;
        case 3:
            rock_paper_scissor_game();
            break;
        case 4:
            snake_game();
            break;
        case 5:
            cout << "Exiting the game. Thank you for playing!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
    while (choice != 5);
    return 0;
}

// Tic-Tac-Toe Game functions
Cell* create_board()
{
    Cell* board = new Cell[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        board[i].symbol = ' ';
    }
    return board;
}

void free_board(Cell* board)
{
    delete[] board;
}

void draw_board(Cell* board)
{
    cout << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << " " << board[i * SIZE + j].symbol;
            if (j < SIZE - 1)
            {
                cout << " |";
            }
        }
        cout << endl;
        if (i < SIZE - 1)
        {
            cout << string(4 * SIZE - 1, '-') << endl;
        }
    }
    cout << endl;
}

bool is_valid_move(Cell* board, int row, int col)
{
    return (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && board[(row - 1) * SIZE + (col - 1)].symbol == ' ');
}

bool is_board_full(Cell* board)
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        if (board[i].symbol == ' ')
        {
            return false;
        }
    }
    return true;
}

int check_win(Cell* board, char symbol)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i * SIZE].symbol == symbol && board[i * SIZE + 1].symbol == symbol && board[i * SIZE + 2].symbol == symbol)
        {
            return (symbol == 'X') ? 1 : 2;
        }
        if (board[0 * SIZE + i].symbol == symbol && board[1 * SIZE + i].symbol == symbol && board[2 * SIZE + i].symbol == symbol)
        {
            return (symbol == 'X') ? 1 : 2;
        }
    }

    if (board[0 * SIZE + 0].symbol == symbol && board[1 * SIZE + 1].symbol == symbol && board[2 * SIZE + 2].symbol == symbol)
    {
        return (symbol == 'X') ? 1 : 2;
    }
    if (board[0 * SIZE + 2].symbol == symbol && board[1 * SIZE + 1].symbol == symbol && board[2 * SIZE + 0].symbol == symbol)
    {
        return (symbol == 'X') ? 1 : 2;
    }

    return 0;
}

void player_move(Cell* board, int player)
{
    int row, col;
    do
    {
        cout << "Player " << player << " (" << get_player_symbol(player) << "), enter your move (row, col): ";
        cin >> row >> col;
        if (!is_valid_move(board, row, col))
        {
            cout << "Invalid move. Please try again." << endl;
        }
    }
    while (!is_valid_move(board, row, col));
    make_move(board, player, row, col);
}

void computer_move(Cell* board)
{
    int row, col;
    do
    {
        int move = get_random_move(board);
        row = move / SIZE + 1;
        col = move % SIZE + 1;
    }
    while (!is_valid_move(board, row, col));
    cout << "Computer (C) chooses " << row << " " << col << endl;
    make_move(board, 2, row, col);
}

int get_random_move(Cell* board)
{
    int emptyCells[SIZE * SIZE];
    int emptyCount = 0;
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        if (board[i].symbol == ' ')
        {
            emptyCells[emptyCount] = i;
            emptyCount++;
        }
    }
    srand(static_cast<unsigned int>(time(NULL)));
    int randomIndex = rand() % emptyCount;
    return emptyCells[randomIndex];
}

char get_player_symbol(int player)
{
    return (player == 1) ? 'X' : 'O';
}

void make_move(Cell* board, int player, int row, int col)
{
    board[(row - 1) * SIZE + (col - 1)].symbol = get_player_symbol(player);
}

// Play Game function
int play_game(int againstComputer)
{
    Cell* board = create_board();
    int currentPlayer = 1; // Player 1 starts
    draw_board(board);

    while (true)
    {
        if (currentPlayer == 1)
        {
            player_move(board, currentPlayer);
        }
        else
        {
            if (againstComputer == 1)
            {
                computer_move(board);
            }
            else
            {
                player_move(board, currentPlayer);
            }
        }

        draw_board(board);

        // Check for a win
        int winner = check_win(board, get_player_symbol(currentPlayer));
        if (winner != 0)
        {
            free_board(board);
            return winner; // Return the winner
        }

        // Check for a draw
        if (is_board_full(board))
        {
            free_board(board);
            return 0; // Draw
        }

        // Switch player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    free_board(board);
    return 0; // This line should never be reached
}

// Quiz Game
void quiz_game() {
    char playAgain;

    do {
        int score = 0, wrong = 0, correct = 0;
        char ans;

        cout << ".........Quiz Game........\n";

        for (int i = 1; i <= 5; i++) {
            switch (i) {
                case 1:
                    cout << "Q1. Who is the father of Computers?\n";
                    cout << "A) James Gosling\t\tB) Charles Babbage\n";
                    cout << "C) Dennis Ritchie\t\tD) Bjarne Stroustrup\n";
                    break;
                case 2:
                    cout << "Q2. What is the full form of CPU?\n";
                    cout << "A) Computer Processing Unit\t\tB) Computer Principle Unit\n";
                    cout << "C) Central Processing Unit\t\tD) Control Processing Unit\n";
                    break;
                case 3:
                    cout << "Q3. Which of the following are physical devices of a computer?\n";
                    cout << "A) Hardware\t\tB) Software\n";
                    cout << "C) System Software\tD) Package\n";
                    break;
                case 4:
                    cout << "Q4. Which of the following is the smallest unit of data in a computer?\n";
                    cout << "A) Bit\t\tB) KB\n";
                    cout << "C) Nibble\tD) Byte\n";
                    break;
                case 5:
                    cout << "Q5. Which of the following is not a characteristic of a computer?\n";
                    cout << "A) Versatility\t\tB) Accuracy\n";
                    cout << "C) Diligence\t\tD) I.Q\n";
                    break;
            }
            cout << "Enter your answer (A/B/C/D) or (0) to go back: ";
            cin >> ans;
            if (ans == '0') return;

            // Check answers for all questions
            if ((i == 1 && (ans == 'B' || ans == 'b')) ||
                (i == 2 && (ans == 'C' || ans == 'c')) ||
                (i == 3 && (ans == 'A' || ans == 'a')) ||
                (i == 4 && (ans == 'A' || ans == 'a')) ||
                (i == 5 && (ans == 'D' || ans == 'd'))) {
                cout << "Correct!\n";
                score++;
                correct++;
            } else {
                cout << "Wrong! Correct answer: " << ((i == 1) ? 'B' : (i == 2 ? 'C' : (i == 3 ? 'A' : (i == 4 ? 'A' : 'D')))) << endl;
                wrong++;
            }
        }

        cout << "\nYour Score is: " << score << "\nCorrect Answers: " << correct << "\nWrong Answers: " << wrong << "\n";

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');
}


// Rock Paper Scissors Game
void  rock_paper_scissor_game() {
    srand(static_cast<unsigned int>(time(NULL))); // Seed random number generator
    int wins = 0, losses = 0, ties = 0;
    char playAgain;


    do {
        cout << "ROCK PAPER SCISSORS GAME" << endl;
        for (int i = 0; i < 3; i++) {  // Play 3 rounds
            char move;
            do {
                cout << "'r' for ROCK\n'p' for PAPER\n's' for SCISSORS\nYour move: ";
                cin >> move;
            } while (move != 'r' && move != 'p' && move != 's');

            int computerChoice = rand() % 3 + 1; // Random choice for computer
            cout << "Your move is " << (move == 'r' ? "ROCK" : move == 'p' ? "PAPER" : "SCISSORS") << endl;
            cout << "Computer's move: " << (computerChoice == 1 ? "ROCK" : computerChoice == 2 ? "PAPER" : "SCISSORS") << endl;

            // Determine the winner
            if ((move == 'r' && computerChoice == 1) || (move == 'p' && computerChoice == 2) || (move == 's' && computerChoice == 3)) {
                cout << "It's a tie!" << endl;
                ties++;
            } else if ((move == 'r' && computerChoice == 3) || (move == 'p' && computerChoice == 1) || (move == 's' && computerChoice == 2)) {
                cout << "You win!" << endl;
                wins++;
            } else {
                cout << "Computer wins!" << endl;
                losses++;
            }
        }

        cout << "Total Wins: " << wins << endl;
        cout << "Total Losses: " << losses << endl;
        cout << "Total Ties: " << ties << endl;

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "THANKS FOR PLAYING!!!" << endl;
}


// Snake Game
void snake_game()
{
    const int width = 20, height = 20;
    int x, y, fruitX, fruitY, score, tailX[100], tailY[100], nTail;
    bool gameOver;
    char direction;
    char playAgain;

    do {
        // Initialize game variables
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        nTail = 0;
        gameOver = false;
        direction = ' ';

        while (!gameOver)
        {
            if (_kbhit())
            {
                switch (_getch())
                {
                case 'a':
                    direction = 'L';
                    break;
                case 'd':
                    direction = 'R';
                    break;
                case 'w':
                    direction = 'U';
                    break;
                case 's':
                    direction = 'D';
                    break;
                case 'x':
                    gameOver = true;
                    break;
                }
            }

            // Save current position
            int prevX = tailX[0];
            int prevY = tailY[0];
            tailX[0] = x;
            tailY[0] = y;

            for (int i = 1; i < nTail; i++)
            {
                int tempX = tailX[i];
                int tempY = tailY[i];
                tailX[i] = prevX;
                tailY[i] = prevY;
                prevX = tempX;
                prevY = tempY;
            }

            // Move snake
            switch (direction)
            {
            case 'L':
                x--;
                break;
            case 'R':
                x++;
                break;
            case 'U':
                y--;
                break;
            case 'D':
                y++;
                break;
            }

            // Collision with walls
            if (x >= width) x = 0;
            else if (x < 0) x = width - 1;
            if (y >= height) y = 0;
            else if (y < 0) y = height - 1;

            // Collision with fruit
            if (x == fruitX && y == fruitY)
            {
                score++;
                fruitX = rand() % width;
                fruitY = rand() % height;
                nTail++;
            }

            // Collision with self
            for (int i = 0; i < nTail; i++)
            {
                if (tailX[i] == x && tailY[i] == y)
                {
                    gameOver = true;
                }
            }

            // Draw
            system("cls");
            for (int i = 0; i < width + 2; i++)
                cout << "#";
            cout << endl;

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (j == 0)
                        cout << "#";
                    if (i == y && j == x)
                        cout << "O"; // Snake head
                    else if (i == fruitY && j == fruitX)
                        cout << "F"; // Fruit
                    else
                    {
                        bool print = false;
                        for (int k = 0; k < nTail; k++)
                        {
                            if (tailX[k] == j && tailY[k] == i)
                            {
                                cout << "o"; // Snake tail
                                print = true;
                            }
                        }
                        if (!print)
                            cout << " ";
                    }
                    if (j == width - 1)
                        cout << "#";
                }
                cout << endl;
            }

            for (int i = 0; i < width + 2; i++)
                cout << "#";
            cout << endl;

            cout << "Score: " << score << endl;
            Sleep(100); // Sleep for a short duration
        }

        // Game over - ask if the player wants to play again
        cout << "Game Over! Your score: " << score << endl;
        cout << "Do you want to play again? (y/n): ";
      //  char playAgain;
        cin >> playAgain;

 } while (playAgain == 'y' || playAgain == 'Y');
}
