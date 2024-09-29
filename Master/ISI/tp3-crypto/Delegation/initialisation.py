from cryptage import *
from usb import *
import os

def initialisation():
	cryptage = Cryptage()
	usbA = "./tools/usbA.enc"
	usbB = "./tools/usbB.enc"
	usbC = "./tools/usbC.enc"
	usbD = "./tools/usbD.enc"
	print("Le mot de passe doit être dans les caractères suivant : [A-Z0-9] et de taille 64 maximum")
	print("Entrez le mot de passe A")
	mdpA = input()
	print("Entrez le mot de passe B")
	mdpB = input()
	print("Entrez le mot de passe C")
	mdpC = input()
	print("Entrez le mot de passe D")
	mdpD = input()
	if(mdpA == mdpB or mdpA == mdpC or mdpA == mdpD or mdpB == mdpC or mdpB == mdpD or mdpC == mdpD):
		print("Des mots de passe ne peuvent pas être identiques")
	else:
		cryptage.cryptAllUsb(mdpA, mdpB, mdpC, mdpD, usbA, usbB, usbC, usbD)
	return True

def main():
	initialisation()
	return 0

if __name__ == "__main__":
	main()