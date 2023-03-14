#include <Arduino.h>
#include "Keypad3x3.h"

//----------------------------------------//
// keypad3x3   -------    Pro Micro       //
//                                        //
//   |>        <------       5.0V         //
//   X         ------>       7            //
//   Y         ------>       6            //
//   Z         ------>       5            //
//   A         <------       4            //
//   B         <------       3            //
//   C         <------       2            //
//----------------------------------------//

// 上記に対応するポート番号で初期化
Keypad3x3 keypad = Keypad3x3(7,6,5,4,3,2);

void setup() {
  Serial.begin(9600);
  Serial.println("Keypad3x3 Test");

  // 各入力信号,制御信号の設定
  keypad.Init();
}

// キー入力の取得
void loop() {
  char key_type;
  // 入力キーの取得
  key_type = keypad.getKeyChar();
  // 表示
  Serial.print(key_type);
  delay(100);
}
