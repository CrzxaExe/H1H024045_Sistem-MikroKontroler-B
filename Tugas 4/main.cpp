// menyimpan cycle dari traffic lightnya yaitu dari 0-3
// 0 = utara
// 1 = timur
// 2 = selatan
// 3 = barat
int cyc = 0;

// Durasi orange menyala
int orangeDur = 2;
// Durasi hijau menyala
int greenDur = 5;

/**
 * Fungsi untuk membuat lampu berkedip
 * @param pin no pin yang akan berkedip
 * @param s durasi pin berkedip
 */
void blinking(int pin, int s)
{
    digitalWrite(pin, HIGH);
    delay(s);
    digitalWrite(pin, LOW);
    delay(s);
}

/**
 * Fungsi utama
 * Menyalakan lampu secara bergiliran sesuai cycle sekarang
 * @param cycle cycle saat ini
 */
void traffic(int cycle)
{
    // variabel yang menyimpan posisi utama pin sesuai cycle(jalur) saat ini
    int lane = 3 * cycle;

    // lane + 2 = pin merah pada jalur sesuai cycle
    // lane + 3 = pin kuning pada jalur sesuai cycle
    // lane + 4 = pin hijau pada jalur sesuai cycle

    // mematikan lampu merah, lampu kuning mulai berkedip 3 kali dengan durasi 300 milidetik tiap loopnya
    digitalWrite(lane + 2, LOW);
    for (int i = 0; i < 3; i++)
        blinking(lane + 3, 300);

    // setelak berkedip, lampu kuning akan menyala selama durasinya lalu berubah ke hijau beberapa saat
    digitalWrite(lane + 3, HIGH);
    delay(orangeDur * 1000);
    digitalWrite(lane + 3, LOW);
    digitalWrite(lane + 4, HIGH);
    delay(greenDur * 1000);

    // setelah durasi, lampu hijau mati dan lampu merah akan menyala kembali
    digitalWrite(lane + 4, LOW);
    digitalWrite(lane + 2, HIGH);
    delay(1000); // optional, jeda antar simpang
}

void setup()
{
    // inisiasi pin output dengan looping, karena pin yang digunakan sudah berurutan (2-14, ada beberapa pin yang tidak terpakai)
    // urutan pin LED: merah, kuning, hijau, merah, ..., hijau.
    for (int i = 2; i < 14; i++)
    {
        pinMode(i, OUTPUT);
        if (i % 3 == 2) // menyalakan semua led merah
            digitalWrite(i, HIGH);
    }
    delay(1000); // delay sebelum memulai looping
}

void loop()
{
    traffic(cyc);
    cyc++;
    cyc %= 4; // memastikan bahwa variabel cyc hanya bernilai 0-3
}