package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import metier.Batiment;
import metier.Salle;

public class BatimentDataServiceImpl implements BatimentDataService {

    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;

    BatimentDataServiceImpl() {
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

    private Batiment createBatiment(ResultSet result) throws Exception {
        Salle salle;
        long id = result.getLong("id");
        String nomBatiment = result.getString("nomBatiment");
        List<Salle> salles = new ArrayList<Salle>();
        String plan = result.getString("plan");
        String query = "SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution WHERE idBatiment = ?) ORDER BY numSalle";
        PreparedStatement statementCreate = this.cnx.prepareStatement(query);
        statementCreate.setLong(1, id);
        ResultSet resultCreate = statementCreate.executeQuery();
        while (resultCreate.next()) {
            long idSalle = resultCreate.getLong("id");
            int x_ini = resultCreate.getInt("x_ini");
            int y_ini = resultCreate.getInt("y_ini");
            int x_fin = resultCreate.getInt("x_fin");
            int y_fin = resultCreate.getInt("y_fin");
            int numSalle = resultCreate.getInt("numSalle");
            String nomSalle = resultCreate.getString("nomSalle");
            String nomAtelier = resultCreate.getString("nomAtelier");
            salle = new Salle(x_ini, y_ini, x_fin, y_fin, numSalle, nomSalle, nomAtelier);
            salle.setId(idSalle);
            salles.add(salle);
        }
        Batiment batiment = new Batiment(nomBatiment, salles, plan);
        batiment.setId(id);
        if(!resultCreate.isClosed()){
            resultCreate.close();
        }
        if(!statementCreate.isClosed()){
            statementCreate.close();
        }
        return batiment;
    }

    @Override
    public Batiment add(Batiment batiment) throws Exception {
        cnx = this.sql.connect();
        Batiment newBatiment = null;
        boolean execute = false;
        long id = 0;
        List<Long> idSallesNonAttribue = new ArrayList<Long>();
        String query = "INSERT INTO batiment (nomBatiment, plan) VALUES (?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setString(1, batiment.getNomBatiment());
        statement.setString(2, batiment.getPlan());
        if (statement.executeUpdate() > 0) {
            execute = true;
            result = statement.getGeneratedKeys();
            if (result.next()) {
                id = result.getLong(1);
            }
        }
        if (execute) {
            query = "SELECT id FROM salle WHERE id NOT IN (SELECT idSalle FROM attribution)";
            statement = this.cnx.prepareStatement(query);
            result = statement.executeQuery();
            while (result.next()) {
                idSallesNonAttribue.add(result.getLong("id"));
            }
            query = "INSERT INTO attribution (idBatiment, idSalle) VALUES (?, ?)";
            statement = this.cnx.prepareStatement(query);
            for (Salle salle : batiment.getSalles()) {
                if (idSallesNonAttribue.contains(salle.getId())) {
                    statement.setLong(1, id);
                    statement.setLong(2, salle.getId());
                    statement.executeUpdate();
                }
            }
        }
        if (id != 0) {
            newBatiment = getById(id);
        }
        this.close();
        return newBatiment;
    }

    @Override
    public boolean remove(Batiment batiment) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM attribution WHERE idBatiment = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, batiment.getId());
        statement.executeUpdate();
        query = "DELETE FROM batiment WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, batiment.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Batiment batiment) throws Exception {
        cnx = this.sql.connect();
        List<Long> idSallesBatiment = new ArrayList<Long>();
        List<Long> idSallesNonAttribue = new ArrayList<Long>();
        boolean execute = false;
        String query = "UPDATE batiment SET nomBatiment = ?, plan = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, batiment.getNomBatiment());
        statement.setString(2, batiment.getPlan());
        statement.setLong(3, batiment.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        if (execute) {
            query = "SELECT idSalle FROM attribution WHERE idBatiment = ?";
            statement = this.cnx.prepareStatement(query);
            statement.setLong(1, batiment.getId());
            result = statement.executeQuery();
            while (result.next()) {
                idSallesBatiment.add(result.getLong("idSalle"));
            }
            query = "SELECT id FROM salle WHERE id NOT IN (SELECT idSalle FROM attribution)";
            statement = this.cnx.prepareStatement(query);
            result = statement.executeQuery();
            while (result.next()) {
                idSallesNonAttribue.add(result.getLong("id"));
            }
            query = "INSERT INTO attribution (idBatiment, idSalle) VALUES (?, ?)";
            statement = this.cnx.prepareStatement(query);
            for (Salle salle : batiment.getSalles()) {
                if (idSallesNonAttribue.contains(salle.getId())) {
                    statement.setLong(1, batiment.getId());
                    statement.setLong(2, salle.getId());
                    statement.executeUpdate();
                } else if (idSallesBatiment.contains(salle.getId())) {
                        idSallesBatiment.remove(salle.getId());
                }
            }
            query = "DELETE FROM attribution WHERE idSalle = ?";
            statement = this.cnx.prepareStatement(query);
            for (long idSalleBatiment : idSallesBatiment) {
                statement.setLong(1, idSalleBatiment);
                statement.executeUpdate();
            }
        }
        this.close();
        return execute;
    }

