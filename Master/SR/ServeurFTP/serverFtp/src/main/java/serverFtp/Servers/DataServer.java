package serverFtp.Servers;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class DataServer extends Thread {
    
    private Client client;
    private String ip;
    private String port;
    

    public DataServer(Client client, String ip, String port) {
        this.client = client;
        this.ip = ip;
        this.port = port;
    }

    public void run() {
        try{
            int port = Integer.parseInt(this.port);
			InetAddress ad = InetAddress.getByName(this.ip);
            System.out.println(port + " " + ip);
            ServerSocket socket = new ServerSocket(port, 0, ad);
            Socket res = socket.accept();
            this.client.setSocketData(res, this.port);
            socket.close();
		}catch(IOException e){
			System.err.println("Error: " + e.getMessage());
		}
    }
}
