#pragma once

#include <stdint.h>
#include <stdbool.h>

struct sampler {
    struct sample *sample;
    uint16_t position;
};

struct audio_event {
    uint8_t priority;
    struct sampler sampler;
};

struct sample {
    int16_t *data;
    uint16_t length;
};

// struct sampler *get_sampler(void *, struct audio_format);

int sampler_play(struct sampler *, uint8_t);
