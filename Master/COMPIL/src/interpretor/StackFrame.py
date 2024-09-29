class StackFrame:

    def __init__(self,name):
        self.stack = []
        self.variables = {}
        self.nb_variables = 0
        self.functions = {}
        self.nb_functions = 0
        self.nb_while = 0
        self.nb_if = 0  
        self.nb_for = 0
        self.parent = None
        self.name = name
        
    def getName(self):
        return self.name
        
    def push(self, value):
        self.stack.append(value)
        
    def length_stack(self):
        return self.stack.__len__()

    def pop(self):
        if(self.stack.__len__() == 0):
            return None
        return self.stack.pop()
    
    def top(self):  
        if(self.stack.__len__() == 0):
            return None 
        return self.stack[-1]
    
    def add_var(self,name,value):
        if(not(name in self.variables)):
            self.nb_variables += 1 
        self.variables[name] = value

    def get_var(self,name):
        return self.variables[name]
    
    def delete_var(self,name):
        del self.functions[name]
        self.nb_functions -= 1
        
    def add_func(self,name,value):
        if(not(name in self.functions)):
            self.nb_variables += 1 
        self.functions[name] = value

    def get_func(self,name):
        return self.functions[name]
    
    def delete_func(self,name):
        del self.functions[name]
        self.nb_functions -= 1

    def add_parent(self,parent):
        self.parent = parent
    
    def get_stack(self):
        return self.stack
    
    def get_variables(self):
        return self.variables
    
    def get_nb_variables(self):
        return self.nb_variables

    def get_functions(self):
        return self.functions
    
    def get_nb_while(self):
        return self.nb_while
    
    def add_nb_while(self):
        self.nb_while += 1
        
    def get_nb_if(self):
        return self.nb_if
    
    def add_nb_if(self):
        self.nb_if += 1
    
    def get_nb_for(self):
        return self.nb_for
    
    def add_nb_for(self):
        self.nb_for += 1

    def get_parent(self):
        return self.parent
    
    def print(stack):
        print(stack.stack)

