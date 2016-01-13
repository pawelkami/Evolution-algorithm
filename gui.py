#!/usr/bin/python
#-*- coding: utf-8 -*-

from ttk import *
from numpy import *
import Tkinter as tk
from matplotlib.pyplot import *
import evolution
import tkMessageBox

# class representing main window in application
class MainWindow(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        # first player moves
        self.x0 = tk.StringVar(self)
        self.x1 = tk.StringVar(self)
        self.x2 = tk.StringVar(self)

        # second player moves
        self.y0 = tk.StringVar(self)
        self.y1 = tk.StringVar(self)
        self.y2 = tk.StringVar(self)

        # number of iterations of genetic algorithm
        self.iterationNumber = tk.StringVar(self)

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
        Label(self, text="0 - współpraca").place(x=10,y=200)
        Label(self, text="1 - brak współpracy").place(x=10, y=220)
        self.makeSpinbox("Liczba iteracji algorytmu:", 10, 200, 200, increment=1, from_=0, to= 1000000, textvariable=self.iterationNumber)
        self.x0.set(0)
        self.x1.set(0)
        self.x2.set(0)
        self.y0.set(0)
        self.y1.set(0)
        self.y2.set(0)
        self.iterationNumber.set(2000)

        # solve button
        button = tk.Button(self, text ="Oblicz", command = self.solve).place(x=110, y= 260)
        buttonClose = tk.Button(self, text ="Zamknij", command = self.closeWindow).place(x=170, y=260)

    def closeWindow(self):
        self.parent.destroy()

    # function which solves problem with evolutionary algorithm
    def solve(self):
        history = str(self.x0.get() + self.y0.get() + self.x1.get() + self.y1.get() + self.x2.get() + self.y2.get())
        pd = evolution.PrisonersDilemma(history, int(self.iterationNumber.get()))

        # solving problem
        self.beginWaitCursor()
        result = pd.solve()
        self.endWaitCursor()

        result = "Strategia: %s\n\n" \
		         "WSP z ALLD przed: %s\n\n" \
		         "WSP z ALLC przed: %s\n\n" \
		         "WSP z ALLD po: %s\n\n" \
		         "WSP z ALLC po: %s\n\n" % (result, result, result, result, result)
				 
        tkMessageBox.showinfo("Wynik", result)
        fitnesses = pd.getFitnesses()

        #drawing plot
        self.drawPlot(fitnesses)

    # method which begins mouse waiting cursor
    def beginWaitCursor(self):
        self.parent.config(cursor="wait")
        self.parent.update()

    # method which stops 'waiting' mouse cursor
    def endWaitCursor(self):
        self.parent.config(cursor="")
        self.parent.update()

    # method which creates spinbox
    def makeSpinbox(parent, caption, width, x, y, **options):
        Label(parent, text=caption).place(x=x,y=y)
        Label(parent, text=caption).place(x=x,y=y)

        spinbox = tk.Spinbox(parent, **options)
        if width:
            spinbox.config(width=width)
        spinbox.place(x=x, y=y+20)
        return spinbox

    # function which draws plot of the shape of tool
    def drawPlot(self, fitnesses ):
        # x plot
        x = range(0, size(fitnesses))

        # function which will be drawn
        y = fitnesses
        figure()
        plot(x, y)
        grid(True)
        savefig("plot.png")
        xlabel(r"Iteracja")
        ylabel(r"Fitness")
        title(r"Optymalne fitnessy przy kolejnych iteracjach")
        show()

def main():
    root = tk.Tk()
    mw = MainWindow(root)
    root.geometry("340x300")
    root.resizable(width=tk.FALSE, height=tk.FALSE)
    root.iconbitmap('panda.ico')
    root.mainloop()

if __name__ == '__main__':
    main()
