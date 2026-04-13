package moe.greenhandzdl.inClass.test;

import javax.swing.*;

public class PasswordConfirm {
private JPanel panel;
private JButton Confirm;
private JPasswordField passwdConfirm;
private JLabel Status;
private JPasswordField passwdEnter;

private void createListener(){
Confirm.addActionListener(e -> {
String userInput1 = new String(passwdEnter.getPassword());
String userInput2 = new String(passwdConfirm.getPassword());
// 如果两次密码有一个不存在
if(userInput1.isEmpty() || userInput2.isEmpty()){
Status.setToolTipText("Please enter your password in both fields.");
Status.setText("Error: Password fields cannot be empty.");
return;
}
if(userInput1.equals(userInput2)){
Status.setToolTipText("Passwords match.");
Status.setText("Success: Passwords match.");
} else {
Status.setToolTipText("Passwords do not match.");
Status.setText("Error: Passwords do not match.");
return;
}
String userInput = "Password entered: " + userInput1;
Status.setToolTipText(userInput);
Status.setText(userInput);
});
}

public static void main(String[] args) {
JFrame frame = new JFrame("PasswordConfirm");
PasswordConfirm passwordConfirm = new PasswordConfirm();
passwordConfirm.createListener();

frame.setContentPane(passwordConfirm.panel);
frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
frame.setSize(500, 400);
frame.setVisible(true);
}
}