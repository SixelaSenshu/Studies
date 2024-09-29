from reader import *
from formula import *

def main():
    print("--------------------------------------------\nTest ex_N0_res10000\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N0_res10000 copie")
    print(findTallerSurface(reader))
    print(PGSD(reader,0,reader.getSize()-1))

    print("--------------------------------------------\nTest ex_N2_res10000\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N2_res10000 copie")
    print(findTallerSurface(reader))
    print(PGSD(reader,0,reader.getSize()-1))
    
    print("--------------------------------------------\nTest ex_N10_res24400144\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N10_res24400144 copie")
    print(findTallerSurface(reader))
    print(PGSD(reader,0,reader.getSize()-1))
    
    print("--------------------------------------------\nTest ex_N100_res6741\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N100_res6741 copie")
    print(findTallerSurface(reader))
    print(PGSD(reader,0,reader.getSize()-1))
    
    print("--------------------------------------------\nTest ex_N500_res7616\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N500_res7616 copie")
    print(findTallerSurface(reader))
    print(PGSD(reader,0,reader.getSize()-1))
    
    print("--------------------------------------------\nTest ex_N500_res7854\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N500_res7854 copie")
    print(findTallerSurface(reader))
    print(PGSD(reader,0,reader.getSize()-1))
    
    print("--------------------------------------------\nTest ex_N100000_res100000\n--------------------------------------------")
    reader = Reader()   
    reader.readFile("TestsTP1/ex_N100000_res100000 copie")
    print(PGSD(reader,0,reader.getSize()-1))
    
    
main()