#ifndef AED_TRANSPORTESPUBLICOSPORTO_LINE_H
#define AED_TRANSPORTESPUBLICOSPORTO_LINE_H

#include "Stop.h"
#include <string>
#include <vector>

class Line {
    string code;
    string name;
    vector<Stop*> stops;
public:
    /**
     * Construtor da classe.
     * @param code código único string da linha
     * @param name string representativa do nome da linha
     */
    Line(const string& code, const string& name);

    /**
    * Método void que adiciona a stop recebida ao vetor stops atributo da classe
    * @param stop apontador para instância de Stop
    */
    void addStop(Stop* stop);
    /** Getter do atributo code */
    string getCode() const;
    /** Getter do atributo name */
    string getName() const;
    /** Getter do atributo stops */
    const vector<Stop*> &getStops() const;
};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LINE_H
