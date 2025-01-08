package event.service;

import event.model.Seminar;
import event.model.Slot;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.util.*;


public class SchedulerServiceTest {
    private SchedulerService schedulerService;
    private Seminar seminar1;
    private Seminar seminar2;
    private Seminar seminar3;
    private Slot slot1;
    private Slot slot2;
    private Slot slot3;

    @BeforeEach
    public void setUp() {
        schedulerService = new SchedulerService();

        // Mock seminars with attendees
        seminar1 = new Seminar(1,"Seminar 1", "Speaker A", Arrays.asList(1, 2, 3));
        seminar2 = new Seminar(2,"Seminar 2", "Speaker B", Arrays.asList(3, 4, 5));
        seminar3 = new Seminar(3,"Seminar 3", "Speaker C", Arrays.asList(5, 6, 7));

        List<Seminar> seminars = new ArrayList<>(Arrays.asList(seminar1, seminar2, seminar3));
        schedulerService.getSeminarDAO().setSeminars(seminars);

        slot1 = new Slot(1,"Room 101", 9);
        slot2 = new Slot(2,"Room 101", 9);
        slot3 = new Slot(3,"Room 102", 10);


        Map<Seminar, Slot> schedule = new HashMap<>();
        schedule.put(seminar1, slot1);
        schedule.put(seminar2, slot2);
        schedule.put(seminar3, slot3);
        schedulerService.scheduledao.setSchedule(schedule);
    }

    @Test
    public void testFindOverlappingAttendees() {
        Map<Integer, List<Seminar>> overlappingAttendees = schedulerService.findOverlappingAttendees();

        assertTrue(overlappingAttendees.containsKey(3));
        assertTrue(overlappingAttendees.containsKey(5));

        List<Seminar> seminarsWithAttendee3 = overlappingAttendees.get(3);
        assertTrue(seminarsWithAttendee3.contains(seminar1));
        assertTrue(seminarsWithAttendee3.contains(seminar2));

        List<Seminar> seminarsWithAttendee5 = overlappingAttendees.get(5);
        assertTrue(seminarsWithAttendee5.contains(seminar2));
        assertTrue(seminarsWithAttendee5.contains(seminar3));
    }

    @Test
    public void testFindConflictingTimeSlots() {
        List<Slot> conflictingSlots = schedulerService.findConflictingTimeSlots();

        assertTrue(conflictingSlots.contains(slot1));
        assertTrue(conflictingSlots.contains(slot2));

        assertFalse(conflictingSlots.contains(slot3));
    }
}
