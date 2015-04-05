//
// KeyStroker II code - used to send randam phrases as keyboard entries.  This was inspired by this post on MAKE:
// http://makezine.com/projects/make-32/the-awesome-button/
//

int led = 12;                      // Pin for LED status light
long counter = 0;                  // Used to delay the call to send the output string
long numCycles = 20000000;          // this is the check value as a replacement for the delay() function
const byte NUMBER_OF_WORDS = 26;    // Number of phrases - used to provide random seed and dimension for array


// Array of phrases
char* words[NUMBER_OF_WORDS] = {
 "I do not fear computers.  I fear lack of them.  ISACAC ASIMOV",
 "A computer once beat me at chess, but it was no match for me at kick boxing.  EMO PHILLIPS",
 "Computer Science is no more about computers than astronomy is about telescopes.  EDSGER DIJKSTRA",
 "The computer was born to solve problems that did not exist before.  BILL GATES",
 "Software is like entropy:  It is difficult to grasp, weighs nothing, and obeys the Second Law of Thermodynamics; i.e., it always increases.  NORMAN AUGUSTINE",
 "Software is a gas; it expands to fill its container.  NATHAN MYHRVOLD",
 "All parts should go together without forcing.  You must remember that the parts you are reassembling were disassembled by you.  Therefore, if you cannot get them together again, there must be a reason.  By all means, do not use a hammer.  IBM MANUAL 1925",
 "Standards are always out of date.  That is what makes them standards.  ALAN BENNETT",
 "Physics is the universes operating system.  STEVEN GARMAN",
 "It is the hardware that makes a machine fast.  It is the software that makes a fast machine slow.  CRAIG BRUCE",
 "Imagination is more important than knowledge.  For knowledge is limited, whereas imagination embraces the entire world, stimulating progress, giving birth to evolution.  ALBERT EINSTEIN",
 "The greatest enemy of knowledge is not ignorance, it is the illusion of knowledge.  STEPHEN HAWKING",
 "The more you know, the more you realize you know nothing.  SOCRATES",
 "Tell me and I forget.  Teach me and I remember.  Involve me and I learn.  BENJAMIN FRANKLIN",
 "Real knowledge is to know the extent of one's ignorance.  CONFUCIOUS",
 "If people never did silly things, nothing intelligent would ever get done.  LUDWIG WITTGENSTEIN",
 "Getting information off the internet is like taking a drink from a fire hydrant.  MITCHELL KAPOR",
 "If you think your users are idiots, only idiots will use it.  LINUS TORVOLDS",
 "Where is the any key?  HOMER SIMPSON",
 "Your most unhappy customers are your greatest source of learning.  BILL GATES",
 "In a room full of top software designers, if two agree on the same thing, that is a majority.  BILL CURTIS",
 "If you automate a mess, you get an automated mess.  ROD MICHAEL",
 "It is easier to change the specification to fit the program than vice versa.  ALAN PERLIS",
 "Simplicity, carried to the extreme, becomes elegance.  JON FRANKLIN",
 "Make everything as simple as possible, but not simpler. ALBERT EINSTEIN",
 "BMW Rulz!"
};

void setup(){
 randomSeed(analogRead(0));   //give the random number generator funky data as a seed
 pinMode(0, INPUT_PULLUP);    // saves us from needing to use a resistor in the circuit
 pinMode(led, OUTPUT);
 delay(5000);
}

void loop(){
  
  if (digitalRead(0) == LOW)   // the switch is in the on position
  {
    // First time in - send a message.
    if (counter == 0)
    {
      sendMessage();
    }
    
    counter++;                 // increment the counter by one   
         
    digitalWrite(led, HIGH);   // turn on the led light, indicating the switch is on
    
    // Check if the appropriate number of cycles have occurred to ensure the right 'delay()' has been met
    if ( counter > numCycles )
    {
      sendMessage();
      counter = 1;              // Reset the counter
    }
  }  
  else
  {
    digitalWrite(led, LOW);    // Turn off the led
    counter = 0;
  }
}


void sendMessage()
{
  Keyboard.print(words[random(0,NUMBER_OF_WORDS)]); // type a random phrase from our list
  Keyboard.println(); // and add a newline
}
