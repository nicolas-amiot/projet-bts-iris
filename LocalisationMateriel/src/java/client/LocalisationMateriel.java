package client;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.Batiment;
import metier.BatimentService;
import metier.Localisation;
import metier.LocalisationService;
import metier.Materiel;
import metier.MaterielService;
import metier.MetierFactory;
import metier.Salle;
import metier.Type;
import metier.TypeService;

public class LocalisationMateriel extends HttpServlet {

    private static MaterielService materielSrv;
    private static TypeService typeService;
    private static LocalisationService localisationSrv;
    private static BatimentService batimentSrv;
    List<Materiel> materiels;
    List<Salle> salles;
    List<Batiment> batiments;
    Date now;
    SimpleDateFormat dateFormatFr;
    SimpleDateFormat dateFormatEn;
    String strPage;
    int page;
    int debut;
    int parPage;
    int totalElement;
    int maxPage;
    int debutPage;
    int finPage;
    String urlPage;

    @Override
    public void init() throws ServletException {
        try {
            LocalisationMateriel.materielSrv = MetierFactory.getMaterielService();
            LocalisationMateriel.typeService = MetierFactory.getTypeService();
            LocalisationMateriel.localisationSrv = MetierFactory.getLocalisationService();
            LocalisationMateriel.batimentSrv = MetierFactory.getBatimentService();
            dateFormatFr = new SimpleDateFormat("dd/MM/yyyy");
            dateFormatEn = new SimpleDateFormat("yyyy-MM-dd");
        } catch (Exception ex) {
            throw new ServletException(ex.getMessage());
        }
    }

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        materiels = new ArrayList<Materiel>();
        salles = new ArrayList<Salle>();
        batiments = new ArrayList<Batiment>();
        now = new Date();
        String attribut = request.getParameter("attribut");
        String recherche = request.getParameter("recherche");
        Date date = now;

