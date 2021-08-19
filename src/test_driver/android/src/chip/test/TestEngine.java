package chip.test;

import android.content.Context;
import android.util.Log;

import java.util.Arrays;
import java.util.List;

public class TestEngine {
    static private final String TAG = TestEngine.class.getSimpleName();
    private static String mlibDir;
    private static TestListener mListener;

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
        return null;
    }

    public static int runTest(String name) {
        return nativeRunTest(name);
    }

    private static void onTestLog(String log) {
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