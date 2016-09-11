uint32_t  LastTimerTick;

void setup() {
  pinMode(A2,INPUT_PULLUP);
  Serial.begin(57600);
  Serial.println("ok."); 
}

void loop() {
  ButtonState();
}

void ButtonState(){
  static int state = 0;
  uint32_t Ti;
  static uint32_t DoubleClickTick;
  
  switch(state){
    case 0:                                             // ボタン押下チェックstate
            if(digitalRead(A2) == 0){                   // プルアップされているので押下でL
              LastTimerTick = millis();                 // 押下時の時間セット
              state = 1;
            }
            break;
    case 1:                                             // ボタン離しチェックstate
            if(digitalRead(A2) == 1){                   // 立ち上がりを検出
              Ti = millis() - LastTimerTick;
              if(Ti >= 500 ){                           // 500ms超えた？
                Serial.println("long press!");          // 長押し確定
                state = 0;
              } else if(Ti >= 100){                     // シングルクリック仮確定
//              Serial.println("1:click!");
                DoubleClickTick =  millis();            // シングルクリック時の時間格納
                state = 2;
              }
            }
            break;
    case 2:                                             // ボタン押下チェックstate
          if(digitalRead(A2) == 0){                     // プルアップされているので押下でL
              LastTimerTick = millis();                 // 押下時の時間セット
              state = 3;
            }
            if( millis()-DoubleClickTick >= 500){       // シングルクリック確定
                Serial.println("click!!");
                state = 0;
            }
            break;
    case 3:                                             // ボタン離しチェックstate
            if(digitalRead(A2) == 1){                   // 立ち上がりを検出
              Ti = millis() - LastTimerTick;
              if(Ti >= 500 ){                           // 500ms超えた？
                Serial.println("long press!");          // シングルクリック->長押し確定
                state = 0;
              } else if(Ti >= 250){
                Ti = millis()-DoubleClickTick;
//              Serial.println(Ti,DEC);
                if( Ti <= 500){                         // シングルクリックから500ms以内だったら、ダブルクリック確定
                  Serial.println("Doble click!");
                  state = 0;
                } else {
                  Serial.println("2:click!");           // 
                  state = 0;                  
              }
            }
            break;
    default:
          break;
    }
  }            
}