        if (attribut != null) {

            if (attribut.equals("controleAFaire")) { // Initialise les attributs supplémentaires pour cet valeur
                int jour;
                try {
                    jour = Integer.parseInt(recherche);
                } catch (NumberFormatException e) {
                    jour = 0;
                }
                GregorianCalendar calendar = new GregorianCalendar(); // Crée un calendirer grégorian afin de respecter les années biseextiles...
                calendar.setTime(date); // Date d'aujourd'hui
                calendar.add(Calendar.DATE, jour); // Ajoute x jour à la date
                date = calendar.getTime(); // On récupère la valeur sous une date
            }

            strPage = (String) request.getParameter("page");
            try { // Récupère la page demandé, s'il y a une erreur, la première page est donnée
                page = Integer.parseInt(strPage);
            } catch (NumberFormatException e) {
                page = 1;
            }
            if (page < 1) { // Si la page demandé est en dessous de 1, la première page est donnée
                page = 1;
            }
            parPage = 10; // initatilise nombre d'élément par page

            totalElement = 0;
            if(attribut.equals("all")){
                totalElement = materielSrv.getCount();
            } else if (attribut.equals("controleAFaire")) {
                totalElement = materielSrv.getCountByPeriode(date, true);
            } else if (attribut.equals("idBadge")) {
                totalElement = 1;
            } else if (attribut.equals("dateControle")) {
                Date dateControle;
                dateControle = DateValidator.validParse(recherche, dateFormatEn); // Test le format englais en premier: aaaa-mm-jj
                if (dateControle != null) {
                    totalElement = materielSrv.getCountByDateControle(dateControle);
                } else {
                    dateControle = DateValidator.validParse(recherche, dateFormatFr); // Puis le format francais si celui en anglais n'a pas réussi: jj/mm/aaaa
                    if (dateControle != null) {
                        totalElement = materielSrv.getCountByDateControle(dateControle);
                    }
                }
            } else if (attribut.equals("nomMateriel")) {
                totalElement = materielSrv.getCountByNomMateriel(recherche);
            } else if (attribut.equals("nomType")) {
                Type type = typeService.getByNomType(recherche);
                totalElement = materielSrv.getCountByType(type);
            }

            if (totalElement > parPage) { // Si le nombre d'élément est supérieur à ce que la page peut contenir

                urlPage = "&attribut=" + attribut + "&recherche=" + recherche; // url de la page actuelle
                maxPage = totalElement / parPage; // nombre de page pleine (int)
                if (totalElement % parPage != 0) {  // Si il reste des élément, on rajoute une page
                    maxPage = maxPage + 1;
                }
                if (page > maxPage) { // Si la page demandé est au dessus du nombre de page, la derniere page est donnée
                    page = maxPage;
                }

                request.setAttribute("page", page);
                request.setAttribute("urlPage", urlPage);

                if (maxPage > 10) {
                    // barre de pagination doit contenir au aximum les 10 numéros de page les plus proches de la page actuelle
                    // 4 avant numéro de page demandé et 5 après
                    int decalage = 0;
                    debutPage = page - 4; // premier numéro de page à afficher sur la barre de pagination
                    if (debutPage < 1) {
                        decalage = debutPage - 1; // Si la barre de pagination ne peut pas afficher 4 numéro de page avant celle demandé, on récupère l'opposé du nombre de page qui n'a pas pu être affiché
                        debutPage = 1;
                    }
                    finPage = page + 5; // Dernier numéro de page à afficher sur la barre de pagination
                    if (finPage > maxPage) {
                        decalage = finPage - maxPage; // Si la barre de pagination ne peut pas afficher 5 numéro de page après celle demandé, on récupère le nombre de page qui n'a pas pu être affiché
                        finPage = maxPage;
                    }
                    if (decalage < 0) {
                        finPage = finPage - decalage; // Le nombre de page qui n'ont pas été affiché avant la page demandé vont être introduit après la page demandé
                    } else if (decalage > 0) {
                        debutPage = debutPage - decalage; // Le nombre de page qui n'ont pas été affiché après la page demandé vont être introduit avant la page demandé
                    }
                } else { // S'il n'y a pas plus de 10 pages, on les affichent normalement
                    debutPage = 1;
                    finPage = maxPage;
                }
                request.setAttribute("debutPage", debutPage);
                request.setAttribute("finPage", finPage);
                request.setAttribute("maxPage", maxPage);
            }

            debut = (page - 1) * parPage;
            if(attribut.equals("all")){
                materiels.addAll(materielSrv.getAll(debut, parPage)); // addAll permet d'ajouter tous les éléments d'une collection à notre liste actuelle. Accepte la valeur null, dans ce cas rien n'est ajouté
            } else if (attribut.equals("controleAFaire")) {
                materiels.addAll(materielSrv.getByPeriode(date, true, debut, parPage));
            } else if (attribut.equals("idBadge")) {
                Materiel materiel = materielSrv.getByIdBadge(recherche);
                if (materiel != null) {
                    materiels.add(materiel); // add permet d'ajouter un élément non null à notre liste actuelle
                }
            } else if (attribut.equals("dateControle")) {
                Date dateControle;
                dateControle = DateValidator.validParse(recherche, dateFormatEn);
                if (dateControle != null) {
                    materiels.addAll(materielSrv.getByDateControle(dateControle, debut, parPage));
                } else {
                    dateControle = DateValidator.validParse(recherche, dateFormatFr);
                    if (dateControle != null) {
                        materiels.addAll(materielSrv.getByDateControle(dateControle, debut, parPage));
                    }
                }
            } else if (attribut.equals("nomMateriel")) {
                materiels.addAll(materielSrv.getByNomMateriel(recherche, debut, parPage));
            } else if (attribut.equals("nomType")) {
                Type type = typeService.getByNomType(recherche);
                materiels.addAll(materielSrv.getByType(type, debut, parPage));
            }
            for (Materiel materiel : materiels) { // Pour tous les matériels on récupère sa localisation afin de connaître la salle est donc le batîment ou ce trouve chaque matériel
                Localisation localisation = localisationSrv.getByMateriel(materiel);
                if(localisation != null){ // Si une localisation existe on recherche sa localisation
                    Salle salle = localisation.getSalle();
                    salles.add(salle);
                    batiments.add(batimentSrv.getBySalle(salle));
                }else{ // Sinon on indique qu'il n'en a pas en mettant null
                    salles.add(null);
                    batiments.add(batimentSrv.getBySalle(null));
                }
            }
            request.setAttribute("now", now);
            request.setAttribute("materiels", materiels);
            request.setAttribute("salles", salles);
            request.setAttribute("batiments", batiments);

        }

        String view = "localisationMateriel";
        view = "/" + view + ".jsp";
        request.setAttribute("view", view);

        String template = "Default";
        request.getRequestDispatcher("/Template/" + template + "/main.jsp").forward(request, response);
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
