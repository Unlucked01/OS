#!/bin/sh

if [ $# -lt 2 ]
	then
	echo "Некорректно переданны аргументы"
	echo 'Пример ввода: ./task3.sh <out_файл> <error_файл>'
	exit 1
fi

output_file="$1_out_$$"
error_file="$2_err_$$"

echo 'Выберите пункт меню\nОперация 1.\nОперация 2.'
read -p "Ввод: "

case $REPLY in
    1)
        find ~ -type f -mtime 2 1> ../out/"$output_file" 2> ../out/"$error_file"
	echo 'Завершено успешно! Результат находится в папке ../out/'
	cd ../out/
	;;
    2)
        read -p "Введите имя пользователя: "
	ps -U $REPLY -e -o="pid %cpu %mem" > ../out/"$output_file.$(id -u $REPLY)"
	echo 'Завершено успешно!\nРезультат находится в папке ../out/'
	cd ../out/
	;;
    *)
        echo "Неверный ввод" > "$output_file" 2> "$error_file"
        ;;
esac

