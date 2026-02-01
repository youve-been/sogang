package com.example.whackamole;

import java.util.Random;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

public class WhackAMole extends Activity {

    static {
        System.loadLibrary("whack-a-mole"); // 네이티브 라이브러리 로드
    }

    public native void driverClose();
    public native int readSwitchInput(int curr); // 스위치 입력을 듣는 네이티브 메서드 선언
    public native void loseLife(int lives); // 목숨을 하나 잃었을 때 IO에 반영하는 네이티브 메서드 선언

    private ImageView[] imageViews;
    private Random random;
    private TextView timerTextView;
    private TextView scoreTextView;
    private TextView livesTextView;
    private long startTime;
    private Handler handler;
    private static final String TAG = "WhackAMole";

    private static final int TOTAL_TIME = 120; // 총 제한 시간 120초 (2분)
    private static final int INITIAL_SHOW_TIME = 1500; // 초기 두더지 표시 시간 1.5초
    private static final int TIME_DECREASE_INTERVAL = 20; // 20초마다 표시 시간 감소
    private static final int TIME_DECREASE_AMOUNT = 150; // 20초마다 0.15초씩 감소
    private static final int MIN_SHOW_TIME = 200; // 최소 두더지 표시 시간 0.2초

    private int currentScoreIncrement = 10; // 초기 점수 증가값 10
    private int currentShowTime = INITIAL_SHOW_TIME;
    private int currentMoleIndex = -1; // 현재 보이는 두더지의 인덱스
    private int score = 0;
    private int lives = 8; // 초기 목숨 개수 8개
    private Thread switchThread;
    private boolean moleHandled = false; // 두더지가 이미 잡혔는지 확인

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_whackamole);
        
        currentShowTime = INITIAL_SHOW_TIME;
        currentMoleIndex = -1;
        score = 0;
        lives = 8;
        moleHandled = false;

        imageViews = new ImageView[9];
        imageViews[0] = (ImageView) findViewById(R.id.imageView1);
        imageViews[1] = (ImageView) findViewById(R.id.imageView2);
        imageViews[2] = (ImageView) findViewById(R.id.imageView3);
        imageViews[3] = (ImageView) findViewById(R.id.imageView4);
        imageViews[4] = (ImageView) findViewById(R.id.imageView5);
        imageViews[5] = (ImageView) findViewById(R.id.imageView6);
        imageViews[6] = (ImageView) findViewById(R.id.imageView7);
        imageViews[7] = (ImageView) findViewById(R.id.imageView8);
        imageViews[8] = (ImageView) findViewById(R.id.imageView9);

        timerTextView = (TextView) findViewById(R.id.timer);
        scoreTextView = (TextView) findViewById(R.id.score); // 점수 텍스트뷰
        livesTextView = (TextView) findViewById(R.id.lives); // 남은 목숨 텍스트뷰

        // 초기 상태에서 모든 두더지를 숨기기
        for (ImageView imageView : imageViews) {
            imageView.setImageResource(R.drawable.hole);
        }

        random = new Random();
        startTime = System.currentTimeMillis();

        handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                if (msg.what == 0) {
                    updateMole();
                } else if (msg.what == 1) {
                    updateTimer();
                } else if (msg.what == 2) {
                    int switchState = msg.arg1;
                    Log.d(TAG, "Switch state: " + switchState);
                    // 스위치 상태에 따른 처리 추가
                    if (!moleHandled) {
                        if (switchState == 1) { // correct
                        	score += currentScoreIncrement;
                            scoreTextView.setText("Score: " + score);
                            moleHandled = true; // 처리된 것으로 표시
                            // 두더지 이미지를 boom.png로 변경
                            if (currentMoleIndex != -1) {
                                imageViews[currentMoleIndex].setImageResource(R.drawable.boom);
                            }
                        } else if (switchState == 0) { // wrong
                            lives--; // 목숨 감소
                            livesTextView.setText("Lives: " + lives); // 화면에 목숨 업데이트
                            moleHandled = true;
                            loseLife(lives);
                         // 두더지 이미지를 wrong.png로 변경
                            if (currentMoleIndex != -1) {
                                imageViews[currentMoleIndex].setImageResource(R.drawable.wrong);
                            }
                            if (lives <= 0) {
                                gameOver("lives"); // 목숨이 0으로 게임 종료
                            }
                        }
                    }
                }
            }
        };

        // 두더지와 타이머 업데이트 시작
        handler.sendEmptyMessage(0);
        handler.sendEmptyMessage(1);

        // 스위치 입력을 듣는 백그라운드 스레드 시작
        switchThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while (!Thread.currentThread().isInterrupted()) {
                    int correct = readSwitchInput(currentMoleIndex);
                    Message msg = handler.obtainMessage(2);
                    msg.arg1 = correct;
                    Log.d(TAG, "correct = " + correct);
                    handler.sendMessage(msg);
                    try {
                        Thread.sleep(50); // 0.05초마다 스위치 상태 확인
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt(); // 스레드가 인터럽트되면 루프 종료
                    }
                }
            }
        });
        switchThread.start();
    }

    private void updateMole() {
        long elapsedTime = (System.currentTimeMillis() - startTime) / 1000;
        if (elapsedTime >= TOTAL_TIME) {
            // 게임 종료
            for (ImageView imageView : imageViews) {
                imageView.setImageResource(R.drawable.hole);
            }
            gameOver("time"); // 시간 초과로 게임 종료
            return;
        }

        // 모든 두더지를 숨기기
        for (ImageView imageView : imageViews) {
            imageView.setImageResource(R.drawable.hole);
        }

        // 랜덤으로 보일 두더지를 결정
        currentMoleIndex = random.nextInt(imageViews.length);
        imageViews[currentMoleIndex].setImageResource(R.drawable.mole);

        // moleHandled 초기화
        moleHandled = false;

        // 두더지 표시 시간을 계산
        int previousShowTime = currentShowTime; // 이전 표시 시간 저장
        currentShowTime = INITIAL_SHOW_TIME - (int) (elapsedTime / TIME_DECREASE_INTERVAL) * TIME_DECREASE_AMOUNT;
        if (currentShowTime < MIN_SHOW_TIME) {
            currentShowTime = MIN_SHOW_TIME;
        }
        
     // currentScoreIncrement를 업데이트
        currentScoreIncrement = 10 + (int)(elapsedTime / TIME_DECREASE_INTERVAL) * 2;

        // currentShowTime이 변경될 때마다 로그 남기기
        if (currentShowTime != previousShowTime) {
            Log.d(TAG, "Current show time updated: " + currentShowTime + "ms");
        }

        // 다음 두더지 표시 시간 예약
        handler.sendEmptyMessageDelayed(0, currentShowTime);
    }

    private void updateTimer() {
        long elapsedTime = (System.currentTimeMillis() - startTime) / 1000;
        long remainingTime = TOTAL_TIME - elapsedTime;
        if (remainingTime >= 0) {
            long minutes = remainingTime / 60;
            long seconds = remainingTime % 60;
            timerTextView.setText(String.format("Timer: %02d:%02d", minutes, seconds));
            handler.sendEmptyMessageDelayed(1, 1000);
        } else {
            gameOver("time"); // 시간 초과로 게임 종료
        }
    }

    private void gameOver(String reason) {
        handler.removeMessages(0); // 두더지 타이머 중지
        handler.removeMessages(1); // 타이머 업데이트 중지
        if (switchThread != null && switchThread.isAlive()) {
            switchThread.interrupt();
        }

        Intent intent = new Intent(WhackAMole.this, GameOver.class);
        intent.putExtra("message", reason.equals("lives") ? "Game Over" : "Time's Up!");
        intent.putExtra("score", score);
        startActivity(intent);
        finish(); // 현재 액티비티를 종료하여 뒤로가기 버튼이 게임 중 액티비티로 돌아가지 않게 함
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        handler.removeMessages(0);
        handler.removeMessages(1);
        if (switchThread != null && switchThread.isAlive()) {
            switchThread.interrupt();
        }
    }
}
