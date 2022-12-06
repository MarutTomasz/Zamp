#define ROTATE_SPEED 60
/*
 *   Przykładowy zestaw poleceń
 */

Begin_Parallel_Actions
  Set Ob_A 2 0 30      // Polozenie obiektu A
  Set Ob_B 10 10 0     // Polozenie obiektu B
End_Parallel_Actions

Begin_Parallel_Actions
  Rotate Ob_A ROTATE_SPEED 210
End_Parallel_Actions

Begin_Parallel_Actions
  Pause 1000       /* Zawieszenie działania na 1 sek. */
End_Parallel_Actions

Begin_Parallel_Actions
  Move Ob_A 10 10
  Rotate Ob_A ROTATE_SPEED 30
  Rotate Ob_B ROTATE_SPEED 120
  Move Ob_B 10 20
End_Parallel_Actions
