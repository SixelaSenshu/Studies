import os
import subprocess
from usb import *
from cryptage import *

def main():
    cryptage = Cryptage()
    usbA = "./tools/usbA.enc"
    usbB = "./tools/usbB.enc"
    print("Entrez le mot de passe A")
    mdpA = input()
    print("Entrez le mot de passe B")
    mdpB = input()
    result = cryptage.decryptUsb(mdpA, mdpB, usbA, usbB)
    end = False
    isOn = False
    filename = "data/data.txt"
    if result == True:
        key = cryptage.gen_Key(mdpA)
        print("Les mots de passe sont les valides")
        while not end:
            print("--------------------------")
            print("Option :")
            print("Turn on (T)")
            print("Find (F)")
            print("Delete (D)")
            print("Add (A)")
            print("Exit (E)")
            print("Show (S)")
            choice = input() 
            if choice == "T":
                print("1 : Serveur actif")
                print("0 : Serveur inactif")
                choice = input()   
                isOn = turnOn(choice)
            elif choice == "E":
                end = True
            else:
                if isOn == False:
                    print("Le serveur est inactif")
                else:
                    if choice == "F":
                        print("Entrez le nom")
                        choice = input()
                        findInFile(choice, key, filename)
                    elif choice == "D":
                        print("Entrez le nom")
                        choice = input()
                        print("Entrez le n° de carte")
                        num_card = input()
                        delInFile(choice, num_card, filename, key)
                    elif choice == "A":
                        print("Entrez le nom")
                        choice = input()
                        print("Entrez le n° de carte")
                        num_card = input()
                        addInFile(choice, num_card, filename, key)
                    elif choice == "S":
                        showFiles(filename, key)

###
# Met en route le serveur 
def turnOn(choice):
    if choice == "1":
        print("Serveur actif")
        return True
    else:
        print("Serveur inactif")
        return False

###
# Ajoute une entrée dans le fichier
def addInFile(nameChoice, num_card, filedata, key):
    content = nameChoice + " " + num_card
    data = cryptContent(filedata, content, key)

###
# Crypte le contenu du fichier
def cryptContent(filedata, data, key):
	filedata = open(filedata, "ab")
	os.system("touch crypted_password.txt")
	os.system(f'echo -n "{data}" | openssl enc -aes-256-ecb -K {key} -nosalt -out crypted_password.txt > /dev/null 2>&1')
	result = readUsb("crypted_password.txt")
	os.system("rm crypted_password.txt")
	if(result.__len__() > 0):
		filedata.write(result[0])
		filedata.write(b"[END]")
	filedata.close()

def findInFile(nameChoiced, key, filename):
    content = decryptContent(filename, key)
    nameChoiced = nameChoiced.encode()
    for i in range(len(content)):
        name = content[i].split(b" ")[0]
        if name == nameChoiced:
            print(content[i])

def showFiles(filedata, key):
    content = decryptContent(filedata, key)
    for i in range(len(content)):
        if content[i].__len__():
            print(content[i])

def delInFile(nameChoice, num_card, filedata, key):
	res = (nameChoice + " " + num_card).encode()
	content = decryptContent(filedata, key)
	for i in range(len(content)):	
		if content[i] == res:
			content.pop(i)
	filed = open(filedata, "w")
	filed.write("")
	filed.close()
	for i in range(len(content)):
	    cryptContent(filedata, content[i].decode(), key)

def decryptContent(filedata, key):
    result = []
    content = open(filedata, "rb").read()
    contents = content.split(b"[END]")
    for data in contents:
        if data.strip():
            decrypt_process = subprocess.Popen(['openssl', 'enc', '-aes-256-ecb', '-d', '-K', key, '-nosalt'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            decrypted_data, stderr = decrypt_process.communicate(input=data)
            result.append(decrypted_data)
    return result


if __name__ == "__main__":
    main()
