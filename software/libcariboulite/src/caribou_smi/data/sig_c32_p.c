typedef struct {
    uint16_t i;     // In-phase component
    uint16_t q;     // Quadrature component
    sig_meta;  // meta data for sync and rf path
} sig_c32_p;

// Utility functions for complex samples
static inline long calc_mag_sqrd(sig_c32_p sample) {
    return (long)(sample.i * sample.i + sample.q * sample.q);
}

// Extract normalized complex sample from 32-bit SMI data word
static inline sig_c32_p extract_sample(uint32_t data) {
    sig_c32_p sample;

    sample.sig_meta.sync = data & 0x0001;
    // Extract I/Q values
    sample.i = (data >> 17) & 0x1FFF;
    sample.q = (data >> 1) & 0x1FFF;

    // Normalize values
    if (sample.i >= 0x1000) sample.i -= 0x2000;
    if (sample.q >= 0x1000) sample.q -= 0x2000;

    return sample;
}

// Check if data matches SMI complex sample 32-bit data shape
static inline bool is_valid_shape(uint32_t data) {
    return (data & 0xC001C000) == 0x80004000;
}

typedef struct {
    bool sync;
    // other meta data values can be unpacked here
} sig_meta;
