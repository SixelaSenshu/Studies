#!/bin/bash

USER=/home/ubuntu
PATH=/home/

# Creation des utilisateur et des groupes & ajouts des groupes aux utilisateurs
sudo adduser administrateur
sudo adduser user_a
sudo adduser user_b
sudo adduser user_b2
sudo adduser user_a2

sudo addgroup groupe_a
sudo addgroup groupe_b

sudo adduser user_a groupe_a
sudo adduser user_b groupe_b
sudo adduser user_b2 groupe_b
sudo adduser user_a2 groupe_a
sudo adduser administrateur groupe_a
sudo adduser administrateur groupe_b

sudo adduser user_a ubuntu
sudo adduser user_b ubuntu
sudo adduser user_b2 ubuntu
sudo adduser user_a2 ubuntu     
sudo adduser administrateur ubuntu

# Creation des dossiers et association des dossiers aux groupes et au utilisateurs

sudo mkdir $PATH/dir_a
sudo mkdir $PATH/dir_b
sudo mkdir $PATH/dir_c

sudo chown administrateur $PATH/dir_a
sudo chown administrateur $PATH/dir_b
sudo chown administrateur $PATH/dir_c
sudo chown administrateur:groupe_a $PATH/dir_a
sudo chown administrateur:groupe_b $PATH/dir_b
sudo chown administrateur:administrateur $PATH/dir_c

sudo chmod g+s $PATH/dir_a
sudo chmod g+s $PATH/dir_b

# Modification des droits dir_a
sudo chmod +t $PATH/dir_a

sudo chmod u+r $PATH/dir_a
sudo chmod u+w $PATH/dir_a
sudo chmod u+x $PATH/dir_a

sudo chmod g+r $PATH/dir_a
sudo chmod g+w $PATH/dir_a
sudo chmod g+x $PATH/dir_a

sudo chmod o-r $PATH/dir_a
sudo chmod o-w $PATH/dir_a
sudo chmod o-x $PATH/dir_a

# Modification des droits dir_b
sudo chmod +t $PATH/dir_b

sudo chmod u+r $PATH/dir_b
sudo chmod u+w $PATH/dir_b
sudo chmod u+x $PATH/dir_b

sudo chmod g+r $PATH/dir_b
sudo chmod g+w $PATH/dir_b
sudo chmod g+x $PATH/dir_b

sudo chmod o-r $PATH/dir_b
sudo chmod o-w $PATH/dir_b
sudo chmod o-x $PATH/dir_b

# Modification des droits dir_c
sudo chmod +t $PATH/dir_c

sudo chmod u+r $PATH/dir_c
sudo chmod u+w $PATH/dir_c
sudo chmod u+x $PATH/dir_c

sudo chmod g+r $PATH/dir_c
sudo chmod g-w $PATH/dir_c
sudo chmod g-x $PATH/dir_c

sudo chmod o+r $PATH/dir_c
sudo chmod o-w $PATH/dir_c
sudo chmod o-x $PATH/dir_c

