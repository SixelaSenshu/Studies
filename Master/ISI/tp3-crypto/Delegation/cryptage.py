from usb import *
import os
import subprocess
import secrets
import string

class Cryptage:

	def __init__(self):
		self.key = "clef"

	def gen_random_key(self,longueur):
		caracteres = string.ascii_letters + string.digits
		return ''.join(secrets.choice(caracteres) for _ in range(longueur))

	def gen_Key(self,password):
		command = f'echo -n "{password}" | sha256sum'
		key_hex = os.popen(command).read().strip().split(' ')[0]
		return key_hex

	def crypt(self, message, key):
		os.system("touch ram.txt")
		os.system(f'echo -n "{message}" | openssl enc -aes-256-ecb -K {key} -nosalt -out ram.txt > /dev/null 2>&1')
		result = readUsb("ram.txt")
		os.system("rm ram.txt")
		return result

	def decrypt(self, message, key):
		decrypt_process = subprocess.Popen(['openssl', 'enc', '-aes-256-ecb', '-d', '-K', key, '-nosalt'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		decrypted_data, stderr = decrypt_process.communicate(input=message)
		return decrypted_data

	def decryptUsb(self,mdpA,mdpB,usbA,usbB):
		mdpAHex = self.gen_Key(mdpA)
		mdpBHex =  self.gen_Key(mdpB)
		usbACrypt = readUsb(usbA)[0] 	
		usbBCrypt = readUsb(usbB)[0]
		if(usbACrypt == None or usbBCrypt == None):
			return False
		decrypted_dataA = self.decrypt(usbACrypt,mdpAHex)
		decrypted_dataB = self.decrypt(usbBCrypt,mdpBHex)
		if(decrypted_dataA and decrypted_dataB):
			#decryptage des deux clés dépendantes
			decrypted_commonA = self.decrypt(decrypted_dataA,decrypted_dataB)
			decrypted_commonB = self.decrypt(decrypted_dataB,decrypted_dataA)
			print(decrypted_commonA)
			print(decrypted_commonB)
			if(decrypted_commonA == decrypted_commonB):
				return True
		return False

	def get_key(self,mdpA,mdpB,usbA,usbB):
		mdpAHex = self.gen_Key(mdpA)
		mdpBHex =  self.gen_Key(mdpB)
		usbACrypt = readUsb(usbA)[0] 	
		usbBCrypt = readUsb(usbB)[0]
		if(usbACrypt == None or usbBCrypt == None):
			return False
		decrypted_dataA = self.decrypt(usbACrypt,mdpAHex)
		decrypted_dataB = self.decrypt(usbBCrypt,mdpBHex)
		if(decrypted_dataA and decrypted_dataB):
			#decryptage des deux clés dépendantes
			decrypted_commonA = self.decrypt(decrypted_dataA,decrypted_dataB)
			decrypted_commonB = self.decrypt(decrypted_dataB,decrypted_dataA)
			if(decrypted_commonA == decrypted_commonB):
				return decrypted_commonA
		return None

	def cryptAllUsb(self,mdpA, mdpB, mdpC, mdpD, usbA, usbB, usbC, usbD):
		mdpAHex = self.gen_Key(mdpA)
		mdpBHex =  self.gen_Key(mdpB)
		mdpCHex = self.gen_Key(mdpC)
		mdpDHex =  self.gen_Key(mdpD)
		command_commonKey = f'echo -n "{self.gen_random_key(64)}" | sha256sum'
		commonKey = os.popen(command_commonKey).read().strip()
		command_newKey = f'echo -n "{self.gen_random_key(64)}" | sha256sum'
		newKey = os.popen(command_newKey).read().strip()
		command_newKey2 = f'echo -n "{self.gen_random_key(64)}" | sha256sum'
		newKey2 = os.popen(command_newKey2).read().strip()
		commonkey1 = self.crypt(newKey2, newKey)
		commonkey2 = self.crypt(newKey, newKey2)
		keyRes1 = self.crypt(commonKey, commonkey1)
		keyRes2 = self.crypt(commonKey, commonkey2)
		mdpACryptB = self.crypt(keyRes1,mdpAHex)
		mdpBCryptA = self.crypt(keyRes2,mdpBHex)
		mdpCCryptD = self.crypt(keyRes1,mdpDHex)
		mdpDCryptC = self.crypt(keyRes2,mdpCHex)
		if(mdpACryptB == None or mdpBCryptA == None or mdpCCryptD == None or mdpDCryptC == None):
			return False
		writeUsb(usbA,mdpACryptB[0])
		writeUsb(usbB,mdpBCryptA[0])
		writeUsb(usbC,mdpCCryptD[0])
		writeUsb(usbD,mdpDCryptC[0])
		return True