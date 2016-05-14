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

        wave_simulate.tsk -p sample/parameters.txt -o sample/out

3. Generate movie

        cd scripts
        python wave.py ../sample/parameters.txt ../sample/out


*parameters.txt* is a parameter file that contains values for all the parameters needed for the simulation
and *sample/out* will be used to name files generated at each step of the simulation:

        sample/out_1.xyz
        sample/out_2.xyz
        ...
