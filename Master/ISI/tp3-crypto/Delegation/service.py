import os
import subprocess
from usb import *
from cryptage import *

def main():
	cryptage = Cryptage()
	print("Les clés sont A, B, C et D")
	print("Quels est la première clé usb")
	ChoiceUsb1 = input()
	print("Quels est la deuxième clé usb")
	ChoiceUsb2 = input()
	if(ChoiceUsb1 == ChoiceUsb2):
		print("Les clés usb doivent être différentes")
		return
	else:
		usbA = getPathUsb(ChoiceUsb1)
		usbB = getPathUsb(ChoiceUsb2)
	print("Entrez le mot de passe n°1")
	mdp1 = input()
	print("Entrez le mot de passe n°2")
	mdp2 = input()
	result = cryptage.decryptUsb(mdp1, mdp2, usbA, usbB)
	if result == True:
		print("Authentifié !")
		key = cryptage.get_key(mdp1, mdp2, usbA, usbB)
	end = False
	isOn = False
	filename = "./disk/data.txt"
	if result == True:
		print("Les mots de passe sont valides")
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

def getPathUsb(Choice_usb):
	if Choice_usb == "A":
		return "./tools/usbA.enc"
	elif Choice_usb == "B":
		return "./tools/usbB.enc"
	elif Choice_usb == "C":
		return "./tools/usbC.enc"
	elif Choice_usb == "D":
		return "./tools/usbD.enc"
	else:
		return "./tools/usbA.enc"

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
    filed = open("./disk/data.txt", "ab")
    os.system("touch ram.txt")
    os.system(f'echo -n "{data}" | openssl enc -aes-256-ecb -K {key} -nosalt -out ram.txt > /dev/null 2>&1')
    result = readUsb("ram.txt")
    os.system("rm ram.txt")
    if result.__len__() > 0:
        filed.write(result[0])
        filed.write(b"[END]")
    filed.close()

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
    remaining_content = [item for item in content if item != res]
    with open(filedata, "wb") as file:
        for item in remaining_content:
            cryptContent(file, item.decode(), key)

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
