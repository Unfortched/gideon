package unfort;

import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;
import java.util.Objects;

public class Music {
    private File sourceFile;
    private String songName;
    private Long currentFrame;
    private Clip clip;
    private AudioInputStream audioInputStream;

    public Music(File file){
        sourceFile = file;
        songName = file.getName();
    }

    public void playMusic(){
        resetAudioStream();
        clip.start();
    }

    public void pauseMusic(){
        this.currentFrame = this.clip.getMicrosecondPosition();
        clip.stop();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Music music = (Music) o;
        return Objects.equals(sourceFile, music.sourceFile) && Objects.equals(songName, music.songName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(sourceFile, songName);
    }

    public boolean musicIsPlaying(){
        return clip.isRunning();
    }

    public void resumeMusic(){
        clip.close();
        resetAudioStream();
        clip.setMicrosecondPosition(currentFrame);
        clip.start();
    }

    public void stopMusic(){
        clip.close();
    }

    public void changeVolume(int state){
        if(clip.isOpen()){
            FloatControl gainControl =
                    (FloatControl) clip.getControl(FloatControl.Type.MASTER_GAIN);
            gainControl.setValue((float) ((float)state));
        }
    }

    private void resetAudioStream() {
        try {
            audioInputStream = AudioSystem.getAudioInputStream(sourceFile);
            clip = AudioSystem.getClip();
            clip.open(audioInputStream);
        } catch (UnsupportedAudioFileException e) {
        } catch (LineUnavailableException e) {
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String getSongName() {
        return songName;
    }
}
