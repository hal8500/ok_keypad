# 仕様

マクロ一覧管理画面
マクロはnameを一意のキーにして管理する
マクロはlocalstorageを利用して、接続したPCのブラウザに保管できる
保存ボタンを押したときだけ

keypadの各ボタンには単純な文字列か、マクロ一覧のマクロを割り当てる

keypadに割り当てられているマクロはマクロ一覧と同期している”同期マクロ”とそうでない”非同期マクロ”の２状態とする。
接続時にはすべて非同期マクロで、非同期マクロを取り込んでマクロ一覧に追加するか、マクロ一覧からボタンに割り当てることで同期マクロになる。

メイン画面
    マクロ一覧
    keypad接続
    keypadボタン設定
        非同期マクロ
            取り込み
            割当
        同期マクロ
            編集
            割当

マクロ編集画面　（ダイアログ形式）
    複製
    項目の編集
    actionsの追加、並び替え、削除

エディター
<https://www.codelantis.com/blog/sveltekit-monaco-editor>

## 参考サイト

[Arduino日本語リファレンス](http://www.musashinodenpa.com/arduino/ref/)

[Keypad Example](https://github.com/Chris--A/Keypad/tree/master/examples)

[ゼロから学ぶ C++](https://rinatz.github.io/cpp-book/)

[c++で動的に配列を作成する](https://forum.arduino.cc/t/set-size-of-member-array-at-runtime/1106318/5)

[Arduino json](https://github.com/arduino-libraries/Arduino_JSON)