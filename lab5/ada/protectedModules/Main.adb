with Ada.Text_IO; use Ada.Text_IO;
with Data(10); use Data;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

--  q = MAX(MH * MK - ML)

procedure Main is
  N: Integer := 10;

  MH: Integer_Matrix(1 .. N, 1 .. N);
  MK: Integer_Matrix(1 .. N, 1 .. N);
  ML: Integer_Matrix(1 .. N, 1 .. N);

  q: Integer;

begin
  Put_Line("Lab1 PP started");

  for i in 1..N loop
    for j in 1..N loop
      MH(i, j) := 1;
      MK(i, j) := 1;
      ML(i, j) := 1;
    end loop;
  end loop;

  q := Func(MH, MK, ML);

  Put_Line("q = MAX(MH * MK - ML) result:");
  Put(q);

end Main;
