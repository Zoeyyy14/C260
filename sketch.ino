#include <Keypad.h>
const int row_num=4;
const int col_num=4;
long int current_time=0;
long int prev_time=0;
int threshold=4000;
char keypressed='\0';
int score=0;

char keys[row_num][col_num]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte row_pins[]={19,18,5,17};
byte col_pins[]={16,4,2,15};

Keypad k=Keypad(makeKeymap(keys),row_pins,col_pins,row_num,col_num);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  byte random_row=random(1,5);
  byte random_column=random(1,5);
  char random_element=keys[random_row-1][random_column-1];
  String hint1="Row : "+String(random_row);
  String hint2="Column : "+String(random_column);
  byte random_hint=random(1,3);
  if(random_hint==1){
    Serial.println(hint1+"\t"+hint2);
  }
  else{
    Serial.println(hint2+"\t"+hint1);
  }
  while(true){
    char key=k.getKey();
    if(key){
      keypressed=key;
    }
    current_time=millis();
    if(current_time-prev_time==threshold){
      if(keypressed==random_element){
        score++;
        if(score>6){
          Serial.println("You Won");
          while(1);
        }
        Serial.println("Correct Guess, Score : "+String(score));
        threshold=threshold-500;
        if(threshold<500)threshold=500;
      }
      else{
        Serial.println("You Lose");
        while(1);
      }
      prev_time=current_time;
      break;
    }
  }
}
