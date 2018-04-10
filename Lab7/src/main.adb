with Ada.Text_IO; use Ada.Text_IO;
with Data;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

--  f = MAX(MG * MK) - MIN (MG + MH)

procedure Main is
   package data1 is new data(5);
   use data1;
   F:Integer;

   MG: Matrix;
   MK: Matrix;
   MH: Matrix;

begin
   MG := fillMatrix1;
   MK := fillMatrix1;
   MH := fillMatrix1;

   F := Func(MG, MK, MH);

   Put_Line("Result:");
   Put(F);

end Main;
