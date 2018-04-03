package com.project.rondierprojet;

import java.util.List;

/**
 * @file Ronde.java
 * @brief Définition de la classe de gestion de ronde
 * @version 1.0
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe modélisant une ronde.
 */
public class Ronde {
    private int id;
    private String nom;
    private List<Pointeau> pointeauList;
    private int index = 0;
    private int numeroRonde;

    /**
     * @brief Constructeur Ronde
     * Permet de créer une ronde en fournissant son id et son nom.
     * @param id L'ID de la ronde.
     * @param nom Le nom de la ronde.
     */
    public Ronde(int id, String nom, List<Pointeau> pointeauList, int numeroRonde)
    {
        this.id = id;
        this.nom = nom;
        this.pointeauList = pointeauList;
        this.numeroRonde = numeroRonde;
    }

    /**
     * @brief Obtenir l'ID d'une ronde.
     * Permet d'obtenir l'ID attribué à une ronde.
     * @return L'ID de la ronde.
     */
    public int obtenirId()
    {
        return id;
    }

    /**
     * @brief Obtenir le nom d'une ronde.
     * Permet d'obtenir le nom attribué à une ronde.
     * @return Le nom de la ronde.
     */
    public String obtenirNom()
    {
        return nom;
    }

    /**
     * @brief Obtenir la liste des pointeaux d'une ronde.
     * Permet d'obtenir une liste de pointeaux que comporte une ronde.
     * @return La liste de pointeaux associés à cette ronde.
     */
    public List<Pointeau> obtenirListePointeaux()
    {
        return pointeauList;
    }

    /**
     * @brief Obtenir le numero d'une ronde.
     * Permet d'obtenir le numero attribué à une ronde.
     * @return Le numéro de la ronde.
     */
    public int obtenirNumeroRonde() {
        return numeroRonde;
    }

    /**
     * @brief Obtenir l'index d'une ronde.
     * Permet d'obtenir l'index d'une ronde.
     * @return L'index de la ronde.
     */
    public int obtenirIndex() {
        return index;
    }

    /**
     * @brief Définir l'index d'une ronde.
     * Permet de définir l'index d'une ronde.
     * @param index L'index présent dans la ronde.
     */
    public void definirIndex(int index) {
        this.index = index;
    }
}