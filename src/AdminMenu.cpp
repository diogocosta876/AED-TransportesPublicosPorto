
#include "AdminMenu.h"

#include <utility>

AdminMenu::AdminMenu(LoadData data): data(std::move(data)){}

void AdminMenu::mainMenu(int page_counter) {
    //For faster development //TODO REMOVE PATH DEBUGGING SCREEN
    //selectedStopID_origin = 215;
    //selectedStopID_destination = 234;
    selectedStopID_origin = 1123;
    selectedStopID_destination = 1124;

    //Checks if stops have already been selected
    if(selectedStopID_origin != -1 && selectedStopID_destination != -1) tripMenu();
    printTitle();

    int table_length = 69;
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";
    printInTable("ID", 10);
    printInTable("Line Code", 15);
    printInTable("Line Name", 40);
    cout << "|\n";
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    //Table Content
    vector<int> possible_inputs_selection;
    for (int i = (page_counter-1)*6; i < page_counter*6; ++i) {
        if (i == data.getLines().size()) break;
        printInTable(to_string(i), 10);
        printInTable(data.getLines()[i]->getCode(), 15);
        printInTable(data.getLines()[i]->getName(), 40);
        cout << "|\n";
        possible_inputs_selection.push_back(i);
    }
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-";
    size_t totalpages = data.getLines().size()/6 + (data.getLines().size()%6>0);
    cout << "\n> Page " << page_counter << "/" << totalpages;
    if (selectedStopID_origin != -1) cout << "\tOrigin: " << data.getStops()[selectedStopID_origin]->getCode();
    cout << "\n\n";
    cout << "\tAdmin Menu\n";
    cout << "(1) Select a Line\n";
    cout << "(2) Select a Stop\n";
    cout << "(3) Select a Location\n";
    cout << "(4) Next Page\n";
    cout << "(5) Previous Page\n";
    cout << "(0) Exit\n";
    cout << " > ";

    //Receive input
    vector<int> possible_inputs = {0,1,2,3,4,5};
    int input; int input_sub;
    input = getUserInput(possible_inputs);

    switch (input) {
        case 1:
            cout << "(" << possible_inputs_selection.front() << " to " << possible_inputs_selection.back() <<") >";
            input_sub = getUserInput(possible_inputs_selection);
            clearScreen();
            lineMenu(data.getLines()[input_sub]);
            break;
        case 2: {
            selectStopByCodeMenu();
            break;
        }
        case 3:
            selectStopByLocationMenu();
            break;
        case 4:
            clearScreen();
            if (page_counter==totalpages) mainMenu(page_counter);
            else mainMenu(page_counter+1);
            break;
        case 5:
            clearScreen();
            if (page_counter==1) mainMenu(page_counter);
            else mainMenu(page_counter-1);
            break;
        case 0:
            exit(0);
        default:
            break;
    }
}

void AdminMenu::lineMenu(Line* line) {
    printTitle();

    int table_length = 65;
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";
    printInTable("ID", 10);
    printInTable("Stop Code", 15);
    printInTable("Stop Name", 25);
    printInTable("Zone", 10);
    cout << "|\n";
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    //Table Content
    for (int i = 0; i < line->getStops().size(); ++i) {
        if (i == data.getLines().size()) break;
        printInTable(to_string(i), 10);
        printInTable(line->getStops()[i]->getCode(), 15);
        printInTable(line->getStops()[i]->getName(), 25);
        printInTable(line->getStops()[i]->getZone(), 10);

        cout << "|\n";
    }
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-";

    cout << "\n\n";
    cout << "\tAdmin Menu\n";
    cout << "(1) Select a Stop\n";
    cout << "(2) Go Back\n";
    cout << "(0) Exit\n";
    cout << " > ";

    //Receive input
    vector<int> possible_inputs = {0,1,2}; vector<int> possible_inputs_selection;
    int input; int input_sub;
    input = getUserInput(possible_inputs);

    switch (input) {
        case 1:
            for (int i = 0; i < line->getStops().size(); ++i) possible_inputs_selection.push_back(i);
            cout << "(0 to " + to_string(line->getStops().size()-1)+")";
            input_sub = getUserInput(possible_inputs_selection);
            selectStop(line->getStops()[input_sub]);
            clearScreen();
            mainMenu(1);
            break;
        case 2:
            clearScreen();
            mainMenu(1);
            break;
        case 0:
            exit(0);
        default:
            break;
    }
}

