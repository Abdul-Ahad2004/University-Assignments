package event.model;
public class Slot {
    private int id;
    private Room room;
    private int timeSlot;

    public Slot(int id, String room, int timeSlot) {
        this.id = id;
        this.room = new Room(room);
        this.timeSlot = timeSlot;
    }

    public int getId() {
        return id;
    }

    public int getTimeSlot() {
        return timeSlot;
    }

    public String getRoom() {
        return room.getRoomNumber();
    }
}