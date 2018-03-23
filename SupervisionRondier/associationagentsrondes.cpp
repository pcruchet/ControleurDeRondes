#include "associationagentsrondes.h"

AssociationAgentsRondes::AssociationAgentsRondes(int _idAgent, int _idRonde) :
    idAgent(_idAgent),
    idRonde(_idRonde)
{

}

int AssociationAgentsRondes::ObtenirIdAgent()
{
    return idAgent;
}

int AssociationAgentsRondes::ObtenirIdRonde()
{
    return idRonde;
}

void AssociationAgentsRondes::DefinirIdAgent(int _idAgent)
{
    idAgent = _idAgent;
}

void AssociationAgentsRondes::DefinirIdRonde(int _idRonde)
{
    idRonde = _idRonde;
}
