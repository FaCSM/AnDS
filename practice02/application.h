#ifndef APPLICATION_H
#define APPLICATION_H

class TApplication {
public:
    static int execute();
private:
    static void help();
    static bool menu(char&);
};

#endif
