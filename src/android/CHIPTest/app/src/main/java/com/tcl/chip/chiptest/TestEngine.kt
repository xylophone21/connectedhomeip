package com.tcl.chip.chiptest

class TestEngine {

    external fun getTestList(): String
    external fun runTest(name: String): String
}