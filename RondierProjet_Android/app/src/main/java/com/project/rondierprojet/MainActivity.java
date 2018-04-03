package com.project.rondierprojet;

import android.content.Intent;
import android.content.SharedPreferences;
import android.media.Image;
import android.nfc.NfcAdapter;
import android.nfc.Tag;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

/**
 * @file MainActivity.java
 * @brief Définition de la classe lancée au démarrage de l'application.
 * @version 2.2
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe gérant le module NFC et la récupération des informations des badges via ce dernier.
 */
public class MainActivity extends AppCompatActivity {

    private NfcAdapter nfcAdapter;

    /**
     * @brief Méthode appelée au lancement de l'activité.
     * La méthode onCreate est une méthode appelée par le système Android au lancement de l'activité associée.
     * Cette méthode est ici utilisée pour lancer la vérification des prérequis au bon fonctionnement de l'application.
     * @param savedInstanceState Etat antérieur de l'activité.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(getString(R.string.tag_log), "MainActivity: Lancement de l'activité principale.");

        verificationNFC();

        Log.d("Rondier", "Application lancée.");
    }

    /**
     * @brief Méthode appelée automatiquement après l'initialisation de la classe.
     * La méthode onResume est une méthode appelée par le système Android après l'initialisation de la classe.
     * Cette méthode est ici utilisée pour gérer l'évènement de découverte de tag par le module NFC.
     * Lorsqu'un tag est découvert, la méthode réoriente l'utilisateur vers la prochaine activité.
     * Si une ronde est en cours, l'utilisateur est réorienté vers l'interface de réalisation de ronde.
     * Dans le cas contraire, l'utilisateur doit choisir la ronde qu'il souhaite effectuer.
     */
    @Override
    protected void onResume()
    {
        super.onResume();

        GestionBDD bdd = new GestionBDD(this);

        Agent agent;
        Tag tagMifare;
        String tagID;
        Intent intent = getIntent();
        String action = intent.getAction();

        if(NfcAdapter.ACTION_TAG_DISCOVERED.equals(action))
        {
            tagMifare = intent.getParcelableExtra(NfcAdapter.EXTRA_TAG);

            Log.d(getString(R.string.tag_log), "MainActivity: Tag détecté.");

            if(tagMifare == null)
            {
                Toast.makeText(this, "Erreur lors de la lecture du badge.", Toast.LENGTH_LONG).show();
            }
            else
            {
                tagID = obtenirIDTag(tagMifare);
                if(obtenirEtatRonde())
                {
                    Log.d(getString(R.string.tag_log), "MainActivity: Pointeau " + tagID + " trouvé, chargement d'InterfaceRondier.");

                    transmettreIdPointeau(tagID);
                    recupererInterfaceRondier();
                }
                else
                {
                    agent = bdd.obtenirAgentAvecID(tagID);

                    if(agent != null)
                    {
                        Intent activityIntent = new Intent(MainActivity.this, ChoixRonde.class);
                        activityIntent.putExtra("badgeIDString", tagID);

                        Toast.makeText(this, "Utilisateur trouvé : " + agent.obtenirNom(), Toast.LENGTH_LONG).show();
                        Log.d(getString(R.string.tag_log), "MainActivity: Agent " + agent.obtenirNom() + " identifié, chargement de ChoixRonde.");
                        startActivity(activityIntent);
                    }
                    else
                    {
                        Toast.makeText(this, "Utilisateur non reconnu", Toast.LENGTH_LONG).show();
                        Log.d(getString(R.string.tag_log), "MainActivity: Aucun agent enregistré pour ce tag.");
                    }
                }
            }
        }

        Log.d(getString(R.string.tag_log), "MainActivity: Application en fonctionnement.");
    }

    /**
     * @brief Méthode vérifiant l'état du module NFC.
     * Cette méthode vérifie si le NFC est disponnible sur le smartphone sur lequel est lancé l'application.
     * Si la fonctionnalité NFC est disponnible, cette méthode vérifie ensuite si cette dernière est bien activée.
     */
    private void verificationNFC()
    {
        nfcAdapter = NfcAdapter.getDefaultAdapter(this);
        if (nfcAdapter == null) {
            ImageView img = (ImageView) findViewById(R.id.imageViewRadioWave);
            TextView txt = (TextView) findViewById(R.id.textView);

            img.setImageResource(R.drawable.rfid_signal1600brocken);
            txt.setText("NFC non supporté par l'appareil.");

            Toast.makeText(this, "NFC non supporté par l'appareil.", Toast.LENGTH_LONG).show();

            Log.d(getString(R.string.tag_log), "MainActivity: NFC Non supporté.");
        } else {
            if (!nfcAdapter.isEnabled()) {
                ImageView img = (ImageView) findViewById(R.id.imageViewRadioWave);
                TextView txt = (TextView) findViewById(R.id.textView);

                img.setImageResource(R.drawable.rfid_signal1600brocken);
                txt.setText("NFC désactivé.");

                Toast.makeText(this, "NFC désactivé.", Toast.LENGTH_LONG).show();

                Log.d(getString(R.string.tag_log), "MainActivity: NFC Désactivé.");
            }
        }
    }

    /**
     * @brief Méthode retournant l'ID d'un tag en fonction du tag passé en paramètre.
     * Cette méthode récupère l'ID du tag passé en paramètre et le convertit ensuite en une string.
     * @param tagMifare L'objet Tag utilisé par l'API Android pour caractériser un tag MiFare.
     * @return La string contenant l'ID du tag.
     */
    private String obtenirIDTag(Tag tagMifare)
    {
        String badgeIDtoString = new String();
        byte[] badgeID = tagMifare.getId();

        for(int i = 0; i < badgeID.length; i++)
        {
            badgeIDtoString += Integer.toHexString(badgeID[i] & 0xFF);
        }

        return badgeIDtoString;
    }

    /**
     * @brief Méthode retournant si une ronde est en cours ou non.
     * Cette méthode récupère dans les fichiers partagés entre les différentes activités si une ronde est en cours ou non.
     * @return Retourne true si une ronde est en cours. Sinon, retourne false.
     */
    private boolean obtenirEtatRonde() {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        return prefs.getBoolean("RondeEnCours", false);
    }

    /**
     * @brief Méthode transmettant l'ID du badge de l'agent identifié.
     * Cette méthode transmet aux autres activités l'ID sous forme de string de l'agent identifié via les fichiers partagés.
     * @param tagID L'ID du tag MiFare transféré.
     */
    private void transmettreIdPointeau(String tagID)
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putString("idPointeau", tagID);
        editor.commit();
    }

    /**
     * @brief Méthode récupérant l'interface de réalisation d'une ronde.
     * Cette méthode appelle l'activité de réalisation de ronde sans réinitialiser son état. Les modifications précédemment apportées à cette dernière sont alors conservés et l'utilisateur retrouve l'interface comme il l'a laissé en sortant de l'application.
     */
    private void recupererInterfaceRondier()
    {
        Intent activityIntent = new Intent(MainActivity.this, InterfaceRondier.class);
        activityIntent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        startActivity(activityIntent);
    }
}