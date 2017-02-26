package physique;

import java.sql.*;

public abstract class ServiceSQL {
    protected String dbDriver = null;
    protected String dbURL = null;
    
    private Connection cnx;

    protected final String dbHost;
    protected final int dbPort;
    protected final String dbName;
    protected final String dbUser;
    protected final String dbPasswd;

    protected ServiceSQL() {
        this.dbHost = "localhost";
        this.dbPort = 3306;
        this.dbName = "localisationmateriel";
        this.dbUser = "root";
        this.dbPasswd = "cobra";
    }

    public Connection connect() throws Exception {
        Class.forName(dbDriver);
        this.cnx = DriverManager.getConnection(this.dbURL, this.dbUser, this.dbPasswd);
        return this.cnx;
    }
    
    public void close() throws Exception {
        if(!this.cnx.isClosed()){
            this.cnx.close();// Sous java les instructions sont en mode auto-commit
        }
    }
}
