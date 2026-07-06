// ============================================================
//  Serpent.ino
//  PERINGATAN: Nama file ini HARUS "Serpent.ino", jangan diubah
// ------------------------------------------------------------
//  DEVELOPER : SERPENTSECHUNTER
//  VERSI     : 0.1
//  RILIS     : 07-07-2026
//  LICENSE   : All rights reserved © 2026 SERPENTSECHUNTER
// ============================================================

#include <DFRobotDFPlayerMini.h>

// ================== WIRING ==================
// DFPlayer VCC -> VU
// DFPlayer GND -> G
// DFPlayer RX  -> TX NodeMCU
// DFPlayer TX  -> RX NodeMCU
// PENTING: Cabut kabel RX/TX DFPlayer setiap mau upload!
// ============================================
// CARA ISI SD CARD:
// Taruh file mp3 langsung di root SD card
// Nama file: 0001.mp3, 0002.mp3, 0003.mp3, dst
// ============================================

DFRobotDFPlayerMini myDFPlayer;
int totalLagu = 0;
int laguSekarang = 1;

void setup() {
  Serial.begin(9600);
  delay(3000);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  int retry = 0;
  bool ok = false;
  while (retry < 3 && !ok) {
    ok = myDFPlayer.begin(Serial, /*isACK=*/true, /*doReset=*/true);
    if (!ok) {
      retry++;
      delay(1000);
    }
  }

  if (!ok) {
    while (true) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
    }
  }

  digitalWrite(LED_BUILTIN, LOW);

  totalLagu = myDFPlayer.readFileCounts();
  if (totalLagu <= 0) totalLagu = 1;

  myDFPlayer.volume(20);
  myDFPlayer.play(laguSekarang);
}

void loop() {
  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();

    if (type == DFPlayerPlayFinished) {
      laguSekarang++;
      if (laguSekarang > totalLagu) {
        laguSekarang = 1;
      }
      myDFPlayer.play(laguSekarang);
    }
  }
}
