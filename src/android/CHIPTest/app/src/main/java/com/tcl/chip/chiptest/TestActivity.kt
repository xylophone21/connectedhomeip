package com.tcl.chip.chiptest

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import chip.test.TestEngine
import com.tcl.chip.chiptest.databinding.ActivityTestBinding

class TestActivity : AppCompatActivity() {

    private lateinit var binding: ActivityTestBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityTestBinding.inflate(layoutInflater)
        setContentView(binding.root)

        TestEngine.setListener { log ->
            binding.testLog.append(log)
        }
        var testName = intent.getStringExtra(MainActivity.EXTRA_TEST_NAME);
        var ret = TestEngine.runTest(testName);
        if (ret == 0) {
            binding.testLog.append(getString(R.string.test_finished));
        } else {
            binding.testLog.append(getString(R.string.test_failed,ret));
        }
    }
}