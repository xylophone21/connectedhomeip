package chip.test;

import android.content.Context;
import android.util.Log;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.StringJoiner;
import java.util.regex.Pattern;

public class TestEngine {
    static private final String TAG = TestEngine.class.getSimpleName();
    static private String mlibDir;
    static private TestListener mListener;

    public interface TestListener {
        void onTestLog(String log);
    }

    public static void setContext(Context ctx) {
        mlibDir = ctx.getApplicationInfo().nativeLibraryDir;
    }

    public static void setListener(TestListener listener) {
        mListener = listener;
    }

    public static List<String> getTestList() {
        if (mlibDir == null) {
            return null;
        }

        String pattern = ".*Test.+\\.so";
        Pattern reg = Pattern.compile(pattern);

        List<String> list = new ArrayList<String>();
        File[] fileList = new File(mlibDir).listFiles();
        for (int i=0;i<fileList.length;i++) {
            File file = fileList[i];
            String filename = file.getName();

            if(file.isFile() && reg.matcher(filename).matches()) {
                list.add(filename);
            }
        }

        return list;
    }

    public static int runTest(String name) {
        File testFile = new File(mlibDir, name);
        if (testFile.exists()) {
            return nativeRunTest(testFile.toString());
        } else {
            return -1;
        }
    }

    public static void onTestLog(String log) {
        Log.i(TAG, log);
        if (mListener != null) {
            mListener.onTestLog(log);
        }
    }

    private static native int nativeRunTest(String testFile);

    static {
        System.loadLibrary("CHIPTest");
    }
}