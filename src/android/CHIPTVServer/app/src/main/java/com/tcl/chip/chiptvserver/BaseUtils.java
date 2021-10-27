package com.tcl.chip.chiptvserver;

import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BaseUtils {

    /*-------------单例实现 开始--------------*/
    private static class SingletonBaseUtil {

        static final BaseUtils SingletonBU = new BaseUtils();
    }

    public static BaseUtils getInstance() {
        // setParameters(BaseActivity.getContext());
        return SingletonBaseUtil.SingletonBU;
    }

    private BaseUtils() {
        super();
    }

    /*-------------单例实现 结束--------------*/

    public static boolean isTrue(int x) {
        if (x == 1) {
            return true;
        }
        return false;
    }

    public static boolean isTrue(String string) {
        if (isValidString(string) == false) {
            return false;
        }
        if ("1".equals(string) || "true".equals(string)
                || "yes".equalsIgnoreCase(string)) {
            return true;
        }
        return false;
    }

    /**
     * @param str 需要验证的字符串
     * @return 是否有效字符串排除null或者“”型
     */
    public static boolean isValidString(String str) {
        if (str == null) {
            return false;
        }
        String str1 = str.trim();
        return (!"".equals(str1) &&
                !"NULL".equalsIgnoreCase(str1) &&
                !"null".equalsIgnoreCase(str1) &&
                !"undefined".equalsIgnoreCase(str1));
    }

    public static boolean isValidData(String str) {
        return isValidString(str);
    }

    public static boolean isValidData(List<? extends Object> list) {
        return isValidList(list);
    }

    public static boolean isValidData(
            Map<? extends Object, ? extends Object> map) {
        return isValidMap(map);
    }

    /**
     * @param list
     * @return list是否有效
     */
    public static boolean isValidList(List<? extends Object> list) {
        if (list == null) {
            return false;
        }
        if (list.size() > 0) {
            return true;
        }
        return false;
    }

    /**
     * @param map
     * @return map是否有效
     */
    public static boolean isValidMap(Map<? extends Object, ? extends Object> map) {
        if (map == null) {
            return false;
        }
        if (map.size() > 0) {
            return true;
        }
        return false;
    }

    /**
     * @discription 杀死当前进程
     */
    public void killMyProcess() {

        android.os.Process.killProcess(android.os.Process.myPid());
    }

    /**
     * @param str
     * @return 是否有特殊字符，ture：是有特殊字符
     */
    public static boolean CheckSpecialCharacter(String str) {
        // String str = "/";
        String regEx = "[`~!@#$%^&*()+=|{}':;',\\[\\].<>/?~！@#￥%……&*（）——+|{}【】‘；：”“’。，、？]";
        Pattern p = Pattern.compile(regEx);
        Matcher m = p.matcher(str);
        if (m != null && m.find()) {
            return true;
        }
        return false;
    }

}
