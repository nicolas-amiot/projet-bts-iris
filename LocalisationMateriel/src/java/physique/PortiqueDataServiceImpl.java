package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import metier.LecteurRFID;
import metier.Portique;
import metier.Salle;

public class PortiqueDataServiceImpl implements PortiqueDataService{

    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;
    private final SalleDataService salleDataSrv;
    private final LecteurRFIDDataService lecteurDataSrv;

    PortiqueDataServiceImpl() {
        sql = new ServiceSQLImpl();
        salleDataSrv = PhysiqueFactory.getSalleDataService();
        lecteurDataSrv = PhysiqueFactory.getLecteurRFIDDataService();
    }
    
    private void close() throws SQLException, Exception{
        if(!this.result.isClosed()){
            this.result.close();
        }
        if(!this.statement.isClosed()){
            this.statement.close();
        }
        if(!this.cnx.isClosed()){
            this.cnx.close();
        }
        this.sql.close();
    }

    private Portique createPortique(ResultSet result) throws Exception {
        long id = result.getLong("id");
        float x = result.getFloat("x");
        float y = result.getFloat("y");
        long idSalle1 = result.getLong("idSalle1");
        long idSalle2 = result.getLong("idSalle2");
        long idLecteur = result.getLong("idLecteur");
        Salle salle1 = salleDataSrv.getById(idSalle1);
        Salle salle2 = salleDataSrv.getById(idSalle2);
        LecteurRFID lecteur = lecteurDataSrv.getById(idLecteur);
        Portique portique = new Portique(x, y, salle1, salle2, lecteur);
        portique.setId(id);
        return portique;
    }
    
    @Override
    public Portique add(Portique portique) throws Exception {
        cnx = this.sql.connect();
        Portique newPortique = null;
        String query = "INSERT INTO portique (x, y, idSalle1, idSalle2, idLecteur) VALUES (?, ?, ?, ?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setFloat(1, portique.getX());
        statement.setFloat(2, portique.getY());
        statement.setLong(3, portique.getSalle1().getId());
        if(portique.getSalle2() != null && portique.getSalle2().getId() > 0){
            statement.setLong(4, portique.getSalle2().getId());
        }else{
            statement.setNull(4, java.sql.Types.INTEGER);
        }
        statement.setLong(5, portique.getLecteurRFID().getId());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newPortique = getById(result.getLong(1));
            }
        }
        this.close();
        return newPortique;
    }

    @Override
    public boolean remove(Portique portique) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM portique WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, portique.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Portique portique) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE portique SET x = ?, y = ?, idSalle1 = ?, idSalle2 = ?, idLecteur = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setFloat(1, portique.getX());
        statement.setFloat(2, portique.getY());
        statement.setLong(3, portique.getSalle1().getId());
        if(portique.getSalle2() != null && portique.getSalle2().getId() > 0){
            statement.setLong(4, portique.getSalle2().getId());
        }else{
            statement.setNull(4, java.sql.Types.INTEGER);
        }
        statement.setLong(5, portique.getLecteurRFID().getId());
        statement.setLong(6, portique.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<Portique> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Portique> portiques = new ArrayList<Portique>();
        String query = "SELECT * FROM portique ORDER BY id ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            portiques.add(createPortique(result));
        }
        this.close();
        return portiques;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM portique";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Portique getById(long id) throws Exception {
        cnx = this.sql.connect();
        Portique portique = null;
        String query = "SELECT * FROM portique WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            portique = createPortique(result);
        }
        this.close();
        return portique;
    }

    @Override
    public Portique getByLecteurRFID(LecteurRFID lecteur) throws Exception {
        cnx = this.sql.connect();
        Portique portique = null;
        String query = "SELECT * FROM portique WHERE idLecteur = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, lecteur.getId());
        result = statement.executeQuery();
        if (result.next()) {
            portique = createPortique(result);
        }
        this.close();
        return portique;
    }

    @Override
    public List<LecteurRFID> getListLecteurRFID(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<LecteurRFID> lecteurs = new ArrayList<LecteurRFID>();
        String query = "SELECT * FROM lecteur WHERE id IN (SELECT idLecteur FROM portique) ORDER BY ip ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            long id = result.getLong("id");
            String ip = result.getString("ip");
            String modele = result.getString("modele");
            boolean etatOn = result.getBoolean("etatOn");
            LecteurRFID lecteur = new LecteurRFID(ip, modele, etatOn);
            lecteur.setId(id);
            lecteurs.add(lecteur);
        }
        this.close();
        return lecteurs;
    }

    @Override
    public int getCountListLecteurRFID() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM lecteur WHERE id IN (SELECT idLecteur FROM portique)";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Portique> getBySalle(Salle salle, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Portique> portiques = new ArrayList<Portique>();
        String query = "SELECT * FROM portique WHERE idSalle1 = ? OR idSalle2 = ? ORDER BY id ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
        statement.setLong(2, salle.getId());
        statement.setInt(3, debut);
        statement.setInt(4, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            portiques.add(createPortique(result));
        }
        this.close();
        return portiques;
    }

    @Override
    public int getCountBySalle(Salle salle) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM portique WHERE idSalle1 = ? OR idSalle2 = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
        statement.setLong(2, salle.getId());
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Salle> getListSalle(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        Salle salle;
        List<Salle> salles = new ArrayList<Salle>();
        String query = "SELECT * FROM salle WHERE id IN (SELECT DISTINCT idSalle1 FROM portique UNION SELECT idSalle2 FROM portique) ORDER BY numSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            long id = result.getLong("id");
            int x_ini = result.getInt("x_ini");
            int y_ini = result.getInt("y_ini");
            int x_fin = result.getInt("x_fin");
            int y_fin = result.getInt("y_fin");
            int numSalle = result.getInt("numSalle");
            String nomSalle = result.getString("nomSalle");
            String nomAtelier = result.getString("nomAtelier");
            salle = new Salle(x_ini, y_ini, x_fin, y_fin, numSalle, nomSalle, nomAtelier);
            salle.setId(id);
            salles.add(salle);
        }
        this.close();
        return salles;
    }

    @Override
    public int getCountListSalle() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM salle WHERE id IN (SELECT DISTINCT idSalle1 FROM portique UNION SELECT idSalle2 FROM portique)";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }
    
}
