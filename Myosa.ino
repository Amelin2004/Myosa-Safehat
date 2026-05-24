#include <Wire.h>

#include <MPU6500_WE.h>
#include <Adafruit_BMP085.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// =====================================================
// OLED
// =====================================================

Adafruit_SH1106G display =
    Adafruit_SH1106G(128, 64, &Wire);

// =====================================================
// MPU6500
// =====================================================

#define MPU6500_ADDR 0x69

MPU6500_WE mpu =
    MPU6500_WE(MPU6500_ADDR);

// =====================================================
// BMP180
// =====================================================

Adafruit_BMP085 bmp;

// =====================================================
// APDS9930 REGISTERS
// =====================================================

#define APDS_ADDR 0x39

#define APDS_ENABLE 0x80
#define APDS_ATIME 0x81
#define APDS_PTIME 0x82
#define APDS_CONTROL 0x8F

#define APDS_CDATAL 0x94
#define APDS_CDATAH 0x95

#define APDS_PDATAL 0x9C
#define APDS_PDATAH 0x9D

// =====================================================
// THRESHOLDS
// =====================================================

#define FALL_THRESHOLD 0.3
#define IMPACT_THRESHOLD 2.5

#define LIGHT_THRESHOLD 20
#define PROX_THRESHOLD 200

// =====================================================
// GLOBALS
// =====================================================

float baselinePressure = 0;

bool freefallDetected = false;
bool impactDetected = false;

unsigned long inactivityStart = 0;

// =====================================================
// LOW LEVEL APDS FUNCTIONS
// =====================================================

void apdsWrite(uint8_t reg, uint8_t value) {

    Wire.beginTransmission(APDS_ADDR);

    Wire.write(reg);

    Wire.write(value);

    Wire.endTransmission();
}

uint16_t apdsRead16(
    uint8_t lowReg,
    uint8_t highReg
) {

    Wire.beginTransmission(APDS_ADDR);

    Wire.write(lowReg);

    Wire.endTransmission(false);

    Wire.requestFrom(APDS_ADDR, 1);

    uint8_t low = Wire.read();

    Wire.beginTransmission(APDS_ADDR);

    Wire.write(highReg);

    Wire.endTransmission(false);

    Wire.requestFrom(APDS_ADDR, 1);

    uint8_t high = Wire.read();

    return (high << 8) | low;
}

void initAPDS() {

    // Power ON + ALS + Proximity

    apdsWrite(APDS_ENABLE, 0x0F);

    // Ambient light integration time

    apdsWrite(APDS_ATIME, 0xDB);

    // Proximity integration time

    apdsWrite(APDS_PTIME, 0xFF);

    // Gain settings

    apdsWrite(APDS_CONTROL, 0x24);

    Serial.println("APDS9930 INIT DONE");
}

uint16_t readAmbientLight() {

    return apdsRead16(
        APDS_CDATAL,
        APDS_CDATAH
    );
}

uint16_t readProximity() {

    return apdsRead16(
        APDS_PDATAL,
        APDS_PDATAH
    );
}

// =====================================================
// OLED PRINT
// =====================================================

void oledPrint(
    String line1,
    String line2,
    String line3
) {

    display.clearDisplay();

    display.setTextSize(1);

    display.setTextColor(SH110X_WHITE);

    display.setCursor(0, 0);
    display.println(line1);

    display.setCursor(0, 20);
    display.println(line2);

    display.setCursor(0, 40);
    display.println(line3);

    display.display();
}

// =====================================================
// SETUP
// =====================================================

void setup() {

    Serial.begin(115200);

    Wire.begin();

    Wire.setClock(100000);

    delay(1000);

    // =================================================
    // OLED
    // =================================================

    display.begin(0x3C, true);

    display.clearDisplay();

    display.setTextSize(2);

    display.setTextColor(SH110X_WHITE);

    display.setCursor(0, 0);

    display.println("SAFEHAT");

    display.display();

    Serial.println("OLED OK");

    delay(1000);

    // =================================================
    // MPU6500
    // =================================================

    if (!mpu.init()) {

        Serial.println("MPU6500 FAILED");

        while (1);
    }

    Serial.println("MPU6500 OK");

    mpu.autoOffsets();

    Serial.println("MPU6500 CALIBRATED");

    // =================================================
    // BMP180
    // =================================================

    if (!bmp.begin()) {

        Serial.println("BMP180 FAILED");

        while (1);
    }

    Serial.println("BMP180 OK");

    baselinePressure = bmp.readPressure();

    // =================================================
    // APDS9930
    // =================================================

    initAPDS();

    // =================================================

    Serial.println("SAFEHAT PRO READY");

    oledPrint(
        "SAFEHAT PRO",
        "SYSTEM READY",
        "Monitoring..."
    );
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

    fallDetection();

    confinedSpaceDetection();

    morseSOS();

    proximityDetection();

    delay(100);
}

