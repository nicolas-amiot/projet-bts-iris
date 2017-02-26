package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import metier.Type;

public class TypeDataServiceImpl implements TypeDataService {

    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;

    TypeDataServiceImpl() {
        sql = new ServiceSQLImpl();
    }

    private Type createType(ResultSet result) throws Exception {
        long id = result.getLong("id");
        String nomType = result.getString("nomType");
        String nomImage = result.getString("nomImage");
        Type type = new Type(nomType, nomImage);
        type.setId(id);
        return type;
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

    @Override
    public Type add(Type type) throws Exception {
        cnx = this.sql.connect();
        Type newType = null;
        String query = "INSERT INTO type (nomType, nomImage) VALUES (?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setString(1, type.getNomType());
        statement.setString(2, type.getNomImage());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newType = getById(result.getLong(1));
            }
        }
        this.close();
        return newType;
    }

    @Override
    public boolean remove(Type type) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM type WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, type.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Type type) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE type SET nomType = ?, nomImage = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, type.getNomType());
        statement.setString(2, type.getNomImage());
        statement.setLong(3, type.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<Type> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Type> types = new ArrayList<Type>();
        String query = "SELECT * FROM type ORDER BY nomType ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            types.add(createType(result));
        }
        this.close();
        return types;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM type";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Type getById(long id) throws Exception {
        cnx = this.sql.connect();
        Type type = null;
        String query = "SELECT * FROM type WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            type = createType(result);
        }
        this.close();
        return type;
    }

    @Override
    public Type getByNomType(String nomType) throws Exception {
        cnx = this.sql.connect();
        Type type = null;
        String query = "SELECT * FROM type WHERE nomType = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomType);
        result = statement.executeQuery();
        if (result.next()) {
            type = createType(result);
        }
        this.close();
        return type;
    }

    @Override
    public List<String> getListNomType(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listNomType = new ArrayList<String>();
        String query = "SELECT nomType FROM type WHERE nomType != '' ORDER BY nomType ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNomType.add(result.getString("nomType"));
        }
        this.close();
        return listNomType;
    }

    @Override
    public int getCountListNomType() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(nomType) FROM type WHERE nomType != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Type getByNomImage(String nomImage) throws Exception {
        cnx = this.sql.connect();
        Type type = null;
        String query = "SELECT * FROM type WHERE nomImage = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, nomImage);
        result = statement.executeQuery();
        if (result.next()) {
            type = createType(result);
        }
        this.close();
        return type;
    }

    @Override
    public List<String> getListNomImage(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listNomImage = new ArrayList<String>();
        String query = "SELECT nomImage FROM type WHERE nomImage != '' ORDER BY nomImage ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listNomImage.add(result.getString("nomImage"));
        }
        this.close();
        return listNomImage;
    }

    @Override
    public int getCountListNomImage() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(nomImage) FROM type WHERE nomImage != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

}
