#!/usr/bin/python
# -*- coding: utf-8 -*-
from reader import *


def getAbs(x, x2):
    return abs(x - x2)


## Valide 
def findTallerSurface(reader):
    maxSurface = -1
    if reader.getSize() == 0:
        return reader.height * reader.width
    for i in range(reader.getSize()):
        xStart = reader.listsOfPoints[i][0] 
        minHeight = reader.height
        surface = 0
        for j in range(i + 1, reader.getSize()):
            xEnd = reader.listsOfPoints[j][0]  # l
            yEnd = reader.listsOfPoints[j][1]  # h
            l = getAbs(xStart, xEnd)
            if j == i + 1 :
                h = reader.height
                surface = l * h
                if surface > maxSurface:
                    maxSurface = surface
                minHeight = yEnd
            else:
                h = minHeight
                if yEnd <= minHeight:
                    minHeight = yEnd
                    surface = l * h
                    if(surface > maxSurface):
                        maxSurface = surface
    return maxSurface

def PGSD(reader,first,end):
    reader.nbOfPoints += 2
    if not((0,0) in reader.listsOfPoints):
        reader.nbOfPoints += 1
        reader.listsOfPoints = [(0,0)] + reader.listsOfPoints 
    if not((reader.width,reader.height) in reader.listsOfPoints):
        reader.nbOfPoints += 1
        reader.listsOfPoints = reader.listsOfPoints + [(reader.width,reader.height)]
    # print(reader.listsOfPoints)
    return PGSD_prep(reader, first, len(reader.listsOfPoints) -1,reader.width)

def PGSD_prep(reader, first, end,currentWidth):
    minh = reader.height
    pos = -1
    if len(reader.listsOfPoints) == 0: 
        return reader.height * reader.width
    if(end - first ==  1):
        value = getAbs(reader.listsOfPoints[first][0],reader.listsOfPoints[end][0])
        return value * reader.height
    for i in range(first, end, 1):
        if reader.listsOfPoints[i][1] <= minh:
            minh = reader.listsOfPoints[i][1]
            pos = i
    if(pos == first):
        return max(PGSD_prep(reader,first+1,end,reader.listsOfPoints[first+1][0]),(currentWidth - reader.listsOfPoints[first][0])* reader.listsOfPoints[first][1])
    elif(pos == end):
        return max(PGSD_prep(reader,first,end -1,currentWidth),(currentWidth - reader.listsOfPoints[first][0]) * reader.listsOfPoints[end][1])
    else:
        value = getAbs(reader.listsOfPoints[first][0],reader.listsOfPoints[end][0])
        return max(PGSD_prep(reader,first,pos,currentWidth), PGSD_prep(reader,pos,end,reader.listsOfPoints[pos][0]),value * reader.listsOfPoints[pos][1])

    