# FDF

The point of this project is to create a map in iron lines, using isometric (and other) perspectives.
The map also rotates,  moves in space, can be zoomed and handles colors.

## Usage

* Usual project : 
```
make
./fdf map.fdf
```
* Bonus : 
```
make bonus
./fdf map.fdf
```

## Sources

* [Bresenham's algorithm in 3D](http://members.chello.at/easyfilter/bresenham.html)
* [Matricial rotations around a plane](https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space)

## To go further

* The map only rotates around one Euler angle at once ([Euler angles](https://en.wikipedia.org/wiki/Euler_angles)). The use of quaternions ([Quaternions](https://en.wikipedia.org/wiki/Quaternion)) seems to be a better alternative than a 3D representation.
* The points' coordinates rotate within a fix axis. It would be cleaner mathematically to move the axis with points coordinates fixed to it.
* Maybe create more independant maps ?
* The possibility to modify the points' coordinates within the  window ?