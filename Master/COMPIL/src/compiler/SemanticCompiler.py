from src.compiler.StackFrame import *

def expressionStatement(exp, compiler,stackFrame, scope):
	if(exp["type"] == "NumericLiteral"):
		numericLiteral(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "BinaryExpression"):
		binaryExpression(exp, compiler,stackFrame, scope)
	elif(exp["type"] == "UpdateExpression"):
		updateExpression(exp,compiler,False,stackFrame, scope)
	elif(exp["type"]  == "CallExpression"):
		callExpression(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "AssignmentExpression"):
		assignementExpression(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "MemberExpression"):
		memberExpression(exp,compiler,False,stackFrame, scope)
	elif(exp["type"] == "LogicalExpression"):
		logicalExpression(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "UnaryExpression"):
		unaryExpression(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "Identifier"):
		identifier(exp,compiler,stackFrame, scope)
		
def identifier(exp,compiler,stackFrame, scope):
	if(compiler.get_stackFrame().get_var_global(exp["name"]) != None):
		compiler.add_code(r"    movl "+exp["name"]+", %eax")
		compiler.add_code(r"    pushq %rax")
		compiler.set_line(exp["name"],compiler.get_code().__len__())
		if(scope == True):
			compiler.set_scope(exp["name"],True)
	elif(get_var_from_stackFrame(stackFrame,exp["name"]) != None):
		compiler.add_code(r"    movl "+str(get_var_from_stackFrame(stackFrame,exp["name"]) * 8) + "(%rsp), %eax")
		compiler.add_code(r"    pushq %rax")
	else:
		compiler.add_code(r"    # ERROR: Variable "+exp["name"]+" not declared")
		compiler.add_code(r"    movl $0, %eax")
		compiler.add_code(r"    pushq %rax")
	
##########################################################################
######
#####                     Expression
######
#########################################################################	
def binaryExpression(exp,compiler,stackFrame, scope):
	isBool = True
	left = exp["left"]
	right = exp["right"]
	operator = exp["operator"]
	if(left["type"] == "BinaryExpression"):
		binaryExpression(left,compiler,stackFrame, scope)
	elif(left["type"] == "NumericLiteral"):
		numericLiteral(left,compiler,stackFrame, scope)
	elif(left["type"] == "UpdateExpression"):
		updateExpression(left,compiler,True,stackFrame, scope)
	elif(left["type"] == "Identifier"):
		arg = ""
		arg2 = ""
		if(compiler.get_stackFrame().get_var_global(left["name"]) != None):
			compiler.set_line(left["name"],compiler.get_code().__len__())
			arg = r"    movl "+left["name"]+r", %eax"
			arg2 = r"    pushq %rax"
		elif(get_var_from_stackFrame(stackFrame,left["name"])  != None):
			arg = r"    movl "+str(get_var_from_stackFrame(stackFrame,left["name"]) * 8) + "(%rsp), %eax"
			arg2 = r"    pushq %rax"
			isBool = False
		if(scope == False):
			compiler.add_code(arg)
			compiler.add_code(arg2)
		else:
			compiler.add_func(arg)
			compiler.add_func(arg2)
	elif (left["type"] == "CallExpression"):
		callExpression(left,compiler,stackFrame, scope)
	if(right["type"] == "BinaryExpression"):
		binaryExpression(right,compiler,stackFrame, scope)
	elif(right["type"] == "NumericLiteral"):
		numericLiteral(right,compiler,stackFrame, scope)
	elif(right["type"] == "UpdateExpression"):
		updateExpression(right,compiler,True,stackFrame, scope)
	elif(right["type"] == "Identifier"):
		if(compiler.get_stackFrame().get_var_global(right["name"]) != None):
			compiler.add_code(r"    movl "+right["name"]+r", %eax")
			compiler.add_code(r"    pushq %rax")
			compiler.set_line(right["name"],compiler.get_code().__len__())
			if(scope == True):
				compiler.set_scope(right["name"],True)
		elif(get_var_from_stackFrame(stackFrame,right["name"])  != None):
			isBool = False
			compiler.add_func(r"    movl "+str(get_var_from_stackFrame(stackFrame,right["name"]) * 8) + "(%rsp), %eax")
			compiler.add_func(r"    pushq %rax")
	elif (right["type"] == "CallExpression"):
		callExpression(right,compiler,stackFrame, scope)
	# Dependence
	if(exp["left"]["type"] == exp["right"]["type"] == "Identifier"):
		if(compiler.get_stackFrame().get_var_global(exp["left"]["name"]) != None):
			if(compiler.get_stackFrame().get_var_global(exp["right"]["name"]) != None):
				compiler.create_dependence(exp["left"]["name"],exp["right"]["name"])

	if(isBool == False):
		compiler.add_func(r"    popq %rax")
		compiler.add_func(r"    popq %rbx")
		if(operator == "+"):
			compiler.add_func(r"    addl %ebx, %eax")
		elif(operator == "-"):
			compiler.add_func(r"    subl %ebx, %eax")
		elif(operator == "*"):
			compiler.add_func(r"    imull %ebx, %eax")
		elif(operator == "/"):
			compiler.add_func(r"    movl %eax, %edx")
			compiler.add_func(r"    idivl %ebx")
		elif(operator == "=="):
			compiler.add_func(r"    cmpl %ebx, %eax")
			compiler.add_func(r"    sete %al")
			compiler.add_func(r"    movzbl %al, %eax")
		compiler.add_func(r"    pushq %rax")
	else:
		compiler.add_code(r"    popq %rax")
		compiler.add_code(r"    popq %rbx")
		if(operator == "+"):
			compiler.add_code(r"    addl %ebx, %eax")
		elif(operator == "-"):
			compiler.add_code(r"    subl %ebx, %eax")
		elif(operator == "*"):
			compiler.add_code(r"    imull %ebx, %eax")
		elif(operator == "/"):
			compiler.add_code(r"    movl %eax, %edx")
			compiler.add_code(r"    idivl %ebx")
		elif(operator == "=="):
			compiler.add_code(r"    cmpl %ebx, %eax")
			compiler.add_code(r"    sete %al")
			compiler.add_code(r"    movzbl %al, %eax")
		compiler.add_code(r"    pushq %rax")

