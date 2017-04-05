import java.io.*;
import java.net.Socket;

/**
 * Created by huchao on 17-4-5.
 */

public class ServerThread extends Thread {
    private Socket socket = null;
    public ServerThread(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        InputStream is = null;
        InputStreamReader isr = null;
        BufferedReader br = null;
        OutputStream os = null;
        PrintWriter pw = null;

        try {
            is = socket.getInputStream();
            isr = new InputStreamReader(is);
            br = new BufferedReader(isr);
            String info;
            while((info = br.readLine())!=null) {
                System.out.println("我是服务器：客户端说："+info);
            }
            socket.shutdownInput();
            os = socket.getOutputStream();
            pw = new PrintWriter(os);
            pw.write("欢迎您！");
            pw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if(pw!=null) pw.close();
                if(os!=null) os.close();
                if(br!=null) br.close();
                if(isr!=null) isr.close();
                if(is!=null) is.close();
                if(socket!=null) socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
