# M5IMU_Toy

M5StickC Plus2 用の IMU センサー可視化プログラム

## 機能

- **加速度センサー**：傾きに応じて赤い点が同心円上を移動
- **ジャイロセンサー**：3軸の角速度を画面三等分してバー表示
  - 上段: X軸（赤）
  - 中段: Y軸（緑）
  - 下段: Z軸（青）
- **WiFi + UDP 通信**：デバイスを素早く振ったとき（ジャイロ magnitude が閾値超過）に UDP パケットを送信

## 必要な環境

### ハードウェア
- M5StickC Plus2

### ライブラリ
- [M5Unified](https://github.com/m5stack/M5Unified) - M5Stack デバイス統合ライブラリ
- [M5GFX](https://github.com/m5stack/M5GFX) - グラフィックライブラリ（M5Unified に含まれる）

## インストール

### Arduino IDE の場合
1. ライブラリマネージャーから `M5Unified` をインストール
2. `config.h.template` を `config.h` にコピーして WiFi と UDP サーバー設定を記入
3. `M5IMU_Toy.ino` を開いてコンパイル・書き込み

その後、`config.h.template` → `config.h` にコピーして設定を記入

## 使い方

1. `config.h` で WiFi と UDP サーバー設定を行う
2. プログラムを書き込んで起動（WiFi 接続状態が画面に表示される）
3. デバイスを傾けると赤い点が移動
4. デバイスを回転させるとカラーバーが伸縮
5. デバイスを素早く振ると UDP サーバーに `{"magnitude":...}` JSON が送信される

## 設定（config.h）

```cpp
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define UDP_SERVER_IP "192.168.1.100"
#define UDP_SERVER_PORT 8888
#define GYRO_MAGNITUDE_THRESHOLD 200.0  // deg/s
```

## パラメータ調整

- `smoothFactor` (0.1～1.0): 点の追従速度（小さいほど滑らか）
- `gyroScale`: ジャイロバーのスケール
- `GYRO_MAGNITUDE_THRESHOLD`: UDP 送信する角速度の閾値（deg/s）
- `sendCooldown`: UDP 送信間隔（ms）

## セキュリティ

`config.h` は `.gitignore` に追加してコミットしないでください。共有には `config.h.template` を使用してください。
