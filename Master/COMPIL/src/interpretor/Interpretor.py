from src.interpretor.StackFrame import *
from src.Semantic import *

class Interpretor:

    def __init__(self):
        self.main_stack = StackFrame("interpreter")

    def read(self, data):
        print("var Print = console.log;");
        program = data["program"]
        body = program["body"]
        for exp in body:
            type = exp["type"]
            if(type == "ExpressionStatement"):
                expressionStatement(exp["expression"],self.main_stack)
            elif(type == "VariableDeclaration"):
                for declaration in exp["declarations"]:
                    variableDeclaration(declaration,self.main_stack)
            elif(type == "FunctionDeclaration"):
                functionDeclaration(exp,self.main_stack)
            elif(type.find("Statement")):
                statement(exp,self.main_stack)
        
def interpreteProgram(data):
    interpretor = Interpretor()
    interpretor.read(data)
    
