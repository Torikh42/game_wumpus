#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#define GRID_SIZE 5
#define ROOMS (GRID_SIZE * GRID_SIZE)

// Struktur untuk menyimpan posisi objek dan status permainan
struct GameGrid {
    int oil_reservoir;
    int high_pressure;
    int dry_hole;
    int water_zone;
    int oil_seepage;
    int player_pos;
    int budget;
    int last_budget;
};

// Fungsi untuk menginisialisasi permainan dan grid
GameGrid init_game() {
    GameGrid grid;
    int positions[5] = {0};

    srand(time(0));

    while (true) {
        positions[0] = rand() % ROOMS;
        positions[1] = rand() % ROOMS;
        positions[2] = rand() % ROOMS;
        positions[3] = rand() % ROOMS;
        positions[4] = rand() % ROOMS;

        // Memastikan posisi objek tidak tumpang tindih
        bool unique = true;
        for (int i = 0; i < 5; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (positions[i] == positions[j]) {
                    unique = false;
                    break;
                }
            }
            if (!unique) break;
        }
        if (unique) break;
    }

    grid.oil_reservoir = positions[0];
    grid.high_pressure = positions[1];
    grid.dry_hole = positions[2];
    grid.water_zone = positions[3];
    grid.oil_seepage = positions[4];
    grid.player_pos = 0;
    grid.budget = 1000;
    grid.last_budget = grid.budget;

    return grid;
}

// Fungsi untuk menampilkan peta
void print_map(int player_pos, GameGrid grid) {
    cout << "Peta (P = Pemain, OR = Oil Reservoir, HP = High Pressure, DH = Dry Hole, WZ = Water Zone, OS = Oil Seepage):" << endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int room = i * GRID_SIZE + j;
            if (room == player_pos) {
                cout << "P ";
            } else if (room == grid.oil_reservoir) {
                cout << "OR ";
            } else if (room == grid.high_pressure) {
                cout << "HP ";
            } else if (room == grid.dry_hole) {
                cout << "DH ";
            } else if (room == grid.water_zone) {
                cout << "WZ ";
            } else if (room == grid.oil_seepage) {
                cout << "OS ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Fungsi untuk memberikan petunjuk berdasarkan posisi pemain
void give_hint(int player_pos, GameGrid grid) {
    bool proximity = false;
    if (abs(player_pos - grid.oil_reservoir) < 2) cout << "Dekat dengan reservoir minyak (OR). ";
    if (abs(player_pos - grid.high_pressure) < 2) cout << "Dekat dengan zona tekanan tinggi (HP). ";
    if (abs(player_pos - grid.dry_hole) < 2) cout << "Dekat dengan lubang kering (DH). ";
    if (abs(player_pos - grid.water_zone) < 2) cout << "Dekat dengan zona air (WZ). ";
    if (abs(player_pos - grid.oil_seepage) < 2) cout << "Dekat dengan indikasi minyak (OS). ";
    if (!proximity) cout << "Tidak ada petunjuk di sekitar sini." << endl;
    else cout << endl;
}

// Fungsi untuk memeriksa status permainan
const char* check_game_status(int player_pos, GameGrid grid) {
    if (player_pos == grid.oil_reservoir) {
        return "Selamat! Anda menemukan reservoir minyak dan berhasil mengekstraksi minyak!";
    }
    return nullptr;
}

// Fungsi untuk memeriksa pergerakan pemain dan anggaran
void move_player(char move, GameGrid &grid) {
    int player_pos = grid.player_pos;
    int budget = grid.budget;

    if (move == 'u' && player_pos >= GRID_SIZE) {
        player_pos -= GRID_SIZE;
        budget -= 50;
    } else if (move == 'd' && player_pos < ROOMS - GRID_SIZE) {
        player_pos += GRID_SIZE;
        budget -= 50;
    } else if (move == 'l' && player_pos % GRID_SIZE != 0) {
        player_pos -= 1;
        budget -= 50;
    } else if (move == 'r' && player_pos % GRID_SIZE != GRID_SIZE - 1) {
        player_pos += 1;
        budget -= 50;
    } else {
        cout << "Pergerakan tidak valid!" << endl;
        return;
    }

    // Update posisi dan anggaran berdasarkan objek yang ditemukan
    if (player_pos == grid.oil_reservoir) {
        budget += 500;
        cout << "Anda menemukan minyak! Anggaran bertambah." << endl;
    } else if (player_pos == grid.high_pressure) {
        budget -= 200;
        cout << "Anda terkena blow out! Anggaran berkurang." << endl;
    } else if (player_pos == grid.dry_hole) {
        budget -= 100;
        cout << "Anda jatuh ke lubang kering! Anggaran berkurang." << endl;
    } else if (player_pos == grid.water_zone) {
        budget -= 50;
        cout << "Anda terjebak di zona air! Anggaran berkurang." << endl;
    } else if (player_pos == grid.oil_seepage) {
        budget += 100;
        cout << "Indikasi minyak ditemukan! Anggaran bertambah." << endl;
    }

    grid.player_pos = player_pos;
    grid.budget = budget;
}

// Fungsi untuk melanjutkan permainan
bool continue_game(GameGrid &grid) {
    cout << "Total Uang Anda: $" << grid.budget << endl;
    char response;
    cout << "Apakah Anda ingin melanjutkan permainan? (y/n): ";
    cin >> response;
    if (response == 'y') {
        grid.budget = grid.last_budget;
        return true;
    }
    return false;
}

// Fungsi utama untuk menjalankan permainan
void play_game() {
    GameGrid grid = init_game();
    cout << "Selamat datang di Game Edukatif Eksplorasi Minyak Bumi!" << endl;
    cout << "Tujuan: Temukan reservoir minyak (Oil Reservoir) dan ekstraksi minyak." << endl;
    cout << "Hindari bahaya seperti blow out, lubang kering, dan zona air." << endl;

    while (true) {
        print_map(grid.player_pos, grid);
        give_hint(grid.player_pos, grid);
        cout << "Anggaran Anda: $" << grid.budget << endl;

        if (grid.budget <= 0) {
            cout << "Game Over! Anggaran Anda habis." << endl;
            break;
        }

        char move;
        cout << "Masukkan pergerakan (u = atas, d = bawah, l = kiri, r = kanan): ";
        cin >> move;

        move_player(move, grid);

        const char* status = check_game_status(grid.player_pos, grid);
        if (status) {
            cout << status << endl;
            break;
        }
    }

    if (continue_game(grid)) {
        play_game();
    }
}

int main() {
    play_game();
    return 0;
}
