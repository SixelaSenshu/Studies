/**
 * La classe principale de l'application
 * @version 1.0
 * @file App.java
 * @authors Alexis Bernard & Tom Taffin
 */

package serverFtp;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;

import serverFtp.Servers.Server;

/**
 * Classe principale
 */
public class App 
{
    /**
	 * Main function
	 * @param args Arguments
	 * @throws IOException Exception IO
	 */
    public static void main( String[] args ) throws IOException
    {
        if(args.length !=2 ){
            System.err.println("Error: arguments expected");
            System.exit(1);
        }
        System.out.println("Beginning of app");
        OutputStream output = new FileOutputStream("log.txt");
        PrintStream printOut = new PrintStream(output);
        System.setErr(printOut);
        appMain(args[0],args[1]);
        System.out.println("End of app");
    }

   /**
	* Application principale
	* @param port Le port sur lequel le serveur va écouter
	* @param ip L'adresse ip du serveur
	* @throws IOException Exception IO
    */
    public static void appMain(String port,String ip) throws IOException{
        Server server = new Server(port,ip);
        server.run();
		while(true){}
    }
}
