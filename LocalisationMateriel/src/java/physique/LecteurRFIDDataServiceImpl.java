package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import metier.LecteurRFID;

public class LecteurRFIDDataServiceImpl implements LecteurRFIDDataService{
    
    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;

    LecteurRFIDDataServiceImpl() {
        sql = new ServiceSQLImpl();
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

    private LecteurRFID createLecteurRFID(ResultSet result) throws Exception {
        long id = result.getLong("id");
        String ip = result.getString("ip");
        String modele = result.getString("modele");
        boolean etatOn = result.getBoolean("etatOn");
        LecteurRFID lecteur = new LecteurRFID(ip, modele, etatOn);
        lecteur.setId(id);
        return lecteur;
    }

    @Override
    public LecteurRFID add(LecteurRFID lecteur) throws Exception {
        cnx = this.sql.connect();
        LecteurRFID newLecteur = null;
        String query = "INSERT INTO lecteur (ip, modele, etatOn) VALUES (?, ?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setString(1, lecteur.getIp());
        statement.setString(2, lecteur.getModele());
        statement.setBoolean(3, lecteur.getEtatOn());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newLecteur = getById(result.getLong(1));
            }
        }
        this.close();
        return newLecteur;
    }

    @Override
    public boolean remove(LecteurRFID lecteur) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM lecteur WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, lecteur.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(LecteurRFID lecteur) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE lecteur SET ip = ?, modele = ?, etatOn = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, lecteur.getIp());
        statement.setString(2, lecteur.getModele());
        statement.setBoolean(3, lecteur.getEtatOn());
        statement.setLong(4, lecteur.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<LecteurRFID> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<LecteurRFID> lecteurs = new ArrayList<LecteurRFID>();
        String query = "SELECT * FROM lecteur ORDER BY ip ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            lecteurs.add(createLecteurRFID(result));
        }
        this.close();
        return lecteurs;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM lecteur";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public LecteurRFID getById(long id) throws Exception {
        cnx = this.sql.connect();
        LecteurRFID lecteur = null;
        String query = "SELECT * FROM lecteur WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            lecteur = createLecteurRFID(result);
        }
        this.close();
        return lecteur;
    }

    @Override
    public LecteurRFID getByIp(String ip) throws Exception {
        cnx = this.sql.connect();
        LecteurRFID lecteur = null;
        String query = "SELECT * FROM lecteur WHERE ip = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, ip);
        result = statement.executeQuery();
        if (result.next()) {
            lecteur = createLecteurRFID(result);
        }
        this.close();
        return lecteur;
    }

    @Override
    public List<String> getListIp(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listIp = new ArrayList<String>();
        String query = "SELECT ip FROM lecteur WHERE ip != '' ORDER BY ip ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listIp.add(result.getString("ip"));
        }
        this.close();
        return listIp;
    }

    @Override
    public int getCountListIp() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(ip) FROM lecteur WHERE ip != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<LecteurRFID> getByModele(String modele, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<LecteurRFID> lecteurs = new ArrayList<LecteurRFID>();
        String query = "SELECT * FROM lecteur WHERE modele = ? ORDER BY ip ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, modele);
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            lecteurs.add(createLecteurRFID(result));
        }
        this.close();
        return lecteurs;
    }

    @Override
    public int getCountByModele(String modele) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM lecteur WHERE nomMateriel = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, modele);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<String> getListModele(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listModele = new ArrayList<String>();
        String query = "SELECT DISTINCT modele FROM lecteur WHERE modele != '' ORDER BY modele ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listModele.add(result.getString("modele"));
        }
        this.close();
        return listModele;
    }

    @Override
    public int getCountListModele() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(DISTINCT modele) FROM lecteur WHERE modele != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<LecteurRFID> getByEtatOn(boolean etatOn, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<LecteurRFID> lecteurs = new ArrayList<LecteurRFID>();
        String query = "SELECT * FROM lecteur WHERE etatOn = ? ORDER BY ip ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setBoolean(1, etatOn);
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            lecteurs.add(createLecteurRFID(result));
        }
        this.close();
        return lecteurs;
    }

    @Override
    public int getCountByEtatOn(boolean etatOn) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM lecteur WHERE etatOn = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setBoolean(1, etatOn);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }
    
}
