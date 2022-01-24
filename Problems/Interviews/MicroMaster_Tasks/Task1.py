import Tkinter #GUI pack
import tkMessageBox #messagebox
import re #regex 

#map 0 to canvas_height to y coordinates max to min
def map_func(x,max,min):
    if x>=0:
        return abs(max-x)
    else:
        return abs(max)+abs(min)-abs(min-x)
#map_func function test cases
#test case1
print("pass" if (map_func(150,150,-150)==0) else "fail")
#test case2
print("pass" if (map_func(-150,150,-150)==300) else "fail")
#test case3
print("pass" if (map_func(0,150,-150)==150) else "fail")
#test case4
print("pass" if (map_func(140,150,-150)==10) else "fail")
#test case5
print("pass" if (map_func(-140,150,-150)==290) else "fail")

def DrawCallBack():
    #draw logic
    global function_str
    function_plot_canvas.delete("all")
    global verticalline
    global horizontalline
    coord = function_plot_canvas.create_line(verticalline,fill="black")
    coord = function_plot_canvas.create_line(horizontalline,fill="black")
    x = 10
    tobe_eval_str = function_str.replace("x",str(x-10))
    newline = x,map_func(eval(tobe_eval_str),150,-150)
    while x<400:
        tobe_eval_str = function_str.replace("x",str(x-10))#10 pixels offset of vertical axis left padding
        newline += x,map_func(eval(tobe_eval_str),150,-150)
        coord = function_plot_canvas.create_line(newline,fill="red")
        print("x = "+str(x)+" "+"map_func = "+str(map_func(eval(tobe_eval_str),150,-150)))
        x+=1#shift next x coordinates
        if(map_func(eval(tobe_eval_str),150,-150) == 0 or map_func(eval(tobe_eval_str),150,-150) == 300):
            break
    print("End plotting")

root = Tkinter.Tk()#create window
root.geometry("400x400")#window size

#function string to be set from user input
function_str = ""


## first container label+entry(input field)
section1 = Tkinter.Frame(root)
var = Tkinter.StringVar()
#label component
var.set("Enter Your Function")
label = Tkinter.Label( section1, textvariable=var, relief=Tkinter.RAISED )
# input field component
sv = Tkinter.StringVar()
sv.trace("w", lambda name, index, mode, sv=sv: callback(sv))#add tracer to callback function as input field event 
e = Tkinter.Entry(section1, textvariable=sv)
label.grid(row=0, column=1)
e.grid(row=0, column=2)


#canvas component
function_plot_canvas = Tkinter.Canvas(root, bg="white", height=300, width=400)

#draw_button component
Draw_button = Tkinter.Button(root, text ="Draw", command = DrawCallBack)

#vertical and horizontal lines coordinates
verticalline = 10, 0, 10, 300
horizontalline = 10, 150, 400, 150 

# draw those coordinates
coord = function_plot_canvas.create_line(verticalline,fill="black")
coord = function_plot_canvas.create_line(horizontalline,fill="black")

#input validation function
def callback(sv):
    # sv.set("asw")
    global function_str
    text = sv.get() 
    reg = r"^[0-9xX\+\-\*\/\^\.\(\)]*$" #the group of char a to c

    if re.match(reg, text): #Check if regex is correct
        function_str = text
        print(function_str)
    else:
        sv.set(text[:-1])
        tkMessageBox.showinfo("Warning", "Please Enter Valid Input 0-9 or + - * / ^")
        print("Not any match")



section1.grid_columnconfigure(0, weight=1)
section1.grid_columnconfigure(4, weight=1)
section1.pack(side="top", fill="x")

Draw_button.pack()
function_plot_canvas.pack()

root.mainloop()#start the window

########################

# Import libraries
# import matplotlib.pyplot as plt
# import numpy as np
 
# x = np.linspace(-6, 6, 50)
 
# fig = plt.figure(figsize = (14, 8))
 
# # Plot y = cos(x)
# y = np.cos(x)
# plt.plot(x, y, 'b', label ='cos(x)')
 
# # Plot degree 2 Taylor polynomial
# y2 = eval("1 - x**2 / 2")
# plt.plot(x, y2, 'r-.', label ='Degree 2')
 
# # Plot degree 4 Taylor polynomial
# y4 = 1 - x**2 / 2 + x**4 / 24
# plt.plot(x, y4, 'g:', label ='Degree 4')
 
# # Add features to our figure
# plt.legend()
# plt.grid(True, linestyle =':')
# plt.xlim([-6, 6])
# plt.ylim([-4, 4])
 
# plt.title('Taylor Polynomials of cos(x) at x = 0')
# plt.xlabel('x-axis')
# plt.ylabel('y-axis')
 
# # Show plot
# plt.show()