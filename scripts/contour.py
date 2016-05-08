import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.animation as ani
import os

#setup movie writer
FFMpegWriter = ani.writers['ffmpeg']
metadata     = dict( title  = '2D Wave', artist='Matplotlib',
                     comment= '2D Wave Equation')
writer       = FFMpegWriter(fps=15, metadata=metadata)

Nframes = 600
dpi = 100
fig = plt.figure()
with writer.saving(fig, "../data/waveHeatMapAnimation.mp4", dpi):

    for i in range(1,Nframes+1, 1):
        name = '../data/surface_' + str(i) + '.xyz'
        while not os.path.isfile(name):
            time.sleep(10)

        #load frame from xyz file
        frame = np.loadtxt(name)
        m = 995
        n = 2527
        
        #format data for plot
        X = np.tile(frame[0:n:1,0],(m,1))
        Y = np.tile(frame[1:m*n:n,1],(n,1)).transpose()
        Z = frame[:,2].reshape((m,n))

        plt.clf()
        
        plt.contourf(X, Y, Z)
        plt.colorbar()
         
        writer.grab_frame()

        print("done with " + str(i) + " frames")
        #delete files processed so far to save disk space
        for j in range(1,i+1):
            fname = '../data/surface_'+str(j)+'.xyz'
            if os.path.isfile(fname):
                os.remove(fname)
