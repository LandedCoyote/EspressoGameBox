#include <TFT_eSPI.h>
#include <SPI.h>
#include <SD.h>
#include <vector>

// GPIO definitions
constexpr int SD_CS        = 15; // SD card CS
constexpr int TFT_CS       = 5;  // ILI9341 CS
constexpr int TFT_DC       = 2;  // ILI9341 DC
constexpr int TFT_RST      = 4;  // ILI9341 RESET

constexpr int BUTTON_LEFT  = 25;
constexpr int BUTTON_RIGHT = 26;
constexpr int BUTTON_SELECT= 27; // A button

// Layout constants
constexpr int ICON_WIDTH   = 64;
constexpr int ICON_HEIGHT  = 64;
constexpr int ICON_SPACING = 10;
constexpr uint32_t DEBOUNCE_MS = 200;

struct GameEntry {
  String name;
  String iconPath;
};

TFT_eSPI tft = TFT_eSPI();
std::vector<GameEntry> games;
size_t selected = 0;

// Draw 24bit BMP icon and optional highlight
static void drawIcon(const String& path, int x, int y, bool highlight) {
  if (!SD.exists(path)) return;
  tft.drawBmp(path.c_str(), x, y);
  if (highlight) {
    tft.drawRect(x - 2, y - 2, ICON_WIDTH + 4, ICON_HEIGHT + 4, TFT_YELLOW);
  }
}

// Scan /games directory and populate game list
static void loadGames() {
  File dir = SD.open("/games");
  if (!dir) return;
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;
    if (entry.isDirectory()) {
      GameEntry g;
      g.name = entry.name();
      g.iconPath = String("/games/") + g.name + "/icon.bmp";
      games.push_back(g);
    }
    entry.close();
  }
}

// Render home screen with all icons
static void drawHome() {
  tft.fillScreen(TFT_BLACK);
  for (size_t i = 0; i < games.size(); ++i) {
    int x = 10 + i * (ICON_WIDTH + ICON_SPACING);
    drawIcon(games[i].iconPath, x, 80, i == selected);
  }
}

// Update selection with wrap-around
static void updateSelection(int dir) {
  if (games.empty()) return;
  selected = (selected + dir + games.size()) % games.size();
  drawHome();
}

inline bool isPressed(int pin) {
  return digitalRead(pin) == LOW;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_LEFT,   INPUT_PULLUP);
  pinMode(BUTTON_RIGHT,  INPUT_PULLUP);
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

void loop() {
  static uint32_t lastInput = 0;
  uint32_t now = millis();
  if (now - lastInput > DEBOUNCE_MS) {
    if (isPressed(BUTTON_LEFT)) {
      updateSelection(-1);
      lastInput = now;
    } else if (isPressed(BUTTON_RIGHT)) {
      updateSelection(1);
      lastInput = now;
    } else if (isPressed(BUTTON_SELECT)) {
      tft.fillScreen(TFT_BLACK);
      tft.setTextDatum(MC_DATUM);
      tft.drawString("Launching " + games[selected].name, 160, 120);
      delay(1000);
      // TODO: add real game launch logic here
    }
  }
}
