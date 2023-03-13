#include <Servo.h>


int moves[][3] = { // array with each servo's angle for each step/move
  // repetition means no move

  {180, 45, 180, 90}, // motor 4 and 5: 90 no move, 180 left, 0 right
  {180, 45, 180, 90},
  {0, 55, 180, 180},
  {0, 55, 180, 180},
  {0, 45, 180, 180},
  {0, 45, 180, 180},
  {0, 55, 180, 0},
  {0, 55, 180, 0},
  {1, 135, 180},
  {1, 100, 180},
  {1, 100, 180}, 
  {1, 100, 180}
};


int beats[][2] = { // beats per step/move. nr 0 is getting to start position..
  {4, 0},
  {4, 0},
  {3, 375},
  {5, 0},
  {3, 750},
  {5, 0},
  {3, 750},
  {5, 0},
  
};



class Dancer // creates a class to keep all functions necessary
{
    Servo servo;              // the servo
    int pos;                  // current servo position
    int increment;            // increment to move for each interval (0, -1 or 1)
    float updateInterval;     // interval between updates, ms
    unsigned long lastUpdate; // last update of position, ms
    float bps;                // beats per second
    float mspb;               // milliseconds per beat
    int degrees;              // degrees to move
    long startMillis;         // milliseconds at start of each move
    int angle;                // destination angle
    int beats;                // beats for said move
    int msTot;                // total milliseconds
    int w;

  public:
    Dancer(int bpm, int ws) // initiates each servo, and calculates mspb
    {
      bps = bpm / 60;
      mspb = 1000 / bps;

      w = ws;
    }


    void Attach(int pin) // attaches each servo to respective pin in setup
    {
      servo.attach(pin);
    }

    void write(int rotate)
    {
      servo.write(rotate);
    }


    void contValues(int vinkel, int takter) // decide direction and set start time for continuous servo
    // use 'takter'? can be longer and shorter...
    {
      
      msTot = vinkel * w; // time for movement

      if (vinkel == 90)
      {
        angle = 90;
      }

      else {
        angle = vinkel; 
      }

      startMillis = millis();
    }


    void Increment(int vinkel, int takter)  // calculates increment and updateInterval
    { // by given values (angle and beats)

      angle = vinkel;
      beats = takter;

      msTot  = beats * mspb;
      pos = servo.read();

      if (angle == pos) { // if the servo shouldn't move, increment = 0
        // servo increments one time (degrees = 1)
        degrees = 1;
        increment = 0;
      }

      else if (angle > pos) { // either ++ or -=1.

        degrees = angle - pos;
        increment = 1;
      }

      else if (angle < pos) {

        degrees = pos - angle;
        increment = -1;
      }
      updateInterval = msTot / degrees; // time between each update.

      startMillis = millis();
    }


    int Update() { // updates the servo

      pos = servo.read();

      if (pos == angle) { // if the angle has been reached (ms not precise)

        increment = 0;
      }

      if ((millis() - lastUpdate) >= updateInterval) { // time to update

        lastUpdate = millis();  // 'reset' lastUpdate
        pos += increment;       // increase/decrease pos
        servo.write(pos);       // update servo

        Serial.println(pos);            // check the values in monitor
        Serial.println(lastUpdate);
        Serial.println(updateInterval);
        Serial.println(msTot);
      }

      if ((millis() - startMillis) >= msTot) { // if the total time has run, break while loop
        return 1;
      }

      else { // otherwise, keep looping
        return 0;
      }
    }


    int contServo()
    { // update continuous servo

      if ((millis() - startMillis) > msTot) // if position is reached, stop rotating
      {
        angle = 90; // stop servo
        return 1; // ready
      }

      else
      {
        return 0; // keep looping
      }

      servo.write(angle); // direction, 0, 180 or 90. maxspeed.

    }
};
// end of class

int antalSteg = sizeof(beats) / sizeof(beats[0]); // amount of steps/moves
int bpm = 120; // a song's bpm, different for each
int i = 0; // int to for-loop and iterations.
int w = 250; // 1/4 pi / sec. 1 unit is 1/4 pi, 45 deg. 250 ms for 45 deg. 

int b; // ints to break while-loop
int s;
int e;
int n;
int h;

Dancer base(bpm, w);     // creates an instance of each servomotor/joint
Dancer shoulder(bpm, w); // passing the 'bpm' and 'w' argument
Dancer elbow(bpm, w);
Dancer neck(bpm, w);
Dancer head(bpm, w);


void setup()
{
  Serial.begin(9600); // initiate Serial monitor

  base.Attach(2);      //D4 // calls the function Attach
  shoulder.Attach(0);  // D3attaches each servo to resp pin
  elbow.Attach(5); //D1
  neck.Attach(3);
  head.Attach(6);
  
}


void loop()
{

  for (i; i < antalSteg; i++) { // iterates for each step

    base.Increment(moves[i][0], beats[i]);      // calls function Increment
    shoulder.Increment(moves[i][1], beats[i]);  // passes arguments angle and beats
    elbow.Increment(moves[i][2], beats[i]);     // from the arrays moves and beats
    // neck.Increment(moves[i][3], beats[i]);
    // head.Increment(moves[i][4], beats[i]);

    b, s, e = 0; // reset the ints to 0

    while (b + s + e/* + n + h */< 3) { // loops the Update function
      // if all return 1, break loop
      b = base.Update();
      s = shoulder.Update();  // updates the servo accordingly
      e = elbow.Update();     // returns either value 1 or 0
      //n = neck.Update();
      //h = head.Update();
    }
  }
}
