#include <FastLED.h>
#include <math.h>


// pinn assignment
#define LED_PIN_LEG_R 3 //red wire
#define LED_PIN_LEG_L 4
#define LED_PIN_UPB_R 5 //red wire
#define LED_PIN_UPB_L 6

// set number of leds
#define NUM_LED_UPB_R 25
#define NUM_LED_UPB_L 24
#define NUM_LED_LEGS 32


// set the leds variable 
// for the upper body
CRGB LEDS_UPB_R[NUM_LED_UPB_R]; 
CRGB LEDS_UPB_L[NUM_LED_UPB_L];

// set the leds variable 
// for the legs
CRGB LEDS_LEG_R[NUM_LED_LEGS]; 
CRGB LEDS_LEG_L[NUM_LED_LEGS];

// Initialize the main color variables
int RED = 0;
int GREEN = 0;
int BLUE = 0;

// Initialize the main suit itirator varibles
const int ST_SIDE = 2;
const int P_ROWS = 5;
const int P_COLS = 7;
const int S_ROWS = 4;
const int S_COLS = 14;

int pants_grid[ST_SIDE][P_ROWS][P_COLS] = {
    { // right 
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,0},
        {1,1,1,1,1,1,0},
        {1,1,1,1,1,1,0},
    },
    { // left
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,0},
        {1,1,1,1,1,1,0},
        {1,1,1,1,1,1,0},
    }
};

int shirt_grid[ST_SIDE][S_ROWS][S_COLS] = {
    { // right 
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0}
    },
    { // left
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0}
    }

};

// function variables
static char st_parts[6];
static int st_sides[6];
static int st_snake_sides[6];

// 0 for part, 1 for sides, 2 snake sides
static int list_cnts[3]; 

int max_intervals = NUM_LED_LEGS * 1; // Two times the most number of connected leds

// Available Colors
const int num_of_col = 7;
int COLORS[num_of_col][3] = {
    {255, 255, 255}, //white
    {255.215,40}, //sunlight yellow
    {22, 159, 51}, // Cal Poly Pomona Green
    {20, 182, 58}, // Dark Spring Green
    {248, 178, 41}, //  Orange-Yellow
    {234, 70, 48}, // Cinnabar
    {187, 37, 40} //Firebrick
};

int upb_count, leg_count = 1;
int MAX_LIGHT = 2; // maximum light percentage
int MIN_LIGHT = 1; // maximum light percentage

 


// Initialize the main functions
void sleep(double seconds);
void setLegLed(char position, int row, int column, float brightness);
void setUPBLed(char position, int row, int column, float brightness);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600); // open the serial port at 9600 bps
    FastLED.addLeds<WS2812, LED_PIN_LEG_R, GRB>(LEDS_LEG_R, NUM_LED_LEGS);
    FastLED.addLeds<WS2812, LED_PIN_LEG_L, GRB>(LEDS_LEG_L, NUM_LED_LEGS);
    FastLED.addLeds<WS2812, LED_PIN_UPB_R, GRB>(LEDS_UPB_R, NUM_LED_UPB_R);
    FastLED.addLeds<WS2812, LED_PIN_UPB_L, GRB>(LEDS_UPB_L, NUM_LED_UPB_L);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}


