package client;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.Materiel;
import metier.MaterielService;
import metier.MetierFactory;
import metier.Type;
import metier.TypeService;

public class Test extends HttpServlet {

    private static MaterielService materielSrv;
    private static TypeService typeSrv;
    List<Object> list;
    SimpleDateFormat dateFormat;
    String choixMateriel;
    long id;
    String idBadge;
    Date dateControle;
    Date newDateControle;
    String nomMateriel;
    String nomType;
    Type type;
    int debut;
    int parPage;
    boolean avant;

    @Override
    public void init() throws ServletException {
        try {
            Test.materielSrv = MetierFactory.getMaterielService();
            Test.typeSrv = MetierFactory.getTypeService();
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
        list = new ArrayList<Object>();
        dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        choixMateriel = request.getParameter("choixMateriel");
        try {
            id = Long.parseLong(request.getParameter("id"));
        } catch (NumberFormatException ex) {
            id = 0;
            Logger.getLogger(Test.class.getName()).log(Level.SEVERE, null, ex);
        }
        idBadge = request.getParameter("idBadge");
        if (request.getParameter("dateControle") != null) {
            dateControle = DateValidator.validParse(request.getParameter("dateControle"), dateFormat);
        }
        if (request.getParameter("newDateControle") != null) {
            newDateControle = DateValidator.validParse(request.getParameter("newDateControle"), dateFormat);
        }
        nomMateriel = request.getParameter("nomMateriel");
        nomType = request.getParameter("nomType");
        type = typeSrv.getByNomType(nomType);
        try {
            parPage = Integer.parseInt(request.getParameter("parPage"));
            debut = (Integer.parseInt(request.getParameter("page")) - 1) * parPage;
        } catch (NumberFormatException ex) {
            parPage = 0;
            debut = 0;
            Logger.getLogger(Test.class.getName()).log(Level.SEVERE, null, ex);
        }
        avant = request.getParameter("avant") != null;
        if (choixMateriel != null) {
            if (choixMateriel.equals("add")) {
                list.add(materielSrv.add(new Materiel(idBadge, dateControle, newDateControle, nomMateriel, type)));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("remove")) {
                Materiel materiel = materielSrv.getById(id);
                list.add(materielSrv.remove(materiel));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("update")) {
                Materiel materiel = materielSrv.getById(id);
                if (!idBadge.isEmpty()) {
                    materiel.setIdBadge(idBadge);
                }
                if (dateControle != null && !dateControle.toString().isEmpty()) {
                    materiel.setDateControle(dateControle);
                }
                if (newDateControle != null && !newDateControle.toString().isEmpty()) {
                    materiel.setNewDateControle(newDateControle);
                }
                if (!nomMateriel.isEmpty()) {
                    materiel.setNomMateriel(nomMateriel);
                }
                if (type != null) {
                    materiel.setType(type);
                }
                list.add(materielSrv.update(materiel));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getById")) {
                list.add(materielSrv.getById(id));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getAll")) {
                List<Materiel> materiels = materielSrv.getAll(debut, parPage);
                if(materiels != null){
                list.addAll(materiels);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCount")) {
                list.add(materielSrv.getCount());
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getBiIdBadge")) {
                list.add(materielSrv.getByIdBadge(idBadge));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getListIdBadge")) {
                List<String> listIdBadge = materielSrv.getListIdBadge(debut, parPage);
                if(listIdBadge != null){
                list.addAll(listIdBadge);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountListIdBadge")) {
                list.add(materielSrv.getCountListIdBadge());
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getByDateControle")) {
                List<Materiel> materiels = materielSrv.getByDateControle(dateControle, debut, parPage);
                if(materiels != null){
                    list.addAll(materiels);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountByDateControle")) {
                list.add(materielSrv.getCountByDateControle(dateControle));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getListDateControle")) {
                List<Date> listDate = materielSrv.getListDateControle(debut, parPage);
                if(listDate != null){
                    list.addAll(listDate);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountListDateControle")) {
                list.add(materielSrv.getCountListDateControle());
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getByNewDateControle")) {
                List<Materiel> materiels = materielSrv.getByNewDateControle(newDateControle, debut, parPage);
                if(materiels != null){
                    list.addAll(materiels);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountByNewDateControle")) {
                list.add(materielSrv.getCountByNewDateControle(newDateControle));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getListNewDateControle")) {
                List<Date> listDate = materielSrv.getListNewDateControle(debut, parPage);
                if(listDate != null){
                    list.addAll(listDate);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountListNewDateControle")) {
                list.add(materielSrv.getCountListNewDateControle());
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getByPeriode")) {
                List<Materiel> materiels = materielSrv.getByPeriode(dateControle, avant, debut, parPage);
                if(materiels != null){
                    list.addAll(materiels);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountByPeriode")) {
                list.add(materielSrv.getCountByPeriode(dateControle, avant));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getByNomMateriel")) {
                List<Materiel> materiels = materielSrv.getByNomMateriel(nomMateriel, debut, parPage);
                if(materiels != null){
                list.addAll(materiels);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountByNomMateriel")) {
                list.add(materielSrv.getCountByNomMateriel(nomMateriel));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getListNomMateriel")) {
                List<String> listNomMateriel = materielSrv.getListNomMateriel(debut, parPage);
                if(listNomMateriel != null){
                list.addAll(listNomMateriel);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountListNomMateriel")) {
                list.add(materielSrv.getCountListNomMateriel());
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getByType")) {
                List<Materiel> materiels = materielSrv.getByType(type, debut, parPage);
                if(materiels != null){
                list.addAll(materiels);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountByType")) {
                list.add(materielSrv.getCountByType(type));
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getListType")) {
                List<Type> types = materielSrv.getListType(debut, parPage);
                if(types != null){
                list.addAll(types);
                }
                request.setAttribute("list", list);
            } else if (choixMateriel.equals("getCountListType")) {
                list.add(materielSrv.getCountListType());
                request.setAttribute("list", list);
            }
        }
        request.getRequestDispatcher("/test.jsp").forward(request, response);
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
