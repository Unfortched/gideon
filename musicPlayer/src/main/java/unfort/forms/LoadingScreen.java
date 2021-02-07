package unfort.forms;

import javax.swing.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.Timer;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class LoadingScreen extends InitialForm {
    private JProgressBar loadingProgressBar;
    private JPanel loadingPicturePanel;
    private JPanel loadingTextField;
    private JLabel loadingLabel;

    private static LoadingScreen loadingScreenForm = new LoadingScreen();

    public static LoadingScreen getInstance(){
        return loadingScreenForm;
    }

    private LoadingScreen() {
        super.pictureName = getPicture("loadingScreenPicture");
        super.mainContentPanel = loadingTextField;
        super.picturePanel = loadingPicturePanel;
        setUndecorated(true);
        basicFrameSettings();
        loadingSimulation();
    }

    private void loadingSimulation(){

            TimerTask timerTask = new TimerTask() {
                int timerStep = 1;
                String prefix = "Unpacking files: ";
                ArrayList<String> strings = getStringLoadingProcess();
                    @Override
                public void run() {
                    int currentValue = loadingProgressBar.getValue();
                    if(currentValue < loadingProgressBar.getMaximum()) {
                        loadingProgressBar.setValue(currentValue + timerStep);
                        loadingLabel.setText(prefix + strings.get(currentValue));
                    }
                    else {
                        cancel();
                        loadingLabel.setText("Ready.");
                        changeWindow();
                    }
                }
        };

        Timer timer = new Timer("Timer");
        int periodTime = 50;
        timer.scheduleAtFixedRate(timerTask,0,periodTime);
    }

    private ArrayList<String> getStringLoadingProcess() {

        String filename = "src/main/resources/supportFiles/loadingStrings.txt".replace('/', File.separatorChar);
        ArrayList<String> result = new ArrayList<>();
        try (Stream<String> fileStream = Files.lines(Path.of(filename))) {
            fileStream.map(s -> s.toString()).limit(100).collect(Collectors.toList()).forEach(result::add);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    private void changeWindow(){
        try {
            Thread.sleep(1000);
            PathChooseScreen.getInstance();
            dispose();
        } catch (InterruptedException interruptedException) {
            interruptedException.printStackTrace();
        }
    }
}