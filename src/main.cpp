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
            bool tie{true};
            std::println(R"( {} | {} | {}
---+---+---
 {} | {} | {}
---+---+---
 {} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);


            for (int i = 0; i < 9; i++){
                /* мусорное значение*/
                char current_player = '.';
                /* проверка на текущего пользователя*/
                if (i % 2 == 0){
                    current_player = 'X';
                }
                else {
                    current_player = 'O';
                }
                /* базовый алгоритм */
                int p;
                do {
                    std::print("Player {}: ", current_player);
                    std::cin >> p;
                }while (p < 1 || p > 9 || v[p - 1] != '.');
                v[p - 1] = current_player;

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
                    tie = false;
                    std::println("Player {} won", current_player);
                    std::println(R"( {} | {} | {}
---+---+---
 {} | {} | {}
---+---+---
 {} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
                        break;
                    }
                    if (i != 8){
                        std::println(R"( {} | {} | {}
---+---+---
 {} | {} | {}
---+---+---
 {} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
                    }
                }
            /*Если в результате игры не нашлось победителя - вывожу ничью и доску*/
            if (tie == true){
            std::println("Tie");
            std::println(R"( {} | {} | {}
---+---+---
 {} | {} | {}
---+---+---
 {} | {} | {})",
            v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]);
            }
}