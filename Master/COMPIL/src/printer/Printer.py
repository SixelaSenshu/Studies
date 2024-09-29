import json

def parseProgram(data):
        program = data["program"]
        body = program["body"]
        for i in body:
            string = "" 
            if i["type"] == "ExpressionStatement":
                string += expressionStatement(i,"expression") + ";"
            if i["type"] == "VariableDeclaration":
                declaration = i["declarations"]
                for j in declaration:
                    if (j == declaration[0]):
                        string += "var "
                    string += variableDeclaration(j)
                    if(j != declaration[-1]):
                        string += ", "
                string += ";"   
            if i["type"] == "WhileStatement":
                string += whileStatement(i)
            if i["type"] == "IfStatement":
                string += ifStatement(i,"")
            if i["type"] == "FunctionDeclaration":
                string += functionDeclaration(i,"")
            if i["type"] == "ForStatement":
                string += forStatement(i)
            print(string)
        return string
    
def functionDeclaration(exp,space):
        string = ""
        string += "function "
        string += exp["id"]["name"]
        string += "("
        for arg in exp["params"]:
            string += arg["name"]
            if(arg != exp["params"][-1]):
                string += ", "
        string += "){"
        for sub_exp in exp["body"]["body"]:
            if (sub_exp["type"] == "ExpressionStatement"):
                string += "\n" + space + "  "+expressionStatement(sub_exp,"expression") +";"
            elif (sub_exp["type"] == "ReturnStatement"):
                string += "\n" + space + "  "+ returnStatement(sub_exp) + ";"
            elif (sub_exp["type"] == "VariableDeclaration"):
                string += "\n" + space + "  "+ variableDeclaration(sub_exp) + ";"
            elif (sub_exp["type"] == "IfStatement"):
                string += "\n" + space + "  "+ ifStatement(sub_exp,"  ")
            elif (sub_exp["type"] == "WhileStatement"):
                string += "\n" + space + "  "+ whileStatement(sub_exp)
            elif (sub_exp["type"] == "ForStatement"):
                string += "\n" + space + "  "+ forStatement(sub_exp)
            elif (sub_exp["type"] == "BinaryExpression"):
                string += "\n" + space + "  "+ binaryExpression(sub_exp) + ";"
            elif (sub_exp["type"] == "CallExpression"):
                string += "\n" + space + "  "+ callExpression(sub_exp) + ";"
            elif (sub_exp["type"] == "SwitchStatement"):
                string += "\n" + space + "  "+ switchStatement(sub_exp,space + " ") + ""
            elif(sub_exp["type"] == "FunctionDeclaration"):
                string += "\n" + space + "  "+ functionDeclaration(sub_exp,space + "  ") + ""
        return string + "\n" + space + "};\n" 

def ifStatement(exp,space):
        string = ""
        string += "if("
        if(exp["test"]["type"] == "BinaryExpression"):
            string += binaryExpression(exp["test"])
        if(exp["test"]["type"] == "LogicalExpression"):
            string += logicalExpression(exp["test"])
        string += "){\n" 
        if(exp["consequent"]["type"] == "BlockStatement"):
            for sub_exp in exp["consequent"]["body"]:
                if(sub_exp["type"] == "IfStatement"):
                    string = string  + space + "  " + ifStatement(sub_exp)
                    space = "  "
                if(sub_exp["type"] == "ExpressionStatement"):
                    string = string  + space + "  " + expressionStatement(sub_exp,"expression")
                    if(sub_exp != exp["consequent"]["body"][-1]):
                        string += "\n"
                    else:
                        string += ";"
                if (sub_exp["type"] == "ContinueStatement"):
                    string = string  + space + "  " + continueStatement()
                if (sub_exp["type"] == "BreakStatement"):
                    string = string  + space + "  " + breakStatement()
                if (sub_exp["type"] == "ReturnStatement"):
                    string = string  + space + "  " + returnStatement(sub_exp)
        string += "\n" + space + "}"
        if(exp["alternate"]):
            string += " else {\n"
            if(exp["alternate"]["type"] == "BlockStatement"):
                for sub_exp in exp["alternate"]["body"]:
                    string = string  + "  " + expressionStatement(sub_exp,"expression")
                    if(sub_exp != exp["alternate"]["body"][-1]):
                        string += ";\n"
                    else:
                        string += ";"
            string += "\n" + space + "}"
        return string
    
