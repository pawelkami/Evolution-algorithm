#!/usr/bin/python
#-*- coding: utf-8 -*-

from ttk import *
from numpy import *
import Tkinter as tk
from matplotlib.pyplot import *
import evolution

# class representing main window in application
class MainWindow(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.x0 = tk.StringVar(self)
        self.x1 = tk.StringVar(self)
        self.x2 = tk.StringVar(self)
		
        self.y0 = tk.StringVar(self)
        self.y1 = tk.StringVar(self)
        self.y2 = tk.StringVar(self)

        self.initUI()

    def initUI(self):
        self.parent.title("Algorytm Ewolucyjny")
        self.style = Style()
        self.style.theme_use("default")

        self.pack(fill=tk.BOTH, expand=1)

        # Spinboxes for coordinates
        Label(self, text="Ruchy pierwszego gracza:").place(x=10,y=10)
        Label(self, text="Ruchy drugiego gracza:").place(x=200, y=10)
		
        self.makeSpinbox("Pierwszy:", 10, 10, 30, increment=1, textvariable=self.x0, values=(0,1))
        self.makeSpinbox("Pierwszy:", 10, 200, 30, increment=1, textvariable=self.y0, values=(0,1))
        self.makeSpinbox("Drugi:", 10, 10, 90, increment=1, textvariable=self.x1, values=(0,1))
        self.makeSpinbox("Drugi:", 10, 200, 90, increment=1, textvariable=self.y1, values=(0,1))
        self.makeSpinbox("Trzeci:", 10, 10, 150, increment=1, textvariable=self.x2, values=(0,1))
        self.makeSpinbox("Trzeci:", 10, 200, 150, increment=1, textvariable=self.y2, values=(0,1))
        Label(self, text="0 - brak współpracy").place(x=10,y=200)
        Label(self, text="1 - współpraca").place(x=10, y=220)
        self.x0.set(0)
        self.x1.set(0)
        self.x2.set(0)
        self.y0.set(0)
        self.y1.set(0)
        self.y2.set(0)

        # solve button
        button = tk.Button(self, text ="Oblicz", command = self.solve).place(x=110, y= 260)
        buttonClose = tk.Button(self, text ="Zamknij", command = self.closeWindow).place(x=170, y=260)

    def closeWindow(self):
        self.parent.destroy()

    # function which solves problem with evolutionary algorithm
    def solve(self):
        print evolution.getName()
        #drawing plot
        self.drawPlot(11,2)

    # method which sets scale value to friction
    def onScale(self, val):
        v = float(val)
        self.friction.set(v)

    # method which creates spinbox
    def makeSpinbox(parent, caption, width, x, y, **options):
        #Label(parent, text=caption).pack('''anchor=tk.NW, padx=10, pady=10''')
        Label(parent, text=caption).place(x=x,y=y)
        Label(parent, text=caption).place(x=x,y=y)

        spinbox = tk.Spinbox(parent, **options)
        if width:
            spinbox.config(width=width)
        #spinbox.pack(anchor=tk.S, side=side,padx=10, pady=10)
        spinbox.place(x=x, y=y+20)
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
    root.geometry("340x300")
    root.resizable(width=tk.FALSE, height=tk.FALSE)
    root.mainloop()

if __name__ == '__main__':
    main()
