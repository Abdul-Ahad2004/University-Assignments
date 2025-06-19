import json
import time
import copy
from collections import deque

# Problem Statement:

# The problem involves solving a Four-in-a-Row game using search algorithms (BFS, DFS, and IDS) to find a sequence of moves that transforms an initial board state into a predefined goal state within a limited depth. The goal is to analyze the efficiency of these algorithms in terms of memory usage, time taken, and nodes explored while ensuring that results are stored properly for evaluation.

# Part1 Questions:

# 1-Game Board State:
#  I am taking the game board as a 6x7 2D list in implementation where each cell can contain:
# "-" ,"O" ,"X"
# "-" it represents an empty cell.
# "O" it represents a piece placed by one player.
# "X" it represents a piece placed by the opponent.
# The board is stored in self.board, which is loaded from a file using the load_state() function.

# -The initial state will be stored in initial_state.txt, with 4 rows filled with X and O in a pre-defined pattern.
# I am considering the following initial state in the file:
# - - - - - - -
# - - - - - - -
# - - X - - - -
# - O X O - - -
# O X O X O - -
# X O X O X O -

# The goal state will be stored in goal_state.txt, with 4 rows filled such that the goal can be reached within 5 moves.
# I am considering the following goal state in the file, which easily can be achieved in the 5 depths:
# - - - - - - -
# - - - - - - -
# - - X - - - -
# - O X O - - -
# O X O X O X -
# X O X O X O O

# 2- Valid Moves:
# I am taking a valid move in the game will be any column where a piece can be dropped (i.e., the topmost row in that column which is still containing "-").

# Valid moves can be get through the function get_valid_moves() which returns a list of column indices (0 to 6) where a move can still be made.

# 3- State Transitions (Making a Move):
# A state will be transition  when a player places a piece in one of the valid columns. The new state (board configuration) is created by updating the lowest available row in that column.

#  State can be transitioned through the function make_move(self, board, col, piece) which loops from the bottom row to the top having the same column number it receives as an argument, placing the piece in the first empty cell it finds.And the piece type receiving in an argument depends upon the path length at even numbers , we will receive O and at odd numbers, receive X

# 4. Goal State Checking (Win Detection)
# A goal state occurs when a player achieves the goal state which I defined in the goal_state.txt

# This is checked using the function is_goal_state(self, board) which actually compares the current board with the pre-defined goal state stored in goal_state variable.

class FourInARow:
    ROWS = 6
    COLS = 7
    #Taking the max depth is 10 for each algorithm
    MAX_DEPTH = 5 

    def __init__(self):
        self.board = self.load_state("initial_state.txt")
        self.goal_state = self.load_state("goal_state.txt")
    
    #load the board from inital_state.txt file
    def load_state(self, filename):
        with open(filename, "r") as file:
            return [line.strip().split() for line in file.readlines()]

   
    # save the results after each algorithm in JSON file to keep the record for the comparison
    def save_search_results(self, algorithm, solution_path, nodes_explored, time_taken, moves_needed, depth_reached):
        result = {
            "Search Algorithm": algorithm,
            "Solution Path": solution_path if solution_path else "No solution found",
            "Nodes Explored": nodes_explored,
            "Time Taken": time_taken,
            "Moves Needed": moves_needed,
            "Depth Reached": depth_reached
        }
        with open(f"search_results_{algorithm}.json", "w") as file:
            json.dump(result, file, indent=4)
    
    

    #Appends the final state in the final_state.txt of every algorithm
    def save_state(self, algorithm, board):
        #opened file in append mode to add all algo state in one file
        with open("final_state.txt", "a") as file: 
            file.write(f"\n** {algorithm} Final State **\n")
            for row in board:
                file.write(" ".join(row) + "\n")
            file.write("\n" + "-" * 30 + "\n")

    # Returns columns where a piece can be dropped
    def get_valid_moves(self, board):
        return [col for col in range(self.COLS) if board[0][col] == "-"]

    #Drops a piece into a column (starting from the bottom row).
    def make_move(self, board, col, piece): 
        new_board = copy.deepcopy(board)
        for row in reversed(range(self.ROWS)):
            if new_board[row][col] == "-":
                new_board[row][col] = piece
                return new_board
        return None  # If column is full, return None

    #Checks if the board matches the goal state.
    def is_goal_state(self, board):
        return board == self.goal_state

