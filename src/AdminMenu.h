#ifndef AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H
#define AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H

#include "LoadData.h"

class AdminMenu {
    LoadData data;
    int selectedStopID_origin = -1;
    int selectedStopID_destination = -1;
    float walkingDistance = 1;
public:
    explicit AdminMenu(LoadData data);
    void mainMenu(int page_counter = 1);
private:
    void selectStop(Stop* stop);
    void selectStopByCodeMenu();
    void selectStopByLocationMenu(bool userInsertedLocation = false, double lat = -INT_MAX, double lon=-INT_MAX);
    void lineMenu(Line* line);
    void tripMenu();
    void pathMenu(vector<int> path, double path_distance = -1, vector<string> lines = {{}});
    static int getUserInput(const vector<int>& inputs);
    static string getUserTextInput(const vector<string>& possible_inputs = {});
    static void printInTable(const string &s, int linelength);
    static void printTitle();
    static void clearScreen();

};


#endif //AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H
