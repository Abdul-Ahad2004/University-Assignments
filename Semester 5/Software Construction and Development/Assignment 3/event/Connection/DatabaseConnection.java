package event.Connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;


public class DatabaseConnection {
    private static final String URL = "jdbc:sqlserver://DESKTOP-Q3M4KLE;databaseName=EventScheduling;encrypt=true;trustServerCertificate=true";
    private static final String USER = "ahad";
    private static final String PASSWORD = "12345678";


    public static Connection getConnection() throws SQLException {

        return DriverManager.getConnection(URL, USER, PASSWORD);

    }
}