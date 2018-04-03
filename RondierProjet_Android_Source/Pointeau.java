package com.project.rondierprojet;

/**
 * @file Pointeau.java
 * @brief Définition de la classe de gestion d'un pointeau.
 * @version 1.1
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe modélisant un pointeau.
 */
public class Pointeau {

    private int id;
    private String idTag;
    private String nom;
    private int numero;
    private int ordrePassage;

    /**
     * @brief Constructeur Pointeau
     * Permet de créer un pointeau en fournissant son id, son idTag, son nom, son numero ainsi que son ordre de passage.
     * @param id L'ID du pointeau.
     * @param idTag L'ID du tag MiFare associé au pointeau.
     * @param nom Le nom du pointeau.
     * @param numero Le numéro du pointeau.
     * @param ordrePassage L'ordre de passage du pointeau.
     */
    public Pointeau(int id, String idTag, String nom, int numero, int ordrePassage)
    {
        this.id = id;
        this.idTag = idTag;
        this.nom = nom;
        this.numero = numero;
        this.ordrePassage = ordrePassage;
    }

    /**
     * @brief Constructeur Pointeau
     * Permet de créer un pointeau en fournissant son id, son idTag, son nom ainsi que son numero.
     * @param id L'ID du pointeau.
     * @param idTag L'ID du tag MiFare associé au pointeau.
     * @param nom Le nom du pointeau.
     * @param numero Le numéro du pointeau.
     */
    public Pointeau(int id, String idTag, String nom, int numero)
    {
        this.id = id;
        this.idTag = idTag;
        this.nom = nom;
        this.numero = numero;
    }

    /**
     * @brief Obtenir l'ordre de passag d'un pointeau.
     * Permet d'obtenir l'ordre de passage associé à un pointeau.
     * @return L'ordre de passage du pointeau.
     */
    public int obtenirOrdrePassage() {
        return ordrePassage;
    }

    /**
     * @brief Définir un ordre de passage d'un pointeau.
     * Permet de définir un ordre de passage associé à un pointeau.
     * @param ordrePassage L'ordre de passage associé au pointeau.
     */
    public void definirOrdrePassage(int ordrePassage) {
        this.ordrePassage = ordrePassage;
    }

    /**
     * @brief Otebnir le numéro d'un pointeau.
     * Permet d'obtenir le numéro associé à un pointeau.
     * @return Le numéro associé au pointeau.
     */
    public int obtenirNumero() {
        return numero;
    }

    /**
     * @brief Obtenir l'idTag d'un pointeau.
     * Permet d'obtenir l'idTag associé à un pointeau.
     * @return L'ID du tag associé au pointeau.
     */
    public String obtenirIdTag() {
        return idTag;
    }

    /**
     * @brief Obtenir le nom d'un pointeau.
     * Permet de obtenir le nom associé à un pointeau.
     * @return Le nom du pointeau.
     */
    public String obtenirNom() {
        return nom;
    }

    /**
     * @brief Obtenir l"id d'un pointeau.
     * Permet de obtenir l"id associé à un pointeau.
     * @return L'ID du pointeau.
     */
    public int obtenirId() {
        return id;
    }
}