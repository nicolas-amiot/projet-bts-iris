package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import metier.Materiel;
import metier.Type;

public class MaterielDataServiceImpl implements MaterielDataService {

    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;
    private final TypeDataService typeDataSrv;

    MaterielDataServiceImpl() {
        typeDataSrv = PhysiqueFactory.getTypeDataService();
        sql = new ServiceSQLImpl();
    }
    
    private void close() throws SQLException, Exception{ // Permet de fermer toutes les connexions requisent pour effectuer une requêtre à la bdd
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

    private Materiel createMateriel(ResultSet result) throws Exception { // Permet de créer les matériels pour les méthodes getAll / getBy
        long id = result.getLong("id");
        String idBadge = result.getString("idBadge");
        Date dateControle = result.getDate("dateControle");
        Date newDateControle = result.getDate("newDateControle");
        String nomMateriel = result.getString("nomMateriel");
        long idType = result.getLong("idType");
        Type type = typeDataSrv.getById(idType);
        Materiel materiel = new Materiel(idBadge, dateControle, newDateControle, nomMateriel, type);
        materiel.setId(id);
        return materiel;
    }

    @Override
    public Materiel add(Materiel materiel) throws Exception {
        cnx = this.sql.connect();
        Materiel newMateriel = null;
        String query = "INSERT INTO materiel (idBadge, dateControle, newDateControle, nomMateriel, idType) VALUES (?, ?, ?, ?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setString(1, materiel.getIdBadge());
        statement.setDate(2, new java.sql.Date(materiel.getDateControle().getTime()));
        statement.setDate(2, new java.sql.Date(materiel.getNewDateControle().getTime()));
        statement.setString(4, materiel.getNomMateriel());
        statement.setLong(5, materiel.getType().getId());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newMateriel = getById(result.getLong(1));
            }
        }
        this.close();
        return newMateriel;
    }

    @Override
    public boolean remove(Materiel materiel) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM materiel WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, materiel.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Materiel materiel) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE materiel SET idBadge = ?, dateControle = ?, newDateControle = ?, nomMateriel = ?, idType = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, materiel.getIdBadge());
        statement.setDate(2, new java.sql.Date(materiel.getDateControle().getTime()));
        statement.setDate(3, new java.sql.Date(materiel.getNewDateControle().getTime()));
        statement.setString(4, materiel.getNomMateriel());
        statement.setLong(5, materiel.getType().getId());
        statement.setLong(6, materiel.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<Materiel> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String query = "SELECT * FROM materiel ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            materiels.add(createMateriel(result));
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM materiel";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Materiel getById(long id) throws Exception {
        cnx = this.sql.connect();
        Materiel materiel = null;
        String query = "SELECT * FROM materiel WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            materiel = createMateriel(result);
        }
        this.close();
        return materiel;
    }

    @Override
    public Materiel getByIdBadge(String idBadge) throws Exception {
        cnx = this.sql.connect();
        Materiel materiel = null;
        String query = "SELECT * FROM materiel WHERE idBadge = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, idBadge);
        result = statement.executeQuery();
        if (result.next()) {
            materiel = createMateriel(result);
        }
        this.close();
        return materiel;
    }

    @Override
    public List<String> getListIdBadge(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listIdBadge = new ArrayList<String>();
        String query = "SELECT idBadge FROM materiel WHERE idBadge != '' ORDER BY idBadge ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listIdBadge.add(result.getString("idBadge"));
        }
        this.close();
        return listIdBadge;
    }

    @Override
    public int getCountListIdBadge() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(idBadge) FROM materiel WHERE idBadge != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Materiel> getByDateControle(Date dateControle, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String query = "SELECT * FROM materiel WHERE dateControle = ? ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setDate(1, new java.sql.Date(dateControle.getTime()));
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            materiels.add(createMateriel(result));
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCountByDateControle(Date dateControle) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM materiel WHERE dateControle = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setDate(1, new java.sql.Date(dateControle.getTime()));
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Date> getListDateControle(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Date> listDateControle = new ArrayList<Date>();
        String query = "SELECT DISTINCT dateControle FROM materiel WHERE dateControle != 0 ORDER BY dateControle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listDateControle.add(result.getDate("dateControle"));
        }
        this.close();
        return listDateControle;
    }

    @Override
    public int getCountListDateControle() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(DISTINCT dateControle) FROM materiel WHERE dateControle != 0";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }
    
    @Override
    public List<Materiel> getByNewDateControle(Date newDateControle, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String query = "SELECT * FROM materiel WHERE newDateControle = ? ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setDate(1, new java.sql.Date(newDateControle.getTime()));
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            materiels.add(createMateriel(result));
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCountByNewDateControle(Date newDateControle) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM materiel WHERE newDateControle = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setDate(1, new java.sql.Date(newDateControle.getTime()));
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Date> getListNewDateControle(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Date> listNewDateControle = new ArrayList<Date>();
        String query = "SELECT DISTINCT newDateControle FROM materiel WHERE newDateControle != 0 ORDER BY newDateControle ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNewDateControle.add(result.getDate("newDateControle"));
        }
        this.close();
        return listNewDateControle;
    }

    @Override
    public int getCountListNewDateControle() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(DISTINCT newDateControle) FROM materiel WHERE newDateControle != 0";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Materiel> getByPeriode(Date date, boolean avant, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String operateur;
        if (avant) {
            operateur = "<=";
        } else {
            operateur = ">=";
        }
        String query = "SELECT * FROM materiel WHERE newDateControle "+ operateur +" ? ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setDate(1, new java.sql.Date(date.getTime()));
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            materiels.add(createMateriel(result));
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCountByPeriode(Date date, boolean avant) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String operateur;
        if (avant) {
            operateur = "<=";
        } else {
            operateur = ">=";
        }
        String query = "SELECT COUNT(*) FROM materiel WHERE newDateControle "+ operateur +" ?";
        statement = this.cnx.prepareStatement(query);
        statement.setDate(1, new java.sql.Date(date.getTime()));
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Materiel> getByType(Type type, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String query = "SELECT * FROM materiel WHERE idType = ? ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, type.getId());
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            materiels.add(createMateriel(result));
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCountByType(Type type) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM materiel WHERE idType = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, type.getId());
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Type> getListType(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Type> types = new ArrayList<Type>();
        String query = "SELECT * FROM type WHERE id IN (SELECT DISTINCT idType FROM materiel) ORDER BY nomType ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            long id = result.getLong("id");
            String nomType = result.getString("nomType");
            String nomImage = result.getString("nomImage");
            Type type = new Type(nomType, nomImage);
            type.setId(id);
            types.add(type);
        }
        this.close();
        return types;
    }

    @Override
    public int getCountListType() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM type WHERE id IN (SELECT DISTINCT idType FROM materiel)";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Materiel> getByNomMateriel(String nomMateriel, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String query = "SELECT * FROM materiel WHERE nomMateriel = ? ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomMateriel);
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            materiels.add(createMateriel(result));
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCountByNomMateriel(String nomMateriel) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM materiel WHERE nomMateriel = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomMateriel);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<String> getListNomMateriel(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listNomMateriel = new ArrayList<String>();
        String query = "SELECT DISTINCT nomMateriel FROM materiel WHERE nomMateriel != '' ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNomMateriel.add(result.getString("nomMateriel"));
        }
        this.close();
        return listNomMateriel;
    }

    @Override
    public int getCountListNomMateriel() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(DISTINCT nomMateriel) FROM materiel WHERE nomMateriel != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

}
