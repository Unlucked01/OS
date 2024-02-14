#!/bin/sh

echo 'ввод: ./task2.sh'

active_users=$(who | wc -l)

if [ "$active_users" -gt 10 ]
then
    echo "Количество активных пользователей > 10."
else
    echo 'Количество активных пользователей = ' $active_users
fi

