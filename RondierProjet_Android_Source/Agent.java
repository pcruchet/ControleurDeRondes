package com.project.rondierprojet;

/**
 * @file Agent.java
 * @brief Définition de la classe de gestion d'un agent
 * @version 1.1
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe modélisant un agent de sécurité
 */
public class Agent {

    private int id;
    private String idTag;
    private String nom;
    private String prenom;

    /**
     * @brief Constructeur Agent
     * Permet de créer un agent en fournissant son id, son nom ainsi que son prénom.
     * @param idTag Id correspondant au tag MiFare associé à l'agent.
     * @param nom Nom de l'agent.
     * @param prenom Prénom de l'agent.
     */
    public Agent(int id, String idTag, String nom, String prenom)
    {
        this.id = id;
        this.idTag = idTag;
        this.nom = nom;
        this.prenom = prenom;
    }

    /**
     * @brief Obtenir l'id d'un agent.
     * Permet d'obtenir l'id attribué à un agent.
     * @return Retourne l'id de l'agent.
     */
    public int obtenirId() {
        return id;
    }

    /**
     * @brief Obtenir le nom d'un agent.
     * Premet d'obtenir le nom attribué à un agent.
     * @return Le nom de l'agent.
     */
    public String obtenirNom()
    {
        return nom;
    }
}