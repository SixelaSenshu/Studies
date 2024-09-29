class Reader:

    # Initialise la class reader
    # self -> La nouvelle instance
    # path_file -> Le chemin du fichier à parser
    def __init__(self, path_file, width, height, string):
        if (path_file != ""):
            file = open(path_file)
            self.width = int(file.readline())
            self.heigth = int(file.readline())
            self.board = []
            self.string = ""
            line = file.readline()
            ind = 0
            while line != "" and line != "\n":
                self.board.append([])
                for i in range(0, len(line)-1):
                    if (line[i] == "p"):
                        self.board[ind].append(0)
                    elif (line[i] == "P"):
                        self.board[ind].append(1)
                    else:
                        self.board[ind].append(-1)
                    self.string += line[i]
                ind += 1
                line = file.readline()
        else:
            self.width = width
            self.heigth = height
            self.board = []
            self.string = ""
            pos = -1
            for i in range(0, width):
                self.board.append([])
                for j in range(0, height):
                    pos += 1
                    if (string[pos] == "p"):
                        self.board[i].append(0)
                        self.string += "p"
                    elif (string[pos] == "P"):
                        self.board[i].append(1)
                        self.string += "P"
                    else:
                        self.board[i].append(-1)
                        self.string += " "

    def check_str(self):
        self.string = ""
        for i in range(0, self.width):
            for j in range(0, self.heigth):
                if (self.board[i][j] == 0):
                    self.string += "p"
                elif (self.board[i][j] == 1):
                    self.string += "P"
                else:
                    self.string += " "
    # Ecris dans la console sous forme textuelle le tableau
    # self -> l'instance

    def toStr(self):
        for i in range(0, len(self.board)):
            line = ""
            for j in range(0, len(self.board[i])):
                if (self.board[i][j] == 0):
                    line = line + "n"
                elif (self.board[i][j] == 1):
                    line = line + "b"
                else:
                    line = line + "."
            print(line)