# Print the board state
def print_board(board):
    for row in board:
        print(" ".join(row))
    print("\n")
# BFS algorithm explores the game board level by level using a queue, ensuring the shortest path to the goal state. It dequeues a board state, checks if it has been visited, and expands all valid moves, adding them to the queue.
def bfs(game):
    start_time = time.time()
    # (board, path, depth)
    queue = deque([(game.board, [], 0)]) 
    visited = set()
    nodes_explored = 0

    while queue:
        board, path, depth = queue.popleft()
        nodes_explored += 1
        board_tuple = tuple(map(tuple, board)) 
        if board_tuple in visited or depth > game.MAX_DEPTH:
            continue
        visited.add(board_tuple)
        if game.is_goal_state(board):
            time_taken = time.time() - start_time
            #if goal state is achieved then store the informationincludig path and nodes to the file
            game.save_search_results("BFS", path, nodes_explored, time_taken, len(path), depth)
            return path, board
        for move in game.get_valid_moves(board):
            new_board = game.make_move(board, move, 'O' if len(path) % 2 == 0 else 'X')
            if new_board:
                # print_board(new_board)
                queue.append((new_board, path + [move], depth + 1))

    time_taken = time.time() - start_time
    game.save_search_results("BFS", None, nodes_explored, time_taken, 0, game.MAX_DEPTH)
    return None, game.board

#DFS algorithm uses a stack to explore game states deeply before backtracking. It pops a board state, checks if it has been visited, and explores valid moves by pushing them onto the stack.
def dfs(game):
    start_time = time.time()
    stack = [(game.board, [], 0)]  # (board, path, depth)
    visited = set()
    nodes_explored = 0

    while stack:
        board, path, depth = stack.pop()
        nodes_explored += 1
        board_tuple = tuple(map(tuple, board))
        if board_tuple in visited or depth > game.MAX_DEPTH:
            continue
        visited.add(board_tuple)
        if game.is_goal_state(board):
            time_taken = time.time() - start_time
            game.save_search_results("DFS", path, nodes_explored, time_taken, len(path), depth)
            return path, board
        for move in game.get_valid_moves(board):
            new_board = game.make_move(board, move, 'O' if len(path) % 2 == 0 else 'X')
            if new_board:
                # print_board(new_board)
                stack.append((new_board, path + [move], depth + 1))

    time_taken = time.time() - start_time
    game.save_search_results("DFS", None, nodes_explored, time_taken, 0, game.MAX_DEPTH)
    return None, game.board

# IDS algorithm iteratively deepens the search depth, using a recursive depth-limited search (DLS) to explore game states within a set depth. It increases the depth limit step by step.
def ids(game):
    start_time = time.time()
    nodes_explored = 0

    def dls(board, path, depth):
        nonlocal nodes_explored
        if depth > game.MAX_DEPTH:
            return None
        nodes_explored += 1
        if game.is_goal_state(board):
            return path, board
        for move in game.get_valid_moves(board):
            new_board = game.make_move(board, move, 'O' if len(path) % 2 == 0 else 'X')
            if new_board:
                # print_board(new_board)
                result = dls(new_board, path + [move], depth + 1)
                if result:
                    return result
        return None

    for depth in range(1, game.MAX_DEPTH + 1):
        result = dls(game.board, [], depth)
        if result:
            path, final_board = result
            time_taken = time.time() - start_time
            game.save_search_results("IDS", path, nodes_explored, time_taken, len(path), depth)
            return path, final_board

    time_taken = time.time() - start_time
    game.save_search_results("IDS", None, nodes_explored, time_taken, 0, game.MAX_DEPTH)
    return None, game.board

