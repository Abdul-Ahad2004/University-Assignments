package event.service;
import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import event.Connection.DatabaseConnection;
import event.dao.*;
import event.model.*;

public class SchedulerService {

    public static SeminarDAO seminardao;

    public ScheduleDAO scheduledao;
    public Connection conn;
    public SchedulerService() {
        try {
            conn = DatabaseConnection.getConnection();
            seminardao= new SeminarDAO(conn);
            scheduledao = new ScheduleDAO(conn);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public Seminar getSeminarbyTitle(String title){
        return seminardao.getSeminarbyTitle(title);
    }
    public void insertSeminarsIntoDB() throws SQLException {
        seminardao.insertSeminarsIntoDB();
    }

    public static SeminarDAO getSeminarDAO(){
        return seminardao;
    }

    public int getSeminarId(String title) throws SQLException{
        return seminardao.getSeminarId(title);
    }

    public void loadSeminarsFromDatabase(){
        seminardao.loadSeminarsFromDatabase();
    }

    public void readSeminarFile(File file) throws IOException, SQLException{
        seminardao.readSeminarFile(file);
    }

    public Seminar getSeminarByTitle(String title){
        return  seminardao.getSeminarByTitle(title);
    }

    public Seminar findOrCreateSeminar(String title, String speaker){
        return seminardao.findOrCreateSeminar(title,speaker);
    }

    public void updateSeminar(Seminar seminar){
        seminardao.updateSeminar(seminar);
    }

    public void deleteSeminar(Seminar seminar) throws SQLException{
        seminardao.deleteSeminar(seminar);
    }

    public int getSeminarId(Seminar seminar) throws SQLException{
        return seminardao.getSeminarId(seminar);
    }

    public List<Seminar> getSeminars(){
        return seminardao.getSeminars();
    }

    public void insertSchedulesIntoDB() throws SQLException{
        scheduledao.insertSchedulesIntoDB();
    }

    public void readScheduleFile(File file) throws IOException, SQLException{
        scheduledao.readScheduleFile(file);
    }

    public void loadScheduleFromDatabase(){
        scheduledao.loadScheduleFromDatabase();
    }

    public void updateSchedule(Slot slot, Seminar seminar) throws SQLException{
        scheduledao.updateSchedule(slot,seminar);
    }

    public void deleteSchedule(Seminar seminar) throws SQLException{
        scheduledao.deleteSchedule(seminar);
    }

    public Map<Seminar, Slot> getSchedule(){
        return scheduledao.getSchedule();
    }

    public Map<Integer, List<Seminar>> findOverlappingAttendees() {
        Map<Integer, List<Seminar>> overlappingAttendeesMap = new HashMap<>();
        for (Seminar seminar1 : seminardao.getSeminars()) {
            for (Seminar seminar2 : seminardao.getSeminars()) {
                if (!seminar1.equals(seminar2)) {
                    List<Integer> overlappingAttendees = seminar1.getOverlappingAttendees(seminar2);
                    for (Integer attendee : overlappingAttendees) {
                        overlappingAttendeesMap.putIfAbsent(attendee, new ArrayList<>());
                        overlappingAttendeesMap.get(attendee).add(seminar1);
                    }
                }
            }
        }
        return overlappingAttendeesMap;
    }

    public List<Slot> findConflictingTimeSlots() {
        List<Slot> conflictingSlots = new ArrayList<>();
        for (Map.Entry<Seminar, Slot> entry1 : scheduledao.getSchedule().entrySet()) {
            for (Map.Entry<Seminar, Slot> entry2 : scheduledao.getSchedule().entrySet()) {
                if (!entry1.getKey().equals(entry2.getKey()) &&
                        entry1.getValue().getRoom().equals(entry2.getValue().getRoom()) &&
                        entry1.getValue().getTimeSlot() == entry2.getValue().getTimeSlot()) {
                    conflictingSlots.add(entry1.getValue());
                }
            }
        }
        return conflictingSlots;
    }
}
