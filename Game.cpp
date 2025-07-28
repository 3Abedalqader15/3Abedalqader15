#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;


void fillScreenWithColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;
    COORD coord = { 0, 0 };

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, color,
        csbi.dwSize.X * csbi.dwSize.Y, coord, &written);
    FillConsoleOutputCharacter(hConsole, ' ',
        csbi.dwSize.X * csbi.dwSize.Y, coord, &written);
    SetConsoleCursorPosition(hConsole, coord);
}


void ringBell() {
    Beep(1000, 300); 
}

int main() {
    srand(time(0));
    string choices[3] = { "stone", "Paper", "Scissors" };
    char playAgain;

    do {
        system("CLS");

        int totalRounds;
        cout << "How many rounds do you want to play? ";
        cin >> totalRounds;

        int userScore = 0, computerScore = 0;

        for (int round = 1; round <= totalRounds; round++) {
            system("CLS");

            cout << "Round " << round << " of " << totalRounds << endl;
            cout << "Choose:\n";
            cout << "0 - Rock\n1 - Paper\n2 - Scissors\n";
            int userChoice;
            cin >> userChoice;

            if (userChoice < 0 || userChoice > 2) {
                cout << "Invalid choice. Skipping round...\n";
                Sleep(1500);
                continue;
            }

            int computerChoice = rand() % 3;

            cout << "You chose: " << choices[userChoice] << endl;
            cout << "Computer chose: " << choices[computerChoice] << endl;

            
            if (userChoice == computerChoice) {
                fillScreenWithColor(BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_INTENSITY); 
                cout << "It's a tie!\n";
            }
            
            else if ((userChoice == 0 && computerChoice == 2) ||
                (userChoice == 1 && computerChoice == 0) ||
                (userChoice == 2 && computerChoice == 1)) {
                fillScreenWithColor(BACKGROUND_GREEN | FOREGROUND_INTENSITY); 
                cout << "You win this round!\n";
                userScore++;
            }
            
            else {
                fillScreenWithColor(BACKGROUND_RED | FOREGROUND_INTENSITY); 
                ringBell(); 
                cout << "Computer wins this round!\n";
                computerScore++;
            }

            Sleep(2000); 
            fillScreenWithColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
        }

        
        system("CLS");
        cout << "===== Game Over =====\n";
        cout << "Your Score: " << userScore << endl;
        cout << "Computer Score: " << computerScore << endl;

        if (userScore > computerScore)
            cout << " You are the overall winner!\n";
        else if (computerScore > userScore)
            cout << " Computer wins overall!\n";
        else
            cout << " It's an overall tie!\n";

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
