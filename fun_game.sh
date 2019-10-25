#!/bin/bash

echo -ne " =========================================== \n"

echo -ne " Welcome to the mystical world of Glorp! \n "

echo -ne "=========================================== \n"

echo -ne '\n'

choice_1=
while [ -z $choice_1 ]
do
  echo -n 'you see stairs that lead up and stairs that lead down, where would you like to go (u/d): '
  read choice_1
done

echo -ne '\n'

if [ $choice_1 == 'u' ]
then
  echo -ne 'You are dead \n'

elif [ $choice_1 == 'd' ]
then
  echo -ne 'ur dead, lol \n'

else
  echo -ne 'That was not an option \n'
fi
