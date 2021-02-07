package unfort;

import junit.framework.TestCase;
import org.junit.Rule;
import org.junit.Test;

import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;

public class MusicTest extends TestCase {

    @Rule
    File testMusicFile = new File("src/test/java/unfort/testMusicFile.wav".replace('/', File.separatorChar));
    private Long currentFrame = 2L;
    private Clip clip;
    private AudioInputStream audioInputStream;

    @Test
    public void testPlayMusic() {
        try {
            audioInputStream = AudioSystem.getAudioInputStream(testMusicFile);
            clip = AudioSystem.getClip();
            clip.open(audioInputStream);
        } catch (UnsupportedAudioFileException e) {
        } catch (LineUnavailableException e) {
        } catch (IOException e) {
            e.printStackTrace();
        }
        assertNotNull(clip);
    }
}