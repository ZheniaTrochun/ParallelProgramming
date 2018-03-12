with Ada.Text_IO; use Ada.Text_IO;
with Data; use Data;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

--  D = MAX(A + B + C) *(MA*ME)

procedure Main is
  N: Integer := 10;
  A: Integer_Vector(1 .. N);
  B: Integer_Vector(1 .. N);
  C: Integer_Vector(1 .. N);
  MA: Integer_Matrix(1 .. N, 1 .. N);
  ME: Integer_Matrix(1 .. N, 1 .. N);
  D: Integer_Matrix(1 .. N, 1 .. N);

begin
  Put_Line("Lab1 PP started");

  for i in 1..N loop
    A(i) := 1;
    B(i) := 1;
    C(i) := 1;

    for j in 1..N loop
      MA(i, j) := 1;
      ME(i, j) := 1;
    end loop;
  end loop;

  D := Func(A, B, C, MA, ME);

  Put_Line("d = MAX(A + B + C) *(MA*ME) result:");
  Put_Matrix(D);

end Main;
