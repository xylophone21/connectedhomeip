package com.tcl.chip.chiptvserver;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class AppUtils {

    /**
     * 获取wifi模块mac地址
     *
     * @return
     */
    public static String getWlanMacAddr() {
        String wifiAddress = "02:00:00:00:00:00";
        try {
            FileReader fileReader = new FileReader("/sys/class/net/wlan0/address");
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            wifiAddress = bufferedReader.readLine();

            //拿不到mac再去获取有线mac
            if (!BaseUtils.isValidString(wifiAddress) || "null".equalsIgnoreCase(wifiAddress)) {
                wifiAddress = getMacAddress();
            }
            wifiAddress.trim();

        } catch (IOException e) {
            e.printStackTrace();
            wifiAddress = getMacAddress();
        }
        return wifiAddress.toUpperCase();
    }

    /**
     * TV端获取mac
     */
    public static String getMacAddress() {
        String strMacAddr = "";
        try {
            FileReader localFileReader = new FileReader("/sys/class/net/eth0/address");
            BufferedReader localBufferedReader = new BufferedReader(localFileReader);
            strMacAddr = localBufferedReader.readLine();
            if (strMacAddr == null || "null".equalsIgnoreCase(strMacAddr)) {
                strMacAddr = "";
            }
            if (!"".equals(strMacAddr)) {
                strMacAddr = strMacAddr.trim();
                strMacAddr = strMacAddr.replace(".", ":").toUpperCase();
            }
            localBufferedReader.close();
            localFileReader.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            // write log
        } catch (IOException e) {
            e.printStackTrace();
            // write log
        }
        return strMacAddr;
    }
}
