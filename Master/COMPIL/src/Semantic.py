
from src.interpretor.StackFrame import *
from src.interpretor.Interpretor import *

#************************************************************************/
#                             Expressions 
#************************************************************************/

def expressionStatement(node,stackFrame):
    if(node["type"] == "Identifier"):
        print("ExpressionStatement : " + str(node["name"]))
        stackFrame.add_var(node["name"],0)
        return stackFrame.get_var(node["name"])
    elif(node["type"]=="NumericLiteral"):
        return literal(node,stackFrame)
    elif(node["type"] == "BinaryExpression"):
        res = binaryExpression(node,stackFrame)
        if(res):
            print("BinaryExpression : " + str(res))
        return res
    elif(node["type"] == "UpdateExpression"):
        return updateExpression(node,stackFrame)
    elif(node["type"] == "CallExpression"):
        res = callExpression(node,stackFrame)
        return res
    elif(node["type"] == "AssignmentExpression"):
        return assignementExpression(node,stackFrame)
    elif(node["type"] == "MemberExpression"):
        res = memberExpression(node,stackFrame)
        print("MemberExpression :" + str(res))
        return res 
    elif(node["type"] == "LogicalExpression"):
        res = logicalExpression(node,stackFrame)
        if(res == 1):
            print("LogicalExpression : True")
        else:
            print("LogicalExpression : False")
        return res
    return None

def binaryExpression(node,stackFrame):
    ope = node["operator"]
    left = node["left"]
    right = node["right"]
    resL = binaryExpressionType(left,stackFrame)
    resR = binaryExpressionType(right,stackFrame) 
    binaryExpressionOpe(ope,stackFrame)
    if(stackFrame.length_stack() == 0):
        return 0
    return stackFrame.top()

    
    
    
def binaryExpressionType(node,stackFrame):
    if(node["type"] == "NumericLiteral"):
        return literal(node,stackFrame)
    elif(node["type"] == "BinaryExpression"):
        return binaryExpression(node,stackFrame)
    elif(node["type"] == "UpdateExpression"):
        return updateExpression(node,stackFrame)
    elif(node["type"] == "Identifier"):
        stackFrame.push(get_var_from_stack(stackFrame,node["name"]))
        return get_var_from_stack(stackFrame,node["name"])   
    elif(node["type"] == "CallExpression"):
        return callExpression(node,stackFrame)

def binaryExpressionOpe(ope,stackFrame):
    if(stackFrame.length_stack() != 0):
        n = stackFrame.pop()
        if(stackFrame.length_stack() != 0):
            m = stackFrame.pop()
            if(ope == "+"):
                stackFrame.push(m+n)
            elif(ope == "-"):
                stackFrame.push(m-n)
            elif(ope == "*"):
                stackFrame.push(m*n)
            elif(ope == "/"):
                if(n == 0):
                    print("Infinity : Division by 0")
                else:
                    stackFrame.push(m/n)
            elif(ope == "=="):
                if(m == n):
                    stackFrame.push(True)
                else:
                    stackFrame.push(False)

def updateExpression(node,stackFrame):
    if(node["operator"] == "++"):
        if(node["argument"]["type"] == "Identifier"):
            var = get_var_from_stack(stackFrame,node["argument"]["name"])
            set_var_from_stack(stackFrame,node["argument"]["name"],var+1)
            stackFrame.push(var+1);
    elif(node["operator"] == "--"):
        if(node["argument"]["type"] == "Identifier"):
            var = get_var_from_stack(stackFrame,node["argument"]["name"])
            set_var_from_stack(stackFrame,node["argument"]["name"],var-1)
            stackFrame.push(var-1);
    print("UpdateExpression : " + str(node["argument"]["name"]) + str(node["operator"]))
    return stackFrame.top()
            
