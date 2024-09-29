from usb import *
import os

class Cryptage:

	def __init__(self):
		self.key = "clef"

	def gen_Key(self,password):
		command = f'echo -n "{password}" | sha256sum'
		key_hex = os.popen(command).read().strip().split(' ')[0]
		return key_hex

	def crypt(self, message, key):
		os.system("touch crypted_password.txt")
		os.system(f'echo -n "{message}" | openssl enc -aes-256-ecb -K {key} -nosalt -out crypted_password.txt > /dev/null 2>&1')
		result = readUsb("crypted_password.txt")
		os.system("rm crypted_password.txt")
		return result

	def decryptUsb(self,mdpA,mdpB,usbA,usbB):
		mdpAHex = self.gen_Key(mdpA)
		mdpBHex =  self.gen_Key(mdpB)
		mdpACryptB = self.crypt(mdpAHex,mdpBHex)
		mdpBCryptA = self.crypt(mdpBHex,mdpAHex)
		if(mdpACryptB == None or mdpBCryptA == None):
			return False
		usbACrypt = readUsb(usbA)[0] 	
		usbBCrypt = readUsb(usbB)[0] 
		if(usbACrypt == None or usbBCrypt == None):
			return False
		mdpACryptB = mdpACryptB[0]
		mdpBCryptA = mdpBCryptA[0]
		if(usbBCrypt == mdpBCryptA and usbACrypt == mdpACryptB):
			return True
		else:
			return False

	def cryptUsb(self,mdpA,mdpB,usbA,usbB):
		mdpAHex = self.gen_Key(mdpA)
		mdpBHex =  self.gen_Key(mdpB)
		mdpACryptB = self.crypt(mdpAHex,mdpBHex)
		mdpBCryptA = self.crypt(mdpBHex,mdpAHex)
		if(mdpACryptB == None or mdpBCryptA == None):
			return False
		writeUsb(usbA,mdpACryptB[0])
		writeUsb(usbB,mdpBCryptA[0])
		return True