void loop() {
    init_show(); //5 seconds
    sleep(55);

    // start of the song
    setColor(3);
    setLegLed(1,5,3,MIN_LIGHT);
    setLegLed(2,5,3,MIN_LIGHT);
    FastLED.show();
    sleep(2);
    FastLED.clear();
    FastLED.show();

    // stary nights on hand then pretend play frum with just arms
    starry_night(
        st_part('a', 'a', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 5, MAX_LIGHT);
    stick_man(
        st_part('a', 'a', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 18, MIN_LIGHT);
    stick_man(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 7, MIN_LIGHT);
    // lights out after pretending as they told you about the 
    // rapa pam pam at 32 seconds
    sleep(4);
    // put hands on head to represtn cron while it changes up and
    // down
    stick_man(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 0.5, MIN_LIGHT);
    bottom_spread(
        st_part('a', 'a', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 1, MIN_LIGHT);
    stick_man(
        st_part('a', 'a', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 3.5, MIN_LIGHT);
    sleep(4);
    setColor(4);
    // return at 45 seconds and pretend like the gift spreading from
    // the chest area
    all_on_fade_in(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 1.5, MAX_LIGHT);
    side_vacuum(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 1, MAX_LIGHT);
    stick_man(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 3.5, MIN_LIGHT);
    sleep(3);
    // go down on knees slowly and pretend lik u laying down somthing
    wave_down(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
     wave_down(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_down(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_down(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_down(
        st_part('a', 'a', 'c', 'c', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    sleep(4);
    // at 1min 8 secs get back up and raise hands in praise
    stick_man(
        st_part('a', 'a', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 9, MIN_LIGHT);
    setColor(5);
    // switch to legs at 1min 17 secs
    starry_night(
        st_part('p', 'p', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 9, MAX_LIGHT);
    // raise right leg and stomp for lil baby pa rapa pom pom
    bottom_spread(
        st_part('p', ' ', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 6, MAX_LIGHT);
    sleep(4);
    // raise left leg and stomp for lil baby pa rapa pom pom at 
    bottom_spread(
        st_part('p', ' ', ' ', ' ', ' ', ' ' ),
        st_side(2,2,1,2,1,2) , 6, MAX_LIGHT);
    sleep(4);
    // step side to side  then march for i have no gift to bring at 1 min 46secs
    stick_man(
        st_part('p' , 'p', ' ', ' ', ' ', ' ' ),
        st_side(1,2,1,2,1,2) , 19, MIN_LIGHT);
    sleep(12);
    setColor(6);
    // Pretend to play drum and enjoy self while light change at 2min 17 secs
    starry_night(
        st_part('p', 'p', 'c', 'c', 'a', 'a' ),
        st_side(1,2,1,2,1,2) , 9, MAX_LIGHT);

    side_spread(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    side_vacuum(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    side_spread(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    side_vacuum(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 3, MAX_LIGHT);
    // time 2min 35 secs

    bottom_spread(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    top_vacuum(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    bottom_spread(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    top_vacuum(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    bottom_spread(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    top_vacuum(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    bottom_spread(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_up(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 1, MAX_LIGHT);
    // 2mins 50 secs
    setColor(7);
    wave_up(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_up(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_up(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_up(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    wave_up(
        st_part('a', 'a', 'c', 'c', 'p', 'p' ),
        st_side(1,2,1,2,1,2) , 2, MAX_LIGHT);
    // 3 mins
    setColor(5);
    snake_walk_up(
        st_snake_side(1,1,1,2,2,0),
        st_part('c', 'p', 'p', 'a', 'a', ' ' ),
        st_side(1,1,2,1,2,0) , 2, MIN_LIGHT);
    snake_walk_up(
        st_snake_side(2,2,2,1,1,0),
        st_part('c', 'p', 'p', 'a', 'a', ' ' ),
        st_side(1,1,2,1,2,0) , 2, MIN_LIGHT);
    snake_walk_up(
        st_snake_side(1,1,1,2,2,0),
        st_part('c', 'p', 'p', 'a', 'a', ' ' ),
        st_side(1,1,2,1,2,0) , 2, MIN_LIGHT);
    snake_walk_up(
        st_snake_side(2,2,2,1,1,0),
        st_part('c', 'p', 'p', 'a', 'a', ' ' ),
        st_side(1,1,2,1,2,0) , 2, MIN_LIGHT);
    snake_walk_up(
        st_snake_side(1,1,1,2,2,0),
        st_part('c', 'p', 'p', 'a', 'a', ' ' ),
        st_side(1,1,2,1,2,0) , 2, MIN_LIGHT);
    snake_walk_up(
        st_snake_side(2,2,2,1,1,0),
        st_part('c', 'p', 'p', 'a', 'a', ' ' ),
        st_side(1,1,2,1,2,0) , 2, MIN_LIGHT);
    sleep(5);
    setColor(4);
    // return to stick man at 3mins 17 secs 
    stick_man(
        st_part('a', 'a', 'p', 'p', 'c', 'c' ),
        st_side(1,2,1,2,1,2) , 6, MIN_LIGHT);
    all_on_fade_out(
        st_part('p', 'p', 'c', 'c', 'a', 'a' ),
        st_side(1,2,1,2,1,2) , 4, MAX_LIGHT);
}

/*
    SHOW FUNCTIONS
*/
// Flash and slowly dim lights and then wait for a minute
void init_show(){ 
    Serial.print(" -> The Show Begin\n");
    FastLED.clear();
    FastLED.show();

    setColor(2);
    int volume = 25;
    sleep(1);
    while (volume >= 0){ // 40 secs brightness reduction
        for(int side= 0; side < ST_SIDE; side++){
            for(int row= 0; row < P_ROWS; row++){
                for(int col = 0; col < P_COLS; col++){
                    if(pants_grid[side][row][col] == 1){
                        setLegLed(side+1, row+1,col+1,volume);
                    }else{
                        break;
                    }
                }
            }
            for(int row= 0; row < S_ROWS; row++){
                for(int col = 0; col < S_COLS; col++){
                    if(shirt_grid[side][row][col] == 1){
                        setUPBLed(side+1, row+1,col+1,volume);
                    }else{
                        break;
                    }
                }
            }
        }
        FastLED.show();
        sleep(0.1);
        volume--;
    }
    sleep(1.5);
    FastLED.clear();
    FastLED.show(); 
}

// turn all leds on
void all_on(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> all_on\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];
     
    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    // counting variables for each part of the suit 
    int pt_cnt[6] = {1};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    for(int interv = 1; interv <= tot_interval; interv++){
        if(interv == 1){
            for(int part_num = 0; part_num < s_part_len; part_num++){
                switch(s_part[part_num]){
                    case 'p':
                        for(int row = 0; row < P_ROWS; row++){
                            for(int col = 0; col < P_COLS; col++){
                                if(pants_grid[side[part_num]-1][row][col] == 1){
                                    setLegLed(side[part_num],row+1,col+1,lum);
                                }else{
                                    break;
                                }
                            }
                        }
                        break;
                    case 'c':
                        for(int col = 1; col <= S_COLS; col++){
                            setUPBLed(side[part_num],1,col,lum);
                        }
                        break;
                    case 'a':
                        for(int row = 1; row < S_ROWS; row++){
                            for(int col = 0; col < S_COLS; col++){
                                if(shirt_grid[side[part_num]-1][row][col] == 1){
                                    setUPBLed(side[part_num],row+1,col+1,lum);
                                }else{
                                    break;
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        FastLED.show();
        sleep(wait_time);
        
    }
    FastLED.clear();
    FastLED.show();
} 

// turn on all light for a moment and fade out
// s_part is for suit part
void all_on_fade_out(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> all_on_fade_out\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];
     
    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double light_decr_val = max_brightness/tot_interval;
    double lum = max_brightness;

    // counting variables for each part of the suit 
    int pt_cnt[6] = {1};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    for(int interv = 1; interv <= tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    for(int row = 0; row < P_ROWS; row++){
                        for(int col = 0; col < P_COLS; col++){
                            if(pants_grid[side[part_num]-1][row][col] == 1){
                                setLegLed(side[part_num],row+1,col+1,lum);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                case 'c':
                    for(int col = 1; col <= S_COLS; col++){
                        setUPBLed(side[part_num],1,col,lum);
                    }
                    break;
                case 'a':
                    for(int row = 1; row < S_ROWS; row++){
                        for(int col = 0; col < S_COLS; col++){
                            if(shirt_grid[side[part_num]-1][row][col] == 1){
                                setUPBLed(side[part_num],row+1,col+1,lum);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        FastLED.show();
        sleep(wait_time);

        if(lum >= (MIN_LIGHT+light_decr_val) ){
            lum -= light_decr_val;
        }
    }
    // clear all leds
    FastLED.clear();
    FastLED.show();
} 

// turn on all light for a moment and fade out
// s_part is for suit part
void all_on_fade_in(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> all_on_fade_in\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];
     
    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double light_incr_val = max_brightness/tot_interval;
    double lum = MIN_LIGHT;

    // counting variables for each part of the suit 
    int pt_cnt[6] = {1};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    for(int interv = 1; interv <= tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    for(int row = 0; row < P_ROWS; row++){
                        for(int col = 0; col < P_COLS; col++){
                            if(pants_grid[side[part_num]-1][row][col] == 1){
                                setLegLed(side[part_num],row+1,col+1,lum);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                case 'c':
                    for(int col = 1; col <= S_COLS; col++){
                        setUPBLed(side[part_num],1,col,lum);
                    }
                    break;
                case 'a':
                    for(int row = 1; row < S_ROWS; row++){
                        for(int col = 0; col < S_COLS; col++){
                            if(shirt_grid[side[part_num]-1][row][col] == 1){
                                setUPBLed(side[part_num],row+1,col+1,lum);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        FastLED.show();
        sleep(wait_time);

        if(lum <= (max_brightness-light_incr_val) ){
            lum += light_incr_val;
        }
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
} 

// move up a bar of light in the center for a duration 
void center_bar(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Center Bar\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_incr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = MIN_LIGHT;

    int p_tot_leds_lvl = P_ROWS;
    int c_tot_leds_lvl = S_COLS;
    int a_tot_leds_lvl = S_ROWS - 1 ;

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds_lvl;
    int c_gap = tot_interval/c_tot_leds_lvl;
    int a_gap = tot_interval/a_tot_leds_lvl;

    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv == 0){
                        pt_row[part_num] = P_ROWS;
                    }else if(interv % p_gap == 0 && pt_row[part_num] > 0){
                        pt_row[part_num]--;
                    }
                    setLegLed(side[part_num], pt_row[part_num],3, lum);
                    setLegLed(side[part_num], pt_row[part_num],4, lum);

                    break;
                case 'c':
                    if(interv % c_gap == 0 && pt_col[part_num] < c_tot_leds_lvl){
                        pt_col[part_num]++;
                    }
                    // Serial.print("... expected col : "); 
                    // Serial.println( pt_col[part_num]);

                    setUPBLed(side[part_num], 1, pt_col[part_num], lum);

                    break;
                case 'a':
                    if(interv == 0){
                        pt_row[part_num] = S_ROWS;
                    }else if(interv % a_gap == 0 && pt_row[part_num] > 1){
                        pt_row[part_num]--;
                    }
                    setUPBLed(side[part_num], pt_row[part_num],2, lum);
                    setUPBLed(side[part_num], pt_row[part_num],3, lum);

                    break;
                default:
                    break;
            }

        }
        FastLED.show();
        sleep(wait_time);
        if(lum <= (max_brightness-light_incr_val) ){
            lum += light_incr_val;
        }
    }
    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void bottom_spread(char s_part[], int side[], double duration, double max_brightness){
    Serial.print("-> Bottom Spread\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_incr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = MIN_LIGHT;

    int p_tot_leds = 14;
    int c_tot_leds = S_COLS + S_COLS;
    int a_tot_leds = 5;    
    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;

    // width for each part
    int p_width = 7;
    int c_width = 0;
    int a_width = 3;

    // mid points for each [art]
    int p_mid = (int) ceil(p_width/2.0);
    int c_mid = (int) ceil(p_width/2.0);
    int a_mid = (int) ceil(a_width/2.0);

    // counting variables for each part of the suit 
    int pt_spread[6] = {0};
    
    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // row variable for keeping track of inverse rows
    int pt_row_inv[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    int pre_spread = 0;


    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv % p_gap == 0 && pt_cnt[part_num] < p_tot_leds){
                        if(interv == 0){
                            pt_spread[part_num] = 1;
                            pt_row_inv[part_num] = 1;
                            pt_row[part_num] = P_ROWS;
                        }

                        // Serial.print("... spread : "); 
                        // Serial.println( pt_spread[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row_inv[part_num]);

                        setLegLed(side[part_num], pt_row[part_num], p_mid + (pt_spread[part_num]-1), lum);
                        setLegLed(side[part_num], pt_row[part_num], p_mid - (pt_spread[part_num]-1), lum);

                        // update the previous leds with the current brightness
                        pre_spread = 0;
                        for(int pre_row = P_ROWS; pre_row > pt_row[part_num]; pre_row--){ 
                            for(int pre_led = 0; pre_led <= pre_spread; pre_led++){
                                setLegLed(side[part_num], pre_row, p_mid+pre_led, lum);
                                setLegLed(side[part_num], pre_row, p_mid-pre_led, lum);
                            }
                            if(pre_spread < p_mid-1){
                                pre_spread++;
                            }
                        }
                        
                        if((pt_spread[part_num] >= pt_row_inv[part_num]) || pt_spread[part_num] >= p_mid){
                            pt_spread[part_num] = 1;
                            pt_row[part_num]--;
                            pt_row_inv[part_num]++;

                        }else{
                            if(pt_spread[part_num] < p_mid){
                                pt_spread[part_num]++;
                            }

                        }

                        pt_cnt[part_num]++;
                    }
                    break;
                case 'c':
                    break;
                 case 'a':
                    if(interv % a_gap == 0 && pt_cnt[part_num] < a_tot_leds){
                        if(interv == 0){
                            pt_spread[part_num] = 1;
                            pt_row_inv[part_num] = 1;
                            pt_row[part_num] = S_ROWS;
                        }

                        // Serial.print("... spread : "); 
                        // Serial.println( pt_spread[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row_inv[part_num]);

                        setUPBLed(side[part_num], pt_row[part_num], a_mid + (pt_spread[part_num]-1), lum);
                        setUPBLed(side[part_num], pt_row[part_num], a_mid - (pt_spread[part_num]-1), lum);

                        // update the previous leds with the current brightness
                        pre_spread = 0;
                        for(int pre_row = S_ROWS; pre_row > pt_row[part_num]; pre_row--){ 
                            for(int pre_led = 0; pre_led <= pre_spread; pre_led++){
                                setUPBLed(side[part_num], pre_row, a_mid+pre_led, lum);
                                setUPBLed(side[part_num], pre_row, a_mid-pre_led, lum);
                            }
                            if(pre_spread < a_mid-1){
                                pre_spread++;
                            }
                        }
                        
                        if((pt_spread[part_num] >= pt_row_inv[part_num]) || pt_spread[part_num] >= a_mid){
                            pt_spread[part_num] = 1;
                            pt_row[part_num]--;
                            pt_row_inv[part_num]++;

                        }else{
                            if(pt_spread[part_num] < a_mid){
                                pt_spread[part_num]++;
                            }
                        }

                        pt_cnt[part_num]++;
                    }
                    break;
                default:
                    break;
            }

        }
        FastLED.show();
        sleep(wait_time);
        if(lum <= (max_brightness-light_incr_val) ){
            lum += light_incr_val;
        }
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void top_vacuum(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Top Vacuum\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_decr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    int p_tot_leds = 19;
    int c_tot_leds = S_COLS + S_COLS;
    int a_tot_leds = 8;    
    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;

    // width for each part
    int p_width = 7;
    int c_width = 0;
    int a_width = 3;

    // mid points for each [art]
    int p_mid = (int) ceil(p_width/2.0);
    int c_mid = (int) ceil(p_width/2.0);
    int a_mid = (int) ceil(a_width/2.0);

    // the number f led that is turned off
    int pt_vacuum[6] = {0};

    // the counting value for the vacuum
    int pt_vacuum_trail[6] = {0};
    
    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};


    // col variable for each part of the suit
    int pt_col[6] = {0};

    int post_vacuum = 0;


    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv % p_gap == 0 && pt_cnt[part_num] < p_tot_leds){
                        if(interv == 0){
                            pt_vacuum[part_num] = p_mid;
                            pt_vacuum_trail[part_num] = p_mid;
                            pt_row[part_num] = 1;
                        }

                        // Serial.print("... vacuum : "); 
                        // Serial.println( pt_vacuum[part_num]);
                        // Serial.print("... vacuum  Trail: "); 
                        // Serial.println( pt_vacuum_trail[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row[part_num]);

                        if(pt_vacuum_trail[part_num] < pt_vacuum[part_num]){
                            setLegLed(side[part_num], pt_row[part_num], p_mid+pt_vacuum_trail[part_num], 0);
                            setLegLed(side[part_num], pt_row[part_num], p_mid-pt_vacuum_trail[part_num], 0);
                        }

                        // update the post leds with the current brightness
                        if(((P_ROWS - pt_row[part_num]) <= p_mid-1) && pt_vacuum[part_num] > 0){
                                post_vacuum = pt_vacuum[part_num] - 1;
                        }else{
                            post_vacuum = pt_vacuum[part_num];
                        }
                        

                        for(int first_leds = 0; first_leds < pt_vacuum_trail[part_num]; first_leds++){
                            // update the current row leds
                            setLegLed(side[part_num], pt_row[part_num], p_mid+first_leds, lum);
                            setLegLed(side[part_num], pt_row[part_num], p_mid-first_leds, lum);
                        }

                        for(int post_row = pt_row[part_num]+1; post_row <= P_ROWS; post_row++){ 
                            // update all the leds after
                            for(int post_led = 0; post_led < post_vacuum; post_led++){
                                setLegLed(side[part_num], post_row, p_mid+post_led, lum);
                                setLegLed(side[part_num], post_row, p_mid-post_led, lum);
                            }
                            if(((P_ROWS - post_row) <= p_mid-1) && post_vacuum > 0){
                                post_vacuum--;
                            }
                        }
                        
                        // gradually reduce the row and vacuum
                        if((pt_vacuum_trail[part_num] <= 0) && pt_row[part_num] < P_ROWS){
                            if(((P_ROWS - pt_row[part_num]) <= (p_mid-1)) && pt_vacuum[part_num] > 0){
                                pt_vacuum[part_num]--;
                            }
                            pt_row[part_num]++;
                            pt_vacuum_trail[part_num] = pt_vacuum[part_num];
                        }else{
                            if(pt_vacuum_trail[part_num] > 0){
                                pt_vacuum_trail[part_num]--;

                            }
                        }

                        pt_cnt[part_num]++;
                    }
                    break;
                case 's':
                    break;
                 case 'a':
                    if(interv % a_gap == 0 && pt_cnt[part_num] < a_tot_leds){
                        if(interv == 0){
                            pt_vacuum[part_num] = a_mid;
                            pt_vacuum_trail[part_num] = a_mid;
                            pt_row[part_num] = 2;
                        }

                        Serial.print("... vacuum : "); 
                        Serial.println( pt_vacuum[part_num]);
                        Serial.print("... vacuum  Trail: "); 
                        Serial.println( pt_vacuum_trail[part_num]);
                        Serial.print("... row: "); 
                        Serial.println( pt_row[part_num]);

                        if(pt_vacuum_trail[part_num] < pt_vacuum[part_num]){
                            setUPBLed(side[part_num], pt_row[part_num], a_mid+pt_vacuum_trail[part_num], 0);
                            setUPBLed(side[part_num], pt_row[part_num], a_mid-pt_vacuum_trail[part_num], 0);
                        }

                        // update the post leds with the current brightness
                        if(((S_ROWS - pt_row[part_num]) <= a_mid-1) && pt_vacuum[part_num] > 0){
                                post_vacuum = pt_vacuum[part_num] - 1;
                        }else{
                            post_vacuum = pt_vacuum[part_num];
                        }
                        

                        for(int first_leds = 0; first_leds < pt_vacuum_trail[part_num]; first_leds++){
                            // update the current row leds
                            setUPBLed(side[part_num], pt_row[part_num], a_mid+first_leds, lum);
                            setUPBLed(side[part_num], pt_row[part_num], a_mid-first_leds, lum);
                        }

                        for(int post_row = pt_row[part_num]+1; post_row <= S_ROWS; post_row++){ 
                            // update all the leds after
                            for(int post_led = 0; post_led < post_vacuum; post_led++){
                                setUPBLed(side[part_num], post_row, a_mid+post_led, lum);
                                setUPBLed(side[part_num], post_row, a_mid-post_led, lum);
                            }
                            if(((S_ROWS - post_row) <= a_mid-1) && post_vacuum > 0){
                                post_vacuum--;
                            }
                        }
                        
                        // gradually reduce the row and vacuum
                        if((pt_vacuum_trail[part_num] <= 0) && pt_row[part_num] < S_ROWS){
                            if(((S_ROWS - pt_row[part_num]) <= (a_mid-1)) && pt_vacuum[part_num] > 0){
                                pt_vacuum[part_num]--;
                            }
                            pt_row[part_num]++;
                            pt_vacuum_trail[part_num] = pt_vacuum[part_num];
                        }else{
                            if(pt_vacuum_trail[part_num] > 0){
                                pt_vacuum_trail[part_num]--;

                            }
                        }

                        pt_cnt[part_num]++;
                    }
                    break;
                default:
                    break;
            }

        }
        FastLED.show();
        sleep(wait_time);
         if(lum >= (MIN_LIGHT+light_decr_val) ){
            lum -= light_decr_val;
        }
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void wave_down(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Wave Down\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_decr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    int p_tot_leds = P_ROWS;
    int c_tot_leds = S_COLS;
    int a_tot_leds = S_ROWS-1;    
    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;
    
    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv % p_gap == 0){
                        pt_row[part_num]++;
                    }
                    if(interv % 2 == 0){
                        // turn on the leds
                        for(int col = 1; col <= P_COLS; col++){
                            if(pants_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setLegLed(side[part_num],pt_row[part_num],col,lum);
                            }else{
                                break;
                            }
                        }
                    }else{
                        // turn the leds off in the line
                        for(int col = 1; col <= P_COLS; col++){
                            if(pants_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setLegLed(side[part_num], pt_row[part_num],col,0);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                case 'c':
                    if(interv == 0){
                        pt_col[part_num] = S_COLS+1;
                    }
                    if(interv % c_gap == 0 && pt_col[part_num] > 1){
                        pt_col[part_num]--;
                    }
                    if(interv % 2 == 0){
                        // turn on the leds
                        setUPBLed(side[part_num], 1,pt_col[part_num],lum);
                    }else{
                        // turn the leds off in the line
                        setUPBLed(side[part_num], 1,pt_col[part_num],0);
                    }
                    break;
                case 'a':
                    if(interv == 0){
                        pt_row[part_num] = 1;
                    }
                    if(interv % a_gap == 0){
                        pt_row[part_num]++;
                    }
                    if(interv % 2 == 0){
                        // turn on the leds
                        for(int col = 1; col <= S_COLS; col++){
                            if(shirt_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], col, lum);
                            }else{
                                break;
                            }
                        }
                    }else{
                        // turn the leds off in the line
                        for(int col = 1; col <= S_COLS; col++){
                            if(shirt_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], col, 0);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        FastLED.show();
        sleep(wait_time);
        if(lum >= (MIN_LIGHT+light_decr_val) ){
            lum -= light_decr_val;
        }
    }
    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void wave_up(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Wave Up\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_incr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = MIN_LIGHT;

    int p_tot_leds = P_ROWS;
    int c_tot_leds = S_COLS;
    int a_tot_leds = S_ROWS-1;    
    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;
    
    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv == 0){
                        pt_row[part_num] = P_ROWS+1;
                    }
                    if(interv % p_gap == 0 && pt_row[part_num] > 1){
                        pt_row[part_num]--;
                    }
                    if(interv % 2 == 0){
                        // turn on the leds
                        for(int col = 1; col <= P_COLS; col++){
                            if(pants_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setLegLed(side[part_num],pt_row[part_num],col,lum);
                            }else{
                                break;
                            }
                        }
                    }else{
                        // turn the leds off in the line
                        for(int col = 1; col <= P_COLS; col++){
                            if(pants_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setLegLed(side[part_num], pt_row[part_num],col,0);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                case 'c':
                    if(interv % c_gap == 0){
                        pt_col[part_num]++;
                    }
                    if(interv % 2 == 0){
                        // turn on the leds
                        setUPBLed(side[part_num], 1,pt_col[part_num],lum);
                    }else{
                        // turn the leds off in the line
                        setUPBLed(side[part_num], 1,pt_col[part_num],0);
                    }
                    break;
                case 'a':
                    if(interv == 0){
                        pt_row[part_num] = S_ROWS+1;
                    }
                    if(interv % a_gap == 0 && pt_row[part_num] > 2){
                        pt_row[part_num]--;
                    }
                    if(interv % 2 == 0){
                        // turn on the leds
                        for(int col = 1; col <= S_COLS; col++){
                            if(shirt_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], col, lum);
                            }else{
                                break;
                            }
                        }
                    }else{
                        // turn the leds off in the line
                        for(int col = 1; col <= S_COLS; col++){
                            if(shirt_grid[side[part_num]-1][pt_row[part_num]-1][col-1] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], col, 0);
                            }else{
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        FastLED.show();
        sleep(wait_time);
        if(lum <= (max_brightness-light_incr_val) ){
            lum += light_incr_val;
        }
    }
    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void side_spread(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Side Spread\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_incr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = MIN_LIGHT;

    // width for each part
    int p_width = P_COLS;
    int c_width = S_COLS;
    int a_width = 4;

    int p_tot_leds = p_width/2;
    int c_tot_leds = S_COLS/2;
    int a_tot_leds = a_width/2;    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;

    // the number f led that is turned off
    int pt_spread[6] = {0};

    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};



    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv % p_gap == 0 && pt_spread[part_num] <= p_tot_leds){
                        pt_spread[part_num]++;
                    }
                    for(int row = 1; row <= P_ROWS; row++){
                        setLegLed(side[part_num], row, pt_spread[part_num], lum);
                        setLegLed(side[part_num], row, p_width - pt_spread[part_num] +1, lum);
                    }
                    break;
                case 'c':
                    if(interv % c_gap == 0 && pt_spread[part_num] < c_tot_leds){
                        pt_spread[part_num]++;
                    }
                    setUPBLed(side[part_num], 1, pt_spread[part_num], lum);
                    setUPBLed(side[part_num], 1, c_width - pt_spread[part_num] +1, lum);
                    break;
                case 'a':
                    if(interv % a_gap == 0 && pt_spread[part_num] <= a_tot_leds){
                        pt_spread[part_num]++;
                    }
                    for(int row = 2; row <= S_ROWS; row++){
                        setUPBLed(side[part_num], row, pt_spread[part_num], lum);
                        setUPBLed(side[part_num], row, a_width - pt_spread[part_num] +1, lum);
                    }
                    break;
                default:
                    break;
            }
        }
        FastLED.show();
        sleep(wait_time);
        if(lum <= (max_brightness-light_incr_val) ){
            lum += light_incr_val;
        }
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void side_vacuum(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Side Vacuum\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double light_decr_val = max_brightness/tot_interval;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    // width for each part
    int p_width = P_COLS;
    int c_width = S_COLS;
    int a_width = 4;

    int p_tot_leds = p_width/2 + 2;
    int c_tot_leds = S_COLS/2 + 2;
    int a_tot_leds = a_width/2 + 2;    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;

    // the number f led that is turned off
    int pt_spread[6] = {0};

    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};



    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv == 0){
                        pt_spread[part_num] = p_tot_leds;
                    }
                    if(interv % p_gap == 0 && pt_spread[part_num] > 0){
                        if(pt_spread[part_num] < p_tot_leds){
                            for(int row = 1; row <= P_ROWS; row++){
                                setLegLed(side[part_num], row, pt_spread[part_num], 0);
                                setLegLed(side[part_num], row, p_width - pt_spread[part_num] +1, 0);
                            } 
                        }
                        pt_spread[part_num]--;
                    }

                    for(int row = 1; row <= P_ROWS; row++){
                        for(int wings = 1; wings <= pt_spread[part_num]; wings++){
                            setLegLed(side[part_num], row, wings, lum);
                            setLegLed(side[part_num], row, p_width - wings +1, lum);
                        }
                    }
                    break;
                case 'c':
                    if(interv == 0){
                        pt_spread[part_num] = c_tot_leds;
                    }
                    if(interv % c_gap == 0 && pt_spread[part_num] > 0){
                        if(pt_spread[part_num] < c_tot_leds){
                            setUPBLed(side[part_num], 1, pt_spread[part_num], 0);
                            setUPBLed(side[part_num], 1, c_width - pt_spread[part_num] +1, 0);
                        }
                        pt_spread[part_num]--;
                    }

                    for(int wings = 1; wings <= pt_spread[part_num]; wings++){
                        setUPBLed(side[part_num], 1, wings, lum);
                        setUPBLed(side[part_num], 1, c_width - wings +1, lum);
                    }
                    
                    break;
                case 'a':
                    if(interv == 0){
                        pt_spread[part_num] = a_tot_leds;
                    }
                    if(interv % a_gap == 0 && pt_spread[part_num] > 0){
                        if(pt_spread[part_num] < a_tot_leds){
                            for(int row = 2; row <= S_ROWS; row++){
                                setUPBLed(side[part_num], row, pt_spread[part_num], 0);
                                setUPBLed(side[part_num], row, a_width - pt_spread[part_num] +1, 0);
                            } 
                        }
                        pt_spread[part_num]--;
                    }

                    for(int row = 2; row <= S_ROWS; row++){
                        for(int wings = 1; wings <= pt_spread[part_num]; wings++){
                            setUPBLed(side[part_num], row, wings, lum);
                            setUPBLed(side[part_num], row, a_width - wings +1, lum);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        FastLED.show();
        sleep(wait_time);
        if(lum >= (MIN_LIGHT+light_decr_val) ){
            lum -= light_decr_val;
        }
    }


    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void snake_walk_up(int snake_side[], char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Snake Walk Up\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    // width for each part
    int p_width = P_COLS-1;
    int c_width = 2;
    int a_width = 3;

    int p_tot_leds = (P_ROWS * 2)  + p_width - 2;
    int c_tot_leds = (S_COLS * 2) + c_width - 2;
    int a_tot_leds = ((S_ROWS - 1 )*2) + a_width - 2;    
    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;

    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv == 0){
                        pt_row[part_num] = P_ROWS;
                        pt_col[part_num] = 1;
                        pt_cnt[part_num]++;
                    }
                    if( interv % p_gap == 0){
                        if(pt_cnt[part_num] <= P_ROWS and pt_row[part_num] > 0){
                            // snake up
                            // Serial.println("... snake going up "); 
                            if(snake_side[part_num] == 1){
                                setLegLed(side[part_num], pt_row[part_num], 1, lum);
                            }else if(snake_side[part_num] == 2){
                                setLegLed(side[part_num], pt_row[part_num], p_width, lum);
                            }
                            if(pt_row[part_num] > 1){
                                pt_row[part_num]--;
                            }
                        }else if(pt_cnt[part_num] <= P_ROWS+(p_width-1)){
                            // snake side
                            // Serial.println("... snake going across"); 
                            if(snake_side[part_num] == 1){
                                setLegLed(side[part_num], 1, pt_col[part_num], lum);
                            }else if(snake_side[part_num] == 2){
                                setLegLed(side[part_num], 1, p_width-pt_col[part_num]+1, lum);
                            }

                            if(pt_col[part_num] <= p_width){
                                pt_col[part_num]++;
                            }

                        }else if(pt_cnt[part_num] <=  (P_ROWS*2)+(p_width-1)){
                            // snake down
                            // Serial.println("... snake going down "); 
                            if(snake_side[part_num] == 1){
                                setLegLed(side[part_num], pt_row[part_num], p_width, lum);
                            }else if(snake_side[part_num] == 2){
                                setLegLed(side[part_num], pt_row[part_num], 1, lum);
                            }
                            if(pt_row[part_num] < P_ROWS){
                                pt_row[part_num]++;
                            }
                        }

                        Serial.print("... count : "); 
                        Serial.println( pt_cnt[part_num]);
                        Serial.print("... row: "); 
                        Serial.println( pt_row[part_num]);
                        Serial.print("... col: "); 
                        Serial.println( pt_col[part_num]);

                        pt_cnt[part_num]++;
                    }
                    break;
                case 'c':
                    if(interv == 0){
                        pt_row[part_num] = 1;
                        pt_col[part_num] = 1;
                        pt_cnt[part_num]++;
                    }
                    if( interv % c_gap == 0){
                        if(pt_cnt[part_num] <= S_COLS and pt_col[part_num] <= S_COLS){
                            // snake up
                            // Serial.println("... snake going up "); 
                            setUPBLed(snake_side[part_num], pt_row[part_num], pt_col[part_num], lum);
                            
                            if(pt_col[part_num] < S_COLS){
                                pt_col[part_num]++;
                            }

                        }else if(pt_cnt[part_num] <= (S_COLS*2 )){
                            // snake down
                            // Serial.println("... snake going down "); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(2, pt_row[part_num], pt_col[part_num], lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(1, pt_row[part_num], pt_col[part_num], lum);
                            }
                            if(pt_col[part_num] > 1){
                                pt_col[part_num]--;
                            }
                        }

                        // Serial.print("... count : "); 
                        // Serial.println( pt_cnt[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row[part_num]);
                        // Serial.print("... col: "); 
                        // Serial.println( pt_col[part_num]);

                        pt_cnt[part_num]++;
                    }
                    break;
                case 'a':
                    if(interv == 0){
                        pt_row[part_num] = S_ROWS;
                        pt_col[part_num] = 1;
                        pt_cnt[part_num]++;
                    }
                    if( interv % a_gap == 0){
                        if(pt_cnt[part_num] <= (S_ROWS-1) and pt_row[part_num] > 1){
                            // snake up
                            // Serial.println("... snake going up "); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], 1, lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(side[part_num], pt_row[part_num], a_width, lum);
                            }
                            if(pt_row[part_num] > 2){
                                pt_row[part_num]--;
                            }
                        }else if(pt_cnt[part_num] <= (S_ROWS-1)+(a_width-1)){
                            // snake side
                            // Serial.println("... snake going across"); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], pt_col[part_num], lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(side[part_num], pt_row[part_num], a_width-pt_col[part_num]+1, lum);
                            }

                            if(pt_col[part_num] <= a_width){
                                pt_col[part_num]++;
                            }

                        }else if(pt_cnt[part_num] <=  ((S_ROWS-1)*2)+(a_width)){
                            // snake down
                            // Serial.println("... snake going down "); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], a_width, lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(side[part_num], pt_row[part_num], 1, lum);
                            }
                            if(pt_row[part_num] < S_ROWS){
                                pt_row[part_num]++;
                            }
                        }

                        // Serial.print("... count : "); 
                        // Serial.println( pt_cnt[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row[part_num]);
                        // Serial.print("... col: "); 
                        // Serial.println( pt_col[part_num]);

                        pt_cnt[part_num]++;
                    }
                    break;
                default:
                    break;
            }

        }
        FastLED.show();
        sleep(wait_time);
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void snake_walk_down(int snake_side[], char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Snake Walk Down\n");
    FastLED.clear();
    FastLED.show();

   int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    // width for each part
    int p_width = P_COLS-1;
    int c_width = 2;
    int a_width = 3;

    int p_tot_leds = (P_ROWS * 2)  + p_width - 2;
    int c_tot_leds = (S_COLS * 2) + c_width - 2;
    int a_tot_leds = ((S_ROWS - 1 )*2) + a_width - 2;    
    

    // gap value variables for each part of the suit
    int p_gap = tot_interval/p_tot_leds;
    int c_gap = tot_interval/c_tot_leds;
    int a_gap = tot_interval/a_tot_leds;

    // counting variables for each part of the suit 
    int pt_cnt[6] = {0};

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    // run at every wait tim
    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    if(interv == 0){
                        pt_row[part_num] = 1;
                        pt_col[part_num] = 1;
                        pt_cnt[part_num]++;
                    }
                    if( interv % p_gap == 0){
                        if(pt_cnt[part_num] <= P_ROWS and pt_row[part_num] <= P_ROWS){
                            // snake up
                            // Serial.println("... snake going up "); 
                            if(snake_side[part_num] == 1){
                                setLegLed(side[part_num], pt_row[part_num], 1, lum);
                            }else if(snake_side[part_num] == 2){
                                setLegLed(side[part_num], pt_row[part_num], p_width, lum);
                            }
                            if(pt_row[part_num] < P_ROWS){
                                pt_row[part_num]++;
                            }
                        }else if(pt_cnt[part_num] <= P_ROWS+(p_width-1)){
                            // snake side
                            // Serial.println("... snake going across"); 
                            if(snake_side[part_num] == 1){
                                setLegLed(side[part_num], pt_row[part_num], pt_col[part_num], lum);
                            }else if(snake_side[part_num] == 2){
                                setLegLed(side[part_num], pt_row[part_num], p_width-pt_col[part_num]+1, lum);
                            }

                            if(pt_col[part_num] <= p_width){
                                pt_col[part_num]++;
                            }

                        }else if(pt_cnt[part_num] <=  (P_ROWS*2)+(p_width-1)){
                            // snake down
                            // Serial.println("... snake going down "); 
                            if(snake_side[part_num] == 1){
                                setLegLed(side[part_num], pt_row[part_num], p_width, lum);
                            }else if(snake_side[part_num] == 2){
                                setLegLed(side[part_num], pt_row[part_num], 1, lum);
                            }
                            if(pt_row[part_num] > 1){
                                pt_row[part_num]--;
                            }
                        }

                        Serial.print("... count : "); 
                        Serial.println( pt_cnt[part_num]);
                        Serial.print("... row: "); 
                        Serial.println( pt_row[part_num]);
                        Serial.print("... col: "); 
                        Serial.println( pt_col[part_num]);

                        pt_cnt[part_num]++;
                    }
                    break;
                case 'c':
                    if(interv == 0){
                        pt_row[part_num] = 1;
                        pt_col[part_num] = S_COLS;
                        pt_cnt[part_num]++;
                    }
                    if( interv % c_gap == 0){
                        if(pt_cnt[part_num] <= S_COLS and pt_col[part_num] <= S_COLS){
                            // snake up
                            // Serial.println("... snake going up "); 
                            setUPBLed(snake_side[part_num], pt_row[part_num], pt_col[part_num], lum);
                            
                            if(pt_col[part_num] > 1){
                                pt_col[part_num]--;
                            }

                        }else if(pt_cnt[part_num] <= (S_COLS*2 )){
                            // snake down
                            // Serial.println("... snake going down "); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(2, pt_row[part_num], pt_col[part_num], lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(1, pt_row[part_num], pt_col[part_num], lum);
                            }
                            if(pt_col[part_num] < S_COLS){
                                pt_col[part_num]++;
                            }
                        }

                        // Serial.print("... count : "); 
                        // Serial.println( pt_cnt[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row[part_num]);
                        // Serial.print("... col: "); 
                        // Serial.println( pt_col[part_num]);

                        pt_cnt[part_num]++;
                    }
                    break;
                case 'a':
                    if(interv == 0){
                        pt_row[part_num] = 2;
                        pt_col[part_num] = 1;
                        pt_cnt[part_num]++;
                    }
                    if( interv % a_gap == 0){
                        if(pt_cnt[part_num] <= (S_ROWS-1) and pt_row[part_num] <= S_ROWS){
                            // snake up
                            // Serial.println("... snake going up "); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], 1, lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(side[part_num], pt_row[part_num], a_width, lum);
                            }
                            if(pt_row[part_num] < S_ROWS){
                                pt_row[part_num]++;
                            }
                        }else if(pt_cnt[part_num] <= (S_ROWS-1)+(a_width-1)){
                            // snake side
                            // Serial.println("... snake going across"); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], pt_col[part_num], lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(side[part_num], pt_row[part_num], a_width-pt_col[part_num]+1, lum);
                            }

                            if(pt_col[part_num] <= a_width){
                                pt_col[part_num]++;
                            }

                        }else if(pt_cnt[part_num] <=  ((S_ROWS-1)*2)+(a_width)){
                            // snake down
                            // Serial.println("... snake going down "); 
                            if(snake_side[part_num] == 1){
                                setUPBLed(side[part_num], pt_row[part_num], a_width, lum);
                            }else if(snake_side[part_num] == 2){
                                setUPBLed(side[part_num], pt_row[part_num], 1, lum);
                            }
                            if(pt_row[part_num] > 2){
                                pt_row[part_num]--;
                            }
                        }

                        // Serial.print("... count : "); 
                        // Serial.println( pt_cnt[part_num]);
                        // Serial.print("... row: "); 
                        // Serial.println( pt_row[part_num]);
                        // Serial.print("... col: "); 
                        // Serial.println( pt_col[part_num]);

                        pt_cnt[part_num]++;
                    }
                    break;
                default:
                    break;
            }

        }
        FastLED.show();
        sleep(wait_time);
    }

    // clear all leds
    FastLED.clear(); 
    FastLED.show();
}

void starry_night(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Starry Night\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double lum = MIN_LIGHT;

    // gap value variables for each part of the suit
    int p_leds_on = NUM_LED_LEGS/4;
    int c_leds_on =  S_COLS/4;
    int a_leds_on = (NUM_LED_UPB_L - S_COLS)/4;

    // row variable for each part of the suit
    int pt_row[6] = {0};

    // col variable for each part of the suit
    int pt_col[6] = {0};

    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){

            // print the results 
            // Serial.print("... part len : "); 
            // Serial.println(s_part_len);
            // Serial.print("...... Part index : "); 
            // Serial.println(part_num);
            // Serial.print("...... part : "); 
            // Serial.println(s_part[part_num]);
            //  Serial.print("...... side : "); 
            // Serial.println(side[part_num]);


            switch(s_part[part_num]){
                case 'p':
                    for(int led_num = 0; led_num < p_leds_on; led_num++ ){
                        lum = (max_brightness - MIN_LIGHT) * ( (double)rand() / (double)RAND_MAX ) + MIN_LIGHT;
                        pt_col[part_num] = (rand() % ((P_COLS-1) - 1 + 1)) + 1;
                        pt_row[part_num] = (rand() % (P_ROWS - 1 + 1)) + 1;
                        setLegLed(side[part_num], pt_row[part_num], pt_col[part_num], lum);
                    }
                    break;
                case 'c':
                    for(int led_num = 0; led_num < c_leds_on; led_num++ ){
                        lum = (max_brightness - MIN_LIGHT) * ( (double)rand() / (double)RAND_MAX ) + MIN_LIGHT;
                        pt_col[part_num] = (rand() % (S_COLS - 1 + 1)) + 1;
                        setUPBLed(side[part_num], 1,pt_col[part_num], lum);
                    }
                    break;
                 case 'a':
                    for(int led_num = 0; led_num < a_leds_on; led_num++ ){
                        lum = (max_brightness - MIN_LIGHT) * ( (double)rand() / (double)RAND_MAX ) + MIN_LIGHT;
                        pt_col[part_num] = (rand() % (3 - 1 + 1)) + 1;
                        pt_row[part_num] = (rand() % (S_ROWS - 2 + 1)) + 2;
                        setUPBLed(side[part_num], pt_row[part_num], pt_col[part_num], lum);
                    }
                    break;
                default:
                    break;
            } 
        }

        FastLED.show();
        sleep(wait_time);

        for(int part_num = 0; part_num < s_part_len; part_num++){
            switch(s_part[part_num]){
                case 'p':
                    for(int led_row = 1; led_row <= P_ROWS; led_row++ ){
                        for(int led_col = 1; led_col <= (P_COLS-1); led_col++ ){
                            setLegLed(side[part_num], led_row,led_col, 0);
                        }
                    }
                    break;
                case 'c':
                    for(int led_num = 1; led_num <= S_COLS; led_num++ ){
                        setUPBLed(side[part_num], 1,led_num, 0);
                    }
                    
                    break;
                case 'a':
                    for(int led_row = 2; led_row <= S_ROWS; led_row++ ){
                        for(int led_col = 1; led_col <= 3; led_col++ ){
                            setUPBLed(side[part_num], led_row, led_col, 0);
                        }
                    }
                    break;
                default:
                    break;
            } 
        }
        FastLED.show();
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
}

void stick_man(char s_part[], int side[], double duration, double max_brightness){
    Serial.print(" -> Starry Night\n");
    FastLED.clear();
    FastLED.show();

    int s_part_len = list_cnts[0];
    int side_len = list_cnts[1];

    int tot_interval = max_intervals;
    double wait_time  = duration/tot_interval;
    double lum = max_brightness;

    for(int interv = 0; interv < tot_interval; interv++){
        for(int part_num = 0; part_num < s_part_len; part_num++){

            switch(s_part[part_num]){
                case 'p':
                    for(int row = 1; row <= P_ROWS; row++){
                        setLegLed(side[part_num], row, 3,lum);
                        setLegLed(side[part_num], row, 4,lum);
                    }
                    break;
                case 'c':
                    for(int col = 1; col <= S_COLS; col++){
                        setUPBLed(side[part_num],1,col,lum);
                    }
                    break;
                case 'a':
                    for(int row = 2; row <= S_ROWS; row++){
                        setUPBLed(side[part_num], row, 2,lum);
                        setUPBLed(side[part_num], row, 3,lum);
                    }
                    break;
                default:
                    break;
            } 
        }
        FastLED.show();
        sleep(wait_time);
    }

    // clear all leds
    FastLED.clear();
    FastLED.show();
}


/*
    MAIN FUNCTIONS
*/
void sleep(double seconds){ delay(seconds*1000.0); }

char * st_part(char p1, char p2, char p3, char p4, char p5, char p6){
    int cnt = 0;
    if(p1 != ' '){ st_parts[0] = p1; cnt++; }
    if(p2 != ' '){ st_parts[1] = p2; cnt++; }
    if(p3 != ' '){ st_parts[2] = p3; cnt++; }
    if(p4 != ' '){ st_parts[3] = p4; cnt++; }
    if(p5 != ' '){ st_parts[4] = p5; cnt++; }
    if(p6 != ' '){ st_parts[5] = p6; cnt++; }

    list_cnts[0] = cnt; 

    return st_parts;
}

int * st_side(int s1, int s2, int s3, int s4, int s5, int s6){
    int cnt = 0;
    if(s1 != 0){ st_sides[0] = s1; cnt++; }
    if(s2 != 0){ st_sides[1] = s2; cnt++; }
    if(s3 != 0){ st_sides[2] = s3; cnt++; }
    if(s4 != 0){ st_sides[3] = s4; cnt++; }
    if(s5 != 0){ st_sides[4] = s5; cnt++; }
    if(s6 != 0){ st_sides[5] = s6; cnt++; }
    
    list_cnts[1] = cnt;  

    return st_sides;
}

int * st_snake_side(int ss1, int ss2, int ss3, int ss4, int ss5, int ss6){
    int cnt = 0;
    if(ss1 != 0){ st_snake_sides[0] = ss1; cnt++; }
    if(ss2 != 0){ st_snake_sides[1] = ss2; cnt++; }
    if(ss3 != 0){ st_snake_sides[2] = ss3; cnt++; }
    if(ss4 != 0){ st_snake_sides[3] = ss4; cnt++; }
    if(ss5 != 0){ st_snake_sides[4] = ss5; cnt++; }
    if(ss6 != 0){ st_snake_sides[5] = ss6; cnt++; }
    
    list_cnts[2] = cnt;  

    return st_snake_sides;
}

void setColor(int color_number){
    if(color_number > 0 && color_number <= num_of_col){
        RED = COLORS[color_number-1][0];
        GREEN = COLORS[color_number-1][1];
        BLUE = COLORS[color_number-1][2];
    }
}

// This functions allows you to set the led color for a specific
// led for the leg
void setLegLed(int side, int row, int column, float brightness){
    // select the specific LED
    int led_position = 0;
    
    // reduce light 
    double fade = brightness/100;
    int red = round(RED * fade);
    int green = round(GREEN * fade);
    int blue = round(BLUE * fade);

    if(side == 2){ // left
        switch (row){
            case 1:
                led_position = 0 + column -1;
                break;
            case 2:
                led_position = 13 + (column*-1) +1;
                break;
            case 3:
                led_position = 14 + column -1;
                break;
            case 4:
                led_position = 25 + (column*-1) +1;
                break;
            case 5:
                led_position = 26 + column -1;
                break;
            default:
                led_position = 0;
                break;
        }
        LEDS_LEG_L[led_position] =  CRGB(red, green, blue);
    }else if(side == 1){ // right
        switch (row){
            case 1:
                led_position = 6 + (column*-1) +1;
                break;
            case 2:
                led_position = 7 + column -1;
                break;
            case 3:
                led_position = 19 + (column*-1) +1;
                break;
            case 4:
                led_position = 20 + column -1;
                break;
            case 5:
                led_position = 31 + (column*-1) +1;
                break;
            default:
                led_position = 0;
                break;
        }
        LEDS_LEG_R[led_position] =   CRGB(red, green, blue);
    }
}


// This functions allows you to set the led color for a specific
// led for the upper body
void setUPBLed(int side, int row, int column, float brightness){
    // select the specific LED
    int led_position = 0;

     // reduce light 
    double fade = brightness/100;
    int red = round(RED * fade);
    int green = round(GREEN * fade);
    int blue = round(BLUE * fade);

    // Serial.print("... recieved col : "); 
    // Serial.println( column);
    

    if(side == 2){ // left
         switch (row){
            case 1:
                led_position = 0 + column -1;
                break;
            case 2:
                led_position = 17 + (column*-1) +1;
                break;
            case 3:
                led_position = 18 + column -1;
                break;
            case 4:
                led_position = 23 + (column*-1) +1;
                break;
            default:
                led_position = 0;
                break;
        }
        LEDS_UPB_L[led_position] =  CRGB(red, green, blue);
    }else if(side == 1){ // right
         switch (row){
            case 1:
                led_position = 0 + column -1;
                break;
            case 2:
                led_position = 14 + column -1;
                break;
            case 3:
                led_position = 21 + (column*-1) +1;
                break;
            case 4:
                led_position = 22 + column -1;
                break;
            default:
                led_position = 0;
                break;
        }
        LEDS_UPB_R[led_position] =   CRGB(red, green, blue);
    }

    // Serial.print("... led pos : "); 
    // Serial.println(led_position);
}
