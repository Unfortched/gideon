package unfort.forms;

import junit.framework.TestCase;
import org.junit.Rule;
import org.junit.Test;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.NoSuchElementException;
import java.util.stream.Stream;

public class InitialFormTest extends TestCase {

    @Rule
    String pictureName = "src/main/resources/screensPictures/loadingScreen.jpg";

    @Test(timeout = 200)
    public void testLoadImage() {
        BufferedImage myPicture = null;
        try {
            myPicture = ImageIO.read(new File(pictureName));
        } catch (IOException e) {
            e.printStackTrace();
        }
        JLabel picLabel = new JLabel(new ImageIcon(myPicture));
        assertNotNull(picLabel);
    }

    @Test (expected = IOException.class, timeout = 100)
    public void testGetPicture() {
        String initialPictureName = "loadingPictureScreen";
        String pictureNameLine = "";
        try (Stream<String> fileStrings = Files.lines(Path.of("src/main/resources/supportFiles/filesPaths.txt".replace('/',
                File.separatorChar)))) {
            pictureNameLine = fileStrings.filter(str -> str.contains(initialPictureName)).findAny().get();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        String result = pictureNameLine.replace(initialPictureName + " = ", "").replace('/',File.separatorChar);
        assertEquals(pictureName,result);

    }

    @Test (expected = NoSuchElementException.class)
    public void testScreenSizeSetting(){
        JPanel testPanel = new JPanel();
        testPanel.setSize(500,500);
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locationX = (int) ((screenSize.getWidth() - testPanel.getWidth())/2);
        int locationY = (int) ((screenSize.getHeight() - testPanel.getHeight())/2);
        Point centerOfScreen = new Point(locationX,locationY);
        Point expectedScreenPoint = new Point(710, 290);
        assertEquals(expectedScreenPoint, centerOfScreen);
    }
}