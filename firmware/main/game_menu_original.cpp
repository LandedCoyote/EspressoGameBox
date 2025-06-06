#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <vector>

#define SD_CS 15       // SDカード CS（黄）
#define TFT_CS 5       // ILI9341 CS（黄）
#define TFT_DC 2       // ILI9341 DC（白）
#define TFT_RST 4      // ILI9341 RESET（緑）

#define BUTTON_LEFT   25  // 白
#define BUTTON_RIGHT  26  // 白
#define BUTTON_SELECT 27  // A ボタン（黄）

#define ICON_WIDTH 64
#define ICON_HEIGHT 64
#define ICON_SPACING 10

TFT_eSPI tft = TFT_eSPI();
std::vector<String> gameNames;
std::vector<String> iconPaths;
int selected = 0;

// BMPアイコン表示（BMPは24bit非圧縮）
void drawIcon(const String& path, int x, int y, bool highlight) {
  if (!SD.exists(path)) return;
  tft.drawBmp(path.c_str(), x, y);
  if (highlight) {
    tft.drawRect(x - 2, y - 2, ICON_WIDTH + 4, ICON_HEIGHT + 4, TFT_YELLOW);
  }
}

// ゲーム情報の読み込み
void loadGames() {
  File dir = SD.open("/games");
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    if (entry.isDirectory()) {
      String name = entry.name();
      gameNames.push_back(name);
      iconPaths.push_back("/games/" + name + "/icon.bmp");
    }
    entry.close();
  }
}

// ホーム画面描画
void drawHome() {
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < gameNames.size(); ++i) {
    int x = 10 + i * (ICON_WIDTH + ICON_SPACING);
    drawIcon(iconPaths[i], x, 80, i == selected);
  }
}

// 選択更新
void updateSelection(int dir) {
  selected += dir;
  if (selected < 0) selected = 0;
  if (selected >= gameNames.size()) selected = gameNames.size() - 1;
  drawHome();
}

// 入力状態の取得
bool isPressed(int gpio) {
  return digitalRead(gpio) == LOW;
}

// 初期化処理
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  tft.init();
  tft.setRotation(1);
  if (!SD.begin(SD_CS)) {
    tft.println("SD init failed!");
    return;
  }

  loadGames();
  drawHome();
}

// メインループ（簡易入力）
void loop() {
  static uint32_t lastInput = 0;
  if (millis() - lastInput > 200) { // デバウンス
    if (isPressed(BUTTON_LEFT)) {
      updateSelection(-1);
      lastInput = millis();
    } else if (isPressed(BUTTON_RIGHT)) {
      updateSelection(1);
      lastInput = millis();
    } else if (isPressed(BUTTON_SELECT)) {
      tft.fillScreen(TFT_BLACK);
      tft.setTextDatum(MC_DATUM);
      tft.drawString("Launching " + gameNames[selected], 160, 120);
      delay(1000);
      // TODO: 実際のゲーム起動処理
    }
  }
}
