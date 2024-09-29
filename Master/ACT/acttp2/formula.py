from reader import *

# Q1
# Permet de calculer la meilleur configuration possible
# list -> La liste des valeurs des plateaux


def getBetterConfiguration(list: [int]):
    haveneg = False
    maxNeg = 0
    maxPos = 0
    for i in range(len(list)):
        if list[i] >= 0 and list[i] > maxPos:
            maxPos = list[i]
        elif list[i] < 0:
            if (not (haveneg)):
                haveneg = True
                maxNeg = list[i]
            elif (maxNeg < list[i]):
                maxNeg = list[i]
    if haveneg:
        return maxNeg
    else:
        return maxPos

# Q2
# Vérifie et confirme un déplacment avec un joueur si il n'y pas a un adversaire
# col -> la colonne
# lig -> la ligne
# reader -> Le tableau de jeu
# player -> La couleur du joueur


def canmove(col: int, lig: int, reader: Reader, player: str):
    if player == "b" and col - 1 >= 0 and reader.board[col - 1][lig] == -1:
        return 1
    if player == "n" and col + 1 < (len(reader.board)) and reader.board[col + 1][lig] == -1:
        return 1
    return 0

# Lance un déplacment avec un joueur si il n'y pas a un adversaire
# col -> la colonne
# lig -> la ligne
# reader -> Le tableau de jeu
# player -> La couleur du joueur


def move(col: int, lig: int, reader: Reader, player: str):
    if player == "b":
        reader.board[col][lig] = -1
        reader.board[col - 1][lig] = 1
        reader.check_str()
    if player == "n":
        reader.board[col][lig] = -1
        reader.board[col + 1][lig] = 0
        reader.check_str()

# Vérifie et confirme une attaque avec un joueur si il y a un adversaire
# col -> la colonne
# lig -> la ligne
# side -> la direction de l'attaque
# reader -> Le tableau de jeu
# player -> La couleur du joueur


def canAttack(col: int, lig: int, side: str, reader: Reader, player: str):
    if player == "b":
        if side == "left" and (
            col - 1 >= 0
            and lig - 1 >= 0
            and reader.board[col - 1][lig - 1] == 0
        ):
            return 1
        elif side == "right" and (
            col - 1 >= 0
            and lig + 1 < reader.heigth - 1
            and reader.board[col - 1][lig + 1] == 0
        ):
            return 1
    if player == "n":
        if side == "left" and (
            col + 1 < len(reader.board) - 1
            and lig - 1 >= 0
            and reader.board[col + 1][lig - 1] == 1
        ):
            return 1
        elif side == "right" and (
            col + 1 < len(reader.board) - 1
            and lig + 1 < reader.heigth - 1
            and reader.board[col + 1][lig + 1] == 1
        ):
            return 1
    return 0

# Lance une attaque avec un joueur si il y a un adversaire
# col -> la colonne
# lig -> la ligne
# side -> la direction de l'attaque
# reader -> Le tableau de jeu
# player -> La couleur du joueur


def attack(col: int, lig: int, side: str, reader: Reader, player: str):
    if player == "b":
        if side == "left":
            reader.board[col][lig] = -1
            reader.board[col - 1][lig - 1] = 1
            reader.check_str()
        if side == "right":
            reader.board[col][lig] = -1
            reader.board[col - 1][lig + 1] = 1
            reader.check_str()
    if player == "n":
        if side == "left":
            reader.board[col][lig] = -1
            reader.board[col + 1][lig - 1] = 0
            reader.check_str()
        if side == "right":
            reader.board[col][lig] = -1
            reader.board[col + 1][lig + 1] = 0
            reader.check_str()

# Permet pour un plateau de savoir si il reste des coups disponibles
# board -> Le tableau de jeu


def endOfGame(reader: Reader):
    haveplayerb = False
    haveplayern = False
    for i in range(0, len(reader.board)):
        for j in range(0, len(reader.board[i])):
            if reader.board[i][j] == 0:
                haveplayern = True
                if (
                    canAttack(i, j, "left", reader, "n")
                    or canAttack(i, j, "right", reader, "n")
                    or canmove(i, j, reader, "n")
                ):
                    return 0
                if (j == reader.heigth):
                    return 1
            elif reader.board[i][j] == 1:
                haveplayerb = True
                if (
                    canAttack(i, j, "left", reader, "b")
                    or canAttack(i, j, "right", reader, "b")
                    or canmove(i, j, reader, "b")

                ):
                    return 0
                if (j == 0):
                    return 1
    if (haveplayerb == False or haveplayern == False):
        return 0
    return 1

#  Algorithme naif qui permet de simuler toutes les configurations afin d'avoir la meilleur
# board -> Le tableau de jeu
# nb -> nombre de tour depuis le début


