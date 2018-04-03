package com.project.rondierprojet;

import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.os.Environment;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.File;

/**
 * @file Synchronisation.java
 * @brief Définition de la classe de synchronisation de la base de données
 * @version 1.0
 * @author Tanguy Herbron
 * @date 27 Avril 2017
 *
 * Classe synchronisant la base de données avec le poste de supervision.
 * Cette classe n'est jamais appelée dans l'application elle-même.
 * Elle n'a pour but que d'être appelée via adb, commande à faire sur un ordinateur : adb shell am start -n "com.project.rondierprojet/com.project.rondierprojet.Synchronisation" -a android.intent.action.SYNC.
 * La classe Synchronisation utilise la base de données du téléphone présente dans l'application et gérée par GestionBDD ainsi que la base de données envoyée par le poste de supervision dans /sdcard/Android/data/com.project.rondierprojet/files/Documents.
 */
public class Synchronisation extends AppCompatActivity {

    SQLiteDatabase dbExterne = null;

    /**
     * Méthode appelée automatiquement après l'instanciation de la classe.
     * La méthode onCreate est une méthode appelée par le système Android à l'instanciation de la classe.
     * Cette méthode est ici utilisée pour synchroniser les tables entre les différentes base de données.
     * Cette synchronisation ne se fait que si l'appel de la classe se fait avec l'intent "android.intent.action.SYNC".
     * @param savedInstanceState Etat antérieur de l'activité.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_synchronisation);

        final Handler handler = new Handler();

        if(getIntent().getAction().equals(Intent.ACTION_SYNC))
        {
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {

                    try
                    {
                        dbExterne = SQLiteDatabase.openDatabase(getExternalFilesDir(Environment.DIRECTORY_DOCUMENTS) + File.separator + "ControleurDeRonde.db", null, SQLiteDatabase.OPEN_READWRITE);
                        Log.d(getString(R.string.tag_log), getExternalFilesDir(Environment.DIRECTORY_DOCUMENTS) + File.separator + "ControleurDeRonde.db");
                    } catch (SQLiteException e)
                    {
                        Log.d(getString(R.string.tag_log), "Erreur à l'ouverture de la base de données externe : " + e.toString());
                    }

                    if(dbExterne != null)
                    {
                        GestionBDD db = new GestionBDD(Synchronisation.this);

                        db.transfererMainCouranteHistoriquePointeau(dbExterne);
                        db.transfererPointeauxAgentsRondes(dbExterne);
                    }

                    Log.d(getString(R.string.tag_log), "BDDSynchroFin");

                    finish();
                }
            }, 2000);
        }
    }
}
