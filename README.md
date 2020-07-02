<p align="center"><img width="100px" src="https://i.imgur.com/5GTnqLg.png" alt="Asteroids"/></p>

---

An asteroids clone using C++ &amp; freeglut, developed as a project for my Computer Programming course. I was a very novice programmer at that point (a couple years ago) and consequently the code might not be as efficient.

<p align="center"><img src="https://imgur.com/kvFBrwc.gif" alt="A* Visualization"/></p>

## Instructions
The following instructions are for Ubuntu 16.04 and onwards. You may edit the `install_dependencies.sh` file to modify the installation command for your distro. You need `make` and `g++` to compile the source code, both of which come preinstalled in Ubuntu. 

```
git clone git@github.com:parkerqueen/asteroids.git
cd asteroids
chmod +x install_dependencies.sh
./install_dependencies.sh
make all
```

You'll have an executable named `game` generated. Use `make clean` to clean everything.

## Notes
* Use arrow keys (`up`, `right` & `left`) to steer the ship. If you press & hold the `up` key, the speed will keep increasing towards a certain threshold.
* Use `space` to shoot and destroy the asteroids & saucers.
* You have three lives. The number of `A`s at the top left indicate the remaining lives.

## Issues
* Collisions are not as precise.
* Speed is just an arbitrary unit and not really 'MPH'.
* Using SDL2 only to play sounds.
