package com.wulala.myapplicationktjni

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Column
import androidx.compose.material.Button
import androidx.compose.material.Scaffold
import androidx.compose.material.Text
import androidx.compose.runtime.*
import com.wulala.myapplicationktjni.ui.theme.MyApplicationKTJniTheme

class MainActivity : ComponentActivity() {

    private val TAG = MainActivity.javaClass.simpleName
    companion object {
        init {
            System.loadLibrary("udprev")
        }
    }

    var textVal = stringFromJNI()
    //var text2 = String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {

            var text2 by remember { mutableStateOf("abcd") }

            MyApplicationKTJniTheme {
                Scaffold() {
                    Column() {
                        PlayerScreen(textVal)

                        Text(text2)

                        Button(onClick = {
                            changeTextThreadStart()
                            changeText("start")
                        }) {
                            Text("开启C子线程")
                            //
                        }
                    }
                }
            }
        }
    }

    private fun changeText(newVal: String) {
        Log.d(TAG, "changeText: " + newVal)
    }

    private external fun changeTextThreadStart()
    private external fun stringFromJNI(): String

}


