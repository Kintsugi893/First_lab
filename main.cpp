#include <iostream
#include <cstdlib>
#include <ctime>)
#include <limits>
#include <string>

// Функция сдачи: выводит секретное число и завершает раунд
void сдаться(int secret) {
    std::cout << "Вы сдались. Загаданное число было: " << secret << std::endl;
}

int main() {
    std::setlocale(LC_ALL, "RUS");
    bool playAgain = true;

    while (playAgain) {
        int min, max, attempts;

        // Ввод минимального значения с проверкой
        do {
            std::cout << "Введите минимальное число (от 0): ";
            std::cin >> min;
            if (std::cin.fail() || min < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: Введите число ≥0.\n";
                min = -1;
            }
        } while (min < 0);

        // Ввод максимального значения с проверкой
        do {
            std::cout << "Введите максимальное число: ";
            std::cin >> max;
            if (std::cin.fail() || max < min) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: Введите число > " << min << ".\n";
                max = min - 1;
            }
        } while (max < min);

        // Ввод попыток с проверкой
        do {
            std::cout << "Количество попыток: ";
            std::cin >> attempts;
            if (std::cin.fail() || attempts < 1) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: Введите число ≥1.\n";
                attempts = 0;
            }
        } while (attempts < 1);
        std::cout << std::endl;

        std::srand(std::time(0)); // Инициализация генератора
        int secretNumber = min + std::rand() % (max - min + 1); // Генерация числа

        std::cout << "Угадайте число между " << min << " и " << max << std::endl;

        bool guessed = false;
        while (attempts > 0) {
            std::string input;
            int guess;

            // Ввод варианта с проверкой
            do {
                std::cout << "Осталось попыток: " << attempts << std::endl;
                std::cout << "Ваш вариант (введите 'сдаться' для сдачи): ";
                std::cin >> input;

                if (input == "сдаться") {
                    сдаться(secretNumber);
                    guessed = true;
                    break;
                }

                try {
                    guess = std::stoi(input);
                } catch (...) {
                    std::cout << "Ошибка: Введите число или 'сдаться'.\n";
                    continue;
                }

                if (guess < min || guess > max) {
                    std::cout << "Ошибка: Число вне диапазона [" << min << "; " << max << "].\n";
                    continue;
                }

                break;
            } while (true);

            if (guessed) break;

            if (guess == secretNumber) {
                std::cout << "Поздравляю! Вы угадали число!\n";
                guessed = true;
                break;
            }

            attempts--;
        }

        if (!guessed && attempts == 0) {
            std::cout << "Вы проиграли. Загаданное число: " << secretNumber << std::endl;
        }

        // Предложение сыграть еще раз
        char choice;
        do {
            std::cout << "\nХотите сыграть еще раз? (y/n): ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: Введите 'y' или 'n'.\n";
            }
        } while (choice != 'y' && choice != 'n');

        playAgain = (choice == 'y');
        std::cout << std::endl;
    }

    return 0;
}
