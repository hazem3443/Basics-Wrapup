import tkinter
import re #regex

from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg, NavigationToolbar2Tk)
# Implement the default Matplotlib key bindings.
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure

import numpy as np

#global properties
formula = "0"
Max_val = 100
Min_val = 0
fig = Figure(figsize=(5, 4), dpi=100)#figure instance
root = tkinter.Tk()#tkinter window
canvas_section = tkinter.Frame(root)#canvas frame section to stick matplot lib figure to it
canvas = FigureCanvasTkAgg(fig, master=canvas_section)  # A tk.DrawingArea

#input validation function
def formula_callback(sv):
    global formula
    text = sv.get() 
    reg = r"^[0-9xX\+\-\*\/\^\.\(\)]*$" #the group of char a to c

    if re.match(reg, text): #Check if regex is correct or if text matches the pattern
        formula = text

    else:
        sv.set(text[:-1])#remove last inputed invalid char
        #trigger a warning window notifying the user to correct himself#
        tkinter.messagebox.showinfo("Warning", "Please Enter Valid Input 0-9 or + - * / ^")
        print("Not any match")

def Max_callback(sv):
    global Max_val
    text = sv.get()
    if len(text) == 0:#if no text inputed then return
        return
    reg = r"^[0-9\-]*$" #the group of char a to c
    if re.match(reg, text): #Check if regex is correct
        if text=="-":#handle minus sign validation cause it is allowed here :D
            return
        Max_val = eval(text)#convert string to python code integer
        # print(Max_val)
        if Min_val>Max_val:#check min and max values validation
            tkinter.messagebox.showinfo("Warning", "Please select appropriate value greater than Min value of X")
    else:
        sv.set(text[:-1])
        tkinter.messagebox.showinfo("Warning", "Please Enter Valid Input 0-9 as positive or negative number")
        print("Not any match")

def Min_callback(sv):
    global Min_val
    text = sv.get()
    if len(text) == 0:
        return
    reg = r"^[0-9\-]*$" #the group of char a to c
    if re.match(reg, text): #Check if regex is correct
        if text=="-":
            return
        else:
            Min_val = eval(text)
        # print(Min_val)
        if Min_val>Max_val:
            tkinter.messagebox.showinfo("Warning", "Please select appropriate value less than Max value of X")
    else:
        sv.set(text[:-1])
        tkinter.messagebox.showinfo("Warning", "Please Enter Valid Input 0-9 as positive or negative number")
        print("Not any match")

def DrawCallBack():
    global canvas ,fig ,formula ,Max_val ,Max_val#refer to global scope
    fig.clf()#clear the figure
    x = np.arange(Min_val, Max_val, .01)#add constrains of MAX and MIN values 
    formula = formula.lower()#convert formula to lower case
    if "x" not in formula:#formula must contain x param even if it is useless so if not found add it
        formula = formula+"+x*0"

    if "^" in formula:#handle power sign easy in python hah :D
        formula = formula.replace("^","**")

    fig.add_subplot(111).plot(x, eval(formula))#function to be Drawn

    canvas.draw()#draw the canvas field

    canvas.get_tk_widget().pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=1)#link the widget field 

def on_key_press(event):
    #TODO: can be extended to handle enter key strok to draw or click on draw button
    print("you pressed {}".format(event.key))
    key_press_handler(event, canvas,toolbar)

def _quit():
    root.quit()     # stops mainloop
    root.destroy()  # this is necessary on Windows to prevent
                    # Fatal Python Error: PyEval_RestoreThread: NULL tstate

if __name__ == '__main__':     
    root.wm_title("Function Plotter")

    ## first container label+entry(input field)
    FormulaSection = tkinter.Frame(root)
    var = tkinter.StringVar()
    #label component
    var.set("Formula in x")
    label = tkinter.Label( FormulaSection, textvariable=var, relief=tkinter.RAISED )
    varbr = tkinter.StringVar()
    # input field component
    sv = tkinter.StringVar()
    sv.trace("w", lambda name, index, mode, sv=sv: formula_callback(sv))#add tracer to callback function as input field event 
    e = tkinter.Entry(FormulaSection, textvariable=sv)
    label.grid(row=0,pady=1)
    e.grid(row=0,column=4,pady=1)

    ## second container label+entry(input field) + label+entry(input field)
    Min_MaxSection = tkinter.Frame(root)
    #label component
    var2 = tkinter.StringVar()
    var2.set("Max val of X")
    label2 = tkinter.Label(Min_MaxSection, textvariable=var2, relief=tkinter.RAISED)
    # input field component
    sv2 = tkinter.StringVar()
    sv2.set(str(Max_val))
    try:
        sv2.trace("w", lambda name, index, mode, sv=sv2: Max_callback(sv2))#add tracer to callback function as input field event 
    except Exception as e:
        print("empty minus exception")

    e2 = tkinter.Entry(Min_MaxSection, textvariable=sv2)

    #label component
    var3 = tkinter.StringVar()
    var3.set("Min val of X")
    label3 = tkinter.Label(Min_MaxSection, textvariable=var3, relief=tkinter.RAISED )
    # input field component
    sv3 = tkinter.StringVar()
    sv3.set(str(Min_val))
    try:
        sv3.trace("w", lambda name, index, mode, sv=sv3: Min_callback(sv3))#add tracer to callback function as input field event 
    except Exception as e:
        print("empty minus exception")

    e3 = tkinter.Entry(Min_MaxSection, textvariable=sv3)

    #section two elements positions
    label2.grid(row=0,pady=1)
    e2.grid(row=0,column=4,pady=1)
    label3.grid(row=1,pady=1)
    e3.grid(row=1,column=4,pady=1)

    #Draw_button component
    Draw_button = tkinter.Button(root, text ="Draw", command = DrawCallBack)

    #connect figure to canvas
    canvas.draw()

    #Toolbar configurations
    toolbar = NavigationToolbar2Tk(canvas, canvas_section)
    toolbar.update()
    canvas.get_tk_widget().pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=2)

    canvas.mpl_connect("key_press_event", on_key_press)#add function tracer callback

    #pack window object with all created and configured section and elements
    canvas_section.pack(side="top", fill="x",padx=17)
    FormulaSection.pack(side="top", fill="both",padx=20)
    Min_MaxSection.pack(side="top", fill="both",padx=20)
    Draw_button.pack(fill="x",side="top",padx=20)

    button = tkinter.Button(master=root, text="Quit", command=_quit)
    button.pack(fill="x",side="top",padx=20)

    root.resizable(False, False)#diable resizing for more responsiveness

    tkinter.mainloop()
