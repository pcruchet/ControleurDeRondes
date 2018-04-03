package com.project.rondierprojet;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.support.annotation.IdRes;
import android.app.ActionBar;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ViewFlipper;

import com.roughike.bottombar.BottomBar;
import com.roughike.bottombar.OnTabSelectListener;

import java.io.File;
import java.util.ArrayList;

/**
 * @file InterfaceRondier.java
 * @brief Définition de la classe correspondant à l'interface de réalisation d'une ronde.
 * @version 1.5
 * @author Tanguy Herbron
 * @date 3 Février 2017
 *
 * Classe gérant l'interface de réalisation d'une ronde.
 */
public class InterfaceRondier extends AppCompatActivity {

    private Pointeau pointeauScanne;
    private Agent agent;
    private Ronde ronde;
    private LinearLayout layoutListePointeaux;
    private LinearLayout layoutListePhotos;
    private LinearLayout layoutListeMainsCourantes;
    private ViewFlipper flipperPrincipal;
    private BottomBar bottomBar;

    /**
     * @brief Méthode appelée au lancement de l'activité.
     * La méthode onCreate est une méthode appelée par le système Android au lancement de l'activité associée.
     * Cette méthode est ici utilisée pour récupérer l'agent utilisant l'application à partir de la dernière activité ainsi que la ronde en cours aussi récupérée via la dernière activité.
     * par la suite, la classe InterfaceRondier crée dynamiquement la liste des pointeaux à scanner, les interfaces de prise de photo et de saisie de main courante (au début vides).
     * La méthode finit par créer la barre de naviguation permettant de changer la vue (liste mains courantes, liste pointeaux ou liste photos) et le bouton donnant la possibilité à l'utilisateur de terminer la ronde manuellement.
     * @param savedInstanceState Etat antérieur de l'activité.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_liste_pointeaux);

        GestionBDD db = new GestionBDD(this);
        agent = db.obtenirAgentAvecID(obtenirBadgeIDTransmis());
        ronde = db.obtenirRondeAvecNom(obtenirNomRondeTransmis());

        layoutListePointeaux = (LinearLayout) findViewById(R.id.layoutListePointeaux);
        layoutListePhotos = (LinearLayout) findViewById(R.id.layoutPhotos);
        layoutListeMainsCourantes = (LinearLayout) findViewById(R.id.layoutMainCourante);

        creerTxtViewAucunPointeauScanne();

        flipperPrincipal = (ViewFlipper)findViewById(R.id.vfDisposition);

        FloatingActionButton boutonTerminerRonde = (FloatingActionButton) findViewById(R.id.terminer_ronde);
        boutonTerminerRonde.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new AlertDialog.Builder(InterfaceRondier.this)
                        .setMessage(R.string.demande_terminer_ronde)
                        .setPositiveButton(R.string.oui, new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                redemarrerApplication();
                            }
                        })
                        .setNegativeButton(R.string.annuler, new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {

                            }
                        })
                        .show();
            }
        });

        bottomBar = (BottomBar) findViewById(R.id.bottombar);
        bottomBar.setOnTabSelectListener(new OnTabSelectListener() {
            @Override
            public void onTabSelected(@IdRes int tabId) {
                if(tabId == R.id.tab_mainsCourantes)
                {
                    flipperPrincipal.setDisplayedChild(0);
                }

                if(tabId == R.id.tab_listePointeaux)
                {
                    flipperPrincipal.setDisplayedChild(1);
                }

                if(tabId == R.id.tab_photos)
                {
                    flipperPrincipal.setDisplayedChild(2);
                }
            }
        });
        bottomBar.setDefaultTab(R.id.tab_listePointeaux);

        if(ronde.obtenirListePointeaux() != null)
        {
            for(int i = 0; i < ronde.obtenirListePointeaux().size(); i++)
            {
                creerCheckboxPointeau(i);
            }
        }
        else
        {
            TextView txtView = new TextView(this);
            txtView.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.WRAP_CONTENT, ActionBar.LayoutParams.WRAP_CONTENT));
            txtView.setText("Aucun point dans cette ronde.");
            layoutListePointeaux.addView(txtView, new ActionBar.LayoutParams(ActionBar.LayoutParams.WRAP_CONTENT, ActionBar.LayoutParams.WRAP_CONTENT));
        }

        getSupportActionBar().setTitle(ronde.obtenirNom());
    }

    /**
     * @brief Méthode appelée automatiquement après l'initialisation de la classe.
     * La méthode onResume est une méthode appelée par le système Android après l'initialisation de la classe.
     * Cette méthode est ici utilisée pour récupérer le dernier pointeau scannée via MainActivity.
     * Si le pointeau scanné est reconnu et que c'est le premier pointeau scannée depuis le lancement de l'application, les interfaces de prise de photo et de saisie de main courante sont actualisées.
     * Le pointeau est ensuite vérifié dans la base de donnée et le passage y est enregistré.
     */
    @Override
    protected void onResume()
    {
        super.onResume();

        boolean pointeauVerifie = false;
        int loop = 0;

        GestionBDD db = new GestionBDD(this);

        String pointeauID = obtenirIDPointeauTransmis();

        pointeauScanne = db.obtenirPointeauAvecID(pointeauID);

        if(pointeauScanne != null && findViewById(R.id.boutonAjouterPhoto) == null)
        {
            supprimerTxtViewAucunPointeauScanne();

            creerInterfaceAjouterMainCourante();
            creerBoutonAjouterPhoto();
        }

        if(pointeauScanne != null && findViewById(R.id.boutonAjouterPhoto) != null)
        {
            mettreAJourTexteBoutonAjouterPhoto();
            mettreAJourTexteMainCourante();
        }

        if(pointeauScanne != null)
        {
            pointeauScanne.definirOrdrePassage(ronde.obtenirIndex()+1);

            Toast.makeText(this, "Nouveau pointeau scanné : " + pointeauScanne.obtenirNom(), Toast.LENGTH_LONG).show();

            db.enregistrerPassagePointeau(agent.obtenirId(), pointeauScanne.obtenirNumero(), ronde.obtenirId(), pointeauScanne.obtenirOrdrePassage(), ronde.obtenirNumeroRonde());

            ArrayList<String> listeMainsCourantesPointeau = db.obtenirMainsCourantesAvecPointeau(pointeauScanne);

            LinearLayout layoutMainsCourantes = (LinearLayout)findViewById(R.id.layoutListeMainsCourantes);
            layoutMainsCourantes.removeAllViews();

            for(int i = 1; i < listeMainsCourantesPointeau.size(); i+=2)
            {
                creerCheckboxMainCourante(layoutMainsCourantes.getChildCount()+1, listeMainsCourantesPointeau.get(i-1), listeMainsCourantesPointeau.get(i));
            }

            while(loop < layoutListePointeaux.getChildCount() && !pointeauVerifie)
            {
                if(verificationPointDansRonde(loop))
                {
                    pointeauVerifie = true;

                    if(loop == layoutListePointeaux.getChildCount()-1)
                    {
                        demandeFinRonde();
                    }
                }
                loop++;
            }

            if(!pointeauVerifie)
            {
                Toast.makeText(this, "Pointeau non présent dans la ronde en cours.", Toast.LENGTH_SHORT).show();
                creerCheckboxMauvaisPointeau(pointeauScanne, ronde.obtenirIndex());
            }

            ronde.definirIndex(ronde.obtenirIndex()+1);

            creerImagesVisualisation(pointeauScanne);
        }
        else
        {
            if(pointeauID != "-1")
            {
                Toast.makeText(this, "Pointeau non reconnu.", Toast.LENGTH_LONG).show();
            }
        }
    }

