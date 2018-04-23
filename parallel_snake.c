#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"

//functie ce calculeaza noile coordonate in cazul deplasarii catre nord
struct coord move_north(struct coord coord_to_be_moved, int num_lines){

	struct coord new_coord;
	
	if(coord_to_be_moved.line == 0) {
		new_coord.line = num_lines - 1;
	}else {
		new_coord.line = coord_to_be_moved.line - 1;
	}

	new_coord.col = coord_to_be_moved.col;
	
	return new_coord;
}

//functie ce calculeaza noile coordonate in cazul deplasarii catre sud
struct coord move_south(struct coord coord_to_be_moved, int num_lines){
	struct coord new_coord;

	if(coord_to_be_moved.line == num_lines - 1) {
		new_coord.line = 0;
	} else {
		new_coord.line = coord_to_be_moved.line + 1;
	}

	new_coord.col = coord_to_be_moved.col;
	
	return new_coord;
}

//functie ce calculeaza noile coordonate in cazul deplasarii catre est
struct coord move_east(struct coord coord_to_be_moved, int num_cols){
	struct coord new_coord;

	if(coord_to_be_moved.col == num_cols - 1) {
		new_coord.col = 0;
	} else {
		new_coord.col = coord_to_be_moved.col + 1;
	}

	new_coord.line = coord_to_be_moved.line;
	
	return new_coord;
}

//functie ce calculeaza noile coordonate in cazul deplasarii catre vest
struct coord move_west(struct coord coord_to_be_moved, int num_cols){
	struct coord new_coord;

	if(coord_to_be_moved.col == 0) {
		new_coord.col = num_cols - 1;
	} else {
		new_coord.col = coord_to_be_moved.col - 1;
	}
	
	new_coord.line = coord_to_be_moved.line;
	
	return new_coord;
}

