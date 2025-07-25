#include <LPC17xx.h>

// LCD Macros
#define RS_CTRL  0x08000000  // P0.27
#define EN_CTRL  0x10000000  // P0.28
#define DT_CTRL  0x07800000  // P0.23 to P0.26

// Global Variables
unsigned int motion;
unsigned char flag = 0, lcd_displayed = 0;
unsigned long int temp1 = 0, temp2 = 0, i;
unsigned char flag1 = 0, flag2 = 0;
unsigned char msg[] = {"WELCOME"};

unsigned long int init_command[] = {
    0x30, 0x30, 0x30, 0x20,
    0x28, 0x0C, 0x06, 0x01, 0x80
};

// Function Prototypes
void pwm_init(void);
void PWM1_IRQHandler(void);
void delay_ms(unsigned int ms);
void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
void lcd_init(void);
void lcd_clear(void);
void lcd_print(char *str);

// Main Function
int main(void) {
    SystemInit();
    SystemCoreClockUpdate();

    // IR Sensor on P0.8 (Input)
    LPC_PINCON->PINSEL0 &= ~(3 << 16);
    LPC_GPIO0->FIODIR &= ~(1 << 8);

    // LCD Pins as Output
    LPC_GPIO0->FIODIR |= DT_CTRL | RS_CTRL | EN_CTRL;

    lcd_init();   // Initialize LCD
    pwm_init();   // Initialize PWM for LED

    while (1) {
        motion = (LPC_GPIO0->FIOPIN >> 8) & 0x01;

        if (!motion) { // Hand is near (IR sensor output LOW)
            if (flag == 0x00) {
                LPC_PWM1->MR4 += 50;
                LPC_PWM1->LER = 0xFF;
                if (LPC_PWM1->MR4 >= 29000) flag = 0xFF;
                delay_ms(100);
            }
            if (!lcd_displayed) {
                lcd_clear();
                lcd_print("WELCOME");
                lcd_displayed = 1;
            }
        } else { // Hand is away (IR sensor output HIGH)
            if (flag == 0xFF) {
                LPC_PWM1->MR4 -= 50;
                LPC_PWM1->LER = 0xFF;
                if (LPC_PWM1->MR4 <= 0) flag = 0x00;
                delay_ms(100);
            }
            if (lcd_displayed) {
                lcd_clear();
                lcd_displayed = 0;
            }
        }
    }
}

// PWM Initialization
void pwm_init(void) {
    LPC_SC->PCONP |= (1 << 6);               // Power up PWM1
    LPC_PINCON->PINSEL3 &= ~(3 << 14);       
    LPC_PINCON->PINSEL3 |= (2 << 14);        // P1.23 as PWM1.4

    LPC_PWM1->PCR = (1 << 12);               // Enable PWM1.4
    LPC_PWM1->MCR = 0x02;                    // Reset on MR0
    LPC_PWM1->MR0 = 30000;
    LPC_PWM1->MR4 = 0;                       // Start with LED off
    LPC_PWM1->LER = 0xFF;

    LPC_PWM1->TCR = 0x02;                    // Reset counter
    LPC_PWM1->TCR = 0x09;                    // Enable PWM and counter

    NVIC_EnableIRQ(PWM1_IRQn);
}

// Delay in milliseconds
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++);
}

// PWM Interrupt Service Routine
void PWM1_IRQHandler(void) {
    LPC_PWM1->IR = 0xFF;
    if (flag == 0x00) {
        LPC_PWM1->MR4 += 50;
        LPC_PWM1->LER = 0xFF;
        if (LPC_PWM1->MR4 >= 29000)
            flag = 0xFF;
    } else if (flag == 0xFF) {
        LPC_PWM1->MR4 -= 50;
        LPC_PWM1->LER = 0xFF;
        if (LPC_PWM1->MR4 <= 0)
            flag = 0x00;
    }
}

// LCD Initialization
void lcd_init(void) {
    flag1 = 0;
    for (i = 0; i < 9; i++) {
        temp1 = init_command[i];
        lcd_write();
    }
}

// LCD Print String
void lcd_print(char *str) {
    flag1 = 1;
    i = 0;
    while (str[i] != '\0') {
        temp1 = str[i];
        lcd_write();
        i++;
    }
}

// LCD Write Logic
void lcd_write(void) {
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;

    temp2 = temp1 & 0xF0;
    temp2 <<= 19;
    port_write();

    if (flag2 == 0) {
        temp2 = temp1 & 0x0F;
        temp2 <<= 23;
        port_write();
    }
}

// Send Data to LCD
void port_write(void) {
    LPC_GPIO0->FIOPIN = temp2;

    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = RS_CTRL;
    else
        LPC_GPIO0->FIOSET = RS_CTRL;

    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    delay_lcd(1000000);
}

// Simple Delay for LCD
void delay_lcd(unsigned int r1) {
    unsigned int r;
    for (r = 0; r < r1; r++);
}

// LCD Clear Screen
void lcd_clear(void) {
    flag1 = 0;
    temp1 = 0x01; // Clear display
    lcd_write();
}