def memberExpression(exp):
        string = ""
        if(exp["object"]["type"] == "NullLiteral"):
            string += nullLiteral()
        elif(exp["object"]["type"] == "Identifier"):
            string += indentifier(exp["object"])
        elif(exp["object"]["type"] == "ThisExpression"):
            string += thisExpression(exp["object"])    
        string += "."
        string += exp["property"]["name"]
        string += ""
        return string
    
def unaryExpression(exp):
        string = ""
        string += exp["operator"]
        if(exp["argument"]["type"] == "BinaryExpression"):
            string += binaryExpression(exp["argument"])
        elif(exp["argument"]["type"] == "NumericLiteral"):
            string += numericLiteral(exp["argument"])
        elif(exp["argument"]["type"] == "StringLiteral"):
            string += stringLiteral(exp["argument"])
        elif(exp["argument"]["type"] == "Identifier"):
            string += indentifier(exp["argument"])
        return "(" +  string + ")"


def logicalExpression(exp):
        string = ""
        if(exp["left"]["type"] == "MemberExpression"):
            string += memberExpression(exp["left"])
        elif(exp["left"]["type"] == "BooleanLiteral"):
            string += booleanLiteral(exp["left"])
        elif(exp["left"]["type"] == "BinaryExpression"):
            string += binaryExpression(exp["left"])
        string += " " + exp["operator"] + " "
        if(exp["right"]["type"] == "MemberExpression"):
            string += memberExpression(exp["right"])
        elif(exp["right"]["type"] == "BooleanLiteral"):
            string += booleanLiteral(exp["right"])
        elif(exp["right"]["type"] == "BinaryExpression"):
            string += binaryExpression(exp["right"])
        return string

def whileStatement(exp):
        string = ""
        string += "while("
        if(exp["test"]["type"] == "BinaryExpression"):
            string += binaryExpression(exp["test"])
        string += "){\n" 
        if(exp["body"]["type"] == "BlockStatement"):
            for sub_exp in exp["body"]["body"]:
                if(sub_exp["type"] == "IfStatement"):
                    string = string  + "  " + ifStatement(sub_exp,"  ")
                elif(sub_exp["type"] == "WhileStatement"):
                    string = string  + "  " + whileStatement(sub_exp)
                elif(sub_exp["type"] == "ExpressionStatement"):
                    string = string  + "  " + expressionStatement(sub_exp,"expression")
                if(sub_exp != exp["body"]["body"][-1]):
                    string += ";\n"
                else:
                    string += ";"
        string += "\n}"
        return string
    
def assignmentExpression(exp):
        if(exp == None):
            return ""
        string = ""
        var = exp.get("left") 
        if(var):
            if(exp["left"]["type"] == "MemberExpression"):
                string += memberExpression(exp["left"])
            elif(exp["left"]["type"] == "Identifier"):
                string += exp["left"]["name"]
        string += " " + exp["operator"] + " "
        if(exp["right"]["type"] == "BinaryExpression"):
            string += binaryExpression(exp["right"])
        elif(exp["right"]["type"] == "NumericLiteral"):
            string += numericLiteral(exp["right"])
        elif(exp["right"]["type"] == "StringLiteral"):
            string += stringLiteral(exp["right"])
        elif(exp["right"]["type"] == "Identifier"):
            string += indentifier(exp["right"])
        return string
    
def forStatement(exp):
        string = ""
        string += "for("
        string += assignmentExpression(exp["init"])
        string += "; "
        line = binaryExpression(exp["test"])
        string += line
        string += "; "
        if(exp["update"]["type"] == "AssignmentExpression"):
            string += assignmentExpression(exp["update"])
        elif (exp["update"]["type"] == "UpdateExpression"):
            string += updateExpression(exp["update"])
        string += "){\n"

        if(exp["body"]["type"] == "BlockStatement"):
            for sub_exp in exp["body"]["body"]:
                string = string  + "  " + expressionStatement(sub_exp,"expression")
                if(sub_exp != exp["body"]["body"][-1]):
                    string += "\n"
                else:
                    string += ";"
        return  string + "\n}\n"
    
