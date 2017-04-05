import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by huchao on 17-4-5.
 */
public class client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("119.29.36.247",8888);
            OutputStream os = socket.getOutputStream();
            PrintWriter pw=new PrintWriter(os);//将输出流包装为打印流
            pw.write("用户名：alice;密码：789");
            pw.flush();
            socket.shutdownOutput();//关闭输出流
            //3.获取输入流，并读取服务器端的响应信息
            InputStream is=socket.getInputStream();
            BufferedReader br=new BufferedReader(new InputStreamReader(is));
            String info=null;
            while((info=br.readLine())!=null){
                System.out.println("我是客户端，服务器说："+info);
            }
            //4.关闭资源
            br.close();
            is.close();
            pw.close();
            os.close();
            socket.close();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
