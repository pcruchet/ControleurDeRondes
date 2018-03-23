#ifndef ASSOCIATIONAGENTSRONDES_H
#define ASSOCIATIONAGENTSRONDES_H

/**
 * @author Tanguy Herbron
 * @brief Déclaration de la classe AssociationAgentsRondes
 */

class AssociationAgentsRondes
{
public:
    //Constructeur - Destructeur
    AssociationAgentsRondes(int _idAgent, int _idRonde);

    // Getters - Setters
    int ObtenirIdAgent();
    int ObtenirIdRonde();

    void DefinirIdAgent(int _idAgent);
    void DefinirIdRonde(int _idRonde);

private:
    int idAgent;
    int idRonde;
};

#endif // ASSOCIATIONAGENTSRONDES_H
