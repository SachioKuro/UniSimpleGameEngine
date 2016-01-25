import numpy as np
import os
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# has to change whenever noise_width and noise_height change in the PerlinNoise.hpp file
DIMENSION1 = 200
DIMENSION2 = 200

# works if the working directory is set
path = os.path.dirname(os.path.realpath(__file__))
FILENAME = path + "\input0.txt"

if __name__ == '__main__':
    string = open(FILENAME, '+r')
    noise = np.fromstring(string.read(), sep=" ", dtype=float).reshape(DIMENSION2, DIMENSION1)

    # Build a grid by the 2 dimensions
    Xr = np.arange(DIMENSION1)
    Yr = np.arange(DIMENSION2)
    X, Y = np.meshgrid(Xr, Yr)

    # Build a figure with 2 subplots, the first is 3D
    fig = plt.figure()
    fig.suptitle("3D and 2D heighmap")
    colormap = 'coolwarm'
    ax = fig.add_subplot(2, 1, 1, projection='3d')
    surf = ax.plot_surface(X, Y, noise, rstride=1, cstride=1, cmap=colormap, linewidth=0, antialiased=False)

    ax2 = fig.add_subplot(2, 1, 2)
    im = ax2.imshow(noise, cmap=colormap, interpolation='nearest')
    # swap the Y axis so it aligns with the 3D plot
    ax2.invert_yaxis()

    # add an explanatory colour bar
    plt.colorbar(im, orientation='horizontal')

    # Show the image
    plt.show()





