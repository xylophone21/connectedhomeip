package com.tcl.chip.chiptest

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import chip.test.TestEngine
import com.tcl.chip.chiptest.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        TestEngine.getTestList();
        TestEngine.runTest("hello");
    }
}