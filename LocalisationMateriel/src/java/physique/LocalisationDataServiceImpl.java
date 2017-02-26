package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import metier.Localisation;
import metier.Materiel;
import metier.MetierFactory;
import metier.Salle;
import metier.Type;
import metier.TypeService;

public class LocalisationDataServiceImpl implements LocalisationDataService{
    
    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;
    private final TypeDataService typeDataSrv;
    private final MaterielDataService materielDataSrv;
    private final SalleDataService salleDataSrv;

    LocalisationDataServiceImpl() {
        typeDataSrv = PhysiqueFactory.getTypeDataService();
        materielDataSrv = PhysiqueFactory.getMaterielDataService();
        salleDataSrv = PhysiqueFactory.getSalleDataService();
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

    private Localisation createLocalisation(ResultSet result) throws Exception {
        long id = result.getLong("id");
        long idMateriel = result.getLong("idMateriel");
        long idSalle = result.getLong("idSalle");
        boolean sortie = result.getBoolean("sortie");
        Materiel materiel = materielDataSrv.getById(idMateriel);
        Salle salle = salleDataSrv.getById(idSalle);
        Localisation localisation = new Localisation(materiel, salle, sortie);
        localisation.setId(id);
        return localisation;
    }
    
    @Override
    public Localisation add(Localisation localisation) throws Exception {
        cnx = this.sql.connect();
        Localisation newLocalisation = null;
        String query = "INSERT INTO localisation (idMateriel, idSalle, sortie) VALUES (?, ?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setLong(1, localisation.getMateriel().getId());
        statement.setLong(2, localisation.getSalle().getId());
        statement.setBoolean(3, localisation.getSortie());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newLocalisation = getById(result.getLong(1));
            }
        }
        this.close();
        return newLocalisation;
    }

    @Override
    public boolean remove(Localisation localisation) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM localisation WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, localisation.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Localisation localisation) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE localisation SET idMateriel = ?, idSalle = ?, sortie = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, localisation.getMateriel().getId());
        statement.setLong(2, localisation.getSalle().getId());
        statement.setBoolean(3, localisation.getSortie());
        statement.setLong(4, localisation.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<Localisation> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Localisation> localisations = new ArrayList<Localisation>();
        String query = "SELECT * FROM localisation ORDER BY id ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            localisations.add(createLocalisation(result));
        }
        this.close();
        return localisations;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM localisation";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Localisation getById(long id) throws Exception {
        cnx = this.sql.connect();
        Localisation localisation = null;
        String query = "SELECT * FROM localisation WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            localisation = createLocalisation(result);
        }
        this.close();
        return localisation;
    }

    @Override
    public List<Localisation> getBySalle(Salle salle, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Localisation> localisations = new ArrayList<Localisation>();
        String query = "SELECT * FROM localisation WHERE idSalle = ? ORDER BY id ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            localisations.add(createLocalisation(result));
        }
        this.close();
        return localisations;
    }

    @Override
    public int getCountBySalle(Salle salle) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM localisation WHERE idSalle = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, salle.getId());
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
        List<Salle> salles = new ArrayList<Salle>();
        String query = "SELECT * FROM salle WHERE id IN (SELECT DISTINCT idSalle FROM localisation) ORDER BY numSalle ASC LIMIT ?,?";
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
        String query = "SELECT COUNT(*) FROM salle WHERE id IN (SELECT DISTINCT idSalle FROM localisation)";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Localisation getByMateriel(Materiel materiel) throws Exception {
        cnx = this.sql.connect();
        Localisation localisation = null;
        String query = "SELECT * FROM localisation WHERE idMateriel = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, materiel.getId());
        result = statement.executeQuery();
        if (result.next()) {
            localisation = createLocalisation(result);
        }
        this.close();
        return localisation;
    }

    @Override
    public List<Materiel> getListMateriel(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Materiel> materiels = new ArrayList<Materiel>();
        String query = "SELECT * FROM materiel WHERE id IN (SELECT idMateriel FROM localisation) ORDER BY nomMateriel ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            long id = result.getLong("id");
            String idBadge = result.getString("idBadge");
            Date dateControle = result.getDate("dateControle");
            Date newDateControle = result.getDate("newDateControle");
            String nomMateriel = result.getString("nomMateriel");
            long idType = result.getLong("idType");
            Type type = typeDataSrv.getById(idType);
            Materiel materiel = new Materiel(idBadge, dateControle, newDateControle, nomMateriel, type);
            materiel.setId(id);
            materiels.add(materiel);
        }
        this.close();
        return materiels;
    }

    @Override
    public int getCountListMateriel() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM materiel WHERE id IN (SELECT idMateriel FROM localisation)";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public List<Localisation> getBySortie(boolean sortie, int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Localisation> localisations = new ArrayList<Localisation>();
        String query = "SELECT * FROM localisation WHERE sortie = ? ORDER BY id ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setBoolean(1, sortie);
        statement.setInt(2, debut);
        statement.setInt(3, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            localisations.add(createLocalisation(result));
        }
        this.close();
        return localisations;
    }

    @Override
    public int getCountBySortie(boolean sortie) throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM localisation WHERE sortie = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setBoolean(1, sortie);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }
    
}