# Main function code to run and check all the above implemented code
if __name__ == "__main__":
    game = FourInARow()
   

    print("Performing DFS!!")
    dfs_solution, dfs_final_board = dfs(game)
    game.save_state("DFS", dfs_final_board)

    # print("Performing IDS!!")
    # ids_solution, ids_final_board = ids(game)
    # game.save_state("IDS", ids_final_board)

    # print("Performing BFS!!")
    # bfs_solution, bfs_final_board = bfs(game)
    # game.save_state("BFS", bfs_final_board)

    print("All results saved to JSON files respective to the Algorithms! and final states stored in txt file.")

# Part3 Questions:

# 1- Approximate Number of Nodes in the Complete Game Tree for the First Move:
    
# As, we are taking the branching factor (average number of valid moves per turn) is 5.

# For the first move, there are 5 possible moves.
# At depth 1, each move can lead to 5 new possible states, so there are: 5^1=5

# At depth 2, there are: 5^2=25


# So, the approximate number of nodes in the complete game tree for first move up to depth 5 is: 1+5+25=31

# 2- Performance Comparison of BFS, DFS, and IDS:

# Observations from the Given Results specified in the json files respective of Algorithms:

# The results recorded when the goal state is set at a depth of 5 show that BFS explored 56 nodes and took 0.0176 seconds to find the solution. DFS explored significantly more nodes, 2041, and took 0.0627 seconds. IDS had the highest number of nodes explored at 2660 and took the longest time at 0.3639 seconds.

# Memory Usage Comparison:
# Breadth-First Search (BFS) consumes the most memory because it stores all nodes at the current level before proceeding to the next. Depth-First Search (DFS) uses less memory as it only stores a path from the root to a leaf node. Iterative Deepening Search (IDS) falls in between, as it repeatedly executes DFS with increasing depth limits, leading to moderate-to-high memory consumption.Their space complexities are: O(b^d)(exponential),	O(bd)(linear) and O(bd)(like DFS) respectively.

# Time to Find Solution:
# In this case, BFS was the fastest, finding the solution in just 0.0176 seconds. DFS was slower at 0.0627 seconds due to exploring unnecessary paths. IDS was the slowest at 0.3639 seconds because it re-ran DFS multiple times with increasing depth limits.

# Number of Nodes Explored:
# BFS explored the fewest nodes (56), which is expected since it searches level by level and finds the shortest path efficiently. DFS explored significantly more nodes (2041) because it goes deep into the tree before backtracking. IDS explored the highest number of nodes (2660) because it executes DFS repeatedly at different depth limits.

# Best Algorithm for Finding the Shortest Path:
# BFS is the best for finding the shortest path, as it guarantees the optimal solution in an unweighted search space. DFS is not suitable for shortest path problems because it may go deep into the wrong direction before backtracking. IDS, while more memory-efficient than BFS, is still slower since it repeatedly runs DFS.

# Best Algorithm for Large Search Spaces:
# For large search spaces, BFS is impractical due to its high memory requirements. DFS is more efficient in terms of memory but does not guarantee an optimal solution. IDS is a good compromise, as it retains the benefits of BFS while using less memory.

# These results are specific to the current setup, where the goal state is defined at a fixed depth. If the goal state were deeper, DFS might take even longer, and IDS would explore an even larger number of nodes. BFS would still be optimal for shortest paths but would require significant memory.

# 3- Storage Format for Game States and Search Results:
# To store the game states and search results, I am using the following formats:

# Text files (.txt) for game board states, which stores the whole state of board of every algorithm i.e., BFS, DFS and IDS

# JSON files (.json) for search results, which stores the "Search Algorithm","Solution Path"(if exists),"Nodes Explored","Time Taken","Moves Needed","Depth Reached" 