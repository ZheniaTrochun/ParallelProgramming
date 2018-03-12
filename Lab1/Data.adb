with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

--  d = MAX(A + B + C) *(MA*ME)

package body Data is
  function Func(A,B,C: Integer_Vector; MA,ME: Integer_Matrix) return Integer_Matrix is
    len: Integer := A'Length;
    D: Integer_Matrix(1 .. len, 1 .. len);
    S: Integer_Vector(1 .. len);
    tmp: Integer;
    MU: Integer_Matrix(1 .. len, 1 .. len);

    task T1 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task1");
      pragma Priority(4);
      pragma CPU(0);
    end T1;

    task body T1 is
    begin
      Put_Line("A + B + C started");

      for i in 1 .. len loop
        S(i) := A(i) + B(i) + C(i);
      end loop;

      Put_Line("A + B + C finished");
      Set_True(awaitSum);
    end T1;

    task T2 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task2");
      pragma Priority(4);
      pragma CPU(0);
    end T2;

    task body T2 is
      sum: Integer;
    begin
      Put_Line("MA*ME started");

      for i in 1 .. len loop
        for j in 1 .. len loop
          sum := 0;
            for r in 1 .. len loop
              sum := sum + MA(i,r) * ME(r, j);
            end loop;
          MU(i, j) := sum;
        end loop;
      end loop;

      Set_True(awaitMult);
      Put_Line("MA*ME finished");
    end T2;

    task T3 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task3");
      pragma Priority(4);
      pragma CPU(0);
    end T3;

    task body T3 is
    begin
      Suspend_Until_True(awaitSum);
      Put_Line("MAX(S) started");

      tmp := S(1);

      for i in 1 .. len loop
        if tmp < S(i) then
          tmp := S(i);
        end if;
      end loop;

      Set_True(awaitMax);
      Put_Line("MAX(S) finished");
    end T3;

    begin
      Suspend_Until_True(awaitMult);
      Suspend_Until_True(awaitMax);

      for i in 1 .. len loop
        for j in 1 .. len loop
          D(i,j) := tmp * MU(i,j);
        end loop;
      end loop;

      return D;
    end Func;

    procedure Put_Matrix(M: Integer_Matrix) is
    begin
      for i in 1..M'Length loop
        for j in 1..M'Length loop
          Put(M(i,i));
        end loop;
        New_Line(1);
      end loop;
    end Put_Matrix;

end Data;
