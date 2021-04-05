'''
Assigning values to the grid
The grid will look like this:
  0,0 | 0,1 | 0,2 | 0,3 | 0,4 | 0,5 | 0,6
  1,0 | 1,1 | 1,2 | 1,3 | 1,4 | 1,5 | 1,6
  2,0 | 2,1 | 2,2 | 2,3 | 2,4 | 2,5 | 2,6
  3,0 | 3,1 | 3,2 | 3,3 | 3,4 | 3,5 | 3,6
  4,0 | 4,1 | 4,2 | 4,3 | 4,4 | 4,5 | 4,6
  5,0 | 5,1 | 5,2 | 5,3 | 5,4 | 5,5 | 5,6
'''
N, M = 6, 7
a_row = 4
grid = []
marks=['X','O']
#This function prints the grid of Connect Four Game as the game progresses
def print_grid():
    print("Player 1: X  vs  Player 2: O")
    print('--' + '---' * M + '--')
    for i in range(N):
        print(end='|  ')
        for j in range(M):
            print(grid[i][j], end='  ')
        print(end='|')
        print()
        print('--' + '---' * M + '--')

#This function checks the existence of any winning consecutive horizontal four 
def check_rows(grid):
    for row in range(N-1,-1,-1):
        for col in range(M-(a_row-1)):
            for i in range(col+1,col+a_row):
                if grid[row][col] == grid[row][i] and grid[row][col] in marks:
                    continue
                else:
                    break
            else:
                return True
    return False

#This function checks the existence of any winning consecutive vertical four 
def check_cols(grid):
    for col in range(M):
        for row in range(N-1,a_row-2,-1):
            for j in range(row-1,row-a_row,-1):
                if grid[row][col] == grid[j][col] and grid[row][col] in marks:
                    continue
                else:
                    break
            else:
                return True
    return False

#This function checks the existence of any winning consecutive diagonal four
def check_diags(grid):
    for row in range(N-1,a_row-2,-1):
        for col in range(M-1,a_row-2,-1):
            j = col-1
            for i in range(row-1,row-a_row,-1):
                if grid[row][col] == grid[i][j] and grid[row][col] in marks:
                    j -= 1
                    continue
                else:
                    break
            else:
                return True

    for row in range(N-1,a_row-2,-1):
        for col in range(0,M-(a_row-1)):
            j = col+1
            for i in range(row-1,row-a_row,-1):
                if grid[row][col] == grid[i][j] and grid[row][col] in marks:
                    j += 1
                    continue
                else:
                    break
            else:
                return True

    return False

#This function checks if row or column or diagonal is full with same characters
def check_win():
    if check_rows(grid) or check_cols(grid) or check_diags(grid):
        return True
    else:
        return False

#This function makes a temporary copy from grid and fill the spaces with specific mark
def list_try(mark):
    temp=[]
    for row in range(N):
        l = []
        for col in range(M):
            if grid[row][col] == '.':
                l.append(mark)
            else:
                l.append(grid[row][col])
        temp.append(l)
    return temp

#This function checks if the game has a tie state or not for the given mark
def check_tie_player(mark):
    temp = list_try(mark)
    if check_rows(temp) or check_cols(temp) or check_diags(temp):
        return False
    else:
        return True

#This function checks if there is a tie status
def check_tie():
    all_tie = True
    for mark in marks:
        if not check_tie_player(mark):
            all_tie = False
    return all_tie

#This function checks if given column has empty cell or not 
def check_empty_col_cell(i):
    index = None
    for j in range(N-1,-1,-1):
        if grid[j][i] =='.' :
            index = j
            break
    return index

#This function checks if given cell is empty or not 
def check_empty(i):
    if grid[0][i] == '.':
        return True
    else:
        return False

#This function checks if given position is valid or not 
def check_valid_column(i):
    if 0 <= i < M :
        return True
    else:
        return False

#This function sets a value to a cell
def set_cell(i, mark):
    row = check_empty_col_cell(i)
    grid[row][i] = mark


#This function clears the grid
def grid_clear():
    grid.clear()
    for i in range(N):    
        grid.append(['.']*M)


#MAIN FUNCTION
def play_game():
    print("Connect Four Game!")
    print("Welcome...")
    print("============================")
    player = 0
    while True:
        #Prints the grid
        print_grid()
        #Set mark value based on the player
        mark = 'X' if player == 0 else 'O'
        #Takes input from the user to fill in the grid
        print('Player %s' % mark)
        i = int(input('Enter the column index: '))
        while not check_valid_column(i) or not check_empty(i):
            i = int(input('Enter a valid column index: '))
        #Set the input position with the mark
        set_cell(i, mark)
        #Check if the state of the grid has a win state
        if check_win():
            #Prints the grid
            print_grid()
            print('Congrats, Player %s is won!' % mark)
            break
        
        #Check if the state of the grid has a tie state
        if check_tie():
            #Prints the grid
            print_grid()
            print("Woah! That's a tie!")
            break		
        #Player number changes after each turn
        player = 1 - player 


while True:
	grid_clear()
	play_game()
	c = input('Play Again [Y/N] ')
	if c not in 'yY':
		break
