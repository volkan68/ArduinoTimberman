#include "LCD5110.h"
#include <Button.h>
#include <stdlib.h>

#define LEFT   9
#define RIGHT  8

// Posición del leñador:
int position = 34;

// Puntos obtenidos:
int points = 0;

// Arbol inicial;
int tree[6];

// Dibuja Arbol
void DrawTree(void) {
     char Points[5];
     itoa(points, Points, 10);     
  
     for(int i=0; i<5; i++) {
       if (tree[i] == 34) {
          gotoXY(39, i);
          LcdCharacter(0x5b);
          gotoXY(34, i);
          LcdCharacter(0x5e);          
       } else {
          gotoXY(39, i);
          LcdCharacter(0x5c);
          gotoXY(44, i);
          LcdCharacter(0x5f);
       }
     }
     gotoXY(39, 5);
     LcdCharacter(0x5d);

     gotoXY(2, 0);
     LcdString(Points);
}

// Dibuja Leñador
void DrawTimberman(void) {
     gotoXY(position, 5);
     LcdCharacter(0x60);
}

// Mueve leñador a la izquierda
void MoveLeft(void) {
     int branch;
     
     // Check if branch will fall over the Timberman
     if (tree[4] == 34) {
        gotoXY(54,0);
        LcdString("YOU");
        gotoXY(54,1);
        LcdString("DIE");
        return;
     }
     // Move the tree one notch down
     for(int i=4; i>0; i--) {
        tree[i] = tree[i-1];
     }
     // Put a new branch on top
     branch = random(100);
     if (branch < 50) {
        tree[0] = 34;
     } else {
        tree[0] = 44;
     }

     points++;
     LcdClear();     
     DrawTree();
     gotoXY(34,5);
     LcdCharacter(0x60);
}

// Mueve leñador a la derecha
void MoveRight(void) {
     int branch;
     
     // Check if branch will fall over the Timberman
     if (tree[4] == 44) {
        gotoXY(54,0);
        LcdString("YOU");
        gotoXY(54,1);
        LcdString("DIE");
        return;
     }
     // Move the tree one notch down
     for(int i=4; i>0; i--) {
        tree[i] = tree[i-1];
     }
     // Put a new branch on top
     branch = random(100);
     if (branch < 50) {
        tree[0] = 34;
     } else {
        tree[0] = 44;
     }

     points++;
     LcdClear();
     DrawTree();
     gotoXY(44,5);
     LcdCharacter(0x60);
}

// Configura botones izquierda y derecha
Button leftButton  = Button(LEFT, LOW);
Button rightButton = Button(RIGHT, LOW);

void setup(void)
{
  int branch;
  LcdInitialise();
  LcdClear();
  // Posición inicial de las ramas
  for(int i=0; i<5; i++) {
     branch = random(100);
     if (branch < 50) {
        tree[i] = 34;
     } else {
        tree[i] = 44;
     }
  }
  // Dibuja el Arbol
  DrawTree();
  // Dibuja el leñador
  DrawTimberman();
}

void loop(void)
{
    leftButton.listen();
    rightButton.listen();
    
    if (leftButton.onPress()) {
       MoveLeft();
    }
    
    if (rightButton.onPress()) {
       MoveRight();
    }
}
