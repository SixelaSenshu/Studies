from src.compiler.SemanticCompiler import *   
from src.compiler.StackFrame import * 
class Compiler:
	def __init__(self):
		self.code = [] 
		self.data = []
		self.garbage = {}
		self.functions = []
		self.statement = {}
		self.pointers = []
		self.program = []
		self.stackFrame = StackFrame("main")
		self.last_label = []
		
	def compileProgram(self,program):
		program = program["program"]
		body = program["body"]
		stackFrame = self.get_stackFrame()
		for exp in body:
			type = exp["type"]
			if(type == "ExpressionStatement"):
				expressionStatement(exp["expression"],self,stackFrame,False)
				self.code.append("")
			else:
				statement(exp,self,stackFrame,False)

		## add Free
		## check global
		for key in self.garbage:
			if(self.garbage[key]["Type"] == "Var" and self.garbage[key]["global"] == True):
				self.garbage[key]["line"] = self.code.__len__()
		for key in self.garbage:
			if(self.garbage[key]["global"] == False):
				res = self.searchFunctionInCode(self.garbage[key]["lastFunction"])
				self.garbage[key]["line"] = res + 1
		for key in self.garbage:
			self.checkEscapeWithLabel(key)
		for key in self.garbage:
			if self.garbage[key]["isEscape"] == False:
				pos = self.garbage[key]["line"]
				if pos == -1:
					pos = 0
				for keyres in self.garbage:
					poscmp = self.garbage[keyres]["line"]
					if poscmp > pos and key != keyres:
						self.set_line(keyres,poscmp + 1)
				string = ["    # free(" + str(key) + ")"]
				self.code = self.code[0:pos] + string + self.code[pos:]
		## add data
		self.add_print()
		if(self.data.__len__() != 0):
			self.data = [r".section .data"] + self.data
		for data in self.data:
			self.program.append(data)
		self.program.append(r"")
		
		## add data malloc
		if(self.pointers.__len__() != 0):
			self.pointers = [r".section .bss"] + self.pointers
		for pts_arg in self.pointers:
			self.program.append(pts_arg)
		self.program.append(r"")

		## add function
		self.program.append(r".section .text")
		self.program.append(r".global main")
		for function in self.functions:
			self.program.append(function)

		## add code
		self.code = [r"",r"main:"] + self.code
		for code in self.code:
			self.program.append(code)
		self.add_end()
		res = self.string_garbage()
		fileName = open("garbage.txt", "a")
		for line in res:
			fileName.write(line + "\n")
		fileName.close()
		return self.program
					
	def get_code(self):
		return self.code
	
	def add_code(self,exp):
		self.code.append(exp)

	def get_pts(self):
		return self.pointers
	
	def add_pts(self,exp):
		self.pointers.append(exp)
		
	def get_var(self):
		return self.data
	def add_var(self,exp):
		self.data.append(exp)
	
	def get_func(self):
		return self.functions
	def get_last_label(self):
		if(self.last_label.__len__() == 0):
			return None
		return self.last_label[-1]
	def add_last_label(self,label):
		self.last_label = self.last_label + [label]	
		
	def add_func(self,exp):
		self.functions.append(exp)
	def del_function(self,name):
		for i in range(self.functions.__len__()):
			if(name in self.functions[i]):
				while(self.functions[i] != r"    ret"):
					self.functions.pop(i)
				self.functions.pop(i)
				break
		return self.functions
	def get_stackFrame(self):
		return self.stackFrame
		
	def add_end(self):
		self.program.append(r"    movl $60, %eax")
		self.program.append(r"    xor %edi, %edi")
		self.program.append(r"    syscall")
			
	def add_print(self):
		self.add_var(r"buffer:")
		self.add_var(r"    .asciz "+ "\n")
		self.add_var(r"len:")
		self.add_var(r"    .long 32")
		self.add_func(r"")
		self.add_func(r"console_log:")
		self.add_func(r"    movq $1, %rax")
		self.add_func(r"    movq $1, %rdi")
		self.add_func(r"    movq buffer, %rsi")
		self.add_func(r"    movq $len, %rdx")
		self.add_func(r"    syscall")
		self.add_func(r"    ret")

	def create_var_garbage(self,name, lineExpr):
		self.garbage[name] = {"line": lineExpr,"isEscape" : False,"scope" : 0,	 "depended": [],"Type": "null","global": True, "lastFunction" : "main"}
	
	def remove_var_garbage(self,name):
		self.garbage.pop(name)

	def get_var_garbage(self,name):
		if name not in self.garbage:
			return None
		return self.garbage[name]

	def set_type(self, name, typename):
		self.garbage[name]["Type"] = typename

	def get_type(self, name):
		return self.garbage[name]["Type"]

	def set_lastFunction(self, name, lastFunction):
		self.garbage[name]["lastFunction"] = lastFunction
	
	def get_lastFunction(self, name):
		return self.garbage[name]["lastFunction"]

	def set_global(self, name, glob):
		self.garbage[name]["global"] = glob
	
	def get_global(self, name):
		return self.garbage[name]["global"]

	def set_line(self, name, line):
		self.garbage[name]["line"] = line

	def get_line(self, name):
		return self.garbage[name]["line"]

	def create_dependence(self, name, dependence):
		self.garbage[name]["depended"].append(dependence)

	def remove_dependence(self, name, dependence):
		self.garbage[name]["depended"].remove(dependence)

	def get_dependences(self, name):
		return self.garbage[name]["depended"]

	def isAvailable(self, name, dependence):
		if dependence in self.garbage[name]["depended"]:
			return True
		return False

	def checkIfVarFreeable(self, name):
		if self.garbage[name]["depended"].__len__() == 0:
			return True
		return False

	def add_dependences(self, name, dependences):
		for dependence in dependences:
			if get_var_garbage(dependence) == None:
				self.create_var_garbage(dependence,"")
			if dependence not in self.garbage[name]["depended"]:
				self.garbage[name]["depended"].append(dependence)

	def can_be_free(self, name):
		if self.garbage[name]["isEscape"] == False:
			return True
		return False

	def set_escape(self, name):
		self.garbage[name]["isEscape"] = True
	
	def set_scope(self, name,value):
		if(value == True):
			self.garbage[name]["scope"] += 1
		else:
			self.garbage[name]["scope"] -= 1

	def get_scope(self, name):
		return self.garbage[name]["scope"]

	def get_garbage(self):
		return self.garbage

	def string_garbage(self):
		listString = []
		for key in self.garbage:
			listString.append(key + " : " + str(self.garbage[key]))
		return listString

	def get_line_statement(self,statement):
		return self.statement[statement]
	
	def set_line_statement(self,statement,linedeb,lineend):
		self.statement[statement] = [str(linedeb),str(lineend)]

	def add_statement(self,statement,linedeb,lineend):
		self.statement[statement] = [str(linedeb),str(lineend)]

	def checkEscapeWithLabel(self, name):
		if self.garbage[name]["isEscape"] == False:
			for state in self.statement:
				debState = int(self.get_line_statement(state)[0])
				endState = int(self.get_line_statement(state)[1])
				lineVar = self.get_line(name)
				if debState <= lineVar and endState >= lineVar:
					self.set_line(name, endState)
		
	def searchFunctionInCode(self, name):
		count = -1
		res = -1
		for code in self.code:
			count += 1
			if name in code:
				res = count
		return res