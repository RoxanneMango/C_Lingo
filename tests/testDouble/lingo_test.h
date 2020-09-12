#ifndef LINGO_TEST_H
#define LINGO_TEST_H

#include "fake_lingo.h"
#include "../tests.h"

bool lingo_start_test(struct Lingo * lingo, Param * param);
bool lingo_stop_test(struct Lingo * lingo, Param * param);
bool lingo_game_rotation_test(struct Lingo * lingo);
//
bool lingo_isWon_ack_test(struct Lingo * lingo, Param * param);
//
bool lingo_invalid_guess_test(struct Lingo * lingo, Param * param);
bool lingo_wrong_guess_test(struct Lingo * lingo, Param * param);
bool lingo_correct_guess_test(struct Lingo * lingo, Param * param);
//
bool lingo_time_test(struct Lingo * lingo);

#endif // LINGO_TEST_H