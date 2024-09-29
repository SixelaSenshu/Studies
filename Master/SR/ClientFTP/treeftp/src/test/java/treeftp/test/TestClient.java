package treeftp.test;

import java.io.IOException;
import java.net.UnknownHostException;

import treeftp.commands.*;
import treeftp.server.*;

public class TestClient {

    private TestClient() {
    }

    public static Boolean testConnection() throws UnknownHostException, IOException {
        Parameters parameters = new Parameters();
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        if (!Connection.checkReachableConnection(client_cmd, parameters)) {
            return false;
        }
        client_cmd.getConnection().getRequest().disconnect();
        client_cmd.getConnection().getRequest().readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

    public static Boolean testAuthentification() throws UnknownHostException, IOException {
        Parameters parameters = new Parameters();
        parameters.setUser("anonymous");
        parameters.setPassword("anonymous");
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        client_cmd.getConnection().getRequest().disconnect();
        client_cmd.getConnection().getRequest().readRequest();
        client_cmd.getConnection().disconnect();
        return true;
    }

    public static Boolean testPassiveMode() throws UnknownHostException, IOException {
        Parameters parameters = new Parameters();
        ClientRequest requestHandlerCmd, requestHandlerData;
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        String port = requestHandlerCmd.PASV();
        if (port == null) {
            return false;
            
        } else {
            System.err.println("Port -> " + port);
            client_cmd.getConnection().getRequest().disconnect();
            client_cmd.getConnection().getRequest().readRequest();
            client_cmd.getConnection().disconnect();
            return true;
        }

    }

    public static Boolean testList() throws UnknownHostException, IOException{
         Parameters parameters = new Parameters();
        ClientRequest requestHandlerCmd, requestHandlerData;
        Client client_cmd = new Client(parameters.getUrl(), 21,
                parameters.getUsername(), parameters.getPassword());
        requestHandlerCmd = client_cmd.getConnection().getRequest();
        if (!Connection.checkConnection(client_cmd, parameters)) {
            return false;
        }
        String port = requestHandlerCmd.PASV();
        if (port == null) {
            return false;
        }
        Client client_data = new Client(parameters.getUrl(), Integer.valueOf(port),
                parameters.getUsername(), parameters.getPassword());
        client_data.getConnection().connect();
        requestHandlerData = client_data.getConnection().getRequest();
        String params[] = { parameters.getUsername() };
        requestHandlerData.writeRequest("USER", params);
        requestHandlerData.sendRequest();
        params[0] = parameters.getPassword();
        requestHandlerData.writeRequest("PASS", params);
        requestHandlerData.sendRequest();
        requestHandlerCmd.changeRepository("/");
        requestHandlerCmd.showRepository("/");
        client_cmd.getConnection().getRequest().disconnect();
        client_cmd.getConnection().getRequest().readRequest();
        client_data.getConnection().getRequest().disconnect();
        client_data.getConnection().disconnect();
        client_cmd.getConnection().disconnect();
        return true;
        
    }
}
