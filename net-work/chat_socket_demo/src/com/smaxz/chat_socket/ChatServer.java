package com.smaxz.chat_socket;

import java.net.ServerSocket;
import java.util.ArrayList;

/**
 * Created by huchao on 17-4-6.
 */
public class ChatServer {
    private static final int SOCKET_PORT = 52000;
    public static ArrayList<SocketBean> mSocketList = new ArrayList<SocketBean>();

    private void initServer() {
        try {
            // 创建一个ServerSocket，用于监听客户端Socket的连接请求
            ServerSocket server = new ServerSocket(SOCKET_PORT);
            while(true) {
                // 每当接收到客户端的Socket请求，服务器端也相应的创建一个Socket
                SocketBean socketBean = new SocketBean();
                socketBean.setSocket(server.accept());
                mSocketList.add(socketBean);
                // 每连接一个客户端，启动一个ServerThread线程为该客户端服务
                ServerThread serverThread = new ServerThread(socketBean);
                serverThread.start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ChatServer server = new ChatServer();
        server.initServer();
    }
}
