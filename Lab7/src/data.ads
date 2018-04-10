with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

generic
   n: Integer;
package Data is

   type Vector is array(0..n) of Integer;
   type Matrix is array(0..n) of Vector;
   suspend1: Suspension_Object;
   
   
   function Func(MG, MK, MH: in out Matrix) return Integer;
   
   function multMatrix(m1,m2: Matrix; start, finish: Integer) return Matrix;
   function sumVectors(v1,v2: Vector) return Vector;
   function sumMatrix(m1,m2: Matrix; start, finish: Integer) return Matrix;
   function minInVector(v: Vector) return Integer;
   function minInMatrix(m1: Matrix; start, finish: Integer) return Integer;
   function maxInVector(v: Vector) return Integer;
   function maxInMatrix(m1: Matrix; start, finish: Integer) return Integer;
   function fillVector0 return Vector;
   function fillMatrix0 return Matrix;
   function fillVector1 return Vector;
   function fillMatrix1 return Matrix;
end Data;