def updateExpression(exp,compiler,push,stackFrame, scope):
	arg = ""
	if(exp["argument"]["type"] == "Identifier"):
		if(compiler.get_stackFrame().get_var_global(exp["argument"]["name"]) != None):
			arg = exp["argument"]["name"]
			compiler.set_line(exp["argument"]["name"],compiler.get_code().__len__())
			if(scope == True):
				compiler.set_scope(exp["argument"]["name"],True)
		elif(get_var_from_stackFrame(stackFrame,exp["argument"]["name"])  != None):
			arg = str(get_var_from_stackFrame(stackFrame,exp["argument"]["name"]) * 8) + "(%rsp)"
	if(exp["operator"] == "++"):
		compiler.add_code(r"    incl " + arg)  
	elif(exp["operator"] == "--"):
		compiler.add_code(r"    decl " + arg)
	if(push):
		compiler.add_code(r"    movl " + arg + ", %eax")
		compiler.add_code(r"    pushq %rax")
	
def assignementExpression(exp,compiler,stackFrame, scope):
	arg = ""

	# Right part
	if(exp["right"]["type"] == "Identifier"):
		if(compiler.get_stackFrame().get_var_global(exp["right"]["name"]) != None):
			arg = exp["right"]["name"]
			compiler.set_line(exp["right"]["name"],compiler.get_code().__len__() + 1)
			if(scope == True):
				compiler.set_scope(exp["right"]["name"],True)
		elif(get_var_from_stackFrame(stackFrame,exp["right"]["name"]) != None):
			arg = str(get_var_from_stackFrame(stackFrame,exp["right"]["name"]) * 8) + "(%rsp)"
	elif(exp["right"]["type"] == "NumericLiteral"):
		arg = ""+str(exp["right"]["value"])
	elif(exp["right"]["type"] == "StringLiteral"):
		arg = ""+str(exp["right"]["value"])
	elif(exp["right"]["type"] == "NullLiteral"):
		arg = "$0"				
	elif(exp["right"]["type"] == "BinaryExpression"):
		binaryExpression(exp["right"],compiler,stackFrame, scope)
		arg = "%eax"
	# Left part
	if(exp["left"]["type"] == "Identifier"):
		if(compiler.get_stackFrame().get_var_global(exp["left"]["name"]) != None):
			argL = str(exp["left"]["name"])
			compiler.set_line(exp["left"]["name"],compiler.get_code().__len__() + 1)
			if(scope == True):
				compiler.set_scope(exp["left"]["name"],True)
		elif(get_var_from_stackFrame(stackFrame,exp["left"]["name"]) != None):
			argL = str(get_var_from_stackFrame(stackFrame,exp["left"]["name"]) * 8) + "(%rsp)"
	elif(exp["left"]["type"] == "MemberExpression"):
		argL = memberExpression(exp["left"],compiler,True,stackFrame, scope)
	else:
		argL = str(exp["left"]["name"])

	# Dependence
	if(exp["left"]["type"] == exp["right"]["type"] == "Identifier"):
		compiler.create_dependence(exp["left"]["name"],exp["right"]["name"])

	if(scope == True): 
		res=compiler.get_var_garbage(exp["left"]["name"])
		if(res["global"] == False):
			compiler.set_line(exp["left"]["name"],compiler.get_code().__len__())
			compiler.set_lastFunction(exp["left"]["name"],compiler.get_stackFrame().getName())
	# Scope 
	if(scope == False):
		if(arg != "%eax"):
			arg = "$" + str(arg)
		if(exp["operator"] == "="):
			compiler.add_code(r"    movl " + str(arg) + ", " + str(exp["left"]["name"]))
		elif(exp["operator"] == "+="):
			compiler.add_code(r"    addl " + str(arg) + ", " + str(exp["left"]["name"]))
		elif(exp["operator"] == "-="):
		    compiler.add_code(r"    subl " + str(arg) + ", " + str(exp["left"]["name"]))
	else:
		if(exp["operator"] == "="):
			compiler.add_func(r"    movl %eax" + ", " + str(argL))
		elif(exp["operator"] == "+="):
			compiler.add_func(r"    addl %eax" + ", " + str(argL))
		elif(exp["operator"] == "-="):
		    compiler.add_func(r"    subl %eax" + ", " + str(argL))
	return 1

