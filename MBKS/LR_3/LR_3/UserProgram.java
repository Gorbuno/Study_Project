
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class UserProgram {
    private JFrame frame;
    private JTextField userNameField;
    private JTextField inputTextField;
    private JTextArea filteredTextArea;
    private JButton submitButton;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                UserProgram window = new UserProgram();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }
    public UserProgram() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblUserName = new JLabel("User Name:");
        lblUserName.setBounds(10, 10, 80, 25);
        frame.getContentPane().add(lblUserName);

        userNameField = new JTextField();
        userNameField.setBounds(100, 10, 150, 25);
        frame.getContentPane().add(userNameField);
        userNameField.setColumns(10);

        JLabel lblInputText = new JLabel("Input Text:");
        lblInputText.setBounds(10, 40, 80, 25);
        frame.getContentPane().add(lblInputText);

        inputTextField = new JTextField();
        inputTextField.setBounds(100, 40, 150, 25);
        frame.getContentPane().add(inputTextField);
        inputTextField.setColumns(10);

        submitButton = new JButton("Submit");
        submitButton.setBounds(10, 70, 80, 25);
        frame.getContentPane().add(submitButton);

        filteredTextArea = new JTextArea();
        filteredTextArea.setBounds(10, 100, 414, 150);
        frame.getContentPane().add(filteredTextArea);
        submitButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String userName = userNameField.getText();
                String inputText = inputTextField.getText();
                StringBuilder filteredText = filterText(userName, inputText);
                filteredTextArea.setText(filteredText.toString());
            }
        });
    }
    private StringBuilder filterText(String userName, String inputText) {
        String accessRightsFilePath = "access_rights.txt";
        StringBuilder filteredText = new StringBuilder();
        try {
            List<String> lines = Files.readAllLines(Paths.get(accessRightsFilePath));
            for (String line : lines) {
                String[] parts = line.split(":");
                if (parts.length == 2 && parts[0].equals(userName)) {
                    var objects = List.of(parts[1].split("-"));
                    for (char c : inputText.toCharArray()) {
                        String charStr = String.valueOf(c);
                        if (objects.contains(charStr)) {
                            filteredText.append(charStr);
                        }
                    }
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return filteredText;
    }
}

