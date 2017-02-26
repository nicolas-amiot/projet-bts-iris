package client;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DateValidator {

    public static Date validParse(String str, SimpleDateFormat sdf) {
        Date date = null;
        sdf.setLenient(false); // Permet de forcer une erreur sur les dates incorrectes au lieu d'éssayer de l'interpreter.
        // Exemple le dernier jour du mois de janvier est le 30, le 31 janvier ne sera pas considéré comme le 1 février mais comme une erreur.
        try {
            date = sdf.parse(str);
        } catch (ParseException ex) {
        }
        return date;
    }

}
