#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "tictactoe.h"
//---------------------------------------------------------------------------
///TicTacToe default contructor creates an empty board,
///where the current turn is to player1.
TicTacToe::TicTacToe()
  : m_board(boost::extents[3][3]),
    m_current_player(TicTacToe::player1)
{
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = TicTacToe::empty;
  }

  assert(GetCurrentTurn() == 0);
  assert(GetCurrentPlayer() == TicTacToe::player1);
}
//---------------------------------------------------------------------------
///TicTacToe contructor from summized state integer.
TicTacToe::TicTacToe(const int state)
  : m_board(boost::extents[3][3]),
    m_current_player(-1)
{
  SetSummarizedState(state);

  assert(GetCurrentPlayer() == TicTacToe::player1
    ||   GetCurrentPlayer() == TicTacToe::player2);
}
//---------------------------------------------------------------------------
bool TicTacToe::CanDoMove(const int x, const int y) const
{
  if (m_board[x][y]==0) return true;
  return false;
}
//---------------------------------------------------------------------------
void TicTacToe::DoMove(const int x, const int y)
{
  assert(CanDoMove(x,y));
  //std::clog << "Player " << m_current_player
  //  << ": (" << x << "," << y << ")\n";
  m_board[x][y] = m_current_player;
  m_current_player = (m_current_player == 1 ? 2 : 1);
}
//---------------------------------------------------------------------------
///GetCurrentTurn returns the turn number.
int TicTacToe::GetCurrentTurn() const
{
  int turn = 0;
  for (int i=0; i!=9; ++i)
  {
    if (m_board[i/3][i%3] != TicTacToe::empty) ++turn;
  }
  return turn;
}
//---------------------------------------------------------------------------
///GetSquare returns the content at square (x,y)
int TicTacToe::GetSquare(const int x,const int y) const
{
  return m_board[x][y];
}
//---------------------------------------------------------------------------
///GetSummarizedState returns an integer summarizing the
///state, which is both tic-tac-toe board and whose turn it is.
///In trinary, for lowest order digit:\n
///# : content\n
///0 : content of (0,0)\n
///1 : content of (1,0)\n
///2 : content of (2,0)\n
///3 : content of (0,1)\n
///4 : content of (1,1)\n
///5 : content of (2,1)\n
///6 : content of (0,2)\n
///7 : content of (1,2)\n
///8 : content of (2,2)\n
///9 : current turn\n
///For indices [0,8] content is stored as:
///[#] : description\n
/// 0  : empty\n
/// 1  : player1\n
/// 2  : player2\n
///For index 9 content is stored as:
///[#] : description\n
/// 0  : ERROR\n
/// 1  : player1\n
/// 2  : player2\n
int TicTacToe::GetSummarizedState() const
{
  int z = m_board[0][0];
  for (int i=1; i!=9; ++i)
  {
    z += (m_board[i/3][i%3] * IntPower(3,i));
  }
  z += (m_current_player * IntPower(3,9));
  return z;
}
//---------------------------------------------------------------------------
///GetWinner returns the winner.
///TicTacToe::no_winner : no winner yet\n
///TicTacToe::player1   : player1 has won\n
///TicTacToe::player2   : player2 has won\n
///TicTacToe::draw      : draw\n
int TicTacToe::GetWinner() const
{
  //Check rows
  for (int y=0; y!=3; ++y)
  {
    if (m_board[0][y] != TicTacToe::empty
     && m_board[0][y] == m_board[1][y]
     && m_board[1][y] == m_board[2][y])
      return m_board[0][y];
  }
  //Check collumns
  for (int x=0; x!=3; ++x)
  {
    if (m_board[x][0] != TicTacToe::empty
     && m_board[x][0] == m_board[x][1]
     && m_board[x][1] == m_board[x][2])
       return m_board[x][0];
  }
  //Check diagonal
  if (m_board[0][0] != TicTacToe::empty
   && m_board[0][0] == m_board[1][1]
   && m_board[1][1] == m_board[2][2])
    return m_board[1][1];
  //Check other diagonal
  if (m_board[0][2] != TicTacToe::empty
   && m_board[0][2] == m_board[1][1]
   && m_board[1][1] == m_board[2][0])
    return m_board[1][1];
  //Check for draw
  if (NoEmptySquares())return TicTacToe::draw;
  //No winner
  return TicTacToe::no_winner;
}
//---------------------------------------------------------------------------
bool TicTacToe::NoEmptySquares() const
{
  for (int i=0; i!=9; ++i)
  {
    if (m_board[i/3][i%3] == TicTacToe::empty) return false;
  }
  return true;
}
//---------------------------------------------------------------------------
///SetBoard sets a tic-tac-toe board.
void TicTacToe::SetBoard(const boost::multi_array<int,2>& board)
{
  m_board = board;

  #ifndef NDEBUG
  {
    for (int i=0; i!=9; ++i)
    {
      const int z = m_board[i/3][i%3];
      assert(z == TicTacToe::empty
          || z == TicTacToe::player1
          || z == TicTacToe::player2);
    }
  }
  #endif
}
//---------------------------------------------------------------------------
///SetSquare sets the value of square (x,y).
void TicTacToe::SetSquare(
  const int x, const int y, const int square_state)
{
  assert(square_state == TicTacToe::empty
    || square_state == TicTacToe::player1
    || square_state == TicTacToe::player2);

  m_board[x][y] = square_state;

  //Internal test
  assert(GetSquare(x,y)==square_state);
}
//---------------------------------------------------------------------------
///SetSummarizedState sets the TicTacToe state,
///which is both tic-tac-toe board and whose turn it is.
void TicTacToe::SetSummarizedState(const int original_state)
{
  int s = original_state;
  for (int i=0; i!=9; ++i)
  {
    m_board[i/3][i%3] = s % 3;
    s/=3;
  }
  if (s!=TicTacToe::player1 && s != TicTacToe::player2)
  {
    throw std::invalid_argument("Invalid TicTacToe state");
  }

  m_current_player = s;

  //Internal check
  assert(GetSummarizedState()==original_state);
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const TicTacToe& t)
{
  os
    << t.GetSquare(0,0)
    << t.GetSquare(1,0)
    << t.GetSquare(2,0)
    << '\n'
    << t.GetSquare(0,1)
    << t.GetSquare(1,1)
    << t.GetSquare(2,1)
    << '\n'
    << t.GetSquare(0,2)
    << t.GetSquare(1,2)
    << t.GetSquare(2,2);
  return os;
}
//---------------------------------------------------------------------------
bool operator==(const TicTacToe& lhs, const TicTacToe& rhs)
{
  return lhs.GetBoard() == rhs.GetBoard()
      && lhs.GetCurrentPlayer() == rhs.GetCurrentPlayer()
      && lhs.GetCurrentTurn() == rhs.GetCurrentTurn();
}
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppIntPower.htm
int IntPower(const int base, const int exponent)
{
  assert(exponent != 0
    && "When calculating IntPower(x,0) the result "
       "might be zero or one, depending on the context");
  assert(exponent > 0);

  int result = base;
  for (int i=1; i!=exponent; ++i)
  {
    result*=base;
  }
  return result;
}
//---------------------------------------------------------------------------
