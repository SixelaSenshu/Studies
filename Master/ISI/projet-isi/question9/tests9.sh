#!/bin/bash

make
sudo chown administrateur 
sudo chmod u+s pwg_c
sudo chmod o-w pwg_c
sudo chmod g-w pwg_c
sudo chmod u+s rmg_crypt_c
sudo chmod o-w rmg_crypt_c
sudo chmod g-w rmg_crypt_c

sudo su user_a

touch /home/ubuntu/dir_a/file_a_to_erase
./rmg_crypt_c /home/ubuntu/dir_a/file_a_to_erase
touch /home/ubuntu/dir_a/file_a_to_erase

sudo su_user_b

./rmg_crypt_c /home/ubuntu/dir_a/file_a_to_erase


./pwg_c "mon_nouveau_mdp"




