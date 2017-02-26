package physique;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import metier.Metrologue;

public class MetrologueDataServiceImpl implements MetrologueDataService{

    private final ServiceSQL sql;
    private Connection cnx;
    private PreparedStatement statement;
    private ResultSet result;

    MetrologueDataServiceImpl() {
        sql = new ServiceSQLImpl();
    }

    private Metrologue createMetrologue(ResultSet result) throws Exception {
        long id = result.getLong("id");
        String login = result.getString("login");
        String password = result.getString("password");
        Metrologue metrologue = new Metrologue(login, password);
        metrologue.setId(id);
        return metrologue;
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
    public Metrologue add(Metrologue metrologue) throws Exception {
        cnx = this.sql.connect();
        Metrologue newMetrologue = null;
        String query = "INSERT INTO metrologue (login, password) VALUES (?, ?)";
        statement = this.cnx.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
        statement.setString(1, metrologue.getLogin());
        statement.setString(2, metrologue.getPassword());
        if (statement.executeUpdate() > 0) {
            result = statement.getGeneratedKeys();
            if (result.next()) {
                newMetrologue = getById(result.getLong(1));
            }
        }
        this.close();
        return newMetrologue;
    }

    @Override
    public boolean remove(Metrologue metrologue) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "DELETE FROM metrologue WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, metrologue.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public boolean update(Metrologue metrologue) throws Exception {
        cnx = this.sql.connect();
        boolean execute = false;
        String query = "UPDATE metrologue SET login = ?, password = ? WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, metrologue.getLogin());
        statement.setString(2, metrologue.getPassword());
        statement.setLong(3, metrologue.getId());
        if (statement.executeUpdate() > 0) {
            execute = true;
        }
        this.close();
        return execute;
    }

    @Override
    public List<Metrologue> getAll(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<Metrologue> metrologue = new ArrayList<Metrologue>();
        String query = "SELECT * FROM metrologue ORDER BY login ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            metrologue.add(createMetrologue(result));
        }
        this.close();
        return metrologue;
    }

    @Override
    public int getCount() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(*) FROM metrologue";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

    @Override
    public Metrologue getById(long id) throws Exception {
        cnx = this.sql.connect();
        Metrologue metrologue = null;
        String query = "SELECT * FROM metrologue WHERE id = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setLong(1, id);
        result = statement.executeQuery();
        if (result.next()) {
            metrologue = createMetrologue(result);
        }
        this.close();
        return metrologue;
    }

    @Override
    public Metrologue getByLogin(String login) throws Exception {
        cnx = this.sql.connect();
        Metrologue metrologue = null;
        String query = "SELECT * FROM metrologue WHERE login = ?";
        statement = this.cnx.prepareStatement(query);
        statement.setString(1, login);
        result = statement.executeQuery();
        if (result.next()) {
            metrologue = createMetrologue(result);
        }
        this.close();
        return metrologue;
    }

    @Override
    public List<String> getListLogin(int debut, int parPage) throws Exception {
        cnx = this.sql.connect();
        List<String> listLogin = new ArrayList<String>();
        String query = "SELECT login FROM metrologue WHERE login != '' ORDER BY login ASC LIMIT ?,?";
        statement = this.cnx.prepareStatement(query);
        statement.setInt(1, debut);
        statement.setInt(2, parPage);
        result = statement.executeQuery();
        while (result.next()) {
            listLogin.add(result.getString("login"));
        }
        this.close();
        return listLogin;
    }

    @Override
    public int getCountListLogin() throws Exception {
        cnx = this.sql.connect();
        int count = 0;
        String query = "SELECT COUNT(login) FROM materiel WHERE idBadge != ''";
        statement = this.cnx.prepareStatement(query);
        result = statement.executeQuery();
        if (result.next()) {
            count = result.getInt(1);
        }
        this.close();
        return count;
    }

}
