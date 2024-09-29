package treeftp.test;

import java.io.IOException;
import java.net.UnknownHostException;

import treeftp.commands.*;

public class TestCommandes {

    private TestCommandes() {
    }

    public static Boolean testCommandesLog() throws UnknownHostException, IOException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "anonymous", "anonymous" };
        return request.checkParametersCommand(arguments);
    }

    public static Boolean testCommandesLogOptional() throws UnknownHostException, IOException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "anonymous", "anonymous", "-p", "cdimage", "-j" };
        return request.checkParametersCommand(arguments);
    }

    public static Boolean testCommandesOptional() throws UnknownHostException, IOException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "-p", "cdimage", "-j", "-dd" };
        return request.checkParametersCommand(arguments);
    }
}
