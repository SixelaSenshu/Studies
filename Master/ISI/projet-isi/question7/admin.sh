#!/bin/bash
sudo su administrateur

USER=administrateur
DIR_A=/home/$USER/dir_a
FILE_A=$DIR_A/file_a.txt
FILE_A2=$DIR_A/file2_a.txt
DIR_B=/home/$USER/dir_b
FILE_B=$DIR_B/file_b.txt
FILE_B2=$DIR_B/file_b2.txt
DIR_C=/home/$USER/dir_c
FILE_C=$DIR_C/file_c.txt

sudo su user_a

touch $FILE_A

sudo su user_b

touch $FILE_B

sudo su administrateur

ls * -l

cat $FILE_A
cat $FILE_B

mv $FILE_A 
mv $FILE_B 
rm $FILE_A
rm $FILE_B