def callExpression(exp,compiler,stackFrame, scope):
	new_stackFrame = StackFrame(str(exp["callee"]["name"]))
	new_stackFrame.add_parent(stackFrame)
	if(scope == False):
		if(str(exp["callee"]["name"]) == "print"):
			for arg in exp["arguments"]:  
				if(arg["type"] == "CallExpression"):
					callExpression(arg,compiler,new_stackFrame, scope)
				elif(arg["type"] == "Identifier"):
					compiler.add_code(r"    movl "+arg["name"]+r", %eax")
					compiler.add_code(r"    pushq %rax")
					stackFrame.add_var(arg["name"])  
				elif(arg["type"] == "NumericLiteral"):
					compiler.add_code(r"    movl $"+str(arg["value"])+r",%eax")
					compiler.add_code(r"    pushq %rax")
				elif(arg["type"] == "MemberExpression"):
					memberExpression(arg,compiler,True,stackFrame, scope)
				compiler.add_code(r"    movq %rax, buffer")
				compiler.add_code(r"    call console_log")
		else:
			if(compiler.get_stackFrame().get_func(exp["callee"]["name"]) != 0):
				for arg in exp["arguments"]:
					if(arg["type"] == "CallExpression"):
						callExpression(arg,compiler,new_stackFrame, scope)
					elif(arg["type"] == "Identifier"):
						compiler.add_code(r"    movl "+arg["name"]+r", %eax")
						compiler.add_code(r"    pushq %rax")
						stackFrame.add_var(arg["name"])
					elif(arg["type"] == "NumericLiteral"):
						compiler.add_code(r"    movl $"+str(arg["value"])+r",%eax")
						compiler.add_code(r"    pushq %rax")
					elif(arg["type"] == "MemberExpression"):
						memberExpression(arg,compiler,True,stackFrame, scope)
				compiler.add_code(r"    call "+str(exp["callee"]["name"]))
			else:
				compiler.add_code(r"    #ERROR: Function "+exp["callee"]["name"]+" not declared")
				compiler.add_code(r"    call "+str(exp["callee"]["name"]))
	else:
		if(str(exp["callee"]["name"]) == "print"):
			for arg in exp["arguments"]:  
				if(arg["type"] == "CallExpression"):
					callExpression(arg,compiler,new_stackFrame, scope)
				elif(arg["type"] == "Identifier"):
					compiler.add_func(r"    movl "+arg["name"]+r", %eax")
					compiler.add_func(r"    pushq %rax")
					stackFrame.add_var(arg["name"])  
				elif(arg["type"] == "NumericLiteral"):
					compiler.add_func(r"    movl $"+str(arg["value"])+r",%eax")
					compiler.add_func(r"    pushq %rax")
				elif(arg["type"] == "MemberExpression"):
					memberExpression(arg,compiler,True,stackFrame, scope)
				compiler.add_func(r"    movl %eax, buffer")
				compiler.add_func(r"    call console_log")
		else:
			if(compiler.get_stackFrame().get_func(exp["callee"]["name"]) != 0):
				for arg in exp["arguments"]:
					if(arg["type"] == "CallExpression"):
						callExpression(arg,compiler,new_stackFrame, scope)
					elif(arg["type"] == "Identifier"):
						compiler.add_func(r"    movl "+arg["name"]+r", %eax")
						compiler.add_func(r"    pushq %rax")
						stackFrame.add_var(arg["name"])
					elif(arg["type"] == "NumericLiteral"):
						compiler.add_func(r"    movl $"+str(arg["value"])+r",%eax")
						compiler.add_func(r"    pushq %rax")
					elif(arg["type"] == "MemberExpression"):
						memberExpression(arg,compiler,True,stackFrame, scope)
				compiler.add_func(r"    call "+str(exp["callee"]["name"]))
			else:
				compiler.add_func(r"    #ERROR: Function "+exp["callee"]["name"]+" not declared")
				compiler.add_func(r"    call "+str(exp["callee"]["name"]))				