    @Override
    public List<Batiment> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Batiment> batiments = new ArrayList<Batiment>();
        String query = "SELECT * FROM batiment ORDER BY nomBatiment ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            batiments.add(createBatiment(result));
        }
        this.close();
        return batiments;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM batiment";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Batiment getById(long id) throws Exception {
        cnx = this.sql.connect();
        Batiment batiment = null;
        String query = "SELECT * FROM batiment WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            batiment = createBatiment(result);
        }
        this.close();
        return batiment;
    }

    @Override
    public Batiment getByNomBatiment(String nomBatiment) throws Exception {
        cnx = this.sql.connect();
        Batiment batiment = null;
        String query = "SELECT * FROM batiment WHERE nomBatiment = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomBatiment);
        result = statement.executeQuery();
        if (result.next()) {
            batiment = createBatiment(result);
        }
        this.close();
        return batiment;
    }

    @Override
    public List<String> getListNomBatiment(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listNomBatiment = new ArrayList<String>();
        String query = "SELECT nomBatiment FROM batiment WHERE nomBatiment != '' ORDER BY nomBatiment ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNomBatiment.add(result.getString("nomBatiment"));
        }
        this.close();
        return listNomBatiment;
    }

    @Override
    public int getCountListNomBatiment() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(nomBatiment) FROM batiment WHERE idBadge != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Batiment getBySalle(Salle salle) throws Exception {
        cnx = this.sql.connect();
        Batiment batiment = null;
        String query = "SELECT * FROM batiment WHERE id IN (SELECT idBatiment FROM attribution WHERE idSalle = ?)";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
        result = statement.executeQuery();
        if (result.next()) {
            batiment = createBatiment(result);
        }
        this.close();
        return batiment;
    }

    @Override
    public List<Salle> getListSalle(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Salle> salles = new ArrayList<Salle>();
        String query = "SELECT * FROM salle WHERE id IN (SELECT idSalle FROM attribution) ORDER BY numSalle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            long id = result.getLong("id");
            float x_ini = result.getFloat("x_ini");
            float y_ini = result.getFloat("y_ini");
            float x_fin = result.getFloat("x_fin");
            float y_fin = result.getFloat("y_fin");
            int numSalle = result.getInt("numSalle");
            String nomSalle = result.getString("nomSalle");
            String nomAtelier = result.getString("nomAtelier");
            Salle salle = new Salle(x_ini, y_ini, x_fin, y_fin, numSalle, nomSalle, nomAtelier);
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
        String query = "SELECT COUNT(*) FROM salle WHERE id IN (SELECT idSalle FROM attribution)";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Batiment getByPlan(String plan) throws Exception {
        cnx = this.sql.connect();
        Batiment batiment = null;
        String query = "SELECT * FROM batiment WHERE plan = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, plan);
        result = statement.executeQuery();
        if (result.next()) {
            batiment = createBatiment(result);
        }
        this.close();
        return batiment;
    }

    @Override
    public List<String> getListPlan(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listPlan = new ArrayList<String>();
        String query = "SELECT plan FROM batiment WHERE plan != '' ORDER BY plan ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listPlan.add(result.getString("plan"));
        }
        this.close();
        return listPlan;
    }

    @Override
    public int getCountListPlan() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(plan) FROM batiment WHERE plan != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

}
