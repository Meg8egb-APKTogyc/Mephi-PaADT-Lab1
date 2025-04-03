#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Использование: $0 <программа> <входной_файл> <выходной_файл>"
    exit 1
fi

program_file=$1
input_file=$2
output_file=$3

gcc -o program "$program_file" DynamicArray.c input.c VTables.c ErrorHandler.c


if [ $? -eq 0 ]; then
    echo "Компиляция прошла успешно."
else
    echo "Ошибка компиляции."
    exit 1
fi

./program < "$input_file" > "$output_file"

if [ $? -eq 0 ]; then
    echo "Программа выполнена успешно. Результат записан в $output_file."
else
    echo "Ошибка выполнения программы."
    exit 1
fi