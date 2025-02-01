#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H

class TApplication {
public:
    static int execute();      // Execute the main thread
private:
    static int executeList();  // Execute the list thread
    static int executeDArr();  // Execute the dynamic array thread
    static int executeStack(); // Execute the stack thread
    static int executeRPN();   // Execute the polish notation thread

    static void helpList();    // Print the available list commands
    static void helpDArr();    // Print the available dynamic array commands
    static void helpStack();   // Print the available stack commands

    static bool menu(char&);   // Wait for user's choice
};


#endif
