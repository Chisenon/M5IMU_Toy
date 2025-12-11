# M5IMU_Toy

M5StickC Plus2 用の IMU センサー可視化プログラム

## 機能

- **加速度センサー**：傾きに応じて赤い点が同心円上を移動
- **ジャイロセンサー**：3軸の角速度を画面三等分してバー表示
  - 上段: X軸（赤）
  - 中段: Y軸（緑）
  - 下段: Z軸（青）

## 必要な環境

### ハードウェア
- M5StickC Plus2

### ライブラリ
- [M5Unified](https://github.com/m5stack/M5Unified) - M5Stack デバイス統合ライブラリ
- [M5GFX](https://github.com/m5stack/M5GFX) - グラフィックライブラリ（M5Unified に含まれる）

## インストール

### Arduino IDE の場合
1. ライブラリマネージャーから `M5Unified` をインストール
2. `M5IMU_Toy.ino` を開いてコンパイル・書き込み

## 使い方

1. プログラムを書き込んで起動
2. デバイスを傾けると赤い点が移動
3. デバイスを回転させるとカラーバーが伸縮

## パラメータ調整

- `smoothFactor` (0.1～1.0): 点の追従速度（小さいほど滑らか）
- `gyroScale`: ジャイロバーのスケール
