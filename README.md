# 🎵 Serpent-MP3-Player

> Pemutar MP3 otomatis berbasis ESP8266 NodeMCU + DFPlayer Mini, tanpa layar, tanpa tombol — cukup nyalakan, langsung memutar semua lagu dari SD card secara berurutan dan looping otomatis.

---

## 👤 Informasi Project

| | |
|---|---|
| **Developer** | SERPENTSECHUNTER |
| **Versi** | 0.1 |
| **Rilis** | 07-07-2026 |
| **Platform** | ESP8266 NodeMCU (Generic ESP8285 Module) |
| **Bahasa** | C++ (Arduino Framework) |
| **Repo** | [github.com/SerpentSecHunter2006/Serpent-MP3-Player](https://github.com/SerpentSecHunter2006/Serpent-MP3-Player) |

---

## 📦 Alat & Modul yang Dibutuhkan

| No | Nama Modul/Alat | Fungsi & Kegunaan |
|---|---|---|
| 1 | **NodeMCU ESP8266 (ESP-12F)** | Otak utama sistem. Menjalankan program, mengirim perintah ke DFPlayer lewat komunikasi serial (UART), dan menyuplai power ke semua komponen. |
| 2 | **DFPlayer Mini (MP3-TF-10P / Funduino)** | Modul pemutar file MP3. Membaca file audio dari SD card dan mengubahnya menjadi sinyal audio yang dikirim ke speaker. |
| 3 | **MicroSD Card (≤32GB, FAT32)** | Tempat menyimpan file lagu dalam format MP3. Harus diformat FAT32 dan nama file harus diawali 4 digit angka (0001.mp3, 0002.mp3, dst). |
| 4 | **Speaker (4Ω / 8Ω, 3W)** | Mengubah sinyal audio dari DFPlayer menjadi suara yang bisa didengar. Disambungkan langsung ke pin SPK_1 dan SPK_2 DFPlayer. |
| 5 | **Kabel Jumper** | Menghubungkan antar pin/modul di atas breadboard atau langsung ke board. |
| 6 | **Kabel USB Micro** | Menghubungkan NodeMCU ke laptop/PC untuk upload kode dan sebagai sumber power utama. |
| 7 | **Laptop/PC + Arduino IDE** | Digunakan untuk menulis, kompilasi, dan upload kode ke NodeMCU. |

---

## 🔌 Wiring / Diagram Pinout

### Tabel Koneksi

| DFPlayer Mini | NodeMCU ESP8266 | Keterangan |
|---|---|---|
| **VCC** | **VU** | Power 5V langsung dari jalur USB NodeMCU. JANGAN pakai VIN atau 3V3. |
| **GND** | **G** | Ground. Wajib disatukan antara DFPlayer dan NodeMCU. |
| **RX** | **TX** | DFPlayer menerima perintah dari NodeMCU. |
| **TX** | **RX** | DFPlayer mengirim status/respon ke NodeMCU. |
| **SPK_1** | — | Sambung ke terminal (+) speaker. |
| **SPK_2** | — | Sambung ke terminal (−) speaker. |

### Diagram Visual

```
                    ┌─────────────────────┐
                    │    NodeMCU ESP8266   │
                    │                     │
     USB ke Laptop──┤ (USB)               │
                    │                     │
                    │  VU ───────────────►│──► VCC  ┐
                    │  G  ───────────────►│──► GND  │  DFPlayer Mini
                    │  TX ───────────────►│──► RX   │  (MP3-TF-10P)
                    │  RX ◄───────────────│◄── TX   │
                    │                     │         │
                    └─────────────────────┘  SPK_1 ─┤──► Speaker (+)
                                             SPK_2 ─┘──► Speaker (−)
```

### Posisi Pin di Board NodeMCU (Sisi Kanan, atas ke bawah)

```
D0
D1
D2
D3
D4
3V
G    ◄── GND DFPlayer
D5
D6
D7
D8
RX   ◄── TX DFPlayer
TX   ◄── RX DFPlayer
G
3V
```

### Posisi Pin di Board NodeMCU (Sisi Kiri, atas ke bawah)

```
A0
VU   ◄── VCC DFPlayer  ⚠️ Gunakan pin ini, bukan VIN!
S3
S2
S1
SC
SO
SK
G
3V
EN
RST
G
VIN  ✗  (jangan dipakai untuk output power ke DFPlayer)
```

### Posisi Pin di DFPlayer Mini (Sisi Kiri, atas ke bawah)

```
VCC   ◄── VU NodeMCU
RX    ◄── TX NodeMCU
TX    ◄── RX NodeMCU
DAC_R     (tidak dipakai)
DAC_L     (tidak dipakai)
SPK_1 ◄── Speaker (+)
GND   ◄── G NodeMCU
SPK_2 ◄── Speaker (−)
```

---

## ⚠️ Hal Penting Sebelum Upload Kode

> **WAJIB: Cabut kabel RX dan TX dari DFPlayer setiap kali mau upload kode!**

Karena project ini menggunakan pin Hardware Serial (RX/TX) bawaan ESP8266 — pin yang sama yang dipakai untuk upload kode dari Arduino IDE — maka jika kabel RX/TX masih terpasang ke DFPlayer saat proses upload, upload akan gagal.

**Urutan upload yang benar:**
1. Cabut kabel **RX** dan **TX** dari DFPlayer (VCC dan GND boleh tetap)
2. Upload kode dari Arduino IDE
3. Tunggu hingga muncul **"Done uploading"**
4. Colok kembali kabel **RX** dan **TX** ke DFPlayer
5. Tekan tombol **RST** di NodeMCU
6. Lagu otomatis akan mulai diputar

---

## 💾 Cara Mengisi SD Card

1. Format SD card menggunakan **SD Card Formatter** (download di [sdcard.org](https://www.sdcard.org/downloads/formatter/)) — pilih **FAT32**
2. Copy file MP3 ke **root** SD card (jangan taruh dalam folder)
3. Rename file sesuai urutan: `0001.mp3`, `0002.mp3`, `0003.mp3`, dst
4. Mau tambah lagu baru? Tinggal copy dan rename sesuai urutan berikutnya — **tidak perlu ubah kode sama sekali**
5. Eject SD card dengan benar sebelum dicabut dari card reader
6. Pasang ke slot DFPlayer Mini

**Contoh isi SD card:**
```
D:\
├── 0001.mp3
├── 0002.mp3
├── 0003.mp3
├── 0004.mp3
└── ... (bisa sampai 0999.mp3)
```

---

## 🔧 Library yang Dibutuhkan

Install lewat **Arduino IDE → Tools → Manage Libraries**:

| Library | Versi | Link |
|---|---|---|
| `DFRobotDFPlayerMini` | Latest | [Arduino Library Manager](https://www.arduino.cc/reference/en/libraries/dfrobotdfplayermini/) |

---

## ⚙️ Pengaturan Arduino IDE

| Setting | Value |
|---|---|
| Board | Generic ESP8285 Module / NodeMCU 1.0 |
| Upload Speed | 115200 |
| CPU Frequency | 80 MHz |
| Flash Size | 1MB |
| Port | Sesuaikan (misal COM4) |

---

## 📋 Fitur

- ✅ Putar semua lagu di SD card secara otomatis berurutan
- ✅ Looping otomatis — setelah lagu terakhir selesai, balik ke lagu pertama
- ✅ Deteksi jumlah lagu otomatis — tidak perlu ubah kode saat tambah/kurangi lagu
- ✅ Indikator LED onboard — solid = OK, berkedip cepat = gagal
- ✅ Retry otomatis 3x saat koneksi ke DFPlayer gagal
- ✅ Tidak butuh tombol, tidak butuh layar, tidak butuh internet

---

## 🐛 Troubleshooting

| Gejala | Kemungkinan Penyebab | Solusi |
|---|---|---|
| LED berkedip cepat | DFPlayer gagal terdeteksi | Cek wiring RX/TX, pastikan kabel sudah dicolok kembali setelah upload, tekan RST |
| Tidak ada suara | Speaker tidak tersambung / volume 0 | Cek kabel SPK_1 & SPK_2, coba naikkan volume di kode |
| Upload gagal | Kabel RX/TX masih terpasang ke DFPlayer | Cabut kabel RX/TX sebelum upload |
| Lagu tidak terbaca (-1) | Format SD card salah / nama file salah | Format ulang ke FAT32, rename file ke format 0001.mp3 |
| LED DFPlayer mati total | Power tidak sampai ke DFPlayer | Pastikan VCC DFPlayer disambung ke pin **VU** (bukan VIN atau 3V3) |

---

## 📜 Lisensi & Hak Cipta

```
Copyright © 2026 SERPENTSECHUNTER
All rights reserved.

Dilarang keras menyalin, mendistribusikan, atau memodifikasi
kode ini tanpa izin tertulis dari pemilik.
Nama file utama HARUS tetap "Serpent.ino".
```

---

<p align="center">Made with ❤️ by <b>SERPENTSECHUNTER</b> | 2026</p>
