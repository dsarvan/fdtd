#!/usr/bin/env python
""" Electromagnetic simulation using the FDTD method """


import ctypes
import sys

import numpy as np
from PyQt6 import QtWidgets

import visualize


def main():
    """FDTD method"""

    libname = "simulation.so"
    # libname = sys.argv[1] # python main.py simulation.so
    loader_path = "."

    fdtd = np.ctypeslib.load_library(libname, loader_path)

    ke = 200
    ex = np.zeros(ke, dtype=np.float64)
    hy = np.zeros(ke, dtype=np.float64)

    nsteps = 500

    Ex = np.zeros(ke * nsteps, dtype=np.float64)
    Hy = np.zeros(ke * nsteps, dtype=np.float64)

    double = np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags="C")

    fdtd.simulate.argtypes = [ctypes.c_int, double, double, double, double]
    fdtd.simulate.restype = ctypes.c_int

    fdtd.simulate(ke, ex, hy, Ex, Hy)

    app = QtWidgets.QApplication(sys.argv)
    window = visualize.MainWindow(Ex.reshape(-1, ke), Hy.reshape(-1, ke))
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
