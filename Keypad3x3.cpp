/**
 * 入力キーを調べるプログラム
 * 3x3マトリクスの交差点を以下の対応付けで判別する
 *
 *     X  Y  Z
 *  A  1  2  3
 *  B  4  5  6
 *  C  7  8  9
 *
 */

#include "Keypad3x3.h"

/**
 * コンストラクタ
 * 仮引数A-Cの値を各_KEY_* 変数に割り当てる
 */
 
Keypad3x3::Keypad3x3(byte X,byte Y,byte Z,byte A,byte B,byte C) {
	_KEY_X = X;
	_KEY_Y = Y;
	_KEY_Z = Z;
	_KEY_A = A;
	_KEY_B = B;
	_KEY_C = C;
}

// ピンの設定
void Keypad3x3::Init(void)
{
    // X,Y,Z:制御信号  A,B,C:入力信号
	pinMode(_KEY_X, OUTPUT);
	pinMode(_KEY_Y, OUTPUT);
	pinMode(_KEY_Z, OUTPUT);
	pinMode(_KEY_A, INPUT);
	pinMode(_KEY_B, INPUT);
	pinMode(_KEY_C, INPUT);
    // 制御信号HIGH(プルアップ)
	digitalWrite(_KEY_X,1);
	digitalWrite(_KEY_Y,1);
	digitalWrite(_KEY_Z,1);
}


int Keypad3x3::getKey(void)
{
	byte xkey,ykey,zkey;
    // X列:LOW X列の入力を読む
	digitalWrite(_KEY_X,0);
	digitalWrite(_KEY_Y,1);
	digitalWrite(_KEY_Z,1);
    // C-Aの入力信号0/1を3bit(CBA)で保持
	xkey =  (digitalRead(_KEY_C)<<2)|
			(digitalRead(_KEY_B)<<1)|
			(digitalRead(_KEY_A)<<0);
	//Serial.println(xkey,HEX);

    // 以下Y列
	digitalWrite(_KEY_X,1);
	digitalWrite(_KEY_Y,0);
	digitalWrite(_KEY_Z,1);
	ykey = 	(digitalRead(_KEY_C)<<2)|
			(digitalRead(_KEY_B)<<1)|
			(digitalRead(_KEY_A)<<0);
	//Serial.println(ykey,HEX);

    // 以下Z列
	digitalWrite(_KEY_X,1);
	digitalWrite(_KEY_Y,1);
	digitalWrite(_KEY_Z,0);
	zkey = 	(digitalRead(_KEY_C)<<2)|
			(digitalRead(_KEY_B)<<1)|
			(digitalRead(_KEY_A)<<0);
	//Serial.println(zkey,HEX);

    /**
     * X-Z列の順でキー入力を読み、入力を発見したらint値を返して終了
     */
  
    // ButtonState 予めLOWにしておき、どのボタンも押されていなかった時 HIGH にする
  ButtonState = LOW;
  
    // X列
	if(xkey!=0x07) //111なら終了(入力なし)
	{
		if(xkey==0x06) //110
			return 1;
		else if(xkey==0x05) //101
			return 4;
		else if(xkey==0x03) //011
			return 7;
	}
    // Y列
	if(ykey!=0x07)
	{
		if(ykey==0x06) //110
			return 2;
		else if(ykey==0x05) //101
			return 5;
		else if(ykey==0x03) //011
			return 8;
	}
    // Z列
	if(zkey!=0x07)
	{
		if(zkey==0x06) //110
			return 3;
		else if(zkey==0x05) //101
			return 6;
		else if(zkey==0x03) //011
			return 9;
	}
	else {
    // どのボタンも押されていないため
    ButtonState = HIGH;
        // 入力ない場合0
		return 0;
  }
}

// getKey() の返り値と対応するchar型を返す
char Keypad3x3::getKeyChar(void)
{
  // getKey呼び出す(この際に ButtonState も更新される)
  int keyNumber = getKey();
  // keyNumber を cahr型に変換
  char keyChar = keyNumber + '0';

  // 電圧が HIGH->LOW(立ち下がり)の場合のみキーを返す
  if ((ButtonState != previousButtonState) && (ButtonState == LOW))
  {
    // previousButtonState の更新
    previousButtonState = ButtonState;
    // 入力されたキーを返す
    return keyChar;
  }
  else
  {
    // previousButtonState の更新
    previousButtonState = ButtonState;
    // NULL返す(同じキー押し続け or 入力なし)
    return '\0';    
  }

}