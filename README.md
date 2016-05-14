# Wave
2D wave simulation project.

This repository was created for the final project of the NYU "Numerical Methods II" class of the Spring 2016 semester.
It runs a finite differencing 2D wave simulator on input xyz data.

A good source for xyz bathymetry data I found in:
https://www.ngdc.noaa.gov/mgg/bathymetry/relief.html

Quick start
-----------

1. Build

        make

2. Run simulation

        wave_simulate.tsk -p parameters -o outprefix

3. Generate movie

        cd scripts
        python wave.py parameters outprefix


*parameters* is a parameter file that contains values for all the parameters needed for the simulation
and *outprefix* will be used to name files generated at each step of the simulation:

        outprefix_1.xyz
        outprefix_2.xyz
        ...
