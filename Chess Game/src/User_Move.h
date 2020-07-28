

#ifndef USER_MOVE_H
#define USER_MOVE_H
/*direction that chess piece moves: (n)orth is up, (e)ast is right etc.*/
enum direction {n, ne, e, se, s, sw, w, nw};

 /*The value is what has to be added to the queen's position in order to move in that direction. (n)orth, (n)orth(e)ast, (e)ast, etc. */
enum direction_value {n_value = -8, ne_value = -7, e_value = 1, se_value = 9, s_value = 8, sw_value = 7, w_value = -1, nw_value = -9};

/*Moves the queen. 
Returns 0 if no errors. 
Returns -10 if error occured (trying to move past a piece or invalid move). 
Returns 10 if capture occured*/
int MoveQueen(int queen_value, int arr[], int start, int end);

/*Gets direction that the queen moves. used in MoveQueen()
Returns 0 if no error
Returns -10 if error (Invalide Move)*/
int GetQueenDirection(int start, int end, enum direction_value *D_value);

/*Moves the bishop. 
Returns 0 if no errors. 
Returns -10 if error occured (trying to move past a piece or invalid move). 
Returns 10 if capture occured*/
int MoveBishop(int bishop_value, int arr[], int start, int end);

/*Gets direction that the queen moves. used in MoveQueen()
Returns 0 if no error
Returns -10 if error (Invalide Move)*/
int GetBishopDirection(int start, int end, enum direction_value *D_value);

/*Moves the rook. 
Returns 0 if no errors. 
Returns -10 if error occured (trying to move past a piece or invalid move). 
Returns 10 if capture occured*/
int MoveRook(int rook_value, int arr[], int start, int end);

/*Gets direction that the queen moves. used in MoveQueen()
Returns 0 if no error
Returns -10 if error (Invalide Move)*/
int GetRookDirection(int start, int end, enum direction_value *D_value);

/*Verifies if the king is in check or if moving it to a position will put it in check. 
Position parameter is the position to be verified, does not need to be the king's current position.
Returns 0 if not in check.
Returns 1 if in check.*/
int isKingInCheck(int king_value, int position);

/*Verifies if king is in checkmate.
Run isKingInCheck() before running this function as this one is a lot more code and would be a waste to run on every turn.
Only run this function if isKingInCheck() returns a 1 for the king's CURRENT position.
For position use only the King's CURRENT position.
Returns 1 if checkmate.
Returns 0 if not checkmate. (King could still be in check)
*/
int isKingInCheckMate(int king_value, int position);


#endif //USER_MOVE_H
