import os
import sys

print("gid , uid, egid, euid")
print(os.getgid() , os.getuid() , os.getegid(), os.getegid())

if sys.argv[1] == None:
    print("Veuillez spécifier un fichier")
    sys.exit()
print(sys.argv[1])
fichier = open(sys.argv[1],'r')
if(fichier != None):
    print("Ouverture du fichier réussie")
    fichier.close()
else:
    print("Ouverture du fichier échouée")