def memberExpression(exp,compiler,push,stackFrame, scope):
	var_att = ""
	if(exp["object"]["type"] == "NullLiteral"):
		compiler.add_code(r"    #ERROR: Type NullLiteral ")
		compiler.add_code(r"    movl $0,%eax")
		if(push == True):
			compiler.add_code(r"    pushq %rax")
	if(exp["object"]["type"] == "Identifier"):
		compiler.add_code(r"    movl "+ exp['object']['name'] +"_"+exp["property"]["name"] +r",%eax")
		compiler.set_line(exp["object"]["name"],compiler.get_code().__len__())
		if(scope == True):
			compiler.set_scope(exp["object"]["name"],True)
	if(scope == True):
		var_att = exp["property"]["name"]
		if(exp["object"]["type"] == "ThisExpression"):
			compiler.add_func(r"    popq %rax")
			value_rdi = 8 * stackFrame.get_var(exp["property"]["name"])
			var_att = str(value_rdi) + "(%rdi)"
	return var_att

def logicalExpression(exp,compiler,stackFrame, scope):
	if(scope == False):
		if(exp["left"]["type"] == "BooleanLiteral"):
			literal(exp["left"],compiler,stackFrame, scope)
		elif(exp["left"]["type"] == "MemberExpression"):
			memberExpression(exp["left"],compiler,True,stackFrame, scope)
		elif(exp["right"]["type"] == "BooleanLiteral"):
			literal(exp["right"],compiler,stackFrame, scope)	
		elif(exp["right"]["type"] == "MemberExpression"):
			memberExpression(exp["right"],compiler,True,stackFrame, scope)	
		elif(exp["right"]["type"] == "BinaryExpression"):
			binaryExpression(exp["right"],compiler,stackFrame, scope)
		if(exp["operator"] == "&&"):
			compiler.add_code(r"    popq %rax")
			compiler.add_code(r"    popq %rbx")
			compiler.add_code(r"    andl %ebx, %eax")
			compiler.add_code(r"    pushq %rax")
		elif(exp["operator"] == "||"):
			compiler.add_code(r"    popq %rax")
			compiler.add_code(r"    popq %rbx")
			compiler.add_code(r"    orl %ebx, %eax")
			compiler.add_code(r"    pushq %rax")
	else:
		if(exp["left"]["type"] == "BooleanLiteral"):
			literal(exp["left"],compiler,stackFrame, scope)
		elif(exp["left"]["type"] == "MemberExpression"):
			memberExpression(exp["left"],compiler,True,stackFrame, scope)
		elif(exp["right"]["type"] == "BooleanLiteral"):
			literal(exp["right"],compiler,stackFrame, scope)	
		elif(exp["right"]["type"] == "MemberExpression"):
			memberExpression(exp["right"],compiler,True,stackFrame, scope)
		elif(exp["right"]["type"] == "BinaryExpression"):
			binaryExpression(exp["right"],compiler,stackFrame, scope)
		if(exp["operator"] == "&&"):
			compiler.add_func(r"    popq %rax")
			compiler.add_func(r"    popq %rbx")
			compiler.add_func(r"    andl %ebx, %eax")
			compiler.add_func(r"    pushq %rax")
		elif(exp["operator"] == "||"):
			compiler.add_func(r"    popq %rax")
			compiler.add_func(r"    popq %rbx")
			compiler.add_func(r"    orl %ebx, %eax")
			compiler.add_func(r"    pushq %rax")
	return 1	

def unaryExpression(exp,compiler,stackFrame, scope):
	return 1

##########################################################################
######
#####                     Variables
######
#########################################################################
		
def variableDeclaration(exp,compiler,stackFrame, scope):
	for var in exp["declarations"]:
		if(var["type"] == "VariableDeclarator"):
			variableDeclarator(var,compiler,stackFrame, scope)
	
def variableDeclarator(exp,compiler,stackFrame, scope):
	if(exp["id"]["type"] == "Identifier"):
		identifierVar(exp,compiler,stackFrame, scope)
			
