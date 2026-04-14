#include "main.h"

/*
 * この CubeMX/HAL プロジェクトには USB PCD までは入っていますが、
 * USB DEVICE CDC middleware はまだ追加されていません。
 * そのため Arduino 版のような USB CDC echo はこのままでは移植できません。
 *
 * CubeMX で USB_DEVICE / Communication Device Class (Virtual Port Com) を追加してから、
 * ここに CDC 送受信コードを書く想定です。
 */

extern "C" void setup(void) {}

extern "C" void loop(void) {}
