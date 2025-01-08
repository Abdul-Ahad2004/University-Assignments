package event.dao;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import event.model.*;

public class SeminarDAO {
    private Connection conn;
    private List<Seminar> seminars = new ArrayList<>();

    public SeminarDAO(Connection con) {

            conn = con;

    }

    public Seminar getSeminarbyTitle(String title)
    {
        for(Seminar seminar:seminars)
        {
            if(seminar.getTitle().equals(title))
                return seminar;
        }
        return null;
    }

    public void insertSeminarsIntoDB() throws SQLException {
        String insertSeminarSQL = "INSERT INTO Seminars (title, speaker) VALUES (?, ?)";
        String insertAttendeeSQL = "INSERT INTO Attendees (seminar_id, attendee_id) VALUES (?, ?)";


        conn.setAutoCommit(false);

        try (PreparedStatement seminarStmt = conn.prepareStatement(insertSeminarSQL, Statement.RETURN_GENERATED_KEYS);
             PreparedStatement attendeeStmt = conn.prepareStatement(insertAttendeeSQL)) {
            for (Seminar seminar : seminars) {
                seminarStmt.setString(1, seminar.getTitle());
                seminarStmt.setString(2, seminar.getSpeaker());
                seminarStmt.executeUpdate();

                try (ResultSet generatedKeys = seminarStmt.getGeneratedKeys()) {
                    if (generatedKeys.next()) {
                        int seminarId = generatedKeys.getInt(1);

                        // Insert each attendee for this seminar
                        for (Integer attendeeId : seminar.getAttendees()) {
                            attendeeStmt.setInt(1, seminarId);
                            attendeeStmt.setInt(2, attendeeId);
                            attendeeStmt.addBatch();
                        }
                        attendeeStmt.executeBatch();
                    }
                }
            }
            conn.commit();
        } catch (SQLException ex) {
            conn.rollback();
            throw ex;
        }

    }

    public int getSeminarId(String title) throws SQLException {
        String selectSeminarSQL = "SELECT id FROM Seminars WHERE title = ?";
        try (PreparedStatement stmt = conn.prepareStatement(selectSeminarSQL)) {
            stmt.setString(1, title);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("id");
                }
            }
        }
        return -1;
    }
    public void loadSeminarsFromDatabase() {
        String selectSeminarsSQL = "SELECT id, title, speaker FROM Seminars";
        String selectAttendeesSQL = "SELECT attendee_id FROM Attendees WHERE seminar_id = ?";

        try (PreparedStatement seminarStmt = conn.prepareStatement(selectSeminarsSQL);
             PreparedStatement attendeeStmt = conn.prepareStatement(selectAttendeesSQL)) {

            seminars.clear();

            try (ResultSet seminarRS = seminarStmt.executeQuery()) {
                while (seminarRS.next()) {
                    int seminarId = seminarRS.getInt("id");
                    String title = seminarRS.getString("title");
                    String speaker = seminarRS.getString("speaker");


                    attendeeStmt.setInt(1, seminarId);
                    List<Integer> attendees = new ArrayList<>();
                    try (ResultSet attendeeRS = attendeeStmt.executeQuery()) {
                        while (attendeeRS.next()) {
                            attendees.add(attendeeRS.getInt("attendee_id"));
                        }
                    }


                    seminars.add(new Seminar(seminarId,title, speaker, attendees));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public void readSeminarFile(File file) throws IOException, SQLException {
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line;int id=1;
        while ((line = br.readLine()) != null) {
            String[] parts = line.split(", ");
            String title = parts[0];
            String speaker = parts[1];
            List<Integer> attendees = new ArrayList<>();
            for (int i = 2; i < parts.length; i++) {
                attendees.add(Integer.parseInt(parts[i]));
            }
            seminars.add(new Seminar(id,title, speaker, attendees));
            id++;
        }
        br.close();
        insertSeminarsIntoDB();
    }

    public Seminar getSeminarByTitle(String title) {
        for (Seminar seminar : seminars) {
            if (seminar.getTitle().equals(title)) {
                return seminar;
            }
        }
        return null;
    }

    public Seminar findOrCreateSeminar(String title, String speaker) {
        for (Seminar seminar : seminars) {
            if (seminar.getTitle().equals(title) && seminar.getSpeaker().equals(speaker)) {
                return seminar;
            }
        }

        Seminar newSeminar = new Seminar(4,title, speaker, new ArrayList<>());
        seminars.add(newSeminar);
        return newSeminar;
    }


    public void updateSeminar(Seminar seminar) {
        String updateSeminarSQL = "UPDATE Seminars SET title = ?, speaker = ? WHERE id = ?";
        String deleteAttendeesSQL = "DELETE FROM Attendees WHERE seminar_id = ?";
        String insertAttendeeSQL = "INSERT INTO Attendees (seminar_id, attendee_id) VALUES (?, ?)";

        try {
            conn.setAutoCommit(false);

            try (PreparedStatement updateSeminarStmt = conn.prepareStatement(updateSeminarSQL);
                 PreparedStatement deleteAttendeesStmt = conn.prepareStatement(deleteAttendeesSQL);
                 PreparedStatement insertAttendeeStmt = conn.prepareStatement(insertAttendeeSQL)) {

                int seminarId = seminar.getId();

                updateSeminarStmt.setString(1, seminar.getTitle());
                updateSeminarStmt.setString(2, seminar.getSpeaker());
                updateSeminarStmt.setInt(3, seminarId);
                updateSeminarStmt.executeUpdate();

                deleteAttendeesStmt.setInt(1, seminarId);
                deleteAttendeesStmt.executeUpdate();

                for (Integer attendee : seminar.getAttendees()) {
                    insertAttendeeStmt.setInt(1, seminarId);
                    insertAttendeeStmt.setInt(2, attendee);
                    insertAttendeeStmt.addBatch();
                }
                insertAttendeeStmt.executeBatch();

                conn.commit();
            } catch (SQLException e) {
                conn.rollback();
                System.err.println("Transaction rolled back due to an error.");
                e.printStackTrace();
            } finally {
                conn.setAutoCommit(true);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }


    public void deleteSeminar(Seminar seminar) throws SQLException {
        String deleteSeminarSQL = "DELETE FROM Seminars WHERE id = ?";
        conn.setAutoCommit(false);
        try (PreparedStatement deleteSeminarStmt = conn.prepareStatement(deleteSeminarSQL)) {


            int seminarId = getSeminarId(seminar);


            deleteSeminarStmt.setInt(1, seminarId);
            deleteSeminarStmt.executeUpdate();
            conn.commit();

        }
        catch (SQLException e) {
            e.printStackTrace();
        }
        finally {
            conn.setAutoCommit(true);
        }
    }

    public void setSeminars(List<Seminar> seminars){
        this.seminars=seminars;
    }


    public int getSeminarId(Seminar seminar) throws SQLException {
        String selectSeminarIdSQL = "SELECT id FROM Seminars WHERE title = ? AND speaker = ?";
        try (PreparedStatement stmt = conn.prepareStatement(selectSeminarIdSQL)) {
            stmt.setString(1, seminar.getTitle());
            stmt.setString(2, seminar.getSpeaker());
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("id");
                } else {
                    throw new SQLException("Seminar not found in the database.");
                }
            }
        }
    }
    public List<Seminar> getSeminars() {
        return seminars;
    }
}