def identifierVar(exp,compiler,stackFrame, scope):
	init = exp.get("init")
	if(init != None):
		if(exp["init"]["type"] == "NumericLiteral"):
			compiler.add_var(r""+str(exp["id"]["name"] + ":"))
			compiler.add_var(r"    .long " + str(exp["init"]["value"]))
			compiler.get_stackFrame().add_var_global(str(exp["id"]["name"]))
			compiler.create_var_garbage(exp["id"]["name"],-1)
			compiler.set_type(exp["id"]["name"],"Var")
		elif(exp["init"]["type"] == "StringLiteral"):
			compiler.add_var(r""+str(exp["id"]["name"] + ":"))
			compiler.add_var(r"    .string "+ "\"" + str(exp["init"]["value"])+ "\"")
			compiler.get_stackFrame().add_var_global(str(exp["id"]["name"]))
			compiler.set_line(exp["id"]["name"],compiler.get_code().__len__())
			compiler.create_var_garbage(exp["id"]["name"],-1)
			compiler.set_type(exp["id"]["name"],"Var")
		elif(exp["init"]["type"] == "NullLiteral"):
			compiler.add_var(r""+str(exp["id"]["name"] + ":"))
			compiler.add_var(r"    .long "+ str(0))
			compiler.get_stackFrame().add_var_global(str(exp["id"]["name"]))
			compiler.create_var_garbage(exp["id"]["name"],-1)
			compiler.set_type(exp["id"]["name"],"Var")
		elif(exp["init"]["type"] == "ObjectExpression"):
			compiler.add_var(r""+str(exp["id"]["name"] + ":"))
			for param in exp["init"]["properties"]:
				compiler.add_var("    "+exp["id"]["name"]+"_"+param["key"]["value"]+ ":")
				if(param["value"]["type"] == "NumericLiteral"):
					compiler.add_var(r"      .long "+ str(param["value"]["value"]))
				elif(param["value"]["type"] == "StringLiteral"):
					compiler.add_var(r"      .string "+ "\"" + str(param["value"]["value"])+ "\"")
				elif(param["value"]["type"] == "NullLiteral"):
					compiler.add_var(r"      .long "+ str(0))
			compiler.get_stackFrame().add_var_global(str(exp["id"]["name"]+"_"+param["key"]["value"]))
			compiler.create_var_garbage(str(exp["id"]["name"]),-1)
			compiler.set_type(exp["id"]["name"],"Object")
		elif(exp["init"]["type"] == "NewExpression"):
			count = 0
			argString = []
			for param in exp["init"]["arguments"]:
				if(param["type"] == "NumericLiteral"):
					compiler.add_code(r"    movl $"+str(param["value"])+r", %eax")
				elif(param["type"] == "StringLiteral"):
					argString.append(exp["id"]["name"] + "_string" + str(count) + ":")
					argString.append("      .string \""+param["value"]+"\"")
					compiler.add_code(r"    movl " + exp["id"]["name"] + "_string" + str(count) +  r", %eax")
				elif(param["type"] == "NullLiteral"):
					compiler.add_code(r"    movl $"+str(param["value"])+r", %eax")
				count += 1
				compiler.add_code(r"    pushq %rax")
			for arg in argString:
				compiler.add_var(arg)
			compiler.add_pts(str(exp["id"]["name"]) + r": .skip " + str( 8 + 8 * count))
			compiler.get_stackFrame().add_var_global(str(exp["id"]["name"]+"_"+param["value"]))
			compiler.add_code(r"    movq " + exp["id"]["name"]+ r",%rdi")
			compiler.add_code(r"    call "+str(exp["init"]["callee"]["name"]))
			compiler.set_type(exp["id"]["name"],"Object")

		if(scope == True):
			compiler.set_global(exp["id"]["name"],False)
			compiler.set_line(exp["id"]["name"],compiler.get_code().__len__())
	else:
		compiler.add_var(r""+str(exp["id"]["name"] + ":"))
		compiler.add_var(r"    .long "+ str(0))
		compiler.get_stackFrame().add_var_global(str(exp["id"]["name"]))
	
def literal(exp,compiler,stackFrame, scope):
	if(exp["type"] == "NumericLiteral"):
		numericLiteral(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "StringLiteral"):
		stringLiteral(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "NullLiteral"):
		nullLiteral(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "BooleanLiteral"):
		booleanLiteral(exp,compiler,stackFrame, scope)
		
def numericLiteral(exp,compiler,stackFrame, scope):
	value = exp["value"]
	if(scope == False):
		compiler.add_code(r"    movl $"+str(value)+r",%eax")

		compiler.add_code(r"    pushq %rax")
	else:
		compiler.add_func(r"    movl $"+str(value)+r",%eax")
		compiler.add_func(r"    pushq %rax")
	
def stringLiteral(exp,compiler,stackFrame, scope):
	if(scope == False):
		compiler.add_code(r"    movl $"+str(exp["value"])+r",%eax")
		compiler.add_code(r"    pushq %rax")
	else:
		compiler.add_func(r"    movl $"+str(exp["value"])+r",%eax")
		compiler.add_func(r"    pushq %rax")

def nullLiteral(exp,compiler,stackFrame, scope):
	if(scope == False):
		compiler.add_code(r"    movl $0,%eax")
		compiler.add_code(r"    pushq %rax")
	else:
		compiler.add_func(r"    movl $0,%eax")
		compiler.add_func(r"    pushq %rax")

def booleanLiteral(exp,compiler,stackFrame, scope):
	if(exp["value"] == "true"):
		compiler.add_code(r"    movl $1,%eax")
		compiler.add_code(r"    pushq %rax")
	elif(exp["value"] == "false"):
		compiler.add_code(r"    movl $0,%eax")
		compiler.add_code(r"    pushq %rax")
		
