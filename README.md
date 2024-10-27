# Sistem Alarm Keamanan dengan Keypad dan Tampilan LCD

## Gambaran Umum

Proyek ini mengimplementasikan sistem alarm keamanan menggunakan tampilan LCD, keypad matriks 4x4, dan sensor PIR (Passive Infrared). Sistem ini memerlukan password untuk menonaktifkan alarm saat gerakan terdeteksi. Ini menampilkan informasi kepada pengguna melalui LCD.

Proyek ini adalah modifikasi dari proyek saya sebelumnya, yaitu proyek SmartLock untuk pameran 'Kainotech', aksi angkatan dari Massa Elektroteknik'23. Jika ada potongan kode yang tampaknya tidak terkait, ini mungkin adalah bagian kode yang lupa dihapus.

## Komponen yang Diperlukan

- Arduino (misalnya, Arduino Uno)
- Tampilan LCD (I2C)
- Keypad matriks 4x4
- Sensor PIR (Passive Infrared)
- Buzzer (2 buah untuk buzzer dan untuk alarm)
- Kabel jumper
- Breadboard (opsional)

## Library yang Digunakan

- `LiquidCrystal_I2C`: Untuk mengontrol tampilan LCD.
- `Keypad`: Untuk menangani input dari keypad.

## Pemasangan/Setup

- **LCD**: Menghubungkan ke memory address komponen LCD I2C `0x27`
- **Keypad**:
  - Baris: 6, 7, 8, 9 (hubungkan ke pin 6, 7, 8, 9)
  - Kolom: 2, 3, 4, 5 (hubungkan ke pin 2, 3, 4, 5)
- **Sensor PIR**: Hubungkan ke pin 13
- **Buzzer**: Hubungkan ke pin 11
- **Alarm (LED atau Buzzer)**: Hubungkan ke pin 12

## Overview Kode

1. **Inisialisasi**:
   - LCD diinisialisasi dengan backlight.
   - Pin buzzer dan alarm diatur sebagai output, dan sensor PIR diatur sebagai input.

2. **Loop Utama**:
   - Menampilkan pesan awal untuk pengguna agar memasukkan kode password.
   - Memeriksa sensor PIR untuk gerakan:
     - Jika gerakan terdeteksi, sistem mengaktifkan alarm dan menampilkan pemberitahuan di LCD.
   - Menerima penekanan tombol dari keypad:
     - Penekanan tombol yang valid digabungkan menjadi string input.
     - Tombol `#` memeriksa password yang dimasukkan terhadap password yang telah ditentukan.
     - Tombol `*` memungkinkan pengguna untuk menghapus karakter terakhir dari input.

3. **Fungsi**:
   - `displayscreen()`: Menampilkan instruksi awal di LCD.
   - `keypress()`: Mengaktifkan buzzer secara singkat ketika tombol ditekan.
   - `alarmoff()`: Menonaktifkan alarm dan menampilkan pesan konfirmasi.

## Password

Password default diatur ke `29012005`. Ubah variabel `pass` dalam kode untuk mengganti password sesuai kebutuhan.

## Penggunaan

1. Unggah kode ke Arduino.
2. Hubungkan semua komponen sesuai dengan petunjuk pada bagian Pemasangan/Setup.
3. Nyalakan sistem. LCD akan meminta kode password.
4. Masukkan password menggunakan keypad. Gunakan `#` untuk Enter dan `*` untuk menghapus karakter.
5. Setelah berhasil memasukkan password yang benar, alarm akan dinonaktifkan. Jika sensor PIR mendeteksi gerakan, alarm akan
diaktifkan dan menampilkan pemberitahuan.