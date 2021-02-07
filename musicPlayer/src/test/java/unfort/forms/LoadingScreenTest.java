package unfort.forms;

import junit.framework.TestCase;
import org.junit.Rule;
import org.junit.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class LoadingScreenTest extends TestCase {

    @Rule
    String filename = "src/main/resources/supportFiles/loadingStrings.txt".replace('/', File.separatorChar);

    @Rule
    String thirdFileLine = "read/n";

    @Test (expected = IOException.class)
    public void testGetStringLoadingProcess(){
        ArrayList<String> result = new ArrayList<>();
        try (Stream<String> fileStream = Files.lines(Path.of(filename))) {
            fileStream.distinct().collect(Collectors.toList()).forEach(result::add);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        assertEquals(thirdFileLine,result.get(2));
    }
}