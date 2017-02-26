package physique;

public class ServiceSQLImpl extends ServiceSQL {
    ServiceSQLImpl() {
        this.dbDriver = "com.mysql.jdbc.Driver";
        this.dbURL = "jdbc:mysql://" + this.dbHost + ":" + this.dbPort + "/" + this.dbName + "?useUnicode=true&characterEncoding=UTF-8";
    }
}