package il.co.ilrd.jdbc;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import il.co.ilrd.iosystem.CRUD;

public class DataObjectCRUD implements CRUD<String, String> {
    private Connection con = null;
    private String table = "";
    private List<String> pk = new ArrayList<>();
    private List<Integer> indPK = new ArrayList<>();
    private int numberPK = 0;
    private int numOfColumns = 0;
    private String columnsNames = "";

    public DataObjectCRUD(String url, String username, String password, String table)
            throws ClassNotFoundException, SQLException {
        this.table = table;

        Class.forName("com.mysql.cj.jdbc.Driver");
        con = DriverManager.getConnection(url, username, password);

        String qu = "SELECT group_concat(COLUMN_NAME) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'computerStore' AND TABLE_NAME = 'Computer';";
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(qu);
        while (rs.next()) {
            columnsNames = rs.getString(1);
        }
        numOfColumns = columnsNames.split(",").length;
        String[] columnsNamesSplit = columnsNames.split(",");

        /* PK */
        DatabaseMetaData meta = con.getMetaData();
        ResultSet rsMeta = meta.getPrimaryKeys(null, null, table);

        while (rsMeta.next()) {
            int i = 0;
            String temp = rsMeta.getString("COLUMN_NAME");
            pk.add(temp);
            for (i = 0; i < numOfColumns && !columnsNamesSplit[i].equals(temp); ++i) {
            }
            indPK.add(i);
        }
        numberPK = pk.size();

    }

    @Override
    public String create(String data) throws IOException {
        String query = "INSERT INTO " + table + " (" + columnsNames + ") "
                + "VALUES(" + data + ")";

        executeStatement(query);

        String[] splitData = data.split(",");
        String retPK = "";
        for (int i = 0; i < numberPK; ++i) {
            retPK += splitData[indPK.get(i)] + " ";
        }

        return retPK;

    }

    @Override
    public String read(String key) throws IOException {
        String query = "SELECT * FROM " + table + " WHERE " + whereCondition(key) + ";";

        Statement st;
        ResultSet rs;
        String retValue = "";
        try {
            st = con.createStatement();
            rs = st.executeQuery(query);
            while (rs.next()) {
                for (int i = 0; i < numOfColumns; ++i) {
                    retValue += rs.getString(i + 1) + " ";
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return retValue;

    }

    @Override
    public void update(String key, String data) throws IOException {
        String[] columnsNamesSplit = columnsNames.split(",");
        String[] dataSplit = data.split(" ");

        String query = "UPDATE " + table + " SET ";
        for (int i = 0; i < numOfColumns; ++i) {
            query += columnsNamesSplit[i] + "=" + dataSplit[i];
            if (numOfColumns - i > 1) {
                query += ",";
            }
        }
        query += " WHERE " + whereCondition(key) + ";";

        executeStatement(query);

    }

    @Override
    public void delete(String key) throws IOException {
        String query = "DELETE FROM " + table + " WHERE " + whereCondition(key) + ";";
        executeStatement(query);

    }

    @Override
    public void close() throws Exception {
        con.close();

    }

    private void executeStatement(String query) {
        Statement st;

        try {
            st = con.createStatement();
            st.executeUpdate(query);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private String whereCondition(String key) {
        String[] splitKey = key.split(" ");
        String query = "";
        for (int i = 0; i < numberPK; ++i) {
            query += pk.get(i) + "=" + splitKey[i];
            if (numberPK - i > 1) {
                query += " AND ";
            }
        }
        return query;
    }

    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        DataObjectCRUD docrud = new DataObjectCRUD("jdbc:mysql://localhost:3306/computerStore", "root", "", "Computer");

        String newComputer = "10,0,32,300,250,500,0,1,1200";
        try {
            isolationLevel();
            docrud.create(newComputer);
            docrud.read("10 1");
            docrud.update("10 1", "10 1 32 300 250 500 0 1 1200");
            docrud.delete("10 1");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void isolationLevel() throws ClassNotFoundException, SQLException {
        String driverClassName = "com.mysql.cj.jdbc.Driver";
        String url = "jdbc:mysql://localhost:3306/sys";
        String username = "root";
        String password = "";
        String query = "SELECT @@transaction_ISOLATION;";

        Class.forName(driverClassName);
        Connection con = DriverManager.getConnection(url, username, password);
        Statement st = con.createStatement();
        ResultSet rs = st.executeQuery(query);
        while (rs.next()) {
            System.out.println(rs.getString(1));
        }
        con.close();
    }
}
