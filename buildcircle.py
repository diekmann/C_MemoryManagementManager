#!/usr/bin/env python
import time
import math
import curses
stdscr = curses.initscr()

termHeight, termWidth = stdscr.getmaxyx()

def BresenhamCircle(x0, y0, radius, setPixel):
    
    octants = [22,11,44,33,4,2,3,1]
    
    while len(octants) > 0: 
        octant = octants[0]
        octants = octants[1:]
        
        error = 1 - radius
        errorY = 1
        errorX = -2 * radius
        x = radius
        y = 0

        if octant == 11: 
            setPixel(x0, y0 + radius)
        elif octant == 22:
            setPixel(x0, y0 - radius)
        elif octant == 33:
            setPixel(x0 + radius, y0)
        elif octant == 44:
            setPixel(x0 - radius, y0)

        while(y < x):
            if (error > 0): # >= 0 produces a slimmer circle. =0 produces the circle picture at radius 11 above
                x -= 1
                errorX += 2
                error += errorX
            y += 1
            errorY += 2
            error += errorY
            
            if octant == 1: 
                setPixel(x0 + x, y0 + y)
            elif octant == 2:
                setPixel(x0 - x, y0 + y)
            elif octant == 3:
                setPixel(x0 + x, y0 - y)
            elif octant == 4:
                setPixel(x0 - x, y0 - y)
            elif octant == 11:
                setPixel(x0 + y, y0 + x)
            elif octant == 22:
                setPixel(x0 - y, y0 + x)
            elif octant == 33:
                setPixel(x0 + y, y0 - x)
            elif octant == 44:
                setPixel(x0 - y, y0 - x)

def drawCirle(x, y, width, height, setPixel):
    deg = 0
    while deg < 360.0 :
        x = width+(int)(width * math.cos(deg * 180.0 / math.pi))
        y = height+(int)(height * math.sin(deg * 180.0 / math.pi))

        #mvaddch(y,x,DOT)
        setPixel(x, y)
        deg += 1.0

def setPixelCurses(x, y):
    stdscr.addstr(y, x, "X", curses.A_REVERSE)
    stdscr.refresh()
    time.sleep(0.01)


def curses_start():
    curses.noecho()
    curses.cbreak()
    
    curses.curs_set(0)
    #stdscr.move(10,5)
    
    #stdscr.addstr(termHeight/2, termWidth/2, "X", curses.A_REVERSE)
    
    radius = max(0, min(termWidth/2-3, termHeight/2-3))
    
    txt = "... building ..."
    
    stdscr.addstr(termHeight/2, termWidth/2-len(txt)/2, txt, curses.A_STANDOUT)
    
    BresenhamCircle(termWidth/2, termHeight/2, radius, setPixelCurses)
    #drawCirle(termWidth/2, termHeight/2, 20, 20, setPixelCurses)
    stdscr.refresh()
    
    #time.sleep(2)
    
    stdscr.clear()
    stdscr.refresh()
    
    for _ in range(10):
        stdscr.addstr(termHeight/2, termWidth/2-len(txt)/2, " "*len(txt), curses.A_STANDOUT)
        for i in range(len(txt)):
            stdscr.addstr(termHeight/2-len(txt)/2+i, termWidth/2, " ", curses.A_STANDOUT)
        stdscr.refresh()
        time.sleep(0.5)
        
        stdscr.clear()
        stdscr.addstr(termHeight/2, termWidth/2-len(txt)/2, txt, curses.A_STANDOUT)
        stdscr.refresh()
        time.sleep(0.5)
    
    time.sleep(2)
    
    
    #restore terminal
    curses.nocbreak()
    stdscr.keypad(0)
    curses.echo()
    curses.endwin()


if __name__ == "__main__":
    print "strating ..."
    try:
        curses_start()
        print "building ..."
    except:
        curses.nocbreak()
        stdscr.keypad(0)
        curses.echo()
        curses.endwin()
        print "crashed, restoring terminal"
        raise
    
    

