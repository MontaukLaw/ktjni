package com.wulala.myapplicationktjni

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material.Button
import androidx.compose.material.Card
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

@Composable
fun PlayerScreen(text:String) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp),
        elevation = 8.dp
    ) {
        Box(modifier = Modifier.padding(16.dp)) {
            Column() {
                Text(text)

                Button(onClick = {

                }) {
                    Text("点我")
                }
                Text("Text 112")
            }
        }
    }
}