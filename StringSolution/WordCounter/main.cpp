// Написать программу, которая считывает со стандартного входного потока
// заданное слово и набор предложений, разделителями которых являются точка,
// восклицательный знак и вопросительный знак. Необходимо для этого слова
// посчитать среднее арифметическое его вхождений в предложения (без учёта
// регистра). Слова в предложениях разделяются символами, для которых
// библиотечные функции isspace() или ispunct() возвращают ненулевое значение.

#include <iostream>
#include <cstdio>
#include <string>
#include <limits>
#include <set>
#include <clocale>

using std::cin;
using std::cout;
using std::endl;

bool isending(std::string::value_type const ch)
{
    static std::string::value_type prev_ch = '\0';
    std::set<char> available_endings = {'.', '!', '?', '\n'};
    auto out_of_available_endings = available_endings.end();
    auto current_char_is_not_endind = available_endings.find(ch) != out_of_available_endings;
    auto ending_is_not_repeated = available_endings.find(prev_ch) == out_of_available_endings;
    prev_ch = ch;
    return current_char_is_not_endind && ending_is_not_repeated;
}

std::string input_word_to_search()
{
    std::string word;
    cout << "Word to search: ";
    std::cin >> word;
    // отбрасываем входной поток до конца строки, что эквивалентно очистке буфера cin
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return word;
}

std::string input_text()
{
    std::string text;
    cout << "Input text: ";
    getline(cin, text);
    text += '.';
    return text;
}

int main()
{
    // https://en.cppreference.com/w/cpp/locale/setlocale
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string word_to_search = input_word_to_search();
    std::string sentences = input_text();

    auto count_sentences {0};
    auto count_target_word {0};
    std::string current_word = "";
    for (auto ch: sentences)
    {
        if (isending(ch) && !current_word.empty())
            ++count_sentences;
        if (isending(ch) || isspace(ch) || ispunct(ch))
        {
            if (current_word == word_to_search)
                ++count_target_word;
            current_word.erase();
        }
        else
        {
            current_word += ch;
        }
    }
    // посчитать и вывести среднее арифметическое вхождений word_to_search в предложения
    cout << static_cast<double>(count_target_word) / count_sentences;
}
