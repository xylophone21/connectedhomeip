package com.tcl.chip.chiptest

import android.content.Intent
import android.os.Bundle
import android.widget.ArrayAdapter
import androidx.appcompat.app.AppCompatActivity
import chip.test.TestEngine
import com.tcl.chip.chiptest.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        TestEngine.setContext(this);
        var testList = TestEngine.getTestList();

        var adapter = ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,testList);
        binding.testList.adapter = adapter;
        binding.testList.setOnItemClickListener{_, _, position, _ ->
            var filename = testList[position]

            var intent = Intent(this, TestActivity::class.java)
            intent.putExtra(EXTRA_TEST_NAME, filename);

            startActivity(intent);
        }
    }

    companion object {
        const val EXTRA_TEST_NAME = "test_name"
    }
}
