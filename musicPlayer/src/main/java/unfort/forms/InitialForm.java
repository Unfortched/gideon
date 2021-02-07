package unfort.forms;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Stream;

public abstract class InitialForm extends JFrame {

    public String pictureName;
    public JPanel mainContentPanel;
    public JPanel picturePanel;

    private Point screenSizeSetting(){
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locationX = (int) ((screenSize.getWidth() - mainContentPanel.getWidth())/2);
        int locationY = (int) ((screenSize.getHeight() - mainContentPanel.getHeight())/2);
        Point centerOfScreen = new Point(locationX,locationY);
        return centerOfScreen;
    }

    public void basicFrameSettings() {
        picturePanel.add(loadImage(pictureName));
        setContentPane(mainContentPanel);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        pack();
        setLocation(screenSizeSetting());
        setFrameIcon();
        setVisible(true);
    }

    public String getPicture(String name){
        String pictureNameLine = "";
        try (Stream<String> fileStrings = Files.lines(Path.of("src/main/resources/supportFiles/filesPaths.txt".replace('/',
                File.separatorChar)))) {
            pictureNameLine = fileStrings.filter(str -> str.contains(name)).findAny().get();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        String result = pictureNameLine.replace(name + " = ", "").replace('/',File.separatorChar);
        return result;
    }

    public JLabel loadImage(String pictureName){
        BufferedImage myPicture = null;
        if(!pictureName.contains(File.separator))
            pictureName = getPicture(pictureName);
        try {
            myPicture = ImageIO.read(new File(pictureName));
        } catch (IOException e) {
            e.printStackTrace();
        }
        JLabel picLabel = new JLabel(new ImageIcon(myPicture));
        return picLabel;
    }

    public void setFrameIcon(){
        try {
            setIconImage(ImageIO.read(new File(getPicture("musicPlayerIcon"))));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