def switchCase(exp,space):
        string = ""
        if(exp["test"]):
            string += space + "case "
            if(exp["test"]["type"] == "NumericLiteral"):
                string += numericLiteral(exp["test"])
            elif(exp["test"]["type"] == "StringLiteral"):
                string += stringLiteral(exp["test"])
            elif(exp["test"]["type"] == "BinaryExpression"):
                string += binaryExpression(exp["test"])
            elif(exp["test"]["type"] == "Identifier"):
                string += indentifier(exp["test"])
            elif (exp["test"]["type"] == "CallExpression"):
                string += callExpression(exp["test"])
            string += ":\n"
        else:
            string += space + "default:\n"
        for consq in exp["consequent"]:
            string += space + "    return " + expressionStatement(consq,"argument") + ";"
        return string
        


def switchStatement(exp,space):
        string = ""
        string += "switch("
        string += expressionStatement(exp,"discriminant")
        string += "){\n"
        for sub_exp in exp["cases"]:
            string += switchCase(sub_exp,space + "    ")
            if(sub_exp != exp["cases"][-1]):
                string += "\n"
        return string +"\n" + space+ "  }"
    
    
def expressionStatement(exp,name):
        string = "" 

        if exp[name]["type"] == "BinaryExpression":
            string += binaryExpression(exp[name])
        elif exp[name]["type"] == "NumericLiteral":
            string += numericLiteral(exp[name])
        elif exp[name]["type"]== "UpdateExpression":
            string += updateExpression(exp[name])
        elif exp[name]["type"] == "CallExpression":
            string += callExpression(exp[name])
        elif exp[name]["type"] == "AssignmentExpression":
            string += assignmentExpression(exp[name])
        elif exp[name]["type"] == "MemberExpression":
            string += memberExpression(exp[name])
        elif exp[name]["type"] == "LogicalExpression":
            string += logicalExpression(exp[name])
        elif exp[name]["type"] == "Identifier":
            string += indentifier(exp[name])
        elif exp[name]["type"] == "ReturnStatement":
            string += returnStatement(exp[name])
        elif exp[name]["type"] == "UnaryExpression":
            string += unaryExpression(exp[name])
        return string
    
    
def callExpression(exp):
        string = "" 
        if(exp["callee"].get("name")):
            string += str(exp["callee"]["name"])
        if(exp["callee"]["type"] == "Indentifier"):
            string += indentifier(exp["callee"])
        elif(exp["callee"]["type"] == "CallExpression"):
            string += callExpression(exp["callee"])
        string += "("
        for arg in exp["arguments"]:
            if arg["type"] == "BinaryExpression":
                string += binaryExpression(arg)
            elif arg["type"] == "NumericLiteral":
                string += numericLiteral(arg)
            elif arg["type"] == "StringLiteral":
                string += stringLiteral(arg)
            elif arg["type"] == "Identifier":
                string += indentifier(arg)
            if(arg != exp["arguments"][-1]):
                string += ", "
            if(arg["type"] == "CallExpression"):
                string += callExpression(arg)
            if(arg["type"] == "UnaryExpression"):
                string += unaryExpression(arg)
        string += ")"
        return string
    
def newExpression(exp):
        string = ""
        string += "new "
        string += exp["callee"]["name"]
        string += "("
        for arg in exp["arguments"]:
            if arg["type"] == "StringLiteral":
                string += stringLiteral(arg)
            elif arg["type"] == "NumericLiteral":
                string += numericLiteral(arg)
            elif arg["type"] == "Identifier":
                string += indentifier(arg)
            if(arg != exp["arguments"][-1]):
                string += ", "
        return string + ")"
    
def thisExpression(exp):
        string = "" 
        string += "this"
        return string
    
