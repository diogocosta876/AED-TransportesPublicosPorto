#ifndef AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H
#define AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H

#include "LoadData.h"

/**
 * Classe AdminMenu
 * @details A classe AdminMenu relaciona-se diretamente com a classe LoadData,
 * por meio do atributo data. Esta classe configura a UI do programa e toda a lógica
 * do menu.
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
     * @param page_counter inteiro relativo à página em que se encontra o menu
     */
    void mainMenu(int page_counter = 1);
private:
    /**
     * Método void utilizado para apresentar no ecrã as paragens da linha selecionada,
     * permitindo a seleção de uma paragem
     * @param line apontador para instância da classe Line, indica ao menu sobre que linha apresentar a informação
     */
    void lineMenu(Line* line);
    /**
     * Método void utilizado para apresentar no ecrã as paragens de origem, destino e
     * mostrar ao utilizador as opções de cálculo do percurso disponíveis.
     */
    void tripMenu();
    /**
    * Método void utilizado para apresentar no ecrã as paragens do percurso calculado e informação acerca do percurso
    * @param path vetor de inteiros, guarda os id's das paragens do percurso ordenadas
    * @param path_distance double, distância percorrida no percurso, se o valor for -1 esta será calculada
    * @param lines vetor de strings, guarda as linhas ou zonas atravessadas no percurso, se aplicável
    */
    void pathMenu(const vector<int>& path, double path_distance = -1, const vector<string>& lines = {});
    /**
     * Método void que permite ao utilizador selecionar uma paragem pelo código único
    */
    void selectStopByCodeMenu();
    /**
     * Método void que apresenta ao utilizador as paragens mais próximas,
     * pedindo-lhe as coordenadas (lat e long)
    */
    void selectStopByLocationMenu();
    /**
     * Método void que recebe uma paragem e a seleciona como origem ou destino
     * @param stop apontador para uma instância da class Stop
    */
    void selectStop(Stop* stop);
    /**
     * Método normal que verifica se o input do utilizador é válido,
     * para um número indefinido de inputs possíveis.
     * * @param possible_inputs vetor de int
     * @return inteiro input do utilizador
    */
    static int getUserInput(const vector<int>& inputs);
    /**
     * Método normal que verifica se o input do utilizador é válido.
     * @param possible_inputs vetor de string
     * @return string input do utilizador
     */
    static string getUserTextInput(const vector<string>& possible_inputs = {});
    /**
     * Método void que formata uma string segundo um tamanho definido
     * para apresentar no ecrã nas listagens.
     * @param s string
     * @param linelength inteiro
     */
    static void printInTable(const string &s, int linelength);
    /**
     * Método void que apresenta o título do menu
     */
    static void printTitle();
    /**
     * Método void que "limpa" o ecrã
     */
    static void clearScreen();

};

#endif //AED_TRANSPORTESPUBLICOSPORTO_ADMINMENU_H
