#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define GRID_SIZE 5
#define NODES (GRID_SIZE * GRID_SIZE)
#define INITIAL_BUDGET 1000

// Struktur untuk node dalam graph
typedef struct {
    char content[3];         // Isi sel (OR, HP, dll)
    int edges[4];           // Indeks node yang terhubung (atas, kanan, bawah, kiri)
    int edge_count;         // Jumlah edge yang terhubung
} Node;

// Struktur untuk game state
typedef struct {
    Node* graph;            // Array of nodes (graph)
    int player_pos;         // Posisi player dalam graph
    int budget;            // Budget pemain
    int last_budget;       // Budget terakhir
} GameState;

// Konstanta objek game
const char* OIL_RESERVOIR = "OR";
const char* HIGH_PRESSURE = "HP";
const char* DRY_HOLE = "DH";
const char* WATER_ZONE = "WZ";
const char* OIL_SEEPAGE = "OS";
const char* EMPTY = "--";
const char* PLAYER = "P ";

// Inisialisasi graph
Node* create_graph() {
    Node* graph = (Node*)malloc(NODES * sizeof(Node));
    
    for (int i = 0; i < NODES; i++) {
        strcpy(graph[i].content, EMPTY);
        graph[i].edge_count = 0;
        
        // Tambahkan edge ke atas
        if (i >= GRID_SIZE) {
            graph[i].edges[graph[i].edge_count++] = i - GRID_SIZE;
        }
        // Tambahkan edge ke kanan
        if ((i + 1) % GRID_SIZE != 0) {
            graph[i].edges[graph[i].edge_count++] = i + 1;
        }
        // Tambahkan edge ke bawah
        if (i < NODES - GRID_SIZE) {
            graph[i].edges[graph[i].edge_count++] = i + GRID_SIZE;
        }
        // Tambahkan edge ke kiri
        if (i % GRID_SIZE != 0) {
            graph[i].edges[graph[i].edge_count++] = i - 1;
        }
    }
    return graph;
}

// Penempatan objek secara random
void place_random_object(GameState* game, const char* object) {
    int pos;
    do {
        pos = rand() % NODES;
    } while (strcmp(game->graph[pos].content, EMPTY) != 0 || pos == 0);
    strcpy(game->graph[pos].content, object);
}

// Inisialisasi game
void init_game(GameState* game) {
    game->graph = create_graph();
    game->player_pos = 0;
    game->budget = INITIAL_BUDGET;
    game->last_budget = INITIAL_BUDGET;
    
    srand(time(NULL));
    place_random_object(game, OIL_RESERVOIR);
    place_random_object(game, HIGH_PRESSURE);
    place_random_object(game, DRY_HOLE);
    place_random_object(game, WATER_ZONE);
    place_random_object(game, OIL_SEEPAGE);
}

// Reset game
void reset_game(GameState* game, bool keep_budget) {
    int current_budget = game->budget;
    free(game->graph);
    game->graph = create_graph();
    game->player_pos = 0;
    
    if (keep_budget) {
        game->budget = current_budget;
    } else {
        game->budget = INITIAL_BUDGET;
    }
    game->last_budget = game->budget;
    
    place_random_object(game, OIL_RESERVOIR);
    place_random_object(game, HIGH_PRESSURE);
    place_random_object(game, DRY_HOLE);
    place_random_object(game, WATER_ZONE);
    place_random_object(game, OIL_SEEPAGE);
}

// Menampilkan peta
void print_map(const GameState* game) {
    printf("\nPeta Saat Ini:\n");
    for (int i = 0; i < NODES; i++) {
        if (i == game->player_pos) {
            printf(" %s ", PLAYER);
        } else {
            printf(" %s ", game->graph[i].content);
        }
        if ((i + 1) % GRID_SIZE == 0) printf("\n");
    }
    if (game->budget > 0)
    {
            printf("\nBudget: $%d\n", game->budget);
    }
}

