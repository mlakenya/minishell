# minishell
My ecole 42 project


Этапы парсинга:
1) Инициировать сигналы
2) Вывести minishell>
3) Получить ждать ввода строки через get_next_line(в это время сигналы будут обрабатываться заданными функциями)
4) Удалить лишние пробелы
5) Разбить строку на токены по пробелам
  5.1) Взять кусок до следующего пробела
  5.2) Определить его тип (аргумент, команда, пайп и тд.)
6) squish_args
7) вернуть первый токен
