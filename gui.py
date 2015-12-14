#!/usr/bin/python
#-*- coding: utf-8 -*-

from ttk import *
from numpy import *
import Tkinter as tk
from matplotlib.pyplot import *

# class representing main window in application
class MainWindow(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.x0 = tk.StringVar(self)
        self.x1 = tk.StringVar(self)
        self.y0 = tk.StringVar(self)
        self.y1 = tk.StringVar(self)
        # viscosity
        self.viscosity = tk.DoubleVar(self)
        self.friction = tk.DoubleVar()

        self.initUI()

    def initUI(self):
        self.parent.title("Algorytm Ewolucyjny")
        self.style = Style()
        self.style.theme_use("default")

        self.pack(fill=tk.BOTH, expand=1)

        # Spinboxes for coordinates
        Label(self, text="Współrzędne:").pack(anchor=tk.NW, padx=10, pady=10)

        self.makeSpinbox("x0", 20, increment=0.1, textvariable=self.x0, from_=0, to=100000000)
        self.makeSpinbox("y0", 20, increment=0.1, textvariable=self.y0, from_=0, to=100000000)
        self.makeSpinbox("x1", 20, increment=0.1, textvariable=self.x1, from_=0, to=100000000)
        self.makeSpinbox("y1", 20, increment=0.1, textvariable=self.y1, from_=0, to=100000000)
        self.makeSpinbox("Współczynnik lepkości", 20, increment=0.01, textvariable=self.viscosity, from_=0, to=1 )
        self.x0.set(0.0)
        self.x1.set(0.0)
        self.y0.set(0.0)
        self.y1.set(0.0)
        self.viscosity.set(0.0)

        # friction scale
        scale = tk.Scale(self, from_=0.0, to=1.0, resolution=0.001, command=self.onScale,
            label="Współczynnik tarcia", orient=tk.HORIZONTAL, length=150)
        scale.pack(anchor=tk.NW, padx=20, pady=10)

        # solve button
        button = tk.Button(self, text ="Oblicz", command = self.solve).pack(anchor=tk.S, padx=20, pady=15)
        buttonClose = tk.Button(self, text ="Zamknij", command = self.closeWindow).pack(anchor=tk.S, padx=20, pady=15)

    def closeWindow(self):
        self.parent.destroy()

    # function which solves problem with evolutionary algorithm
    def solve(self):
        #drawing plot
        self.drawPlot(11,2)

    # method which sets scale value to friction
    def onScale(self, val):
        v = float(val)
        self.friction.set(v)

    # method which creates spinbox
    def makeSpinbox(parent, caption, width=None, **options):
        Label(parent, text=caption).pack(anchor=tk.N, padx=10, pady=10)
        spinbox = tk.Spinbox(parent, **options)
        if width:
            spinbox.config(width=width)
        spinbox.pack(anchor=tk.S, padx=10, pady=10)
        return spinbox

    # function which draws plot of the shape of tool
    def drawPlot(self, a0, a1):
        # coordinates
        x0 = float(self.x0.get())
        x1 = float(self.x1.get())
        y0 = float(self.y0.get())
        y1 = float(self.y1.get())

        # x plot
        x = linspace(x0, x1, 200)

        # function which will be drawn
        y = (y1 + (y0 - y1)/(x0 - y1))*(x-x1) + (x-x0)*(x-x1)*(a0+a1*x)
        figure()
        plot(x, y)
        grid(True)
        savefig("plot.png")
        xlabel(r"Wspolrzedna x")
        ylabel(r"Wspolrzedna y")
        title(r"Ksztalt narzedzia")
        show()
        self.closeWindow()

def main():
    root = tk.Tk()
    mw = MainWindow(root)
    root.geometry("200x580")
    root.mainloop()

if __name__ == '__main__':
    main()
