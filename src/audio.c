#include "audio.h"
#include "engine.h"

int sampler_play(struct sampler *sampler, uint8_t priority) {
    for (int i = 0; i < AUDIO_QUEUE_LEN; i++) {
        uint8_t priority = engine.audio_queue[i].priority;
        // if (priority <)
    }
}

