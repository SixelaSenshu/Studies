from src.printer.Printer import *
from src.json.JSONParser import *
from src.json.JSONParser import *
from src.interpretor.Interpretor import *
from src.compiler.Compiler import *

import sys

def main():
    
    if(sys.argv.__len__() < 2):
        print("Please provide a JSON file")
    elif(sys.argv.__len__() > 3):
        print("Select one option")
        print("-p: Print")
        print("-i: Interprete")
    else:
        if(sys.argv.__len__() == 3):
            if(sys.argv[2] == "-p"):
                jsonParser = JSONParser(str(sys.argv[1]));
                data = jsonParser.parse()
                parseProgram(data)
            elif(sys.argv[2] == "-i"):
                jsonParser = JSONParser(str(sys.argv[1]));
                data = jsonParser.parse()
                interpreteProgram(data)
            elif(sys.argv[2] == "-c"):
                jsonParser = JSONParser(str(sys.argv[1]));
                data = jsonParser.parse()
                compiler = Compiler()
                res= compiler.compileProgram(data)
                for code in res:
                    print(code)
    return 0

if __name__ == '__main__':
    main()