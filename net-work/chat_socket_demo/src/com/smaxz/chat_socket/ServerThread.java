package com.smaxz.chat_socket;

import org.json.JSONObject;

import java.io.*;

/**
 * Created by huchao on 17-4-6.
 */
public class ServerThread extends Thread {
    private SocketBean socketBean = null;

    public ServerThread(SocketBean socketBean) {
        this.socketBean = socketBean;
    }

    @Override
    public void run() {
        try {
            String info_s;
            JSONObject info_j;
            InputStream is;
            InputStreamReader isr;
            BufferedReader br;
            is = socketBean.getSocket().getInputStream();
            isr = new InputStreamReader(is);
            br = new BufferedReader(isr);
            // 循环不断地从Socket中读取客户端发送过来的数据
            while ((info_s = br.readLine()) != null) {
                info_j = new JSONObject(info_s);
                System.out.println(info_j.getString("action"));
                if(info_j.getString("action").equals("LOGIN")) {
                    login(info_j.getString("deviceId"),info_j.getString("nickName"),info_j.getString("loginTime"));
                } else if(info_j.getString("action").equals("LOGOUT")) {
                    logout(info_j.getString("deviceId"));
                } else if(info_j.getString("action").equals("SENDMSG")) {
                    sendmsg(info_j.getString("otherName"),info_j.getString("otherId"),info_j.getString("selfId"),info_j.getString("message"));
                } else if(info_j.getString("action").equals("GETLIST")) {
                    getlist(info_j.getString("deviceId"));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void login(String deviceId, String nickName, String loginTime) throws IOException {
        for (int i=0; i<ChatServer.mSocketList.size(); i++) {
            SocketBean item = ChatServer.mSocketList.get(i);
            if (item.getId().equals(socketBean.getId())) {
                item.setDeviceId(deviceId);
                item.setNickName(nickName);
                item.setLoginTime(loginTime);
                ChatServer.mSocketList.set(i, item);
                break;
            }
        }
    }

    private String getFriend() {
        String friends = "GETLIST,";
        for (SocketBean item : ChatServer.mSocketList) {
            if (item.getDeviceId()!=null && item.getDeviceId().length()>0) {
                String friend = String.format("|%s,%s,%s", item.getDeviceId(), item.getNickName(), item.getLoginTime());
                friends += friend;
            }
        }
        return friends;
    }

    private void getlist(String deviceId) throws IOException {
        for (int i=0; i<ChatServer.mSocketList.size(); i++) {
            SocketBean item = ChatServer.mSocketList.get(i);
            if (item.getId().equals(socketBean.getId()) && item.getDeviceId().equals(deviceId)) {
                PrintStream printStream = new PrintStream(item.getSocket().getOutputStream());
                printStream.println(getFriend());
                break;
            }
        }
    }

    private void logout(String deviceId) throws IOException {
        for (int i=0; i<ChatServer.mSocketList.size(); i++) {
            SocketBean item = ChatServer.mSocketList.get(i);
            if (item.getId().equals(socketBean.getId()) && item.getDeviceId().equals(deviceId)) {
                PrintStream printStream = new PrintStream(item.getSocket().getOutputStream());
                printStream.println("LOGOUT,|");
                item.getSocket().close();
                ChatServer.mSocketList.remove(i);
                break;
            }
        }
    }

    private void sendmsg(String otherName, String otherId, String selfId, String message) throws IOException {
        for (int i=0; i<ChatServer.mSocketList.size(); i++) {
            SocketBean item = ChatServer.mSocketList.get(i);
            if (item.getDeviceId().equals(otherId)) {
                String content = String.format("%s,%s,%s|%s",
                        "RECVMSG", selfId, otherName, message);
                PrintStream printStream = new PrintStream(item.getSocket().getOutputStream());
                printStream.println(content);
                break;
            }
        }
    }
}
