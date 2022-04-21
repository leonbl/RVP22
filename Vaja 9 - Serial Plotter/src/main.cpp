#include <Arduino.h>

// Prikaz sinusa in kosinusa s Better Serial Plotter
// https://hackaday.io/project/181686-better-serial-plotter/details

void setup(){
    Serial.begin(9600);
}

void loop(){
    // get all of our variables of interest
    float t = millis()/1000.0;
    float var_sin = sin(t); // sin(t)
    float var_cos = cos(t); // cos(t)

    // write them all to console with tabs in between them
    Serial.print(t); // first variable is program time in seconds. This can be plotted on an x-axis!
    Serial.print("\t");
    Serial.print(var_sin);   // second variable is sin(t)
    Serial.print("\t");      // this last "\t" isn't required, but doesn't hurt
    Serial.println(var_cos); // third varible is cos(t). make sure to finish with a println!
    
    // For example, at 2.5 seconds, this prints out like so, where \t
    // is the tab character, and \n is the newline character
    // 2500\t0.598\t-0.801\t\n
}