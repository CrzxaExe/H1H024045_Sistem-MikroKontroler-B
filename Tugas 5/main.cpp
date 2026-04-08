const int trafficPin[3] = {4, 5, 6}; // pin lampu lalu lintas (merah, kuning, hijau)
const int pedPin1[2] = {7, 8};       // pin lampu penyebrangan 1 (merah, hijau)
const int pedPin2[2] = {9, 10};      // pin lampu penyebrangan 2
const int buttons[2] = {2, 3};       // pin button interrupt

volatile int state = 0; // data status saat ini

int pedDur = 10; // durasi seberapa lama lampu penyebrangan nyala

void blinking(int pin, int s)
{ // fungsi led untuk berkedip
    digitalWrite(pin, HIGH);
    delay(s);
    digitalWrite(pin, LOW);
    delay(s);
}

void pedestrianMode()
{ // fungsi utama untuk menjalankan lampu penyebrangan

    // Beralih ke lampu kuning yang berkedip 3 kali
    digitalWrite(trafficPin[2], LOW);
    for (int i = 0; i < 3; i++)
        blinking(trafficPin[1], 500);

    // semua lampu penyebrangan akan menyala hijau dan lampu lalu lintas akan menyala merah
    digitalWrite(pedPin1[0], LOW);
    digitalWrite(pedPin2[0], LOW);
    digitalWrite(pedPin1[1], HIGH);
    digitalWrite(pedPin2[1], HIGH);
    digitalWrite(trafficPin[0], HIGH);

    delay(pedDur * 1000); // memberikan jeda lampu penyebrangan

    // mengubah lampu penyebrangan menjadi merah lagi
    digitalWrite(pedPin1[1], LOW);
    digitalWrite(pedPin2[1], LOW);
    digitalWrite(pedPin1[0], HIGH);
    digitalWrite(pedPin2[0], HIGH);

    // mematikan lampu lalu lintas warna merah dan beralih ke warna kuning yang berkedip
    digitalWrite(trafficPin[0], LOW);
    for (int i = 0; i < 3; i++)
        blinking(trafficPin[1], 500);

    // menyalakan kembali lampu hijau pada lalu lintas dan mengatur ulang nilai state
    digitalWrite(trafficPin[2], HIGH);
    state = 0;
}

void onBtnPress()
{ // fungsi interrupt, untuk mengubah nilai state
    if (state == 1)
        return; // membatasi button, agar fungsi berikutnya tidak dijalankan
    state = 1;
}

void setup()
{
    // menginisiasi kan pin dan interrupt yang akan digunakan
    for (int i = 4; i < 11; i++)
        pinMode(i, OUTPUT);
    for (int i = 2; i < 4; i++)
    {
        pinMode(i, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(i), onBtnPress, FALLING);
    }

    // menginisiasi lampu yang akan menyala untuk pertama kali
    digitalWrite(trafficPin[2], HIGH);
    digitalWrite(pedPin1[0], HIGH);
    digitalWrite(pedPin2[0], HIGH);
}

void loop()
{
    if (state == 1)
        pedestrianMode();
}