package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import metier.Salle;

public class SalleDataServiceImpl implements SalleDataService{
    
    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;

    SalleDataServiceImpl() {
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

    private Salle createSalle(ResultSet result) throws Exception {
        long id = result.getLong("id");
        float x_ini = result.getInt("x_ini");
        float y_ini = result.getInt("y_ini");
        float x_fin = result.getInt("x_fin");
        float y_fin = result.getInt("y_fin");
        int numSalle = result.getInt("numSalle");
        String nomSalle = result.getString("nomSalle");
        String nomAtelier = result.getString("nomAtelier");
        Salle salle = new Salle(x_ini, y_ini, x_fin, y_fin, numSalle, nomSalle, nomAtelier);
        salle.setId(id);
        return salle;
    }
    
    @Override
    public Salle add(Salle salle) throws Exception {
        cnx = this.sql.connect();
        Salle newSalle = null;
        String query = "INSERT INTO salle (x_ini, y_ini, x_fin, y_fin, numSalle, nomSalle, nomAtelier) VALUES (?, ?, ?, ?, ?, ?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setFloat(1, salle.getX_ini());
        statement.setFloat(2, salle.getY_ini());
        statement.setFloat(3, salle.getX_fin());
        statement.setFloat(4, salle.getY_fin());
        statement.setInt(5, salle.getNumSalle());
        statement.setString(6, salle.getNomSalle());
        statement.setString(7, salle.getNomAtelier());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newSalle = getById(result.getLong(1));
            }
        }
        this.close();
        return newSalle;
    }

    @Override
    public boolean remove(Salle salle) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM attribution WHERE idSalle = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
        statement.executeUpdate();
        query = "DELETE FROM salle WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Salle salle) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE salle SET x_ini = ?, y_ini = ?, x_fin = ?, y_fin = ?, numSalle = ?, nomSalle = ?, nomAtelier = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setFloat(1, salle.getX_ini());
        statement.setFloat(2, salle.getY_ini());
        statement.setFloat(3, salle.getX_fin());
        statement.setFloat(4, salle.getY_fin());
        statement.setInt(5, salle.getNumSalle());
        statement.setString(6, salle.getNomSalle());
        statement.setString(7, salle.getNomAtelier());
        statement.setLong(8, salle.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<Salle> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Salle> salles = new ArrayList<Salle>();
        String query = "SELECT * FROM salle ORDER BY numSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            salles.add(createSalle(result));
        }
        this.close();
        return salles;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM salle";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Salle getById(long id) throws Exception {
        cnx = this.sql.connect();
        Salle salle = null;
        String query = "SELECT * FROM salle WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            salle = createSalle(result);
        }
        this.close();
        return salle;
    }

    @Override
    public List<Salle> getByNomSalle(String nomSalle, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Salle> salles = new ArrayList<Salle>();
        String query = "SELECT * FROM salle WHERE nomSalle = ? ORDER BY numSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomSalle);
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            salles.add(createSalle(result));
        }
        this.close();
        return salles;
    }

    @Override
    public int getCountByNomSalle(String nomSalle) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM salle WHERE nomSalle = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomSalle);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<String> getListNomSalle(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listNomSalle = new ArrayList<String>();
        String query = "SELECT DISTINCT nomSalle FROM salle WHERE nomSalle != '' ORDER BY nomSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNomSalle.add(result.getString("nomSalle"));
        }
        this.close();
        return listNomSalle;
    }

    @Override
    public int getCountListNomSalle() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(DISTINCT nomSalle) FROM salle WHERE nomSalle != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Salle getByNumSalle(int numSalle) throws Exception {
        cnx = this.sql.connect();
        Salle salle = null;
        String query = "SELECT * FROM salle WHERE numSalle = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, numSalle);
        result = statement.executeQuery();
        if (result.next()) {
            salle = createSalle(result);
        }
        this.close();
        return salle;
    }

    @Override
    public List<Integer> getListNumSalle(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Integer> listNumSalle = new ArrayList<Integer>();
        String query = "SELECT numSalle FROM salle ORDER BY numSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNumSalle.add(result.getInt("numSalle"));
        }
        this.close();
        return listNumSalle;
    }

    @Override
    public int getCountListNumSalle() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(numSalle) FROM salle";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Salle> getByNomAtelier(String nomAtelier, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Salle> salles = new ArrayList<Salle>();
        String query = "SELECT * FROM salle WHERE nomAtelier = ? ORDER BY numSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomAtelier);
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            salles.add(createSalle(result));
        }
        this.close();
        return salles;
    }

    @Override
    public int getCountByNomAtelier(String nomAtelier) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM salle WHERE nomAtelier = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomAtelier);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<String> getListNomAtelier(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listNomAtelier = new ArrayList<String>();
        String query = "SELECT DISTINCT nomAtelier FROM salle WHERE nomAtelier != '' ORDER BY nomAtelier ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNomAtelier.add(result.getString("nomAtelier"));
        }
        this.close();
        return listNomAtelier;
    }

    @Override
    public int getCountListNomAtelier() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(DISTINCT nomAtelier) FROM salle WHERE nomAtelier != 0";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    
}
