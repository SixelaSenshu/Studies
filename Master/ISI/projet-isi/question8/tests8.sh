#!/bin/bash

make
sudo chown administrateur 
sudo chmod u+s rmg_c
sudo chmod o-w rmg_c
sudo chmod g-w rmg_c

sudo chmod 700 /home/administrateur/passwd/password.txt
sudo chmod u+s rmg_c

sudo su user_a

touch /home/ubuntu/dir_a/file_a_to_erase
./rmg_c /home/ubuntu/dir_a/file_a_to_erase
touch /home/ubuntu/dir_a/file_a_to_erase

sudo su_user_b

./rmg_c /home/ubuntu/dir_a/file_a_to_erase





