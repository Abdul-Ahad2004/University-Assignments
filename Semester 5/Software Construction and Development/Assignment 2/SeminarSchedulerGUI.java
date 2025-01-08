import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.io.*;
import java.util.*;
import java.util.List;

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

    public void readSeminarFile(File file) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line;
        while ((line = br.readLine()) != null) {
            String[] parts = line.split(", ");
            String title = parts[0];
            String speaker = parts[1];
            List<Integer> attendees = new ArrayList<>();
            for (int i = 2; i < parts.length; i++) {
                attendees.add(Integer.parseInt(parts[i]));
            }
            seminars.add(new Seminar(title, speaker, attendees));
        }
        br.close();
    }

    public void readScheduleFile(File file) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(file));
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

    public List<Seminar> getSeminars() {
        return seminars;
    }

    public Map<Seminar, Slot> getSchedule() {
        return schedule;
    }

    public Seminar getSeminarByTitle(String title) {
        for (Seminar seminar : seminars) {
            if (seminar.getTitle().equals(title)) {
                return seminar;
            }
        }
        return null;
    }

    public Map<Integer, List<Seminar>> findOverlappingAttendees() {
        Map<Integer, List<Seminar>> overlappingAttendeesMap = new HashMap<>();
        for (Seminar seminar1 : seminars) {
            for (Seminar seminar2 : seminars) {
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
        for (Map.Entry<Seminar, Slot> entry1 : schedule.entrySet()) {
            for (Map.Entry<Seminar, Slot> entry2 : schedule.entrySet()) {
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

public class SeminarSchedulerGUI extends JFrame {
    private Scheduler scheduler = new Scheduler();
    private JTable seminarTable;
    private JTable scheduleTable;
    private DefaultTableModel seminarTableModel;
    private DefaultTableModel scheduleTableModel;
    private JTable conflictTable;
    private DefaultTableModel conflictTableModel;
    private JComboBox<String> conflictOptions;
    private Map<Integer, List<Seminar>> overlappingAttendeesMap = new HashMap<>();
    private List<Slot> conflictingSlots = new ArrayList<>();

    public SeminarSchedulerGUI() {
        setTitle("Seminar Scheduler");
        setSize(600, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JTabbedPane tabbedPane = new JTabbedPane();

        JPanel seminarPanel = new JPanel(new BorderLayout());
        JButton uploadSeminarButton = new JButton("Upload Seminars");
        seminarPanel.add(uploadSeminarButton, BorderLayout.NORTH);

        seminarTableModel = new DefaultTableModel(new String[]{"Title", "Speaker", "Attendees"}, 0);
        seminarTable = new JTable(seminarTableModel);
        JScrollPane seminarScrollPane = new JScrollPane(seminarTable);
        seminarPanel.add(seminarScrollPane, BorderLayout.CENTER);

        uploadSeminarButton.addActionListener(e -> uploadSeminars());

        tabbedPane.add("Seminar Information", seminarPanel);

        JPanel schedulePanel = new JPanel(new BorderLayout());
        JButton uploadScheduleButton = new JButton("Upload Schedule");
        schedulePanel.add(uploadScheduleButton, BorderLayout.NORTH);

        scheduleTableModel = new DefaultTableModel(new String[]{"Seminar", "Room", "Time-slot"}, 0);
        scheduleTable = new JTable(scheduleTableModel);
        JScrollPane scheduleScrollPane = new JScrollPane(scheduleTable);
        schedulePanel.add(scheduleScrollPane, BorderLayout.CENTER);

        uploadScheduleButton.addActionListener(e -> uploadSchedule());

        tabbedPane.add("Scheduling Information", schedulePanel);

        
        JPanel analysisPanel = new JPanel(new BorderLayout());
        JPanel controlPanel = new JPanel();
        conflictOptions = new JComboBox<>(new String[]{"Overlapping Attendees", "Time Conflicts"});
        JButton analyzeButton = new JButton("Analyze Conflicts");
        controlPanel.add(conflictOptions);
        controlPanel.add(analyzeButton);
        analysisPanel.add(controlPanel, BorderLayout.NORTH);

        conflictTableModel = new DefaultTableModel(new String[]{"Seminar", "Speaker/Room", "Attendees/Time-slot"}, 0);
        conflictTable = new JTable(conflictTableModel);
        conflictTable.setDefaultRenderer(Object.class, new ConflictCellRenderer());
        JScrollPane conflictScrollPane = new JScrollPane(conflictTable);
        analysisPanel.add(conflictScrollPane, BorderLayout.CENTER);

        analyzeButton.addActionListener(e -> analyzeConflicts());

        tabbedPane.add("Conflict Analysis", analysisPanel);

        add(tabbedPane, BorderLayout.CENTER);
    }

    private void uploadSeminars() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                scheduler.readSeminarFile(file);
                updateSeminarTable();
            } catch (IOException e) {
                JOptionPane.showMessageDialog(this, "Error reading seminar file: " + e.getMessage());
            }
        }
    }

    private void uploadSchedule() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                scheduler.readScheduleFile(file);
                updateScheduleTable();
            } catch (IOException e) {
                JOptionPane.showMessageDialog(this, "Error reading schedule file: " + e.getMessage());
            }
        }
    }

    private void updateSeminarTable() {
        seminarTableModel.setRowCount(0);
        for (Seminar seminar : scheduler.getSeminars()) {
            seminarTableModel.addRow(new Object[]{seminar.getTitle(), seminar.getSpeaker(), seminar.getAttendees()});
        }
    }

    private void updateScheduleTable() {
        scheduleTableModel.setRowCount(0);
        for (Map.Entry<Seminar, Slot> entry : scheduler.getSchedule().entrySet()) {
            scheduleTableModel.addRow(new Object[]{entry.getKey().getTitle(), entry.getValue().getRoom(), entry.getValue().getTimeSlot()});
        }
    }

    private void analyzeConflicts() {
        conflictTableModel.setRowCount(0);
        String selectedOption = (String) conflictOptions.getSelectedItem();

        if ("Overlapping Attendees".equals(selectedOption)) {
            overlappingAttendeesMap = scheduler.findOverlappingAttendees();
            for (Seminar seminar : scheduler.getSeminars()) {
                conflictTableModel.addRow(new Object[]{seminar.getTitle(), seminar.getSpeaker(), seminar.getAttendees()});
            }
        } else if ("Time Conflicts".equals(selectedOption)) {
            conflictingSlots = scheduler.findConflictingTimeSlots();
            for (Map.Entry<Seminar, Slot> entry : scheduler.getSchedule().entrySet()) {
                conflictTableModel.addRow(new Object[]{entry.getKey().getTitle(), entry.getValue().getRoom(), entry.getValue().getTimeSlot()});
            }
        }
    }

  private class ConflictCellRenderer extends DefaultTableCellRenderer {
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
        Component cell = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        String selectedOption = (String) conflictOptions.getSelectedItem();

        if ("Overlapping Attendees".equals(selectedOption) && column == 2) { 
            List<Integer> attendees = (List<Integer>) conflictTableModel.getValueAt(row, 2);
            StringBuilder boldAttendees = new StringBuilder("<html>");  
            for (Integer attendee : attendees) {
                if (overlappingAttendeesMap.containsKey(attendee)) {
                    boldAttendees.append("<b>").append(attendee).append("</b>, ");
                } else {
                    boldAttendees.append(attendee).append(", ");
                }
            }
            
            if (boldAttendees.length() > 6) {
                boldAttendees.setLength(boldAttendees.length() - 2);
            }
            boldAttendees.append("</html>");

            setText(boldAttendees.toString());
        } else if ("Time Conflicts".equals(selectedOption) && column == 2) { 
            int timeSlot = (int) conflictTableModel.getValueAt(row, 2);
            String room = (String) conflictTableModel.getValueAt(row, 1);
            boolean conflictExists = false;

            for (Slot slot : conflictingSlots) {
                if (slot.getTimeSlot() == timeSlot && slot.getRoom().equals(room)) {
                    conflictExists = true;
                    break;
                }
            }

            if (conflictExists) {
                setText("<html><b>" + timeSlot + "</b></html>");
            } else {
                setText(String.valueOf(timeSlot));
            }
        } else {
            cell.setFont(cell.getFont().deriveFont(Font.PLAIN));
        }

        return cell;
    }
}


    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SeminarSchedulerGUI gui = new SeminarSchedulerGUI();
            gui.setVisible(true);
        });
    }
}
