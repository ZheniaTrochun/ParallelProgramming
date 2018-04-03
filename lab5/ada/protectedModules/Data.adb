with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;
with CountdownPackage;
use CountdownPackage;

--  q = MAX(MH * MK - ML)

package body Data is
  function Func(MH,MK,ML: Integer_Matrix) return Integer is
    len: Integer := A'Length;
    tmp: Integer_Matrix(1 .. len, 1 .. len);
    max: Integer;

    task T1 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task1");
      pragma Priority(4);
      pragma CPU(0);
    end T1;

    task body T1 is
    begin

      mult_part(MH, MK, tmp, 1, len / 4);

    end T1;

    task T2 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task2");
      pragma Priority(4);
      pragma CPU(0);
    end T2;

    task body T2 is
    begin

      mult_part(MH, MK, tmp, (len / 4) + 1, len / 2);

    end T2;

    task T3 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task3");
      pragma Priority(4);
      pragma CPU(0);
    end T3;

    task body T3 is
    begin

      mult_part(MH, MK, tmp, (len / 2) + 1, 3 * len / 4);

    end T3;

    task T4 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task4");
      pragma Priority(4);
      pragma CPU(0);
    end T4;

    task body T4 is
    begin

      mult_part(MH, MK, tmp, (3 * len / 4) + 1, len);

    end T4;


    begin
      countdown.Secure;

      for i in 1 .. len loop
        for j in 1 .. len loop
          tmp(i,j) := tmp(i,j) - ML(i,j);
        end loop;
      end loop;

      max := tmp(1,1);

      for i in 1 .. len loop
        for j in 1 .. len loop
          if max < tmp(i,j) then
            max := tmp(i,j);
          end if;
        end loop;
      end loop;

      return max;
    end Func;

    procedure Mult_Part(MH, MK, tmp: Integer_Matrix; start, finish: Integer) is
    begin
      for i in start..finish loop
        for j in 1..MH'Length loop
          tmp(i,j) := 0;

          for k in 1..MH'Length loop
            tmp(i,j) := tmp(i,j) + (MH(i,k) * MK(k,j));
          end loop;

        end loop;
      end loop;

      countdown.Release;
    end Mult_Part;

end Data;
