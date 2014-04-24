/*********************
  Name: Arduino Network Tool
  Version: v0.5
  
  A robust network tool based on the Arduino, Ardunio Ethernet Shield
  and the Adafruit RGB LCD Shield.
  
  Created by Patrick Jones 2014
  
  *This code is free to use and free to distribute,
  just be sure to thank Adafruit for their kickass
  products!*
**********************/
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>


#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


const int NUM_MENUS = 2;                  // Update with real number of menu items
int subMenuCounts[NUM_MENUS]= {3,2};  // and with submenu items for each.
boolean buttonPressed = false;
int menu =-1, subMenu =-1, color = 1;
boolean tmp = false, conStatus = false;

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);
  lcd.setCursor(0,0);                    
  
  lcd.print("Net Tool v0.5");            
  lcd.setCursor(0,1);                    
  lcd.print("Press any button");      
}

void loop() {
  buttonPressed = false;
  
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (menu == -1) {
      menu = 1; 
    }
    if (subMenu == -1) {
      subMenu = 1; 
    }
    if (buttons & BUTTON_UP) {
      menu = (menu + 1);
      subMenu = 1;
      buttonPressed = true;
    }
    if (buttons & BUTTON_DOWN) {
      menu = (menu - 1);
      subMenu = 1;
      buttonPressed = true;
    }
    if (buttons & BUTTON_LEFT) {
      subMenu = (subMenu - 1);
      buttonPressed = true;
    }
    if (buttons & BUTTON_RIGHT) {
      subMenu = (subMenu + 1);
      buttonPressed = true;
    }
//#############################################
    if (buttons & BUTTON_SELECT) {
      buttonPressed = true;
      if (menu == 1 && subMenu == 2) { // connect
        conStatus = true;
      }
      if (menu == 1 && subMenu == 3) { // disconnect
        conStatus = false;
      }
      
    }
    // Clean up values
    if (menu < 1) {
    menu = NUM_MENUS; 
    }
    else if (menu > NUM_MENUS){
      menu = 1;
    }
    if (subMenu < 1) {
      subMenu = subMenuCounts[menu-1]; 
    }
    if (subMenu > subMenuCounts[menu-1]) {
      subMenu = 1; 
    }
  }

  if(buttonPressed == true) {
    buttonPressed = false;
    updateScreen(menu, subMenu, subMenuCounts[menu-1], conStatus);
    delay(50); // make it smooth like butta, yo
  }
  buttonPressed = false;
}

void updateScreen(int menu, int subMenu, int count, boolean conStatus) {
  lcd.setCursor(0,0);
   // print menu
  
  if (menu == 1){ //connection menu
    lcd.print("Connection");
    lcd.print("   ");
    lcd.print(subMenu);
    lcd.print("/");
    lcd.print(subMenuCounts[menu-1]);
    
    lcd.setCursor(0,1);
    if(subMenu == 1){
      lcd.print("Conn. Status:");
      lcd.print(conStatus ? "Yes" : "NO");
      if (conStatus) {
        lcd.setBacklight(GREEN);
      }
      else {
        lcd.setBacklight(RED); 
      }
    }
    if(subMenu == 2){
      lcd.print("Connect?");
    }
    if(subMenu == 3){
      lcd.print("Disconnect?");
    }
  }
  if (menu == 2) {
    lcd.print("DHCP Info:");
    
    if (subMenu == 1) {
      lcd.print("    IP");
      lcd.setCursor(0,1);
      lcd.print(conStatus ? "192.168.1.7" : "Disconnected");
    }
    if (subMenu == 2) {
      lcd.print("   GTWY");
      lcd.setCursor(0,1);
      lcd.print(conStatus ? "192.168.1.1" : "Disconnected");
    }
  }
}
