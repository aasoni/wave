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

#window to plot
xlow = 8.58
xhig = 9.92
ylow = 38.76
yhig = 40.284
n = round((yhig - ylow) / 0.016666666) 
m = round((xhig - xlow) / 0.016666666) + 1

X = np.zeros((n,m))
Y = np.zeros((n,m))
Z = np.zeros((n,m))

#load frame 
def loadFrame(fileName):

    X_done = False
    x_idx  = 0
    y_idx  = 0
    prev_y = float('-inf')

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
                    Z[n-y_idx-1,x_idx] = z
                    x_idx = x_idx + 1

def waterLandCmap():
    cdict = {'red': ((0.0, 0.0, 0.0),
                     (1.0, 0.0, 0.0)),
             'green': ((0.0, 0.0, 0.0),
                       (0.5, 1.0, 0.0),
                       (1.0, 1.0, 1.0)),
             'blue': ((0.0, 0.0, 1.0),
                      (0.5, 1.0, 0.0),
                      (1.0, 0.5, 0.0))}
    my_cmap = matplotlib.colors.LinearSegmentedColormap('my_colormap',cdict,256)
    return my_cmap

#setup movie writer
FFMpegWriter = ani.writers['ffmpeg']
metadata     = dict( title  = '2D Wave', artist='Matplotlib',
                     comment= '2D Wave Equation')
writer       = FFMpegWriter(fps=15, metadata=metadata)

Nframes = 1
dpi = 100
fig = plt.figure()

#with writer.saving(fig, "../data/waveAnimation.mp4", dpi):

for i in range(1,Nframes+1, 1):
    name = '../data/golfo_cagliari2.xyz'
    while not os.path.isfile(name):
        time.sleep(10)

    loadFrame(name)

    plt.clf()
    
    ax = fig.gca(projection = '3d')
    ax.view_init(elev=50, azim=-50)
    ax.set_xlim3d(xlow,xhig)
    ax.set_ylim3d(ylow,yhig)
    ax.set_zlim3d(-10,2000)
    ax.dist=14
    Z = scipy.ndimage.gaussian_filter(Z,2)
    print X.shape
    print Y.shape
    print Z.shape
    surf = ax.plot_surface(X, Y, Z,
                          alpha = 0.9,
                          rstride = 3,
                          cstride = 3,
                          cmap = waterLandCmap(),
                          linewidth = 0.5)
     
    #writer.grab_frame()
    plt.show()

    print("done with " + str(i) + " frames")

    #delete files processed so far to save disk space
    #for j in range(1,i+1):
    #    fname = '../data/wave_'+str(j)+'.xyz'
    #    if os.path.isfile(fname):
    #        os.remove(fname)