void AdminMenu::tripMenu() {
    printTitle();

    int table_length = 57;
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";
    printInTable("Origin", 55); cout << "|\n";
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    //Table Content
    Stop* origem = data.getStops()[selectedStopID_origin];
    printInTable(origem->getCode(), 10);
    printInTable(origem->getZone(), 8);
    printInTable(origem->getName(), 35);
    cout << "|\n";
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";
    printInTable("Destination", 55); cout << "|\n";
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    //Table Content
    Stop* destino = data.getStops()[selectedStopID_destination];
    printInTable(destino->getCode(), 10);
    printInTable(destino->getZone(), 8);
    printInTable(destino->getName(), 35);
    cout << "|\n";
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";
    cout << "Walking distance: " << data.getWalkingDistance() << " km" <<"\n";

    cout << "\n";
    cout << "\tAdmin Menu\n";
    cout << "(1) Determine the Shortest Path\n";
    cout << "(2) Determine the Path with less Stops\n";
    cout << "(3) Determine the Path with less Line Changes\n";
    cout << "(4) Determine the Cheapest Path (less zones crossed)\n";
    cout << "(5) Change Walking Distance\n";
    cout << "(6) Go Back\n";
    cout << "(0) Exit\n";
    cout << " > ";

    //Receive input
    vector<int> possible_inputs = {0,1,2,3,4,5,6}; vector<string> possible_inputs_selection;
    int input;
    input = getUserInput(possible_inputs);

    switch (input) {
        case 1: {
            //SHORTEST PATH (DIJKSTRA)
            auto path_data = data.getGraph().dijkstra_util(selectedStopID_origin, selectedStopID_destination);
            pathMenu(path_data.first.first, path_data.first.second);
            break;
        }
        case 2: {
            //PATH WITH LESS STOPS (PESQUISA EM LARGURA BFS)
            vector<int> path = data.getGraph().bfsPathSearch(selectedStopID_origin, selectedStopID_destination);
            pathMenu(path);
            break;
        }
        case 3: {
            //PATH WITH LESS LINE CHANGES
            auto path_data = data.getGraph().determineLessLineChangesPath(selectedStopID_origin, selectedStopID_destination);
            vector<int> path;
            vector<string> lines;
            for (const pair<int, string>& stop: path_data){
                path.push_back(stop.first);
                if (find(lines.begin(), lines.end(), stop.second) == lines.end())
                    lines.push_back(stop.second);
            }
            pathMenu(path, -1, lines);
            break;
        }
        case 4: {
            //PATH WITH LESS ZONES CROSSED
            auto path_data = data.getGraph().determineLessZonesCrossedPath(selectedStopID_origin,
                                                                          selectedStopID_destination);
            vector<int> path;
            vector<string> zones;
            for (const pair<int, string>& stop: path_data) {
                path.push_back(stop.first);
                if (find(zones.begin(), zones.end(), stop.second) == zones.end())
                    zones.push_back(stop.second);
            }
            pathMenu(path, -1, zones);
            break;
        }
        case 5: {
            possible_inputs_selection = {"0", "0.1", "0.25", "0.50", "1", "2", "5"};
            cout << "(0, 0.1, 0.25, 0.5, 1, 2 or 5) > ";
            double walking_distance = stod(getUserTextInput(possible_inputs_selection));
            data = LoadData(walking_distance);
            tripMenu();
            break;
        }
        case 6:
            selectedStopID_origin = -1;
            selectedStopID_destination = -1;
            mainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void AdminMenu::pathMenu(const vector<int>& path, double path_distance, const vector<string>& lines) {
    printTitle();

    int table_length = 57;
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";
    printInTable("Path", 55); cout << "|\n";
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    //Table Content
    Stop* origem = data.getStops()[selectedStopID_origin];
    printInTable("Code", 10);
    printInTable("Zone", 8);
    printInTable("Name", 35);
    cout << "|\n";

    for (int stopID: path) {
        auto stop = data.getStops()[stopID];
        printInTable(stop->getCode(), 10);
        printInTable(stop->getZone(), 8);
        printInTable(stop->getName(), 35);
        cout << "|\n";
    }
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-"; cout << "\n";

    if (path_distance == -1) path_distance = data.getGraph().determineDistanceTraveled(path);
    cout << "Stop Count: " << path.size() << endl;
    if(!lines.empty()) {
        cout << "Lines/Zones Used:";
        for (const auto& line: lines)
            cout << line << " ";
        cout << "\n";
    }
    cout << "Distance Traveled: " << path_distance << endl;

    cout << "\n";
    cout << "\tAdmin Menu\n";
    cout << "(1) Go Back\n";
    cout << "(2) Go to the Main Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    //Receive input
    vector<int> possible_inputs = {0,1,2,3,4,5,6}; vector<string> possible_inputs_selection;
    int input; int input_sub;
    input = getUserInput(possible_inputs);

    switch (input) {
        case 1:
            tripMenu();
            break;
        case 2:
            selectedStopID_origin = -1;
            selectedStopID_destination = -1;
            mainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void AdminMenu::selectStopByCodeMenu() {
    cout << "Insert Stop Code (0 to go back)> ";
    string stop_name = getUserTextInput();
    if (stop_name == "0") mainMenu();
    bool found = false;
    for (Stop* stop: data.getStops()){
        if (stop->getCode() == stop_name){
            selectStop(stop);
            clearScreen();
            mainMenu(1);
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nStop Not Found! Try Again\n";
        selectStopByCodeMenu();
    }
}

void AdminMenu::selectStopByLocationMenu() {
    double lat = -INT_MAX;
    double lon = -INT_MAX;

    while (lat == -INT_MAX) {
        cin.clear();
        if (!cin) cin.ignore(1000,'\n');
        cout << "Insert latitude > ";
        cin >> lat;
    }
    while (lon == -INT_MAX) {
        cin.clear();
        if (!cin) cin.ignore(1000,'\n');
        cout << "Insert longitude > ";
        cin >> lon;
    }
    vector<pair<Stop*, double>> closest_stops;
    double min_dist = INT_MAX;
    for(Stop* stop: data.getStops()){

        sort(closest_stops.begin(), closest_stops.end(), [ ]( const pair<Stop*, double>& lhs, const pair<Stop*, double>& rhs )
        {
            return lhs.second < rhs.second;
        });

        double dist = Graph::haversine(lat, lon, stop->getLatitude(), stop->getLongitude());
        if (dist < min_dist){
            pair<Stop*, double> mypair;
            mypair.first = stop; mypair.second = dist;
            if(closest_stops.size() < 5)
                closest_stops.push_back(mypair);
            else {
                closest_stops[4] = mypair;
                min_dist = closest_stops[3].second;
            }
        }
    }

    //OUTPUT
    printTitle();

    int table_length = 80;
    cout << "5 CLOSEST STOPS:\n";
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-";
    cout << "\n";
    printInTable("ID", 10);
    printInTable("Stop Code", 15);
    printInTable("Stop Name", 25);
    printInTable("Zone", 10);
    printInTable("Distance", 13);
    cout << "|\n";
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-";
    cout << "\n";

    //Table Content
    for (int i = 0; i < closest_stops.size(); ++i) {
        printInTable(to_string(i), 10);
        printInTable(closest_stops[i].first->getCode(), 15);
        printInTable(closest_stops[i].first->getName(), 25);
        printInTable(closest_stops[i].first->getZone(), 10);
        printInTable(to_string(closest_stops[i].second), 13);
        cout << "|\n";
    }
    //Table Line Separator
    for (int i = 0; i < table_length; ++i) cout << "-";
    cout << "\n\n";
    cout << "\tAdmin Menu\n";
    cout << "(1) Select a Stop\n";
    cout << "(2) Go Back\n";
    cout << "(0) Exit\n";
    cout << " > ";

    //Receive input
    vector<int> possible_inputs = {0, 1, 2};
    vector<int> possible_inputs_selection;
    int input;
    int input_sub;
    input = getUserInput(possible_inputs);

    switch (input) {
        case 1:
            for (int i = 0; i < closest_stops.size(); ++i) possible_inputs_selection.push_back(i);
            cout << "(0 to " + to_string(closest_stops.size()-1)+")";
            input_sub = getUserInput(possible_inputs_selection);
            selectStop(closest_stops[input_sub].first);
            clearScreen();
            mainMenu(1);
            break;
        case 2:
            clearScreen();
            mainMenu(1);
            break;
        case 0:
            exit(0);
        default:
            break;
    }
}

void AdminMenu::selectStop(Stop *stop) {
    auto hashTable = data.getStopCodes();
    int index = hashTable.find(stop->getCode())->second;
    if (selectedStopID_origin == -1) selectedStopID_origin = index;
    else selectedStopID_destination = index;
}

int AdminMenu::getUserInput(const vector<int>& inputs) {
    int input;
    if(!cin){
        cin.ignore();
        cin.ignore(100,'\n');
        cin.clear();
    }
    cin >> input;
    while (cin.fail() || (find(inputs.begin(), inputs.end(), input) == inputs.end())) {    // assures that input is valid
        if (cin.eof() || input == 0) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore();
        cerr << "Not a valid input, please input one of the shown options: ";
        cin >> input;
    }
    cin.ignore(100, '\n');
    return input;
}

string AdminMenu::getUserTextInput(const vector<string>& possible_inputs) {
    string input;
    getline(cin, input);
    if (cin.fail()) cout << "deez";
    bool found = false;
    if (possible_inputs.empty()) found = true;
    for (const string& my_string: possible_inputs){
        if (my_string == input) found = true;
    }
    while (cin.fail() || input.length() == 0 || !found) {    // assures that input is valid
        if (cin.eof()) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(100, '\n');
        cerr << "Not a valid input, please try again: ";
        getline(cin, input);
        for (const string &my_string: possible_inputs) {
            if (my_string == input)found = true;
        }
        if (possible_inputs.empty()) found = true;
    }
    return input;
}

void AdminMenu::printInTable(const string &s, int linelength) {
    int spaces;
    bool uneven = false;
    if ((linelength - int(s.size())) % 2 == 1) uneven = true;
    spaces = ( linelength - int(s.size()) ) / 2;
    cout << "|";
    if ( spaces > 0 ) cout << string( spaces, ' ' );
    cout << s;
    if ( spaces > 0 ) cout << string( spaces, ' ' );
    if (uneven) cout << " ";
}

void AdminMenu::clearScreen() {
    for (int i = 0; i < 20; ++i) {
        cout << "\n";
    }
}

void AdminMenu::printTitle() {
    cout << R"(
____ ___ ____ ___           ___ ____ ____ _  _ ____ ___  ____ ____ ___ ____ ____    ___  _  _ ___  _    _ ____ ____ ___
[__   |  |    |__]    __     |  |__/ |__| |\ | [__  |__] |  | |__/  |  |___ [__     |__] |  | |__] |    | |    |  | [__
___]  |  |___ |              |  |  \ |  | | \| ___] |    |__| |  \  |  |___ ___]    |    |__| |__] |___ | |___ |__| ___])"
<< endl;
}


