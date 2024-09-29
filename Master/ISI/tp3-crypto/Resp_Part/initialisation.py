from cryptage import *
from usb import *
import os

def initialisation():
	cryptage = Cryptage()
	usbA = "./tools/usbA.enc"
	usbB = "./tools/usbB.enc"
	print("Le mot de passe doit être dans les caractères suivant : [A-Z0-9] et de taille 64 maximum")
	print("Entrez le mot de passe A")
	mdpA = input()
	print("Entrez le mot de passe B")
	mdpB = input()
	cryptage.cryptUsb(mdpA,mdpB,usbA,usbB)
	return True

def main():
	initialisation()
	return 0

if __name__ == "__main__":
	main()