def callExpression(nodeGet,stackFrame):
    callStackFrame = StackFrame(nodeGet['callee']['name'])
    callStackFrame.add_parent(stackFrame)
    if(nodeGet["callee"]["name"] == "print"):
        string = ""
        for param in nodeGet["arguments"]:
            if(param["type"]=="CallExpression"):
                string += str(callExpression(param,callStackFrame))
            elif(param["type"] == "Identifier"):
                string += param["name"] +   " => " + str(get_var_from_stack(stackFrame,param["name"])) + ""
            elif(param["type"].find("Literal")):
                string += str(literal(param,callStackFrame.get_stack())) + ""  
            elif(param["type"]=="ExpressionStatement"):
                string += str(expressionStatement(param,callStackFrame)) + ""
            elif(param["type"].find("Statement")):
                string += str(statement(param,callStackFrame)) + ""
            if(param != nodeGet["arguments"][-1]):
                string += ", "
        print("Print(" + string + ")")
        return string
    else:
        node = get_func_from_stack(callStackFrame,nodeGet["callee"]["name"])
        print("Callee : "+nodeGet["callee"]["name"])
        # for param in node["params"]:
        #     callStackFrame.add_var(param["name"],0)
        # count = 0
        # for param in node["arguments"]:
        #     if(param["type"] == "Identifier"):
        #         callStackFrame.add_var(param["name"],arg["value"])
        #     elif(param["type"] == "UpdateExpression"):
        #         print(param)
        #         updateExpression(param,callStackFrame)
        #     elif(param["type"] == "BinaryExpression"):
        #         binaryExpression(param,callStackFrame)
        # for arg in node["body"]["body"]:
        #     if(arg["type"]=="ExpressionStatement"):
        #         res = expressionStatement(arg["expression"],callStackFrame)    
        #     elif(arg["type"].find("Literal")):
        #         literal(arg,callStackFrame)
        #     elif(arg["type"]=="ReturnStatement"):
        #             res = returnStatement(arg,callStackFrame)
        #             stackFrame.push(res)
        #             return res;
        #     elif(arg["type"].find("Statement")):
        #         statement(arg,callStackFrame)
        return stackFrame.top();
            
                    
def assignementExpression(node,stackFrame):
    variable = node["left"]
    value = node["right"]
    var = get_var_from_stack(stackFrame,variable["name"])
    stackFrame.push(var)
    res = literal(value,stackFrame)
    if(res == None):
        expressionStatement(value,stackFrame)
        res = stackFrame.pop()
    if(not(node["operator"] == "=")):
        assignementExpressionOpe(node["operator"],stackFrame)
        res = stackFrame.pop()
    set_var_from_stack(stackFrame,variable["name"],res)
    print("AssignementExpression : " + str(variable["name"]) + " " + node["operator"] + " " +  str(node["right"]["value"]) + " ==> (" + str(res) +")")
    return res

def assignementExpressionOpe(ope,stackFrame):
    if(ope == "+="):
        n = stackFrame.pop()
        m = stackFrame.pop()
        stackFrame.push(m+n)
    elif(ope == "-="):
        n = stackFrame.pop()
        m = stackFrame.pop()
        stackFrame.push(m-n)
    elif(ope == "*="):
        n = stackFrame.pop()
        m = stackFrame.pop()
        stackFrame.push(m*n)
    elif(ope == "/="):
        n = stackFrame.pop()
        m = stackFrame.pop()
        stackFrame.push(m/n)
        
def memberExpression(node,stackFrame):
    if(node["object"]["type"] == "NullLiteral"):
        return 0
    elif(node["object"]["type"] == "ThisExpression"):
        return 1

def logicalExpression(node,stackFrame):
    ope = node["operator"]
    left = node["left"]
    right = node["right"]
    resL = logicalExpressionType(left,stackFrame)
    resR = logicalExpressionType(right,stackFrame)
    return condition(ope,resL,resR,stackFrame)
     
def logicalExpressionType(node,stackFrame):
    if(node["type"] == "NumericLiteral"):
        return literal(node,stackFrame)
    elif(node["type"] == "BinaryExpression"):
        res = binaryExpression(node,stackFrame)
        stackFrame.push(res)
        return res
    elif(node["type"] == "MemberExpression"):
        return memberExpression(node,stackFrame)
    elif(node["type"] == "Identifier"):
        stackFrame.push(get_var_from_stack(stackFrame,node["name"]))
        return get_var_from_stack(stackFrame,node["name"])
           
    


#************************************************************************/
#                             Statements
#************************************************************************/