// Proses efek sel
void process_cell_effect(GameState* game) {
    const char* cell = game->graph[game->player_pos].content;
    
    if (strcmp(cell, OIL_RESERVOIR) == 0) {
        game->budget += 500;
        printf("Anda menemukan minyak! Budget +$500\n");
        printf("total uang anda: $%d\n", game->budget);
    } else if (strcmp(cell, HIGH_PRESSURE) == 0) {
        game->budget -= 200;
        printf("Zona tekanan tinggi! Budget -$200\n");
    } else if (strcmp(cell, DRY_HOLE) == 0) {
        game->budget -= 100;
        printf("Lubang kering! Budget -$100\n");
    } else if (strcmp(cell, WATER_ZONE) == 0) {
        game->budget -= 50;
        printf("Zona air! Budget -$50\n");
    } else if (strcmp(cell, OIL_SEEPAGE) == 0) {
        game->budget += 100;
        printf("Rembesan minyak ditemukan! Budget +$100\n");
    }
}

// Pergerakan pemain
bool move_player(GameState* game, char direction) {
    // Convert to lowercase for case-insensitive input
    direction = tolower(direction);
    
    // Validate input first
    if (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd') {
        printf("Input tidak valid! Gunakan W/A/S/D untuk bergerak.\n");
        return false;
    }

    int new_pos = game->player_pos;
    
    switch(direction) {
        case 'w': new_pos -= GRID_SIZE; break;
        case 's': new_pos += GRID_SIZE; break;
        case 'a': new_pos -= 1; break;
        case 'd': new_pos += 1; break;
    }
    
    // Cek validitas gerakan menggunakan edges
    bool valid_move = false;
    for (int i = 0; i < game->graph[game->player_pos].edge_count; i++) {
        if (game->graph[game->player_pos].edges[i] == new_pos) {
            valid_move = true;
            break;
        }
    }
    
    if (!valid_move) {
        printf("Gerakan tidak valid! Tetap dalam grid.\n");
        return false;
    }
    
    game->player_pos = new_pos;
    game->budget -= 50;
    process_cell_effect(game);
    return true;
}

int main() {
    GameState game;
    init_game(&game);
    char move;
    bool game_running = true;
    char play_again;
    
    printf("Selamat datang di Game Eksplorasi Minyak!\n");
    printf("Gunakan W/A/S/D untuk bergerak\n");
    
    while (1) {
        while (game_running) {
            print_map(&game);
            
             if (game.budget <= 0) {
                printf("Game Over! Budget Anda habis.\n");
                printf("Apakah anda ingin mencoba lagi? (y/n): ");
                scanf(" %c", &play_again);
                
                if (play_again == 'y' || play_again == 'Y') {
                    reset_game(&game, false);  // false = tidak menyimpan budget sebelumnya
                    game.budget = INITIAL_BUDGET;  // reset ke 1000
                    game_running = true;
                    printf("\nMemulai permainan baru dengan budget $%d\n", game.budget);
                    continue;
                } else {
                    printf("\nTerima kasih telah bermain!\n");
                    free(game.graph);
                    return 0;
                }
            }
            
            printf("Masukkan gerakan (w/a/s/d): ");
            scanf(" %c", &move);
            
            if (!move_player(&game, move)) {
                continue;
            }
            
            if (strcmp(game.graph[game.player_pos].content, OIL_RESERVOIR) == 0) {
                printf("Selamat! Anda menang!\n");
                game_running = false;
            }
        }
        if (game.budget > 0)
        {
            printf("\nApakah anda ingin melanjutkan permainan? (y/n): ");
        scanf(" %c", &play_again);
        
        if (play_again == 'y' || play_again == 'Y') {
            reset_game(&game, true);
            game_running = true;
            printf("\nMemulai permainan baru dengan budget $%d\n", game.budget);
        } else {
            printf("\nTerima kasih telah bermain!\n");
            printf("Total uang yang terkumpul: $%d\n", game.budget);
            free(game.graph);
            break;
        }
        }   
    }
    
    return 0;
}