package event.ui;
import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.sql.*;
import java.util.*;
import java.util.List;
import event.service.*;
import event.model.*;

public class SeminarSchedulerGUI extends JFrame {
    public SchedulerService scheduler;
    private JTable seminarTable;
    private JTable scheduleTable;
    private DefaultTableModel seminarTableModel;
    public JTabbedPane tabbedPane = new JTabbedPane();
    private DefaultTableModel scheduleTableModel;
    private JTable conflictTable;
    private DefaultTableModel conflictTableModel;
    private JComboBox<String> conflictOptions;
    private Map<Integer, List<Seminar>> overlappingAttendeesMap = new HashMap<>();
    private List<Slot> conflictingSlots = new ArrayList<>();

    public SeminarSchedulerGUI() {
        setTitle("Seminar Scheduler");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        scheduler = new SchedulerService();



        JPanel seminarPanel = new JPanel(new BorderLayout());
        JPanel btnPanel = new JPanel();
        JButton loadSeminarButton = new JButton("Upload Seminar File");
        JButton loadSeminarButton1 = new JButton("Load Seminars From DB");
        btnPanel.add(loadSeminarButton);
        btnPanel.add(loadSeminarButton1);
        seminarPanel.add(btnPanel, BorderLayout.NORTH);

        seminarTableModel = new DefaultTableModel(new String[]{"ID", "Title", "Speaker", "Attendees", "Update", "Delete"}, 0);
        seminarTable = new JTable(seminarTableModel);
        seminarTable.getColumn("Update").setCellRenderer(new ButtonRenderer("Update"));
        seminarTable.getColumn("Delete").setCellRenderer(new ButtonRenderer("Delete"));
        seminarTable.getColumn("Update").setCellEditor(new ButtonEditor(new JButton("Update")));
        seminarTable.getColumn("Delete").setCellEditor(new ButtonEditor(new JButton("Delete")));
        JScrollPane seminarScrollPane = new JScrollPane(seminarTable);
        seminarPanel.add(seminarScrollPane, BorderLayout.CENTER);

        loadSeminarButton.addActionListener(e -> uploadSeminars());
        loadSeminarButton1.addActionListener(e -> loadSeminarsFromDatabase());

        tabbedPane.add("Seminar Information", seminarPanel);


        JPanel schedulePanel = new JPanel(new BorderLayout());
        JPanel btonPanel = new JPanel();
        JButton loadScheduleButton = new JButton("Upload Schedule File");
        JButton loadScheduleButton1 = new JButton("Load Schedules From DB");
        btonPanel.add(loadScheduleButton);
        btonPanel.add(loadScheduleButton1);
        schedulePanel.add(btonPanel, BorderLayout.NORTH);

        scheduleTableModel = new DefaultTableModel(new String[]{"ID", "Seminar Title", "Room", "Time-slot", "Update", "Delete"}, 0);
        scheduleTable = new JTable(scheduleTableModel);
        scheduleTable.getColumn("Update").setCellRenderer(new ButtonRenderer("Update"));
        scheduleTable.getColumn("Delete").setCellRenderer(new ButtonRenderer("Delete"));
        scheduleTable.getColumn("Update").setCellEditor(new ButtonEditor(new JButton("Update")));
        scheduleTable.getColumn("Delete").setCellEditor(new ButtonEditor(new JButton("Delete")));
        JScrollPane scheduleScrollPane = new JScrollPane(scheduleTable);
        schedulePanel.add(scheduleScrollPane, BorderLayout.CENTER);

        loadScheduleButton.addActionListener(e -> uploadSchedule());
        loadScheduleButton1.addActionListener(e -> loadScheduleFromDatabase());

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
                loadSeminarsFromDatabase();
            } catch (IOException e) {
                JOptionPane.showMessageDialog(this, "Error reading seminar file: " + e.getMessage());
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private void uploadSchedule() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                scheduler.readScheduleFile(file);
                loadScheduleFromDatabase();

            } catch (IOException e) {
                JOptionPane.showMessageDialog(this, "Error reading schedule file: " + e.getMessage());
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private void loadSeminarsFromDatabase() {
        scheduler.loadSeminarsFromDatabase();
        updateSeminarTable();
    }

    private void loadScheduleFromDatabase() {
        scheduler.loadScheduleFromDatabase();
        updateScheduleTable();
    }

    private void updateSeminarTable() {
        seminarTableModel.setRowCount(0);
        for (Seminar seminar : scheduler.getSeminars()) {

            seminarTableModel.addRow(new Object[]{
                    seminar.getId(),
                    seminar.getTitle(),
                    seminar.getSpeaker(),
                    seminar.getAttendees(),
                    "Update",
                    "Delete"
            });
        }
    }

    private void updateScheduleTable() {
        scheduleTableModel.setRowCount(0);
        for (Map.Entry<Seminar, Slot> entry : scheduler.getSchedule().entrySet()) {
            Seminar seminar = entry.getKey();
            Slot slot = entry.getValue();


            scheduleTableModel.addRow(new Object[]{
                    slot.getId(),
                    seminar.getTitle(),
                    slot.getRoom(),
                    slot.getTimeSlot(),
                    "Update",
                    "Delete"
            });
        }
    }

    private void updateSeminar(Seminar seminar) {
        int row = seminarTable.getSelectedRow();
        if (row == -1) return;

        seminar = new Seminar(seminar.getId(), seminar.getTitle(), seminar.getSpeaker(), seminar.getAttendees());


        scheduler.updateSeminar(seminar);


        loadSeminarsFromDatabase();
        JOptionPane.showMessageDialog(null, "Seminar has been updated successfully", "Update", JOptionPane.INFORMATION_MESSAGE);
    }

    private void deleteSeminar(Seminar seminar) throws SQLException {
        int row = seminarTable.getSelectedRow();
        if (row == -1) return;

        scheduler.deleteSeminar(seminar);
        loadSeminarsFromDatabase();
        JOptionPane.showMessageDialog(null, "Seminar has been deleted Successfully", "Delete", JOptionPane.INFORMATION_MESSAGE);
    }

    private void updateSchedule(Slot slot, int row) throws SQLException {
        if (row == -1) return;

        String title = (String) scheduleTableModel.getValueAt(row, 1);
        Seminar s = scheduler.getSeminarByTitle(title);


        scheduler.updateSchedule(slot, s);

        loadScheduleFromDatabase();

        JOptionPane.showMessageDialog(null, "Scheduler has been updated Successfully", "Update", JOptionPane.INFORMATION_MESSAGE);
    }


    private void deleteSchedule(Slot slot) throws SQLException {
        int row = scheduleTable.getSelectedRow();
        if (row == -1) return;
        String title=(String)scheduleTableModel.getValueAt(row,1);
        Seminar s=scheduler.getSeminarByTitle(title);
        scheduler.deleteSchedule(s);
        loadScheduleFromDatabase();
        JOptionPane.showMessageDialog(null, "Schedule has been deleted Successfully", "Delete", JOptionPane.INFORMATION_MESSAGE);
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


    private static class ButtonRenderer extends JButton implements TableCellRenderer {
        public ButtonRenderer(String text) {
            setText(text);
            setOpaque(true);
        }

        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            setText((value == null) ? "" : value.toString());
            return this;
        }
    }

    private class ButtonEditor extends DefaultCellEditor {
        private JButton button;
        private String label;
        private boolean isPushed;

        public ButtonEditor(JButton button) {
            super(new JCheckBox());
            this.button = button;
            this.button.setOpaque(true);


            button.addActionListener(e -> {
                if (isPushed) {
                    int row;
                    DefaultTableModel model;
                    int selectedTabIndex = tabbedPane.getSelectedIndex();

                    if (selectedTabIndex == 0) {
                        row = seminarTable.getSelectedRow();
                        model = seminarTableModel;
                        if (row >= 0) {
                            int modelRow = seminarTable.convertRowIndexToModel(row);
                            if ("Update".equals(label)) {
                                Integer id = (Integer) seminarTableModel.getValueAt(modelRow, 0);
                                String title = (String) seminarTableModel.getValueAt(modelRow, 1);
                                String speaker = (String) seminarTableModel.getValueAt(modelRow, 2);
                                String attendeesString = (String) seminarTableModel.getValueAt(modelRow, 3);


                                List<Integer> attendees = parseAttendeesString(attendeesString);
                                updateSeminar(new Seminar(id, title, speaker, attendees));
                            } else if ("Delete".equals(label)) {
                                try {
                                    deleteSeminar(scheduler.getSeminars().get(modelRow));
                                } catch (SQLException ex) {
                                    throw new RuntimeException(ex);
                                }
                            }
                        }
                    } else if (selectedTabIndex == 1) {
                        row = scheduleTable.getSelectedRow();
                        model = scheduleTableModel;
                        if (row >= 0) {
                            int modelRow = scheduleTable.convertRowIndexToModel(row);
                            Object idObj = scheduleTableModel.getValueAt(modelRow, 0);
                            Integer id = idObj instanceof Integer ? (Integer) idObj : Integer.parseInt((String) idObj);

                            String room = (String) scheduleTableModel.getValueAt(modelRow, 2);

                            Object timeSlotObj = scheduleTableModel.getValueAt(modelRow, 3);
                            int timeSlot = timeSlotObj instanceof Integer ? (Integer) timeSlotObj : Integer.parseInt((String) timeSlotObj);

                            if ("Update".equals(label)) {
                                try {
                                    updateSchedule(new Slot(id, room, timeSlot),modelRow);
                                } catch (SQLException ex) {
                                    throw new RuntimeException(ex);
                                }
                            } else if ("Delete".equals(label)) {
                                try {
                                    deleteSchedule(new Slot(id, room, timeSlot));
                                } catch (SQLException ex) {
                                    throw new RuntimeException(ex);
                                }
                            }
                        }
                    }
                    fireEditingStopped();
                }
            });

        }

        @Override
        public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column) {
            label = (value == null) ? "" : value.toString();
            button.setText(label);
            isPushed = true;
            return button;
        }

        @Override
        public Object getCellEditorValue() {
            isPushed = false;
            return label;
        }

        @Override
        public boolean stopCellEditing() {
            isPushed = false;
            return super.stopCellEditing();
        }

        @Override
        protected void fireEditingStopped() {
            super.fireEditingStopped();
        }
    }
    private List<Integer> parseAttendeesString(String attendeesString) {
        List<Integer> attendees = new ArrayList<>();
        if (attendeesString == null || attendeesString.trim().isEmpty()) {
            return attendees;
        }

        attendeesString = attendeesString.trim();
        if (attendeesString.startsWith("[") && attendeesString.endsWith("]")) {
            attendeesString = attendeesString.substring(1, attendeesString.length() - 1);
        }

        String[] parts = attendeesString.split(",");
        for (String part : parts) {
            try {
                attendees.add(Integer.parseInt(part.trim()));
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(null, "Invalid attendee format: " + part, "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
        return attendees;
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
                boolean conflictExists = conflictingSlots.stream()
                        .anyMatch(slot -> slot.getTimeSlot() == timeSlot && slot.getRoom().equals(room));
                setText(conflictExists ? "<html><b>" + timeSlot + "</b></html>" : String.valueOf(timeSlot));
            } else {
                cell.setFont(cell.getFont().deriveFont(Font.PLAIN));
                setText(value.toString());
            }

            return cell;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SeminarSchedulerGUI app = new SeminarSchedulerGUI();
            app.setVisible(true);
        });
    }
}
