package com.example.whackamole;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Start extends Activity {

    // 네이티브 메서드 선언
    public native int driverOpen();

    static {
        System.loadLibrary("whack-a-mole"); // 네이티브 라이브러리 로드
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start);
        
        Button startButton = (Button) findViewById(R.id.start_button);
        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 네이티브 메서드 호출
                driverOpen();
                
                // WhackAMole 액티비티 시작
                Intent intent = new Intent(Start.this, WhackAMole.class);
                startActivity(intent);
                finish();
            }
        });
    }
}
