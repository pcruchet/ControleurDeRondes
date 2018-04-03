package com.project.rondierprojet;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Environment;
import android.util.Log;

import java.io.File;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

/**
 * @file GestionBDD.java
 * @brief Définition de la classe de gestion de la base de données
 * @version 1.2
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe gérant les requête SQL envoyées sur le fichier sqlite.
 * Cette classe permet d'injecter de nouvelles données ainsi que de récupérer des données précédemment écrites.
 */
public class GestionBDD extends SQLiteOpenHelper {

    // Version de la base de données
    // Changer le numéro de version et relancer une requête pour renouveler la base de données
    private static final int DATABASE_VERSION = 37;
    // Nom de la base de données
    private static final String DATABASE_NAME = "ControleurDeRonde.db";
    // Nom des tables
    private static final String TABLE_AGENTS = "Agents";
    private static final String TABLE_RONDES = "Rondes";
    private static final String TABLE_POINTEAUX = "Pointeaux";
    private static final String TABLE_HISTORIQUE_POINTEAU = "HistoriquePointeau";
    private static final String TABLE_MAIN_COURANTE = "MainCourante";
    private static final String TABLE_ASSOCIATION_POINTEAUX_RONDES = "AssociationPointeauxRondes";
    private static final String TABLE_ASSOCIATION_AGENTS_RONDES = "AssociationAgentsRondes";
    // Nom des colonnes de la table Agents
    private static final String CLE_AGENT_ID = "idAgent";
    private static final String CLE_AGENT_TAG_ID = "idTag";
    private static final String CLE_NOM_AGENT = "nom";
    private static final String CLE_PRENOM_AGENT = "prenom";
    // Nom des colonnes de la table Rondes
    private static final String CLE_RONDE_ID = "idRonde";
    private static final String CLE_NOM_RONDE = "nom";
    // Nom des colonnes de la table Pointeaux
    private static final String CLE_POINTEAU_ID = "idPointeau";
    private static final String CLE_POINTEAU_TAG_ID = "idTag";
    private static final String CLE_POINTEAU_NOM = "nom";
    private static final String CLE_POINTEAU_NUMERO = "numero";
    // Nom des colonnes de la table HistoriquePointeau
    private static final String CLE_HP_ID = "id";
    private static final String CLE_HP_AGENT_ID = "idAgent";
    private static final String CLE_HP_RONDE_ID = "idRonde";
    private static final String CLE_HP_POINTEAU_ID = "idPointeau";
    private static final String CLE_HP_DATE = "date";
    private static final String CLE_HP_ORDRE_POINTEAU = "ordrePointeau";
    private static final String CLE_HP_NUMERO_RONDE = "numeroRonde";
    // Nom des colonnes de la table MainsCourantes
    private static final String CLE_MAIN_COURANTE_ID = "id";
    private static final String CLE_MAIN_COURANTE_TEXT = "texte";
    private static final String CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU = "idHistoriquePointeau";
    private static final String CLE_MAIN_COURANTE_DATE = "date";
    private static final String CLE_MAIN_COURANTE_TYPE = "type";
    // Nom des colonnes de la table AssociationPointeauxRondes
    private static final String CLE_APR_ID = "id";
    private static final String CLE_APR_POINTEAU_ID = "idPointeau";
    private static final String CLE_APR_RONDE_ID = "idRonde";
    private static final String CLE_APR_ORDRE_POINTEAU = "ordrePointeau";
    // Nom des colonnes de la table AssociationAgentsRondes
    private static final String CLE_AAR_ID = "id";
    private static final String CLE_AAR_RONDE_ID = "idRonde";
    private static final String CLE_AAR_AGENT_ID = "idAgent";

