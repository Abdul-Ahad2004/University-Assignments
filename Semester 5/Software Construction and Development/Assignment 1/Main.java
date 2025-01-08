import java.util.List;
import java.io.*;
import java.util.*;

class Seminar {
    private String title;
    private String speaker;
    private List<Integer> attendees;

    public Seminar(String title, String speaker, List<Integer> attendees) {
        this.title = title;
        this.speaker = speaker;
        this.attendees = attendees;
    }

    public String getTitle() {
        return title;
    }

    public List<Integer> getAttendees() {
        return attendees;
    }

    public boolean hasOverlap(Seminar otherSeminar) {
        for (Integer attendee : attendees) {
            if (otherSeminar.getAttendees().contains(attendee)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public String toString() {
        return "Seminar: " + title + ", Speaker: " + speaker + ", Attendees: " + attendees;
    }
}

class Slot {
    private Room room;
    private int timeSlot;

    public Slot(String room, int timeSlot) {
        this.room = new Room(room);
        this.timeSlot = timeSlot;
    }

    public int getTimeSlot() {
        return timeSlot;
    }

    public String getRoom() {
        return room.getRoomNumber();
    }
}

class Room {
    private String roomNumber;

    public Room(String roomNumber) {
        this.roomNumber = roomNumber;
    }

    public String getRoomNumber() {
        return roomNumber;
    }
}

class Scheduler {
    private List<Seminar> seminars = new ArrayList<>();
    private Map<Seminar, Slot> schedule = new HashMap<>();

    public void readSeminarFile(String filename) throws FileNotFoundException, IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String line;
        while ((line = br.readLine()) != null) {
            String[] parts = line.split(", ");
            String title = parts[0];
            String speaker = parts[1];
            List<Integer> attendees = new ArrayList<>();
            for (int i = 2; i < parts.length; i++) {
                attendees.add(Integer.parseInt(parts[i]));
            }
            Seminar seminar = new Seminar(title, speaker, attendees);
            seminars.add(seminar);
        }
        br.close();
    }

    public void readScheduleFile(String filename) throws FileNotFoundException, IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String line;
        while ((line = br.readLine()) != null) {
            String[] parts = line.split(", ");
            String seminarTitle = parts[0];
            String room = parts[1];
            int timeSlot = Integer.parseInt(parts[2]);

            Seminar seminar = getSeminarByTitle(seminarTitle);
            if (seminar != null) {
                Slot slot = new Slot(room, timeSlot);
                schedule.put(seminar, slot);
            }
        }
        br.close();
    }

    public List<Seminar> findOverlappingSeminars(Seminar targetSeminar) {
        List<Seminar> overlappingSeminars = new ArrayList<>();
        Slot targetSlot = schedule.get(targetSeminar);

        for (Seminar seminar : seminars) {
            if (!seminar.equals(targetSeminar)) {
                Slot seminarSlot = schedule.get(seminar);
                if (seminarSlot.getTimeSlot() == targetSlot.getTimeSlot() && seminar.hasOverlap(targetSeminar)) {
                    overlappingSeminars.add(seminar);
                }
            }
        }
        return overlappingSeminars;
    }

    public List<Seminar> findConflictingSeminars(Seminar seminar) {
        List<Seminar> conflictingSeminars = new ArrayList<>();
        Slot seminarSlot = schedule.get(seminar);
        for (Seminar scheduledSeminar : schedule.keySet()) {
            if (!scheduledSeminar.equals(seminar)) {
                Slot otherSlot = schedule.get(scheduledSeminar);
                if (seminarSlot.getTimeSlot() == otherSlot.getTimeSlot()
                        && seminarSlot.getRoom().equals(otherSlot.getRoom())) {
                    conflictingSeminars.add(scheduledSeminar);
                }
            }
        }
        return conflictingSeminars;
    }

    public Seminar getSeminarByTitle(String title) {
        for (Seminar seminar : seminars) {
            if (seminar.getTitle().equals(title)) {
                return seminar;
            }
        }
        return null;
    }
}

public class Main {
    public static void main(String[] args) {
        Scheduler scheduler = new Scheduler();

        try {
            scheduler.readSeminarFile("seminars.txt");
            scheduler.readScheduleFile("schedule.txt");

            Seminar targetSeminar = scheduler.getSeminarByTitle("Model Driven Development");

            List<Seminar> overlaps = scheduler.findOverlappingSeminars(targetSeminar);
            System.out.println("Seminars with overlapping attendees in the same time slot:\n");
            if (overlaps.size() > 0) {
                for (Seminar seminar : overlaps) {
                    System.out.println(seminar);
                }
            } else {
                System.out.println(
                        "\nThe given seminar has no overlapping attendees with other seminars in the same slot!!");
            }

            List<Seminar> conflicts = scheduler.findConflictingSeminars(targetSeminar);
            System.out.println("\nConflicting seminars in the given time slot:");
            if (conflicts.size() > 0) {
                for (Seminar seminar : conflicts) {
                    System.out.println(seminar);
                }
            } else {
                System.out.println("\nThe given seminar has no conflicts with other seminars!!");
            }

        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("IO error occurred: " + e.getMessage());
        }
    }
}
