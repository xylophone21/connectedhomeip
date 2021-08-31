package com.tcl.chip.chiptest

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import chip.platform.AndroidBLEManager
import chip.platform.AndroidChipPlatform
import chip.platform.PreferencesKeyValueStoreManager
import com.tcl.chip.chiptest.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        TestEngine.setListener { log ->
            binding.testLog.append(log)
        }

        binding.runButton.setOnClickListener {
            var ret = TestEngine.runTest();
            if (ret == 0) {
                binding.testLog.append(getString(R.string.test_finished));
            } else {
                binding.testLog.append(getString(R.string.test_failed,ret));
            }
        }

        AndroidChipPlatform.getInstance().bleManager = AndroidBLEManager();
        AndroidChipPlatform.getInstance().setKeyValueStoreManager(PreferencesKeyValueStoreManager(this));
    }
}
