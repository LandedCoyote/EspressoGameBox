# CLAUDE.md — EspressoGameBox

次の作業は `docs/BACKLOG.md`。

## 目的

ESP32-WROOM-32E と ILI9341 の TFT、タクトスイッチ、SD カードで作る携帯ゲーム機（README による）。メニュー OS をフラッシュに置き、ゲームのバイナリを SD カードの `/games/` から読み込む構想。

## 現状（重要）

**このリポジトリにあるのは `README.md` だけ**（コミット2件、2025-05-10）。README が説明する `firmware/`、`games/`、`hardware/`、`docs/`、`LICENSE`、`CONTRIBUTING.md` はどれも存在しない。

README の「Project Status」には「プロトタイプが起動して SD の一覧を出す」「ILI9341 の独自 SPI ドライバと DMA 転送」が ✅ とあるが、**そのコードはこのリポジトリに無く、確認できない**。コードが別の場所にあるのか、まだ無いのかは作者に確認する（BACKLOG #1）。README の記述を事実として扱わない。

## ハード構成（README の計画）

| 部品 | 内容 |
|---|---|
| MCU | ESP32-WROOM-32E |
| 表示 | 2.4〜2.8インチ ILI9341 TFT、SPI 40MHz、320×240 |
| 記憶 | microSD（FAT32） |
| 入力 | 十字キー4個＋ボタン2個（プルアップ） |
| 音 | 8Ω スピーカー（DAC または PWM＋RC フィルタ。未着手） |
| 電源 | Li-ion 3.7V を 5V に昇圧、または USB-C 5V |

配線（ピン割り当て）と回路図は無い。

## ビルド・書き込み・実行

README の手順（ESP-IDF 5.x、`idf.py menuconfig`、`idf.py flash monitor`）は **未検証**。そもそもビルドするソースが無く、desk には ESP-IDF も無い（2026-11-17 確認）。README 自身も「手順は作成中」と書いている。

## ディレクトリ構成

```
README.md    構想の説明（英語）
docs/        BACKLOG.md（この引き継ぎで追加）
```

## 規約（README から）

- README は英語。コミットメッセージも英語を推奨と書いてある。
- ライセンスは「MIT + 帰属表示」と README にあるが、`LICENSE` ファイルは無い。

## 既知の問題

- README と実体が一致しない（上記）。
- README のバッジと本文が `LICENSE` にリンクしているが、リンク先が無い。
- clone の URL が `https://github.com/<your-github>/EspressoGameBox.git` と仮のまま。
- 「Arduino-ESP32 core ≥ 3.0 will be supported later」など、根拠のコードが無い記述がある。

## 触ってはいけない箇所

- README の「ライセンス」の条件（帰属表示）を、作者の確認なしに変えない。
- README の Project Status を、コードを確認せずに「完了」のまま引き写さない。
