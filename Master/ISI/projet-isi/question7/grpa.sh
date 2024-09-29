#!/bin/bash
# r = read , w = write , m = rename , c = create , e = erase
sudo su user_a

USER=ubuntu
DIR_A=/home/$USER/dir_a
FILE_A=$DIR_A/file_a.txt
FILE_A2=$DIR_A/file_a2.txt
DIR_B=/home/$USER/dir_b
FILE_B=$DIR_B/file_b.txt
DIR_C=/home/$USER/dir_c
FILE_C=$DIR_C/file_c.txt
# Can

sudo su user_a

ls * -l

touch $FILE_A
cat $FILE_A
open $FILE_A
mv $FILE_A $FILE_A2
touch $FILE_A

sudo su user_a2
rm $FILE_A
cat $FILE_A
open $FILE_A2

sudo su administrateur
touch $FILE_C

sudo su user_a2
ls $DIR_C
cat $FILE_C
open $FILE_C
rm $FILE_C




