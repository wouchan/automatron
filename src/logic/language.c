#include "language.h"

#include <complex.h>
#include <string.h>

#include "alphabet.h"
#include "grammar.h"

extern struct grammar grammar;

struct language language = { .words = { { 0 } }, .len = 0 };
static struct word_queue queues[2] = { 0 };
static bool active_queue = 0;

#define MAX_ITERATIONS 1024

bool add_language_word(char * word) {
    for (usize i = 0; i < strlen(word); i += 1) {
        if (!is_terminal(word[i])) {
            return false;
        }
    }

    for (usize i = 0; i < language.len; i += 1) {
        if (strcmp(word, language.words[i]) == 0) {
            return true;
        }
    }

    strcpy(language.words[language.len], word);
    language.len += 1;

    return true;
}

void apply_possible_rules(void) {
    for (usize i = 0; i < 1024; i += 1) {
        if (language.len >= LANGUAGE_SIZE) {
            return;
        }

        for (usize w = 0; w < queues[active_queue].len; w += 1) {
            for (usize rule_idx = 0; rule_idx < grammar.len; rule_idx += 1) {
                usize input_len = strlen(grammar.inputs[rule_idx]);
                isize max_idx = strlen(queues[active_queue].words[w]) - input_len + 1;

                for (                            //
                    usize start_idx = 0;         //
                    (isize) start_idx < max_idx; //
                    start_idx += 1               //
                ) {                              //
                    if (                         //
                        memcmp(
                            grammar.inputs[rule_idx], &queues[active_queue].words[w][start_idx],
                            input_len
                        ) == 0 //
                    ) {        //
                        char new_word[WORD_SIZE];
                        strcpy(new_word, queues[active_queue].words[w]);
                        if (!apply_grammar_rule(new_word, start_idx, rule_idx)) {
                            break;
                        }

                        if (!add_language_word(new_word)) {
                            if (queue_contains_word(new_word, active_queue)) {
                                continue;
                            }

                            if (!add_to_word_queue(new_word, !active_queue)) {
                                continue;
                            }
                        }
                    }
                }
            }
        }

        queues[active_queue].len = 0;
        active_queue = !active_queue;
    }
}

void generate_language(void) {
    language.len = 0;
    active_queue = 0;
    queues[0].len = 0;
    queues[1].len = 0;

    char word[WORD_SIZE] = "S";
    add_to_word_queue(word, active_queue);
    apply_possible_rules();
}

bool queue_contains_word(char * word, bool queue_idx) {
    for (usize i = 0; i < queues[queue_idx].len; i += 1) {
        if (strcmp(queues[queue_idx].words[i], word) == 0) {
            return true;
        }
    }

    return false;
}

bool add_to_word_queue(char * word, bool queue_idx) {
    if (queues[queue_idx].len >= QUEUE_SIZE) {
        return false;
    }

    if (queue_contains_word(word, queue_idx)) {
        return true;
    }

    strcpy(queues[queue_idx].words[queues[queue_idx].len], word);
    queues[queue_idx].len += 1;

    return true;
}
