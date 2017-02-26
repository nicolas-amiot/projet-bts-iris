package client;

import com.google.gson.Gson;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.MaterielService;
import metier.MetierFactory;
import metier.Type;

public class AjaxListeDeroulanteMateriel extends HttpServlet {

    private static MaterielService materielSrv;
    String json;
    List<String> listElement;
    SimpleDateFormat dateFormat;
    String strPage;
    int page;
    int debut;
    int parPage;
    int totalElement;
    int maxPage;

    @Override
    public void init() throws ServletException {
        try {
            AjaxListeDeroulanteMateriel.materielSrv = MetierFactory.getMaterielService();
            dateFormat = new SimpleDateFormat("dd/MM/yyyy");
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
        listElement = new ArrayList<String>();
        String attribut = request.getParameter("attribut");
        strPage = request.getParameter("page");
        try {
            page = Integer.parseInt(strPage);
        } catch (NumberFormatException e) {
            page = 1;
        }
        if (page < 1) {
            page = 1;
        }
        parPage = 100;
        if (attribut.equals("idBadge")) {
            totalElement = materielSrv.getCountListIdBadge();
        } else if (attribut.equals("dateControle")) {
            totalElement = materielSrv.getCountListDateControle();
        } else if (attribut.equals("nomMateriel")) {
            totalElement = materielSrv.getCountListNomMateriel();
        } else if (attribut.equals("nomType")) {
            totalElement = materielSrv.getCountListType();
        } else {
            totalElement = 0;
        }

        maxPage = totalElement / parPage;
        if (totalElement % parPage != 0 || totalElement < 1) {
            maxPage = maxPage + 1;
        }
        if (page > maxPage) {
            page = maxPage;
        }

        debut = (page - 1) * parPage;
        
        listElement.add(Integer.toString(maxPage));
        if (attribut.equals("idBadge")) {
            listElement.addAll(materielSrv.getListIdBadge(debut, parPage));
        } else if (attribut.equals("dateControle")) {
            List<Date> listDateControle = materielSrv.getListDateControle(debut, parPage);
            for (Date dateControle : listDateControle) {
                listElement.add(dateFormat.format(dateControle));
            }
        } else if (attribut.equals("nomMateriel")) {
            listElement.addAll(materielSrv.getListNomMateriel(debut, parPage));
        } else if (attribut.equals("nomType")) {
            List<Type> types = materielSrv.getListType(debut, parPage);
            for (Type type : types) {
                listElement.add(type.getNomType());
            }
        }
        json = new Gson().toJson(listElement); // Crée une une chaine de caractère en json grâce à la librairie Gson
        response.setContentType("application/json"); // Définit le type de réponse envoyé au client
        response.setCharacterEncoding("UTF-8"); // Définit l'encodage de caractère
        response.getWriter().write(json); // Renvoie un objet contenant du texte et qui peut être lu par le client
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
