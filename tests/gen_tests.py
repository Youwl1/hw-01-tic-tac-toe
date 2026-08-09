import os
import random
import subprocess
# AI GENERATED FILE
# Путь к вашему скомпилированному авторскому решению
# Измените его, если путь отличается!
EXECUTABLE_PATH = "../build/hw-01-tic-tac-toe"
TESTS_DIR = "." # Папка, куда сохранять тесты

# Выигрышные комбинации (индексы 0-8)
WINS = [
    [0, 1, 2], [3, 4, 5], [6, 7, 8], # Горизонтали
    [0, 3, 6], [1, 4, 7], [2, 5, 8], # Вертикали
    [0, 4, 8], [2, 4, 6]             # Диагонали
]

def check_win(board, player):
    for line in WINS:
        if board[line[0]] == player and board[line[1]] == player and board[line[2]] == player:
            return True
    return False

def generate_game_sequence(add_errors=False):
    """
    Генерирует последовательность вводов для одной партии.
    Возвращает список чисел (вводов пользователя).
    """
    board = ['.'] * 9
    moves = []
    current_player = 'X'

    for _ in range(9):
        # Находим доступные ячейки (1-9)
        available = [i + 1 for i, cell in enumerate(board) if cell == '.']
        if not available:
            break

        # Имитация ошибок пользователя (если включено)
        if add_errors:
            # С вероятностью 50% добавляем 1-10 ошибочных ввода перед правильным
            if random.random() > 0.5:
                for _ in range(random.randint(1, 10)):
                    error_type = random.choice(['low', 'high', 'taken'])
                    if error_type == 'low':
                        moves.append(random.randint(-100, 0)) # < 1
                    elif error_type == 'high':
                        moves.append(random.randint(10, 100)) # > 9
                    elif error_type == 'taken':
                        # Пытаемся походить в уже занятую ячейку
                        taken = [i + 1 for i, cell in enumerate(board) if cell != '.']
                        if taken:
                            moves.append(random.choice(taken))

        # Выбираем случайный валидный ход
        move = random.choice(available)
        moves.append(move)
        board[move - 1] = current_player

        # Проверяем, не закончилась ли игра
        if check_win(board, current_player):
            break

        # Смена игрока
        current_player = 'O' if current_player == 'X' else 'X'

    return moves

def generate_specific_games():
    """Возвращает заранее заготовленные интересные случаи для первых тестов"""
    return [
        [1, 4, 2, 5, 3],                         # X выигрывает по горизонтали (быстро)
        [1, 2, 4, 5, 7],                         # X выигрывает по вертикали
        [5, 1, 2, 3, 7, 4, 6, 8, 9],             # Ничья
        [-1, 10, 0, 5, 5, 3, 3, 3, 1, 9, 6, 8, 4],     # Сложный ввод с кучей ошибок (как в вашем примере)
    ]

def main():
    if not os.path.isfile(EXECUTABLE_PATH):
        print(f"Ошибка: Исполняемый файл '{EXECUTABLE_PATH}' не найден!")
        print("Скомпилируйте проект перед запуском генератора.")
        return

    os.makedirs(TESTS_DIR, exist_ok=True)

    # Собираем список всех игр
    games = generate_specific_games()

    # Добавляем 6 рандомных игр (итого будет 10 тестов)
    # Половина из них будет с подмешанным невалидным вводом
    for i in range(500):
        games.append(generate_game_sequence(add_errors=(i % 2 == 0)))

    # Генерируем файлы .in и .testout
    for idx, game_moves in enumerate(games, 1):
        # Форматируем имя файла: 01.in, 02.in и т.д.
        test_name = f"{idx:03d}"
        in_file = os.path.join(TESTS_DIR, f"{test_name}.in")
        out_file = os.path.join(TESTS_DIR, f"{test_name}.testout")

        # 1. Записываем входные данные в .in файл
        input_data = "\n".join(map(str, game_moves)) + "\n"
        with open(in_file, 'w', encoding='utf-8') as f:
            f.write(input_data)

        # 2. Запускаем C++ программу и кормим ей этот ввод
        print(f"Генерация теста {test_name} (ходов: {len(game_moves)})...", end=" ")
        try:
            result = subprocess.run(
                [EXECUTABLE_PATH],
                input=input_data,
                text=True,           # Работаем со строками, а не байтами
                capture_output=True, # Перехватываем stdout и stderr
                timeout=2            # Защита от вечных циклов в C++ коде
            )

            # 3. Записываем результат работы C++ программы в .testout
            with open(out_file, 'w', encoding='utf-8') as f:
                f.write(result.stdout)

            print("OK")

        except subprocess.TimeoutExpired:
            print("ОШИБКА (Таймаут: программа зависла в вечном цикле)")
        except Exception as e:
            print(f"ОШИБКА ({e})")

    print("\nГенерация тестов успешно завершена!")

if __name__ == "__main__":
    main()
