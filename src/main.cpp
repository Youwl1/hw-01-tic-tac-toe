#include <iostream>
#include <print>
#include <string>
#include <vector>

int main() {


            const std::vector<std::vector<int>> wins = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8},
            {2, 4, 6}
        };
        /*вывел начальную доску*/
            std::vector<char> v(9,'.');
            bool tie1{true};
            std::println(R"({} | {} | {}
---+---+---
{} | {} | {}
---+---+---
{} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);


            for (int i = 0; i < 9; i++){
                /* Если ходит player X*/
                if (i % 2 == 0){
                    char current_player = 'X';
                    int p;
                    do {
                        std::cout << "Player X: ";
                        std::cin >> p;
                    }while (p < 1 or p > 9 or v[p - 1] != '.');
                    v[p - 1] = 'X';

                    /* проверка на выигрышную позицию*/
                    bool win {false};
                    for(const auto& line : wins){
                        if((v[line[0]] == current_player) && (v[line[1]] == current_player) && (v[line[2]] == current_player)){
                            win = true;
                            break;
                        }
                    }
                    
                    /* если выиграл - вывожу кто и доску*/
                    if(win){
                        tie1 = false;
                        std::println("Player {} won", current_player);
                        std::println(R"( {} | {} | {}
---+---+---
{} | {} | {}
---+---+---
{} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
                        break;
                    }
                    std::println(R"( {} | {} | {}
---+---+---
{} | {} | {}
---+---+---
{} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
                    }
                else {  /*ЭТО ИГРОК "O"*/


                    int p1;
                    char current_player = 'O';
                    do {
                        std::cout << "Player O: ";
                        std::cin >> p1;
                    }while (p1 < 1 or p1 > 9 or v[p1 - 1] != '.');
                    v[p1 - 1] = 'O';

                    bool win {false};
                    for(const auto& line : wins){
                        if((v[line[0]] == current_player) && (v[line[1]] == current_player) && (v[line[2]] == current_player)){
                            win = true;
                            break;
                        }
                    }

                    if (win) {
                        tie1 = false;
                        std::println("Player {} won", current_player);
                        std::println(R"( {} | {} | {}
---+---+---
{} | {} | {}
---+---+---
{} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
                        break;
                    }
                std::println(R"( {} | {} | {}
---+---+---
{} | {} | {}
---+---+---
{} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);       
                }
            }
            if (tie1 == true){
            std::println("Tie");
            std::println(R"( {} | {} | {}
---+---+---
{} | {} | {}
---+---+---
{} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
            }

}