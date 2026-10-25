#ifndef VL53L0X_TEMPLATE_H
#define VL53L0X_TEMPLATE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VL53L0X_UNIT_INCH ((uint8_t)0x50u)
#define VL53L0X_UNIT_CM   ((uint8_t)0x51u)
#define VL53L0X_UNIT_MM   ((uint8_t)0x52u)

#define VL53L0X_CMD_GET_RANGING_RESULT     ((uint8_t)0x00u)
#define VL53L0X_CMD_SET_RANGING_TIMING     ((uint8_t)0x01u)
#define VL53L0X_CMD_START_OFFSET_CAL       ((uint8_t)0x02u)
#define VL53L0X_CMD_START_XTALK_CAL        ((uint8_t)0x03u)
#define VL53L0X_CMD_GET_EEPROM_DATA        ((uint8_t)0x04u)
#define VL53L0X_CMD_RESTORE_FACTORY_CONFIG ((uint8_t)0x05u)
#define VL53L0X_CMD_RESERVED               ((uint8_t)0x06u)
#define VL53L0X_CMD_SET_VCSEL_PERIODS      ((uint8_t)0x07u)
#define VL53L0X_CMD_RESTART                ((uint8_t)0x08u)

#define VL53L0X_RANGING_FRAME_SIZE ((uint8_t)20u)

typedef enum {
    VL53L0X_OK = 0,
    VL53L0X_ERR_ARG,
    VL53L0X_ERR_IO,
    VL53L0X_ERR_TIMEOUT
} vl53l0x_status_t;

typedef uint8_t (*vl53l0x_i2c_write_fn)(uint8_t address, const uint8_t *tx, uint8_t tx_len, void *user_ctx);
typedef uint8_t (*vl53l0x_i2c_read_fn)(uint8_t address, uint8_t *rx, uint8_t rx_len, void *user_ctx);
typedef void (*vl53l0x_delay_ms_fn)(uint16_t delay_ms, void *user_ctx);

typedef struct {
    vl53l0x_i2c_write_fn i2c_write;
    vl53l0x_i2c_read_fn i2c_read;
    vl53l0x_delay_ms_fn delay_ms;
    void *user_ctx;
    uint16_t max_range_mm;
    uint16_t poll_interval_ms;
    uint16_t max_poll_count;
} vl53l0x_template_cfg_t;

typedef struct {
    vl53l0x_template_cfg_t cfg;
} vl53l0x_template_t;

typedef struct {
    uint16_t range_mm;
    uint8_t status;
    uint16_t signal_kcps;
    uint16_t ambient_kcps;
    uint16_t sigma_mm;
    uint16_t ambient_per_spad_kcps;
    uint16_t signal_per_spad_kcps;
    uint16_t spad_count;
} vl53l0x_measurement_t;

vl53l0x_status_t vl53l0x_template_init(vl53l0x_template_t *ctx, const vl53l0x_template_cfg_t *cfg);
vl53l0x_status_t vl53l0x_template_send_simple(vl53l0x_template_t *ctx, uint8_t dev_address, uint8_t command_id);
vl53l0x_status_t vl53l0x_template_set_new_address(vl53l0x_template_t *ctx, uint8_t dev_address, uint8_t new_address);
vl53l0x_status_t vl53l0x_template_set_ranging_timing(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    uint8_t timebudget,
    uint16_t intermeasurement_time_ms
);
vl53l0x_status_t vl53l0x_template_start_offset_cal(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    int16_t cal_distance_mm,
    uint16_t samples_nbr
);
vl53l0x_status_t vl53l0x_template_start_xtalk_cal(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    uint16_t cal_distance_mm,
    uint16_t samples_nbr
);
vl53l0x_status_t vl53l0x_template_set_vcsel_periods(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    uint8_t pre_range_vcsel_period,
    uint8_t final_range_vcsel_period
);
vl53l0x_status_t vl53l0x_template_read_ranging_frame(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    uint8_t *frame,
    uint8_t frame_len
);
vl53l0x_status_t vl53l0x_template_get_measurement(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    uint8_t units,
    vl53l0x_measurement_t *measurement,
    uint16_t *attempts
);
vl53l0x_status_t vl53l0x_template_get_measurements(
    vl53l0x_template_t *ctx,
    const uint8_t *dev_addresses,
    uint8_t dev_count,
    uint8_t units,
    vl53l0x_measurement_t *measurements,
    uint16_t *attempts,
    vl53l0x_status_t *statuses
);

bool vl53l0x_template_status_is_accepted(uint8_t status);
const char *vl53l0x_template_status_text(uint8_t status);
uint16_t vl53l0x_template_convert_range(uint16_t range_mm, uint8_t units);

void vl53l0x_template_demo_run(
    vl53l0x_template_t *ctx,
    uint8_t dev_address,
    uint8_t units,
    uint16_t period_ms,
    uint16_t max_samples
);
void vl53l0x_template_demo_run_all(
    vl53l0x_template_t *ctx,
    const uint8_t *dev_addresses,
    uint8_t dev_count,
    uint8_t units,
    uint16_t period_ms,
    uint16_t max_cycles
);
void vl53l0x_template_demo_run_all_simultaneous(
    vl53l0x_template_t *ctx,
    const uint8_t *dev_addresses,
    uint8_t dev_count,
    uint8_t units,
    uint16_t wait_ms,
    uint16_t period_ms,
    uint16_t max_cycles
);

#ifdef __cplusplus
}
#endif

#endif