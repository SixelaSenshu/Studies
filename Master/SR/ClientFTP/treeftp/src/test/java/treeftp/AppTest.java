package treeftp;

import static org.junit.Assert.assertTrue;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.UnknownHostException;
import org.junit.Test;
import treeftp.test.*;

/**
 * Unit test for simple App.
 */
public class AppTest {
    /**
     * Rigorous Test :-)
     * 
     * @throws IOException
     * @throws UnknownHostException
     * @throws InterruptedException
     */
    @Test
    public void shouldAnswerWithTrue() throws UnknownHostException, IOException, InterruptedException {
       
        OutputStream output = new FileOutputStream("test.txt");
        PrintStream printOut = new PrintStream(output);
        System.setErr(printOut);
        System.out.println("Redirection du debug dans le fichier test.txt et des résultats dans resultTest.txt");
        System.out.println("/******************************************************\nTest de la connection au serveur FTP\n/******************************************************");
        assertTrue(TestClient.testConnection());
        System.out.println("/******************************************************\nTest de l'authentification au serveur FTP\n/******************************************************");
        assertTrue(TestClient.testAuthentification());
        System.out.println("/******************************************************\nTest du mode passif au serveur FTP\n/******************************************************");
        assertTrue(TestClient.testPassiveMode());
        System.out.println("/******************************************************\nTest de la commande LIST au serveur FTP\n/******************************************************");
        assertTrue( TestClient.testList());
        System.out.println("/******************************************************\nTest de la generation de commande avec log\n/******************************************************");
        assertTrue( TestCommandes.testCommandesLog());
        System.out.println("/******************************************************\nTest de la generation de commande avec log et options\n/******************************************************");
        assertTrue( TestCommandes.testCommandesLogOptional());
        System.out.println("/******************************************************\nTest de la generation de commande avec options\n/******************************************************");
        assertTrue(TestCommandes.testCommandesOptional());
        System.out.println("/******************************************************\nTest de la generation d'un arbre avec options\n/******************************************************");
        TestTree.testTreeStandard();
    }
}
