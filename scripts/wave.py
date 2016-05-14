#
#     wave.py
#
#     author: ale.luca.asoni@gmail.com
#

import numpy as np
import matplotlib.colors
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.animation as ani
import scipy.ndimage
import os
import time
import sys

#global parameters

#plot data
X = np.zeros(0)
Y = np.zeros(0)
Z = np.zeros(0)
n = m = 0

#plot window
xlow = xhig = ylow = yhig = 0

#param to determine every
#how many frames to capture video
plotInterval= 1
steps = 0

#movie params
movieFileName = ""

#read parameter file
def readParamFile(fileName):
    deltaX = deltaY = 0
    global xlow, xhig, ylow, yhig, n, m
    global plotInterval, steps
    global movieFileName

    f = open(fileName,'r')
    lines = f.readlines()
    for line in lines:
        if line[0:2] == '//' or line.rstrip() == '':
            continue #ignore comments and empty lines

        (param,value) = line.rstrip().split(':')
        if param.rstrip() == "MOVIE_FILE_NAME":
            movieFileName = value
        elif param.rstrip() == "STEPS":
            steps = int(value)
        elif param.rstrip() == "X_LOW":
            xlow = float(value)
        elif param.rstrip() == "X_HIGH":
            xhig = float(value)
        elif param.rstrip() == "Y_LOW":
            ylow = float(value)
        elif param.rstrip() == "Y_HIGH":
            yhig = float(value)
        elif param.rstrip() == "DELTA_X":
            deltaX = float(value)
        elif param.rstrip() == "DELTA_Y":
            deltaY = float(value)
        elif param.rstrip() == "PLOT_INTERVAL":
            plotInterval = int(value)
        else:
            continue

    n = round((yhig - ylow) / deltaY)
    m = round((xhig - xlow) / deltaX)

#load frame 
def loadFrame(fileName):

    global X, Y, Z
    X = np.zeros((n,m))
    Y = np.zeros((n,m))
    Z = np.zeros((n,m))

    x_idx  = 0
    y_idx  = 0
    prev_y = np.nan

    with open(fileName,'r') as f:
        for line in f:
            (x,y,z) = line.rstrip().split(' ')
            x = float(x)
            y = float(y)
            z = float(z)
            if y > yhig:
                continue
            elif y < ylow:
                return
            else:
                if x < xlow or x > xhig:
                    continue
                else:

                    if y != prev_y:
                        x_idx = 0
                        Y[n-y_idx-1,:] = y
                        X[:,x_idx] = x
                        prev_y = y
                        y_idx = y_idx + 1
                            
                    X[:,x_idx] = x
                    Z[n-y_idx,x_idx] = z
                    x_idx = x_idx + 1

def waterLandCmap():
    cdict = {'red': ((0.0, 0.0, 0.0),
                     (0.5, 0.0, 0.0),
                     (1.0, 0.0, 0.0)),
             'green': ((0.0, 0.0, 0.0),
                       (0.5, 0.5, 0.5),
                       (1.0, 0.1, 0.0)),
             'blue': ((0.0, 0.5, 0.5),
                      (0.2, 0.9, 0.5),
                      (0.5, 0.6, 0.0),
                      (1.0, 0.0, 0.0))}
    my_cmap = matplotlib.colors.LinearSegmentedColormap('my_colormap',cdict,256)
    return my_cmap

def generateMovie(inputFile):

    #get reference to global Z data
    global Z 

    #setup movie writer
    FFMpegWriter = ani.writers['ffmpeg']
    metadata     = dict( title  = '2D Wave', artist='Matplotlib',
                         comment= '2D Wave Equation')
    writer       = FFMpegWriter(fps=15, metadata=metadata, bitrate=6000)
   
    Nframes = steps
    dpi = 120
    fig = plt.figure()
    
    with writer.saving(fig, movieFileName, dpi):
    
        for i in range(1,Nframes+1, plotInterval):
            name = inputFile + '_' + str(i) + '.xyz'
            while not os.path.isfile(name):
                time.sleep(10)
   
            loadFrame(name)
        
            plt.clf()
            
            ax = fig.gca(projection = '3d')
            ax.view_init(elev=50, azim=-80)
            ax.set_xlim3d(xlow,xhig)
            ax.set_ylim3d(ylow,yhig)
            ax.set_zlim3d(-100,2000)
            ax.dist=10
            Z = scipy.ndimage.gaussian_filter(Z,2)
            surf = ax.plot_surface(X, Y, Z,
                                  rstride = 3,
                                  cstride = 3,
                                  cmap = waterLandCmap(),
                                  linewidth = 0,
                                  antialiased = False)
            writer.grab_frame()
            print("done with " + str(i) + " frames")

def main(argv=sys.argv):
    usage = ' '.join(["Usage:",str(argv[0]), "<parameter_file> <input_prefix>"])
    if len(sys.argv) != 3:
        print usage
        sys.exit(0)

    paramFile = sys.argv[1]
    inputFile = sys.argv[2]

    readParamFile(paramFile)
    generateMovie(inputFile)

if __name__ == "__main__": main()
