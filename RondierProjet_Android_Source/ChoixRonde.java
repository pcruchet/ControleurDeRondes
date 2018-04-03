package com.project.rondierprojet;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

/**
 * @file ChoixRonde.java
 * @brief Définition de la classe choix de ronde
 * @version 1.3
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe affichant l'interface responsable de la liste et du choix de la liste attribuée à un agent.
 */
public class ChoixRonde extends AppCompatActivity {

    LinearLayout layoutListeRonde;
    Agent agent;
    Button boutonSelectionne;
    GestionBDD bdd = new GestionBDD(this);
    String badgeID;

    /**
     * @brief Methode appelée au lancement de l'activité.
     * La méthode onCreate est une méthode appelée par le système Android au lancement de l'activité associée.
     * Cette méthode est ici utilisée pour récupérer l'ID des rondes associées à l'agent s'étant identifié précédemment.
     * Grâce aux ID de ces rondes, cette méthode crée une liste de rondes disponnible pour l'agent et l'affiche sur l'interface associée ainsi qu'un bouton valider.
     * @param savedInstanceState Etat antérieur de l'activité.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_choix_ronde);

        Log.d(getString(R.string.tag_log), "ChoixRonde: Lancement de l'activité ChoixRonde.");

        definirEtatRonde(false);

        // Récupération de  l'intent responsable de la transmission de l'id du badge scanné sous forme de chaine de caractère.
        final Intent intent = getIntent();
        badgeID = intent.getStringExtra("badgeIDString");

        // Récupération de l'agent correspondant à l'id transmis et récupéré précédemment.
        agent = bdd.obtenirAgentAvecID(badgeID);

        layoutListeRonde = (LinearLayout) findViewById(R.id.linlayout);

        // Récupération des ids des rondes que l'agent peut faire.
        ArrayList<Integer> badgePatrolList = bdd.obtenirIDRondeParAgent(agent);

        // Si des rondes sont associées à l'agent, sont créés autant de bouton qu'il y a de ronde.
        // Sinon, un texte est créé pour informer l'agent qu'il n'a pas de ronde associée.
        if(badgePatrolList != null)
        {
            for(int i = 0; i < badgePatrolList.size(); i++)
            {
                creerBoutonRonde(bdd.obtenirNomRondeByID(badgePatrolList.get(i)));
            }
        }
        else
        {
            TextView txtView = new TextView(this);
            txtView.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.MATCH_PARENT, ActionBar.LayoutParams.WRAP_CONTENT));
            txtView.setText("Aucune ronde prévue.");
            layoutListeRonde.addView(txtView, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        }

        // Création du bouton de validation du choix d'une ronde.
        Button boutonValider = (Button) findViewById(R.id.buttonValiderRonde);
        boutonValider.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(boutonSelectionne != null)
                {
                    definirEtatRonde(true);

                    definirNomRondeTransmis();

                    Intent intentActivite = new Intent(ChoixRonde.this, InterfaceRondier.class);
                    startActivity(intentActivite);
                }
                else
                {
                    Toast.makeText(ChoixRonde.this, "Choisissez une ronde.", Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    /**
     * @brief Definir si une ronde est en cours ou non dans les fichiers partagers.
     * Permet de définir dans les paramètres communs à toutes les activités si une ronde est en cours ou non.
     * @param etatRonde Retourne vrai si une ronde est en cours sinon retourne faux.
     */
    public void definirEtatRonde(boolean etatRonde)
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putBoolean("RondeEnCours", etatRonde);
        editor.commit();
    }

    /**
     * @brief Définir l'id de l'agent qui lance la ronde ainsi que le nom de la ronde sélectionnée.
     * Permet dé définir dans les paramètres communs à toutes les activités l'id de l'agent qui lance une ronde ainsi que le nom de la ronde qui est lancée.
     */
    private void definirNomRondeTransmis()
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putString("badgeIDString", badgeID);
        editor.putString("idPointeau", "-1");
        editor.putString("nomRonde", boutonSelectionne.getText().toString());
        editor.commit();
    }

    /**
     * @brief Créer un bouton pour la sélection d'une ronde par l'agent.
     * Permet de créer un bouton du nom d'une ronde disponnible pour l'agent. Cette méthode crée aussi les évènements lorsqu'un clique est fait sur le bouton.
     * @param text Le texte à mettre dans le bouton.
     */
    private void creerBoutonRonde(String text)
    {
        Button newButton = new Button(this);
        newButton.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.MATCH_PARENT, ActionBar.LayoutParams.WRAP_CONTENT));
        newButton.setText(text);
        newButton.setId(layoutListeRonde.getChildCount()+1);
        newButton.setBackgroundColor(Color.parseColor("#d6d7d7"));
        newButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                layoutListeRonde = (LinearLayout) findViewById(R.id.linlayout);
                for(int i = 0; i < layoutListeRonde.getChildCount(); i++)
                {
                    View v = layoutListeRonde.getChildAt(i);
                    v.setBackgroundColor(Color.parseColor("#d6d7d7"));
                }
                ((Button) view).setBackgroundColor(Color.parseColor("#FF4081"));
                boutonSelectionne = (Button) view;
            }
        });

        layoutListeRonde.addView(newButton, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
    }
}