// =====================================================
// FALL DETECTION
// =====================================================

void fallDetection() {

    xyzFloat acc = mpu.getGValues();

    xyzFloat gyro = mpu.getGyrValues();

    float accelMagnitude = sqrt(
        acc.x * acc.x +
        acc.y * acc.y +
        acc.z * acc.z
    );

    float gyroMagnitude = sqrt(
        gyro.x * gyro.x +
        gyro.y * gyro.y +
        gyro.z * gyro.z
    );

    // FREEFALL

    if (
        accelMagnitude < FALL_THRESHOLD &&
        !freefallDetected
    ) {

        freefallDetected = true;

        Serial.println(
            "[FALL] Freefall detected"
        );

        oledPrint(
            "FALL DETECTED",
            "FREEFALL",
            "Monitoring..."
        );
    }

    // IMPACT

    if (
        freefallDetected &&
        accelMagnitude > IMPACT_THRESHOLD
    ) {

        impactDetected = true;

        inactivityStart = millis();

        Serial.println(
            "[FALL] Impact detected"
        );

        oledPrint(
            "FALL DETECTED",
            "IMPACT",
            "Checking motion..."
        );
    }

    // INACTIVITY

    if (impactDetected) {

        if (gyroMagnitude < 3.0) {

            if (
                millis() - inactivityStart >
                10000
            ) {

                Serial.println(
                    "[SOS] Worker unconscious"
                );

                oledPrint(
                    "SOS ALERT",
                    "UNCONSCIOUS",
                    "WORKER"
                );

                freefallDetected = false;

                impactDetected = false;
            }
        }
        else {

            freefallDetected = false;

            impactDetected = false;
        }
    }
}

// =====================================================
// CONFINED SPACE DETECTION
// =====================================================

void confinedSpaceDetection() {

    float currentPressure =
        bmp.readPressure();

    float pressureDiff =
        currentPressure -
        baselinePressure;

    float depth =
        pressureDiff / 12.0;

    uint16_t ambientLight =
        readAmbientLight();

    if (
        pressureDiff > 1500 &&
        ambientLight < LIGHT_THRESHOLD
    ) {

        Serial.print(
            "[CONFINED] Underground entry. Depth: "
        );

        Serial.print(depth);

        Serial.println(" m");

        oledPrint(
            "CONFINED SPACE",
            "Depth:",
            String(depth) + "m"
        );
    }
}

// =====================================================
// MORSE TAP SOS
// =====================================================

void morseSOS() {

    static int tapCount = 0;

    static unsigned long firstTap = 0;

    static unsigned long lastTapTime = 0;

    xyzFloat acc = mpu.getGValues();

    float accelMagnitude = sqrt(
        acc.x * acc.x +
        acc.y * acc.y +
        acc.z * acc.z
    );

    if (
        accelMagnitude > 2.2 &&
        millis() - lastTapTime > 300
    ) {

        lastTapTime = millis();

        if (tapCount == 0) {

            firstTap = millis();
        }

        tapCount++;

        Serial.print("[MORSE] Tap ");
        Serial.println(tapCount);

        oledPrint(
            "MORSE INPUT",
            "Tap Count:",
            String(tapCount)
        );
    }

    // 3 taps within 2 sec

    if (
        tapCount >= 3 &&
        millis() - firstTap < 2000
    ) {

        Serial.println(
            "[SOS] MORSE EMERGENCY SIGNAL DETECTED"
        );

        oledPrint(
            "SOS ALERT",
            "MORSE SIGNAL",
            "DETECTED"
        );

        tapCount = 0;
    }

    // RESET

    if (
        tapCount > 0 &&
        millis() - firstTap > 2000
    ) {

        tapCount = 0;
    }
}

// =====================================================
// PROXIMITY DETECTION
// =====================================================

void proximityDetection() {

    uint16_t proximity =
        readProximity();

    if (
        proximity > PROX_THRESHOLD
    ) {

        Serial.print(
            "[WARNING] Hazard nearby | Proximity: "
        );

        Serial.println(proximity);

        oledPrint(
            "WARNING",
            "OBJECT CLOSE",
            String(proximity)
        );
    }
}