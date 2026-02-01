package com.example.whackamole;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class GameOver extends Activity {

    static {
        System.loadLibrary("whack-a-mole"); // 네이티브 라이브러리 로드
    }

    public native void gameOver(int score);
    public native void driverClose();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gameover);

        // Intent 데이터 확인
        Intent intent = getIntent();
        String message = intent.getStringExtra("message");
        int score = intent.getIntExtra("score", 0);

        // Null 체크 추가
        if (message == null) {
            message = "Game Over";
        }

        TextView messageTextView = (TextView) findViewById(R.id.message_text_view);
        TextView scoreTextView = (TextView) findViewById(R.id.score_text_view);
        messageTextView.setText(message);
        scoreTextView.setText("Total Score: " + score);

        Button restartButton = (Button) findViewById(R.id.restart_button);
        Button exitButton = (Button) findViewById(R.id.exit_button);

        // 네이티브 메서드 호출 전에 예외 처리 추가
        try {
            gameOver(score);
        } catch (Exception e) {
            e.printStackTrace();
        }

        restartButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent restartIntent = new Intent(GameOver.this, Start.class);
                startActivity(restartIntent);
                try {
                    driverClose();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                finish();
            }
        });

        exitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    driverClose();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                finish();
            }
        });
    }
}