    /**
     * @brief Constructeur appelé à la création d'une instance bdd.
     * Ce constructeur permet de créer le fichier sqlite s'il n'existe pas déjà et de réinitialiser les tables si un changement de version a eu lieu.
     * @param context Le contexte de l'application.
     */
    public GestionBDD(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    /**
     * @brief Méthode appelée automatiquement après l'instanciation de la classe.
     * La méthode onCreate est une méthode appelée par le système Android à l'instanciation de la classe.
     * Cette méthode est ici utilisée pour créer toutes les tables nécessaires au bon fonctionnement du système. Si les tables existent déjà, rien n'est changé.
     * Toutes les créations sont faites grâce aux variables précédemment définies.
     * @param db La base de données dans laquelle il faut créer les tables.
     */
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_AGENTS + "("
                + CLE_AGENT_ID + " INTEGER PRIMARY KEY,"
                + CLE_AGENT_TAG_ID + " VARCHAR(8),"
                + CLE_NOM_AGENT + " VARCHAR(45),"
                + CLE_PRENOM_AGENT + " VARCHAR(45)"
                + ");");

        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_RONDES + "("
                + CLE_RONDE_ID + " INTEGER PRIMARY KEY,"
                + CLE_NOM_RONDE + " VARCHAR(30)"
                + ");");

        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_POINTEAUX + "("
                + CLE_POINTEAU_ID + " INTEGER PRIMARY KEY,"
                + CLE_POINTEAU_TAG_ID + " VARCHAR(8),"
                + CLE_POINTEAU_NOM + " VARCHAR(20),"
                + CLE_POINTEAU_NUMERO + " INTEGER"
                + ");");

        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_HISTORIQUE_POINTEAU + "("
                + CLE_HP_ID + " INTEGER PRIMARY KEY,"
                + CLE_HP_AGENT_ID + " INTEGER,"
                + CLE_HP_RONDE_ID + " INTEGER,"
                + CLE_HP_POINTEAU_ID + " INTEGER,"
                + CLE_HP_DATE + " DATE,"
                + CLE_HP_ORDRE_POINTEAU + " INTEGER,"
                + CLE_HP_NUMERO_RONDE + " INTEGER"
                + ");");

        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_MAIN_COURANTE + "("
                + CLE_MAIN_COURANTE_ID + " INTEGER PRIMARY KEY,"
                + CLE_MAIN_COURANTE_TEXT + " VARCHAR(250),"
                + CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU + " INTEGER,"
                + CLE_MAIN_COURANTE_DATE + " DATE,"
                + CLE_MAIN_COURANTE_TYPE + " INTEGER"
                + ");");

        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_ASSOCIATION_POINTEAUX_RONDES + "("
                + CLE_APR_ID + " INTEGER PRIMARY KEY,"
                + CLE_APR_RONDE_ID + " INTEGER,"
                + CLE_APR_POINTEAU_ID + " INTEGER,"
                + CLE_APR_ORDRE_POINTEAU + " INTEGER"
                + ");");

        db.execSQL("CREATE TABLE IF NOT EXISTS " + TABLE_ASSOCIATION_AGENTS_RONDES + "("
                + CLE_AAR_ID + " INTEGER PRIMARY KEY,"
                + CLE_AAR_RONDE_ID + " INTEGER,"
                + CLE_AAR_AGENT_ID + " INTEGER"
                + ");");
    }


    /**
     * @brief Supprimer, si les tables existent, l'intégralité des tables pour ensuite les recréer via la méthode onCreate().
     * Permet de supprimer l'intégralité des tables si elles existent et de relancer leurs créations au changement du numéro de version de la base de données.
     * Cette méthode permet aussi de remplir les tables selon une base de données type pour effectuer des testes.
     * @param db La base de données concernée par la mise à jour.
     * @param oldVersion Le numéro de l'ancienne version de la base de données.
     * @param newVersion Le numéro de la nouvelle version de la base de données.
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Supprime les anciennes tables s'il y en a
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_AGENTS);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_RONDES);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_POINTEAUX);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_HISTORIQUE_POINTEAU);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_MAIN_COURANTE);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ASSOCIATION_POINTEAUX_RONDES);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ASSOCIATION_AGENTS_RONDES);

        // Crée les nouvelles tables
        onCreate(db);

        // Injecte un modèle exemple
        // createTemplate(db);
    }

    /*public void createTemplate(SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();

        // Nouveaux pointeaux
        values.put(CLE_POINTEAU_TAG_ID, "a3dd2a13");
        values.put(CLE_POINTEAU_NOM, "Entrepot");
        values.put(CLE_POINTEAU_NUMERO, 1);
        // Injection dans la base de données
        db.insert(TABLE_POINTEAUX, null, values);

        values = new ContentValues();
        values.put(CLE_POINTEAU_TAG_ID, "3e927f44");
        values.put(CLE_POINTEAU_NOM, "Gallerie");
        values.put(CLE_POINTEAU_NUMERO, 2);
        // Injection dans la base de données
        db.insert(TABLE_POINTEAUX, null, values);

        values = new ContentValues();
        values.put(CLE_POINTEAU_TAG_ID, "34a7bb96");
        values.put(CLE_POINTEAU_NOM, "Ordinateur");
        values.put(CLE_POINTEAU_NUMERO, 3);
        // Injection dans la base de données
        db.insert(TABLE_POINTEAUX, null, values);

        // Nouveaux agents
        values = new ContentValues();
        values.put(CLE_AGENT_TAG_ID, "eec8044");
        values.put(CLE_NOM_AGENT, "Bidochon");
        values.put(CLE_PRENOM_AGENT, "Robert");
        // Injection dans la base de données
        db.insert(TABLE_AGENTS, null, values);

        values = new ContentValues();
        values.put(CLE_AGENT_TAG_ID, "eed68144");
        values.put(CLE_NOM_AGENT, "Lorem");
        values.put(CLE_PRENOM_AGENT, "Ipsum");
        // Injection dans la base de données
        db.insert(TABLE_AGENTS, null, values);

        // Nouvelle ronde
        values = new ContentValues();
        values.put(CLE_RONDE_ID, 1);
        values.put(CLE_NOM_RONDE, "Bâtiment extérieur");
        // Injection dans la base de données
        db.insert(TABLE_RONDES, null, values);

        // Nouvelle association Agent Ronde
        values = new ContentValues();
        values.put(CLE_AAR_ID, 1);
        values.put(CLE_AAR_RONDE_ID, 1);
        values.put(CLE_AAR_AGENT_ID, 1);
        // Injection dans la base de données
        db.insert(TABLE_ASSOCIATION_AGENTS_RONDES, null, values);

        values = new ContentValues();
        values.put(CLE_AAR_ID, 1);
        values.put(CLE_AAR_RONDE_ID, 2);
        values.put(CLE_AAR_AGENT_ID, 2);
        // Injection dans la base de données
        db.insert(TABLE_ASSOCIATION_AGENTS_RONDES, null, values);

        // Nouvelles association Pointeaux Rondes
        values = new ContentValues();
        values.put(CLE_APR_ID, 1);
        values.put(CLE_APR_POINTEAU_ID, 3);
        values.put(CLE_APR_RONDE_ID, 1);
        values.put(CLE_APR_ORDRE_POINTEAU, 1);
        // Injection dans la base de données
        db.insert(TABLE_ASSOCIATION_POINTEAUX_RONDES, null, values);

        values = new ContentValues();
        values.put(CLE_APR_ID, 2);
        values.put(CLE_APR_POINTEAU_ID, 1);
        values.put(CLE_APR_RONDE_ID, 1);
        values.put(CLE_APR_ORDRE_POINTEAU, 2);
        // Injection dans la base de données
        db.insert(TABLE_ASSOCIATION_POINTEAUX_RONDES, null, values);
    }*/

    /**
     * @brief Vide les tables Agents, Rondes, Pointeaux, Association Pointeaux/Rondes, Association Agents/Rondes.
     * Cette méthode permet de supprimer les tables Agents, Rondes, Pointeaux, Association Pointeaux/Rondes et Association Agents/Rondes puis les recrée via la fonction onCreate().
     */
    public void supprimerTablesEnvoiePC()
    {
        SQLiteDatabase db = this.getWritableDatabase();

        db.execSQL("DROP TABLE IF EXISTS " + TABLE_AGENTS);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_RONDES);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_POINTEAUX);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ASSOCIATION_POINTEAUX_RONDES);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ASSOCIATION_AGENTS_RONDES);

        onCreate(db);
    }

    /**
     * @brief Vide les tables Historique Pointeau et Main Courante.
     * Cette méthode permet de supprimer les tables Historique Pointeau et Main Courante puis les recrée via la fonction onCreate().
     * */
    public void supprimerTablesReceptionPC()
    {
        SQLiteDatabase db = this.getWritableDatabase();

        db.execSQL("DROP TABLE IF EXISTS " + TABLE_HISTORIQUE_POINTEAU);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_MAIN_COURANTE);

        onCreate(db);
    }

    /**
     * @brief Retourne une liste d'entier correspondants aux ID des rondes associées à un agent.
     * Retourne une liste d'entier correspondants aux ID des rondes associées inscrits dans la table association agents-rondes pour un agent passé en paramètre.
     * @param agent L'agent avec lequel nous récupérons la liste des rondes.
     * @return La liste des rondes sous forme d'ID.
     */
    public ArrayList<Integer> obtenirIDRondeParAgent(Agent agent)
    {
        String selectQuery = "SELECT * FROM " + TABLE_ASSOCIATION_AGENTS_RONDES + " WHERE " + CLE_AAR_AGENT_ID + " = \"" + agent.obtenirId() + "\"";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultat = db.rawQuery(selectQuery, null);
        ArrayList<Integer> listeIDRonde = new ArrayList<Integer>();

        if(resultat.moveToFirst())
        {
            do {
                listeIDRonde.add(resultat.getInt(2));
            }while(resultat.moveToNext());
        }

        resultat.close();

        return listeIDRonde;
    }

    /**
     * @brief Retourne le nom d'une ronde grâce à son ID.
     * Retourne une chaine de caractère correspondant à l'ID de la ronde passé en paramètre.
     * @param id L'identifiant de la ronde dont nous voulons récupérer le nom.
     * @return Nom de la ronde.
     */
    public String obtenirNomRondeByID(int id)
    {
        String selectQuery = "SELECT " + CLE_NOM_RONDE + " FROM " + TABLE_RONDES + " WHERE " + CLE_RONDE_ID + " = \"" + id + "\"";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultat = db.rawQuery(selectQuery, null);
        String patrolName = new String();

        if(resultat.moveToFirst())
        {
            patrolName = resultat.getString(0);
        }

        resultat.close();

        return patrolName;
    }

    /**
     * @brief Retourne un agent en fonction de l'ID passé en paramètre.
     * Retourne un agent composé de son nom, son prénom ainsi que l'ID de son badge grâce à l'ID du badge passé en paramètre. Si aucun agent n'est connu dans la base de données avec l'ID de ce badge, null est renvoyé.
     * @param badgeID L'ID du tag MiFare utilisé pour retrouver l'agent.
     * @return Si un agent existe, retourne l'agent. Sinon, retourne null.
     */
    public Agent obtenirAgentAvecID(String badgeID)
    {
        String searchQuery = "SELECT * FROM " + TABLE_AGENTS + " WHERE " + CLE_AGENT_TAG_ID + " = \"" + badgeID + "\"";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultat = db.rawQuery(searchQuery, null);

        Agent agent;

        if(resultat.moveToFirst())
        {
            agent = new Agent(resultat.getInt(0), resultat.getString(1), resultat.getString(2), resultat.getString(3));
        }
        else
        {
            agent = null;
        }

        resultat.close();

        return agent;
    }

    /**
     * @brief Retourne une ronde grâce au nom passé en paramètre.
     * Retourne une ronde composée de son ID et de son nom grâce à une chaine de caractère passée en paramètre.
     * @param nom Le nom de la ronde que nous voulons récupérer.
     * @return Si une ronde existe, retourne la ronde. Sinon, retourne null.
     */
    public Ronde obtenirRondeAvecNom(String nom)
    {
        String searchQuery = "SELECT * FROM " + TABLE_RONDES + " WHERE " + CLE_NOM_RONDE + " = \"" + nom + "\"";
        String searchQueryNumero = "SELECT MAX("+ CLE_HP_NUMERO_RONDE + ") FROM " + TABLE_HISTORIQUE_POINTEAU;
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor curseurNumero = db.rawQuery(searchQueryNumero, null);
        Cursor resultatRonde = db.rawQuery(searchQuery, null);

        Ronde ronde;

        if(resultatRonde.moveToFirst() && curseurNumero.moveToFirst())
        {

            ronde = new Ronde(Integer.valueOf(resultatRonde.getInt(0)), resultatRonde.getString(1), obtenirPointeauxAvecIDRonde(resultatRonde.getInt(0)), curseurNumero.getInt(0)+1);
        }
        else
        {
            ronde = null;
        }

        resultatRonde.close();

        return ronde;
    }

    /**
     * @brief Retourne un pointeau grâce à l'ID passé en paramètre.
     * Retourne un pointeau constitué d'un ID, de l'ID du tag MiFare associé, de son nom et du numéro qui lui est attribué.
     * @param idTag L'ID du tag MiFare utilisée pour retrouver le pointeau.
     * @return Si un pointeau est trouvé, retourne le pointeau. Sinon renvoi null.
     */
    public Pointeau obtenirPointeauAvecID(String idTag)
    {
        String searchQuery = "SELECT * FROM " + TABLE_POINTEAUX + " WHERE " + CLE_POINTEAU_TAG_ID + " = \"" + idTag + "\"";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultat = db.rawQuery(searchQuery, null);

        Pointeau pointeau;

        if(resultat.moveToFirst())
        {
            pointeau = new Pointeau(resultat.getInt(0), resultat.getString(1), resultat.getString(2), resultat.getInt(3));
        }
        else
        {
            pointeau = null;
        }

        resultat.close();

        return pointeau;
    }

    /**
     * @brief Retourne une liste de pointeaux qui correspond aux pointeaux associés à une ronde.
     * Retourne une liste de pointeaux correspondant pointeaux inscrits dans la table d'association rondes-pointeaux pour l'ID de la ronde passé en paramètre.
     * @param idRonde L'ID de la ronde utilisé pour retrouver la liste des pointeaux associés.
     * @return La liste des pointeaux demandés.
     */
    public List<Pointeau> obtenirPointeauxAvecIDRonde(int idRonde)
    {
        String searchQueryAssociation = "SELECT * FROM " + TABLE_ASSOCIATION_POINTEAUX_RONDES + " WHERE " + CLE_APR_RONDE_ID + " =\"" + idRonde + "\" ORDER BY " + CLE_APR_ORDRE_POINTEAU;
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultatListe = db.rawQuery(searchQueryAssociation, null);

        List<Pointeau> listePointeaux = new ArrayList<Pointeau>();

        if(resultatListe.moveToFirst())
        {
            do
            {
                String searchQueryPointeaux = "SELECT * FROM "  + TABLE_POINTEAUX + " WHERE " + CLE_POINTEAU_ID + " =\"" + resultatListe.getString(2) + "\"";
                Cursor resultatPointeau = db.rawQuery(searchQueryPointeaux, null);

                if(resultatPointeau.moveToFirst())
                {
                    Pointeau pointeau = new Pointeau(
                            resultatPointeau.getInt(0),
                            resultatPointeau.getString(1),
                            resultatPointeau.getString(2),
                            resultatPointeau.getInt(3),
                            resultatListe.getInt(3));

                    listePointeaux.add(pointeau);
                }

                resultatPointeau.close();

            }while(resultatListe.moveToNext());
        }

        resultatListe.close();

        return listePointeaux;
    }

    /**
     * @brief Insère une nouvelle ligne dans la table HistoriquePointeau
     * Cette méthode permet d'insérer une nouvelle ligne dans la table HistoriquePointeau.
     * Cette ligne contient l'idAgent, l'idPointeau, l'idRonde et l'ordre de passage saisis en paramètre de la méthode.
     * En plus de ces informations, la ligne est accompagnée par la date d'enregistrement au format AAAA-MM-DD hh:mm:ss.
     * @param idAgent L'ID de l'agent qui a scanné le pointeau.
     * @param idPointeau L'ID du pointeau qui a été scanné.
     * @param idRonde L'ID de la ronde dans laquelle le pointeau a été scanné.
     * @param ordrePointeau L'ordre dans lequel le pointeau a été scanné.
     */
    public void enregistrerPassagePointeau(int idAgent, int idPointeau, int idRonde, int ordrePointeau, int numeroRonde)
    {
        String queryTempsPresent = "SELECT datetime('now', 'localtime')";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor tempsPresent = db.rawQuery(queryTempsPresent, null);
        ContentValues values = new ContentValues();

        if(tempsPresent.moveToFirst())
        {
            values.put(CLE_HP_AGENT_ID, idAgent);
            values.put(CLE_HP_RONDE_ID, idRonde);
            values.put(CLE_HP_POINTEAU_ID, idPointeau);
            values.put(CLE_HP_DATE, tempsPresent.getString(0));
            values.put(CLE_HP_ORDRE_POINTEAU, ordrePointeau);
            values.put(CLE_HP_NUMERO_RONDE, numeroRonde);
        }

        db.insert(TABLE_HISTORIQUE_POINTEAU, null, values);
        tempsPresent.close();
        db.close();
    }

    /**
     * @brief Insère une nouvelle ligne dans la table MainsCourantes
     * Cette méthode permet d'insérer une nouvelle ligne dans la table MainsCourantes.
     * Cette ligne contient le texte saisie (passé en paramètre de la méthode), l'ID du dernier pointeau scanné ainsi que le type de la main courante (ici 0 qui correspond à une main courante textuelle).
     * @param enregistrement La main courante qui doit être enregistrée.
     */
    public void enregistrerMainCourante(String enregistrement)
    {
        String searchQueryHistoriquePointeau = "SELECT MAX(" + CLE_HP_ID + ") FROM " + TABLE_HISTORIQUE_POINTEAU;
        String queryTempsPresent = "SELECT datetime('now', 'localtime')";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultat = db.rawQuery(searchQueryHistoriquePointeau, null);
        Cursor tempsPresent = db.rawQuery(queryTempsPresent, null);

        if(resultat.moveToFirst() && tempsPresent.moveToFirst())
        {
            ContentValues values = new ContentValues();
            values.put(CLE_MAIN_COURANTE_TEXT, enregistrement);
            values.put(CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU, resultat.getInt(0)+1);
            values.put(CLE_MAIN_COURANTE_DATE, tempsPresent.getString(0));
            values.put(CLE_MAIN_COURANTE_TYPE, "0");

            db.insert(TABLE_MAIN_COURANTE, null, values);
        }

        db.close();
        resultat.close();
    }

    /**
     * @brief Insère une nouvelle ligne dans la table MainsCourantes
     * Cette méthode permet d'insérer une nouvelle ligne dans la table MainsCourantes.
     * Cette ligne contient le chemin où la photo est enregistrée (passé en paramètre de la méthode), l'ID du dernier pointeau scanné ainsi que le type de la main courante (ici 1 qui correspond à une photo).
     * @param chemin Le chemin dans lequel la photo va être enregistrée.
     */
    public void enregistrerPhoto(String chemin)
    {
        String searchQueryHistoriquePointeau = "SELECT MAX(" + CLE_HP_ID + ") FROM " + TABLE_HISTORIQUE_POINTEAU;
        String queryTempsPresent = "SELECT datetime('now', 'localtime')";
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor resultat = db.rawQuery(searchQueryHistoriquePointeau, null);
        Cursor tempsPresent = db.rawQuery(queryTempsPresent, null);

        if(resultat.moveToFirst() && tempsPresent.moveToFirst())
        {
            ContentValues values = new ContentValues();
            values.put(CLE_MAIN_COURANTE_TEXT, chemin);
            values.put(CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU, resultat.getInt(0)+1);
            values.put(CLE_MAIN_COURANTE_DATE, tempsPresent.getString(0));
            values.put(CLE_MAIN_COURANTE_TYPE, "1");

            db.insert(TABLE_MAIN_COURANTE, null, values);
        }

        db.close();
        resultat.close();
    }

    /**
     * @brief Retourne toutes les mains courantes correspondantes au pointeau passé en paramètre.
     * Cette méthode retourne toutes les mains courantes ayant été saisies qui correspondent au pointeau passé en paramètre.
     * Le tableau de string retourné comporte aussi les heures et dates auxquelles les mains courantes ont été saisies.
     * @param pointeau Le pointeau utilisé pour retrouver la liste des mains courantes associées.
     * @return Liste des mains courantes avec l'heure et la date correspondant sous forme de tableau de string.
     */
    public ArrayList<String> obtenirMainsCourantesAvecPointeau(Pointeau pointeau)
    {
        String searchQueryIdHP = "SELECT " + CLE_HP_ID + " FROM " + TABLE_HISTORIQUE_POINTEAU + " WHERE " + CLE_HP_POINTEAU_ID + " = " + pointeau.obtenirId();
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor curseurIdHistorique = db.rawQuery(searchQueryIdHP, null);
        ArrayList<String> listeMainsCourantesEtDate = new ArrayList<String>();

        if(curseurIdHistorique.moveToFirst())
        {
            do
            {
                String searchQueryMainCourante = "SELECT " + CLE_MAIN_COURANTE_TEXT + "," + CLE_MAIN_COURANTE_DATE + " FROM " + TABLE_MAIN_COURANTE + " WHERE " + CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU + " = " + curseurIdHistorique.getInt(0) + " AND " + CLE_MAIN_COURANTE_TYPE + " = 0";
                Cursor textMainCourante = db.rawQuery(searchQueryMainCourante, null);

                if(textMainCourante.moveToFirst())
                {
                    do
                    {
                        listeMainsCourantesEtDate.add(textMainCourante.getString(0));
                        listeMainsCourantesEtDate.add(textMainCourante.getString(1));

                        Log.d("BDD", textMainCourante.getString(0));
                    } while (textMainCourante.moveToNext());

                    textMainCourante.close();
                }

            } while (curseurIdHistorique.moveToNext());

            curseurIdHistorique.close();
        }

        return listeMainsCourantesEtDate;
    }

    /**
     * @brief Retourne toutes photos correspondantes au pointeau passé en paramètre.
     * Cette méthode retourne toutes les photos ayant été prises qui correspondent au pointeau passé en paramètre.
     * @param pointeau Le pointeau utilisé pour retrouver la liste des photos associées.
     * @return Liste des photos sous forme de tableau de string.
     */
    public ArrayList<String> obtenirPhotosAvecPointeau(Pointeau pointeau)
    {
        String searchQueryIdPhoto = "SELECT " + CLE_HP_ID + " FROM " + TABLE_HISTORIQUE_POINTEAU + " WHERE " + CLE_HP_POINTEAU_ID + " = " + pointeau.obtenirId();
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor curseurIdHistorique = db.rawQuery(searchQueryIdPhoto, null);
        ArrayList<String> listeNomsPhotos = new ArrayList<String>();

        if(curseurIdHistorique.moveToFirst())
        {
            do
            {
                String searchQueryPhoto = "SELECT " + CLE_MAIN_COURANTE_TEXT + " FROM " + TABLE_MAIN_COURANTE + " WHERE " + CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU + " = " + curseurIdHistorique.getInt(0) + " AND " + CLE_MAIN_COURANTE_TYPE + " = 1";
                Cursor cheminPhoto = db.rawQuery(searchQueryPhoto, null);

                if(cheminPhoto.moveToFirst())
                {
                    do
                    {
                        listeNomsPhotos.add(cheminPhoto.getString(0));
                    } while (cheminPhoto.moveToNext());
                }
            } while (curseurIdHistorique.moveToNext());

            curseurIdHistorique.close();
        }

        return listeNomsPhotos;
    }

    /**
     * @brief Transfère les données des tables MainCourante et HistoriquePointeau dans la base de données passée en paramètre.
     * Cette méthdoe transfère les données des tables MainCourante et HistoriquePointeau présentent sur le smartphone vers une base de données passée en paramètre.
     * @param dbSortie La base de données utilisée pour envoyer les données vers le poste de supervision.
     */
    public void transfererMainCouranteHistoriquePointeau(SQLiteDatabase dbSortie)
    {
        String searchQueryHistoriquePointeau = "SELECT * FROM " + TABLE_HISTORIQUE_POINTEAU;
        String searchQueryMainCourante = "SELECT * FROM " + TABLE_MAIN_COURANTE;
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor curseurHP = db.rawQuery(searchQueryHistoriquePointeau, null);
        Cursor curseurMC = db.rawQuery(searchQueryMainCourante, null);

        if(curseurHP.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_HP_ID, curseurHP.getInt(0));
                values.put(CLE_HP_AGENT_ID, curseurHP.getInt(1));
                values.put(CLE_HP_RONDE_ID, curseurHP.getInt(2));
                values.put(CLE_HP_POINTEAU_ID, curseurHP.getInt(3));
                values.put(CLE_HP_DATE, curseurHP.getString(4));
                values.put(CLE_HP_ORDRE_POINTEAU, curseurHP.getInt(5));
                values.put(CLE_HP_NUMERO_RONDE, curseurHP.getInt(6));

                dbSortie.insert(TABLE_HISTORIQUE_POINTEAU, null, values);
            } while (curseurHP.moveToNext());
        }

        if(curseurMC.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_MAIN_COURANTE_ID, curseurMC.getInt(0));
                values.put(CLE_MAIN_COURANTE_TEXT, curseurMC.getString(1));
                values.put(CLE_MAIN_COURANTE_ID_HISTORIQUE_POINTEAU, curseurMC.getInt(2));
                values.put(CLE_MAIN_COURANTE_DATE, curseurMC.getString(3));
                values.put(CLE_MAIN_COURANTE_TYPE, curseurMC.getInt(4));

                dbSortie.insert(TABLE_MAIN_COURANTE, null, values);
            } while (curseurMC.moveToNext());
        }

        supprimerTablesReceptionPC();

        curseurHP.close();
        curseurMC.close();
    }

    /**
     * @brief Transfère les données des tables Agents, Rondes, Pointeaux, AssociationAgentsRondes et AssociationPointeauxRondes dans la base de données passée en paramètre.
     * Cette méthdoe transfère les données des tables Agents, Rondes, Pointeaux, AssociationAgentsRondes et AssociationPointeauxRondes présentent sur le smartphone vers une base de données passée en paramètre.
     * @param dbEntree La base de données utilisée pour récupérer les données du poste de supervision.
     */
    public void transfererPointeauxAgentsRondes(SQLiteDatabase dbEntree)
    {
        String searchQueryAgents = "SELECT * FROM " + TABLE_AGENTS;
        String searchQueryRondes = "SELECT * FROM " + TABLE_RONDES;
        String searchQueryPointeaux = "SELECT * FROM " + TABLE_POINTEAUX;
        String searchQueryAssociationAgentsRondes = "SELECT * FROM " + TABLE_ASSOCIATION_AGENTS_RONDES;
        String searchQueryAssociationPointeauxRondes = "SELECT * FROM " + TABLE_ASSOCIATION_POINTEAUX_RONDES;
        SQLiteDatabase db = this.getWritableDatabase();

        Cursor curseurAgents = dbEntree.rawQuery(searchQueryAgents, null);
        Cursor curseurRondes = dbEntree.rawQuery(searchQueryRondes, null);
        Cursor curseurPointeaux = dbEntree.rawQuery(searchQueryPointeaux, null);
        Cursor curseurAssociationAgentsRondes = dbEntree.rawQuery(searchQueryAssociationAgentsRondes, null);
        Cursor curseurAssociationPointeauxRondes = dbEntree.rawQuery(searchQueryAssociationPointeauxRondes, null);

        supprimerTablesEnvoiePC();

        if(curseurAgents.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_AGENT_ID, curseurAgents.getInt(0));
                values.put(CLE_AGENT_TAG_ID, curseurAgents.getString(1));
                values.put(CLE_NOM_AGENT, curseurAgents.getString(2));
                values.put(CLE_PRENOM_AGENT, curseurAgents.getString(3));

                db.insert(TABLE_AGENTS, null, values);
            } while (curseurAgents.moveToNext());
        }

        if(curseurRondes.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_RONDE_ID, curseurRondes.getInt(0));
                values.put(CLE_NOM_RONDE, curseurRondes.getString(1));

                db.insert(TABLE_RONDES, null, values);
            } while (curseurRondes.moveToNext());
        }

        if(curseurPointeaux.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_POINTEAU_ID, curseurPointeaux.getInt(0));
                values.put(CLE_POINTEAU_TAG_ID, curseurPointeaux.getString(1));
                values.put(CLE_POINTEAU_NOM, curseurPointeaux.getString(2));
                values.put(CLE_POINTEAU_NUMERO, curseurPointeaux.getInt(3));

                db.insert(TABLE_POINTEAUX, null, values);
            } while (curseurPointeaux.moveToNext());
        }

        if(curseurAssociationAgentsRondes.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_AAR_ID, curseurAssociationAgentsRondes.getInt(0));
                values.put(CLE_AAR_RONDE_ID, curseurAssociationAgentsRondes.getInt(1));
                values.put(CLE_AAR_AGENT_ID, curseurAssociationAgentsRondes.getInt(2));

                db.insert(TABLE_ASSOCIATION_AGENTS_RONDES, null, values);
            } while (curseurAssociationAgentsRondes.moveToNext());
        }

        if(curseurAssociationPointeauxRondes.moveToFirst())
        {
            do
            {
                ContentValues values = new ContentValues();
                values.put(CLE_APR_ID, curseurAssociationPointeauxRondes.getInt(0));
                values.put(CLE_APR_RONDE_ID, curseurAssociationPointeauxRondes.getInt(1));
                values.put(CLE_APR_POINTEAU_ID, curseurAssociationPointeauxRondes.getInt(2));
                values.put(CLE_APR_ORDRE_POINTEAU, curseurAssociationPointeauxRondes.getInt(3));

                db.insert(TABLE_ASSOCIATION_POINTEAUX_RONDES, null, values);
            } while (curseurAssociationPointeauxRondes.moveToNext());
        }

        curseurAgents.close();
        curseurRondes.close();
        curseurPointeaux.close();
        curseurAssociationAgentsRondes.close();
        curseurAssociationPointeauxRondes.close();
    }
}