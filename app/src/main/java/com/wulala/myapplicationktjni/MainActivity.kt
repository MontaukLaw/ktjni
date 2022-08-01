package com.wulala.myapplicationktjni

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Column
import androidx.compose.material.Scaffold
import androidx.compose.material.Text
import com.wulala.myapplicationktjni.ui.theme.MyApplicationKTJniTheme

class MainActivity : ComponentActivity() {

    companion object {
        init {
            System.loadLibrary("udprev")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val textVal = stringFromJNI()
        setContent {
            MyApplicationKTJniTheme {
                Scaffold() {
                    Column() {
                        PlayerScreen(textVal)
                    }
                }
            }
        }
    }

    private external fun stringFromJNI(): String

}


