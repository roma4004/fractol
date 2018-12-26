# fractol. Goal is to create a small fractal exploration program.
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-05%20at%207.32.47%20PM.png)

**Mandatory part:**

We cannot use global variables, must follow the [Norm](https://github.com/roma4004/fdf/blob/master/documentation/norme.en.pdf), **this explains many unobvious decisions solutions that I applied, like function in 25 row, or only 4 argument in function**).

We have to handle errors carefully. In no way can quit my program in an unexpected
manner (Segmentation fault, bus error, double free, etc).
	
   We are alowed to use the following functions:
   
	• open, read, write, close, malloc, free, perror, strerror, exit	
	• All the functions defined in the math library
	• All the functions defined in the miniLibX library

Short summary:

 	• At least 3 different types of fractals, including the Julia and Mandelbrot set.
    The third fractal (and the optional additional) can be whatever you want.
 	• Parameter of Julia set must vary only with the mouse move. Optional for the other fractal.
 	• The mouse wheel zooms in and out, almost infinitely (within the computer limits).
 	• At least a few colors to show the depth of each fractal. Better if create psychedelic effects.
 	• A parameter is passed on the command line to define what type of fractal will be viewed.

**Bonus part:** (plus = already implemented, minus = decided not to implement)
	
	+ The zoom follow the actual mouse position.
	+ In addition to the zoom: moving with the arrows.
	+ Make the color range shift.
	+ Multi-threading implementation.
	+ Plenty of fun fractals (there are more than a hundred different types of fractals referenced online).
	+ 3D representation.
	+ Two valid parameters in the command line, resulting in two fractals in two windows.

fractal Mandelbrot:
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-05%20at%207.27.31%20PM.png)

mandelbrot with wind effect:
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-04%20at%201.09.48%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-04%20at%201.10.06%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-04%20at%202.59.18%20PM.png)

fractal Mandelbrot with leaf effect:
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-05%20at%205.53.26%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-05%20at%206.59.50%20PM.png)

fractal Mandelbrot with other effect:
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%203.54.16%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%203.55.54%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%203.57.17%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%204.00.13%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%204.02.18%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%204.03.52%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%204.38.16%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-05%20at%206.59.16%20PM.png)

fractal Julia with leaf effect: 
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-08%20at%207.53.16%20PM.png)

fractal Julia with other effects: 
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-10%20at%201.04.00%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.18.55%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.19.39%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.20.34%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.20.58%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-10-10%20at%203.47.14%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-10-10%20at%203.48.29%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.26.10%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.26.22%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%208.26.51%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-06%20at%209.07.19%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-16%20at%205.34.07%20PM.png)
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-16%20at%205.35.19%20PM.png)

mandelbrot cuboid with blades effect:
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-08%20at%206.37.41%20PM.png)
mandelbrot cuboid with mustache effect:
![img](https://github.com/roma4004/fractol/blob/master/images/Screen%20Shot%202018-09-11%20at%205.42.42%20PM.png)