def objectProperty(exp):
        string = ""
        for param in exp["properties"]:
            if(param["key"]["type"]) == "StringLiteral":
                string += param["key"]["value"]
            string += ": "
            if(param["value"]["type"]) == "StringLiteral":
                string += stringLiteral(param["value"])
            elif(param["value"]["type"]) == "NumericLiteral":
                string += numericLiteral(param["value"])
            if(param != exp["properties"][-1]):
                string += ", "
        return string
    
def objectExpression(exp):
        string = ""
        if(exp["type"] == "ObjectExpression"):
            string += "{" + objectProperty(exp) + "}"
        return string

def variableDeclaration(exp):
        string = ""
        string += exp["id"]["name"]
        string += " = "
        if(not exp["init"]):
            string += "undefined"
        else:
            if(exp["init"]["type"] == "NullLiteral"):
                string += nullLiteral()
            elif(exp["init"]["type"] == "NumericLiteral"):
                string += numericLiteral(exp["init"])
            elif(exp["init"]["type"] == "StringLiteral"):
                string += stringLiteral(exp["init"])
            elif(exp["init"]["type"] == "Identifier"):
                string += indentifier(exp["init"])
            elif(exp["init"]["type"] == "BooleanLiteral"):
                string += booleanLiteral(exp["init"])
            elif(exp["init"]["type"] == "MemberExpression"):
                string += memberExpression(exp["init"])
            elif(exp["init"]["type"] == "ObjectExpression"):
                string += objectExpression(exp["init"])
            elif(exp["init"]["type"] == "NewExpression"):
                string += newExpression(exp["init"])
            elif(exp["init"]["type"] == "CallExpression"):
                string += callExpression(exp["init"])
        return string
    
def updateExpression(exp):
        string = ""
        # string += " = "
        if(exp["prefix"]):
            string += exp["operator"]
            string += exp["argument"]["name"]
        else:
            string += exp["argument"]["name"]
            string += exp["operator"]
            
        return string 

def binaryExpression(exp):
        string = "" 
        if exp["left"]["type"] == "BinaryExpression":
            if(exp["left"]["operator"] == "+" and exp["operator"] == "*"):
                string += "("
            string += binaryExpression(exp["left"])
            if(exp["left"]["operator"] == "+" and exp["operator"] == "*"):
                string += ")"
        elif exp["left"]["type"] == "NumericLiteral":
            string += numericLiteral(exp["left"])
        elif exp["left"]["type"] == "Identifier":
            string += indentifier(exp["left"])
        elif exp["left"]["type"] == "UpdateExpression":
            string += updateExpression(exp["left"])
        elif exp["left"]["type"] == "CallExpression":
            string += callExpression(exp["left"])
        string = string + " " + exp["operator"] + " "
        if exp["right"]["type"] == "BinaryExpression":
            if(exp["right"]["operator"] == "+" and exp["operator"] == "*"):
                string += "("
            string += binaryExpression(exp["right"])
            if(exp["right"]["operator"] == "+" and exp["operator"] == "*"):
                string += ")"
        elif exp["right"]["type"] == "NumericLiteral":
            string += numericLiteral(exp["right"])
        elif exp["right"]["type"] == "Identifier":
            string += indentifier(exp["right"])
        elif exp["right"]["type"] == "UpdateExpression":
            string += updateExpression(exp["right"])
        elif exp["right"]["type"] == "CallExpression":
            string += callExpression(exp["right"])
        return string

def numericLiteral(exp):
        return str(exp["value"])
    
def indentifier(exp):
        return str(exp["name"])
    
def nullLiteral():
        return "null"
    
def stringLiteral(exp):
        return "\"" + exp["value"] + "\""
    
def returnStatement(exp):
        return "return " + expressionStatement(exp,"argument")
    
def breakStatement():
        return "break"
    
def continueStatement():
        return "continue"

def booleanLiteral(exp):
        string = ""
        line = str(exp["value"])
        if(line == "True"):
            string += "true"
        else:
            string += "false"
        return string
    
        

    