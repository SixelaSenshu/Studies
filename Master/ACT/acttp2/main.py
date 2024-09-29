from reader import *
from formula import *


# Fonction principale du programme
def main():
    print("----------------------------------------------------------------------------------------\nConfig3x4_1.txt\n----------------------------------------------------------------------------------------")
    board = Reader("./Tests/Config3x4_1.txt", 0, 0, "")
    board.toStr()
    print("res :", algorithmNaif(board, 0, "b", "b"))
    print("res :", algorithmMemo(board, 0, {}, "b", "b"))

    print("----------------------------------------------------------------------------------------\nConfig4x4_0.txt\n----------------------------------------------------------------------------------------")
    board = Reader("./Tests/Config4x4_0.txt", 0, 0, "")
    board.toStr()
    print("res : ", algorithmNaif(board, 0, "b", "b"))
    print("res :", algorithmMemo(board, 0, {}, "b", "b"))

    print("----------------------------------------------------------------------------------------\nConfig4x4_11.txt\n----------------------------------------------------------------------------------------")
    board = Reader("./Tests/Config4x4_11.txt", 0, 0, "")
    board.toStr()
    print("res :", algorithmMemo(board, 0, {}, "b", "b"))


main()
