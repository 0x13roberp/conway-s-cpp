#include <iostream>
#include "/home/rober/libraries/screen.h"

// game size.
const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

// check the value of each cell, x & y are to calculate the coordinates of the neightbors.
bool is_alive(std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH>& game, const int x, const int y){
  int alive = 0;

  // if it's not  a border cell.
  if(x > 0 && game[x-1][y] == 1) alive+=1; // check the value of the left.
  if(x < GAME_WIDTH && game[x+1][y] == 1) alive+=1; // check the value of the right.
  if(y > 0 && game[x][y-1] == 1) alive+=1; // check the value of the top.
  if(y < GAME_HEIGHT && game[x][y+1] == 1) alive+=1; // check value of the floor.

  // check the corners.
  if(y > 0 && x > 0 && game[x-1][y-1] == 1) alive+=1; // top lef.
  if(y > 0 && x < GAME_WIDTH && game[x+1][y-1] == 1) alive+=1; // top right.
  if(y < GAME_HEIGHT && x > 0 && game[x-1][y+1] == 1) alive+=1; // down left.
  if(y < GAME_HEIGHT && x < GAME_WIDTH && game[x+1][y+1] == 1) alive+=1; // down right.

  // calculate if a cell die or live.
  if(game[x][y] == 1 && alive < 2) return false; // if its alive and has less than 2 alive neightbors: die by underpopulation.
  if(game[x][y] == 1 && (alive == 2 || alive == 3)) return true; // if its alive and has two or three alive neightbors: lives.
  if(game[x][y] == 1 && alive > 3) return false; // if its alive and has more than 3 alive neightbors: die by overpopulation.
  if(game[x][y] == 0 &&  alive == 3) return true; // if its dead and has exactly 3 alive neightbors. becomes a live cell.

  return false;
}

int main(){
  G screen; // from screen.h

  // create the two arrays.
  std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display {};
  std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap {};

  // generate random points. the probability of genete a live cell if 10%.
  for(auto& row : display)
    std::generate(row.begin(), row.end(), []() { return rand() % 10 == 0 ? 1 : 0;});

  // main loop.
  while(1){
    for(int i = 0; i < GAME_WIDTH; ++i){
      for(int j = 0; j < GAME_HEIGHT; ++j){
        if(is_alive(display, i, j)){
          swap[i][j] = 1;
        }
        else{
          swap[i][j] = 0;
        }
      }
    }

    // draw points.
    for(int i = 0; i < GAME_WIDTH; ++i){
      for(int j = 0; j < GAME_HEIGHT; ++j){
        if(swap[i][j]){
          screen.drawpixel(i,j);
        }
      }
    }
  
    // copy from swap to display.
    std::copy(swap.begin(), swap.end(), display.begin());

    // show to the screen.
    screen.update();
    SDL_Delay(20);
    screen.input();
    screen.clearpixels();
  }
}
