def readUsb(Filename : str):
	with open(Filename, "rb") as file:
		content = file.readlines()
	file.close()
	return content

def writeUsb(Filename : str, Data):
	file = open(Filename, "wb")
	file.write(Data)
	file.close()