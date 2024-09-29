package treeftp.test;

import java.io.IOException;
import java.net.UnknownHostException;

import treeftp.commands.*;
import treeftp.server.Client;
import treeftp.server.ClientRequest;
import treeftp.server.Connection;
import treeftp.utils.Tree;

public class TestTree {

    private TestTree() {
    }

    public static Boolean testTreeStandard() throws IOException, InterruptedException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "-p", "/cdimage/"};
        request.checkParametersCommand(arguments);
        Parameters parameters = request.getParameters();
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        ClientRequest requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        Tree.start(request.getParameters(), client_cmd);
        requestHandlerCmd.disconnect();
        requestHandlerCmd.readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

    public static Boolean testTreeStandardAuth() throws IOException, InterruptedException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "testlogin", "testpswd" };
        request.checkParametersCommand(arguments);
        Parameters parameters = request.getParameters();
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        ClientRequest requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        Tree.start(request.getParameters(), client_cmd);
        requestHandlerCmd.disconnect();
        requestHandlerCmd.readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

    public static Boolean testSearchTree() throws UnknownHostException, IOException, InterruptedException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "-s", "HEADER.html" };
        request.checkParametersCommand(arguments);
        Parameters parameters = request.getParameters();
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        ClientRequest requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        Tree.start(request.getParameters(), client_cmd);
        requestHandlerCmd.disconnect();
        requestHandlerCmd.readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

    public static Boolean testJsonTree() throws IOException, InterruptedException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "-j" };
        request.checkParametersCommand(arguments);
        Parameters parameters = request.getParameters();
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        ClientRequest requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        Tree.start(request.getParameters(), client_cmd);
        requestHandlerCmd.disconnect();
        requestHandlerCmd.readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

    public static Boolean testOptionTree() throws UnknownHostException, IOException, InterruptedException {
        Commands request = new Commands();
        String[] arguments = { "ftp.ubuntu.com", "-l", "5", "-dd", "-p", "/cdimage" };
        request.checkParametersCommand(arguments);
        Parameters parameters = request.getParameters();
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        ClientRequest requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        Tree.start(request.getParameters(), client_cmd);
        requestHandlerCmd.disconnect();
        requestHandlerCmd.readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

}
