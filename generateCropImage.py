from PIL import Image
from PIL import ImageDraw
from PIL import ImageStat

import os.path
import sys
import numpy as np
import random
import glob

#C:/dev/caffe/caffe-windows/data/xr crop30 30 15
args = sys.argv
directory = "C:/dev/caffe/caffe-windows/data/mytest";
newFolder = args[1]
size = int(args[2]) #30
stride = int(args[3]) #15
trimThreshold = 5


def cropImage(dir):
    newDir = dir + "/" + newFolder
    if os.path.exists(newDir) == False:
        os.mkdir(newDir)
    if os.path.exists(newDir +"/binary") == False:
        os.mkdir(newDir +"/binary")
    if os.path.exists(newDir +"/answer") == False:
        os.mkdir(newDir +"/answer")
    number = 1
    files = glob.glob(dir + "/label/*.bmp")

    hit = 0

    for file in files:

        filename = os.path.basename(file)
        name, ext = os.path.splitext(filename)

        fp = open(dir + '/answer/' + name + ".txt", 'w')

        labelImage = Image.open(dir + "/label/" + filename)
        dataImage = Image.open(dir + "/data/" + filename)
        width, height = labelImage.size


        for j in range(0, height, stride):
            if j+size >= height:
                continue
            for k in range(0, width, stride):
                if k+size >= width:
                    break
                box = (k,j,k+size, j+size)

                cropLabel = labelImage.crop(box)
                cropData = dataImage.crop(box)

                flag = 0
                cnt = len([x for x in cropLabel.getdata() if x != 0])
                if cnt >= trimThreshold: 
                    flag = 1

                newImage = "x"+str(k).zfill(3)+"y"+str(j).zfill(3)+  ".bmp"
                fp.write(newImage + ' ' + str(flag) + "\n")
                cropData.save(newDir + '/' + newImage)
                cropLabel.save(newDir + "/binary/" + newImage)
                number+=1
        fp.close()
        print name, ".txt created"



    
    
cropImage(directory)