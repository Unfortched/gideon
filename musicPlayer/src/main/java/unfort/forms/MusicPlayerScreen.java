package unfort.forms;

import unfort.CustomScrollBarUI;
import unfort.Music;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.event.*;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class MusicPlayerScreen extends InitialForm {
    public JPanel mainPanelForm;
    private JList mediaList;
    private JButton previousButton;
    private JButton playButton;
    private JButton nextButton;
    private JSlider volumeSlider;
    private JPanel speakerPicture;
    private JPanel imagePanel;
    private JLabel authorLabel;
    private JPanel musicPanelScreen;
    private JButton exitButton;
    private JScrollPane listViewScrollPanel;
    private JLabel musicCollectionLabel;
    private JPanel controlPanel;
    private JLabel songLabel;

    private String pathWay;
    private List<Music> musicCollection;
    private Music currentMusic;
    private int currentMusicIndex;
    private static MusicPlayerScreen musicScreenForm = new MusicPlayerScreen();

    public static MusicPlayerScreen getInstance(){
        return musicScreenForm;
    }

    public void searchWithNewPath(String path){
        pathWay = path.replace('\\', File.separatorChar);
        processFilesFromFolder(new File(pathWay));
    }

    private void processFilesFromFolder(File folder) {
        File[] folderEntries = folder.listFiles();
        for (File entry : folderEntries)
        {
            if (entry.isDirectory())
            {
                processFilesFromFolder(entry);
                continue;
            }
            if(isThisMusicFile(entry))
                musicCollection.add(new Music(entry));
        }
    }

    private boolean isThisMusicFile(File file){
        if(file.getName().contains(".wav"))
            return true;
        else return false;
    }

    private MusicPlayerScreen(){
        musicCollection = new ArrayList<>();
        currentMusic = new Music(new File(""));
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispatchEvent(new WindowEvent(MusicPlayerScreen.this, WindowEvent.WINDOW_CLOSING));
            }
        });

        playButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                playButton.removeAll();
                if(currentMusic.musicIsPlaying()){
                    currentMusic.pauseMusic();
                    playButton.add(loadImage("playButton"));
                }
                else {
                    currentMusic.resumeMusic();
                    playButton.add(loadImage("pauseButton"));
                }
                playButton.updateUI();

            }
        });

        mediaList.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == MouseEvent.BUTTON2) {
                    int listSongIndex = mediaList.getSelectedIndex();
                    if(!currentMusic.equals(musicCollection.get(listSongIndex))
                            && !currentMusic.getSongName().equals(""))
                        currentMusic.stopMusic();
                    currentMusic = musicCollection.get(listSongIndex);
                    currentMusicIndex = listSongIndex;
                    authorLabel.setText("Now playing: " + musicCollection.get(listSongIndex).getSongName());
                    playButton.removeAll();
                    playButton.add(loadImage("pauseButton"));
                    volumeSlider.setValue(volumeSlider.getValue());
                    playButton.updateUI();

                    currentMusic.playMusic();
                }
            }
        });

        nextButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                currentMusic.stopMusic();
                if(currentMusicIndex < musicCollection.size() - 1){
                    currentMusic = musicCollection.get(currentMusicIndex++);
                    mediaList.setSelectedIndex(currentMusicIndex);
                    authorLabel.setText("Now playing: " + musicCollection.get(currentMusicIndex).getSongName());
                }
                currentMusic.playMusic();
            }
        });

        previousButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                currentMusic.stopMusic();
                if(currentMusicIndex >= 1){
                    currentMusic = musicCollection.get(currentMusicIndex--);
                    mediaList.setSelectedIndex(currentMusicIndex);
                    authorLabel.setText("Now playing: " + musicCollection.get(currentMusicIndex).getSongName());
                }
                currentMusic.playMusic();
            }
        });

        volumeSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                currentMusic.changeVolume(volumeSlider.getValue());
            }
        });
    }

    private void setButtonIcon(){
        nextButton.add(loadImage("forwardButton"));
        previousButton.add(loadImage("backButton"));
        playButton.add(loadImage("playButton"));
        exitButton.add(loadImage("exitButton"));
        speakerPicture.add(loadImage("volumePicture"));
    }

    private void setScrollbarsUI(){
        listViewScrollPanel.getVerticalScrollBar().setUI(new CustomScrollBarUI());
        listViewScrollPanel.getHorizontalScrollBar().setUI(new CustomScrollBarUI());
    }

    public void startToUse(){
        super.mainContentPanel = musicPanelScreen;
        super.pictureName = getPicture("musicPlayerPicture");
        super.picturePanel = imagePanel;
        loadMusicList();
        setScrollbarsUI();
        setButtonIcon();
        basicFrameSettings();
    }

    private void loadMusicList(){
        String[] songNames = new String[musicCollection.size()];
        for(Music ms: musicCollection){
            int index = musicCollection.indexOf(ms);
            songNames[index] = ms.getSongName();
        }
        mediaList.setListData(songNames);
    }

}
