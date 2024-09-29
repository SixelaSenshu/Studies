#!/bin/bash
# r = read , w = write , m = rename , c = create , e = erase

USER=ubuntu
DIR_A=/home/$USER/dir_a
FILE_A=$DIR_A/file_a.txt
DIR_B=/home/$USER/dir_b
FILE_B=$DIR_B/file_b.txt
FILE_B2=$DIR_B/file_b2.txt
DIR_C=/home/$USER/dir_c
FILE_C=$DIR_C/file_c.txt
# Can

sudo su user_b

ls * -l

touch $FILE_B
cat $FILE_B
open $FILE_B
mv $FILE_B $FILE_B2
touch $FILE_B

sudo su user_b2
rm $FILE_B
cat $FILE_B
open $FILE_B2

sudo su administrateur
touch $FILE_C

sudo su user_b2
ls $DIR_C
cat $FILE_C
open $FILE_C
rm $FILE_C




