# GAME STRATEGI DAN MANAJEMEN RISIKO EKSPLORASI MINYAK BUMI

## Deskripsi Game
Game Eksplorasi Minyak Bumi adalah sebuah permainan edukatif yang mensimulasikan proses pencarian dan ekstraksi minyak bumi. Pemain berperan sebagai tim eksplorasi yang harus menemukan reservoir minyak dalam grid 5x5 sambil mengelola anggaran dengan bijak.

## Tujuan Permainan
- Menemukan lokasi reservoir minyak (OR)
- Menghindari area berbahaya yang dapat mengurangi anggaran
- Mengelola anggaran agar tidak habis sebelum menemukan minyak
- Mengumpulkan uang sebanyak mungkin

## Mekanisme Permainan

### Inisialisasi Game
- Grid 5x5 dengan berbagai objek yang ditempatkan secara acak
- Posisi awal pemain di sudut kiri atas [0][0]
- Anggaran awal: $1000

### Objek dalam Game
- `P ` : Posisi pemain
- `OR` : Reservoir minyak (+$500)
- `HP` : Zona tekanan tinggi (-$200)
- `DH` : Lubang kering (-$100)
- `WZ` : Zona air (-$50)
- `OS` : Rembesan minyak (+$100)
- `--` : Area kosong

### Pergerakan dan Biaya
- Gunakan tombol W/A/S/D untuk bergerak
- W : Atas
- S : Bawah
- A : Kiri
- D : Kanan
- Setiap pergerakan membutuhkan biaya $50

### Fitur Khusus
- Pemain dapat melanjutkan permainan setelah menemukan minyak atau game over
- Jika memilih melanjutkan, anggaran terakhir akan disimpan
- Grid akan di-reset dan objek ditempatkan ulang secara acak
- Total uang yang terkumpul akan ditampilkan di akhir permainan

### Kondisi Menang/Kalah
- Menang: Menemukan reservoir minyak (OR)
- Kalah: Anggaran habis (≤ $0)

### Efek Objek
1. Reservoir Minyak (OR)
   - Menambah anggaran $500
   - Memenangkan level permainan
2. Zona Tekanan Tinggi (HP)
   - Mengurangi anggaran $200
3. Lubang Kering (DH)
   - Mengurangi anggaran $100
4. Zona Air (WZ)
   - Mengurangi anggaran $50
5. Rembesan Minyak (OS)
   - Menambah anggaran $100

## Strategi Bermain
- Bergerak dengan hati-hati untuk menghemat anggaran
- Manfaatkan rembesan minyak (OS) untuk menambah anggaran
- Hindari zona berbahaya (HP, DH, WZ)
- Rencanakan rute eksplorasi yang efisien