def functionDeclaration(exp,compiler,stackFrame, scope):
	if(compiler.get_stackFrame().get_func(exp["id"]["name"]) == 0):
		compiler.get_stackFrame().add_func(exp["id"]["name"],1)
		compiler.add_func("")
		compiler.add_func(exp["id"]["name"]+r":")
		compiler.add_func(r"    pushq %rbp")
		compiler.add_func(r"    movl %esp, %ebp")
		compiler.add_var(r""+str(var["name"] + ":"))
		for var in exp["params"]:
			if(var["type"] == "StringLiteral"):
				compiler.add_var(r"    .string "+ str(0))
			elif(var["type"] == "NumericLiteral"):
				compiler.add_var(r"    .long "+ str(0))
		for var in exp["params"] :
			compiler.get_stackFrame().add_var(var["name"])
		blockStatement(exp["body"],compiler,compiler.get_stackFrame(), True)
		for var in exp["params"]:
			compiler.get_stackFrame().delete_var(var["name"])
		compiler.add_func(r"    popq %rbp")
		compiler.add_func(r"    ret")
		compiler.add_func(r"")
	else:
		compiler.del_function(exp["id"]["name"])
		compiler.add_func(r"")
		compiler.add_func(exp["id"]["name"]+r":")
		compiler.add_func(r"    pushq %rbp")
		compiler.add_func(r"    movq %rsp, %rbp")
		for var in exp["params"] :
			compiler.get_stackFrame().add_var(var["name"])
		blockStatement(exp["body"],compiler,compiler.get_stackFrame(), True)
		for var in exp["params"]:
			compiler.get_stackFrame().delete_var(var["name"])
		compiler.add_func(r"    popq %rbp")
		compiler.add_func(r"    ret")
		compiler.add_func(r"")
	for var in stackFrame.get_vars():
		if(compiler.get_var_garbage(var) != None):
			if(compiler.get_global(var) == False):
				compiler.set_lastFunction(var,exp["id"]["name"])
			
		# if(compiler.get_global(var) == False):
		# compiler.get_global(var["name"])
	return 1
		
##########################################################################
######
#####                     Statement
######
#########################################################################

def statement(exp,compiler,stackFrame, scope):
	if(exp["type"] == "VariableDeclaration"):
		variableDeclaration(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "FunctionDeclaration"):
		functionDeclaration(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "ExpressionStatement"):
		expressionStatement(exp["expression"],compiler,stackFrame, scope)
	elif(exp["type"] == "IfStatement"):
		ifStatement(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "WhileStatement"):
		whileStatement(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "ForStatement"):
		forStatement(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "ReturnStatement"):
		returnStatement(exp,compiler,stackFrame, scope)
	elif(exp["type"] == "BreakStatement"):
		breakStatement(exp,compiler,stackFrame, scope)
		
def ifStatement(exp,compiler,stackFrame, scope):
	stackFrame.add_nb_if()
	linedeb = compiler.get_code().__len__()
	begin_label= str(stackFrame.getName())+"_IF_"+ str(stackFrame.get_nb_if())
	if_label=str(stackFrame.getName())+"_IF_CONS_"+ str(stackFrame.get_nb_if())
	else_label=str(stackFrame.getName())+"_ELSE_CONS_"+ str(stackFrame.get_nb_if())
	end_label=str(stackFrame.getName())+"_IF_END_"+ str(stackFrame.get_nb_if())
	argL = giveArgumentCond(exp["test"]["left"],compiler,"%ebx",stackFrame, scope)
	argR = giveArgumentCond(exp["test"]["right"],compiler,"%ecx",stackFrame, scope)
	if(scope == True):
		compiler.add_func(begin_label + ":")
		condition(exp["test"],compiler,if_label,argL,argR,stackFrame, scope)
		compiler.add_func(r"    jmp "+else_label)
		compiler.add_func(if_label + ":")
		blockStatement(exp["consequent"],compiler,stackFrame, scope)
		compiler.add_func(r"    jmp "+end_label)
		compiler.add_func(else_label + ":") 
		alternate = exp["alternate"]
		if(alternate != None):
			blockStatement(exp["alternate"],compiler,stackFrame, scope)
		compiler.add_func(end_label + ":\n")
	else:
		compiler.add_code(begin_label + ":")
		condition(exp["test"],compiler,if_label,argL,argR,stackFrame, scope)
		compiler.add_code(r"    jmp "+else_label)
		compiler.add_code(if_label + ":")
		blockStatement(exp["consequent"],compiler,stackFrame, scope)
		compiler.add_code(r"    jmp "+end_label)
		compiler.add_code(else_label + ":") 
		alternate = exp["alternate"]
		if(alternate != None):
			blockStatement(exp["alternate"],compiler,stackFrame, scope)
		compiler.add_code(end_label + ":\n")
	garbage = compiler.get_garbage()
	lastline = compiler.get_code().__len__()
	compiler.add_statement(begin_label,linedeb,lastline)
		
		   
