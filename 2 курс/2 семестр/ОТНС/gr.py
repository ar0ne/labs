from tkinter import Canvas,Tk,LAST
from shelve import open

root = Tk()

canvas = Canvas(root,width = 640,height = 480,bg="white")
canvas.create_line(320,480,320,0,arrow=LAST)
canvas.create_line(0,240,640,240,arrow=LAST)

db = open('db.file')
dots = db['res']
db.close()

for i in range(len(dots)-1):
    canvas.create_line((i * 4 + 320),(dots[i] * 1000000 * 2 + 240) ,((i+1) * 4 + 320),(dots[i+1] * 1000000 *2 + 240))
    #print('%-10f' % (dots[i]) )


canvas.pack()
root.mainloop()