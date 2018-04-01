
#ifndef GWU50PC_H
#define GWU50PC_H

#include "lib/app.h"
#include "lib/timef.h"
#include "lib/acp/main.h"
#include "lib/acp/app.h"
#include "lib/udp.h"
#include "lib/tsv.h"
#include "lib/lcorrection.h"
#include "lib/device/max31850.h"

#define APP_NAME gwu50pc
#define APP_NAME_STR TOSTRING(APP_NAME)

#ifdef MODE_FULL
#define CONF_DIR "/etc/controller/" APP_NAME_STR "/"
#endif
#ifndef MODE_FULL
#define CONF_DIR "./config/"
#endif
#define CONF_MAIN_FILE CONF_DIR "main.tsv"
#define CONF_DEVICE_FILE CONF_DIR "device.tsv"
#define CONF_THREAD_FILE CONF_DIR "thread.tsv"
#define CONF_THREAD_DEVICE_FILE CONF_DIR "thread_device.tsv"
#define CONF_LCORRECTION_FILE CONF_DIR "lcorrection.tsv"

#define RETRY_COUNT 3

enum {
    ON = 1,
    OFF,
    DO,
    INIT,
    WTIME
} StateAPP;

struct device_st {
    int id;
    int pin;
    uint8_t address[MAX31850_SCRATCHPAD_BYTE_NUM];
    FTS result;
    LCorrection *lcorrection;
    Mutex mutex;
};
typedef struct device_st Device;

DEC_LIST(Device)
DEC_PLIST(Device)

struct thread_st {
    int id;
    DevicePList device_plist;
    I1List unique_pin_list;
    pthread_t thread;
    struct timespec cycle_duration;
};
typedef struct thread_st Thread;
DEC_LIST(Thread)

extern int readSettings();

extern void serverRun(int *state, int init_state);

extern void *threadFunction(void *arg);

extern void initApp();

extern int initData();

extern void freeData();

extern void freeApp();

extern void exit_nicely();

extern void exit_nicely_e(char *s);

#endif