def whileStatement(exp,compiler,stackFrame, scope):
	stackFrame.add_nb_while()
	linedeb = compiler.get_code().__len__()
	begin_label= str(stackFrame.getName())+"_WHILE_"+ str(compiler.get_stackFrame().get_nb_while())
	end_label=str(stackFrame.getName())+"_WHILE_END_"+ str(compiler.get_stackFrame().get_nb_while())
	compiler.add_last_label(end_label)
	test = exp["test"]
	compiler.add_code(begin_label + ":")
	argR = giveArgumentCond(exp["test"]["right"],compiler,"%ebx",stackFrame, scope)
	argL = giveArgumentCond(exp["test"]["left"],compiler,"%ecx",stackFrame, scope)
	condition(exp["test"],compiler,end_label,argL,argR,stackFrame, scope)
	blockStatement(exp["body"],compiler,stackFrame, scope)
	compiler.add_code(r"    jmp "+begin_label)
	compiler.add_code(end_label + ":\n")
	garbage = compiler.get_garbage()
	lastline = compiler.get_code().__len__()
	compiler.add_statement(begin_label,linedeb,lastline)


def forStatement(exp,compiler,stackFrame, scope): 
	stackFrame.add_nb_for()
	linedeb = compiler.get_code().__len__()
	begin_label= str(stackFrame.getName())+"_FOR_"+ str(stackFrame.get_nb_for())
	end_label=str(stackFrame.getName())+"_FOR_END_"+ str(stackFrame.get_nb_for())
	compiler.add_last_label(end_label)
	if(exp["init"] != None):
		type = exp["init"]["type"]
		if(type == "ExpressionStatement"):
			expressionStatement(exp["init"]["expression"],compiler,stackFrame, scope)
	test = exp["test"]
	compiler.add_code(begin_label + ":")
	argR = giveArgumentCond(exp["test"]["right"],compiler,"%ebx",stackFrame, scope)
	argL = giveArgumentCond(exp["test"]["left"],compiler,"%ecx",stackFrame, scope)  
	condition(exp["test"],compiler,end_label,argL,argR,stackFrame, scope)
	blockStatement(exp["body"],compiler,stackFrame, scope)
	expressionStatement(exp["update"],compiler,stackFrame, scope)
	compiler.add_code(r"    jmp "+begin_label)
	compiler.add_code(end_label + ":\n")
	garbage = compiler.get_garbage()
	lastline = compiler.get_code().__len__()
	compiler.add_statement(begin_label,linedeb,lastline)

def returnStatement(exp,compiler,stackFrame, scope):
	if(exp["argument"]["type"] == "Identifier"):
		arg = ""
		if(stackFrame.get_var_global(exp["argument"]["name"]) != None):
			arg = exp["argument"]["name"]
		elif(get_var_from_stackFrame(stackFrame,exp["argument"]["name"])  != None):
			arg = str(get_var_from_stackFrame(stackFrame,exp["argument"]["name"]) * 8) + "(%rsp)"
		if(scope == False):
			compiler.add_code(r"    popq %rax")
			compiler.add_code(r"    movl "+arg+", %eax")
		else:
			compiler.add_func(r"    popq %rax")
			compiler.add_func(r"    movl "+arg+", %eax")
	elif(exp["argument"]["type"] == "NumericLiteral"):
		if(scope == False):
			compiler.add_code(r"    movl $"+str(exp["argument"]["value"])+", %eax")
		else:
			compiler.add_func(r"    movl $"+str(exp["argument"]["value"])+", %eax")
			compiler.add_func(r"    popq %rbp")
			compiler.add_func(r"    ret")
	elif(exp["argument"]["type"] == "BinaryExpression"):
		if(scope == False):
			binaryExpression(exp["argument"],compiler,stackFrame, scope)
			compiler.add_code(r"    popq %rax")
		else:
			binaryExpression(exp["argument"],compiler,stackFrame, scope)
			compiler.add_func(r"    popq %rax")
			
def breakStatement(exp,compiler,stackFrame, scope):
	compiler.add_code(r"    jmp "+compiler.get_last_label())

		
##########################################################################
######
#####                     Utils
######
#########################################################################
 
def giveArgumentCond(exp, compiler, register,stackFrame, scope):
	arg = register
	if scope == False:
		if exp["type"] == "Identifier":
			if compiler.get_stackFrame().get_var_global(exp['name']) != None:
				compiler.add_code(r"    movl "+ exp['name'] +", " +register)
				compiler.set_line(exp["name"],compiler.get_code().__len__())
				if(scope == True):
					compiler.set_scope(exp["name"],True)
			elif get_var_from_stackFrame(stackFrame,exp['name']) != None:
				compiler.add_code(r"    movl "+ str(get_var_from_stackFrame(stackFrame,exp['name']) * 8) + "(%rsp), " +register)
		elif exp["type"] == "NumericLiteral":
			compiler.add_code(r"    movl $"+ str(exp['value'])+", " + register)
		elif exp["type"] == "BinaryExpression":
			binaryExpression(exp,compiler,stackFrame, scope)
		return arg
	else:
		if exp["type"] == "Identifier":
			if compiler.get_stackFrame().get_var_global(exp['name']) != None:
				compiler.add_func(r"    movl "+ exp['name'] +", " +register)
			elif get_var_from_stackFrame(stackFrame,exp['name']) != None:
				compiler.add_func(r"    movl "+ str(get_var_from_stackFrame(stackFrame,exp['name']) * 8) + "(%rsp), " +register)
		elif exp["type"] == "NumericLiteral":
			compiler.add_func(r"    movl $"+ str(exp['value'])+", " + register)
		elif exp["type"] == "BinaryExpression":
			binaryExpression(exp,compiler,stackFrame, scope)
			compiler.add_func(r"    popq %rax")
			compiler.add_func(r"    movl %eax," + arg)
		return arg
	

