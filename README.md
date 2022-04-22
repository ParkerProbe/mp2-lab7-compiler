# Лабораторная работа. Среда исполнения программ на языке Pascal--

## Цель

__Цель данной работы__ — разработать программную систему для компиляции и исполнения программы 
на языке программирования Pascal--.

Выполнение работы предполагает решение следующих задач:
1. Разработка интерфейса системы классов для лексического анализа текста на языке Pascal--.
2. Разработка интерфейса системы классов для cинтаксического анализа текста на языке Pascal--.
3. Разработка интерфейса системы классов для семантического анализа текста на языке Pascal--.
3. Разработка интерфейса системы классов для компиляции и исполнения кода на языке Pascal--.
4. Реализация методов каждой системы классов.
5. Разработка и реализация модульных тестов для классов.
5. Публикация исходных кодов в командном репозитории на GitHub.
6. Демонстрация результатов работы заказчику.


## Используемые инструменты
- Система контроля версий Git.
- Фреймворк для написания автоматических тестов Google Test.
- Среда разработки Microsoft Visual Studio.
- Утилита CMake для генерации проектов по сборке исходных кодов.

## Состав команды
- Бугров Андрей
- Колесников Денис
- Цветков Алексей

## Общая структура проекта

Структура проекта:

  - `gtest` — библиотека Google Test.
  - `base` — каталог с основным проектом ЛР.
  - `base_test` — каталог с проектом с модульными тестами.
  - `README.md` — информация о проекте.
  - `mp2-lab7-compiler.sln` - файл с решением (solution) для Microsoft Visual Studio.
  - Служебные файлы
    - `.gitignore` — перечень расширений файлов, игнорируемых Git при добавлении файлов в репозиторий.
    - ` CMakeLists.txt` — корневой файл для сборки проекта с помощью CMake.



## Требования к программной среде

1. Поддержка обработки синтаксиса и языковых конструкций языка Pascal--.
2. Поддержка контроля синтаксиса.
3. Хранение текста программы в иерархическом списке.
4. Хранение констант в таблице констант и переменных в таблице переменных (хеш-таблица).
5. Выполнение вычислений арифметических выражений с помощью постфиксной формы.



## Модели объектов и алгоритмы

### Лексический анализатор
Удаляет информацию из кода, которая не нужна во время разбора. Она включают в себя комментарии и пробелы в коде.
Лексический анализ выявляет в входных данных следующие лексемы: ключевые слова, имена переменных и констант, арифметические операции, операторы. Результатом работы является иерархический список.


### Синтаксический анализатор
Синтаксический анализ следит за соблюдением формальных правил языка программирования.
Проверяет, написана ли программа корректно, а затем определяет порядок выполнения команд. 


### Семантический анализатор
Семантический анализ представляет связи и семантические правила языка программирования.
Обрабатывает иерархический список, построенный синтаксическим анализатором. 
Анализатор определяет, обрабатываются ли операции в правильном порядке, и далее осуществляется анализ их типов и назначений.
Также осуществялется проверка, содержит ли данное условие действительные (сопоставимые) выражения, строятся таблица переменных и констант.

### Исполнитель кода
Имитирует исполнение построенного кода.


### Иерархический список
Представляет собой дерево. У каждого звена есть указатели на потомков (находятся на уровень ниже) и следующее звено (находится том же уровне). Корнем дерева является звено, содержащее весь текст программы. Атомарный уровень - уровень строк кода. 
* Алгоритм прохода по списку - алгоритм Top-Down-Next.

### Постфиксная форма
Для расчета арифметических операций используется постфиксная форма. Она реализуется при помощи стека.

* Алгоритм перевода инфиксной формы в постфиксную:
  1. Перебираем инфиксную запись слева направо.
  2. Если входящий элемент число, то он добавляется в постфикс. Если входящий элемент операция (+, -, *, /) то происходит проверка:
  3. Если стек операций пуст или содержит левую скобку в вершине, то входящий элемент добавляется в стек. 
  4. Если входящий элемент имеет более высокий приоритет чем вершина, он помещается в стек. 
  5. Если входящий элемент имеет более низкий или равный приоритет, чем вершина, стек выгружается в постфикс, пока не обнаружится элемент с меньшим приоритетом или левая скобка на вершине стека, затем входящий элемент добавляется в стек.
  6. Если входящий элемент является левой скобкой, он помещается в стек.
  7. Если входящий элемент является правой скобкой, стек выгружается в постфикс, до тех пор пока на вершине стека не окажется левая скобка, которая удаляется из стека.
  8. В конце инфиксной записи все элементы, оставшиеся в стеке, выгружаются в постфиксную запись.


### Хеш таблица
Структура данных, реализованная на таких структурах хранения, как список и массив. Положение элемента задаётся хэш-функцией. Для разрешения коллизий используется метод цепочек. Все записи, для которых функция хеширования определяет одно и то же значение, представляются в виде линейного списка.

* Алгоритмы:
  - Поиск. Вычисление индекса с помощью хеш-функции. Проход по списку, расположенному по индексу в таблице, до совпадения ключа.
  - Добавление. Вычисление индекса с помощью хеш-функции. Вставка в начало списка, расположенному по индексу в таблице.
  - Удаление. Вычисление индекса с помощью хеш-функции. Проход по списку, расположенному по индексу в таблице до совпадения ключа, удаление найденной записи.

  
### Интерфейс
Интерфейс, обеспечивающий передачу информации между пользователем-человеком и программно-аппаратными компонентами компьютерной системы. В программе представлен в виде консольного интерфейса и предоставляет доступ к пользовательским операциям модулей программной системы.
Служит для операций консольного ввода/вывода при непосредственной работе успешно скомпилированной программы.
