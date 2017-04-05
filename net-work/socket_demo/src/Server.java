import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by huchao on 17-4-5.
 */
public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(8888);
            Socket socket = null;
            int count = 0;
            System.out.println("服务器启动");
            while (true) {
                socket = serverSocket.accept();
                ServerThread serverThread = new ServerThread(socket);
                serverThread.start();
                count++;
                System.out.println("客户端数量："+count);
                InetAddress address = socket.getInetAddress();
                System.out.println("当前客户端IP:"+address.getHostAddress());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
