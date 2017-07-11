package com.smaxz.chat_socket;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by huchao on 17-4-6.
 */
public class DataUtil {

    public static String getTimeId() {
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");
        return sdf.format(date);
    }

    public static String getNowTime() {
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("YYYYmmddHHmmss");
        return sdf.format(date);
    }
}
