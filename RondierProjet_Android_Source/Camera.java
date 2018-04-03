package com.project.rondierprojet;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.google.android.cameraview.CameraView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Calendar;

/**
 * @file Camera.java
 * @brief Définition de la classe de gestion de la caméra
 * @version 1.0
 * @author Tanguy Herbron
 * @date 30 Mars 2017
 *
 * Classe modélisant la caméra créée à partir de l'API de yaraki (https://github.com/google/cameraview)
 * Cette classe permet de créer l'aperçu d'une caméra ainsi que d'enregistrer une photo prise et ce en prenant compte automatiquement de la version d'Android utilisée.
 */
public class Camera extends AppCompatActivity implements ActivityCompat.OnRequestPermissionsResultCallback{

    private View vuePrincipale;

    private CameraView vueCamera;

    private FloatingActionButton boutonCapture;

    private Handler threadFond;

    private Calendar tempsPresent;

    private String nomPointeau;

    private String nomRonde;

    private int etatFlashCourant;

    private static final int REQUETE_CAMERA_PERMISSION = 1;

    private static final String FRAGMENT_DIALOG = "dialog";

    private static final int[] OPTIONS_FLASH = {
            CameraView.FLASH_AUTO,
            CameraView.FLASH_OFF,
            CameraView.FLASH_ON,
    };

    private static final int[] ICONS_FLASH = {
            R.drawable.ic_flash_auto,
            R.drawable.ic_flash_off,
            R.drawable.ic_flash_on,
    };

    private static final int[] TITRES_FLASH = {
            R.string.flash_auto,
            R.string.flash_off,
            R.string.flash_on,
    };