// functie ce calculeaza, in functie de valoarea variabile is_head, doua lucruri,
// astfel:
//		1. daca variabila is_head este adevarata, inseamn ca vrem sa numaram 
// vecinii de pe aceeasi directie cu capul sarpelui, avand de asemenea aceeasi 
// ecodare
//		2. daca variabila is_head este falsa, inseamna ca vrem sa numaram 
// vecinii unei cozi, scopul fiind acela de a gasi exact un vecin cu acceasi 
// codificare caruia sa ii extragem pozitia
int nr_of_neighbours(int** world, int num_lines, int num_cols, int line, int col, bool is_head, char direction, struct coord *neighbour){
	int nr = 0;
	num_lines -= 1;
	num_cols -= 1;
	//vrem sa numaram vecinii unui cap de sarpe
	if(is_head == true) {
		//capul se afla in coltul din stanga sus
		if(line == 0 && col == 0) {
			if(world[line][col + 1] != 0 && direction == 'E'){
				nr++;
			}
			if(world[line + 1][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[num_lines][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[line][num_cols] != 0 && direction == 'V'){
				nr++;
			}
		} 
		//capul se afla in coltul din dreapta sus
		else if(line == 0 && col == num_cols){
			if(world[line][col - 1] != 0 && direction == 'V'){
				nr++;
			}
			if(world[line + 1][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[num_lines][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[line][0] != 0 && direction == 'E'){
				nr++;
			}
		}
		//capul se afla in coltul din stanga jos
		else if(line == num_lines && col == 0) {
			if(world[line -1 ][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[line][col + 1] != 0 && direction == 'E'){
				nr++;
			}
			if(world[line][num_cols] != 0 && direction == 'V'){
				nr++;
			}
			if(world[0][col] != 0 && direction == 'S'){
				nr++;
			}
		}
		//capul se afla in coltul din dreapta jos
		else if(line == num_lines && col == num_cols){
			if(world[line][col - 1] != 0 && direction == 'V'){
				nr++;
			}
			if(world[line - 1][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[0][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[line][0] != 0 && direction == 'E'){
				nr++;
			}
		}
		//capul se afla pe prima linie
		else if(line == 0){
			if(world[line + 1][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[line][col - 1] != 0 && direction == 'V'){
				nr++;
			}
			if(world[line][col + 1] != 0 && direction == 'E'){
				nr++;
			}
			if(world[num_lines][col] != 0 && direction == 'N'){
				nr++;
			}
		}
		//capul se afla pe prima coloana
		else if(col == 0){
			if(world[line][col + 1] != 0 && direction == 'E'){
				nr++;
			}
			if(world[line - 1][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[line + 1][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[line][num_cols] != 0 && direction == 'V'){
				nr++;
			}
		} 
		//capul se afla pe ultima linie
		else if(line == num_lines){
			if(world[line][col - 1] != 0 && direction == 'V'){
				nr++;
			}
			if(world[line][col + 1] != 0 && direction == 'E'){
				nr++;
			}
			if(world[line - 1][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[0][col] != 0 && direction == 'S'){
				nr++;
			}
		}
		//capul se afla pe ultima coloana
		else if(col == num_cols){
			if(world[line][col - 1] != 0 && direction == 'V'){
				nr++;
			}
			if(world[line + 1][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[line - 1][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[line][0] != 0 && direction == 'E'){
				nr++;
			}
		} else {
			if(world[line - 1][col] != 0 && direction == 'N'){
				nr++;
			}
			if(world[line + 1][col] != 0 && direction == 'S'){
				nr++;
			}
			if(world[line][col - 1] != 0 && direction == 'V'){
				nr++;
			}
			if(world[line][col + 1] != 0 && direction == 'E'){
				nr++;
			}
		}
	}
	//vrem sa identificam vecinul unei cozi
	else if(is_head == false) {
		//coada se afla in coltul din stanga sus
		if(line == 0 && col == 0) {
			if(world[line][col + 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col + 1;
			}
			if(world[line + 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line + 1;
				(*neighbour).col = col;
			}
			if(world[num_lines][col] == world[line][col]){
				nr++;
				(*neighbour).line = num_lines;
				(*neighbour).col = col;
			}
			if(world[line][num_cols] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = num_cols;
			}
		}
		//coada se afla in coltul din dreapta sus
		else if(line == 0 && col == num_cols){
			if(world[line][col - 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col - 1;
			}
			if(world[line + 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line + 1;
				(*neighbour).col = col;
			}
			if(world[num_lines][col] == world[line][col]){
				nr++;
				(*neighbour).line = num_lines;
				(*neighbour).col = col;
			}
			if(world[line][0] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = 0;
			}
		} 
		//coada se afla in coltul din stanga jos
		else if(line == num_lines && col == 0) {
			if(world[line -1 ][col] == world[line][col]){
				nr++;
				(*neighbour).line = line - 1;
				(*neighbour).col = col;
			}
			if(world[line][col + 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col + 1;
			}
			if(world[0][col] == world[line][col]){
				nr++;
				(*neighbour).line = 0;
				(*neighbour).col = col;
			}
			if(world[line][num_cols] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = num_cols;
			}
		}
		//coada se afla in coltul din dreapta jos
		else if(line == num_lines && col == num_cols){
			if(world[line][col - 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col - 1;
			}
			if(world[line - 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line - 1;
				(*neighbour).col = col;
			}
			if(world[line][0] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = 0;
			}
			if(world[0][col] == world[line][col]){
				nr++;
				(*neighbour).line = 0;
				(*neighbour).col = col;
			}
		}
		//coada se afla pe prima linie
		else if(line == 0){
			if(world[line + 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line + 1;
				(*neighbour).col = col;
			}
			if(world[line][col - 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col - 1;
			}
			if(world[line][col + 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col + 1;
			}
			if(world[num_lines][col] == world[line][col]){
				nr++;
				(*neighbour).line = num_lines;
				(*neighbour).col = col;
			}
		}
		//coada se afla pe prima coloana
		else if(col == 0){
			if(world[line][col + 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col + 1;
			}
			if(world[line - 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line - 1;
				(*neighbour).col = col;
			}
			if(world[line + 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line + 1;
				(*neighbour).col = col;
			}
			if(world[line][num_cols] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = num_cols;
			}
		}
		//coada se afla pe ultima linie
		else if(line == num_lines){
			if(world[line][col - 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col - 1;
			}
			if(world[line][col + 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col + 1;
			}
			if(world[line - 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line - 1;
				(*neighbour).col = col;
			}
			if(world[0][col] == world[line][col]){
				nr++;
				(*neighbour).line = 0;
				(*neighbour).col = col;
			}
		}
		//coada se afla pe ultima coloana
		else if(col == num_cols){
			if(world[line][col - 1] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = col - 1;
			}
			if(world[line + 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line + 1;
				(*neighbour).col = col;
			}
			if(world[line - 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line - 1;
				(*neighbour).col = col;
			}
			if(world[line][0] == world[line][col]){
				nr++;
				(*neighbour).line = line;
				(*neighbour).col = 0;
			}
		} else {
			if(world[line - 1][col] == world[line][col]){
				nr++;
				(*neighbour).line = line - 1;
				(*neighbour).col = col;
			}
			if(world[line + 1][col] == world[line][col]){
					nr++;
					(*neighbour).line = line + 1;
					(*neighbour).col = col;
			}
			if(world[line][col - 1] == world[line][col]){
					nr++;
					(*neighbour).line = line;
					(*neighbour).col = col - 1;
			}
			if(world[line][col + 1] == world[line][col]){
					nr++;
					(*neighbour).line = line;
					(*neighbour).col = col + 1;
			}
		}
	}
	return nr;
}

// Verificam daca valoarea unei pozitii din matrice corespunde unui cap de sarpe.
// In caz afirmativ, intoarcem directia capului, altfel intoracem 'U'.
char check_if_snake_head(struct snake * snakes, int num_snakes, int line, int col){
	int i;

	for(i = 0; i < num_snakes; i++) {
		if(snakes[i].head.line == line && snakes[i].head.col == col){
			return snakes[i].direction;
		}
	}
	
	//returneaza 'U' (undefined) daca celula nu este cap de sarpe
	return 'U';
}

// Functie ce intoarce poztiai in vectorul de serpi a sarpelui cu encondarea 
// primita ca parametru.
int find_snake_with_enc(struct snake* snakes, int num_snakes, int encoding){
	int i, snake_id;
	
	for(i = 0; i < num_snakes; i++) {
		if(snakes[i].encoding == encoding) {
			return i;
		}
	}
}

// Functie ce returneaza pozitia vecinului cozii primita ca parametru prin line si col.
struct coord new_tail_neighbour(int** world, int num_lines, int num_cols, int line, int col) {
	struct coord new_tail_neighbour;
	
	if(nr_of_neighbours(world, num_lines, num_cols, line, col, false, 'U', 
						(&new_tail_neighbour)) == 1) {
		return new_tail_neighbour;
	}
}

void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	struct snake *snakes, int step_count, char *file_name) 
{
	struct tail_and_neighbour * tails_and_neighbour;
	tails_and_neighbour = (struct tail_and_neighbour*)malloc(num_snakes * 
							sizeof(struct tail_and_neighbour));
	int i, j, snake_id;
	struct coord found_neighbour;

	// Parcurgem matricea pentru a identifica pozitiile cozilor serpilor, 
	// pe care le introducem intr-un vector de structuri de tip 
	// tail_and_neighbour, formata din campul corespunzator cozii( indica  
	// pozitia pe linie si coloana) si campul corespunzator vecinului 
	// acesteia, cu aceleasi elemente identificatoare.

	#pragma omp parallel for private(i,j)
	for(i = 0; i < num_lines; i++) {
		for(j = 0; j < num_cols; j++) {
			if(world[i][j] != 0 && nr_of_neighbours(world, num_lines, num_cols, i, j, false, 'U', (&found_neighbour)) == 1 && check_if_snake_head(snakes, num_snakes, i, j) == 'U') {
				snake_id = find_snake_with_enc(snakes, num_snakes, world[i][j]);
				tails_and_neighbour[snake_id].tail.line = i;
				tails_and_neighbour[snake_id].tail.col = j;
				tails_and_neighbour[snake_id].tail_neighbour.line = found_neighbour.line;
				tails_and_neighbour[snake_id].tail_neighbour.col = found_neighbour.col;
			}
		}
	}

	bool collision_detected = false;
	struct coord new_coord;
	struct coord tail_neighbour;
	int k = 0;

	// Incepem sa contorizam rundele.
	for(i = 0; i < step_count; i++) {
			// Inainte de a modifica matricea, ne asiguram ca pe parcursul 
			// acestei runde nu vor aparea coliziuni intre oricare doi serpi. 
			// Acest lucru il realizam prin numararea vecinilor de pe directia 
			// fiecarui cap de sarpe si verificarea ca numarul acestora sa nu 
			// depaseasca 0.
			#pragma omp parallel for private(j) shared(world)
			for(j = 0; j < num_snakes; j++) {
				if(nr_of_neighbours(world, num_lines, num_cols, snakes[j].head.line, snakes[j].head.col, 
					true, snakes[j].direction, &found_neighbour) >= 1) {
					collision_detected = true;
				}
			}
			
			// Daca verificarea precedenta nu ne avertizeaza ca va avea 
			// loc o coliziune, incepem sa parcurgem vectorul de serpi, 
			// calculand pentru fiecare cap in parte noile coordonate 
			// bazandu-se pe directia specificata la input. Dupa aceste 
			// calcule, valoarile pozitiei capului sunt modificate, 
			// se identifica vecinul cozii, adica pozitia ce ii va lua 
			// locul, iar matricea este actualizata. 
			if(collision_detected == false) {
				#pragma omp parallel for private(j, tail_neighbour, new_coord) shared(world)
				for(j = 0; j < num_snakes; j++) {
					if(snakes[j].direction == 'N') {
						new_coord = move_north(snakes[j].head, num_lines);
					} else if(snakes[j].direction  == 'S') {
						new_coord = move_south(snakes[j].head, num_lines);
					} else if(snakes[j].direction  == 'E') {
						new_coord = move_east(snakes[j].head, num_cols);
					} else if(snakes[j].direction  == 'V') {
						new_coord = move_west(snakes[j].head, num_cols);
					}
					snakes[j].head.line = new_coord.line;
					snakes[j].head.col = new_coord.col;
					tail_neighbour = new_tail_neighbour(world, num_lines, num_cols, tails_and_neighbour[j].tail.line, tails_and_neighbour[j].tail.col);
					world[new_coord.line][new_coord.col] = snakes[j].encoding;
					world[tails_and_neighbour[j].tail.line][tails_and_neighbour[j].tail.col] = 0;
					tails_and_neighbour[j].tail = tail_neighbour;
				}
			}
	}
}