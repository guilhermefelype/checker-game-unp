#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "board.h"
#include "movement_handler.h"
#include "capture_handler.h"

void handleKeyboardInput(unsigned char key, Board& board, bool& isWhiteTurn);

#endif // INPUT_HANDLER_H