    private View.OnClickListener mOnClickListener = new View.OnClickListener() {

        /**
         * @brief onClick general de la classe
         * Méthode permettant de définir quelle action à effecter lorsqu'un bouton est clické.
         */
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.prendre_photo:
                    if (vueCamera != null) {
                        vueCamera.takePicture();
                    }
                    break;
            }
        }
    };

    /**
     * @brief Méthode appelée automatiquement après l'instanciation de la classe.
     * La méthode onCreate est une méthode appelée par le système Android à l'instanciation de la classe.
     * Cette méthode est ici utilisée pour attacher les différents éléments du code avec l'interface graphique.
     * @param savedInstanceState Etat antérieur de l'activité.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);

        Intent intent = getIntent();
        nomRonde = intent.getStringExtra("nomRonde");
        nomPointeau = intent.getStringExtra("nomPoint");

        vuePrincipale = findViewById(R.id.vuePrincipale);
        vueCamera = (CameraView) findViewById(R.id.camera);
        if(vueCamera != null)
        {
            vueCamera.addCallback(mCallback);
        }

        boutonCapture = (FloatingActionButton) findViewById(R.id.prendre_photo);
        if(boutonCapture != null)
        {
            boutonCapture.setOnClickListener(mOnClickListener);
        }

        Toolbar barOutil = (Toolbar) findViewById(R.id.bar_outil);
        setSupportActionBar(barOutil);
        ActionBar actionBar = getSupportActionBar();
        if(actionBar != null)
        {
            actionBar.setDisplayShowTitleEnabled(false);
            actionBar.setDisplayHomeAsUpEnabled(true);
        }
    }

    /**
     * @brief Méthode appelée automatiquement après l'initialisation de la classe.
     * La méthode onResume est une méthode appelée par le système Android après l'initialisation de la classe.
     * Cette méthode est ici utilisée pour vérifier si l'application dispose de toutes les autorisations nécessaires et, si ça n'est pas le cas, demande à l'utilisateur de les lui accorder.
     */
    @Override
    protected void onResume() {
        super.onResume();
        if (ContextCompat.checkSelfPermission(this, android.Manifest.permission.CAMERA)
                == PackageManager.PERMISSION_GRANTED) {
            vueCamera.start();
        } else if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                android.Manifest.permission.CAMERA)) {
            ConfirmationDialogFragment
                    .newInstance(R.string.confirmation_permission_camera,
                            new String[]{android.Manifest.permission.CAMERA},
                            REQUETE_CAMERA_PERMISSION,
                            R.string.permission_camera_non_accorde)
                    .show(getSupportFragmentManager(), FRAGMENT_DIALOG);
        } else {
            ActivityCompat.requestPermissions(this, new String[]{android.Manifest.permission.CAMERA},
                    REQUETE_CAMERA_PERMISSION);
        }
    }

    /**
     * @brief Méthode appelée automatiquement lorsque l'activité est mise en pause.
     * La méthode onPause est une méthode appelée par le système Android à la mise en pause de cette activité (application mise en arrière plan, verrouillage du smartphone etc.)
     * Cette méthode est ici utilisée pour arrêter l'aperçu de la caméra lorsque l'activité n'est plus visible par l'utilisateur.
     */
    @Override
    protected void onPause() {
        vueCamera.stop();
        super.onPause();
    }

    /**
     * @brief Méthode appelée automatiquement lorsque l'activité est détruite par le système Android.
     * La méthode onDestroy est une méthode appelée par le système Android lorsque ce dernier détruit l'activité (besoin de ressources système, application fermée etc).
     * Cette méthode est ici utilisée pour détruire, en fonction de la version Android, l'interface de prévision de façon correcte.
     */
    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (threadFond != null) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR2) {
                threadFond.getLooper().quitSafely();
            } else {
                threadFond.getLooper().quit();
            }
            threadFond = null;
        }
    }

    private CameraView.Callback mCallback
            = new CameraView.Callback() {

        /**
         * @brief Méthode appelée automatiquement à l'ouverture de la caméra.
         * La méthode onCameraOpened est une méthode appelée par le système Android lorsqu'une caméra est lancée.
         * Cette méthode envoit ici un message dans les logs et appelle la fonction créant le bouton permettant de prendre une photo.
         * @param cameraView L'association {@link CameraView}.
         */
        @Override
        public void onCameraOpened(CameraView cameraView) {
            Log.d(getString(R.string.tag_log), "Camera:onCameraOpened");
            repositionCaptureFab();
        }

        @Override
        public void onCameraClosed(CameraView cameraView) {
            Log.d(getString(R.string.tag_log), "Camera:onCameraClosed");
        }

        /**
         * @brief Méthode appelée automatiquement lors de la prise d'une photo.
         * La méthode onPictureTaken est une méthode appelée par le système Android lorsqu'une photo est prise.
         * Cette méthode va ici créer une fichier temporaire correspondant à la photo prise utilisée pour la prévisualisation donnée à l'utilisateur.
         * Lorsque l'image a bien été créée, une fenêtre de dialogue est appelée pour faire la prévisualisation à l'utilisateur.
         * La photo est ensuite supprimée pour éviter tout problème de surcharge de la mémoire du smartphone.
         * @param cameraView L'association {@link CameraView}.
         * @param data       Données au format JPEG.
         */
        @Override
        public void onPictureTaken(CameraView cameraView, final byte[] data) {

            Log.d(getString(R.string.tag_log), "Camera:onPictureTaken " + data.length);

            tempsPresent = Calendar.getInstance();

            Toast.makeText(cameraView.getContext(), R.string.photo_prise, Toast.LENGTH_SHORT)
                    .show();
            obtenirThreadFond().post(new Runnable() {
                @Override
                public void run() {

                    File dossierTemp = Camera.this.getCacheDir();
                    File photoTemp = creationPhotoTemp(dossierTemp, data);

                    if(photoTemp != null)
                    {
                        //Changement du format de l'image pour ensuite pouvoir changer sa taille pour l'usage dans l'alartdialog
                        Bitmap bitMap = BitmapFactory.decodeFile(photoTemp.getAbsolutePath());
                        bitMap = Bitmap.createScaledBitmap(bitMap, 540, 960, true);

                        ImageView tmpImage = new ImageView(Camera.this);
                        tmpImage.setImageBitmap(bitMap);
                        tmpImage.setLayoutParams(new ActionBar.LayoutParams(ActionBar.LayoutParams.MATCH_PARENT, ActionBar.LayoutParams.MATCH_PARENT));

                        creerFenetreDialogue(tmpImage, data, photoTemp);

                        photoTemp.delete();

                    }
                }
            });
        }

    };

    /**
     * @brief Méthode créant le menu de la bar d'outils.
     * Cette méthode crée dynamiquement les éléments du menu de la bar d'outils.
     * @param menu Le menu qui doit être créé.
     * @return Vrai dans tous les cas.
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    /**
     * @brief Méthode en charge des événements de la bar d'outils.
     * Cette méthode change les icones de la bar d'outils ainsi que les réglages de la camera lorsque l'utilisateur clique sur les éléments de la bar d'outils.
     * @param item L'item du menu sélectionné.
     * @return Faux dans tous les cas.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
            case R.id.choix_flash:
                if(vueCamera != null)
                {
                    etatFlashCourant = (etatFlashCourant + 1) % OPTIONS_FLASH.length;
                    item.setTitle(TITRES_FLASH[etatFlashCourant]);
                    item.setIcon(ICONS_FLASH[etatFlashCourant]);
                    vueCamera.setFlash(OPTIONS_FLASH[etatFlashCourant]);
                }
                break;
            case R.id.choix_camera:
                if(vueCamera != null)
                {
                    int sens = vueCamera.getFacing();
                    vueCamera.setFacing(sens == CameraView.FACING_FRONT ?
                        CameraView.FACING_BACK : CameraView.FACING_FRONT);
                }
                break;
            case android.R.id.home:
                Log.d(getString(R.string.tag_log), "Camera:Bouton retour pressée.");
                retourActiviteInterfaceRondier();
        }
        return false;
    }

    /**
     * @brief Méthode permettant d'écrire la photo capturée dans la mémoire du smartphone.
     * Cette méthode écrit dans un dossier temporaire passé en paramètre la photo passée en paramètre.
     * @param dossierTemp Le chemin vers le dossier temporaire.
     * @param data Les données au format JPEG de l'image.
     * @return La photo temporaire créée.
     */
    private File creationPhotoTemp(File dossierTemp, byte[] data)
    {
        File photoTemp = null;

        try
        {
            photoTemp = File.createTempFile("000", ".jpg", dossierTemp);

            OutputStream sortieTemp = null;
            try {
                sortieTemp = new FileOutputStream(photoTemp);
                sortieTemp.write(data);
                sortieTemp.close();
            } catch (IOException e) {
                Log.w(getString(R.string.tag_log), "Camera: Impossible d'écrire " + photoTemp, e);
            } finally {
                if (sortieTemp != null) {
                    try {
                        sortieTemp.close();
                    } catch (IOException e) {
                        // Ignore
                    }
                }
            }

        } catch (IOException e)
        {
            // Ignore
        }

        return photoTemp;
    }

    /**
     * @brief Méthode permettant de créer une fenêtre de dialogue.
     * Cette méthode crée et affiche une fenêtre de dialogue permettant de montrer une photo entrée en paramètre à l'utilisateur.
     * L'utilisateur peut ensuite décider de conserver cette photo et donc de l'enregistrer dans un répertoire défini par le système ou refuser de garder cette photo.
     * Les photos enregistrées sont situées dans /sdcard/Android/data/<nom paquet application>/files/Pictures.
     * @param tmpImage La prévisualisation de l'image dans l'interface.
     * @param data Les données au format JPEG de l'image.
     * @param photoTemp L'image utilisée pour créer la prévisualisation.
     */
    private void creerFenetreDialogue(ImageView tmpImage, final byte[] data, final File photoTemp)
    {
        new AlertDialog.Builder(Camera.this)
                .setMessage(R.string.demande_validité_photo)
                .setView(tmpImage)
                .setPositiveButton(R.string.oui, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        //Enregistrer la photo et supprimer la photo temporaire
                        String nomFicher = nomRonde + "|" + nomPointeau + "|" + tempsPresent.get(Calendar.DAY_OF_MONTH) + "." + (tempsPresent.get(Calendar.MONTH) + 1) +
                                "." + tempsPresent.get(Calendar.YEAR) + "|" + tempsPresent.get(Calendar.HOUR_OF_DAY) + "." + tempsPresent.get(Calendar.MINUTE) +
                                "." + tempsPresent.get(Calendar.SECOND) + ".jpg";
                        File imageFinale = new File(getExternalFilesDir(Environment.DIRECTORY_PICTURES), nomFicher);

                        OutputStream sortieFinale = null;
                        try {
                            sortieFinale = new FileOutputStream(imageFinale);
                            sortieFinale.write(data);
                            sortieFinale.close();

                            GestionBDD db = new GestionBDD(Camera.this);
                            db.enregistrerPhoto(nomFicher);

                            sortieFinale = null;
                        } catch (IOException e) {
                            Log.w(getString(R.string.tag_log), "Impossible d'écrire " + photoTemp.getName(), e);
                        } finally {
                            if (sortieFinale != null) {
                                try {
                                    sortieFinale.close();
                                } catch (IOException e) {
                                    // Ignore
                                }
                            }
                        }

                        Camera.this.retourActiviteInterfaceRondier();
                    }
                })
                .setNegativeButton(R.string.annuler_photo, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {

                    }
                })
                .show();
    }

    /**
     * @brief Méthode permettant de créer un thread pour l'arrière plan de l'activité.
     * Cette méthode crée, s'il n'en existe pas déjà un, un thread utilisé pour actualiser le fond de l'activité (ici l'aperçu que fourni la camera).
     * @return Le thread créé.
     */
    private Handler obtenirThreadFond() {
        if (threadFond == null) {
            HandlerThread thread = new HandlerThread("background");
            thread.start();
            threadFond = new Handler(thread.getLooper());
        }
        return threadFond;
    }

    /**
     * @brief Méthode permettant de replacer le bouton de capture de photo.
     * Cette méthode permet de repositionner le bouton de capture en fonction de la taille de l'écran sur lequel l'application est lancée.
     */
    private void repositionCaptureFab() {
        if ((vuePrincipale == null) || (vueCamera == null) || (boutonCapture == null)) {
            return;
        }
        boutonCapture.post(new Runnable() {
            @Override
            public void run() {
                RelativeLayout.LayoutParams layoutParams =
                        (RelativeLayout.LayoutParams) boutonCapture.getLayoutParams();

                DisplayMetrics displayMetrics = getResources().getDisplayMetrics();
                int minMargin = (int) (15 * displayMetrics.density + 0.5f);

                if (displayMetrics.widthPixels > displayMetrics.heightPixels) {
                    int rightMargin = ((vuePrincipale.getWidth() - vueCamera.getWidth()) / 2) -
                            (boutonCapture.getWidth() / 2);
                    if (rightMargin < minMargin) {
                        rightMargin = minMargin;
                    }
                    layoutParams.rightMargin = rightMargin;
                } else {
                    int bottomMargin = ((vuePrincipale.getHeight() - vueCamera.getHeight()) / 2) -
                            (boutonCapture.getHeight() / 2);
                    if (bottomMargin < minMargin) {
                        bottomMargin = minMargin;
                    }
                    layoutParams.bottomMargin = bottomMargin;
                }

                boutonCapture.setLayoutParams(layoutParams);
            }
        });
    }

    /**
     * @brief Méthode permettant de retourner à l'activité InterfaceRondier.
     * Cette méthode permet de retourner à l'activité InterfaceRondier tout en terminant l'activité Camera.
     */
    private void retourActiviteInterfaceRondier()
    {
        Intent intent = new Intent(this, InterfaceRondier.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        startActivity(intent);
        finish();
    }
}
