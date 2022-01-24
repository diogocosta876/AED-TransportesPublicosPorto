#ifndef AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H
#define AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H

#include "LoadData.h"

/**
 * Classe AdminMenu
 * @details A classe AdminMenu relaciona-se diretamente com a classe LoadData,
 * por meio do atributo data. Esta classe configura a UI do programa, toda a lógica
 * do menu e certas operações de sorting/filtragem.
 */

class AdminMenu {
    LoadData data;
    int selectedStopID_origin = -1;
    int selectedStopID_destination = -1;
public:
    /**
     * Construtor da classe.
     * @param data membro da classe LoadData
     * @see LoadData
     */
    explicit AdminMenu(LoadData data);
    /**
     * Método void utilizado para apresentar no ecrã as opções, relativas
     * a um conjunto de data definido por um membro LoadData, do menu inicial ao
     * utilizador.
     * @param size_listing inteiro relativo ao tamanho da listagem
     */
    void mainMenu(int page_counter = 1);
private:
    void selectStop(Stop* stop);
    void selectStopByCodeMenu();
    void selectStopByLocationMenu(bool userInsertedLocation = false, double lat = -INT_MAX, double lon=-INT_MAX);
    void lineMenu(Line* line);
    void tripMenu();
    void pathMenu(const vector<int>& path, double path_distance = -1, const vector<string>& lines = {});
    static int getUserInput(const vector<int>& inputs);
    static string getUserTextInput(const vector<string>& possible_inputs = {});
    static void printInTable(const string &s, int linelength);
    static void printTitle();
    static void clearScreen();

};


#endif //AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H
