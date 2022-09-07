gcc main.c -I minilibx_macos -I /opt/X11/include -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit

3D to 2D : (x', y') = Mp(x, y, z) = ((sqrt(2) / 2) * (x - y), sqrt(2z / 3) - 1/sqrt(6) * (x + y))

Map display format : size depends of total size. Size can be bigger than number of pixel, so I need to handle
that case.

The map is stored in a char[y][x].

Can I do a get_next_line ? It returns a malloced line, so why not.

Now that we have a map, how do we assign each value to a struct array ? Done.

Now that we have a struct array, we need to print it on the screen, using the formula above.
This means for each point, it's gonna be assigned a coordinate on the screen in (x', y')
using (x, y, z).

How do we make the translation though ? Well, simple. Kinda. We need to translate the coordinates
of each point to another point, converted from spherical coordinates. This means we translate it
from an angle to another. And that's how you rotate a map. If we have a point (x, y), we need to translate
it's coordinates using the angle value.

However, we have to assign a reference point from where we draw. So where do we start ? We can't start at (0, 0). It
would feel a bit weird since it wouldn't be in the middle. So we'd have to keep a few hundreds pixels to draw.


Warning ! When printing the 2D map, in x_prime and y prime, x and y are reversed to print the point in the right "angle".

How do I want to make my map ? I want to have one big final array of points that I can draw on the screen, which means making an array of points of all the vectors I have. I don't want an array of array of points since I'd like to write everything on the screen once. That means eventually a strjoin, but with points instead of chars. This might mean I'd have one big array of points in my "main" function that I'd print at every frame, and recalculate the coordinates if we rotate around an angle.

I need to return an array of points from the system, conserve that version and rotate this one instead of reusing the "screenable" one to avoid recalculating back all the points in the referential.