def blockStatement(exp,compiler,stackFrame, scope):
	for block in exp["body"]:
		if(block["type"] == "ExpressionStatement"):
			expressionStatement(block["expression"],compiler,stackFrame, scope)
		else:
			statement(block,compiler,stackFrame, scope)


def condition(test,compiler,label,argL,argR,stackFrame, scope):
	if(scope == False):
		compiler.add_code(r"    cmpl "+argL+","+argR)
		if(test["operator"] == "<="):
			compiler.add_code(r"    jge "+ " " +label)
		elif(test["operator"] == ">="):
			compiler.add_code(r"    jle "+" " +label)
		elif(test["operator"] == "=="):
			compiler.add_code(r"    je "+" " +label)
		elif(test["operator"] == "!="):
			compiler.add_code(r"    jne"+" " +label)
		elif(test["operator"] == "<"):
			compiler.add_code(r"    jl"+" " +label)
		elif(test["operator"] == ">"):
			compiler.add_code(r"    jg "+" " +label)
	else:
		if(test["operator"] == "<="):
			compiler.add_func(r"    cmpl %ebx, %ecx")
			compiler.add_func(r"    jge "+ " " +label)
		elif(test["operator"] == ">="):
			compiler.add_func(r"    cmpl %ebx, %ecx")
			compiler.add_func(r"    jle "+" " +label)
		elif(test["operator"] == "=="):
			compiler.add_func(r"    cmpl %ebx, %ecx")
			compiler.add_func(r"    je "+" " +label)
		elif(test["operator"] == "!="):
			compiler.add_func(r"    cmpl %ebx, %ecx")
			compiler.add_func(r"    jne"+" " +label)
		elif(test["operator"] == "<"):
			compiler.add_func(r"    cmpl %ebx, %ecx")
			compiler.add_func(r"    jl"+" " +label)
		elif(test["operator"] == ">"):
			compiler.add_func(r"    cmpl %ebx, %ecx")
			compiler.add_func(r"    jg "+" " +label)
		elif(test["operator"] == "||"):
			compiler.add_func(r"    orl %ebx, %ecx")
			compiler.add_func(r"    cmpl $1, %ecx")
			compiler.add_func(r"    je"+" " + label)


def conditionBoucle(test,compiler,label,argL,argR,stackFrame, scope):
	if scope == False:
		compiler.add_code(r"    cmpl "+argL+","+argR)
		if(test["operator"] == "<="):
			compiler.add_code(r"    jle "+ " " +label)
		elif(test["operator"] == ">="):
			compiler.add_code(r"    jge "+" " +label)
		elif(test["operator"] == "=="):
			compiler.add_code(r"    je "+" " +label)
		elif(test["operator"] == "!="):
			compiler.add_code(r"    jne"+" " +label)
		elif(test["operator"] == "<"):
			compiler.add_code(r"    jg"+" " +label)
		elif(test["operator"] == ">"):
			compiler.add_code(r"    jl "+" " +label)
	else:
		compiler.add_func(r"    cmpl %ebx, %ecx")
		if(test["operator"] == "<="):
			compiler.add_func(r"    jle "+ " " +label)
		elif(test["operator"] == ">="):
			compiler.add_func(r"    jge "+" " +label)
		elif(test["operator"] == "=="):
			compiler.add_func(r"    je "+" " +label)
		elif(test["operator"] == "!="):
			compiler.add_func(r"    jne"+" " +label)
		elif(test["operator"] == "<"):
			compiler.add_func(r"    jg"+" " +label)
		elif(test["operator"] == ">"):
			compiler.add_func(r"    jl "+" " +label)
  

def get_var_from_stackFrame(stackframe,name):
	if(stackframe.get_var(name) != None):
		return stackframe.get_var(name)
	if(stackframe.get_parent() != None):
		return get_var_from_stackFrame(stackframe.get_parent(),name)
	return None

def set_var_from_stackFrame(stackframe,name,value):
	if(stackframe.get_var(name) != None):
		stackframe.set_var(name,value)
	if(stackframe.get_parent() != None):
		set_var_from_stackFrame(stackframe.get_parent(),name,value)
	return None

