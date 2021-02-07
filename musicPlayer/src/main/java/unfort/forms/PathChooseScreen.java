package unfort.forms;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;


public class PathChooseScreen extends InitialForm {
    private JTextField pathTextField;
    private JButton reviewButton;
    private JButton continueButton;
    public JPanel pathPanelForm;
    private JPanel pathScreenPanel;

    private static PathChooseScreen pathScreenForm = new PathChooseScreen();

    public static PathChooseScreen getInstance(){
        return pathScreenForm;
    }

    private PathChooseScreen(){

        super.mainContentPanel = pathPanelForm;
        super.pictureName = getPicture("pathChooseScreenPicture");
        super.picturePanel = pathScreenPanel;
        setUndecorated(true);
        basicFrameSettings();

        reviewButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                pathTextField.setText(showFileChooser().getAbsolutePath());
            }
        });
        continueButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                MusicPlayerScreen mps = MusicPlayerScreen.getInstance();
                mps.searchWithNewPath(pathTextField.getText());
                mps.startToUse();
                dispose();
            }
        });
    }

    private File showFileChooser(){
        JFileChooser dialog = new JFileChooser();
        dialog.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        dialog.setApproveButtonText("Confirm");
        dialog.setDialogTitle("Choose your directory with music");
        dialog.setDialogType(JFileChooser.OPEN_DIALOG);
        dialog.setMultiSelectionEnabled(true);
        dialog.showOpenDialog(this);
        File file = dialog.getSelectedFile();
        return file;
    }
}