    /**
     * @brief Méthode appelée automatiquement lorsque l'activité est détruite par le système Android.
     * La méthode onDestroy est une méthode appelée par le système Android lorsque ce dernier détruit l'activité (besoin de ressources système, application fermée etc).
     * Cette méthode définie ici que plus aucune ronde n'est en cours.
     */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();

        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putBoolean("RondeEnCours", false);
        editor.commit();

    }

    /**
     * @brief Méthode créant l'interface d'ajout de main courante.
     * Cette méthode crée les différents layouts et boutons permettant la saisie de mains courantes par l'utilisateur.
     * L'interface consiste en une zone de texte, un bouton de validation ainsi qu'une liste déroulante pour afficher les mains courantes saisies et validées.
     */
    private void creerInterfaceAjouterMainCourante()
    {
        Log.d(getString(R.string.tag_log), "Interface créée");

        LinearLayout.LayoutParams layoutParamsWrap = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        LinearLayout.LayoutParams layoutParamsMatch = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);

        Button boutonAjouterMainCourante = new Button(this);
        boutonAjouterMainCourante.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                EditText editText = (EditText)findViewById(R.id.editTextAjouterMainCourante);

                if(!editText.getText().toString().equals(""))
                {
                    GestionBDD bdd = new GestionBDD(InterfaceRondier.this);
                    bdd.enregistrerMainCourante(editText.getText().toString());

                    ajouterMainCouranteListe(editText.getText().toString());

                    editText.setText(null);
                }
                else
                {
                    Toast.makeText(InterfaceRondier.this, "Veuillez saisir une main courante.", Toast.LENGTH_LONG).show();
                }
            }
        });
        boutonAjouterMainCourante.setId(R.id.boutonAjouterMainCourante);
        boutonAjouterMainCourante.setLayoutParams(layoutParamsWrap);
        boutonAjouterMainCourante.setGravity(Gravity.LEFT);
        boutonAjouterMainCourante.setText("Valider");

        TextView txtViewAjouterMainCourante = new TextView(this);
        txtViewAjouterMainCourante.setLayoutParams(layoutParamsWrap);
        txtViewAjouterMainCourante.setGravity(Gravity.CENTER);
        txtViewAjouterMainCourante.setId(R.id.textViewMainCourante);
        txtViewAjouterMainCourante.setText("Ajouter une main courante à " + pointeauScanne.obtenirNom());

        EditText editTextAjouterMainCourante = (EditText)getLayoutInflater().inflate(R.xml.edittext_main_courante, null);
        editTextAjouterMainCourante.setTextColor(getResources().getColor(R.color.black));

        LinearLayout layoutMainCourante = new LinearLayout(this);
        layoutMainCourante.setId(R.id.layoutListeMainsCourantes);
        layoutMainCourante.setLayoutParams(layoutParamsMatch);
        layoutMainCourante.setOrientation(LinearLayout.VERTICAL);

        layoutListeMainsCourantes.addView(txtViewAjouterMainCourante);
        layoutListeMainsCourantes.addView(editTextAjouterMainCourante);
        layoutListeMainsCourantes.addView(boutonAjouterMainCourante);
        layoutListeMainsCourantes.addView(layoutMainCourante);
    }

    /**
     * @brief Méthode créant les interfaces (vierges avec un message d'alerte) pour la prise de photo et la saisie de main courante.
     * Cette méthode crée des interfaces vides avec un message à l'utilisateur l'informant qu'aucun pointeau n'a été scanné et qu'il est obligatoire d'en avoir scanné au moins un pour prendre une photo ou saisir une main courante.
     */
    private void creerTxtViewAucunPointeauScanne()
    {
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        TextView aucunPointScanneMainCourante = new TextView(this);
        aucunPointScanneMainCourante.setId(R.id.txtViewAucunPointeauMainCourante);
        aucunPointScanneMainCourante.setText(R.string.aucun_point_scanne_main_courante);
        aucunPointScanneMainCourante.setGravity(Gravity.CENTER);

        TextView aucunPointScannePhoto = new TextView(this);
        aucunPointScannePhoto.setId(R.id.txtViewAucunPointeauPhoto);
        aucunPointScannePhoto.setText(R.string.aucun_point_scanne_photo);
        aucunPointScannePhoto.setGravity(Gravity.CENTER);

        layoutListePhotos.addView(aucunPointScannePhoto, layoutParams);
        layoutListeMainsCourantes.addView(aucunPointScanneMainCourante);

    }

    /**
     * @brief Méthode supprimant les interfaces créées avec la fonction creerTxtViewAucunPointeauScanne.
     * Cette méthode supprime les messages d'alertes des interfaces de prise de photo ainsi que de saisie de main courante.
     */
    private void supprimerTxtViewAucunPointeauScanne()
    {
        layoutListePhotos.removeView(findViewById(R.id.txtViewAucunPointeauPhoto));
        layoutListeMainsCourantes.removeView(findViewById(R.id.txtViewAucunPointeauMainCourante));
    }

    /**
     * @brief Méthode créant la liste des photos prises et correspondants au dernier pointeau scanné.
     * Cette méthode crée la liste des photos prises par l'utilisateur qui correspondent au dernier pointeau scanné passé en paramètre.
     * Les photos sont récupérées et triées parmis le dossier où elles sont toutes stockées.
     * @param pointeau
     */
    private void creerImagesVisualisation(Pointeau pointeau)
    {
        LinearLayout layoutInterfacePhotos = (LinearLayout)findViewById(R.id.layoutPhotos);
        LinearLayout.LayoutParams layoutParamsImage = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);

        LinearLayout layoutPhotos;
        if(findViewById(R.id.layoutListePhotos) != null)
        {
            layoutPhotos = (LinearLayout)findViewById(R.id.layoutListePhotos);
            layoutPhotos.removeAllViews();
        }
        else
        {
            layoutPhotos = new LinearLayout(this);
            layoutPhotos.setId(R.id.layoutListePhotos);
            layoutPhotos.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));
            layoutPhotos.setOrientation(LinearLayout.VERTICAL);
            layoutInterfacePhotos.addView(layoutPhotos);
        }

        String path = getExternalFilesDir(Environment.DIRECTORY_PICTURES).toString();
        File directory = new File(path);
        ArrayList<File> files = new ArrayList<File>();

        GestionBDD db = new GestionBDD(this);
        ArrayList<String> listeNomsPhotos = db.obtenirPhotosAvecPointeau(pointeau);

        for(int i = 0; i < listeNomsPhotos.size(); i++)
        {
            files.add(new File(directory + "/" + listeNomsPhotos.get(i)));
        }

        final float echelle = getApplicationContext().getResources().getDisplayMetrics().density;
        int pixels = (int) (350 * echelle + 0.5f);

        layoutPhotos.removeAllViews();

        layoutParamsImage.width = pixels;
        layoutParamsImage.gravity = Gravity.CENTER;
        Log.d(getString(R.string.tag_log), "InterfaceRondier: Visualisation.");

        if(files != null)
        {
            for(int i = 0; i < files.size(); i++)
            {
                Bitmap imageBitmap = BitmapFactory.decodeFile(files.get(i).getAbsolutePath());
                ImageView nouvelleImage = new ImageView(this);
                nouvelleImage.setImageBitmap(imageBitmap);

                layoutPhotos.addView(nouvelleImage, layoutParamsImage);

                Log.d(getString(R.string.tag_log), "InterfaceRondier: Filename: " + files.get(i).getName());
            }
        }
    }

    /**
     * @brief Méthode créant le bouton d'ajout de photo.
     * Cette méthode crée le bouton qui, quand pressé, lancera l'activité camera permettant à l'utilisateur de prendre une photo.
     * Le bouton ici défini passe le nom de la ronde en cours ainsi que le nom du dernier point scanné à l'activité camera.
     */
    private void creerBoutonAjouterPhoto()
    {
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER;
        Button boutonAjouterPhoto = new Button(this);
        boutonAjouterPhoto.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                Intent intentActivite = new Intent(InterfaceRondier.this, Camera.class);
                intentActivite.putExtra("nomRonde", ronde.obtenirNom());
                intentActivite.putExtra("nomPoint", pointeauScanne.obtenirNom());
                startActivity(intentActivite);
            }
        });
        boutonAjouterPhoto.setId(R.id.boutonAjouterPhoto);
        boutonAjouterPhoto.setLayoutParams(layoutParams);
        boutonAjouterPhoto.setText("Ajouter une photo à " + pointeauScanne.obtenirNom());

        layoutListePhotos.addView(boutonAjouterPhoto);
    }

    /**
     * @brief Méthode mettant à jour le bouton d'ajout de photo.
     * Cette méthode met à jour le bouton d'ajout de photo avec le nom du dernier pointeau scanné.
     */
    private void mettreAJourTexteBoutonAjouterPhoto()
    {
        Button boutonAjouterPhoto = (Button)findViewById(R.id.boutonAjouterPhoto);
        boutonAjouterPhoto.setText("Ajouter une photo à " + pointeauScanne.obtenirNom());
    }

    /**
     * @brief Méthode mettant à jour le bouton d'ajout de main courante.
     * Cette méthode met à jour le bouton d'ajout de main courante avec le nom du dernier pointeau scanné.
     */
    private void mettreAJourTexteMainCourante()
    {
        TextView textViewMainCourante = (TextView)findViewById(R.id.textViewMainCourante);
        textViewMainCourante.setText("Ajouter une main courante à " + pointeauScanne.obtenirNom());
    }

    /**
     * @brief Méthode créant une checkbox pour le pointeau passé en paramètre.
     * Cette méthode crée une checkbox avec le nom du pointeau passé en paramètre grâce à son index.
     * La checkbox ainsi créée est ensuite ajoutée à la liste des pointeaux à scanner dans l'interface principale.
     * @param index L'index auquel la checkbox doit être créée.
     */
    private void creerCheckboxPointeau(int index)
    {
        CheckBox newCheckBox = new CheckBox(this);
        newCheckBox.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.WRAP_CONTENT, ActionBar.LayoutParams.WRAP_CONTENT));
        newCheckBox.setText("[" + ronde.obtenirListePointeaux().get(index).obtenirNumero() + "] " + ronde.obtenirListePointeaux().get(index).obtenirNom());
        newCheckBox.setTag(ronde.obtenirListePointeaux().get(index).obtenirIdTag());
        newCheckBox.setClickable(false);
        newCheckBox.setChecked(false);

        layoutListePointeaux.addView(newCheckBox, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
    }

    /**
     * @brief Méthode créant et plaçant une checkbox pour le pointeau passé en paramètre à l'index passé en paramètre.
     * Cette méthode crée une checkbox avec le nom du pointeau passé en paramètre inscrit en rouge.
     * La checkbox ainsi créée est ensuite ajoutée à la liste des pointeau à scanner dans l'interface principale après le dernier pointeau coché.
     * @param pointeau Le pointeau utilisé pour créer la checkbox.
     * @param indexRonde L'index auquel la checkbox doit être créée.
     */
    private void creerCheckboxMauvaisPointeau(Pointeau pointeau, int indexRonde)
    {
        CheckBox checkBox = new CheckBox(this);
        checkBox.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.WRAP_CONTENT, ActionBar.LayoutParams.WRAP_CONTENT));
        checkBox.setText("[" + pointeau.obtenirNumero() + "] " + pointeau.obtenirNom());
        checkBox.setTag(pointeau.obtenirIdTag());
        checkBox.setTextColor(getResources().getColor(R.color.red));
        checkBox.setChecked(true);
        checkBox.setClickable(false);

        layoutListePointeaux.addView(checkBox, indexRonde, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
    }

    /**
     * @brief Méthode créant une checkbox pour la main courante passée en paramètre.
     * Cette méthode crée une checkbox avec le texte de la main courante et la date correspondante qui ont été passés en paramètre.
     * La checkbox ainsi créée est ensuite ajoutée à la liste des mains courantes affichée dans l'interface principale.
     * @param mainCourante La main courante utilisée pour créer la checkbox.
     * @param date La date utilisée pour créer la checkbox.
     */
    private void creerCheckboxMainCourante(int index, String mainCourante, String date)
    {
        LinearLayout layoutMainsCourantes = (LinearLayout)findViewById(R.id.layoutListeMainsCourantes);
        CheckBox checkBox = new CheckBox(this);
        checkBox.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.WRAP_CONTENT, ActionBar.LayoutParams.WRAP_CONTENT));
        checkBox.setText(index + ") " + mainCourante + " (" + date + ")");
        checkBox.setChecked(false);
        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked)
                {
                    GestionBDD bdd = new GestionBDD(InterfaceRondier.this);
                    bdd.enregistrerMainCourante(buttonView.getText().toString().substring(buttonView.getText().toString().indexOf(" ")+1, buttonView.getText().toString().lastIndexOf("(")-1));
                }
            }
        });

        layoutMainsCourantes.addView(checkBox, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
    }

    /**
     * @brief Méthode retournant l'ID du pointeau passé entre les différentes activités.
     * Cette méthode récupère dans les fichiers partagés entre les différentes activités l'ID du pointeau.
     * @return L'ID du pointeau partagé.
     */
    private String obtenirIDPointeauTransmis()
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        String idPointeau = prefs.getString("idPointeau", null);

        return idPointeau;
    }

    /**
     * @brief Méthode vérifiant si le dernier pointeau scanné est égale au pointeau indiqué en paramètre.
     * Cette méthode vérifie si le dernier pointeau scanné est le même que le pointeau passé en paramètre grâce à son index.
     * @param index L'index dans la liste des pointeaux vérifié par la fonction.
     * @return Si les pointeaux sont identiques, retourne true. Sinon, retourne false.
     */
    private boolean verificationPointDansRonde(int index)
    {
        boolean valeurRetourne = false;
        if(layoutListePointeaux.getChildAt(index).getTag().toString().equals(pointeauScanne.obtenirIdTag()))
        {
            CheckBox chckBox = (CheckBox) layoutListePointeaux.getChildAt(index);
            if(!chckBox.isChecked())
            {
                chckBox.setChecked(true);

                valeurRetourne = true;
            }
        }

        return valeurRetourne;
    }

    /**
     * @brief Méthode retournant le nom de la ronde passé entre les différentes activités.
     * Cette méthode récupère dans les fichiers partagés entre les différentes activités le nom de la ronde en cours.
     * @return Si une ronde est bien inscrite, retourne une string contenant le nom de la ronde. Sinon, retourne null.
     */
    private String obtenirNomRondeTransmis()
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        return prefs.getString("nomRonde", null);
    }

    /**
     * @brief Méthode retournant l'ID du badge de l'agent passé entre les différentes activités sous forme de string.
     * Cette méthode récupère dans les fichiers partagés entre les différentes activités l'ID du badge de l'agent identifié sous la forme d'une string.
     * @return Si un agent est inscrit, retourne une string contenant l'ID du badge de l'agent. Sinon, retourne null.
     */
    private String obtenirBadgeIDTransmis()
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        return prefs.getString("badgeIDString", null);
    }

    /**
     * @brief Méthode permettant de redémarrer l'application.
     * Cette méthode permet de redémarrer l'application et ainsi de supprimer toute modification sur l'interface de l'application lors de son utilisation (Liste de pointeaux, affichage de mains courantes saisies, affichage des photos prises etc).
     */
    private void redemarrerApplication()
    {
        SharedPreferences prefs = getSharedPreferences("prefs", 0);
        SharedPreferences.Editor editor = prefs.edit();
        editor.clear();
        editor.commit();

        Intent intent = getBaseContext().getPackageManager().getLaunchIntentForPackage(getBaseContext().getPackageName());
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
        finish();
    }

    /**
     * @brief Méthode créant une boîte de dialogue demandant la confirmation de l'arrêt manuel d'une ronde.
     * Cette méthode crée une boîte de dialogue demandant à l'utilisateur s'il souhaite arrêter manuellement la ronde en cours ou la continuer.
     */
    private void demandeFinRonde()
    {
        new AlertDialog.Builder(InterfaceRondier.this)
                .setMessage(R.string.dernier_pointeau)
                .setPositiveButton(R.string.terminer, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        redemarrerApplication();
                    }
                })
                .setNegativeButton(R.string.continuer, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {

                    }
                })
                .show();
    }

    /**
     * @brief Méthode ajoutant la main courante saisie à la liste dans l'interface d'ajout de main courante.
     * Cette méthode ajoute la main courante passée en paramètre sous forme de string à la liste des mains courantes saisies de l'interface d'ajout de main courante.
     * @param mainCourante La main courante qui doit être ajoutée.
     */
    private void ajouterMainCouranteListe(String mainCourante)
    {
        LinearLayout layoutAffichageMainsCourantes = (LinearLayout) findViewById(R.id.layoutListeMainsCourantes);

        TextView txtView = new TextView(this);
        txtView.setText(mainCourante);

        layoutAffichageMainsCourantes.addView(txtView, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT));
    }
}