def statement(exp,stackFrame):
    res = 1
    if(exp["type"] == "WhileStatement"):
        print("\nWhileStatement : BEGIN")
        res = whileStatement(exp,stackFrame)
        print("WhileStatement : END\n")
    elif(exp["type"] == "IfStatement"):
        print("\nIfStatement : BEGIN")
        res = ifStatement(exp,stackFrame)
        print("IfStatement : END\n")
    elif(exp["type"] == "ForStatement"):
        print("\nForStatement : BEGIN")
        res = forStatement(exp,stackFrame)
        print("ForStatement : END\n")
    elif(exp["type"] == "EmptyStatement"):
        print("EmptyStatement")
        res = emptyStatement()
    elif(exp["type"] == "BreakStatement"):
        res = breakStatement()
        print("BreakStatement")
    elif(exp["type"] == "ContinueStatement"):
        res = continueStatement()
        print("ContinueStatement")
    elif(exp["type"] == "ReturnStatement"):
        res = returnStatement(exp,stackFrame)
        print("ReturnStatement ")
    elif(exp["type"] == "SwitchStatement"):
        switchStatement(exp,stackFrame)
        print("SwitchStatement ")
    return res

def switchStatement(node,stackFrame):
    var = get_var_from_stack(stackFrame,node["discriminant"])
    for cases in node["cases"]:
        if(condition("==",node["discriminant"],cases["test"])):
            return returnStatement(cases["consequent"])

def whileStatement(node,stackFrame):
    test = node["test"]
    body = node["body"] 
    while(condition(test["operator"],test["left"],test["right"],stackFrame)):
        for block in body["body"]:
            if(block["type"] == "ExpressionStatement"):
                expressionStatement(block["expression"],stackFrame)
            elif(block["type"].find("Statement")):
                res = statement(block,stackFrame)
                if(res == 0):
                    return 0

def ifStatement(node,stackFrame):
    test = node["test"] 
    consequent = node["consequent"]
    alternate = node["alternate"]
    if(condition(test["operator"],test["left"],test["right"],stackFrame)):
        for block in consequent["body"]:
            if(block["type"] == "LogicalExpression"):
                logicalExpression(block,stackFrame)
            elif(block["type"] == "ExpressionStatement"):
                expressionStatement(block["expression"],stackFrame)
            elif(block["type"].find("Statement")):
                res = statement(block,stackFrame)
                if(res == 0):
                    return res
    elif(alternate):
        print("ElseStatement : BEGIN")
        for block in consequent["body"]:
            if(block["type"] == "ExpressionStatement"):
                expressionStatement(block["expression"],stackFrame)
            elif(block["type"].find("Statement")):
                res = statement(block,stackFrame)
                if(res == 0):
                    return res
        print("ElseStatement : END")
        return 1
        
def forStatement(node,stackFrame):
    init = node["init"]
    test = node["test"]
    update = node["update"]
    body = node["body"] 
    print("Condition : " + str(conditionGet(test["left"],stackFrame)) + " " + test["operator"] + " " +  str(conditionGet(test["right"],stackFrame)))
    if(init):
        assignementExpression(init,stackFrame)
    while(condition(test["operator"],test["left"],test["right"],stackFrame)):
        for arg in body["body"]:
            expressionStatement(arg,stackFrame)
        expressionStatement(update,stackFrame)
    
def emptyStatement():
   return 1

def breakStatement():
    return 0

def continueStatement():
    return 1

def returnStatement(node,stackFrame):
    if(node["argument"]["type"] == "BinaryExpression"):
        return binaryExpression(node["argument"],stackFrame)
    elif(node["argument"]["type"].find("Literal")):
        return literal(node["argument"],stackFrame)    
    elif(node["argument"]["type"] == "CallExpression"):
        return callExpression(node["argument"],stackFrame)
    elif(node["argument"]["type"] == "Identifier"):
        return get_var_from_stack(stackFrame,node["argument"]["name"])
    elif(node["argument"]["type"].find("Expression")):
        return expressionStatement(node["argument"],stackFrame)
    elif(node["argument"]["type"].find("Statement")):
        return statement(node,stackFrame)


#************************************************************************/
#                             Declarations
#************************************************************************/

def variableDeclaration(node,variables):
    if(node["type"] == "VariableDeclarator"):
        declaration(node,variables)
        print("VariableDeclaration : "+ str(node["id"]["name"]) + " = " + str(variables.get_var(node["id"]["name"])))    

