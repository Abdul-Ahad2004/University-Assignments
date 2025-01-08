package event.dao;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;
import event.service.SchedulerService;
import event.model.*;
public class ScheduleDAO {

    private Connection conn;

    private  SeminarDAO service;
    public Map<Seminar, Slot> schedule = new HashMap<>();

    public ScheduleDAO(Connection co) {

            conn =co;
            service=SchedulerService.getSeminarDAO();

    }

    public void insertSchedulesIntoDB() throws SQLException {
        String insertScheduleSQL = "INSERT INTO Schedule (seminar_id, room, time_slot) VALUES (?, ?, ?)";

        conn.setAutoCommit(false);

        try (PreparedStatement scheduleStmt = conn.prepareStatement(insertScheduleSQL)) {
            for (Map.Entry<Seminar, Slot> entry : schedule.entrySet()) {
                Seminar seminar = entry.getKey();
                Slot slot = entry.getValue();
                // Retrieve seminar_id by looking up seminar in Seminars table
                int seminarId = service.getSeminarId(seminar.getTitle());
                if (seminarId != -1) {
                    scheduleStmt.setInt(1, seminarId);
                    scheduleStmt.setString(2, slot.getRoom());
                    scheduleStmt.setInt(3, slot.getTimeSlot());
                    scheduleStmt.addBatch();
                }
            }
            scheduleStmt.executeBatch();
            conn.commit();

        } catch (SQLException ex) {
            conn.rollback();
            throw ex;
        }

    }


    public void readScheduleFile(File file) throws IOException, SQLException {
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line;
        int id=1;
        while ((line = br.readLine()) != null) {
            String[] parts = line.split(", ");
            String seminarTitle = parts[0];
            String room = parts[1];
            int timeSlot = Integer.parseInt(parts[2]);

            Seminar seminar = service.getSeminarByTitle(seminarTitle);
            if (seminar != null) {

                Slot slot = new Slot(id,room, timeSlot);
                schedule.put(seminar, slot);
            }
            id++;
        }
        br.close();

        insertSchedulesIntoDB();
    }


    public void loadScheduleFromDatabase() {
        String selectScheduleSQL = "SELECT s.id, s.title, s.speaker, sc.room, sc.time_slot " +
                "FROM Seminars s JOIN Schedule sc ON s.id = sc.seminar_id";

        try (PreparedStatement scheduleStmt = conn.prepareStatement(selectScheduleSQL)) {
            schedule.clear();
            int id=1;
            try (ResultSet scheduleRS = scheduleStmt.executeQuery()) {
                while (scheduleRS.next()) {
                    String title = scheduleRS.getString("title");
                    String speaker = scheduleRS.getString("speaker");
                    String room = scheduleRS.getString("room");
                    int timeSlot = scheduleRS.getInt("time_slot");


                    Seminar seminar = service.findOrCreateSeminar(title, speaker);

                    Slot slot = new Slot(id,room, timeSlot);
                    id++;
                    schedule.put(seminar, slot);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }




    public void updateSchedule(Slot slot, Seminar seminar) throws SQLException {
        String updateScheduleSQL = "UPDATE Schedule SET room = ?, time_slot = ? WHERE seminar_id = ?";
        try {
            conn.setAutoCommit(false);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        try (PreparedStatement updateScheduleStmt = conn.prepareStatement(updateScheduleSQL)) {


            int seminarId = service.getSeminarId(seminar);

            // Update room and time slot
            updateScheduleStmt.setString(1, slot.getRoom());
            updateScheduleStmt.setInt(2, slot.getTimeSlot());
            updateScheduleStmt.setInt(3, seminarId);
            updateScheduleStmt.executeUpdate();
            conn.commit();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        finally {
            conn.setAutoCommit(true);
        }
    }


    public void setSchedule(Map<Seminar, Slot> schedule){
        this.schedule=schedule;
    }

    public void deleteSchedule(Seminar seminar) throws SQLException {
        String deleteScheduleSQL = "DELETE FROM Schedule WHERE seminar_id = ?";
        conn.setAutoCommit(false);
        try (PreparedStatement deleteScheduleStmt = conn.prepareStatement(deleteScheduleSQL)) {


            int seminarId = service.getSeminarId(seminar);

            deleteScheduleStmt.setInt(1, seminarId);
            deleteScheduleStmt.executeUpdate();
            conn.commit();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        finally {
            conn.setAutoCommit(true);
        }
    }

    public Map<Seminar, Slot> getSchedule() {
        return schedule;
    }


}
