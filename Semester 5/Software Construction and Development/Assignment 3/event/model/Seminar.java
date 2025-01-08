package event.model;
import java.util.ArrayList;
import java.util.List;

public class Seminar {
    public int id;
    public String title;
    public String speaker;
    public List<Integer> attendees;

    public Seminar(int id, String title, String speaker, List<Integer> attendees) {
        this.id = id;
        this.title = title;
        this.speaker = speaker;
        this.attendees = attendees;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getSpeaker() {
        return speaker;
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



    public List<Integer> getOverlappingAttendees(Seminar otherSeminar) {
        List<Integer> overlapping = new ArrayList<>();
        for (Integer attendee : attendees) {
            if (otherSeminar.getAttendees().contains(attendee)) {
                overlapping.add(attendee);
            }
        }
        return overlapping;
    }

    @Override
    public String toString() {
        return "Seminar: " + title + ", Speaker: " + speaker + ", Attendees: " + attendees;
    }
}