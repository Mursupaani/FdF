# FDF

The goal of the "FDF" project is to represent a 3D landscape in a wireframe model using the MLX42 graphics library. 

For the complete project rules, see the official subject file: **en.subject_4.pdf**.

## 🚀 How to Run

Compile the program using `make`, then pass a `.fdf` map file as an argument.

```bash
make
./fdf path/to/map.fdf
```

*Note: The `.fdf` file contains a grid of numbers where the horizontal and vertical positions represent X and Y coordinates, and the value represents the Z altitude.*

## 🎮 Controls

The following controls have been implemented for full manipulation of the wireframe model:

* **Mouse Scroll Up / Down**: Zoom in / Zoom out
* **Arrow Keys (Up, Down, Left, Right)**: Move/translate the model across the screen
* **Q / W**: Decrease / Increase the Z-depth (altitude) of the map
* **C / V**: Rotate the model up and down
* **Z / X**: Cycle or change the wireframe colors
* **R**: Reset the view to the default starting position
* **ESC (or window cross)**: Exit the program cleanly