def algorithmNaif(board: Reader, nb: int, joueur, joueur_start):
    newboards = []
    res = []
    if (endOfGame(board)):
        if (joueur != joueur_start):
            return -nb
        return nb
    for i in range(0, len(board.board)):
        for j in range(0, len(board.board[0])):
            if (board.board[i][j] == 0 and joueur == "n"):
                if (canAttack(i, j, "left", board, "n")):
                    newboarln = Reader(
                        "", board.width, board.heigth, board.string)
                    attack(i, j, "left", newboarln, "n")
                    newboards.append(newboarln)
                if (canAttack(i, j, "right", board, "n")):
                    newboardrn = Reader(
                        "", board.width, board.heigth, board.string)
                    newboards.append(newboardrn)
                    attack(i, j, "right", newboardrn, "n")
                if (canmove(i, j, board, "n")):
                    newboard = Reader(
                        "", board.width, board.heigth, board.string)
                    move(i, j, newboard, "n")
                    newboards.append(newboard)
            elif (board.board[i][j] == 1 and joueur == "b"):
                if (canAttack(i, j, "left", board, "b")):
                    newboardlb = Reader(
                        "", board.width, board.heigth, board.string)
                    newboards.append(newboardlb)
                    attack(i, j, "left", newboardlb, "b")
                if (canAttack(i, j, "right", board, "b")):
                    newboardrb = Reader(
                        "", board.width, board.heigth, board.string)
                    attack(i, j, "right", newboardrb, "b")
                    newboards.append(newboardrb)
                if (canmove(i, j, board, "b")):
                    newboardmb = Reader(
                        "", board.width, board.heigth, board.string)
                    move(i, j, newboardmb, "b")
                    newboards.append(newboardmb)
    if (len(newboards) == 0):
        if (joueur != joueur_start):
            return - nb
        return nb
    newnb = nb + 1
    for k in range(0, len(newboards)):
        newj = ""
        if (joueur == "b"):
            newj = "n"
        elif (joueur == "n"):
            newj = "b"
        cal = algorithmNaif(newboards[k], newnb, newj, joueur_start)
        res.append(cal)
    # print(res)
    return getBetterConfiguration(res)


# Q3

#  Algorithme naif qui permet de simuler toutes les configurations afin d'avoir la meilleur
# board -> Le tableau de jeu
def algorithmMemo(board: Reader, nb: int, hastable, joueur, joueur_start):
    newboards = []
    res = []
    if (endOfGame(board)):
        if (joueur != joueur_start):
            return - nb
        return nb
    for i in range(0, len(board.board)):
        for j in range(0, len(board.board[0])):
            if (board.board[i][j] == 0 and joueur == "n"):
                if (canAttack(i, j, "left", board, "n")):
                    newboarln = Reader(
                        "", board.width, board.heigth, board.string)
                    attack(i, j, "left", newboarln, "n")
                    newboards.append(newboarln)
                if (canAttack(i, j, "right", board, "n")):
                    newboardrn = Reader(
                        "", board.width, board.heigth, board.string)
                    newboards.append(newboardrn)
                    attack(i, j, "right", newboardrn, "n")
                if (canmove(i, j, board, "n")):
                    newboard = Reader(
                        "", board.width, board.heigth, board.string)
                    move(i, j, newboard, "n")
                    newboards.append(newboard)
            elif (board.board[i][j] == 1 and joueur == "b"):
                if (canAttack(i, j, "left", board, "b")):
                    newboardlb = Reader(
                        "", board.width, board.heigth, board.string)
                    newboards.append(newboardlb)
                    attack(i, j, "left", newboardlb, "b")
                if (canAttack(i, j, "right", board, "b")):
                    newboardrb = Reader(
                        "", board.width, board.heigth, board.string)
                    attack(i, j, "right", newboardrb, "b")
                    newboards.append(newboardrb)
                if (canmove(i, j, board, "b")):
                    newboardmb = Reader(
                        "", board.width, board.heigth, board.string)
                    move(i, j, newboardmb, "b")
                    newboards.append(newboardmb)
    if (len(newboards) == 0):
        if (joueur != joueur_start):
            return - nb
        return nb
    newnb = nb + 1
    for k in range(0, len(newboards)):
        string = newboards[k].string
        value = 0
        if (string in hastable):
            value = hastable[newboards[k].string]
            res.append(value)
            return value
        else:
            newj = ""
            if (joueur == "b"):
                newj = "n"
            elif (joueur == "n"):
                newj = "b"
            value = algorithmMemo(
                newboards[k], newnb, hastable, newj, joueur_start)
            res.append(value)
            better = getBetterConfiguration(res)
            hastable[newboards[k].string] = better
            # print(res)
            return better
