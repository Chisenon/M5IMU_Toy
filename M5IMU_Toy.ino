#include <M5Unified.h>
#include <math.h>

static auto &dsp = (M5.Display);
static LGFX_Sprite sprite(&M5.Display);

// visualization parameters
const int R1 = 20, R2 = 40, R3 = 60;
const int X0 = 120, Y0 = 67;

// smoothing
float smoothPx = X0, smoothPy = Y0;
const float smoothFactor = 0.3f;

// gyro bar colors (X, Y, Z)
static constexpr uint32_t gyro_colors[3] = {0xFF0000u, 0x00FF00u, 0x0000FFu};

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  dsp.setRotation(3);
  dsp.fillScreen(TFT_BLACK);
  sprite.setColorDepth(16);
  sprite.createSprite(dsp.width(), dsp.height());
  sprite.setTextSize(2);
  sprite.setTextColor(TFT_WHITE, TFT_BLACK);
}

// draw a horizontal bar from center (ox). positive -> right, negative -> left
void drawBar(LGFX_Sprite &spr, int32_t ox, int32_t oy, int32_t barValue, int32_t h, uint32_t color)
{
  if (barValue > 0)
  {
    spr.fillRect(ox, oy, barValue, h, color);
  }
  else if (barValue < 0)
  {
    spr.fillRect(ox + barValue, oy, -barValue, h, color);
  }
}

// main loop: read IMU and render (gyro bars background + accel dot)
void loop()
{
  if (M5.Imu.update())
  {
    auto data = M5.Imu.getImuData();
    float ax = data.accel.x;
    float ay = data.accel.y;
    float az = data.accel.z;
    float gx = data.gyro.x;
    float gy = data.gyro.y;
    float gz = data.gyro.z;
    if (!isfinite(ax) || !isfinite(ay) || !isfinite(az))
      return;

    float targetPx = X0 - ay * R3;
    float targetPy = Y0 - ax * R3;
    smoothPx += (targetPx - smoothPx) * smoothFactor;
    smoothPy += (targetPy - smoothPy) * smoothFactor;
    int px = (int)smoothPx;
    int py = (int)smoothPy;

    sprite.fillScreen(TFT_BLACK);

    int screenW = sprite.width();
    int screenH = sprite.height();
    int barHeight = screenH / 3;
    int centerX = screenW / 2;
    float gyroScale = screenW / 512.0f;
    int gx_pos = (int)(gx * gyroScale);
    int gy_pos = (int)(gy * gyroScale);
    int gz_pos = (int)(gz * gyroScale);

    drawBar(sprite, centerX, 0, gx_pos, barHeight - 2, gyro_colors[0]);
    drawBar(sprite, centerX, barHeight, gy_pos, barHeight - 2, gyro_colors[1]);
    drawBar(sprite, centerX, barHeight * 2, gz_pos, barHeight - 2, gyro_colors[2]);

    sprite.drawLine(centerX, 0, centerX, screenH, TFT_DARKGREY);
    sprite.drawLine(0, barHeight, screenW, barHeight, TFT_DARKGREY);
    sprite.drawLine(0, barHeight * 2, screenW, barHeight * 2, TFT_DARKGREY);

    sprite.drawCircle(X0, Y0, R1, TFT_WHITE);
    sprite.drawCircle(X0, Y0, R2, TFT_WHITE);
    sprite.drawCircle(X0, Y0, R3, TFT_WHITE);
    sprite.drawLine(X0 - R3 - 10, Y0, X0 + R3 + 10, Y0, TFT_WHITE);
    sprite.drawLine(X0, Y0 - R3 - 5, X0, Y0 + R3 + 5, TFT_WHITE);

    sprite.setCursor(0, 5);
    sprite.setTextSize(1);
    sprite.printf("gx:%6.1f\ngy:%6.1f\ngz:%6.1f", gx, gy, gz);
    sprite.setTextSize(2);

    sprite.fillCircle(px, py, 8, TFT_RED);
    sprite.pushSprite(0, 0);
  }

  M5.update();
  if (M5.BtnA.wasClicked())
  {
    // calibration placeholder
  }

  delay(10);
}