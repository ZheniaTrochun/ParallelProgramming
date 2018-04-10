with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

--  f = MAX(MG * MK) - MIN (MG + MH)

package body Data is
   function Func(MG, MK, MH: in out Matrix) return Integer is
      len: Integer := MG'length;
      res: Integer;
      task T1 is
         entry maxMGxMKsyncT3 (m: Integer);
         entry maxMGxMKsyncT2T4 (m: Integer);
         entry calculated(a: Integer);
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task1");
         pragma Priority(4);
         pragma CPU(0);
      end T1;

      task body T1 is
         result: Integer;
      begin
         result:= maxInMatrix(
                              multMatrix(MG, MK, 0, len / 4 -1),
                              0, len / 4 -1);

         accept maxMGxMKsyncT3(m: Integer) do
            if m > result then
               result:=m;
            end if;
         end maxMGxMKsyncT3;

         accept maxMGxMKsyncT2T4 (m: Integer) do
            if m > result then
               result:=m;
            end if;
         end maxMGxMKsyncT2T4;

         accept calculated(a:Integer) do
            res:= result - a;
         end calculated;
		 
         Set_True(suspend1);
      end T1;

      task T2 is
         entry maxMGxMKsyncT4 (m: Integer);
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task2");
         pragma Priority(4);
         pragma CPU(0);
      end T2;

      task body T2 is
         result: Integer;
      begin
         result:= maxInMatrix(
                              multMatrix(MG, MK, (len / 4),  (len / 2)-1),
                              (len / 4),  (len / 2)-1);

         accept maxMGxMKsyncT4(m: Integer) do
            if m > result then
               result:=m;
            end if;
         end maxMGxMKsyncT4;
         T1.maxMGxMKsyncT2T4(result);
      end T2;

      task T3 is
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task3");
         pragma Priority(4);
         pragma CPU(0);
      end T3;

      task body T3 is
         result: Integer;
      begin
         result:= maxInMatrix(
                              multMatrix(MG, MK, (len / 2), (3*len / 4)-1),
                              (len / 2), (3*len / 4)-1);

         						
         T1.maxMGxMKsyncT3(result);
      end T3;

      task T4 is
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task4");
         pragma Priority(4);
         pragma CPU(0);
      end T4;

      task body T4 is
         result: Integer;
      begin
         result:= maxInMatrix(
                              multMatrix(MG, MK, (3*len / 4), len-1),
                              (3*len / 4), len-1);

						
         
         T2.maxMGxMKsyncT4(result);
      end T4;

      task T5 is
         entry minMGxMHsyncT7 (m: Integer);
         entry minMGxMHsyncT6T8 (m: Integer);
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task5");
         pragma Priority(4);
         pragma CPU(0);
      end T5;
      task body T5 is
         result: Integer;
      begin
         result:= minInMatrix(
                              sumMatrix(MG, MH, 0, len / 4 -1),
                              0, len / 4 -1);

         accept minMGxMHsyncT7(m: Integer) do
            if m > result then
               result:=m;
            end if;
         end minMGxMHsyncT7;

         accept minMGxMHsyncT6T8 (m: Integer) do
            if m < result then
               result:=m;
            end if;
         end minMGxMHsyncT6T8;
		 
         T1.calculated(result);
      end T5;

      task T6 is
         entry minMGxMHsyncT8 (m: Integer);
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task6");
         pragma Priority(4);
         pragma CPU(0);
      end T6;

      task body T6 is
         result: Integer;
      begin
         result:= minInMatrix(
                              sumMatrix(MG, MH, (len / 4),  (len / 2)-1),
                              (len / 4),  (len / 2)-1);

         accept minMGxMHsyncT8(m: Integer) do
            if m < result then
               result:=m;
            end if;
         end minMGxMHsyncT8;
         T5.minMGxMHsyncT6T8(result);
      end T6;

      task T7 is
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task7");
         pragma Priority(4);
         pragma CPU(0);
      end T7;

      task body T7 is
         result: Integer;
      begin
         result:= minInMatrix(
                              sumMatrix(MG, MH, (len / 2), (3*len / 4)-1),
                              (len / 2), (3*len / 4)-1);

         T5.minMGxMHsyncT7(result);
      end T7;

      task T8 is
         pragma Storage_Size (10_000_000);
         pragma Task_Name ("Task8");
         pragma Priority(4);
         pragma CPU(0);
      end T8;

      task body T8 is
         result: Integer;
      begin
         result:= minInMatrix(
                              sumMatrix(MG, MH, (3*len / 4), len-1),
                              (3*len / 4), len-1);

         
         T6.minMGxMHsyncT8(result);
      end T8;
   begin
      Suspend_Until_True(suspend1);
      return res;
   end Func;
   
   
   function multMatrix(m1,m2: Matrix; start, finish: Integer) return Matrix is
      result: Matrix;
      temp: Integer;
   begin
      result := fillMatrix0;
      loop1:
      for i in start .. finish loop

         loop2:
         for j in 0 .. m1'Length - 1  loop
            temp:=0;
            loop3:
            for k in 0 .. m1'Length - 1 loop
               temp:=temp + m1(i)(k) * m2(k)(j);
            end loop loop3;
            result(i)(j) := temp;
         end loop loop2;
      end loop loop1;
      return result;
   end multMatrix;
   
   function sumVectors(v1,v2: Vector) return Vector is
      result: Vector;
   begin
      loop1:
      for i in v1'Range loop
         result(i):=v1(i) + v2(i);
      end loop loop1;
      return result;
   end sumVectors;

   function sumMatrix(m1,m2: Matrix; start, finish: Integer) return Matrix is
      result: Matrix;
   begin
      loop1:
      for i in start..finish loop
         result(i) := sumVectors(m1(i), m2(i));
      end loop loop1;
      return result;
   end sumMatrix;
   
   function minInVector(v: Vector) return Integer is
      result: Integer := 32000;
   begin
      loop1:
      for i in v'range loop
         if v(i) < result then
            result := v(i);
         end if;
      end loop loop1;
      return result;
   end minInVector;
   
   function minInMatrix(m1: Matrix; start, finish: Integer) return Integer is
      result: Integer := 32000;
      temp: Integer;
   begin
      loop1:
      for i in start..finish loop
         temp := minInVector(m1(i));
         if temp < result then
            result := temp;
         end if;
      end loop loop1;
      return result;
   end minInMatrix;
   
   function maxInVector(v: Vector) return Integer is
      result: Integer := -32000;
   begin
      loop1:
      for i in v'range loop
         if v(i) > result then
            result := v(i);
         end if;
      end loop loop1;
      return result;
   end maxInVector;
   
   function maxInMatrix(m1: Matrix; start, finish: Integer) return Integer is
      result: Integer := -32000;
      temp: Integer;
   begin
      loop1:
      for i in start..finish loop
         temp := minInVector(m1(i));
         if temp > result then
            result := temp;
         end if;
      end loop loop1;
      return result;
   end maxInMatrix;

   function fillVector0 return Vector is
      result: Vector;
   begin
      for i in 0..N loop
         result(i) := 0;
      end loop;
      return result;
   end fillVector0;

   function fillMatrix0 return Matrix is
      result: Matrix;
   begin
      for i in 0..N loop
         result(i) := fillVector0;
      end loop;
      return result;
   end fillMatrix0;

   function fillVector1 return Vector is
      result: Vector;
   begin
      for i in 0..N loop
         result(i) := 1;
      end loop;
      return result;
   end fillVector1;

   function fillMatrix1 return Matrix is
      result: Matrix;
   begin
      for i in 0..N loop
         result(i) := fillVector1;
      end loop;
      return result;
   end fillMatrix1;


end Data;
