#include "Rpm.h"
#include "driver/pcnt.h"

const int16_t COUNTER_MAX = 32767;

esp_err_t Rpm::begin()
{
    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = _pin,
        .ctrl_gpio_num = PCNT_PIN_NOT_USED,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_KEEP,
        .pos_mode = PCNT_COUNT_INC,
        .neg_mode = PCNT_COUNT_INC,
        .counter_h_lim = COUNTER_MAX,
        .counter_l_lim = 0,
        .unit = PCNT_UNIT_0,
        .channel = PCNT_CHANNEL_0,
    };

    // Init
    esp_err_t err;
    err = pcnt_unit_config(&pcnt_config);
    if (err != ESP_OK)
    {
        log_e("pcnt_unit_config failed: %d %s", err, esp_err_to_name(err));
        return err;
    }

    err = pcnt_counter_clear(pcnt_config.unit);
    if (err != ESP_OK)
    {
        log_e("pcnt_counter_clear failed: %d %s", err, esp_err_to_name(err));
        return err;
    }

    err = pcnt_counter_resume(pcnt_config.unit);
    if (err != ESP_OK)
    {
        log_e("pcnt_counter_resume failed: %d %s", err, esp_err_to_name(err));
        return err;
    }

    return ESP_OK;
}

uint16_t Rpm::rpm()
{
    // Append to buffer
    auto now = micros();
    int16_t count = 0;
    pcnt_get_counter_value(_unit, &count);

    _index = (_index + 1) % SAMPLES;
    _values[_index] = {
        .time = now,
        .count = count,
    };

    // Calculate
    auto oldest = _values[(_index + 1) % SAMPLES];

    auto revs = ((int32_t)COUNTER_MAX + count - oldest.count) % COUNTER_MAX;
    auto elapsed = now - oldest.time;

    return 15000000 * revs / elapsed;
}