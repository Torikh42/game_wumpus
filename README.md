                                              GAME STRATEGI DAN MANAJEMEN RISIKO EKSPLORASI MINYAK BUMI

Game Eksplorasi Minyak Bumi ini adalah sebuah permainan edukatif yang
mensimulasikan proses pencarian dan ekstraksi minyak bumi. Pemain berperan sebagai tim
eksplorasi yang terdiri dari berbagai ahli, seperti geologist, geophysicist, dan drilling
engineer. Tujuan utama permainan adalah menemukan reservoir minyak di dalam grid 5x5
dengan menghindari bahaya seperti zona tekanan tinggi, lubang kering, dan zona air.
Permainan ini dirancang untuk memberikan pemahaman tentang tantangan dalam
industri minyak bumi, seperti manajemen risiko, pengelolaan anggaran, dan strategi
eksplorasi. Pemain harus membuat keputusan cerdas untuk bergerak di dalam grid,
mempertimbangkan biaya pergerakan, dan menghindari area berbahaya yang dapat
menguras anggaran.

Penjelasan
• Inisialisasi Game:
- Program dimulai dengan menginisialisasi grid 5x5 yang berisi berbagai objek, seperti
reservoir minyak (`OR`), zona tekanan tinggi (`HP`), lubang kering (`DH`), zona air
(`WZ`), dan rembesan minyak (`OS`). Posisi objek-objek ini ditentukan secara acak
menggunakan fungsi `random.randint()`.
- Untuk memastikan tidak ada objek yang menempati posisi yang sama, program
menggunakan loop `while` agar semua posisi objek berbeda.
- Posisi awal pemain ditetapkan di sudut kiri atas grid (posisi [0][0]), dan anggaran awal
pemain adalah $1000.
- Program juga menyimpan `last_budget`, yaitu anggaran terakhir yang tercatat sebelum
pemain menemukan reservoir minyak. Ini memungkinkan pemain untuk melanjutkan
permainan dari titik tersebut jika mereka memilih untuk bermain lagi.
• Tampilan Peta:
- Fungsi `print_map()` menampilkan grid 5x5 dengan simbol-simbol yang mewakili posisi
pemain dan objek-objek di dalam grid.
- Simbol yang digunakan antara lain:
- `P` untuk posisi pemain.
- `OR` untuk reservoir minyak.
- `HP` untuk zona tekanan tinggi.
- `DH` untuk lubang kering.
- `WZ` untuk zona air.
- `OS` untuk rembesan minyak.
- Area yang kosong ditandai dengan simbol `-`.

 Pergerakan Pemain:
- Pemain dapat bergerak ke atas, bawah, kiri, atau kanan dengan mengimput teks. Setiap
pergerakan mengurangi anggaran sebesar $50.
- Program memeriksa batasan grid untuk memastikan pemain tidak keluar dari area
permainan. Jika pemain mencoba bergerak keluar grid, program akan menampilkan pesan
error.
- Setelah pemain bergerak, program memeriksa posisi baru pemain. Jika pemain berada di
posisi objek tertentu, anggaran akan bertambah atau berkurang sesuai dengan aturan yang
telah ditetapkan:
8
(1) Reservoir Minyak (`OR`): Anggaran bertambah $500, dan pemain memenangkan
permainan. Anggaran terakhir (`last_budget`) disimpan untuk memungkinkan
pemain melanjutkan permainan.
(2) Zona Tekanan Tinggi (`HP`): Anggaran berkurang $200 karena pemain terkena
blow out.
(3) Lubang Kering (`DH`): Anggaran berkurang $100 karena pemain jatuh ke lubang
yang tidak menghasilkan minyak.
(4) Zona Air (`WZ`): Anggaran berkurang $50 karena pemain terjebak di area yang
tidak produktif.
(5) Rembesan Minyak (`OS`): Anggaran bertambah $100 karena pemain menemukan
indikasi minyak. 