def declaration(node,variables):
    if(node["id"]["type"] == "Identifier"):
        if(not(node.get("init",0))):
            variables.add_var(node["id"]["name"],0)
        else :
            if(node["init"]["type"] == "ObjectExpression"):
                print("Declaration : ObjectExpression")
                objectCreated = {};
                for property in node["init"]["properties"]:
                    objectCreated[property["key"]["value"]] = property["value"]["value"]
                variables.add_var(node["id"]["name"],objectCreated) 
            elif(node["init"]["type"] == "NewExpression"):
                res = {}
                func = get_func_from_stack(variables,node["init"]["callee"]["name"])
                count = 0;
                for param in func["body"]["body"]:
                    name = param["expression"]["left"]["property"]["name"];
                    res[name] = node['init']["arguments"][count]["value"]
                    count += 1
                variables.add_var(node["id"]["name"],res);
            else :
                if(node["init"].get("value")):
                    variables.add_var(node["id"]["name"],node["init"]["value"])
                elif(node["init"].get("name")) :
                    variables.add_var(node["id"]["name"],"\"" + node["init"]["name"] + "\"")
                else :
                    variables.add_var(node["id"]["name"],0)
        

def literal(exp, stackFrame):
    if(exp["type"] == "NumericLiteral"):
        stackFrame.push(exp["value"])
        return exp["value"]
    elif(exp["type"] == "StringLiteral"):
        stackFrame.push(exp["value"])
        return exp["value"]
    elif(exp["type"] == "NullLiteral"):
        stackFrame.push(0)
        return 0
    elif(exp["type"] == "BooleanLiteral"):
        stackFrame.push(exp["value"])
        return exp["value"]
    
def functionDeclaration(node,stackFrame):
    print("FunctionDeclaration : " + str(node["id"]["name"]))   
    stackFrame.add_func(node["id"]["name"],node)

#************************************************************************/
#                               Conditions 
#************************************************************************/

def condition(operator,before,after,stackFrame):
    if(before == None or after == None):
        return False
    beforeRes = conditionGet(before,stackFrame)
    afterRes = conditionGet(after,stackFrame)
    if(operator == "||"):
        if(beforeRes or afterRes):
            return True
    if(operator == "&&"):
        if(beforeRes and afterRes):
            return True
    elif(operator == "<"):
        if(beforeRes < afterRes):
            return True
        else:
            return False
    elif(operator == "<="):
        if(beforeRes <= afterRes):
            return True
        else:
            return False
    elif(operator == ">"):
        if(beforeRes > afterRes):
            return True
        else:
            return False
    elif(operator == ">="):
        if(beforeRes >= afterRes):
            return True
        else:
            return False
    elif(operator == "=="):
        if(beforeRes == afterRes):
            return True
        else:
            return False
    elif(operator == "!="):
        if(not(beforeRes == afterRes)):
            return True
        else:
            return False
    else :
        return False

def conditionGet(node,stackFrame):
        if(node["type"] == "BinaryExpression"):
            return binaryExpression(node,stackFrame)
        elif(node["type"] == "Identifier"): 
            return get_var_from_stack(stackFrame,node["name"])
        elif(node["type"].find("Literal")):
            return literal(node,stackFrame)
        elif(node["type"] == "ExpressionStatement"):
            return expressionStatement(node["expression"],stackFrame)
        elif(node["type"].find("MemberExpression")):
            return memberExpression(node,stackFrame)
        return None 
    
#************************************************************************/
#                               Stack 
#************************************************************************/
    
def get_var_from_stack(callStackFrame,name):
    if(name in callStackFrame.get_variables()):
        return callStackFrame.get_var(name)
    else:
        while(callStackFrame.get_parent()):
           res = get_var_from_stack(callStackFrame.get_parent(),name)
           if(res != None):
               return res
    return None        

def set_var_from_stack(callStackFrame,name,value):
    if(name in callStackFrame.get_variables()):
        callStackFrame.add_var(name,value)
        return 1
    else:
        res = 0
        while(callStackFrame.get_parent()):
           res += set_var_from_stack(callStackFrame.get_parent(),name,value)
    return 0  + res
  

def get_func_from_stack(callStackFrame,name):
    if(name in callStackFrame.get_functions()):
        return callStackFrame.get_func(name)
    else:
        while(callStackFrame.get_parent()):
           res = get_func_from_stack(callStackFrame.get_parent(),name)
           if(res != None):
               return res
    return None              