class Reader:
 
    ###
    # Constructeur de la classe contient :
    def __init__(self) :
        self.file = 0
        self.line = " "
        self.height = 0
        self.width = 0
        self.nbOfPoints = 0 
        self.listsOfPoints = []   
        
    ###
    # Permet de lire et fermer un fichier en gardant toutes les données dans l'objet Reader qui l'appelle
    def readFile(self,path) :
        self.file = open(path,'r+')
        # Lecture des tailles du rectangle
        self.line = self.file.readline()
        self.width = int(self.line.split(' ')[0])
        self.height = int(self.line.split(' ')[1])
        #t Lecture du nombre de point
        self.nbOfPoints = int(self.file.readline()) 
        #Lecture des tuples de points
        self.line = self.file.readline()
        while (self.line != "" and self.line != "\0" and self.line != "\n"):
            l = self.line.split(' ')[0]
            h = self.line.split(' ')[1]
            h.replace("\n", "")
            self.listsOfPoints.append((int(l),int(h)))   
            self.line = self.file.readline()
        print("Info\n--------------")
        # print("List of points : ",self.listsOfPoints)
        print("Path : ",path)
        print("Width : ",self.width)
        print("Heigth : ",self.height)
        print("Nb of points : ",self.nbOfPoints)
        self.file.close()
        print("--------------")
        return
    
    def getSize(self):
        return self.nbOfPoints
        
