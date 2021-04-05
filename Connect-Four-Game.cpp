#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int M = 7;
const int a_row = 4;
const int n_players = 2;
char marks[n_players] = {'X', 'O'};
char grid[N][M];
char temp[N][M];
//This function prints the grid of Connect Four Game as the game progresses
void print_grid() {
	for (int i = 0; i< n_players; i++) {
        cout << "Player " << i+1 << ": " << marks[i] << "  ";
        if (i < n_players-1)
            cout << "vs  ";
	}
	cout << "\n";
	cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < M; cout << "---", i++);
        cout << "--\n";
    }
}

//This function checks if there is a win row
bool check_row(char grid[N][M]){
	for(int row=N-1;row>-1;row--){
		for(int col=0;col<M-(a_row-1);col++){
			for(int i = col+1;i<col+a_row;i++){
				if(grid[row][col]==grid[row][i] && (grid[row][col] == 'X' || grid[row][col] == 'O')){
					if(i==(col+a_row)-1){
						return true;
					}
					continue;	
				}
				else{
					break;
				}
			}
		}
	}
	return false;
}
//This function checks if there is a win column
bool check_col(char grid[N][M]){
	for(int col=0; col<M ; col++){
		for(int row = N-1 ; row > a_row-2 ; row--){
			for(int i = row-1 ; i > row-a_row ; i--){
				if (grid[row][col] == grid[i][col] && (grid[row][col] == 'X' || grid[row][col] == 'O')){
					if(i==(row-a_row)+1){
						return true;
					}
					continue;
				}
				else{
					break;
				}
			}
		}
	}
	return false;
}

//This function checks if there is a win diagonal
bool check_diag(char grid[N][M]){
	for(int row = N-1 ; row > a_row-2; row--){
		for(int col = M-1 ; col > a_row-2 ; col--){
			int j = col -1;
			for(int i = row-1 ; i > row-a_row;i--){
				if (grid[row][col] == grid[i][j] && (grid[row][col] == 'X' || grid[row][col] == 'O')){
					if(i==(row-a_row)+1){
						return true;
					}
					j -= 1;
					continue;
				}
				else{
					break;
				}
			}
		}
	}
	
	for(int row = N-1 ; row > a_row-2; row--){
		for(int col = 0 ; col < M-(a_row-1) ; col++){
			int j = col +1;
			for(int i = row-1 ; i > row-a_row;i--){
				if (grid[row][col] == grid[i][j] && (grid[row][col] == 'X' || grid[row][col] == 'O')){
					if(i==(row-a_row)+1){
						return true;
					}
					j += 1;
					continue;
				}
				else{
					break;
				}
			}
		}
	}
	return false;
}

//This function checks if the game has a win state or not
bool check_win() {
	if(check_row(grid) || check_col(grid) || check_diag(grid)){
		return true;
	}
	else{
		return false;
	}
}

//This function copy the main array(grid) to a temporary array(temp) and replace empty spaces with marks
void arr_try(char mark){
	for(int i = 0;i<N;i++){
		for(int j = 0;j<M;j++){
			if(grid[i][j]==' '){
				temp[i][j] = mark;
			}else{
				temp[i][j] = grid[i][j];
			}
		}		
	}
}

//This function checks if the game has a tie state or not for the given mark
bool check_tie_player(char mark) {
	arr_try(mark);
	if(check_row(temp)||check_col(temp)||check_diag(temp)){
		return false;
	}
	return true;
}
//This function checks if the game has a tie state or not
bool check_tie() {
    bool all_tie = true;
    for (int i = 0; i < n_players; i++)
        if (!check_tie_player(marks[i]))
            all_tie = false;
    return all_tie;
}
//This function checks if given cell is empty or not 
bool check_empty(int i) {
	if (grid[0][i] == ' '){
		return true;	
	}
	else{
		return false;
	}
}
//This function checks if given position is valid or not 
bool check_valid_column(int i) {
	if( 0 <= i && i < M){
		return true;
	}
	else{
		return false;
	}
}
//This function gets the first empty place in column
int get_empty(int i){
	for(int row = N-1 ; row>-1 ; row-- ){
		if (grid[row][i]==' '){
			return row;
		}
	}
}
//This function sets the given mark to the given column
void set_cell(int i, char mark) {
	int row = get_empty(i);
	grid[row][i]=mark;
}
//This function clears the game structures
void grid_clear() {
	for(int i = 0;i<N;i++){
		for(int j = 0;j<M;j++){
			grid[i][j] = ' ';
		}
	}
}
//This function reads a valid position input
void read_input(int &i) {
    cout << "Enter the column index: ";
    cin >> i;
    while (!check_valid_column(i) || !check_empty(i)) {
        cout << "Enter a valid column index: ";
        cin >> i;
    }
}
//MAIN FUNCTION
void play_game() {
    cout << "Connect Four Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    int player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i;
		read_input(i);
        //Set the input position with the mark
        set_cell(i, marks[player]);
        //Check if the state of the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, Player " << marks[player] << " is won!\n";
            break;
        }
        //Check if the state of the grid has a tie state
        if (check_tie()) {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Woah! That's a tie!\n";
            break;
        }
        //Player number changes after each turn
        player = (player + 1) % n_players;
    }
}
int main() {
    while (true) {
    	grid_clear();
    	play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
    }
}
