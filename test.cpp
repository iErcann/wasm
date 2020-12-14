#include <fstream>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) < (Y) ? (X) : (Y))

#define SAMPLE 44100.0
#define BUFFER_LENGTH (int)(SAMPLE)

#define C4 (int)(SAMPLE/261.63)
#define D4 (int)(SAMPLE/293.66)
#define E4 (int)(SAMPLE/329.63)
#define F4 (int)(SAMPLE/349.23)
#define G4 (int)(SAMPLE/392.0)
#define A4 (int)(SAMPLE/440.0)
#define B4 (int)(SAMPLE/493.88)
#define C5 C4/2

using namespace std;

void osc(int note, char * buffer, int length){
    int note2 = note/2;
    
    for(int i=0; i<length; i++)
    {
        if(i%note < note2){
            buffer[i] = 0x7f;            
        }
        else{
            buffer[i] = -0x7f;
        }
    }
}

void flush_buffer(ofstream & of, char * buffer, int length){
    for(int j=0;j<length;j++){
        of<<(char)buffer[j];
    }
}

int main()
{
    char buffer[BUFFER_LENGTH]; //1 second buffer
    
    int time = 0;
    
    int notes[]={C4,D4,E4,F4,G4,A4,B4,C5};
    ofstream of("output.raw");
    
    int noteLength = BUFFER_LENGTH/2;
    
    for(int i=0;i<8;i++){
        osc(notes[i], buffer, noteLength);
        flush_buffer(of, buffer, noteLength);
    }
    
    of.close();
}